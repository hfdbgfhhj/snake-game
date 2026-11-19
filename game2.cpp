#include"snake.h"
void InitSnake2() {
	snake2.size = 3;
	snake2.dir = VK_RIGHT;

	Node* p = new Node;
	p->X = WIDE * (0.75);
	p->Y = HIGH / 2;
	p->next = NULL;
	p->last = NULL;
	snake2.head = p;
	for (int i = 1;i < snake2.size;i++) {
		int term = rand() % MAX_IMAGE;
		Node* newnode = new Node;
		newnode->X = WIDE * (0.75)-i;
		newnode->Y = HIGH / 2;
		newnode->image = term;
		newnode->last = p;
		p->next = newnode;
		p = p->next;
		newnode->next = NULL;
		
		snake2.tail = newnode;
	}
}

void DrawSnake2() {
	Node* p = snake2.head;
	bool ishead = true;
	while(p != NULL) {
		int dx = p->X*30;
		int dy = p->Y*30;
		if (ishead) {
			putimage(dx, dy, &img_head2);
			ishead = false;
		}
		else {
			putimage(dx, dy, &img_body2[p->image]);
		}
		p = p->next;
	}
}

void MoveSnake2() {
	Node* p = new Node;
	p->X = snake2.head->X;
	p->Y = snake2.head->Y;
	p->last = NULL;
	p->next = snake2.head;
	snake2.head->last = p;
	switch (snake2.dir) {
	case VK_RIGHT:p->X++;
		break;
	case VK_UP: p->Y--;
		break;
	case VK_DOWN: p->Y++;
		break;
	case VK_LEFT: p->X--;
		break;
	}
	snake2.head = p;
	p = p->next;
	while (p->next != NULL) {
		p->image = p->next->image;
		p = p->next;
	}
	int is = CheckEat2();
	if (is) {
		p->image = rand() % MAX_IMAGE;
	}
	else {
		snake2.tail = snake2.tail->last;
		snake2.tail->next = NULL;
		map[p->X][p->Y] = 0;
		delete p;
	}
}

bool CheckEat2() {
	int dx = snake2.head->X;
	int dy = snake2.head->Y;
	int cell = map[dx][dy];
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
		return true;
	}
	else {
		return false;
	}
}