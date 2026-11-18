#ifndef snake_h
#define snake_h

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<graphics.h>
#include<tchar.h>

extern IMAGE img_body1;
extern IMAGE img_head1;
extern IMAGE img_head2;
extern IMAGE img_body2;
extern IMAGE img_food;

#define WIDE 50
#define HIGH 30

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

#define MAX_FOOD 3

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
void InitSnake1();//蛇初始化
void InitSnake2();
void InitFood();//食物初始化
void InitImage();//图片初始化
//渲染
void DrawSnake();//画蛇
void DrawFood();//画食物
void DrawMap();//画地图
//逻辑运行
void MoveSnake();
void CheckEat();
void CheckCollision();//检查撞墙，撞自己
void gameover();

//更新地图状态，判断食物生成是否合法
void Updatemap();

//声明变量
extern Snake snake1;
extern Snake snake2;
extern int score1;
extern int score2;
extern int map[WIDE][HIGH];
extern Food foods[MAX_FOOD];
#endif