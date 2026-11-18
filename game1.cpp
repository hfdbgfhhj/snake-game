#include"snake.h"

void InitImage() {
	loadimage(&img_body1, _T("images/body1.png"), 30, 30);
	loadimage(&img_head1, _T("images/head1.png"), 30, 30);
	loadimage(&img_food, _T("images/food.png"), 30, 30);
	loadimage(&img_body2, _T("images/body2.png"), 30, 30);
	loadimage(&img_head2, _T("images/head2.png"), 30, 30);
}

IMAGE img_body1;
IMAGE img_head1;
IMAGE img_food;
IMAGE img_head2;
IMAGE img_body2;
Snake snake2;
Snake snake1;
int score1;
int score2;
int map[WIDE][HIGH] = { 0 };
Food foods[MAX_FOOD];

void InitSnake1() {
	snake2.size = 3;
	snake2.dir = VK_RIGHT;

	snake2.head = new Node;
	snake2.head->X = WIDE / 4;
	snake2.head->Y = HIGH / 2;
	snake2.head->next = NULL;
	snake2.head->last = NULL;

	Node* p = snake2.head;
	snake2.tail = snake2.head;
	for (int i = 1;i < snake2.size;i++) {
		Node* newnode = new Node;
		newnode->Y = HIGH / 2;
		newnode->X = WIDE / 4 - i;
		newnode->last = p;
		p->next = newnode;
		newnode->next = NULL;
		snake2.tail = newnode;
		p = p->next;
	}
}

// 随机取一个空格；地图上没有空格时返回 false
static bool RandomEmptyCell(int* ox, int* oy) {
	static int ex[WIDE * HIGH], ey[WIDE * HIGH];
	int count = 0;
	for (int x = 0;x < WIDE;x++) {
		for (int y = 0;y < HIGH;y++) {
			if (map[x][y] == 0) {
				ex[count] = x;
				ey[count] = y;
				count++;
			}
		}
	}
	if (count == 0) return false;
	int j = rand() % count;
	*ox = ex[j];
	*oy = ey[j];
	return true;
}

// 只负责把蛇身写进 map
void Updatemap() {
	for (int x = 0;x < WIDE;x++) {
		for (int y = 0;y < HIGH;y++) {
			map[x][y] = 0;
		}
	}
	for (Node* p = snake2.head; p != NULL; p = p->next) {
		map[p->X][p->Y] = 1;
	}
	for (Node* p = snake1.head;p != NULL;p = p->next) {
		map[p->X][p->Y] = 1;
	}
}

// 一次生成 MAX_FOOD 个食物
void InitFood() {
	for (int i = 0;i < MAX_FOOD;i++) {
		foods[i].X = -1;			// -1 表示这一格没有食物
		foods[i].Y = -1;
		if (RandomEmptyCell(&foods[i].X, &foods[i].Y)) {
			map[foods[i].X][foods[i].Y] = 2;
		}
	}
}

void InitGame() {
	InitSnake1();
	InitSnake2();
	Updatemap();
	InitFood();
	score1 = 0;
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
	TCHAR buf1[64];
	_stprintf_s(buf1,_T("score1:%d"), score1);
	settextcolor(RGB(255, 0, 0));
	settextstyle(24, 0,_T("Consolas"));
	outtextxy(90, 5, buf1);
	TCHAR buf2[64];
	_stprintf_s(buf2, _T("score2: % d"), score2);
	settextcolor(RGB(255, 0, 0));
	settextstyle(24, 0, _T("Consolas"));
	outtextxy(WIDE*30-200, 5, buf2);
}

void DrawSnake1() {
	Node* p = snake2.head;
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
	for (int i = 0;i < MAX_FOOD;i++) {
		if (foods[i].X >= 0) {
			putimage(foods[i].X * 30, foods[i].Y * 30, &img_food);
		}
	}
}

void MoveSnake1() {
	Node* p = new Node;
	p->X = snake2.head->X;
	p->Y = snake2.head->Y;
	switch (snake2.dir) {
	case VK_UP: p->Y--;
		break;
	case VK_DOWN: p->Y++;
		break;
	case VK_LEFT: p->X--;
		break;
	case VK_RIGHT: p->X++;
		break;
	}
	p->next = snake2.head;
	p->last = NULL;
	snake2.head->last = p;
	snake2.head = p;
	// 这里不再写 map：新头是不是食物交给 CheckEat 判断，
	// 否则会把食物标记 2 覆盖成 1，永远吃不到东西
}

void CheckEat() {
	int dx = snake2.head->X;
	int dy = snake2.head->Y;

	int cell = map[dx][dy];
	map[dx][dy] = 1;			// 新头占位

	if (cell == 2) {			// 吃到食物：不删尾巴，蛇变长
		score1 += 10;
		//snake1.size++;
		for (int i = 0;i < MAX_FOOD;i++) {
			if (foods[i].X == dx && foods[i].Y == dy) {	// 只补充被吃掉的那一个
				if (RandomEmptyCell(&foods[i].X, &foods[i].Y)) {
					map[foods[i].X][foods[i].Y] = 2;
				}
				else {
					foods[i].X = -1;	// 地图满了就不再生成
					foods[i].Y = -1;
				}
				break;
			}
		}
	}
	else {						// 没吃到：删尾巴
		map[snake2.tail->X][snake2.tail->Y] = 0;
			Node* p = snake2.tail;
			snake2.tail = snake2.tail->last;
			snake2.tail->next = NULL;
			delete p;
	}
	dx = snake1.head->X;
	dy = snake1.head->Y;
	cell = map[dx][dy];
	map[dx][dy] = 1;
	if (cell == 2) {
		score2 += 10;
		for (int i = 0;i < MAX_FOOD;i++) {
			if (dx == foods[i].X && dy == foods[i].Y) {
				if (RandomEmptyCell(&foods[i].X, &foods[i].Y)) {
					map[foods[i].X][foods[i].Y] = 2;
				}
				else {
					foods[i].X = -1;
					foods[i].Y = -1;
				}
				break;
			}
		}
	}
	else {
		map[snake1.tail->X][snake1.tail->Y] = 0;
		map[dx][dy] = 1;
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
	Node* p = snake2.head;
	while (p != NULL) {
		Node* temp = p->next;
		delete p;
		p = temp;
	}
	snake2.head = NULL;
	snake2.tail = NULL;
	Node* q = snake1.head;
	while (q != NULL) {
		Node* temp = q->next;
		delete q;
		q = temp;
	}
	snake1.head = NULL;
	snake1.tail = NULL;
	exit(0);
}
void CheckCollision() {
	if (snake2.head->X < 0 || snake2.head->X > WIDE - 1 || snake2.head->Y < 0 || snake2.head->Y > HIGH - 1) {
		gameover();
	}
	if (snake1.head->X < 0 || snake1.head->X > WIDE - 1 || snake1.head->Y < 0 || snake1.head->Y > HIGH - 1) {
		gameover();
	}
	Node* p = snake2.head->next;
	while(p!=NULL) {
		if (snake2.head->X == p->X && snake2.head->Y ==p->Y) {
			gameover();
		}
		p = p->next;
	}
	Node* q = snake1.head->next;
	while (q != NULL) {
		if (snake1.head->X == q->X && snake1.head->Y == q->Y) {
			gameover();
		}
		q = q->next;
	}
}
