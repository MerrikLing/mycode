#include"head.hpp"
int OfferMoneyTimes = 0;//�����Ů����Ĵ���
int meetSage = 0;
int meetPrincess = 0;

//ײǽ���
int judge_hit(int value)
{
	if (value == 0 || value == 1 || value == 52 || value == 53)
	{
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
	p.hp -= Damage(p, m);
}

//������������˺�
int Damage(Player& p, const Monster& m)
{
	int hp = p.hp;
	int l = m.hp;
	if (p.atk - m.def >= l)  //һ������
		return 0;
	while (hp > 0 && l > 0)
	{
		if (p.def < m.atk)
			hp -= m.atk - p.def;
		if (m.def < p.atk)
			l -= p.atk - m.def;
	}
	if (hp <= 0)
		return p.hp; //����
	else
		return p.hp - hp;
}

//����
//����Ҫ���ݶ�Ϊ��50*Lv;   ע�����������������
//������Ѫ���� 100�� ���� ��5�������� 5
void LvUp(Player& p)
{
	p.hp_limit += 50;
	p.atk += 2;
	p.def += 2;
	p.Lv += 1;
	musicLvUp();
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

void MeetGodness(Player& p, int map[][COL], int r1,int c1,int r,int c)   //������Ҫ��ʧ��
{
	if (OfferMoneyTimes == 2 && meetPrincess==0)
	{
		//����������û��� //Ů������ʧ��
		set_new_position(p.position, r1, c1);
		return;
	}
	musicMeet();
	int cost = 50* (OfferMoneyTimes + 1);
	std::string message1 = "\n\nWould you like to offer \n" + std::to_string(cost) + " gold coins to the goddess?\n\nYes: 1  NO: 2";
	std::string message2 = "\n\nWould you offer all your money\nto the goddess for a miracle?\n\nYes: 1  NO: 2";
	char message3[] = "\n\n\nA new entrance is now opened";
	if (OfferMoneyTimes < 2)
		PrintSpecialInfor(message1.c_str());
	//else if (OfferMoneyTimes == 2 && meetPrincess) //�Ѿ�����������,��������������֮��
	//	PrintSpecialInfor(message2.c_str());

	if (OfferMoneyTimes == 2 && meetPrincess)//�����ι����������������֮��
	{
		PrintSpecialInfor(message2.c_str());
		while (1)
		{
			Sleep(70);
			if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) //ͬ��
			{
				while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
					Sleep(30);
				OfferMoneyTimes += 1;
				map[r][c] = 7;   //Ů������ʧ
				//����������û��� 
				set_new_position(p.position, r1, c1);
				p.money = 0;
				musicLvUp();
				Map[2][8][11] = 11;//����¥����¥��,��Ҫ��ά���飡
				PrintSpecialInfor(message3);
				exit();
				return;
			}

			if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) //��ͬ��
			{
				while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
					Sleep(30);
				//����������û���
				set_new_position(p.position, r1, c1);
				return;
			}
		}
	}

	while (1)  //ǰ���ι���
	{
		Sleep(70);
		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) //ͬ��
		{
			while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
				Sleep(30);
			if (p.money >=  cost)
			{
				p.money -=  cost;
				OfferMoneyTimes += 1;
				if (OfferMoneyTimes == 1)
				{
					map[r][c] = 7;   //Ů������ʧ
					//����������û���
					set_new_position(p.position, r1, c1);
					PrintSpecialInfor("\n\n\nYou get nothing!");
					Sleep(600);
					return;
				}//ɶ��û�У�������
				else if (OfferMoneyTimes == 2)//��һ��������ʯ
				{
					musicLvUp();
					int defence = 2;
					p.def += defence;
					PrintLifeGem(defence);
					//Ů������ʧ��
					//����������û���
					set_new_position(p.position, r1, c1);
					return;
				}
				else
					return;
			}
			else
			{
				//����������û���
				set_new_position(p.position, r1, c1);
				PrintSpecialInfor("\n\n\nYour money is not enough!");
				Sleep(600);
				return;
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) //��ͬ��
		{
			while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
				Sleep(30);
			//����������û���
			set_new_position(p.position, r1, c1);
			return;
		}
	}
}

