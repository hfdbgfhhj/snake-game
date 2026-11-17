#include"snake.h"

void InitImage() {
	loadimage(&img_body1, _T("images/body1.png"), 30, 30);
	loadimage(&img_head1, _T("images/head1.png"), 30, 30);
	loadimage(&img_food, _T("images/food.png"), 30, 30);
}

IMAGE img_body1;
IMAGE img_head1;
IMAGE img_food;
Snake snake1;
int score;
int map[WIDE][HIGH] = { 0 };
Food foods[MAX_FOOD];

void InitSnake() {
	snake1.size = 3;
	snake1.dir = KEY_RIGHT;

	snake1.head = new Node;
	snake1.head->X = WIDE / 4;
	snake1.head->Y = HIGH / 2;
	snake1.head->next = NULL;
	snake1.head->last = NULL;

	Node* p = snake1.head;
	snake1.tail = snake1.head;
	for (int i = 1;i < snake1.size;i++) {
		Node* newnode = new Node;
		newnode->Y = HIGH / 2;
		newnode->X = WIDE / 4 - i;
		newnode->last = p;
		p->next = newnode;
		newnode->next = NULL;
		snake1.tail = newnode;
		p = p->next;
	}
}

void Updatemap() {
	Node* p = snake1.head;
	while (p != NULL) {
		int dx = p->X;
		int dy = p->Y;
		map[dx][dy] = 1;
		p = p->next;
	}
	delete p;
	for (int i = 0;i < MAX_FOOD;i++) {
		int dx = foods[i].X;
		int dy = foods[i].Y;
		map[dx][dy] = 1;
	}
}

void InitFood() {
	Updatemap();
	for (int i = 0;i < MAX_FOOD;i++) {
		int count = 0;
		int EmptyX[WIDE] = { 0 };
		int EmptyY[HIGH] = { 0 };
		for (int x = 0;x < WIDE;x++) {
			for (int y = 0;y < HIGH;y++) {
				if (map[x][y] == 0) {
					EmptyX[count] = x;
					EmptyY[count] = y;
					count++;
				}
			}
		}
		int j = rand() % (count - 1);
		foods[i].X = EmptyX[j];
		foods[i].Y = EmptyY[j];
		map[foods[i].X][foods[i].Y] = 1;
	}

}

void InitGame() {
	InitSnake();
	InitFood();
	score = 0;
}

void DrawMap() {
	setfillcolor(RGB(40, 40, 40));
	solidrectangle(0, 0, WIDE * 30,HIGH * 30);
	setlinecolor(RGB(80, 80, 80));
	for (int i = 0;i <=HIGH * 30;i += 30) {
		line(0, i , WIDE * 30, i );
	}
	for (int j = 0;j <= WIDE * 30;j += 30) {
		line(j , 0, j , HIGH * 30);
	}
	setlinecolor(RGB(255, 255, 255));
	rectangle(0, 0, WIDE * 30, HIGH * 30);
	TCHAR buf[64];
	_stprintf_s(buf,_T("score:%d"), score);
	settextcolor(RGB(255, 0, 0));
	settextstyle(24, 0,_T("Consolas"));
	outtextxy(90, 5, buf);
}

void DrawSnake() {
	Node* p = snake1.head;
	bool isHead = true;
	while (p != NULL) {
		int px = p->X*30;
		int py = p->Y*30;
		if (isHead) {
			putimage(px, py, &img_head1);
			isHead = false;
		}
		else {
			putimage(px, py, &img_body1);
		}
		p = p->next;
	}
}

void DrawFood() {
	int px = food.X*30;
	int py = food.Y*30;
	putimage(px, py, &img_food);
}

void MoveSnake() {
	Node* p = new Node;
	p->X = snake1.head->X;
	p->Y = snake1.head->Y;
	switch (snake1.dir) {
	case KEY_UP: p->Y--;
		break;
	case KEY_DOWN: p->Y++;
		break;
	case KEY_LEFT: p->X--;
		break;
	case KEY_RIGHT: p->X++;
		break;
	}
	p->next = snake1.head;
	p->last = NULL;
	snake1.head->last = p;
	snake1.head = p;
}

void CheckEat() {
	if (snake1.head->X == food.X && snake1.head->Y == food.Y) {
		snake1.size++;
		score += 10;
		InitFood();
	}
	else {
		Node* p = snake1.tail;
		snake1.tail = snake1.tail->last;
		snake1.tail->next = NULL;
		delete p;
	}
}
void gameover() {
	settextcolor(RGB(255, 0, 0));
	settextstyle(60, 0, _T("Consolas"));
	outtextxy(WIDE * 15 - 150, HIGH * 15 - 30, _T("GAME OVER"));
	FlushBatchDraw();
	Sleep(3000);
	Node* p = snake1.head;
	while (p != NULL) {
		Node* temp = p->next;
		delete p;
		p = temp;
	}
	snake1.head = NULL;
	snake1.tail = NULL;
	exit(0);
}
void CheckCollision() {
	if (snake1.head->X < 0 || snake1.head->X > WIDE - 1 || snake1.head->Y < 0 || snake1.head->Y > HIGH - 1) {
		gameover();
	}
	Node* p = snake1.head->next;
	while(p!=NULL) {
		if (snake1.head->X == p->X && snake1.head->Y ==p->Y) {
			gameover();
		}
		p = p->next;
	}
}