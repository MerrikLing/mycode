#include"head.hpp"
//int OfferMoneyTimes = 0;//�����Ů����Ĵ���
int meetSage = 0;
int meetPrincess = 0;
int wizardReward = 0;

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

	int atk = p.atk + (5 + p.Lv*3) * p.enhancedAtk;
	p.enhancedAtk = 0;//����
	if (p.backpack[CROSS])//ʮ�ּܿ���ʹ�������������
	{
		if (m.isSkeleton)
			atk *= 1.5;
	}
	if (atk - m.def >= l)  //һ�������������˺�����
	{
		if (m.atk > p.def)
		{
			hp -= (m.atk - p.def) / 2;
			return p.hp - hp;
		}
		else
			return 0;
	}
	//��һ�ֹ���Ҫ����ӥ��
	if (p.def < m.atk)
		hp -= m.atk - p.def;
	if (m.def < atk)
		l -= atk - m.def;
	
	atk = p.atk;    //�����ù���
	if (p.backpack[CROSS])//ʮ�ּܿ���ʹ�������������
	{
		if (m.isSkeleton)
			atk *= 1.5;
	}
	while (hp > 0 && l > 0)
	{
		if (p.def < m.atk)
			hp -= m.atk - p.def;
		if (m.def < atk)
			l -= atk - m.def;
	}
	if (hp <= 0)
		return p.hp; //����
	else
		return p.hp - hp;
}

//����
//����Ҫ���ݶ�Ϊ��50*Lv;   ע�����������������
//������Ѫ�����޼� 50�� ���� ��2�������� 2
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
		p.killnumber += 1;
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]],p);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //ͼ�λ�չʾ��Ϣ
		p.money += m.money;
		p.Exp += m.exp;
		if (p.backpack[EAGLEFLAG])//ӥ�������Ѫ 10%
		{
			int recovery = p.hp_limit - p.hp > m.hp / 10 ? m.hp / 10 : p.hp_limit - p.hp;
			PrintBattleRecovery(recovery);
			p.hp += recovery;
		}
		Judge_and_LvUp(p);

		//1%���ʵ���ʳ��
		srand((unsigned int)time(NULL));
		int randomNum = rand() % 300;
		if (randomNum == 100)   //ƻ��
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get an apple!");exit();
			p.backpack[2] += 1;
			return 0;
		}
		if (randomNum == 200)   //����
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get grapes!");exit();
			p.backpack[3] += 1;
			return 0;
		}
		if (randomNum == 0)   //��
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get fish!");exit();
			p.backpack[4] += 1;
			return 0;
		}
		return 0;
	}
	//ʧ�ܣ��������û���
	set_new_position(p.position, r1, c1);
	return 2; //����

}

int YesOrNo()//����1��yes������1������2��no������0
{
	while (1)
	{
		Sleep(70);
		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) //yes
		{
			while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
			{
				Sleep(30);
			}
			return 1;
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) //no
		{
			while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
			{
				Sleep(30);
			}
			return 0;
		}
	}
}
void MeetGodness(Player& p, int map[][COL], int r1,int c1,int r,int c)   //������Ҫ��ʧ��
{
	musicMeet();
	//�򿪵��Ĳ�ͨ��
	if (meetPrincess)
	{
		std::string message1 = "\nWould you offer all your money\n\nto the goddess for a miracle?\n\nYes: 1  NO: 2";
		char message2[] = "\n\n\nA new entrance is opened";
		PrintSpecialInfor(message1.c_str());
		if (YesOrNo())//ͬ��
		{
			map[r][c] = 7;   //Ů������ʧ
			//����������û��� 
			set_new_position(p.position, r1, c1);
			p.money = 0;
			musicLvUp();
			Map[2][8][1] = 11;//����¥����¥��,��Ҫ��ά���飡
			PrintSpecialInfor(message2);
			exit();
			return;
		}   //��Ϊ��ͬ��
		//����������û���
		set_new_position(p.position, r1, c1);
		return;
	}
	
	//��ͨ���̵�Ĵ�����
	if (1 == p.position[0] && 6 == r && 8 == c)
	{
		std::string message1 = "\nWould you like to offer \n\n" + std::to_string(p.money) + " gold coins to the goddess?\n\n(Yes: 1  NO: 2)";
		char message2[] = "\n\n\nA new entrance is opened";
		PrintSpecialInfor(message1.c_str());
		if (YesOrNo())  //yes
		{   
			musicLvUp();
			PrintSpecialInfor(message2);exit();
			map[r][c] = 7;   //Ů������ʧ
			//����������û���
			set_new_position(p.position, r1, c1);
			p.money = 0;
			Map[1][7][12] = 73;
			return;
		}
		//����������û���
		set_new_position(p.position, r1, c1);
		return;
	}
	//��ͨ��ThreeD��¥��
	if (TwoD == p.position[0] && 2 == r && 5 == c)
	{
		int cost = 50;
		std::string message1 = "\nWould you like to offer \n\n" + std::to_string(cost) + " gold coins to the goddess?\n\n(Yes: 1  NO: 2)";
		char message2[] = "\n\n\nA new entrance is opened";
		PrintSpecialInfor(message1.c_str());
		if (YesOrNo())  //yes
		{
			if (p.money >= cost)
			{
				p.money -= cost;
				musicLvUp();
				PrintSpecialInfor(message2);exit();
				Map[TwoD][2][5] = 11;   //Ů������ʧ
				//����������û���
				set_new_position(p.position, r1, c1);
				return;
			}
			else
			{
				PrintSpecialInfor("\n\n\nYour money is not enough!");
				Sleep(600);
				//����������û���
				set_new_position(p.position, r1, c1);
				return;
			}
		}
		//����������û���
		set_new_position(p.position, r1, c1);
		return;
	}
	
	////
	//if (OfferMoneyTimes == 2 && meetPrincess==0)
	//{
	//	//����������û��� //Ů������ʧ��
	//	set_new_position(p.position, r1, c1);
	//	return;
	//}
	//musicMeet();
	//int cost = 50* (OfferMoneyTimes + 1);
	//std::string message1 = "\n\nWould you like to offer \n" + std::to_string(cost) + " gold coins to the goddess?\n\nYes: 1  NO: 2";
	//std::string message2 = "\n\nWould you offer all your money\nto the goddess for a miracle?\n\nYes: 1  NO: 2";
	//char message3[] = "\n\n\nA new entrance is now opened";
	//if (OfferMoneyTimes < 2)
	//	PrintSpecialInfor(message1.c_str());
	////else if (OfferMoneyTimes == 2 && meetPrincess) //�Ѿ�����������,��������������֮��
	////	PrintSpecialInfor(message2.c_str());

	//if (OfferMoneyTimes == 2 && meetPrincess)//�����ι����������������֮��
	//{
	//	PrintSpecialInfor(message2.c_str());
	//	//
	//	if (YesOrNo())//ͬ��
	//	{
	//		OfferMoneyTimes += 1;
	//		map[r][c] = 7;   //Ů������ʧ
	//		//����������û��� 
	//		set_new_position(p.position, r1, c1);
	//		p.money = 0;
	//		musicLvUp();
	//		Map[2][8][11] = 11;//����¥����¥��,��Ҫ��ά���飡
	//		PrintSpecialInfor(message3);
	//		exit();
	//		return;
	//	}   //��Ϊ��ͬ��
	//	//����������û���
	//	set_new_position(p.position, r1, c1);
	//	return;
	//}

	////ǰ���ι���
	//if (YesOrNo())  //yes
	//{
	//	if (p.money >= cost)
	//	{
	//		p.money -= cost;
	//		OfferMoneyTimes += 1;
	//		if (OfferMoneyTimes == 1)
	//		{
	//			map[r][c] = 7;   //Ů������ʧ
	//			//����������û���
	//			set_new_position(p.position, r1, c1);
	//			PrintSpecialInfor("\n\n\nYou get nothing!");
	//			Sleep(600);
	//			return;
	//		}//ɶ��û�У�������
	//		else if (OfferMoneyTimes == 2)//��һ��������ʯ
	//		{
	//			musicLvUp();
	//			int defence = 2;
	//			p.def += defence;
	//			PrintLifeGem(defence);
	//			//Ů������ʧ��
	//			//����������û���
	//			set_new_position(p.position, r1, c1);
	//			return;
	//		}
	//		else
	//			return;
	//	}
	//	else //ûǮ
	//	{
	//		//����������û���
	//		set_new_position(p.position, r1, c1);
	//		PrintSpecialInfor("\n\n\nYour money is not enough!");
	//		Sleep(600);
	//		return;
	//	}
	//}
	////��ͬ��
	////����������û���
	//set_new_position(p.position, r1, c1);
	//return;
}

