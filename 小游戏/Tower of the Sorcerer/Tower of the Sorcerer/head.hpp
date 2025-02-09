#pragma once
#undef UNICODE    //这个东西非常重要，不加的话easyX中
                  //关于字符串的几乎都要报错，然后超级麻烦
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
#define CAPACITY 8 //背包容量
#define EAGLEFLAG 7 //鹰旗在背包中对应的位置
#define CROSS 6     //十字架...位置 
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

//类
class Player {
public:
    // 构造函数
    Player();
    int position[3]; // 位置数组
    int hp;         // 生命值
    int hp_limit;   // 生命值上限
    int atk;        // 攻击力
    int def;        // 防御力
    int money;      // 金钱
    int Lv;         // 等级
    int Exp;        // 经验值
    int yellow_key; // 黄钥匙
    int blue_key;   // 蓝钥匙
    int red_key;    // 红钥匙
    int pickaxe;    //镐子
    int killnumber; //击杀数
    int backpack[CAPACITY]; //背包中的物品
    int enhancedAtk;       //是否强化攻击
};

class Monster {
public:
    Monster(int hp, int atk, int def, int exp,int gold,int isSkeleton);
    int hp; // 生命值
    int atk; // 攻击力
    int def; // 防御力
    int exp; // 经验值
    int money;
    int isSkeleton;//是否能被十字架针对
};

//对象
extern Monster GreenSlime; extern Monster RedSlime;   
extern Monster Skeleton;  extern Monster SkeletonSoldier; extern Monster BoneWarrior; extern Monster SkeletonGeneral;
extern Monster Bat;  extern Monster BloodBat;
extern Monster EvilWizard;  extern Monster BloodWizard;
extern Monster Orc;
extern Monster DemonKing;
extern Monster DemonEmperor;

//函数
//void display_map(int map[][COL]);   //控制台版本
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
void PrintMap(int map[][COL], Player& p);    //图形化
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

//商品价格
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

//道具
void DrinkPotion(Player& p, int healing, int kind);
void GetDEFGem(Player& p, int defence);
void GetATKGem(Player& p, int attack);