int ValidMove(int map[][COL], Player& p, int r, int c, int r1, int c1, \
	int direction_picture_number,int direction) //direction 4 5 6 7�ֱ��ʾ��������
{
	int hp = p.hp;

	if (map[r][c] == 39)  //�ҵ���������ʤ��
	{
		meetPrincess += 1;
		set_new_position(p.position, r1, c1);//�������û���
		if (meetPrincess == 1)
		{
			musicMeet();
			PrintFalsePrincess();
			map[r][c] = 7;//�ٹ�����ʧ
			return 0;
		}
		return 3;//ʤ��
	}

	//�յ�
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	if (map[r][c] == 51) //����
	{
		meetSage += 1;
		set_new_position(p.position, r1, c1);//�������û���
		musicMeet();
		if(meetSage==1)
		{
			char message1[] = "\n\nThe tower seems a bit strange\n\nI'm not sure if Princess is here";
			char message2[] = "\n\nThe tower is extremely dangerous\n\nThis is the Magic Book";
			char message3[] = "\n\nIt can turn souls of the monsters \n\nkilled into Exp to strengthen you";
			char message4[] = "\n\nThe Monster Encyclopedia in it \n\ncontains the information I know\n(Press e to open or close)";
			char message5[] = "\nAlso\n\nthere might be something good\n\n on the third floor";
			char message6[] = "\n\nRemember,solving a problem is  \n\nnever confined to a single way";
			char message7[] = "\n\n\nGood luck to you!";
			PrintSpecialInfor(message1);
			exit();
			PrintSpecialInfor(message2);
			exit();
			PrintSpecialInfor(message3);
			exit();
			PrintSpecialInfor(message4);
			exit();
			PrintSpecialInfor(message5);
			exit();
			PrintSpecialInfor(message6);
			exit();
			PrintSpecialInfor(message7);
			exit();
		}
		else
		{
			//char message1[] = "\n\nGood job!\n\nYou've made it to the second floor";
			char message1[] = "\n\nI've found Princess is here,\n\nbut I'm little confused...";
			char message2[] = "\n\nBy the way,\n\nDef may weigh more than Ack";
			char message3[] = "\n\nHere is a Moderate Healing Potion.\n\nGood luck!";
			PrintSpecialInfor(message1);
			exit();
			PrintSpecialInfor(message2);
			exit();
			PrintSpecialInfor(message3);
			exit();
			//����еȻָ�ҩˮ
			musicPickup();
			if (p.hp + 50 > p.hp_limit)
			{
				p.hp = p.hp_limit;
			}
			else
			{
				p.hp += 50;
			}
			char name[] = "Moderate Healing Potion";
			PrintInfor(name, p.hp - hp);
		}
		map[r][c] = 7;//������ʧ
		return 0;
	}
	//Կ��
		//��ɫ
	if (map[r][c] == 4)
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key += 1;
		return 0;
	}

	if (map[r][c] == 17)  //��ɫԿ��
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.blue_key += 1;
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
		musicEnter();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key -= 1;
		return 0;
	}

	if (map[r][c] == 18)   //��ɫ��
	{
		if (p.blue_key < 1)
		{
			//�������û���
			set_new_position(p.position, r1, c1);
			PrintNoKey();
			return 0;
		}
		//��Կ��
		musicEnter();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.blue_key -= 1;
		return 0;
	}

	//�����������ܣ����ܻ��þ�������   �ж�Ѫ��
		//��ɫʷ��ķ�� 6
	if (map[r][c] == 6)
	{
		musicBattle();
		char name[] = "Green Slime";//��������
		return Battle(map, p, GreenSlime, name, r1, c1, r, c, hp, direction_picture_number);
	}

	//��ɫʷ��ķ�� 9
	if (map[r][c] == 9)
	{
		musicBattle();
		char name[] = "Red Slime";//��������
		return Battle(map, p, RedSlime, name, r1, c1, r, c, hp, direction_picture_number);
	}

	//����   30 bat B   
	if (map[r][c] == 30)
	{
		musicBattle();
		char bt[] = "Bat";//��������
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp, direction_picture_number);
	}
	//����  31 ���� S 
	if (map[r][c] == 31)
	{
		musicBattle();
		char name[] = "Skeleton";//��������
		return Battle(map, p, Skeleton, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//����ʿ��  32  
	if (map[r][c] == 32)
	{
		musicBattle();
		char name[] = "Skeleton Soldier";//��������
		return Battle(map, p, SkeletonSoldier, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//��ʦ  33  
	if (map[r][c] == 33)
	{
		musicBattle();
		char name[] = "Wizard";//��������
		return Battle(map, p, Wizard, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//ħ��  38  
	if (map[r][c] == 38)
	{
		musicBattle();
		char name[] = "Demon King";//��������
		return Battle(map, p, DemonKing, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//����սʤ��ħ�� 54
	if (map[r][c] == 54)
	{
		musicBattle();
		char name[] = "Demon Emperor";//��������
		return Battle(map, p, DemonEmperor, name, r1, c1, r, c, hp, direction_picture_number);
	}
	// ҩˮ   2 - minor_healing_potion h  3 - moderate_healing_potion H
		//minor
	if (map[r][c] == 2)
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		if (p.hp + 20 > p.hp_limit)
		{
			p.hp = p.hp_limit;
		}
		else
		{
			p.hp += 20;
		}
		PrintMap(Map[p.position[0]], p);
		char name[] = "Minor Healing Potion";
		PrintInfor(name, p.hp - hp);
		_kbhit();
		return 0;
	}
	//moderate
	if (map[r][c] == 3)
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		if (p.hp + 50 > p.hp_limit)
		{
			p.hp = p.hp_limit;
		}
		else
		{
			p.hp += 50;
		}
		PrintMap(Map[p.position[0]], p);
		char name[] = "Moderate Healing Potion";
		PrintInfor(name, p.hp - hp);
		return 0;
	}

	if (map[r][c] == 22)//��
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.def += 10;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		char name[] = "Boko Shield";
		PrintShield(name,10); //������10
		return 0;
	}

	if (map[r][c] == 21)//��
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.atk += 10;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		char name[] = "Boko Sword";
		PrintSword(name, 10); //������10
		return 0;
	}

	if (map[r][c] == 24)//����
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.pickaxe += 1;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		char message[] = "\n\n\nYou get a Pickaxe!";
		PrintSpecialInfor(message);
		exit();
		return 0;
	}

	if (map[r][c] == 20)//������ʯ
	{
		int defence = 2;

		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.def += defence;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		PrintLifeGem(defence);
		return 0;
	}

	if (map[r][c] == 19)//������ʯ
	{
		int attack = 2;

		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.atk += attack;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		PrintAttackGem(attack);
		return 0;
	}
	
	if (map[r][c] == 50) //Ů����
	{
		MeetGodness(p,map,r1,c1,r,c);
		return 0;
	}
	//��¥����¥  11 upstairs +   12 downstairs -
	  //��
	if (map[r][c] == 11)
	{
		map[r1][c1] = 7;
		p.position[0] += 1; //��һ��
		return direction;
	}
	//��
	if (map[r][c] == 12)
	{
		map[r1][c1] = 7;
		p.position[0] -= 1; //��һ��
		return direction;
	}
	
	return 0;
}

int afterPress(int map[][COL], Player& p,int r,int c,int r1,int c1,\
	int direction_picture_number,int direction)//4 5 6 7�ֱ��ʾ��������
{
	if (judge_hit(map[r][c]))//ûײǽ��ִ��
	{
		set_new_position(p.position, r, c);
		return ValidMove(map, p, r, c, r1, c1, direction_picture_number,direction);
	}
	//����
	r = r1;c = c1;
	return 19;//��ʾ��Ч����
}

int play(int map[][COL],Player &p)    //����ƶ�
{
	int r = p.position[1];
	int c = p.position[2];
	//direction 
	int up = 4;int down = 5;int left = 6;int right = 7;
	//����
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	int ret;   //����afterPress��ֵ�����ж�

	//��һ�����ߺü�������ͨ��sleep���
	while (true)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('a') & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
		{ // ������
			while ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			{
				Sleep(30);
			}//ʵ��һ��һ�����ɿ�ʱ���ƶ�
			ret=afterPress(map, p, r, c - 1, r1, c1,35,left);//35��������زĵı��
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // ����Ҽ�
			while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r, c + 1, r1, c1,36,right);//����
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // ����ϼ�
			while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r-1, c , r1, c1,37,up);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // ����¼�
			while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r + 1, c, r1, c1,8,down);
			if (ret != 19)
				return ret;
		}

		//���� p
		else if ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
		{ // ���p��
			while ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
			{
				Sleep(30);
			}
			if (p.pickaxe <= 0)
				continue;
			char message[] = "\n\n\nYou have destroyed a wall!";
			PrintUsePickaxe();
			//Sleep(200);
			while (true)
			{
				if ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
				{//�ٴΰ� p ȡ��
					while ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
					{
						Sleep(30);
					}
					return 0;
				}
				else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
				{ // ���� ���
					while ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r][c - 1] == 1)
					{
						PrintMessage(message);
						map[r][c - 1] = 7;
						p.pickaxe -= 1;
					}
					return 0;
				}

				else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
				{ // ���� �Ҽ�
					while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r][c + 1] == 1)
					{
						PrintMessage(message);
						map[r][c + 1] = 7;
						p.pickaxe -= 1;
					}
					return 0;
				}

				else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
				{ // ���� �ϼ�
					while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r - 1][c] == 1)
					{
						PrintMessage(message);
						map[r - 1][c] = 7;
						p.pickaxe -= 1;
					}
					return 0;
				}

				else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
				{ // ���� �¼�
					while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r + 1][c] == 1)
					{
						PrintMessage(message);
						map[r + 1][c] = 7;
						p.pickaxe -= 1;
					}
					return 0;
				}
			}
		}

		//ͼ�� e
		else if ((GetAsyncKeyState('e') & 0x8000) || (GetAsyncKeyState('E') & 0x8000) && meetSage)
		{ // ���e��
			while ((GetAsyncKeyState('e') & 0x8000) || (GetAsyncKeyState('E') & 0x8000))
			{
				Sleep(30);
			}
			musicEncyclopedia();
			MonsterEncyclopedia(p);
			return 0;
		}
		//�˳���
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			return -12;
		}
	}
	return 0;
}

 //�˴���������map������¥��ģ�
