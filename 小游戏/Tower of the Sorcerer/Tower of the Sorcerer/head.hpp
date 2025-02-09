#pragma once
#undef UNICODE    //��������ǳ���Ҫ�����ӵĻ�easyX��
                  //�����ַ����ļ�����Ҫ����Ȼ�󳬼��鷳
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define ROW 13
#define COL 13
#define FLOOR 9
#define TwoA 4
#define TwoB 5
#define TwoC 6
#define TwoD 7
#define ThreeD 8
#define CAPACITY 8 //��������
#define EAGLEFLAG 7 //ӥ���ڱ����ж�Ӧ��λ��
#define CROSS 6     //ʮ�ּ�...λ�� 
#define IS_SKELETON 1
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
#include<easyx.h>
#include <string>
#include<time.h>

//map
extern int Map[FLOOR][ROW][COL];

//��
class Player {
public:
    // ���캯��
    Player();
    int position[3]; // λ������
    int hp;         // ����ֵ
    int hp_limit;   // ����ֵ����
    int atk;        // ������
    int def;        // ������
    int money;      // ��Ǯ
    int Lv;         // �ȼ�
    int Exp;        // ����ֵ
    int yellow_key; // ��Կ��
    int blue_key;   // ��Կ��
    int red_key;    // ��Կ��
    int pickaxe;    //����
    int killnumber; //��ɱ��
    int backpack[CAPACITY]; //�����е���Ʒ
    int enhancedAtk;       //�Ƿ�ǿ������
};

class Monster {
public:
    Monster(int hp, int atk, int def, int exp,int gold,int isSkeleton);
    int hp; // ����ֵ
    int atk; // ������
    int def; // ������
    int exp; // ����ֵ
    int money;
    int isSkeleton;//�Ƿ��ܱ�ʮ�ּ����
};

//����
extern Monster GreenSlime; extern Monster RedSlime;   
extern Monster Skeleton;  extern Monster SkeletonSoldier; extern Monster BoneWarrior; extern Monster SkeletonGeneral;
extern Monster Bat;  extern Monster BloodBat;
extern Monster EvilWizard;  extern Monster BloodWizard;
extern Monster Orc;
extern Monster DemonKing;
extern Monster DemonEmperor;

//����
//void display_map(int map[][COL]);   //����̨�汾
int play(int map[][COL], Player &p);
void ChangeFloor(int Map[FLOOR][ROW][COL], Player& P, int ret);
int Damage(Player& p, const Monster& m);
int YesOrNo();

//visualization
void LoadImages();
void StartImage();
void InventInfor();
void InitImage();
void MonsterEncyclopedia(Player& p);
void PrintStore(Player& p);
void PrintMap(int map[][COL], Player& p);    //ͼ�λ�
void PrintInfor(char* name, int d_hp, int money, int exp);
void PrintInfor(char* name, int addHP);
void PrintMessage(const char* message);
void PrintMessageYellow(const char* message);
void PrintNoKey();
void PrintLvUp();
void PrintShield(char* name, int defence);
void PrintSword(char* name, int attack);
void PrintLifeGem(int defence);
void PrintAttackGem(int attack);
void PrintSpecialInfor(const char* name);
void exit();
void PrintFalsePrincess();
void PrintLose();
void PrintWin();
void exit();
void PrintUsePickaxe();
void ShowBackpack(Player& p);
void PrintBattleRecovery(int recovery);

//audio
void musicGameLoading();
void musicPickup();
void musicBattle();
void musicEnter();
void musicLvUp();
void musicMeet();
void closeMusic();
void musicDie();
void musicWin();
void musicEncyclopedia();
void musicDrink();
void musicOpenBackpack();

//��Ʒ�۸�
#define PRICE1 60
#define PRICE2 100
#define PRICE3 100
#define PRICE4 300
#define PRICE5 400
#define PRICE6 150
#define PRICE7 300
#define PRICE8 500
#define PRICE9 600
#define PRICE0 700

//����
void DrinkPotion(Player& p, int healing, int kind);
void GetDEFGem(Player& p, int defence);
void GetATKGem(Player& p, int attack);