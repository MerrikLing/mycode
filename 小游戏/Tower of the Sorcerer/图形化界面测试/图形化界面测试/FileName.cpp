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
//// �������������ֲ�ͬ�ĵ�ͼԪ�أ����桢ǽ�ں͵���
//IMAGE images[35];
//
//// ����ͼƬ�ز�
//void LoadImages() {
//	//������һ��ʧ�ܵĳ��ԣ���֪������
//	
//	//std::string a = "0";
//	//for (int i = 0;i <= 12;i++)
//	//{// ���´���ʵ��  ����python��string format Ч��
//	//	int num = std::stoi(a); // ���ַ���ת��Ϊ����
//	//	num += i;               // ������ֵ����
//	//	a = std::to_string(num); // �����ת�����ַ���
//	//	std::string base_path = "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\";
//	//	std::string file_type = ".png";
//	//	std::string file_name = base_path + a + file_type;
//	//	std::wstring wfile_name(file_name.begin(), file_name.end());
//	//	LPCTSTR fileName = wfile_name.c_str();
//	//	loadimage(&images[i], fileName,50, 50);//�����������ֱ�ʾ��ͼ�����ŵ����
//	//}
//	
//	loadimage(&images[0],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\0.png", 50, 50);   //border
//    loadimage(&images[1],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\1.png", 50, 50);         //wall
//    loadimage(&images[2],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\2.png", 50, 50);        //minor_healing_potion
//    loadimage(&images[3],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\3.png", 50, 50);        //moderate_healing_potion
//    loadimage(&images[4],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\4.png", 50, 50);         //yellow_key
//    loadimage(&images[5],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\5.png", 50, 50);         //yellow_door
//    loadimage(&images[6],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\6.png", 50, 50);         //green_slime
//    loadimage(&images[7],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\7.png", 50, 50);         //area
//    loadimage(&images[8],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\8.png", 50, 50);         //player
//	loadimage(&images[9],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\9.png", 50, 50);         //red_slime
//    loadimage(&images[10],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\10.png", 50, 50);       //magma
//    loadimage(&images[11],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\11.png", 50, 50);      //upstairs
//    loadimage(&images[12],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\12.png", 50, 50);       //downstairs
//
//    loadimage(&images[30],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\30.png", 50, 50);  //bat
//    loadimage(&images[31],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\31.png", 50, 50);  //Skeleton
//    //loadimage(&images[10],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\10magma.png"));
//    //loadimage(&images[10],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\10magma.png"));
//
//}
//
//void PrintMap(int map[][COL]) {
//	for (int i = 0; i < ROW; ++i) {
//		for (int j = 0; j < COL; ++j) 
//		{
//			putimage(j * 50, i * 50, &images[map[i][j]]); // ��ʾͼ��
//
//			//int imgIndex = mapData[i][j] - '0'; // ���ַ�ת��Ϊ��������
//			//if (imgIndex >= 0 && imgIndex < MAX_IMAGES) {
//			//	putimage(j * ���, i * �߶�, &images[imgIndex], 1); // ��ʾͼ��
//			//}
//		}
//	}
//}
//char str[20] = "";
////����ת��Ϊ�ַ�
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
//    initgraph(800, 700); // ��ʼ��һ��800x600�Ĵ���
//    LoadImages();        // ����ͼƬ�ز�
//    PrintMap(Map[0]);          // ��ӡ��ͼ
////�������   650��������ͼƬ
//	//char s[] = "Hello World";
//	outtextxy(20, 660, intToString(12));
//	//outtextxy(10, 20, s);
//
//    getch();             // �ȴ��û�����
//    closegraph();        // �ر�ͼ�δ���
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
//// ������εĳ�ʼλ�úʹ�С
//int x = 100, y = 100, width = 200, height = 100;
//
//int main() {
//    // ��ʼ�� EasyX ͼ�λ���
//    initgraph(640, 480);
//
//    // ���ö�ʱ����2���ִ��
//    int timerId = SetTimer(NULL, 0, 2000, NULL);
//
//    // ���ƾ��κ�����
//    setfillcolor(RED); // ���������ɫΪ��ɫ
//    settextcolor(WHITE); // ����������ɫΪ��ɫ
//    settextstyle(20, 0, "Consolas"); // ����������ʽ
//    rectangle(x, y, x + width, y + height); // ���ƾ���
//    char text[] = "Hello, EasyX!"; // Ҫ��ʾ������
//    outtextxy(x + 10, y + 10, text); // ��ʾ����
//
//    // ��ʼ��������
//    BeginBatchDraw();
//
//    // �ȴ���ʱ������
//    while (true) {
//        if (WaitForSingleObject(GetTimerQueue(), INFINITE) == WAIT_OBJECT_0) {
//            // ��ʱ����������ʼ����Ч��
//            for (float alpha = 1.0f; alpha > 0; alpha -= 0.05f) {
//                SetAlphaBlendMode(ALPHABLEND_OVER, (BYTE)(alpha * 255));
//                Sleep(50); // �ȴ�һ��ʱ�䣬�Ա�۲쵭��Ч��
//                FlushBatchDraw(); // ˢ����������
//            }
//            EndBatchDraw(); // ������������
//            break; // �˳�ѭ��
//        }
//    }
//
//    // ������Դ
//    DeleteTimerQueueTimer(GetTimerQueue(), timerId, NULL);
//    closegraph(); // �ر�ͼ�λ���
//
//    return 0;
//}

#include <graphics.h>              // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
//#include <math.h>
//int r1[] = { 30,20,130,60 };//���밴ť�ľ��β���
//int r2[] = { 170,20,220,60 };//���а�ť�ľ��β���
//int r3[] = { 260,20,310,60 };//�˳���ť�ľ��β���
int main()
{
	int i;
	short win_width, win_height;//���崰�ڵĿ�Ⱥ͸߶�
	win_width = 850;win_height = 700;
	//initgraph(850, 700);//��ʼ�����ڣ�������
	mciSendString("open bk.mp3 alias background", 0, 0, 0);
	mciSendString("play background repeat", 0, 0, 0);

	system("pause");//��ͣ��Ϊ����ʾ
	//closegraph();
	return 0;
}