//�� kind 1 ���˶� ��2 ��ʦ֮��
void GetShield(Player& p, int kind)
{
	if (kind == 1)
	{
		p.def += 10;
		musicPickup();
		char name[] = "Boko Shield";
		PrintShield(name, 10);
	}
	if (kind == 2)
	{
		p.def += 15;
		musicPickup();
		char name[] = "Master Shield";
		PrintShield(name, 15);
	}
	if (kind == 3) //ľ��
	{
		p.def += 5;
		musicPickup();
		char name[] = "Wooden Shield";
		PrintShield(name, 5);
	}
}
//�� kind 1 ���˽� ��2 ��ʦ֮��
void GetSword(Player& p,int kind)
{
	if (1 == kind)
	{
		p.atk += 10;
		musicPickup();
		char name[] = "Boko Sword";
		PrintSword(name, 10);
	}
	if (2 == kind)
	{
		p.atk += 15;
		musicPickup();
		char name[] = "Master Sword";
		PrintSword(name, 15);
	}
	if (3 == kind) //����
	{
		p.atk += 5;
		musicPickup();
		char name[] = "Wooden Sword";
		PrintSword(name, 5);
	}
}
//������������
void RandomReward(Player& p)
{
	srand((unsigned int)time(NULL));
	int randomNum = rand() % 100;
	if (randomNum == 0)  //1% ľ�� ����+5
		GetShield(p,3);
	else if (randomNum == 1) //1% ľ֦ ����+5
		GetSword(p,3);
	else if (randomNum <= 10)  //8% 100���
	{
		p.money += 100;
		musicPickup();
		PrintSpecialInfor("\n\n\nYou find 100 gold coins!");
		exit();
	}
	else if (randomNum <= 20)    //10% moderate healing potion
	{
		musicPickup();
		p.backpack[1] += 1;
		char message[] = "\n\n\nYou get a moderate healing potion";
		PrintMessage(message);
	}
	else if (randomNum <= 40)    //20% minor...
	{
		musicPickup();
		p.backpack[0] += 1;
		char message[] = "\n\n\nYou get a minor healing potion";
		PrintMessage(message);
	}
	else if (randomNum <= 60)    //20% ������ʯ
		GetATKGem(p, 2);
	else if (randomNum <= 80)      //20% ������ʯ
		GetDEFGem(p, 2);
	else                         //20% nothing
	{
		PrintSpecialInfor("\n\n\nYou get nothing!");
		exit();
	}
}
// ҩˮ   2 - minor_healing_potion 20�ָ�  3 - moderate_healing_potion 50�ָ�
void DrinkPotion(Player& p, int healing,int kind)
{
	musicDrink();
	int hp = p.hp;
	if (p.hp + healing > p.hp_limit)
	{
		p.hp = p.hp_limit;
	}
	else
	{
		p.hp += healing;
	}

	char name1[] = "Minor Healing Potion";
	char name2[] = "Moderate Healing Potion";
	switch (kind)
	{
	case 1:
		p.backpack[0] -= 1;
		PrintInfor(name1, p.hp - hp);
		break;
	case 2:
		p.backpack[1] -= 1;
		PrintInfor(name2, p.hp - hp);
		break;
	}
}

