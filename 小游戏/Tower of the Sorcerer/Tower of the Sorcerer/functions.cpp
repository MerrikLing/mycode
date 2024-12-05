#include"head.hpp"

//ײǽ���
int judge_hit(int value)
{
	if (value == 0 || value == 1)
	{
		//printf("ײǽ��\n");
		return 0;
	}
	return 1;
}
//ûײǽʱ
// ����������
void set_new_position(int position[], int r, int c)
{
	position[1] = r;
	position[2] = c;
}

//��ս
void PK(Player& p, const Monster& m)
{
	int l = m.hp;
	if (p.atk - m.def >= l)  //һ������
		return;
	while (p.hp > 0 && l > 0)
	{
		if (p.def < m.atk)
			p.hp -= m.atk - p.def;
		if (m.def < p.atk)
			l -= p.atk - m.def;
	}
	if (p.hp < 0)
		p.hp = 0;
}

//ս��
int Battle(int map[][COL], Player& p, Monster& m, char* name, \
	int r1, int c1, int r, int c, int hp)//��������
{
	PK(p, m);
	if (p.hp)//����Ѫ�������ִ��
	{
		//�ĵ�ͼ
		map[r1][c1] = 7;
		map[r][c] = 8;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]],p);
		//printf("You've beaten the %s!\nYou lost %d HP in the battle\nYou get %d gold coin and get %d Exp\n", \
		//	name, hp - p.hp, m.money, m.exp);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //ͼ�λ�չʾ��Ϣ
		p.money += m.money;
		p.Exp += m.exp;

		_kbhit();
		return 0;
	}
	//�������û���
	set_new_position(p.position, r1, c1);
	return 2; //����

}

//����ƶ�
// ��Ҫ��ǰ��ͼ�����λ�ã��ṩ����ֵ����¥ 1������ 0����¥ -1��
// ���������һ���� (��������������������ң�����)

int move(int map[][COL],Player &p)
{
	int r = p.position[1];
	int c = p.position[2];
	//����
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	while(1)               //��ȡ����,��ȷ����ȷ���룬��ûײǽ
	{    //bug �����ߵ�ǽ���棡ԭ��û������r��c
		switch (_getch()) {
		case 'w': // ��
			r -= 1;
			if(judge_hit(map[r][c]))//ûײǽ��ִ��
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//����
			r = r1;c = c1;
			break;
		case 's': // ��
			r += 1;
			if (judge_hit(map[r][c]))//ûײǽ��ִ��
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//����
			r = r1;c = c1;
			break;
		case 'a': // ��
			c -= 1;
			if (judge_hit(map[r][c]))//ûײǽ��ִ��
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//����
			r = r1;c = c1;
			break;
		case 'd': // ��
			c += 1;
			if (judge_hit(map[r][c]))//ûײǽ��ִ��
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//����
			r = r1;c = c1;
			break;
		default:
			//printf("�����������������\n");
			break;
		}
	}
next:  
	//�޸ĵ�ͼ�����������Ϊ area 7�����ڵ���������Ϊ player 8
	//�յ�
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		return 0;
	}
	//Կ��
		//��ɫ
	if (map[r][c] == 4)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.yellow_key += 1;
		return 0;
	}
	//�ţ���û��Կ��  
		// 5������ɫ��
	if (map[r][c] == 5)
	{
		if (p.yellow_key < 1)
		{
			//printf("Your yellows keys is not enough! \nGo around and find one!\n");
			//�������û���
			set_new_position(p.position, r1, c1);
			_kbhit();
			return 0;
		}
		//��Կ��
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.yellow_key -= 1;
		return 0;
	}

	//�����������ܣ����ܻ��þ�������   �ж�Ѫ��
		//ʷ��ķ�� 6
	if (map[r][c] == 6)
	{   
		char gs[]= "Green Slime";//��������
		return Battle(map, p, GreenSlime, gs, r1, c1, r, c, hp);
	}
		//����   30 bat B   
	if (map[r][c] == 30)
	{
		char bt[] = "Bat";//��������
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp);
	}
		//����  31 ���� S 
	if (map[r][c] == 31)
	{
		char sk[] = "Skeleton";//��������
		return Battle(map, p, Skeleton, sk, r1, c1, r, c, hp);
	}


	// ҩˮ   2 - minor_healing_potion h  3 - moderate_healing_potion H
		//minor
	if (map[r][c] == 2)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.hp += 20;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]],p);
		//printf("You find a minor healing potion and get 20 hp");
		char name[] = "Minor Healing Potion";
		PrintInfor(name, 20);
		_kbhit();
		return 0;
	}
		//moderate
	if (map[r][c] == 3)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.hp += 50;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]],p);
		//printf("You find a moderate healing potion and get 50 hp");
		char name[] = "Moderate Healing Potion";
		PrintInfor(name, 50);
		_kbhit();
		return 0;
	}

	//��¥����¥  11 upstairs +   12 downstairs -
	  //��
	if (map[r][c] == 11)
	{
		map[r1][c1] = 7;
		p.position[0] += 1; //��һ��
		return 1;
	}
		//��
	if (map[r][c] == 12)
	{
		map[r1][c1] = 7;
		p.position[0] -= 1; //��һ��
		return -1;
	}
	// ˮ��
	// ������Ʒ��
	return 0;
}


//void display_map(int map[][COL])
//{
//	system("cls");
//	for (int i = 0;i < ROW;i++)
//	{
//		for (int j = 0;j < COL;j++)
//		{
//			switch (map[i][j]) //��ӡÿ�е�ͼ
//			{
//			case 0:
//				printf("#");
//				break;
//			case 1:
//				printf("#");
//				break;
//			case 2:
//				printf("h");
//				break;
//			case 3:
//				printf("H");
//				break;
//			case 4:
//				printf("k");
//				break;
//			case 5:
//				printf("d");
//				break;
//			case 6:
//				printf("s");
//				break;
//			case 7:
//				printf(" ");
//				break;
//			case 8:
//				printf("P");
//				break;
//			case 9:
//				printf("T");
//				break;
//			case 11:
//				printf("+");
//				break;
//			case 12:
//				printf("-");
//				break;
//			case 30:
//				printf("B");
//				break;
//			case 31:
//				printf("S");
//				break;
//			default:
//				printf("��ͼ��������");
//			}
//		}
//		printf("\n");
//	}
//}
