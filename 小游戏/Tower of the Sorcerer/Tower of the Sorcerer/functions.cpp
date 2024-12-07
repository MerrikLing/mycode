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

//����
//����Ҫ���ݶ�Ϊ��50*Lv;   ע�����������������
//������Ѫ���� 100�� ���� ��5�������� 5
void LvUp(Player& p)
{
	p.hp += 100;
	p.atk += 5;
	p.def += 5;
	PrintLvUp();
}

void Judge_and_LvUp(Player& p)
{
	while (p.Exp >= p.Lv * 50)
	{
		p.Exp -= p.Lv * 50;
		LvUp(p);
	}
}


//ս��
int Battle(int map[][COL], Player& p, Monster& m, char* name, \
	int r1, int c1, int r, int c, int hp,int direction_picture_number)//��������
{
	PK(p, m);
	if (p.hp)//����Ѫ�������ִ��
	{
		//�ĵ�ͼ
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]],p);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //ͼ�λ�չʾ��Ϣ
		p.money += m.money;
		p.Exp += m.exp;
		Judge_and_LvUp(p);
		return 0;
	}
	//�������û���
	set_new_position(p.position, r1, c1);
	return 2; //����

}



int ValidMove(int map[][COL], Player& p, int r, int c, int r1, int c1, int direction_picture_number)
{
	int hp = p.hp;
	//�յ�
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}
	//Կ��
		//��ɫ
	if (map[r][c] == 4)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key += 1;
		return 0;
	}
	//�ţ���û��Կ��  
		// 5������ɫ��
	if (map[r][c] == 5)
	{
		if (p.yellow_key < 1)
		{
			//�������û���
			set_new_position(p.position, r1, c1);
			PrintNoKey();
			return 0;
		}
		//��Կ��
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key -= 1;
		return 0;
	}

	//�����������ܣ����ܻ��þ�������   �ж�Ѫ��
		//ʷ��ķ�� 6
	if (map[r][c] == 6)
	{
		char gs[] = "Green Slime";//��������
		return Battle(map, p, GreenSlime, gs, r1, c1, r, c, hp, direction_picture_number);
	}
	//����   30 bat B   
	if (map[r][c] == 30)
	{
		char bt[] = "Bat";//��������
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp, direction_picture_number);
	}
	//����  31 ���� S 
	if (map[r][c] == 31)
	{
		char sk[] = "Skeleton";//��������
		return Battle(map, p, Skeleton, sk, r1, c1, r, c, hp, direction_picture_number);
	}


	// ҩˮ   2 - minor_healing_potion h  3 - moderate_healing_potion H
		//minor
	if (map[r][c] == 2)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.hp += 20;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]], p);
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
		map[r][c] = direction_picture_number;
		p.hp += 50;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]], p);
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

int afterPress(int map[][COL], Player& p,int r,int c,int r1,int c1,int direction_picture_number)
{
	if (judge_hit(map[r][c]))//ûײǽ��ִ��
	{
		set_new_position(p.position, r, c);
		return ValidMove(map, p, r, c, r1, c1, direction_picture_number);
	}
	//����
	r = r1;c = c1;
	return 19;//��ʾ��Ч����
}

int move(int map[][COL],Player &p)    //����ƶ�
{
	int r = p.position[1];
	int c = p.position[2];
	//����
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	int ret;   //����afterPress��ֵ�����ж�

	//����һ�ַ�ʽ�����⣬��һ�����ߺü�������ͨ��sleep���
	while (true)
	{
		Sleep(80);
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('a') & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
		{ // ������
			ret=afterPress(map, p, r, c - 1, r1, c1,35);//35��������زĵı��
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // ����Ҽ�
			ret = afterPress(map, p, r, c + 1, r1, c1,36);//����
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // ����ϼ�
			ret = afterPress(map, p, r-1, c , r1, c1,37);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // ����¼�
			ret = afterPress(map, p, r + 1, c, r1, c1,8);
			if (ret != 19)
				return ret;
		}
	}
}

//��������Ŀ���̨�汾�ĺ���ʵ�ֲ���

		// ����̨�汾����Ҫ��������ηŵ�ѭ�����棡
		////bug �����ߵ�ǽ���棡ԭ��û������r��c
		//switch (_getch()) {
		//case 'W':
		//case 72:
		//case 'w': // ��
		//	r -= 1;
		//	if(judge_hit(map[r][c]))//ûײǽ��ִ��
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//����
		//	r = r1;c = c1;
		//	break;
		//case 'S':
		//case 80:
		//case 's': // ��
		//	r += 1;
		//	if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//����
		//	r = r1;c = c1;
		//	break;
		//case 'A':
		//case 75:
		//case 'a': // ��
		//	c -= 1;
		//	if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//����
		//	r = r1;c = c1;
		//	break;
		//case 'D':
		//case 77:
		//case 'd': // ��
		//	c += 1;
		//	if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//����
		//	r = r1;c = c1;
		//	break;
		//default:
		//	//printf("�����������������\n");
		//	break;
		//}

	//}


//����̨�汾��ͼ�λ�
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

//��һ�ֳ����ü��̿��Ƶ�ʧ�ܷ�������֪��������
	//MSG msg;
	//while(1)               //��ȡ����,��ȷ����ȷ���룬��ûײǽ
	//{    
		////���в��ˣ���
		//// ʹ��GetMessage����Ϣ�����л�ȡ��Ϣ
		//GetMessage(&msg,NULL, 0, 0);

		//// �����Ϣ�����Ƿ�Ϊ���̰����¼�
		//if (msg.message == WM_KEYDOWN)
		//{
		//	switch (msg.wParam)
		//	{
		//	case 'A':
		//	case 'a':
		//	case VK_LEFT: // ���
		//		c -= 1;
		//		if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//����
		//		r = r1;c = c1;
		//		break;

		//	case 'D':// �Ҽ�
		//	case 'd':
		//	case VK_RIGHT:
		//		c += 1;
		//		if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//����
		//		r = r1;c = c1;
		//		break;

		//	case 'W':
		//	case 'w':
		//	case VK_UP: // �ϼ�
		//		r -= 1;
		//		if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//����
		//		r = r1;c = c1;
		//		break;

		//	case 'S':
		//	case 's':
		//	case VK_DOWN: // �¼�
		//		r += 1;
		//		if (judge_hit(map[r][c]))//ûײǽ��ִ��
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//����
		//		r = r1;c = c1;
		//		break;

		//	default:
		//		break;
		//	}
		//}
