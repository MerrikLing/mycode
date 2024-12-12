#pragma once
#undef UNICODE    //��������ǳ���Ҫ�����ӵĻ�easyX��
                  //�����ַ����ļ�����Ҫ����Ȼ�󳬼��鷳
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define ROW 13
#define COL 13
#define FLOOR 4
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<conio.h>
#include<easyx.h>
#include <string>
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
    int red_key;   // ��Կ��
    int pickaxe;    //����
};

class Monster {
public:
    Monster(int hp, int atk, int def, int exp,int gold/*, char* name*/);
    int hp; // ����ֵ
    int atk; // ������
    int def; // ������
    int exp; // ����ֵ
    int money;
    ////char name[20];
    //const char* name;
};
//����
extern Monster GreenSlime; extern Monster RedSlime;
extern Monster Skeleton;  extern Monster SkeletonSoldier;
extern Monster Bat;
extern Monster Wizard;
extern Monster DemonKing;

//����
//void display_map(int map[][COL]);   //����̨�汾
int play(int map[][COL], Player &p);
void ChangeFloor(int Map[FLOOR][ROW][COL], Player& P, int ret);
int Damage(Player& p, const Monster& m);

void LoadImages();
void StartImage();
void InventInfor();
void InitImage();
void MonsterEncyclopedia(Player& p);
void PrintMap(int map[][COL], Player& p);    //ͼ�λ�
void PrintInfor(char* name, int d_hp, int money, int exp);
void PrintInfor(char* name, int addHP);
void PrintMessage(const char* message);
void PrintNoKey();
void PrintLvUp();
void PrintShield(char* name, int defence);
void PrintSword(char* name, int attack);
void PrintLifeGem(int defence);
void PrintAttackGem(int attack);
void PrintSpecialInfor(const char* name);
void PrintFalsePrincess();
void PrintLose();
void PrintWin();
void exit();
void PrintUsePickaxe();
//map
extern int Map[FLOOR][ROW][COL];

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