int MeetPotion(int map[][COL], Player& p, int r, int c, int r1, int c1, \
	int direction_picture_number,int healing,int kind)//kind��ʾħҩ����
{
	musicPickup();
	map[r1][c1] = 7;
	map[r][c] = direction_picture_number;
	if (1 == kind)
		p.backpack[0] += 1;
	else if (2 == kind)
		p.backpack[1] += 1;
	return 0;
}

//�̵�
void FailToBuy(Player& p)
{
	char message[] = "\n\n\nYour money is not enough!";
	PrintMessage(message);
	PrintMap(Map[p.position[0]], p);
	PrintStore(p);
}
void meetMerchant(Player& p)
{
	musicMeet();
	PrintStore(p);//ͼ�λ�չʾ
	while (1) //��ͬѡ��
	{
		Sleep(70);
		//�������Ϊ1����Ʒ��minor potion
		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)   
		{
			while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE1)
			{
				p.money -= PRICE1;
				musicPickup();
				p.backpack[0] += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ2����Ʒ��moderate potion
		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)   
		{
			while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE2)
			{
				p.money -= PRICE2;
				musicPickup();
				p.backpack[1] += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ3����Ʒ��yellow key
		if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)   
		{
			while (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE3)
			{
				musicPickup();
				p.money -= PRICE3;
				p.yellow_key += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ4����Ʒ��blue key
		if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)   
		{
			while (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE4)
			{
				musicPickup();
				p.money -= PRICE4;
				p.blue_key += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ5����Ʒ��pickaxe
		if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE5)
			{
				musicPickup();
				p.money -= PRICE5;
				p.pickaxe += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ6����Ʒ������
		if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE6)
			{
				musicPickup();
				p.money -= PRICE6;
				RandomReward(p);
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ7����Ʒ��mysterious potion
		if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE7)
			{
				musicPickup();
				p.money -= PRICE7;
				p.backpack[5] += 1;
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ8����Ʒ��wisdom potion
		if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE8)
			{
				musicPickup();
				p.money -= PRICE8;
				musicDrink();
				LvUp(p);
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ9����Ʒ�����˽�
		if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE9)
			{
				musicPickup();
				p.money -= PRICE9;
				GetSword(p, 1);
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}

		//�������Ϊ0����Ʒ�����˶�
		if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
		{
			while (GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
			{
				Sleep(30);
			}
			if (p.money >= PRICE0)
			{
				musicPickup();
				p.money -= PRICE0;
				GetShield(p, 1);
				PrintMap(Map[p.position[0]], p);
				PrintStore(p);
			}
			else
				FailToBuy(p);
		}
		//�˳�
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)  
		{
			while (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				Sleep(30);
			}
			break;
		}
	}

}
//��ʯ
void GetDEFGem(Player& p, int defence)
{
	p.def += defence;
	musicPickup();
	PrintLifeGem(defence);
}
void GetATKGem(Player& p, int attack)
{
	p.atk += attack;
	musicPickup();
	PrintAttackGem(attack);
}

int ValidMove(int map[][COL], Player& p, int r, int c, int r1, int c1, \
	int direction_picture_number,int direction) //direction 4 5 6 7�ֱ��ʾ��������
{
	int hp = p.hp;

	//����
	if (map[r][c] == 39)  
	{
		meetPrincess += 1;
		set_new_position(p.position, r1, c1);//�������û���
		if (meetPrincess == 1)
		{
			musicMeet();
			PrintFalsePrincess();
			map[r][c] = 7;//�ٹ�����ʧ
			//�����µ�Ů����
			Map[1][6][9] = 50;
			return 0;
		}
		return 3;//ʤ��
	}

	//����
	if (map[r][c] == 55)      
	{
		set_new_position(p.position, r1, c1);//�������û���
		meetMerchant(p);
		return 0;
	}

	//apple
	if (map[r][c] == 57)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		musicPickup();
		p.backpack[2] += 1;
		PrintSpecialInfor("\nYou find an apple.\n\nIt is very precious in the tower\n\nand might be useful somewhere...");
		exit();
	}

	//grape
	if (map[r][c] == 58)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		musicPickup();
		p.backpack[3] += 1;
		PrintSpecialInfor("\nYou get a bunch of grapes.\n\nIt looks tasty\n\nand might be useful somewhere...");
		exit();
	}

	//fish
	if (map[r][c] == 59)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		musicPickup();
		p.backpack[4] += 1;
		PrintSpecialInfor("\nYou get a fish.\n\nAs we all know,\n\ncats are carzy about it...");
		exit();
	}

	//����
	if (map[r][c] == 74)
	{
		//����1
		if (ThreeD == p.position[0] && 1 == p.position[1] && 1 == p.position[2])
		{
			Map[ThreeD][1][2] = 52;
			Map[ThreeD][1][1] = 7;//����ʹ��һ�κ�ʧЧ
			PrintMessage("\n\n\nYou stepped into a trap!");
			//map[r1][c1] = 7;
		}
		//����2
		if (TwoB == p.position[0] && 3 == p.position[1] && 3 == p.position[2])
		{
			Map[TwoB][5][3] = 52;
			Map[TwoB][3][3] = 7;//����ʹ��һ�κ�ʧЧ
			PrintMessage("\n\n\nYou stepped into a trap!");
			map[r1][c1] = 7;
		}

		map[r][c] = direction_picture_number;
		return 0;
	}
	//�յ�
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//ӥ��  ���Ը��� 10 HPǿ����һ����r����
	if (map[r][c] == 63)
	{
		map[r1][c1] = 7;//ԭλ�ñ�Ϊ�յ�
		map[r][c] = direction_picture_number;
		musicLvUp();//�˴�ֻ��������ʾ�кö���
		p.backpack[EAGLEFLAG] = 1;
		PrintSpecialInfor("\nEagle Flag\n\nFrom now on,you can get roughly\n\n10% HP of each monster killed");
		exit();
		PrintSpecialInfor("\nYou can also activate it(Press 'r')\n\nat the cost of 10 HP\n\nto strenghen your next attack");
		exit();
	}
	
	//ʮ�ּ�  ��������atk��1.5��
	if (map[r][c] == 64)
	{
		map[r1][c1] = 7;//ԭλ�ñ�Ϊ�յ�
		map[r][c] = direction_picture_number;
		musicLvUp();//�˴�ֻ��������ʾ�кö���
		p.backpack[CROSS] = 1;
		PrintSpecialInfor("\n\nSliver Cross\n\nIt gives you purifying power");exit();
		PrintSpecialInfor("\n\nAnd damage will increase \n\nby 1.5 times to skeletons");exit();
		
	}

	//����
	if (map[r][c] == 51) 
	{
		meetSage += 1;
		set_new_position(p.position, r1, c1);//�������û���
		musicMeet();
		if(meetSage==1)
		{
			char message1[] = "\n\nLong time no see.\n\nYou have been asleep for a century.";
			char message2[] = "\n\nThe tower is extremely dangerous\n\nTake this Magic Book";
			//char message3[] = "\n\nIt can turn souls of the monsters \n\nkilled into Exp to strengthen you";
			char message4[] = "\n\nThe Monster Encyclopedia in it \n\ncontains the information I know\n(Press e to open or close)";
			char message5[] = "\n\nThere is also a backpack \n\n(Press b to open or close)";
			//char message5[] = "\n\nThere are some hidden rooms\n\nonly you can open";
			//char message6[] = "\n\nAnd treasure are inside.\n\nGo ahead and find them!";
			char message7[] = "\n\n\nGood luck to you!";
			PrintSpecialInfor(message1);exit();
			PrintSpecialInfor(message2);exit();
			//PrintSpecialInfor(message3);exit();
			PrintSpecialInfor(message4);exit();
			PrintSpecialInfor(message5);exit();
			//PrintSpecialInfor(message6);exit();
			PrintSpecialInfor(message7);exit();
		}
		else
		{
			//char message1[] = "\n\nGood job!\n\nYou've made it to the second floor";
			char message1[] = "\n\nThe Princess seems a bit strange,\n\nbut I'm not sure...";
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
			p.backpack[1] += 1;
		}
		map[r][c] = 7;//������ʧ
		return 0;
	}

	//��ʦ
	if (map[r][c] == 26)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//�������û���
		char m1[] = "\n\nStranger,listen!\n\nDarkness spreads in the tower";
		char m2[] = "\nEach monster killed brings\n\nmoments of light\n\nTime is limited,act quickly...";
		char m3[] = "\n\nTen monsters were killed.\n\nYou've done well.";
		char m4[] = "\n\nTake the Life Gem\n\nMay godness bless you!";
		char m5[] = "\n\nTwenty monsters were beaten.\n\nYou've done well.";
		char m6[] = "\n\nTake the Wooden Sword\n\nMay godness bless you!";
		char m7[] = "\n\nThirty monsters were killed.\n\nYou've done well.";
		char m8[] = "\n\nTake the Wooden Shield\n\nMay godness bless you!";
		char m9[] = "\n\nForty monsters were beaten.\n\nGood job!";
		char m10[] = "\n\nTake the Wisdom Potion\n\nMay godness bless you!";
		char m11[] = "\n\n50 monsters were beaten.\n\nGood job!";
		char m12[] = "\n\nTake the 100 gold coins\n\nMay godness bless you!";
		char m13[] = "\n\n60 monsters were beaten.\n\nGood job!";
		char m14[] = "\n\nTake the 100 gold coins\n\nMay godness bless you!";
		char m15[] = "\n\n70 monsters were beaten.\n\nGood job!";
		char m16[] = "\n\n80 monsters were beaten.\n\nGood job!";
		char m17[] = "\n\n90 monsters were beaten.\n\nGood job!";
		char m18[] = "\n\n100 monsters were beaten.\n\nGood job!";
		char m19[] = "\n\n110 monsters were beaten.\n\nGood job!";
		char m20[] = "\n\n120 monsters were beaten.\n\nGood job!";
		char m21[] = "\n\n130 monsters were beaten.\n\nGood job!";
		char m22[] = "\n\n140 monsters were beaten.\n\nGood job!";
		char m23[] = "\n\n150 monsters were beaten.\n\nGood job!";
		char M[]= "\n\nTake the 150 gold coins\n\nMay godness bless you!";
		if (p.killnumber >= 10 && wizardReward == 0)//Life Gem
		{
			wizardReward += 1;
			PrintSpecialInfor(m3);exit();
			PrintSpecialInfor(m4);exit();
			GetDEFGem(p, 2);
			return 0;
		}
		if (p.killnumber >= 20 && wizardReward == 1)//ľ��
		{
			wizardReward += 1;
			PrintSpecialInfor(m5);exit();
			PrintSpecialInfor(m6);exit();
			GetSword(p, 3);
			return 0;
		}
		if (p.killnumber >= 30 && wizardReward == 2)//ľ��
		{
			wizardReward += 1;
			PrintSpecialInfor(m7);exit();
			PrintSpecialInfor(m8);exit();
			GetShield(p, 3);
			return 0;
		}
		if (p.killnumber >= 40 && wizardReward == 3) //�ǻ�ҩ��
		{
			wizardReward += 1;
			PrintSpecialInfor(m9);exit();
			PrintSpecialInfor(m10);exit();
			musicDrink();
			LvUp(p);
			return 0;
		}
		if (p.killnumber >= 50 && wizardReward == 4) //100���
		{
			wizardReward += 1;
			PrintSpecialInfor(m11);exit();
			PrintSpecialInfor(m12);exit();
			p.money += 100;
			return 0;
		}
		if (p.killnumber >= 60 && wizardReward == 5) //100���
		{
			wizardReward += 1;
			PrintSpecialInfor(m13);exit();
			PrintSpecialInfor(m14);exit();
			p.money += 100;
			return 0;
		}
		if (p.killnumber >= 70 && wizardReward == 6) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m15);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 80 && wizardReward == 7) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m16);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 8) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m17);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 100 && wizardReward == 9) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m18);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 110 && wizardReward == 10) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m19);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 120 && wizardReward == 11) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m20);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 130 && wizardReward == 12) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m21);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 13) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m22);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 14) //150���
		{
			wizardReward += 1;
			PrintSpecialInfor(m23);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		PrintSpecialInfor(m1);exit();
		PrintSpecialInfor(m2);exit();
		return 0;
	}
	//����
	if (map[r][c] == 66)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//�������û���
		char m1[] = "\n\nAh,traveler! This tower only\n\nserves stable bread,moldy cheese...";
		char m2[] = "\nBring me an apple...or grapes!\n\nBring both,and...\n\nthat's undoubtedly better!";
		char m3[] = "\nGold? Magic Potion? Or...\n\na talking spoon?\n\nI'll give you whatever you like!";
		char m4[] = "\n\nI've been here 1000 years\n\n����I'm desperate!";
		char mA1[] = "\nOh,my godness!\n\nA fruit feast--APPLE and GRAPES!\n\nI must be dreaming!";
		char mA2[] = "\nGive me both\n\nand I'll give you Great Rewards!\n\n(yes 1,no 2)";
		char mA3[] = "\n\nA great hero's gift!\n\nYou save my life!";
		char mA4[] = "\n\nSweet,crispy,divine\n\n--it's the meal of king!";
		char mA5[] = "\n\nTake the blue key\n\nyellow key and 200 gold coins!";
		char mA6[] = "\n\nNo fruit at all?\n\nEven rats will pity me!";
		char mA7[] = "\nWell...if you change your mind\n\nI'll be here\n\n--forever ready to trade.";
		char mB1[] = "\nOh,beautiful red thing!\n\nAPPLE!\n\nCan you spare it for an old man?";
		char mB2[] = "\nI promise,my gratitude\n\nwill be as sweet as its juice\n\n(yes 1,no 2)";
		char mB3[] = "\nCrispy,delightful!\n\nYou saved my lifetime\n\nfrom bread and cheese!";
		char mB4[] = "\n\nTake the blue key\n\nNext time,maybe bring a pie?";
		char mB5[] = "\nAh...no apple?\n\nI have to survive on bread and\n\ncheese for the rest of my days!";
		char mB6[] = "\nBut if you change your mind\n\nI'll be here\n\n--always ready for a crispy bite!";
		char mC1[] = "\nPurple diamonds!\n\nGRAPES!\n\nCan you spare them for an old man?";
		char mC2[] = "\nI promise,my gratitude\n\nwill be more useful\n\n(yes 1,no 2)";
		char mC3[] = "\nSweet as a bird's melody!\n\nYou saved my lifetime\n\nfrom bread and cheese!";
		char mC4[] = "\n\nTake 150 gold coins\n\nNext time,maybe bring apples?";
		char mC5[] = "\nAh...no grapes?\n\nI am left with bread and cheese\n\n--a tragic fate!";
		char mC6[] = "\nBut if you change your mind\n\nI'll be here\n\n--always ready for a juicy bunch!";
		char mE1[] = "\nNow,listen well\n\nThere exists a dangerous potion\n\n��drink it,and your life will weaken";
		char mE2[] = "\nBut your strength will grow\n\nChoose wisely\n\nfor such choices shape your fate";
		char mE3[] = "\nBut there also exists a potion\n\nIt's green\n\nand can strengthen your life";
		char mE4[] = "\nNow,listen!\n\nThere exists a green potion\n\nIt can strengthen your life";
		char mE5[] = "\n\n\nGo ahead and find it!";

		//���ѡ�ƻ��ͬʱ����
		if (p.backpack[2] && p.backpack[3]) 
		{
			PrintSpecialInfor(mA1);exit();
			PrintSpecialInfor(mA2);
			if (YesOrNo())
			{
				p.backpack[2] -= 1;p.backpack[3] -= 1;
				PrintSpecialInfor(mA3);exit();
				PrintSpecialInfor(mA4);exit();
				PrintSpecialInfor(mA5);
				musicPickup();
				p.blue_key += 1;
				p.yellow_key += 1;
				p.money += 200;
				exit();
				PrintMap(Map[p.position[0]], p);
				PrintSpecialInfor(mE1);exit();
				PrintSpecialInfor(mE2);exit();
				PrintSpecialInfor(mE3);exit();
				return 0;
			}
			PrintSpecialInfor(mA6);exit();
			PrintSpecialInfor(mA7);exit();
			return 0;
		}
		//ƻ��
		if (p.backpack[2])
		{
			PrintSpecialInfor(mB1);exit();
			PrintSpecialInfor(mB2);
			if (YesOrNo())
			{
				p.backpack[2] -= 1;
				PrintSpecialInfor(mB3);exit();
				PrintSpecialInfor(mB4);
				musicPickup();
				p.blue_key += 1;
				exit();
				PrintMap(Map[p.position[0]], p);
				PrintSpecialInfor(mE1);exit();
				PrintSpecialInfor(mE2);exit();
				return 0;
			}
			PrintSpecialInfor(mB5);exit();
			PrintSpecialInfor(mB6);exit();
			return 0;
		}
		//����
		if (p.backpack[3])
		{
			PrintSpecialInfor(mC1);exit();
			PrintSpecialInfor(mC2);
			if (YesOrNo())
			{
				p.backpack[3] -= 1;
				PrintSpecialInfor(mC3);exit();
				PrintSpecialInfor(mC4);
				musicPickup();
				p.money += 150;
				exit();
				PrintMap(Map[p.position[0]], p);
				PrintSpecialInfor(mE4);exit();
				PrintSpecialInfor(mE5);exit();
				return 0;
			}
			PrintSpecialInfor(mC5);exit();
			PrintSpecialInfor(mC6);exit();
			return 0;
		}
		PrintSpecialInfor(m1);exit();
		PrintSpecialInfor(m2);exit();
		PrintSpecialInfor(m3);exit();
		PrintSpecialInfor(m4);exit();
		return 0;
	}

	//��è
	if (map[r][c] == 65)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//�������û���
		char mA1[] = "\n\nMeow!That smell...\n\nso charming,so familiar...";//message A 1
		char mA2[] = "\n\n\nFISH!!!";
		char mA3[] = "\n\nWould you be kind enough\n\nto share just one bite?(yes 1,no 2)";
		char mA4[] = "\n\nMeow! You're a true hero\n\nThank you!";
		char mA5[] = "\nThis fish...it's perfect!\n\n����so tender,so fresh!\n\nMeow!";
		char mA6[] = "\n\nTake my gifts\n\ntwo Moderate Healing Potion";
		char mA7[] = "\nMeow...really?\n\nNot even a bite?\n\nBut it smells so divine!";
		char mA8[] = "\nOh,if you change your mind\n\nI'll be here\n\n����always ready for fish!";
		char mB1[] = "\n\nHaving some fruit might\n\nbenefit to my health";
		char mC1[] = "\nYou've got an apple?\n\nThe round and red staff?\n\nGive me a bite!(yes 1,no 2)";
		char mC2[] = "\nMeow...Hmm...\n\nIt's interesting.Not fish,but...\n\nfine.";
		char mD1[] = "\nThose round and shiny things...\n\nGRAPES?!\n\nGive me a bunch!(yes 1,no 2)";
		char mD2[] = "\n\n\nMeow...Sour as dragon's tear!";
		char mB2[] = "\n\n\nAnyway,thank you,traveler";
		char mB3[] = "\n\nMeow...all right!\n\nNo fruit today? Fine.";
		char mB4[]= "\n\nBut if you can find fish...\n\nbring it here!";
		char mC3[] = "\n\n\nHere is a yellow key";
		char mD3[] = "\n\nHere are 70 gold coins\n\nNext time...bring some fish";
		char m1[] = "\n\nMeow...how I miss the\n\nwonderful taste of fish!";
		char m2[] = "\n\nThe tower only has boring mice\n\nI'm fed up with them!";
		char m3[] = "\nBring me a morsel of fish\n\n����just one bite����\n\nand I'll share secrets of the tower";
		char m4[] = "\n...or give you my magic bell\n\nIt rings for true heroes\n\n(Or cats.Mostly cats)";
		char m5[] = "\n\nFish is great,but...\n\nmaybe I should try some fruit?";
		char mE1[] = "\nNow,listen closely\n\nIt's a wise idea to use\n\nEagleFlag when meeting BloodWizard";
		                                               

		if (p.backpack[4])//fish
		{
			PrintSpecialInfor(mA1);exit();
			PrintSpecialInfor(mA2);exit();
			PrintSpecialInfor(mA3);
			if(YesOrNo())
			{//yes
				p.backpack[4] -= 1;
				PrintSpecialInfor(mA4);exit();
				PrintSpecialInfor(mA5);exit();
				PrintSpecialInfor(mA6);
				musicPickup();
				p.backpack[1] += 2;
				exit();
				PrintMap(Map[p.position[0]], p);
				PrintSpecialInfor(mE1);exit();
				return 0;
			}
			//no
			PrintSpecialInfor(mA7);exit();
			PrintSpecialInfor(mA8);exit();
			
			return 0;
		}
		if (p.backpack[2] || p.backpack[3]) //apple or grape
		{
			PrintSpecialInfor(mB1);exit();
			if(p.backpack[2]) //apple
			{
				PrintSpecialInfor(mC1);
				if (YesOrNo())
				{
					p.backpack[2] -= 1;
					PrintSpecialInfor(mC2);exit();
					PrintSpecialInfor(mB2);exit();
					PrintSpecialInfor(mC3);
					musicPickup();
					p.yellow_key += 1;
					exit();return 0;
				}
				//no
				PrintSpecialInfor(mB3);exit();
				PrintSpecialInfor(mB4);exit();
				return 0;
			}
			else     //grape
			{
				PrintSpecialInfor(mD1);
				if (YesOrNo())
				{
					p.backpack[3] -= 1;
					PrintSpecialInfor(mD2);exit();
					PrintSpecialInfor(mB2);exit();
					PrintSpecialInfor(mD3);
					musicPickup();
					p.money += 70;
					exit();return 0;
				}
				PrintSpecialInfor(mB3);exit();
				PrintSpecialInfor(mB4);exit();
				return 0;
			}
		}
		PrintSpecialInfor(m1);exit();
		PrintSpecialInfor(m2);exit();
		PrintSpecialInfor(m3);exit();
		PrintSpecialInfor(m4);exit();
		PrintSpecialInfor(m5);exit();
		return 0;
	}

	// ����
	if (map[r][c] == 56)  
	{
		set_new_position(p.position, r1, c1);//�������û���
		map[r][c] = 7;  //������ʧ
		RandomReward(p);
		return 0;
	}

	//�ǿմ�����
	if (map[r][c] == 73)
	{
		musicEnter();
		//���㣬�����̵�TwoA
		if (1 == p.position[0] && 7 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoA;
			p.position[1] = 6;
			p.position[2] = 1;
			Map[TwoA][6][1] = 8;
			PlaySound(TEXT("shop.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);//����������
			return 0;
		}
		//�̵꣬���͵�����
		if (TwoA == p.position[0] && 6 == r && 0 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 7;
			p.position[2] = 11;
			Map[1][7][11] = 8;
			PlaySound(TEXT("ZeldaBackground.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);//���²���
			return 0;
		}
		//���㵽 TwoB
		if (1 == p.position[0] && 0 == r && 5 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoB;
			p.position[1] = 11;
			p.position[2] = 11;
			Map[TwoB][11][11] = 8;
			return 0;
		}
		//TwoB������
		if (TwoB == p.position[0] && 11 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 1;
			p.position[2] = 5;
			Map[1][1][5] = 8;
			return 0;
		}
		//���㵽 TwoC
		if (1 == p.position[0] && 6 == r && 0 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoC;
			p.position[1] = 2;
			p.position[2] = 11;
			Map[TwoC][2][11] = 8;
			return 0;
		}
		//TwoC�� ���� 
		if (TwoC == p.position[0] && 2 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 6;
			p.position[2] = 1;
			Map[1][6][1] = 8;
			return 0;
		}
		//���㵽 TwoD
		if (1 == p.position[0] && 12 == r && 8 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoD;
			p.position[1] = 11;
			p.position[2] = 7;
			Map[TwoD][11][7] = 8;
			return 0;
		}
		//TwoD�� ���� 
		if (TwoD == p.position[0] && 12 == r && 7 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 11;
			p.position[2] = 8;
			Map[1][11][8] = 8;
			return 0;
		}
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

	//��ɫԿ��
	if (map[r][c] == 17)  
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

	//��ɫ��
	if (map[r][c] == 18)   
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
	//а����ʦ  33  
	if (map[r][c] == 33)
	{
		musicBattle();
		char name[] = "Evil Wizard";//��������
		return Battle(map, p, EvilWizard, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BloodBat 68
	if (map[r][c] == 68)
	{
		musicBattle();
		char name[] = "Blood Bat";//��������
		return Battle(map, p, BloodBat, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BoneWarrior 69
	if (map[r][c] == 69)
	{
		musicBattle();
		char name[] = "Bone Warrior";//��������
		return Battle(map, p, BoneWarrior, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BloodWizard 70
	if (map[r][c] == 70)
	{
		musicBattle();
		char name[] = "Blood Wizard";//��������
		return Battle(map, p, BloodWizard, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//Orc 71
	if (map[r][c] == 71)
	{
		musicBattle();
		char name[] = "Orc";//��������
		return Battle(map, p, Orc, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//SkeletonGeneral 72
	if (map[r][c] == 72)
	{
		musicBattle();
		char name[] = "Skeleton General";//��������
		return Battle(map, p, SkeletonGeneral, name, r1, c1, r, c, hp, direction_picture_number);
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

	// ҩˮ   2 - minor_healing_potion�� 3 - moderate_healing_potion 
		//minor
	if (map[r][c] == 2)
	{
		return MeetPotion(map,p, r,c, r1,c1, \
			direction_picture_number, 20,1); //����������ֱַ��ʾ �ظ�20����������minor potion
	}
	//moderate
	if (map[r][c] == 3)
	{
		return MeetPotion(map, p, r, c, r1, c1, \
			direction_picture_number, 50,2); //����������ֱַ��ʾ �ظ�50�������� ��moderate potion
	}
	//wisdom potion,��1������ֱ��ʹ��
	if (map[r][c] == 61)
	{
		musicPickup();
		PrintSpecialInfor("\nWisdom Potion\n\nIt has a tempeting smell and\n\na charming gold color");exit();
		PrintSpecialInfor("\n\nIt seems that it can strenghen\n\nyou in an unusual way.");exit();
		musicDrink();
		LvUp(p);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
	}
	//life potion,��50�������ޣ���ֱ��ʹ��
	if (map[r][c] == 62)
	{
		musicPickup();
		PrintSpecialInfor("\nLife Potion\n\nIts green glows\n\nlike forests after rain");exit();
		PrintSpecialInfor("\nIt heals...\n\nbut also reminds you\n\nhow fragile life is");exit();
		PrintMap(Map[p.position[0]], p);
		musicDrink();
		PrintMessage("\n\n\nMax HP limit increased by 50");
		p.hp_limit += 50;
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
	}
	//����ҩ�� increase atk at the cost of life-limit
	if (map[r][c] == 60)
	{
		musicPickup();
		PrintSpecialInfor("\nMysterious Potion\n\nIt shines,dark and bright.\n\nSmell changes����sweet and sharp.");exit();
		PrintSpecialInfor("\nMight make you strong....\n\n or break you.\n\nNo one knows...\n(Press 'm' to drink)");exit();
		p.backpack[5] += 1;
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		//PrintMap(Map[p.position[0]], p);
	}
	//��
	//���˶�
	if (map[r][c] == 22)
	{
		GetShield(p,1);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//��ʦ֮��
	if (map[r][c] == 34)
	{
		GetShield(p, 2);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//��
	//���˲���֮��
	if (map[r][c] == 21)
	{
		GetSword(p,1);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//��ʦ֮��
	if (map[r][c] == 29)
	{
		GetSword(p,2);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}
	//����
	if (map[r][c] == 24)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.pickaxe += 1;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		PrintSpecialInfor("\nPickaxe\n\nIt can break an ordinary wall\n\nbut only once");exit();
		PrintSpecialInfor("\nPress 'p'\n\nthen use arrow keys to choose\n\na wall to destroy.");exit();
		return 0;
	}

	//������ʯ
	if (map[r][c] == 20)
	{
		GetDEFGem(p, 2);//���һ������def��ֵ
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//������ʯ
	if (map[r][c] == 19)
	{
		GetATKGem(p, 2);//���һ������atk��ֵ
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//Ů����
	if (map[r][c] == 50) 
	{
		//�������û���
		set_new_position(p.position, r1, c1);
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

int play(int map[][COL],Player &p)    //��Ҳ���
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
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||(GetAsyncKeyState('A') & 0x8000))
		{ // ��������a���ִ�Сд��������ʵ�֡�ע��(GetAsyncKeyState('a')�����⣬�������ã�
			while ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			{
				Sleep(30);
			}//ʵ��һ��һ�����ɿ�ʱ���ƶ�
			ret=afterPress(map, p, r, c - 1, r1, c1,35,left);//35��������زĵı��
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // ����Ҽ�
			while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r, c + 1, r1, c1,36,right);//����
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // ����ϼ�
			while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r-1, c , r1, c1,37,up);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // ����¼�
			while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r + 1, c, r1, c1,8,down);
			if (ret != 19)
				return ret;
		}

		//���� p
		else if (GetAsyncKeyState('P') & 0x8000)
		{ // ���p��
			while (GetAsyncKeyState('P') & 0x8000)
			{
				Sleep(30);
			}
			if (p.pickaxe <= 0)
				continue;
			char message[] = "\n\n\nYou have destroyed a wall!";
			PrintUsePickaxe();exit();
			PrintMap(Map[p.position[0]], p);
			while (true)
			{
				if (GetAsyncKeyState('P') & 0x8000)
				{//�ٴΰ� p ȡ��
					while (GetAsyncKeyState('P') & 0x8000)
					{
						Sleep(30);
					}
					return 0;
				}
				else if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
				{ // ���� ���
					while ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r][c - 1] == 1)
					{
						PrintMessage(message);
						map[r][c - 1] = 7;
						p.pickaxe -= 1;
					}
					else
						PrintMessage("\n\n\nUnbreakable Item!");
					return 0;
				}

				else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) ||(GetAsyncKeyState('D') & 0x8000))
				{ // ���� �Ҽ�
					while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r][c + 1] == 1)
					{
						PrintMessage(message);
						map[r][c + 1] = 7;
						p.pickaxe -= 1;
					}
					else
						PrintMessage("\n\n\nUnbreakable Item!");
					return 0;
				}

				else if ((GetAsyncKeyState(VK_UP) & 0x8000)|| (GetAsyncKeyState('W') & 0x8000))
				{ // ���� �ϼ�
					while ((GetAsyncKeyState(VK_UP) & 0x8000)|| (GetAsyncKeyState('W') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r - 1][c] == 1)
					{
						PrintMessage(message);
						map[r - 1][c] = 7;
						p.pickaxe -= 1;
					}
					else
						PrintMessage("\n\n\nUnbreakable Item!");
					return 0;
				}

				else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
				{ // ���� �¼�
					while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
					{
						Sleep(30);
					}
					if (map[r + 1][c] == 1)
					{
						PrintMessage(message);
						map[r + 1][c] = 7;
						p.pickaxe -= 1;
					}
					else
						PrintMessage("\n\n\nUnbreakable Item!");
					return 0;
				}
			}
		}

		//ͼ�� e
		else if (GetAsyncKeyState('E') & 0x8000)
		{ // ���e��
			while (GetAsyncKeyState('E') & 0x8000)
			{
				Sleep(30);
			}
			musicEncyclopedia();
			MonsterEncyclopedia(p);
			return 0;
		}
		//���� b
		else if (GetAsyncKeyState('B') & 0x8000)
		{ // ���e��
			while (GetAsyncKeyState('B') & 0x8000)
			{
				Sleep(30);
			}
			musicOpenBackpack();
			ShowBackpack(p);
			
			return 0;
		}
		// ʹ��С�ָ�ҩˮ i
		else if (GetAsyncKeyState('I') & 0x8000)
		{ 
			while (GetAsyncKeyState('I') & 0x8000)
			{
				Sleep(30);
			}
			if (p.backpack[0]>0) //�У����ܺ�
				DrinkPotion(p, 20, 1);
			break;
		}
		// ʹ���лָ�ҩˮ o
		else if (GetAsyncKeyState('O') & 0x8000)
		{
			while (GetAsyncKeyState('O') & 0x8000)
			{
				Sleep(30);
			}
			if (p.backpack[1]>0)
				DrinkPotion(p, 50, 2);
			break;
		}

		//����ҩ�� m
		else if ((GetAsyncKeyState('M') & 0x8000) && p.backpack[5])
		{
			while (GetAsyncKeyState('M') & 0x8000)
			{
				Sleep(30);
			}
			p.backpack[5] = 0;
			musicDrink();
			PrintSpecialInfor("\n\nYou lost 100 Max HP limit\n\nand gained 10 ATK");exit();
			p.hp_limit -= 100;
			if (p.hp > p.hp_limit)
				p.hp = p.hp_limit;
			p.atk += 10;
			break;
		}

		//r ʹ��ӥ��. ǰ����Ҫ�У�
		else if ((GetAsyncKeyState('R') & 0x8000) && p.backpack[EAGLEFLAG] && p.enhancedAtk == 0)
		{                                                                       //ֻ��ǿ��һ��
			while (GetAsyncKeyState('R') & 0x8000)
			{
				Sleep(30);
			}
			p.hp -= 10;
			p.enhancedAtk += 1;
			std::string message = "\nYou lost 10 HP\n\nATK is strenghened by " + \
				std::to_string((5 + p.Lv*3) * p.enhancedAtk) + "\n\nfor the next strike!";
			PrintMessageYellow(message.c_str());
			break;
		}

		//�˳���
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			PrintSpecialInfor("\n\nQuit\n\n(Yes 1, No 2)");
			if (YesOrNo())
			{
				return -12;
			}
			return 0;
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
