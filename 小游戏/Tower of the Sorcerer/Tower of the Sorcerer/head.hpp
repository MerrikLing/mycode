#pragma once
#undef UNICODE    //��������ǳ���Ҫ�����ӵĻ�easyX��
                  //�����ַ����ļ�����Ҫ����Ȼ�󳬼��鷳
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define ROW 13
#define COL 13
#define FLOOR 3
//#define ATTACK 10
//#define LIFE 10
//#define DEFENSE 10
#include<cstdio>
#include<cstdlib>
#include<graphics.h>
#include<windows.h>
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
extern Monster GreenSlime;
extern Monster Skeleton;
extern Monster Bat;

//����
//void display_map(int map[][COL]);   //����̨�汾
int move(int map[][COL], Player &p);
void LoadImages();
void InitImage();
void PrintMap(int map[][COL], Player& p);    //ͼ�λ�
void PrintInfor(char* name, int d_hp, int money, int exp);
void PrintInfor(char* name, int addHP);
void PrintNoKey();
void PrintLvUp();
//map
extern int Map[FLOOR][ROW][COL];


