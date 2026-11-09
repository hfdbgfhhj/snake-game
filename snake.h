#ifndef snake_h
#define snake_h

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
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

//食物位置
typedef struct {
	int X;
	int Y;
}Food;


//蛇身
typedef struct SnakeNode {
	int X;
	int Y;
	struct SnakeNode* next;
	struct SnakeNode* last;
}Node;

//蛇管理(储存数据）
typedef struct {
	int size;
	int dir;
	Node* head;
	Node* tail;
}Snake;
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