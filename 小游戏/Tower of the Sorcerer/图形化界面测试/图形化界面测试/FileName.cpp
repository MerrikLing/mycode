#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#undef UNICODE
#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include<easyx.h>
//#include<TCHAR>

#define ROW 13
#define COL 13
#define FLOOR 3
//int Map[FLOOR][ROW][COL] = {
//	{//1
//			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//			{0,2,2,4,0,1,1,1,2,7,1,7,0},
//			{0,7,7,1,31,1,7,1,7,7,1,7,0},
//			{0,1,7,7,30,6,7,7,5,7,6,6,0},
//			{0,7,7,1,7,1,7,1,7,1,1,1,0},
//			{0,8,1,1,7,1,11,1,7,7,7,7,0},
//			{0,6,1,7,6,1,1,1,1,7,1,1,0},
//			{0,7,6,7,1,1,7,7,6,7,5,2,0},
//			{0,3,1,7,7,7,7,1,3,1,1,1,0},
//			{0,7,1,5,1,7,1,1,7,1,7,4,0},
//			{0,7,5,4,1,7,7,7,7,6,7,3,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0}
//	},
//
//	{//2
//			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//			{0,2,2,4,0,1,1,1,2,7,1,7,0},
//			{0,7,7,1,6,1,7,1,7,7,1,7,0},
//			{0,1,7,7,6,6,7,7,5,7,6,6,0},
//			{0,7,7,1,7,1,7,1,7,1,1,1,0},
//			{0,11,1,1,7,1,12,1,7,7,7,7,0},
//			{0,6,1,7,6,1,7,1,1,7,1,1,0},
//			{0,7,6,7,1,1,7,7,6,7,5,2,0},
//			{0,3,1,7,7,7,7,1,3,1,1,1,0},
//			{0,7,1,5,1,7,1,1,7,1,7,4,0},
//			{0,7,5,4,1,7,7,7,7,6,7,3,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0}
//	},
//
//	{//3
//			{ 0,0,0,0,0,0,0,0,0,0,0,0,0 },
//			{0,2,2,4,0,1,1,1,2,7,1,7,0},
//			{0,7,7,1,6,1,7,1,7,7,1,7,0},
//			{0,1,7,7,6,6,7,7,5,7,6,6,0},
//			{0,7,7,1,7,1,7,1,7,1,1,1,0},
//			{0,12,1,1,7,1,9,1,7,7,7,7,0},
//			{0,7,1,7,6,1,1,1,1,7,1,1,0},
//			{0,7,6,7,1,1,7,7,6,7,5,2,0},
//			{0,3,1,7,7,7,7,1,3,1,1,1,0},
//			{0,7,1,5,1,7,1,1,7,1,7,4,0},
//			{0,7,5,4,1,7,7,7,7,6,7,3,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0},
//			{0,0,0,0,0,0,0,0,0,0,0,0,0}
//	},
//};
//
//
//// 假设我们有三种不同的地图元素：地面、墙壁和敌人
//IMAGE images[35];
//
//// 加载图片素材
//void LoadImages() {
//	//以下是一次失败的尝试，不知道错因
//	
//	//std::string a = "0";
//	//for (int i = 0;i <= 12;i++)
//	//{// 以下代码实现  类似python中string format 效果
//	//	int num = std::stoi(a); // 将字符串转换为整数
//	//	num += i;               // 进行数值增加
//	//	a = std::to_string(num); // 将结果转换回字符串
//	//	std::string base_path = "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\";
//	//	std::string file_type = ".png";
//	//	std::string file_name = base_path + a + file_type;
//	//	std::wstring wfile_name(file_name.begin(), file_name.end());
//	//	LPCTSTR fileName = wfile_name.c_str();
//	//	loadimage(&images[i], fileName,50, 50);//后面两个数字表示把图像缩放到多大
//	//}
//	
//	loadimage(&images[0],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\0.png", 50, 50);   //border
//    loadimage(&images[1],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\1.png", 50, 50);         //wall
//    loadimage(&images[2],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\2.png", 50, 50);        //minor_healing_potion
//    loadimage(&images[3],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\3.png", 50, 50);        //moderate_healing_potion
//    loadimage(&images[4],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\4.png", 50, 50);         //yellow_key
//    loadimage(&images[5],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\5.png", 50, 50);         //yellow_door
//    loadimage(&images[6],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\6.png", 50, 50);         //green_slime
//    loadimage(&images[7],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\7.png", 50, 50);         //area
//    loadimage(&images[8],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\8.png", 50, 50);         //player
//	loadimage(&images[9],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\9.png", 50, 50);         //red_slime
//    loadimage(&images[10],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\10.png", 50, 50);       //magma
//    loadimage(&images[11],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\11.png", 50, 50);      //upstairs
//    loadimage(&images[12],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\12.png", 50, 50);       //downstairs
//
//    loadimage(&images[30],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\30.png", 50, 50);  //bat
//    loadimage(&images[31],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\31.png", 50, 50);  //Skeleton
//    //loadimage(&images[10],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\10magma.png"));
//    //loadimage(&images[10],  "D:\\Merrik\\code\\小游戏\\Tower of the Sorcerer\\materials\\10magma.png"));
//
//}
//
//void PrintMap(int map[][COL]) {
//	for (int i = 0; i < ROW; ++i) {
//		for (int j = 0; j < COL; ++j) 
//		{
//			putimage(j * 50, i * 50, &images[map[i][j]]); // 显示图像
//
//			//int imgIndex = mapData[i][j] - '0'; // 将字符转换为整数索引
//			//if (imgIndex >= 0 && imgIndex < MAX_IMAGES) {
//			//	putimage(j * 宽度, i * 高度, &images[imgIndex], 1); // 显示图像
//			//}
//		}
//	}
//}
//char str[20] = "";
////整数转换为字符
//char* intToString(int Number)
//{
//	int len = 0;
//
//	if (Number == 0) {
//		str[0] = '0';
//		len++;
//	}
//	while (Number)
//	{
//		str[len++] = Number % 10 + '0';
//		Number /= 10;
//	}
//	for (int i = 0; i < len / 2; i++) {
//		char t = str[i];
//		str[i] = str[len - i - 1];
//		str[len - i - 1] = t;
//	}
//	str[len] = '\0';
//	return str;
//}
//
//int main() {
//    initgraph(800, 700); // 初始化一个800x600的窗口
//    LoadImages();        // 加载图片素材
//    PrintMap(Map[0]);          // 打印地图
////输出文字   650及以上是图片
//	//char s[] = "Hello World";
//	outtextxy(20, 660, intToString(12));
//	//outtextxy(10, 20, s);
//
//    getch();             // 等待用户按键
//    closegraph();        // 关闭图形窗口
//
//	//int a = int("1");
//	//a += 1;
//	//printf("%d", a);
//    return 0;
//
//}

