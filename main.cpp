#include"snake.h"
int main() {
	srand((unsigned)time(NULL));
	initgraph(WIDE * 30, HIGH * 30);

	InitImage();
	InitGame();

	BeginBatchDraw();

	ExMessage msg;

	DrawMap();
	DrawFood();
	DrawSnake();
	while (1) {
		while (peekmessage(&msg,EM_KEY)){
			if (msg.message==WM_KEYDOWN) {
				switch (msg.vkcode) {
				case VK_UP:    if (snake1.dir != KEY_DOWN)  snake1.dir = KEY_UP;    break;
				case VK_DOWN:  if (snake1.dir != KEY_UP)    snake1.dir = KEY_DOWN;  break;
				case VK_LEFT:  if (snake1.dir != KEY_RIGHT) snake1.dir = KEY_LEFT;  break;
				case VK_RIGHT: if (snake1.dir != KEY_LEFT)  snake1.dir = KEY_RIGHT; break;
				case VK_ESCAPE:
					gameover();
					EndBatchDraw();
					closegraph();
					return 0;
				}
			}
		}
		MoveSnake();
		CheckEat();
		CheckCollision();
		DrawMap();
		DrawFood();
		DrawSnake();
		FlushBatchDraw();
		Sleep(200);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}