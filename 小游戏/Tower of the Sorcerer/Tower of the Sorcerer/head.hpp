#pragma once
#undef UNICODE    //这个东西非常重要，不加的话easyX中
                  //关于字符串的几乎都要报错，然后超级麻烦
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
//类
class Player {
public:
    // 构造函数
    Player();
    int position[3]; // 位置数组
    int hp;         // 生命值
    int atk;        // 攻击力
    int def;        // 防御力
    int money;      // 金钱
    int Lv;         // 等级
    int Exp;        // 经验值
    int yellow_key; // 黄钥匙
    int blue_key;   // 蓝钥匙
    int red_key;   // 红钥匙
    int pickaxe;    //镐子
};

class Monster {
public:
    Monster(int hp, int atk, int def, int exp,int gold/*, char* name*/);
    int hp; // 生命值
    int atk; // 攻击力
    int def; // 防御力
    int exp; // 经验值
    int money;
    ////char name[20];
    //const char* name;
};
//对象
extern Monster GreenSlime;
extern Monster Skeleton;
extern Monster Bat;

//函数
//void display_map(int map[][COL]);   //控制台版本
int move(int map[][COL], Player &p);
void LoadImages();
void InitImage();
void PrintMap(int map[][COL], Player& p);    //图形化
void PrintInfor(char* name, int d_hp, int money, int exp);
void PrintInfor(char* name, int addHP);
void PrintNoKey();
void PrintLvUp();
//map
extern int Map[FLOOR][ROW][COL];