//#include <graphics.h>
//#include <time.h>
//
//// 定义矩形的初始位置和大小
//int x = 100, y = 100, width = 200, height = 100;
//
//int main() {
//    // 初始化 EasyX 图形环境
//    initgraph(640, 480);
//
//    // 设置定时器，2秒后执行
//    int timerId = SetTimer(NULL, 0, 2000, NULL);
//
//    // 绘制矩形和文字
//    setfillcolor(RED); // 设置填充颜色为红色
//    settextcolor(WHITE); // 设置文字颜色为白色
//    settextstyle(20, 0, "Consolas"); // 设置文字样式
//    rectangle(x, y, x + width, y + height); // 绘制矩形
//    char text[] = "Hello, EasyX!"; // 要显示的文字
//    outtextxy(x + 10, y + 10, text); // 显示文字
//
//    // 开始批量绘制
//    BeginBatchDraw();
//
//    // 等待定时器触发
//    while (true) {
//        if (WaitForSingleObject(GetTimerQueue(), INFINITE) == WAIT_OBJECT_0) {
//            // 定时器触发，开始淡出效果
//            for (float alpha = 1.0f; alpha > 0; alpha -= 0.05f) {
//                SetAlphaBlendMode(ALPHABLEND_OVER, (BYTE)(alpha * 255));
//                Sleep(50); // 等待一段时间，以便观察淡出效果
//                FlushBatchDraw(); // 刷新批量绘制
//            }
//            EndBatchDraw(); // 结束批量绘制
//            break; // 退出循环
//        }
//    }
//
//    // 清理资源
//    DeleteTimerQueueTimer(GetTimerQueue(), timerId, NULL);
//    closegraph(); // 关闭图形环境
//
//    return 0;
//}

#include <graphics.h>              // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
//#include <math.h>
//int r1[] = { 30,20,130,60 };//输入按钮的矩形参数
//int r2[] = { 170,20,220,60 };//运行按钮的矩形参数
//int r3[] = { 260,20,310,60 };//退出按钮的矩形参数
int main()
{
	int i;
	short win_width, win_height;//定义窗口的宽度和高度
	win_width = 850;win_height = 700;
	//initgraph(850, 700);//初始化窗口（黑屏）
	mciSendString("open bk.mp3 alias background", 0, 0, 0);
	mciSendString("play background repeat", 0, 0, 0);

	system("pause");//暂停，为了显示
	//closegraph();
	return 0;
}
