#include"head.hpp"

//撞墙与否
int judge_hit(int value)
{
	if (value == 0 || value == 1)
	{
		//printf("撞墙了\n");
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
	int l = m.hp;
	if (p.atk - m.def >= l)  //一击毙命
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

//战斗
int Battle(int map[][COL], Player& p, Monster& m, char* name, \
	int r1, int c1, int r, int c, int hp)//传入名字
{
	PK(p, m);
	if (p.hp)//还有血量则继续执行
	{
		//改地图
		map[r1][c1] = 7;
		map[r][c] = 8;
		//display_map(Map[p.position[0]]);
		PrintMap(Map[p.position[0]],p);
		//printf("You've beaten the %s!\nYou lost %d HP in the battle\nYou get %d gold coin and get %d Exp\n", \
		//	name, hp - p.hp, m.money, m.exp);
		PrintInfor(name, hp - p.hp, m.money, m.exp); //图形化展示信息
		p.money += m.money;
		p.Exp += m.exp;

		_kbhit();
		return 0;
	}
	//坐标重置回来
	set_new_position(p.position, r1, c1);
	return 2; //死亡

}

//玩家移动
// 需要当前地图，玩家位置，提供返回值（上楼 1，不上 0，下楼 -1）
// 传入玩家这一对象 (生命，攻击，防御，金币，经验)

int move(int map[][COL],Player &p)
{
	int r = p.position[1];
	int c = p.position[2];
	//备份
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	while(1)               //读取输入,并确保正确输入，且没撞墙
	{    //bug 可以走到墙里面！原因，没有重置r、c
		switch (_getch()) {
		case 'w': // 上
			r -= 1;
			if(judge_hit(map[r][c]))//没撞墙则执行
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//重置
			r = r1;c = c1;
			break;
		case 's': // 下
			r += 1;
			if (judge_hit(map[r][c]))//没撞墙则执行
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//重置
			r = r1;c = c1;
			break;
		case 'a': // 左
			c -= 1;
			if (judge_hit(map[r][c]))//没撞墙则执行
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//重置
			r = r1;c = c1;
			break;
		case 'd': // 右
			c += 1;
			if (judge_hit(map[r][c]))//没撞墙则执行
			{
				set_new_position(p.position, r, c);
				goto next;
			}
			//重置
			r = r1;c = c1;
			break;
		default:
			//printf("输入错误，请重新输入\n");
			break;
		}
	}
next:  
	//修改地图！最初的重置为 area 7，现在的坐标重置为 player 8
	//空地
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		return 0;
	}
	//钥匙
		//黄色
	if (map[r][c] == 4)
	{
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.yellow_key += 1;
		return 0;
	}
	//门：有没有钥匙  
		// 5——黄色门
	if (map[r][c] == 5)
	{
		if (p.yellow_key < 1)
		{
			//printf("Your yellows keys is not enough! \nGo around and find one!\n");
			//坐标重置回来
			set_new_position(p.position, r1, c1);
			_kbhit();
			return 0;
		}
		//有钥匙
		map[r1][c1] = 7;
		map[r][c] = 8;
		p.yellow_key -= 1;
		return 0;
	}

	//怪物：死亡或击败，击败会获得经验与金币   判断血量
		//史莱姆酱 6
	if (map[r][c] == 6)
	{   
		char gs[]= "Green Slime";//传入名字
		return Battle(map, p, GreenSlime, gs, r1, c1, r, c, hp);
	}
		//蝙蝠   30 bat B   
	if (map[r][c] == 30)
	{
		char bt[] = "Bat";//传入名字
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp);
	}
		//骷髅  31 骷髅 S 
	if (map[r][c] == 31)
	{
		char sk[] = "Skeleton";//传入名字
		return Battle(map, p, Skeleton, sk, r1, c1, r, c, hp);
	}


	// 药水   2 - minor_healing_potion h  3 - moderate_healing_potion H
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

	//上楼或下楼  11 upstairs +   12 downstairs -
	  //上
	if (map[r][c] == 11)
	{
		map[r1][c1] = 7;
		p.position[0] += 1; //加一层
		return 1;
	}
		//下
	if (map[r][c] == 12)
	{
		map[r1][c1] = 7;
		p.position[0] -= 1; //加一层
		return -1;
	}
	// 水晶
	// 特殊物品？
	return 0;
}


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
