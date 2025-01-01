#include"head.hpp"
IMAGE images[60];

void LoadImagesHelper(int n,int Width,int Height)
{
	//std::string location = "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\" + std::to_string(n) + ".png";
	std::string location = std::to_string(n) + ".png";

	loadimage(&images[n], location.c_str(), Width, Height);  //最后两个数字表示缩放后的大小
}

void LoadImages()       // 加载图片素材
{
	for (int i = 0;i <= 40;i++)
		LoadImagesHelper(i,50,50);
	//大图标，用于显示
	//loadimage(&images[49],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\8.png", 100, 100);
	for (int i = 41;i <= 48;i++)
		LoadImagesHelper(i, 100, 100);

	for (int i = 50;i <= 54;i++)
		LoadImagesHelper(i, 50, 50);
	//开始界面
	loadimage(&images[49], "49.jpg", 850, 650);
}

RECT R = { 0, 00, 850, 650 };//矩形指针，用于打印游戏开始画面
void StartImage()
{
	BeginBatchDraw();
	//setbkcolor(BLACK);
	setfillcolor(BLACK);
	setbkmode(TRANSPARENT);
	//solidrectangle(0, 00, 850, 650); // 填充矩形

	putimage(0, 0, &images[49]);//

	settextstyle(70, 0, "Consolas");
	drawtext("\nTower of Sorcerer", &R, DT_CENTER);

	EndBatchDraw();
	BeginBatchDraw();
	while (1)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))
			break;
	}

	settextstyle(30, 0, "Consolas");
	drawtext(\
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\nThe princess has been captured and imprisoned by the Demon.\nBut nobody knows where she is.\nYou've found clues leading to this tower\n so you come here ..."\
		, &R, DT_CENTER);       //The princess has been captured by the devil You found clues about her that led to this tower ,       Please use your wisdom and courage                                //删除了\n\n(Press space key to continue)                                         
	EndBatchDraw();
	Sleep(500);
	while (1)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))
			break;
	}
}

void InventInfor()   //打印制作信息
{
	BeginBatchDraw();
	cleardevice();
	settextstyle(70, 0, "Consolas");
	drawtext("\n\n Designed by Merrik.", &R, DT_CENTER);
	settextstyle(40, 0, "Consolas");
	drawtext("\n\n\n\n\n\n\n\n\n\nThis game would not have been possible\n without the support of my dear roomates\nor the advice of Leanne", &R, DT_CENTER);//
	EndBatchDraw();
	//musicGameLoading();
	Sleep(5000);
	//mciSendString("close GameLoading ", NULL, 0, NULL);
}

void InitImage()
{
	BeginBatchDraw();
	cleardevice();
	//边框上的图片
	for (int i = 0; i < ROW + 4; ++i)  //上边框
		putimage(i * 50, 0, &images[0]);
	for (int i = 0; i < ROW + 4; ++i)  //下边框
		putimage(i * 50, 600, &images[0]);
	for (int i = 1; i <= COL -1; ++i)  //左边框
		putimage(0, i * 50, &images[0]);
	for (int i = 1; i <= COL - 1; ++i)  //右边框
		putimage(800, i * 50, &images[0]);
	//for (int i = 1; i <= COL - 1; ++i)  //地图左框
	//	putimage(200, i * 50, &images[0]);
	putimage(50, 50, &images[48]); //人
	putimage(50, 150, &images[14]); //hp
	putimage(50, 200, &images[40]); //hp_limit
	putimage(50, 250, &images[13]); //atk
	putimage(50, 300, &images[15]); //def
	putimage(50, 350, &images[16]); //money
	putimage(50, 400, &images[4]); // yellow key
	putimage(50, 450, &images[17]);//blue key
	putimage(50, 500, &images[25]);// red key
	putimage(50, 550, &images[24]); //镐子
	EndBatchDraw();
}
//辅助函数，用于右对齐
int countDigits(int number) {
	if (number == 0) return 1; // 0是一个特殊情况，它有1位

	int count = 0;
	while (number > 0) {
		number /= 10;
		++count;
	}
	return count;
}

