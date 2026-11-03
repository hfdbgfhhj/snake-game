#include"snake.h"
int main() {
	srand((unsigned)time(NULL));
	InitGame();
	DrawMap();
	DrawFood();
	DrawSnake();
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				if (key == KEY_UP && snake.dir != KEY_DOWN) snake.dir = KEY_UP;
				if (key == KEY_DOWN && snake.dir != KEY_UP) snake.dir = KEY_DOWN;
				if (key == KEY_LEFT && snake.dir != KEY_RIGHT) snake.dir = KEY_LEFT;
				if (key == KEY_RIGHT && snake.dir != KEY_LEFT) snake.dir = KEY_RIGHT;
			}
			if (key == KEY_ESC) break;
		}
		MoveSnake();
		CheckEat();
		CheckCollision();
		DrawSnake();
		Sleep(150);
	}
	return 0;
}