void ChangeFloor(int Map[FLOOR][ROW][COL],Player& P,int ret)
{
	musicEnter();
	if (ret == 4 && Map[P.position[0]][P.position[1] - 1][P.position[2]] == 7)//���ϲ���¥����һ���ǿ�
	{
		P.position[1] -= 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else if (ret == 5 && Map[P.position[0]][P.position[1] + 1][P.position[2]] == 7)
	{
		P.position[1] += 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else if (ret == 6 && Map[P.position[0]][P.position[1]][P.position[2] - 1] == 7)
	{
		P.position[2] -= 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else if (ret == 7 && Map[P.position[0]][P.position[1]][P.position[2] + 1] == 7)
	{
		P.position[2] += 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}

	//Ĭ��λ��:����һ���ǿգ����ϣ�����ȥ�����Ŀյ�
	else if (Map[P.position[0]][P.position[1] - 1][P.position[2]] == 7)
	{
		P.position[1] -= 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else if (Map[P.position[0]][P.position[1] + 1][P.position[2]] == 7)
	{
		P.position[1] += 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else if (Map[P.position[0]][P.position[1]][P.position[2] + 1] == 7)
	{
		P.position[2] += 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
	else
	{
		P.position[2] -= 1;
		Map[P.position[0]][P.position[1]][P.position[2]] = 8;
	}
}

//�������Ŀ���̨�汾�ĺ���ʵ�ֲ���

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