void PrintMap(int map[][COL], Player& p)
{
	BeginBatchDraw();
	for (int i = 1; i < ROW-1; ++i) {  //边框都是固定的，不用重复打印
		for (int j = 1; j < COL-1; ++j)
		{
			putimage(200+j * 50, i * 50, &images[map[i][j]]); // 显示图像
		}
	}
	for (int i = 1; i <= COL - 1; ++i)  //地图左框
		putimage(200, i * 50, &images[0]);

	settextcolor(WHITE);
	settextstyle(40, 0,  "Consolas");
	outtextxy(155, 50,  "Lv");
	settextstyle(30, 0,  "Consolas");
	setfillcolor(getbkcolor());
	solidrectangle(150, 100, 200, 150);
	solidrectangle(100, 150, 165, 600); //先清空之前打印的数据
	outtextxy(190 - 15 * countDigits(p.Lv), 100, std::to_string(p.Lv).c_str());	//把数字转化成字符串
	outtextxy(165 - 15 * countDigits(p.hp), 160, std::to_string(p.hp).c_str());

	outtextxy(165 - 15 * countDigits(p.hp_limit), 210, std::to_string(p.hp_limit).c_str());
	outtextxy(165 - 15 * countDigits(p.atk), 260, std::to_string(p.atk).c_str());
	outtextxy(165 - 15 * countDigits(p.def), 310, std::to_string(p.def).c_str());
	outtextxy(165 - 15 * countDigits(p.money), 360, std::to_string(p.money).c_str());
	outtextxy(165 - 15 * countDigits(p.yellow_key), 410, std::to_string(p.yellow_key).c_str());
	outtextxy(165 - 15 * countDigits(p.blue_key), 460, std::to_string(p.blue_key).c_str());
	outtextxy(165 - 15 * countDigits(p.red_key), 510, std::to_string(p.red_key).c_str());
	outtextxy(165 - 15 * countDigits(p.pickaxe), 560, std::to_string(p.pickaxe).c_str());
	EndBatchDraw();
}

RECT R1 = { 220,230,720, 450 };//矩形指针R1，用于打印游戏进程中信息
void PrintMessage(const char* message)
{
	setbkmode(TRANSPARENT);				//设置字体为透明
	settextcolor(BLACK);
	for (int i = 256;i > 64;i -= 5)
	{                                   //双缓冲技术来避免绘制时图像闪烁，效果显著
		BeginBatchDraw();               //与下面的EndBatchDraw();必须成对出现
		settextstyle(30, 0, "Consolas");
		setfillcolor(RGB(i, 0, 0));//第一个数字表示红色
		solidrectangle(220, 230, 720, 450); // 填充矩形
		drawtext(message, &R1, DT_CENTER);
		//在矩形区域R1内输入文字，水平居中，垂直居中
		Sleep(30);
		EndBatchDraw();
	}
}

void PrintInfor(char*name,int d_hp,int money,int exp) //Battle
{
	
	std::string n = name; // 将字符指针转换为std::string
	std::string message = "\n\nYou've beaten the " + n + "\nYou lost " + std::to_string(d_hp) + \
		" HP in the battle\nYou get " + std::to_string(money) + " gold coins\n";
	PrintMessage(message.c_str());
}

void PrintInfor(char* name, int addHP) //potion
{
	//"You find a minor healing potion and get 20 hp"
	std::string n = name; // 将字符指针转换为std::string
	std::string message = "\n\nYou find a\n" + n + "\nand get " + std::to_string(addHP) + " HP";
	PrintMessage(message.c_str());
}

void PrintNoKey()//no enough key
{
	std::string message = "\n\nYou don't have enough keys! \nGo around and find one!";
	PrintMessage(message.c_str());
}

void PrintLvUp()
{
	setbkmode(TRANSPARENT);				//设置字体为透明
	settextcolor(RED);
	for (int i = 256;i > 64;i -= 5)
	{                                   //双缓冲技术来避免绘制时图像闪烁，效果显著
		BeginBatchDraw();               //与下面的EndBatchDraw();必须成对出现
		setfillcolor(RGB(i, i, 0));
		solidrectangle(220, 230, 720, 450); // 填充矩形
		settextstyle(50, 0, "Consolas");
		drawtext("\nLv up!", &R1, DT_CENTER);

		settextstyle(30, 0, "Consolas");
		drawtext("\n\n\n\nYou get 2 Atk  2 Def!\nMax HP limit increased by 100", &R1, DT_CENTER);
		Sleep(30);
		EndBatchDraw();
	}
}

void PrintLifeGem(int defence)
{
	std::string message = "\n\nYou get a Life Gem \n\nand get " + std::to_string(defence)+" Def";
	PrintMessage(message.c_str());
}

