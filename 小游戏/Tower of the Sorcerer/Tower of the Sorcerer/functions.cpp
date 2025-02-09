#include"head.hpp"
//int OfferMoneyTimes = 0;//供奉给女神像的次数
int meetSage = 0;
int meetPrincess = 0;
int wizardReward = 0;

//撞墙与否
int judge_hit(int value)
{
	if (value == 0 || value == 1 || value == 52 || value == 53)
	{
		return 0;
	}
	return 1;
}

//没撞墙时
// 设置新坐标
void set_new_position(int position[], int r, int c)
{
	position[1] = r;
	position[2] = c;
}

//对战
void PK(Player& p, const Monster& m)
{
	p.hp -= Damage(p, m);
}

//计算怪物对玩家伤害
int Damage(Player& p, const Monster& m)
{
	int hp = p.hp;
	int l = m.hp;

	int atk = p.atk + (5 + p.Lv*3) * p.enhancedAtk;
	p.enhancedAtk = 0;//重置
	if (p.backpack[CROSS])//十字架可以使骷髅类防御减半
	{
		if (m.isSkeleton)
			atk *= 1.5;
	}
	if (atk - m.def >= l)  //一击毙命则所受伤害减半
	{
		if (m.atk > p.def)
		{
			hp -= (m.atk - p.def) / 2;
			return p.hp - hp;
		}
		else
			return 0;
	}
	//第一轮攻击要考虑鹰旗
	if (p.def < m.atk)
		hp -= m.atk - p.def;
	if (m.def < atk)
		l -= atk - m.def;
	
	atk = p.atk;    //先重置攻击
	if (p.backpack[CROSS])//十字架可以使骷髅类防御减半
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
		return p.hp; //死亡
	else
		return p.hp - hp;
}

//升级
//经验要求暂定为，50*Lv;   注意连续升级的情况！
//提升：血量上限加 50， 攻击 加2，防御加 2
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


//战斗
int Battle(int map[][COL], Player& p, Monster& m, char* name, \
	int r1, int c1, int r, int c, int hp,int direction_picture_number)//传入名字
{
	PK(p, m);
	if (p.hp)//还有血量则继续执行
	{
		//改地图
		p.killnumber += 1;
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]],p);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //图形化展示信息
		p.money += m.money;
		p.Exp += m.exp;
		if (p.backpack[EAGLEFLAG])//鹰旗可以吸血 10%
		{
			int recovery = p.hp_limit - p.hp > m.hp / 10 ? m.hp / 10 : p.hp_limit - p.hp;
			PrintBattleRecovery(recovery);
			p.hp += recovery;
		}
		Judge_and_LvUp(p);

		//1%概率掉落食物
		srand((unsigned int)time(NULL));
		int randomNum = rand() % 300;
		if (randomNum == 100)   //苹果
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get an apple!");exit();
			p.backpack[2] += 1;
			return 0;
		}
		if (randomNum == 200)   //葡萄
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get grapes!");exit();
			p.backpack[3] += 1;
			return 0;
		}
		if (randomNum == 0)   //鱼
		{
			musicWin();
			PrintSpecialInfor("\n\n\nYou are so lucky to get fish!");exit();
			p.backpack[4] += 1;
			return 0;
		}
		return 0;
	}
	//失败，坐标重置回来
	set_new_position(p.position, r1, c1);
	return 2; //死亡

}

