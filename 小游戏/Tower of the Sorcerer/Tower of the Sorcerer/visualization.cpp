#include"head.hpp"
IMAGE images[100];
RECT R = { 0, 00, 850, 650 };//矩形指针，用于打印游戏开始画面

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
	//开始界面
	loadimage(&images[49], "49.jpg", 850, 650);

	for (int i = 50;i <= 74;i++)
		LoadImagesHelper(i, 50, 50);

}
void StartBackground()
{
	BeginBatchDraw();
	setfillcolor(BLACK);
	setbkmode(TRANSPARENT);

	putimage(0, 0, &images[49]);//

	settextstyle(70, 0, "Consolas");
	drawtext("\nTower of Sorcerer", &R, DT_CENTER);

	EndBatchDraw();
}

void StartImageHelper()
{
	while (1)
	{
		Sleep(70);
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))
		{
			while ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000))
			{
				Sleep(30);
			}
			break;
		}
	}
}

void StartImage()
{
	StartBackground();
	StartImageHelper();
	settextstyle(30, 0, "Consolas");   
	//In ages past, the Tower of the Sorcerer was raised to imprison the Demon King, its seals reinforced by generations of princesses.
	//But the dark lord, biding his time, grew strong once more.He shattered the bindings, wounded the princess, 
	//and locked her away, twisting the tower into a floating citadel of shadows.Cut off from the world, it now teems with monsters
	//and despair.You, a lone hero, awaken within its cursed walls.To survive, you must ascend, face the Demon King, 
	//and free the princess—or be lost forever.
	drawtext(\
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\nLong long ago,Tower of the Sorcerer was built to\nimprison Demon King,with its seals \nreinforced by generations of princesses.\
\nBut the Demon King secretly gathered power\nand grew strong once more"\
		, &R, DT_CENTER);
	StartImageHelper();
	//第二页
	StartBackground();
	settextstyle(30, 0, "Consolas");
	drawtext(\
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\nHe destroyed the prison,wounded the princess,\nlocked her away,and turning Tower into a floating castle\
\nCut off from the land,\nit's now filled with monsters and despair"\
, &R, DT_CENTER);
	StartImageHelper();
	//第三页
	StartBackground();
	settextstyle(30, 0, "Consolas");
	drawtext(\
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\nYou, a brave hero, wake up in the tower\nTo survive and escape from the Tower\
\nyou must face the Demon King, and save the Princess\n——or be lost forever."\
, &R, DT_CENTER);
	StartImageHelper();
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
	for (int i = 0; i < 4; ++i)  //上边框
		putimage(i * 50, 0, &images[0]);
	for (int i = 0; i <4; ++i)  //下边框
		putimage(i * 50, 600, &images[0]);
	for (int i = 1; i <= COL -1; ++i)  //左边框
		putimage(0, i * 50, &images[0]);
	//for (int i = 1; i <= COL - 1; ++i)  //右边框
	//	putimage(800, i * 50, &images[0]);
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
	for (int i = 0; i < ROW; ++i) 
	{  
		for (int j = 0; j < COL; ++j)
		{
			putimage(200+j * 50, i * 50, &images[map[i][j]]); // 显示图像
		}
	}
	//for (int i = 1; i <= COL - 1; ++i)  //地图左框
	//	putimage(200, i * 50, &images[0]);

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

//红色方块显示的信息，都调用下一函数！
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
		//在矩形区域R1内输入文字，水平居中
		Sleep(30);
		EndBatchDraw();
	}
}

void PrintBattleRecovery(int recovery)
{
	std::string message = "\n\nYou recover\n\n" + std::to_string(recovery) + \
		" HP in the battle";
	PrintMessage(message.c_str());
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
	std::string message = "\n\nYou drink a\n" + n + "\nand get " + std::to_string(addHP) + " HP";
	PrintMessage(message.c_str());
}

void PrintNoKey()//no enough key
{
	std::string message = "\n\n\nYou don't have enough keys!";
	PrintMessage(message.c_str());
}

void PrintMessageYellow(const char* message)
{
	setbkmode(TRANSPARENT);				//设置字体为透明
	settextcolor(RED);
	for (int i = 256;i > 64;i -= 5)
	{                                   //双缓冲技术来避免绘制时图像闪烁，效果显著
		BeginBatchDraw();               //与下面的EndBatchDraw();必须成对出现
		settextstyle(30, 0, "Consolas");
		setfillcolor(RGB(i, i, 0));//黄色
		solidrectangle(220, 230, 720, 450); // 填充矩形
		drawtext(message, &R1, DT_CENTER);
		//在矩形区域R1内输入文字，水平居中
		Sleep(50);
		EndBatchDraw();
	}
}
void PrintLvUp()
{
	//setbkmode(TRANSPARENT);				//设置字体为透明
	//settextcolor(RED);
	//for (int i = 256;i > 64;i -= 5)
	//{                                   //双缓冲技术来避免绘制时图像闪烁，效果显著
	//	BeginBatchDraw();               //与下面的EndBatchDraw();必须成对出现
	//	setfillcolor(RGB(i, i, 0));
	//	solidrectangle(220, 230, 720, 450); // 填充矩形
	//	settextstyle(50, 0, "Consolas");
	//	drawtext("\nLv up!", &R1, DT_CENTER);

	//	settextstyle(30, 0, "Consolas");
	//	drawtext("\n\n\n\nYou get 2 Atk  2 Def!\nMax HP limit increased by 50", &R1, DT_CENTER);
	//	Sleep(50);
	//	EndBatchDraw();
	//}
	PrintMessageYellow("\nLv up\n\nYou get 2 Atk  2 Def!\n\nMax HP limit increased by 50");
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
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		{
			while ((GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
			{
				Sleep(30);
			}
			break;
		}
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
	PrintSpecialInfor("\nUsing Pickaxe:\n\nUse arrow keys to choose\n\npress 'p' to cancel");
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

	putimage(400, 150, &images[6]); //绿色史莱姆
	putimage(400, 215, &images[9]); //红色史莱姆
	putimage(400, 280, &images[30]); //蝙蝠
	putimage(400, 345, &images[31]); //骷髅
	putimage(400, 410, &images[33]); //巫师
	putimage(400, 475, &images[32]); //骷髅士兵
	putimage(580, 150, &images[68]); //Blood bat
	putimage(580, 215, &images[70]); //Blood wizard
	putimage(580, 280, &images[69]); //BoneWarrior
	putimage(580, 345, &images[71]); //Orc
	putimage(580, 410, &images[72]); //SkeletonGeneral
	putimage(580, 475, &images[38]); //魔王

	settextstyle(25, 0, "Consolas");
	int d = Damage(p, GreenSlime);    //打印数值
	outtextxy(500 - 15 * countDigits(d), 160, std::to_string(d).c_str());
	d = Damage(p, RedSlime);
	outtextxy(500 - 15 * countDigits(d), 225, std::to_string(d).c_str());
	d = Damage(p, Bat);;
	outtextxy(500 - 15 * countDigits(d), 290, std::to_string(d).c_str());
	d = Damage(p, Skeleton);
	outtextxy(500 - 15 * countDigits(d), 355, std::to_string(d).c_str());
	d = Damage(p, EvilWizard);
	outtextxy(500 - 15 * countDigits(d), 420, std::to_string(d).c_str());
	d = Damage(p, SkeletonSoldier);
	outtextxy(500 - 15 * countDigits(d), 485, std::to_string(d).c_str());
	d = Damage(p, BloodBat);
	outtextxy(680 - 15 * countDigits(d), 160, std::to_string(d).c_str());
	d = Damage(p, BloodWizard);
	outtextxy(680 - 15 * countDigits(d), 225, std::to_string(d).c_str());
	d = Damage(p, BoneWarrior);
	outtextxy(680 - 15 * countDigits(d), 290, std::to_string(d).c_str());
	d = Damage(p, Orc);
	outtextxy(680 - 15 * countDigits(d), 355, std::to_string(d).c_str());
	d = Damage(p, SkeletonGeneral);
	outtextxy(680 - 15 * countDigits(d), 420, std::to_string(d).c_str());
	////魔王
	outtextxy(680 - 45, 485, "???");

	////for test
	//d = Damage(p, DemonKing);
	//outtextxy(680 - 15 * countDigits(d), 485, std::to_string(d).c_str());
	////

	settextstyle(20, 0, "Consolas");
	outtextxy(360, 530, "Numbers are damages from each monster");

	//注释部分为basic version
	//putimage(320, 150, &images[41]); //绿色史莱姆
	//putimage(320, 250, &images[42]); //红色史莱姆
	//putimage(320, 350, &images[43]); //蝙蝠
	//putimage(320, 450, &images[47]); //骷髅
	//putimage(540, 150, &images[46]); //巫师
	//putimage(540, 250, &images[44]); //骷髅士兵
	//putimage(540, 350, &images[45]); //魔王

	//settextstyle(30, 0, "Consolas");
	//for(int i=0;i<4;i++)
	//	outtextxy(430, 160+100*i, "Damage");
	//for (int i = 0;i < 3;i++)
	//	outtextxy(650, 160 + 100 * i, "Damage");
	//
	//int d = Damage(p, GreenSlime);    //打印数值
	//outtextxy(500 - 15 * countDigits(d), 210, std::to_string(d).c_str());
	//d = Damage(p, RedSlime);
	//outtextxy(500 - 15 * countDigits(d), 310, std::to_string(d).c_str());
	//d = Damage(p, Bat);
	//outtextxy(500 - 15 * countDigits(d), 410, std::to_string(d).c_str());
	//d = Damage(p, Skeleton);
	//outtextxy(500 - 15 * countDigits(d), 510, std::to_string(d).c_str());
	//d = Damage(p, EvilWizard);
	//outtextxy(720 - 15 * countDigits(d), 210, std::to_string(d).c_str());
	//d = Damage(p, SkeletonSoldier);
	//outtextxy(720 - 15 * countDigits(d), 310, std::to_string(d).c_str());
	////d = Damage(p, DemonKing);
	//outtextxy(720 - 45, 410,"???");

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

void PrintStore(Player& p) //商店，要增加商品序号
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	setfillcolor(RGB(255, 255, 0));
	solidrectangle(300, 80, 750, 580); // 填充矩形
	settextstyle(35, 0, "Consolas");

	drawtext("Store", &R2, DT_CENTER);
	putimage(320, 150, &images[2]); //小回复药剂
	putimage(320, 200, &images[3]); //中回复药剂
	putimage(320, 250, &images[4]); //yellow key
	putimage(320, 300, &images[17]); //blue key
	putimage(320, 350, &images[24]); //pickaxe
	putimage(320, 400, &images[56]); //宝箱
	putimage(320, 450, &images[60]); //mysterious potion
	putimage(550, 150, &images[61]); //wisdom potion
	putimage(550, 200, &images[21]); //波克剑
	putimage(550, 250, &images[22]); //波克盾
	settextstyle(25, 0, "Consolas");
	//序号
	for (int i = 1;i < 8;i++)
		outtextxy(305, 110 + 50 * i, std::to_string(i).c_str());
	outtextxy(535, 160, std::to_string(8).c_str());
	outtextxy(535, 210, std::to_string(9).c_str());
	outtextxy(535, 260, std::to_string(0).c_str());

	outtextxy(450 - 15 * countDigits(PRICE1)- 15, 160, "$");
	outtextxy(450 - 15 * countDigits(PRICE1), 160, std::to_string(PRICE1).c_str());//小回复药剂
	outtextxy(450 - 15 * countDigits(PRICE2) - 15, 210, "$");
	outtextxy(450 - 15 * countDigits(PRICE2), 210, std::to_string(PRICE2).c_str());//中回复药剂
	outtextxy(450 - 15 * countDigits(PRICE3) - 15, 260, "$");
	outtextxy(450 - 15 * countDigits(PRICE3), 260, std::to_string(PRICE3).c_str());//yellow key
	outtextxy(450 - 15 * countDigits(PRICE4) - 15, 310, "$");
	outtextxy(450 - 15 * countDigits(PRICE4), 310, std::to_string(PRICE4).c_str());//blue key
	outtextxy(450 - 15 * countDigits(PRICE5) - 15, 360, "$");
	outtextxy(450 - 15 * countDigits(PRICE5), 360, std::to_string(PRICE5).c_str());//pickaxe
	outtextxy(450 - 15 * countDigits(PRICE6) - 15, 410, "$");
	outtextxy(450 - 15 * countDigits(PRICE6), 410, std::to_string(PRICE6).c_str());//宝箱
	outtextxy(450 - 15 * countDigits(PRICE7) - 15, 460, "$");
	outtextxy(450 - 15 * countDigits(PRICE7), 460, std::to_string(PRICE7).c_str());//mysterious potion
	outtextxy(680 - 15 * countDigits(PRICE8) - 15, 160, "$");
	outtextxy(680 - 15 * countDigits(PRICE8), 160, std::to_string(PRICE8).c_str());//wisdom potion
	outtextxy(680 - 15 * countDigits(PRICE9) - 15, 210, "$");
	outtextxy(680 - 15 * countDigits(PRICE9), 210, std::to_string(PRICE9).c_str());//波克剑
	outtextxy(680 - 15 * countDigits(PRICE0) - 15, 260, "$");
	outtextxy(680 - 15 * countDigits(PRICE0), 260, std::to_string(PRICE0).c_str());//波克盾
	settextstyle(20, 0, "Consolas");

	outtextxy(360, 530, "Press the number of the goods to buy it");
	outtextxy(440, 560, "Press ESC to leave");
	EndBatchDraw();
}

void ShowBackpackHlper(int x, int PicNum,int n)//x表示实际显示出来的顺序,n 物品数量
{
	int y = x % 4;int z = x / 4;
	putimage(350 + y * 100, 150 + z * 100, &images[PicNum]);
	if(PicNum != 63  && PicNum != 64)//鹰旗和十字架不显示数量
	{
		outtextxy(390 + y * 100 - 15 * countDigits(n) - 15, 200 + z * 100, "x");
		outtextxy(390 + y * 100 - 15 * countDigits(n), 200 + z * 100, std::to_string(n).c_str());
	}
}

void ShowBackpack(Player& p)
{
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	setfillcolor(RGB(255, 255, 0));
	solidrectangle(300, 80, 750, 580); // 填充矩形
	settextstyle(35, 0, "Consolas");
	drawtext("Backpack", &R2, DT_CENTER);
	settextstyle(25, 0, "Consolas");

	int NumArr[] = {2,3,57,58,59,60,64,63};//储存图片对应的数字
		//数组中对应位置 0,小恢复药水；1，中恢复药水；2，Apple；3，葡萄；4 鱼，5 神秘药剂， 6 十字架，7 鹰旗 
	int x = -1; //是第一个打印出来的物品对应的x值为0
	for (int i = 0;i < CAPACITY;i++)
	{
		if (p.backpack[i] > 0)
		{
			x += 1;
			ShowBackpackHlper(x, NumArr[i],p.backpack[i]);
		}
	}
	settextstyle(20, 0, "Consolas");
	outtextxy(320, 430, "Press i to take minor healing potion (red)");
	outtextxy(320, 450, "      o to take moderate healing potion (blue)");
	if (p.pickaxe)
		outtextxy(320, 470, "      p to use pickaxe");
	if (p.backpack[EAGLEFLAG])
		outtextxy(320, 490, "      r to use EagleFlag,at the cost of 10 HP");
	if (p.backpack[5])
		outtextxy(320, 510, "      m to take mysterious potion");
	EndBatchDraw();

	while (1) //退出
	{
		Sleep(70);
		if ((GetAsyncKeyState('B') & 0x8000)|| (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		{
			while ((GetAsyncKeyState('B') & 0x8000) || (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
			{
				Sleep(30);
			}
			return;
		}
	}
}