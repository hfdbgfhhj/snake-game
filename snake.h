#ifndef snake_h
#define snake_h

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define WIDE 60
#define HIGH 20

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

//单个蛇身or食物位置
typedef struct {
	int X;
	int Y;
}Point;


//蛇的结构体
typedef struct {
	Point Body[WIDE*HIGH];
	int size;
	int dir;
}Snake;

//食物的结构体
typedef struct {
	Point pos;
}Food;

//初始化
void InitGame();//游戏总体初始化
void InitSnake();//蛇初始化
void InitFood();//食物初始化
//渲染
void DrawSnake();//画蛇
void DrawFood();//画食物
void DrawMap();//画地图
void DrawUI();//画界面
//逻辑运行
void MoveSnake();
void CheckEat();
void CheckCollision();//检查撞墙，撞自己

//声明变量
extern Snake snake;
extern Food food;
extern int score;

#endif