int YesOrNo()//输入1，yes，返回1；输入2，no，返回0
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
void MeetGodness(Player& p, int map[][COL], int r1,int c1,int r,int c)   //遇见后要消失！
{
	musicMeet();
	//打开第四层通道
	if (meetPrincess)
	{
		std::string message1 = "\nWould you offer all your money\n\nto the goddess for a miracle?\n\nYes: 1  NO: 2";
		char message2[] = "\n\n\nA new entrance is opened";
		PrintSpecialInfor(message1.c_str());
		if (YesOrNo())//同意
		{
			map[r][c] = 7;   //女神像消失
			//玩家坐标重置回来 
			set_new_position(p.position, r1, c1);
			p.money = 0;
			musicLvUp();
			Map[2][8][1] = 11;//第三楼出现楼梯,需要三维数组！
			PrintSpecialInfor(message2);
			exit();
			return;
		}   //下为不同意
		//玩家坐标重置回来
		set_new_position(p.position, r1, c1);
		return;
	}
	
	//打开通往商店的传送门
	if (1 == p.position[0] && 6 == r && 8 == c)
	{
		std::string message1 = "\nWould you like to offer \n\n" + std::to_string(p.money) + " gold coins to the goddess?\n\n(Yes: 1  NO: 2)";
		char message2[] = "\n\n\nA new entrance is opened";
		PrintSpecialInfor(message1.c_str());
		if (YesOrNo())  //yes
		{   
			musicLvUp();
			PrintSpecialInfor(message2);exit();
			map[r][c] = 7;   //女神像消失
			//玩家坐标重置回来
			set_new_position(p.position, r1, c1);
			p.money = 0;
			Map[1][7][12] = 73;
			return;
		}
		//玩家坐标重置回来
		set_new_position(p.position, r1, c1);
		return;
	}
	//打开通往ThreeD的楼梯
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
				Map[TwoD][2][5] = 11;   //女神像消失
				//玩家坐标重置回来
				set_new_position(p.position, r1, c1);
				return;
			}
			else
			{
				PrintSpecialInfor("\n\n\nYour money is not enough!");
				Sleep(600);
				//玩家坐标重置回来
				set_new_position(p.position, r1, c1);
				return;
			}
		}
		//玩家坐标重置回来
		set_new_position(p.position, r1, c1);
		return;
	}
	
	////
	//if (OfferMoneyTimes == 2 && meetPrincess==0)
	//{
	//	//玩家坐标重置回来 //女神像不消失！
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
	////else if (OfferMoneyTimes == 2 && meetPrincess) //已经供奉了两次,必须在遇到公主之后
	////	PrintSpecialInfor(message2.c_str());

	//if (OfferMoneyTimes == 2 && meetPrincess)//第三次供奉，必须在遇到公主之后
	//{
	//	PrintSpecialInfor(message2.c_str());
	//	//
	//	if (YesOrNo())//同意
	//	{
	//		OfferMoneyTimes += 1;
	//		map[r][c] = 7;   //女神像消失
	//		//玩家坐标重置回来 
	//		set_new_position(p.position, r1, c1);
	//		p.money = 0;
	//		musicLvUp();
	//		Map[2][8][11] = 11;//第三楼出现楼梯,需要三维数组！
	//		PrintSpecialInfor(message3);
	//		exit();
	//		return;
	//	}   //下为不同意
	//	//玩家坐标重置回来
	//	set_new_position(p.position, r1, c1);
	//	return;
	//}

	////前两次供奉
	//if (YesOrNo())  //yes
	//{
	//	if (p.money >= cost)
	//	{
	//		p.money -= cost;
	//		OfferMoneyTimes += 1;
	//		if (OfferMoneyTimes == 1)
	//		{
	//			map[r][c] = 7;   //女神像消失
	//			//玩家坐标重置回来
	//			set_new_position(p.position, r1, c1);
	//			PrintSpecialInfor("\n\n\nYou get nothing!");
	//			Sleep(600);
	//			return;
	//		}//啥都没有，哈哈哈
	//		else if (OfferMoneyTimes == 2)//得一个生命宝石
	//		{
	//			musicLvUp();
	//			int defence = 2;
	//			p.def += defence;
	//			PrintLifeGem(defence);
	//			//女神像不消失！
	//			//玩家坐标重置回来
	//			set_new_position(p.position, r1, c1);
	//			return;
	//		}
	//		else
	//			return;
	//	}
	//	else //没钱
	//	{
	//		//玩家坐标重置回来
	//		set_new_position(p.position, r1, c1);
	//		PrintSpecialInfor("\n\n\nYour money is not enough!");
	//		Sleep(600);
	//		return;
	//	}
	//}
	////不同意
	////玩家坐标重置回来
	//set_new_position(p.position, r1, c1);
	//return;
}

