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
		Node* newnode = new Node;
		newnode->X = WIDE * (0.75)-i;
		newnode->Y = HIGH / 2;
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
			putimage(dx, dy, &img_body2);
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
}