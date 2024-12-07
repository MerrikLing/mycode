#include"head.hpp"
IMAGE images[50];
void LoadImagesHelper(int n)
{
	//std::string location = "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\" + std::to_string(n) + ".png";
	std::string location = std::to_string(n) + ".png";

	loadimage(&images[n], location.c_str(), 50, 50);  //����������ֱ�ʾ���ź�Ĵ�С
}
void LoadImages()       // ����ͼƬ�ز�
{
	for (int i = 0;i <= 37;i++)
		LoadImagesHelper(i);
	//�����ͼ�꣬������ʾ
	//loadimage(&images[49],  "D:\\Merrik\\code\\С��Ϸ\\Tower of the Sorcerer\\materials\\8.png", 100, 100);
	loadimage(&images[49], "49.png", 100, 100);

}

void InitImage()
{
	BeginBatchDraw();
	//�߿��ϵ�ͼƬ
	for (int i = 0; i < ROW + 4; ++i)  //�ϱ߿�
		putimage(i * 50, 0, &images[0]);
	for (int i = 0; i < ROW + 4; ++i)  //�±߿�
		putimage(i * 50, 600, &images[0]);
	for (int i = 1; i <= COL -1; ++i)  //��߿�
		putimage(0, i * 50, &images[0]);
	for (int i = 1; i <= COL - 1; ++i)  //�ұ߿�
		putimage(800, i * 50, &images[0]);
	//for (int i = 1; i <= COL - 1; ++i)  //��ͼ���
	//	putimage(200, i * 50, &images[0]);
	putimage(50, 50, &images[49]); //��
	putimage(50, 150, &images[14]); //hp
	putimage(50, 200, &images[13]); //atk
	putimage(50, 250, &images[15]); //def
	putimage(50, 300, &images[16]); //money
	putimage(50, 350, &images[4]); // yellow key
	putimage(50, 400, &images[17]);//blue key
	putimage(50, 450, &images[25]);// red key
	putimage(50, 500, &images[24]); //����
	EndBatchDraw();
}
//���������������Ҷ���
int countDigits(int number) {
	if (number == 0) return 1; // 0��һ���������������1λ

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
	for (int i = 1; i < ROW-1; ++i) {  //�߿��ǹ̶��ģ������ظ���ӡ
		for (int j = 1; j < COL-1; ++j)
		{
			putimage(200+j * 50, i * 50, &images[map[i][j]]); // ��ʾͼ��
		}
	}
	for (int i = 1; i <= COL - 1; ++i)  //��ͼ���
		putimage(200, i * 50, &images[0]);

	settextcolor(WHITE);
	settextstyle(40, 0,  "Consolas");
	outtextxy(155, 50,  "Lv");
	settextstyle(30, 0,  "Consolas");
	setfillcolor(getbkcolor());
	solidrectangle(100, 150, 165, 550); //�����֮ǰ��ӡ������
	outtextxy(190 - 15 * countDigits(p.Lv), 100, std::to_string(p.Lv).c_str());	//������ת�����ַ���
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

RECT R1 = { 240,230,700, 450 };//����ָ��R1�����ڴ�ӡ��Ϸ��������Ϣ
void PrintMessage(const char* message)
{
	setbkmode(TRANSPARENT);				//��������Ϊ͸��
	settextcolor(BLACK);
	for (int i = 256;i > 64;i -= 5)
	{                                   //˫���弼�����������ʱͼ����˸��Ч������
		BeginBatchDraw();               //�������EndBatchDraw();����ɶԳ���
		settextstyle(30, 0, "Consolas");
		setfillcolor(RGB(i, 0, 0));//��һ�����ֱ�ʾ��ɫ
		solidrectangle(240, 230, 700, 450); // ������
		drawtext(message, &R1, DT_CENTER);
		//�ھ�������R1���������֣�ˮƽ���У���ֱ����
		Sleep(30);
		EndBatchDraw();
	}
}

void PrintInfor(char*name,int d_hp,int money,int exp) //Battle
{
	
	std::string n = name; // ���ַ�ָ��ת��Ϊstd::string
	std::string message = "\n\nYou've beaten the " + n + "\nYou lost " + std::to_string(d_hp) + \
		" HP in the battle\nYou get " + std::to_string(money) + " gold coins\n";
	PrintMessage(message.c_str());
}

void PrintInfor(char* name, int addHP) //potion
{
	//"You find a minor healing potion and get 20 hp"
	std::string n = name; // ���ַ�ָ��ת��Ϊstd::string
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