//盾 kind 1 波克盾 ，2 大师之盾
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
	if (kind == 3) //木盾
	{
		p.def += 5;
		musicPickup();
		char name[] = "Wooden Shield";
		PrintShield(name, 5);
	}
}
//剑 kind 1 波克剑 ，2 大师之剑
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
	if (3 == kind) //宝箱
	{
		p.atk += 5;
		musicPickup();
		char name[] = "Wooden Sword";
		PrintSword(name, 5);
	}
}
//宝箱的随机奖励
void RandomReward(Player& p)
{
	srand((unsigned int)time(NULL));
	int randomNum = rand() % 100;
	if (randomNum == 0)  //1% 木盾 防御+5
		GetShield(p,3);
	else if (randomNum == 1) //1% 木枝 攻击+5
		GetSword(p,3);
	else if (randomNum <= 10)  //8% 100金币
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
	else if (randomNum <= 60)    //20% 攻击宝石
		GetATKGem(p, 2);
	else if (randomNum <= 80)      //20% 防御宝石
		GetDEFGem(p, 2);
	else                         //20% nothing
	{
		PrintSpecialInfor("\n\n\nYou get nothing!");
		exit();
	}
}
// 药水   2 - minor_healing_potion 20恢复  3 - moderate_healing_potion 50恢复
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
	int direction_picture_number,int healing,int kind)//kind表示魔药种类
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