void PrintAttackGem(int attack)
{
	std::string message = "\n\nYou get an Attack Gem \n\nand get "+ std::to_string(attack) + " Atk";
	PrintMessage(message.c_str());
}

void  PrintSpecialInfor(const char* name)
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	setfillcolor(RGB(255, 255, 0));
	solidrectangle(220, 230, 720, 450); // 填充矩形
	settextstyle(30, 0, "Consolas");
	drawtext(name, &R1, DT_CENTER);
	EndBatchDraw();
}
void exit()
{
	Sleep(500);
	while (1)
	{
		Sleep(70);
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			break;
	}
}

void PrintFalsePrincess()
{
	char message[] = "\n\n You reached here in a good mood\n\nthinking you've made it...";
	char message2[] = "\n\n\nbut...";
	char message3[] = "\n\nThe princess is fake.\n\n The true one is hided elsewhere!";
	char message4[] = "\n\nYou have to utilize your wisdom\n\nto find the true one";

	PrintSpecialInfor(message);
	exit();
	PrintSpecialInfor(message2);
	exit();
	PrintSpecialInfor(message3);
	exit();
	PrintSpecialInfor(message4);
	exit();
}

void PrintLose()
{
	char message[] = "\n\nIt's a reget that\n\n you have lost your life.";
	PrintSpecialInfor(message);
	exit();
}

void PrintWin()
{
	char message[] = "\nCongratulations!\n\n With your great effort\n you've saved the true princess!";
	PrintSpecialInfor(message);
	exit();
}

void PrintShield(char* name, int defence)
{
	std::string n = name;
	std::string message = "\n\nYou get a " + n + "\n\nand get " + std::to_string(defence) + " Def";
	PrintSpecialInfor(message.c_str());
	exit();
}

void PrintSword(char* name, int attack)
{
	std::string n = name;
	std::string message = "\n\nYou get a " + n + "\n\nand get " + std::to_string(attack) + " Atk";
	PrintSpecialInfor(message.c_str());
	exit();
}

void PrintUsePickaxe()
{
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(40, 0, "Consolas");
	drawtext("\n\nUsing Pickaxe", &R1, DT_CENTER);
}
//图鉴
RECT R2 = { 300, 100, 750, 550 };
void MonsterEncyclopedia(Player& p)
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	setfillcolor(RGB(255, 255, 0));
	solidrectangle(300, 80, 750, 580); // 填充矩形
	settextstyle(35, 0, "Consolas");

	drawtext("Monster Encyclopedia", &R2, DT_CENTER);

	putimage(320, 150, &images[41]); //绿色史莱姆
	putimage(320, 250, &images[42]); //红色史莱姆
	putimage(320, 350, &images[43]); //蝙蝠
	putimage(320, 450, &images[47]); //骷髅
	putimage(540, 150, &images[46]); //巫师
	putimage(540, 250, &images[44]); //骷髅士兵
	putimage(540, 350, &images[45]); //魔王

	settextstyle(30, 0, "Consolas");
	for(int i=0;i<4;i++)
		outtextxy(430, 160+100*i, "Damage");
	for (int i = 0;i < 3;i++)
		outtextxy(650, 160 + 100 * i, "Damage");
	
	int d = Damage(p, GreenSlime);    //打印数值
	outtextxy(500 - 15 * countDigits(d), 210, std::to_string(d).c_str());
	d = Damage(p, RedSlime);
	outtextxy(500 - 15 * countDigits(d), 310, std::to_string(d).c_str());
	d = Damage(p, Bat);
	outtextxy(500 - 15 * countDigits(d), 410, std::to_string(d).c_str());
	d = Damage(p, Skeleton);
	outtextxy(500 - 15 * countDigits(d), 510, std::to_string(d).c_str());
	d = Damage(p, Wizard);
	outtextxy(720 - 15 * countDigits(d), 210, std::to_string(d).c_str());
	d = Damage(p, SkeletonSoldier);
	outtextxy(720 - 15 * countDigits(d), 310, std::to_string(d).c_str());
	//d = Damage(p, DemonKing);
	outtextxy(720 - 45, 410,"???");

	EndBatchDraw();
	while (1)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000)|| (GetAsyncKeyState('e') & 0x8000)\
			|| (GetAsyncKeyState('E') & 0x8000)) 
		{
			while ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState('e') & 0x8000)\
				|| (GetAsyncKeyState('E') & 0x8000))
			{
				Sleep(30);
			}
			break;
		}
	}
}

