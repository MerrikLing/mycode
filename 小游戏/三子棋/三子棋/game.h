#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<windows.h>
#define ROW 3
#define COL 3
#define checker 3
void ini(char board[ROW][COL], int row, int col);
void display(char board[][COL], int row, int col);
void playermove(char board[][COL], int x, int y);
void program(char board[ROW][COL], int row, int col);
char judge(char board[ROW][COL], int row, int col);
