#include"snake.h"

Snake snake;
Food food;
int score;

void Gotoxy(int x, int y) {
	COORD pos = {
		(SHORT)x,(SHORT)y
	};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}



void InitSnake() {
	snake.size = 3;
	snake.dir = KEY_RIGHT;

	snake.head = new Node;
	snake.head->X = WIDE / 2;
	snake.head->Y = HIGH / 2;
	snake.head->next = NULL;
	snake.head->last = NULL;

	Node* p = snake.head;
	snake.tail = snake.head;
	for (int i = 1;i < snake.size;i++) {
		Node* newnode = new Node;
		newnode->Y = HIGH / 2;
		newnode->X = WIDE / 2 - i;
		newnode->last = p;
		p->next = newnode;
		newnode->next = NULL;
		snake.tail = newnode;
		p = p->next;
	}
}

void InitFood() {
	int judge;
	do {
		judge = 0;
		food.X = rand() % (WIDE - 2) + 1;
		food.Y = rand() % (HIGH - 2) + 1;
		Node* p = snake.head;
		while(p!=NULL) {
			if (food.X == p->X && food.Y == p->Y) {
				judge = 1;
				break;
			}
			p = p->next;
		}
	} while (judge);
}

void InitGame() {
	InitSnake();
	InitFood();
	score = 0;
	HideCursor();
}

void DrawMap() {
	for (int i = 0;i < HIGH;i++) {
		for (int j = 0;j < WIDE;j++) {
			if (i == 0 || i == HIGH - 1 || j == 0 || j == WIDE - 1) printf("#");
			else printf(" ");
		}
		printf("\n");
	}
	Gotoxy(0, HIGH);
	printf("Score:%d", score);
}

void DrawSnake() {
	Gotoxy(snake.head->X, snake.head->Y);
	printf("@");
	Node* p = snake.head->next;
	while(p!=NULL) {
		Gotoxy(p->X,p->Y);
		printf("*");
		p = p->next;
	}
}

void DrawFood() {
	Gotoxy(food.X, food.Y);
	printf("$");
}

void MoveSnake() {
	Node* p = new Node;
	p->X = snake.head->X;
	p->Y = snake.head->Y;
	switch (snake.dir) {
	case KEY_UP: p->Y--;
		break;
	case KEY_DOWN: p->Y++;
		break;
	case KEY_LEFT: p->X--;
		break;
	case KEY_RIGHT: p->X++;
		break;
	}
	p->next = snake.head;
	p->last = NULL;
	snake.head->last = p;
	snake.head = p;
}

void CheckEat() {
	if (snake.head->X == food.X && snake.head->Y == food.Y) {
		snake.size++;
		score += 10;
		InitFood();
		DrawFood();
		Gotoxy(0, HIGH);
		printf("Score:%d", score);
	}
	else {
		Gotoxy(snake.tail->X, snake.tail->Y);
		printf(" ");
		Node* p = snake.tail;
		snake.tail = snake.tail->last;
		snake.tail->next = NULL;
		delete p;
	}
}
void gameover() {
	Gotoxy(WIDE / 2 - 5, HIGH / 2);
	printf("GAME OVER");
	Sleep(3000);
	Node* p = snake.head;
	while (p != NULL) {
		Node* temp = p->next;
		delete p;
		p = temp;
	}
	snake.head = NULL;
	snake.tail = NULL;
	exit(0);
}
void CheckCollision() {
	if (snake.head->X <= 0 || snake.head->X >= WIDE - 1 || snake.head->Y <= 0 || snake.head->Y >= HIGH - 1) {
		gameover();
	}
	Node* p = snake.head->next;
	while(p!=NULL) {
		if (snake.head->X == p->X && snake.head->Y ==p->Y) {
			gameover();
		}
		p = p->next;
	}
}