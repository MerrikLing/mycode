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

//升级
//经验要求暂定为，50*Lv;   注意连续升级的情况！
//提升：血量加 100， 攻击 加5，防御加 5
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



int ValidMove(int map[][COL], Player& p, int r, int c, int r1, int c1, int direction_picture_number)
{
	int hp = p.hp;
	//空地
	if (map[r][c] == 7)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		return 0;
	}
	//钥匙
		//黄色
	if (map[r][c] == 4)
	{
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key += 1;
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
		map[r1][c1] = 7;
		map[r][c] = direction_picture_number;
		p.yellow_key -= 1;
		return 0;
	}

	//怪物：死亡或击败，击败会获得经验与金币   判断血量
		//史莱姆酱 6
	if (map[r][c] == 6)
	{
		char gs[] = "Green Slime";//传入名字
		return Battle(map, p, GreenSlime, gs, r1, c1, r, c, hp, direction_picture_number);
	}
	//蝙蝠   30 bat B   
	if (map[r][c] == 30)
	{
		char bt[] = "Bat";//传入名字
		return Battle(map, p, Bat, bt, r1, c1, r, c, hp, direction_picture_number);
	}
	//骷髅  31 骷髅 S 
	if (map[r][c] == 31)
	{
		char sk[] = "Skeleton";//传入名字
		return Battle(map, p, Skeleton, sk, r1, c1, r, c, hp, direction_picture_number);
	}


	// 药水   2 - minor_healing_potion h  3 - moderate_healing_potion H
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

int afterPress(int map[][COL], Player& p,int r,int c,int r1,int c1,int direction_picture_number)
{
	if (judge_hit(map[r][c]))//没撞墙则执行
	{
		set_new_position(p.position, r, c);
		return ValidMove(map, p, r, c, r1, c1, direction_picture_number);
	}
	//重置
	r = r1;c = c1;
	return 19;//表示无效输入
}

int move(int map[][COL],Player &p)    //玩家移动
{
	int r = p.position[1];
	int c = p.position[2];
	//备份
	int r1 = r; 
	int c1 = c;
	int hp = p.hp;
	int ret;   //接收afterPress的值，并判断

	//用另一种方式，问题，按一个键走好几步——通过sleep解决
	while (true)
	{
		Sleep(80);
		if ((GetAsyncKeyState(VK_LEFT) & 0x8000)|| (GetAsyncKeyState('a') & 0x8000)|| (GetAsyncKeyState('A') & 0x8000))
		{ // 检测左键
			ret=afterPress(map, p, r, c - 1, r1, c1,35);//35是向左的素材的编号
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState('d') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
		{ // 检测右键
			ret = afterPress(map, p, r, c + 1, r1, c1,36);//向右
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_UP) & 0x8000) || (GetAsyncKeyState('w') & 0x8000) || (GetAsyncKeyState('W') & 0x8000))
		{ // 检测上键
			ret = afterPress(map, p, r-1, c , r1, c1,37);
			if (ret != 19)
				return ret;
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState('s') & 0x8000) || (GetAsyncKeyState('S') & 0x8000))
		{ // 检测下键
			ret = afterPress(map, p, r + 1, c, r1, c1,8);
			if (ret != 19)
				return ret;
		}
	}
}

//上述代码的控制台版本的核心实现部分

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
