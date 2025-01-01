#include"head.hpp"
int OfferMoneyTimes = 0;//供奉给女神像的次数
int meetSage = 0;
int meetPrincess = 0;

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
	if (p.atk - m.def >= l)  //一击毙命
		return 0;
	while (hp > 0 && l > 0)
	{
		if (p.def < m.atk)
			hp -= m.atk - p.def;
		if (m.def < p.atk)
			l -= p.atk - m.def;
	}
	if (hp <= 0)
		return p.hp; //死亡
	else
		return p.hp - hp;
}

//升级
//经验要求暂定为，50*Lv;   注意连续升级的情况！
//提升：血量加 100， 攻击 加5，防御加 5
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
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		PrintMap(Map[p.position[0]],p);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //图形化展示信息
		p.money += m.money;
		p.Exp += m.exp;
		Judge_and_LvUp(p);
		return 0;
	}
	//坐标重置回来
	set_new_position(p.position, r1, c1);
	return 2; //死亡

}

void MeetGodness(Player& p, int map[][COL], int r1,int c1,int r,int c)   //遇见后要消失！
{
	if (OfferMoneyTimes == 2 && meetPrincess==0)
	{
		//玩家坐标重置回来 //女神像不消失！
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
	//else if (OfferMoneyTimes == 2 && meetPrincess) //已经供奉了两次,必须在遇到公主之后
	//	PrintSpecialInfor(message2.c_str());

	if (OfferMoneyTimes == 2 && meetPrincess)//第三次供奉，必须在遇到公主之后
	{
		PrintSpecialInfor(message2.c_str());
		while (1)
		{
			Sleep(70);
			if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) //同意
			{
				while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
					Sleep(30);
				OfferMoneyTimes += 1;
				map[r][c] = 7;   //女神像消失
				//玩家坐标重置回来 
				set_new_position(p.position, r1, c1);
				p.money = 0;
				musicLvUp();
				Map[2][8][11] = 11;//第三楼出现楼梯,需要三维数组！
				PrintSpecialInfor(message3);
				exit();
				return;
			}

			if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) //不同意
			{
				while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
					Sleep(30);
				//玩家坐标重置回来
				set_new_position(p.position, r1, c1);
				return;
			}
		}
	}

	while (1)  //前两次供奉
	{
		Sleep(70);
		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) //同意
		{
			while (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
				Sleep(30);
			if (p.money >=  cost)
			{
				p.money -=  cost;
				OfferMoneyTimes += 1;
				if (OfferMoneyTimes == 1)
				{
					map[r][c] = 7;   //女神像消失
					//玩家坐标重置回来
					set_new_position(p.position, r1, c1);
					PrintSpecialInfor("\n\n\nYou get nothing!");
					Sleep(600);
					return;
				}//啥都没有，哈哈哈
				else if (OfferMoneyTimes == 2)//得一个生命宝石
				{
					musicLvUp();
					int defence = 2;
					p.def += defence;
					PrintLifeGem(defence);
					//女神像不消失！
					//玩家坐标重置回来
					set_new_position(p.position, r1, c1);
					return;
				}
				else
					return;
			}
			else
			{
				//玩家坐标重置回来
				set_new_position(p.position, r1, c1);
				PrintSpecialInfor("\n\n\nYour money is not enough!");
				Sleep(600);
				return;
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) //不同意
		{
			while (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
				Sleep(30);
			//玩家坐标重置回来
			set_new_position(p.position, r1, c1);
			return;
		}
	}
}

int ValidMove(int map[][COL], Player& p, int r, int c, int r1, int c1, \
	int direction_picture_number,int direction) //direction 4 5 6 7分别表示上下左右
{
	int hp = p.hp;

	if (map[r][c] == 39)  //找到公主——胜利
	{
		meetPrincess += 1;
		set_new_position(p.position, r1, c1);//坐标重置回来
		if (meetPrincess == 1)
		{
			musicMeet();
			PrintFalsePrincess();
			map[r][c] = 7;//假公主消失
			return 0;
		}
		return 3;//胜利
	}

	//空地
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}

	if (map[r][c] == 51) //贤者
	{
		meetSage += 1;
		set_new_position(p.position, r1, c1);//坐标重置回来
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
			//获得中等恢复药水
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
		map[r][c] = 7;//贤者消失
		return 0;
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

	if (map[r][c] == 17)  //蓝色钥匙
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

	if (map[r][c] == 18)   //蓝色门
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
	//巫师  33  
	if (map[r][c] == 33)
	{
		musicBattle();
		char name[] = "Wizard";//传入名字
		return Battle(map, p, Wizard, name, r1, c1, r, c, hp, direction_picture_number);
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
	// 药水   2 - minor_healing_potion h  3 - moderate_healing_potion H
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

	if (map[r][c] == 22)//盾
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.def += 10;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		char name[] = "Boko Shield";
		PrintShield(name,10); //防御加10
		return 0;
	}

	if (map[r][c] == 21)//剑
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.atk += 10;
		musicPickup();
		PrintMap(Map[p.position[0]], p);
		char name[] = "Boko Sword";
		PrintSword(name, 10); //攻击加10
		return 0;
	}

	if (map[r][c] == 24)//镐子
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

	if (map[r][c] == 20)//防御宝石
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

	if (map[r][c] == 19)//攻击宝石
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
	
	if (map[r][c] == 50) //女神像
	{
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

int play(int map[][COL],Player &p)    //玩家移动
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
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('a') & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
		{ // 检测左键
			while ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
			{
				Sleep(30);
			}//实现一键一动，松开时才移动
			ret=afterPress(map, p, r, c - 1, r1, c1,35,left);//35是向左的素材的编号
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // 检测右键
			while ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r, c + 1, r1, c1,36,right);//向右
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // 检测上键
			while ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r-1, c , r1, c1,37,up);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // 检测下键
			while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
			{
				Sleep(30);
			}
			ret = afterPress(map, p, r + 1, c, r1, c1,8,down);
			if (ret != 19)
				return ret;
		}

		//镐子 p
		else if ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
		{ // 检测p键
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
				{//再次按 p 取消
					while ((GetAsyncKeyState('p') & 0x8000) || (GetAsyncKeyState('P') & 0x8000))
					{
						Sleep(30);
					}
					return 0;
				}
				else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState('a') & 0x8000) || (GetAsyncKeyState('A') & 0x8000))
				{ // 镐子 左键
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
				{ // 镐子 右键
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
				{ // 镐子 上键
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
				{ // 镐子 下键
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

		//图鉴 e
		else if ((GetAsyncKeyState('e') & 0x8000) || (GetAsyncKeyState('E') & 0x8000) && meetSage)
		{ // 检测e键
			while ((GetAsyncKeyState('e') & 0x8000) || (GetAsyncKeyState('E') & 0x8000))
			{
				Sleep(30);
			}
			musicEncyclopedia();
			MonsterEncyclopedia(p);
			return 0;
		}
		//退出！
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			return -12;
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