//商店
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
	PrintStore(p);//图形化展示
	while (1) //不同选项
	{
		Sleep(70);
		//购买序号为1的商品，minor potion
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

		//购买序号为2的商品，moderate potion
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

		//购买序号为3的商品，yellow key
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

		//购买序号为4的商品，blue key
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

		//购买序号为5的商品，pickaxe
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

		//购买序号为6的商品，宝箱
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

		//购买序号为7的商品，mysterious potion
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

		//购买序号为8的商品，wisdom potion
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

		//购买序号为9的商品，波克剑
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

		//购买序号为0的商品，波克盾
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
		//退出
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
//宝石
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
	int direction_picture_number,int direction) //direction 4 5 6 7分别表示上下左右
{
	int hp = p.hp;

	//公主
	if (map[r][c] == 39)  
	{
		meetPrincess += 1;
		set_new_position(p.position, r1, c1);//坐标重置回来
		if (meetPrincess == 1)
		{
			musicMeet();
			PrintFalsePrincess();
			map[r][c] = 7;//假公主消失
			//出现新的女神像
			Map[1][6][9] = 50;
			return 0;
		}
		return 3;//胜利
	}

	//商人
	if (map[r][c] == 55)      
	{
		set_new_position(p.position, r1, c1);//坐标重置回来
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

	//陷阱
	if (map[r][c] == 74)
	{
		//陷阱1
		if (ThreeD == p.position[0] && 1 == p.position[1] && 1 == p.position[2])
		{
			Map[ThreeD][1][2] = 52;
			Map[ThreeD][1][1] = 7;//陷阱使用一次后失效
			PrintMessage("\n\n\nYou stepped into a trap!");
			//map[r1][c1] = 7;
		}
		//陷阱2
		if (TwoB == p.position[0] && 3 == p.position[1] && 3 == p.position[2])
		{
			Map[TwoB][5][3] = 52;
			Map[TwoB][3][3] = 7;//陷阱使用一次后失效
			PrintMessage("\n\n\nYou stepped into a trap!");
			map[r1][c1] = 7;
		}

		map[r][c] = direction_picture_number;
		return 0;
	}
	//空地
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//鹰旗  可以付出 10 HP强化下一击（r键）
	if (map[r][c] == 63)
	{
		map[r1][c1] = 7;//原位置变为空地
		map[r][c] = direction_picture_number;
		musicLvUp();//此处只是用来表示有好东西
		p.backpack[EAGLEFLAG] = 1;
		PrintSpecialInfor("\nEagle Flag\n\nFrom now on,you can get roughly\n\n10% HP of each monster killed");
		exit();
		PrintSpecialInfor("\nYou can also activate it(Press 'r')\n\nat the cost of 10 HP\n\nto strenghen your next attack");
		exit();
	}
	
	//十字架  对骷髅类atk翻1.5倍
	if (map[r][c] == 64)
	{
		map[r1][c1] = 7;//原位置变为空地
		map[r][c] = direction_picture_number;
		musicLvUp();//此处只是用来表示有好东西
		p.backpack[CROSS] = 1;
		PrintSpecialInfor("\n\nSliver Cross\n\nIt gives you purifying power");exit();
		PrintSpecialInfor("\n\nAnd damage will increase \n\nby 1.5 times to skeletons");exit();
		
	}

	//贤者
	if (map[r][c] == 51) 
	{
		meetSage += 1;
		set_new_position(p.position, r1, c1);//坐标重置回来
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
			//获得中等恢复药水
			musicPickup();
			p.backpack[1] += 1;
		}
		map[r][c] = 7;//贤者消失
		return 0;
	}

	//巫师
	if (map[r][c] == 26)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//坐标重置回来
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
		if (p.killnumber >= 20 && wizardReward == 1)//木剑
		{
			wizardReward += 1;
			PrintSpecialInfor(m5);exit();
			PrintSpecialInfor(m6);exit();
			GetSword(p, 3);
			return 0;
		}
		if (p.killnumber >= 30 && wizardReward == 2)//木盾
		{
			wizardReward += 1;
			PrintSpecialInfor(m7);exit();
			PrintSpecialInfor(m8);exit();
			GetShield(p, 3);
			return 0;
		}
		if (p.killnumber >= 40 && wizardReward == 3) //智慧药剂
		{
			wizardReward += 1;
			PrintSpecialInfor(m9);exit();
			PrintSpecialInfor(m10);exit();
			musicDrink();
			LvUp(p);
			return 0;
		}
		if (p.killnumber >= 50 && wizardReward == 4) //100金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m11);exit();
			PrintSpecialInfor(m12);exit();
			p.money += 100;
			return 0;
		}
		if (p.killnumber >= 60 && wizardReward == 5) //100金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m13);exit();
			PrintSpecialInfor(m14);exit();
			p.money += 100;
			return 0;
		}
		if (p.killnumber >= 70 && wizardReward == 6) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m15);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 80 && wizardReward == 7) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m16);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 8) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m17);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 100 && wizardReward == 9) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m18);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 110 && wizardReward == 10) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m19);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 120 && wizardReward == 11) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m20);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 130 && wizardReward == 12) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m21);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 13) //150金币
		{
			wizardReward += 1;
			PrintSpecialInfor(m22);exit();
			PrintSpecialInfor(M);exit();
			p.money += 150;
			return 0;
		}
		if (p.killnumber >= 90 && wizardReward == 14) //150金币
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
	//老者
	if (map[r][c] == 66)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//坐标重置回来
		char m1[] = "\n\nAh,traveler! This tower only\n\nserves stable bread,moldy cheese...";
		char m2[] = "\nBring me an apple...or grapes!\n\nBring both,and...\n\nthat's undoubtedly better!";
		char m3[] = "\nGold? Magic Potion? Or...\n\na talking spoon?\n\nI'll give you whatever you like!";
		char m4[] = "\n\nI've been here 1000 years\n\n——I'm desperate!";
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
		char mE1[] = "\nNow,listen well\n\nThere exists a dangerous potion\n\n—drink it,and your life will weaken";
		char mE2[] = "\nBut your strength will grow\n\nChoose wisely\n\nfor such choices shape your fate";
		char mE3[] = "\nBut there also exists a potion\n\nIt's green\n\nand can strengthen your life";
		char mE4[] = "\nNow,listen!\n\nThere exists a green potion\n\nIt can strengthen your life";
		char mE5[] = "\n\n\nGo ahead and find it!";

		//葡萄、苹果同时带来
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
		//苹果
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
		//葡萄
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

	//大猫
	if (map[r][c] == 65)
	{
		musicMeet();
		set_new_position(p.position, r1, c1);//坐标重置回来
		char mA1[] = "\n\nMeow!That smell...\n\nso charming,so familiar...";//message A 1
		char mA2[] = "\n\n\nFISH!!!";
		char mA3[] = "\n\nWould you be kind enough\n\nto share just one bite?(yes 1,no 2)";
		char mA4[] = "\n\nMeow! You're a true hero\n\nThank you!";
		char mA5[] = "\nThis fish...it's perfect!\n\n——so tender,so fresh!\n\nMeow!";
		char mA6[] = "\n\nTake my gifts\n\ntwo Moderate Healing Potion";
		char mA7[] = "\nMeow...really?\n\nNot even a bite?\n\nBut it smells so divine!";
		char mA8[] = "\nOh,if you change your mind\n\nI'll be here\n\n——always ready for fish!";
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
		char m3[] = "\nBring me a morsel of fish\n\n——just one bite——\n\nand I'll share secrets of the tower";
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

	// 宝箱
	if (map[r][c] == 56)  
	{
		set_new_position(p.position, r1, c1);//坐标重置回来
		map[r][c] = 7;  //宝箱消失
		RandomReward(p);
		return 0;
	}

	//星空传送门
	if (map[r][c] == 73)
	{
		musicEnter();
		//二层，传送商店TwoA
		if (1 == p.position[0] && 7 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoA;
			p.position[1] = 6;
			p.position[2] = 1;
			Map[TwoA][6][1] = 8;
			PlaySound(TEXT("shop.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);//播放新音乐
			return 0;
		}
		//商店，传送到二层
		if (TwoA == p.position[0] && 6 == r && 0 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 7;
			p.position[2] = 11;
			Map[1][7][11] = 8;
			PlaySound(TEXT("ZeldaBackground.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);//重新播放
			return 0;
		}
		//二层到 TwoB
		if (1 == p.position[0] && 0 == r && 5 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoB;
			p.position[1] = 11;
			p.position[2] = 11;
			Map[TwoB][11][11] = 8;
			return 0;
		}
		//TwoB到二层
		if (TwoB == p.position[0] && 11 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 1;
			p.position[2] = 5;
			Map[1][1][5] = 8;
			return 0;
		}
		//二层到 TwoC
		if (1 == p.position[0] && 6 == r && 0 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoC;
			p.position[1] = 2;
			p.position[2] = 11;
			Map[TwoC][2][11] = 8;
			return 0;
		}
		//TwoC到 二层 
		if (TwoC == p.position[0] && 2 == r && 12 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = 1;
			p.position[1] = 6;
			p.position[2] = 1;
			Map[1][6][1] = 8;
			return 0;
		}
		//二层到 TwoD
		if (1 == p.position[0] && 12 == r && 8 == c)
		{
			map[r1][c1] = 7;
			p.position[0] = TwoD;
			p.position[1] = 11;
			p.position[2] = 7;
			Map[TwoD][11][7] = 8;
			return 0;
		}
		//TwoD到 二层 
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
	//钥匙
		//黄色
	if (map[r][c] == 4)
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key += 1;
		return 0;
	}

	//蓝色钥匙
	if (map[r][c] == 17)  
	{
		musicPickup();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.blue_key += 1;
		return 0;
	}

	//门：有没有钥匙  
		// 5——黄色门
	if (map[r][c] == 5)
	{
		if (p.yellow_key < 1)
		{
			//坐标重置回来
			set_new_position(p.position, r1, c1);
			PrintNoKey();
			return 0;
		}
		//有钥匙
		musicEnter();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key -= 1;
		return 0;
	}

	//蓝色门
	if (map[r][c] == 18)   
	{
		if (p.blue_key < 1)
		{
			//坐标重置回来
			set_new_position(p.position, r1, c1);
			PrintNoKey();
			return 0;
		}
		//有钥匙
		musicEnter();
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.blue_key -= 1;
		return 0;
	}

	//怪物：死亡或击败，击败会获得经验与金币   判断血量
		//绿色史莱姆酱 6
	if (map[r][c] == 6)
	{
		musicBattle();
		char name[] = "Green Slime";//传入名字
		return Battle(map, p, GreenSlime, name, r1, c1, r, c, hp, direction_picture_number);
	}

	//红色史莱姆酱 9
	if (map[r][c] == 9)
	{
		musicBattle();
		char name[] = "Red Slime";//传入名字
		return Battle(map, p, RedSlime, name, r1, c1, r, c, hp, direction_picture_number);
	}

	//蝙蝠   30 bat B   
	if (map[r][c] == 30)
	{
		musicBattle();
		char bt[] = "Bat";//传入名字
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp, direction_picture_number);
	}
	//骷髅  31 骷髅 S 
	if (map[r][c] == 31)
	{
		musicBattle();
		char name[] = "Skeleton";//传入名字
		return Battle(map, p, Skeleton, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//骷髅士兵  32  
	if (map[r][c] == 32)
	{
		musicBattle();
		char name[] = "Skeleton Soldier";//传入名字
		return Battle(map, p, SkeletonSoldier, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//邪恶巫师  33  
	if (map[r][c] == 33)
	{
		musicBattle();
		char name[] = "Evil Wizard";//传入名字
		return Battle(map, p, EvilWizard, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BloodBat 68
	if (map[r][c] == 68)
	{
		musicBattle();
		char name[] = "Blood Bat";//传入名字
		return Battle(map, p, BloodBat, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BoneWarrior 69
	if (map[r][c] == 69)
	{
		musicBattle();
		char name[] = "Bone Warrior";//传入名字
		return Battle(map, p, BoneWarrior, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//BloodWizard 70
	if (map[r][c] == 70)
	{
		musicBattle();
		char name[] = "Blood Wizard";//传入名字
		return Battle(map, p, BloodWizard, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//Orc 71
	if (map[r][c] == 71)
	{
		musicBattle();
		char name[] = "Orc";//传入名字
		return Battle(map, p, Orc, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//SkeletonGeneral 72
	if (map[r][c] == 72)
	{
		musicBattle();
		char name[] = "Skeleton General";//传入名字
		return Battle(map, p, SkeletonGeneral, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//魔王  38  
	if (map[r][c] == 38)
	{
		musicBattle();
		char name[] = "Demon King";//传入名字
		return Battle(map, p, DemonKing, name, r1, c1, r, c, hp, direction_picture_number);
	}
	//不可战胜的魔王 54
	if (map[r][c] == 54)
	{
		musicBattle();
		char name[] = "Demon Emperor";//传入名字
		return Battle(map, p, DemonEmperor, name, r1, c1, r, c, hp, direction_picture_number);
	}

	// 药水   2 - minor_healing_potion， 3 - moderate_healing_potion 
		//minor
	if (map[r][c] == 2)
	{
		return MeetPotion(map,p, r,c, r1,c1, \
			direction_picture_number, 20,1); //最后两个数字分别表示 回复20的生命、是minor potion
	}
	//moderate
	if (map[r][c] == 3)
	{
		return MeetPotion(map, p, r, c, r1, c1, \
			direction_picture_number, 50,2); //最后两个数字分别表示 回复50的生命、 是moderate potion
	}
	//wisdom potion,加1级，捡到直接使用
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
	//life potion,加50生命上限，捡到直接使用
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
	//神秘药剂 increase atk at the cost of life-limit
	if (map[r][c] == 60)
	{
		musicPickup();
		PrintSpecialInfor("\nMysterious Potion\n\nIt shines,dark and bright.\n\nSmell changes——sweet and sharp.");exit();
		PrintSpecialInfor("\nMight make you strong....\n\n or break you.\n\nNo one knows...\n(Press 'm' to drink)");exit();
		p.backpack[5] += 1;
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		//PrintMap(Map[p.position[0]], p);
	}
	//盾
	//波克盾
	if (map[r][c] == 22)
	{
		GetShield(p,1);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//大师之盾
	if (map[r][c] == 34)
	{
		GetShield(p, 2);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//剑
	//波克布林之剑
	if (map[r][c] == 21)
	{
		GetSword(p,1);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}

	//大师之剑
	if (map[r][c] == 29)
	{
		GetSword(p,2);
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]], p);
		return 0;
	}
	//镐子
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

	//防御宝石
	if (map[r][c] == 20)
	{
		GetDEFGem(p, 2);//最后一个增加def的值
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//攻击宝石
	if (map[r][c] == 19)
	{
		GetATKGem(p, 2);//最后一个增加atk的值
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	//女神像
	if (map[r][c] == 50) 
	{
		//坐标重置回来
		set_new_position(p.position, r1, c1);
		MeetGodness(p,map,r1,c1,r,c);
		return 0;
	}

	//上楼或下楼  11 upstairs +   12 downstairs -
	  //上
	if (map[r][c] == 11)
	{
		map[r1][c1] = 7;
		p.position[0] += 1; //加一层
		return direction;
	}
	//下
	if (map[r][c] == 12)
	{
		map[r1][c1] = 7;
		p.position[0] -= 1; //加一层
		return direction;
	}
	
	return 0;
}

int afterPress(int map[][COL], Player& p,int r,int c,int r1,int c1,\
	int direction_picture_number,int direction)//4 5 6 7分别表示上下左右
{
	if (judge_hit(map[r][c]))//没撞墙则执行
	{
		set_new_position(p.position, r, c);
		return ValidMove(map, p, r, c, r1, c1, direction_picture_number,direction);
	}
	//重置
	r = r1;c = c1;
	return 19;//表示无效输入
}

int play(int map[][COL],Player &p)    //玩家操作
{
	int r = p.position[1];
	int c = p.position[2];
	//direction 
	int up = 4;int down = 5;int left = 6;int right = 7;
	//备份
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	int ret;   //接收afterPress的值，并判断

	//按一个键走好几步——通过sleep解决
	while (true)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000) ||(GetAsyncKeyState('A') & 0x8000))
		{ // 检测左键，a不分大小写，都可以实现。注意(GetAsyncKeyState('a')有问题，不起作用！
			while ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			{
				Sleep(30);
			}//实现一键一动，松开时才移动
			ret=afterPress(map, p, r, c - 1, r1, c1,35,left);//35是向左的素材的编号
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // 检测右键
			while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r, c + 1, r1, c1,36,right);//向右
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // 检测上键
			while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r-1, c , r1, c1,37,up);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // 检测下键
			while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r + 1, c, r1, c1,8,down);
			if (ret != 19)
				return ret;
		}

		//镐子 p
		else if (GetAsyncKeyState('P') & 0x8000)
		{ // 检测p键
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
				{//再次按 p 取消
					while (GetAsyncKeyState('P') & 0x8000)
					{
						Sleep(30);
					}
					return 0;
				}
				else if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
				{ // 镐子 左键
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
				{ // 镐子 右键
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
				{ // 镐子 上键
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
				{ // 镐子 下键
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

		//图鉴 e
		else if (GetAsyncKeyState('E') & 0x8000)
		{ // 检测e键
			while (GetAsyncKeyState('E') & 0x8000)
			{
				Sleep(30);
			}
			musicEncyclopedia();
			MonsterEncyclopedia(p);
			return 0;
		}
		//背包 b
		else if (GetAsyncKeyState('B') & 0x8000)
		{ // 检测e键
			while (GetAsyncKeyState('B') & 0x8000)
			{
				Sleep(30);
			}
			musicOpenBackpack();
			ShowBackpack(p);
			
			return 0;
		}
		// 使用小恢复药水 i
		else if (GetAsyncKeyState('I') & 0x8000)
		{ 
			while (GetAsyncKeyState('I') & 0x8000)
			{
				Sleep(30);
			}
			if (p.backpack[0]>0) //有，才能喝
				DrinkPotion(p, 20, 1);
			break;
		}
		// 使用中恢复药水 o
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

		//神秘药剂 m
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

		//r 使用鹰旗. 前提是要有！
		else if ((GetAsyncKeyState('R') & 0x8000) && p.backpack[EAGLEFLAG] && p.enhancedAtk == 0)
		{                                                                       //只能强化一次
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

		//退出！
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

 //此处传进来的map是所有楼层的！
void ChangeFloor(int Map[FLOOR][ROW][COL],Player& P,int ret)
{
	musicEnter();

	if (ret == 4 && Map[P.position[0]][P.position[1] - 1][P.position[2]] == 7)//向上并且楼梯上一格是空
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

	//默认位置:门上一格是空，门上，否则去其他的空地
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

//下面代码的控制台版本的核心实现部分

		// 控制台版本——要把下面这段放到循环里面！
		////bug 可以走到墙里面！原因，没有重置r、c
		//switch (_getch()) {
		//case 'W':
		//case 72:
		//case 'w': // 上
		//	r -= 1;
		//	if(judge_hit(map[r][c]))//没撞墙则执行
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//重置
		//	r = r1;c = c1;
		//	break;
		//case 'S':
		//case 80:
		//case 's': // 下
		//	r += 1;
		//	if (judge_hit(map[r][c]))//没撞墙则执行
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//重置
		//	r = r1;c = c1;
		//	break;
		//case 'A':
		//case 75:
		//case 'a': // 左
		//	c -= 1;
		//	if (judge_hit(map[r][c]))//没撞墙则执行
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//重置
		//	r = r1;c = c1;
		//	break;
		//case 'D':
		//case 77:
		//case 'd': // 右
		//	c += 1;
		//	if (judge_hit(map[r][c]))//没撞墙则执行
		//	{
		//		set_new_position(p.position, r, c);
		//		goto next;
		//	}
		//	//重置
		//	r = r1;c = c1;
		//	break;
		//default:
		//	//printf("输入错误，请重新输入\n");
		//	break;
		//}

	//}


//控制台版本的图形化
//void display_map(int map[][COL])
//{
//	system("cls");
//	for (int i = 0;i < ROW;i++)
//	{
//		for (int j = 0;j < COL;j++)
//		{
//			switch (map[i][j]) //打印每行地图
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
//				printf("地图设置有误");
//			}
//		}
//		printf("\n");
//	}
//}

//另一种尝试用键盘控制的失败方法，不知错在哪里
	//MSG msg;
	//while(1)               //读取输入,并确保正确输入，且没撞墙
	//{    
		////运行不了！！
		//// 使用GetMessage从消息队列中获取消息
		//GetMessage(&msg,NULL, 0, 0);

		//// 检查消息类型是否为键盘按下事件
		//if (msg.message == WM_KEYDOWN)
		//{
		//	switch (msg.wParam)
		//	{
		//	case 'A':
		//	case 'a':
		//	case VK_LEFT: // 左键
		//		c -= 1;
		//		if (judge_hit(map[r][c]))//没撞墙则执行
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//重置
		//		r = r1;c = c1;
		//		break;

		//	case 'D':// 右键
		//	case 'd':
		//	case VK_RIGHT:
		//		c += 1;
		//		if (judge_hit(map[r][c]))//没撞墙则执行
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//重置
		//		r = r1;c = c1;
		//		break;

		//	case 'W':
		//	case 'w':
		//	case VK_UP: // 上键
		//		r -= 1;
		//		if (judge_hit(map[r][c]))//没撞墙则执行
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//重置
		//		r = r1;c = c1;
		//		break;

		//	case 'S':
		//	case 's':
		//	case VK_DOWN: // 下键
		//		r += 1;
		//		if (judge_hit(map[r][c]))//没撞墙则执行
		//		{
		//			set_new_position(p.position, r, c);
		//			goto next;
		//		}
		//		//重置
		//		r = r1;c = c1;
		//		break;

		//	default:
		//		break;
		//	}
		//}
