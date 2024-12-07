#include"head.hpp"
IMAGE images[50];
void LoadImagesHelper(int n)
{
	//std::string location = "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\" + std::to_string(n) + ".png";
	std::string location = std::to_string(n) + ".png";

	loadimage(&images[n], location.c_str(), 50, 50);  //最后两个数字表示缩放后的大小
}
void LoadImages()       // 加载图片素材
{
	for (int i = 0;i <= 37;i++)
		LoadImagesHelper(i);
	//人物大图标，用于显示
	//loadimage(&images[49],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\8.png", 100, 100);
	loadimage(&images[49], "49.png", 100, 100);

}

void InitImage()
{
	BeginBatchDraw();
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
	putimage(50, 50, &images[49]); //人
	putimage(50, 150, &images[14]); //hp
	putimage(50, 200, &images[13]); //atk
	putimage(50, 250, &images[15]); //def
	putimage(50, 300, &images[16]); //money
	putimage(50, 350, &images[4]); // yellow key
	putimage(50, 400, &images[17]);//blue key
	putimage(50, 450, &images[25]);// red key
	putimage(50, 500, &images[24]); //镐子
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
	solidrectangle(100, 150, 165, 550); //先清空之前打印的数据
	outtextxy(190 - 15 * countDigits(p.Lv), 100, std::to_string(p.Lv).c_str());	//把数字转化成字符串
	outtextxy(165 - 15 * countDigits(p.hp), 160, std::to_string(p.hp).c_str());
	outtextxy(165 - 15 * countDigits(p.atk), 210, std::to_string(p.atk).c_str());
	outtextxy(165 - 15 * countDigits(p.def), 260, std::to_string(p.def).c_str());
	outtextxy(165 - 15 * countDigits(p.money), 310, std::to_string(p.money).c_str());
	outtextxy(165 - 15 * countDigits(p.yellow_key), 360, std::to_string(p.yellow_key).c_str());
	outtextxy(165 - 15 * countDigits(p.blue_key), 410, std::to_string(p.blue_key).c_str());
	outtextxy(165 - 15 * countDigits(p.red_key), 460, std::to_string(p.red_key).c_str());
	outtextxy(165 - 15 * countDigits(p.pickaxe), 510, std::to_string(p.pickaxe).c_str());
	EndBatchDraw();
}

RECT R1 = { 240,230,700, 450 };//矩形指针R1，用于打印游戏进程中信息
void PrintMessage(const char* message)
{
	setbkmode(TRANSPARENT);				//设置字体为透明
	settextcolor(BLACK);
	for (int i = 256;i > 64;i -= 5)
	{                                   //双缓冲技术来避免绘制时图像闪烁，效果显著
		BeginBatchDraw();               //与下面的EndBatchDraw();必须成对出现
		settextstyle(30, 0, "Consolas");
		setfillcolor(RGB(i, 0, 0));//第一个数字表示红色
		solidrectangle(240, 230, 700, 450); // 填充矩形
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
	std::string message = "\nLv up! \n\nYou get 100 HP  5 Atk  5 Def!";
	PrintMessage(message.c_str());
}