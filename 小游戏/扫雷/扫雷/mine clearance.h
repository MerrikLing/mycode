#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<time.h>
#define ROW 12
#define COL 12
#define mine ((ROW*COL*3)/20)//15%µÄÀ×
void ini(char board_show[][COL + 2]);
void set_mine(int board[][COL + 2], int x, int y);
void display(char board_show[][COL + 2]);
int operation(char board_show[][COL + 2], int x, int y, int board[][COL + 2]);
void mine_show(int board[][COL + 2]);
void clear_sur(char board_show[][COL + 2], int x, int y, int board[][COL + 2]);
void flag(char board_show[][COL + 2], int x, int y, int board[][COL + 2],int*m);
