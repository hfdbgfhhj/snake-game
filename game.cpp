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
	snake.Body[0].X = WIDE / 2;
	snake.Body[0].Y = HIGH / 2;
	snake.Body[1].X = WIDE / 2 - 1;
	snake.Body[1].Y = HIGH / 2;
	snake.Body[2].X = WIDE / 2 - 2;
	snake.Body[2].Y = HIGH / 2;
}

void InitFood() {
	int judge;
	do {
		judge = 0;
		food.pos.X = rand() % (WIDE - 2) + 1;
		food.pos.Y = rand() % (HIGH - 2) + 1;
		for (int i = 0;i < snake.size;i++) {
			if (food.pos.X == snake.Body[i].X && food.pos.Y == snake.Body[i].Y) {
				judge = 1;
				break;
			}
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
	Gotoxy(snake.Body[0].X, snake.Body[0].Y);
	printf("@");
	for (int i = 1;i < snake.size;i++) {
		Gotoxy(snake.Body[i].X, snake.Body[i].Y);
		printf("*");
	}
}

void DrawFood() {
	Gotoxy(food.pos.X, food.pos.Y);
	printf("$");
}

void MoveSnake() {
	Gotoxy(snake.Body[snake.size - 1].X, snake.Body[snake.size - 1].Y);
	printf(" ");
	for (int i = snake.size - 1;i > 0;i--) {
		snake.Body[i] = snake.Body[i - 1];
	}
	switch (snake.dir) {
	case KEY_UP: snake.Body[0].Y--;
		break;
	case KEY_DOWN: snake.Body[0].Y++;
		break;
	case KEY_LEFT: snake.Body[0].X--;
		break;
	case KEY_RIGHT: snake.Body[0].X++;
		break;
	}
}

void CheckEat() {
	if (snake.Body[0].X == food.pos.X && snake.Body[0].Y == food.pos.Y) {
		snake.size++;
		score += 10;
		InitFood();
		DrawFood();
		Gotoxy(0, HIGH);
		printf("Score:%d", score);
	}

}

void CheckCollision() {
	if (snake.Body[0].X <= 0 || snake.Body[0].X >= WIDE - 1 || snake.Body[0].Y <= 0 || snake.Body[0].Y >= HIGH - 1) {
		Gotoxy(WIDE / 2 - 5, HIGH / 2);
		printf("GAME OVER");
		Sleep(3000);
		exit(0);
	}
	for (int i = 1;i < snake.size;i++) {
		if (snake.Body[i].X == snake.Body[0].X && snake.Body[i].Y == snake.Body[0].Y) {
			Gotoxy(WIDE / 2 - 5, HIGH / 2);
			printf("GAME OVER");
			Sleep(3000);
			exit(0);
		}
	}
}