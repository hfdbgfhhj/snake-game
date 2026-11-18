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
	DrawSnake1();
	while (1) {
		while (peekmessage(&msg,EM_KEY)){
			if (msg.message==WM_KEYDOWN) {
				switch (msg.vkcode) {
				case VK_UP:    if (snake2.dir != VK_DOWN)  snake2.dir = VK_UP;    break;
				case VK_DOWN:  if (snake2.dir != VK_UP)    snake2.dir = VK_DOWN;  break;
				case VK_LEFT:  if (snake2.dir != VK_RIGHT) snake2.dir = VK_LEFT;  break;
				case VK_RIGHT: if (snake2.dir != VK_LEFT)  snake2.dir = VK_RIGHT; break;
				case 'W':    if (snake1.dir != VK_DOWN)  snake1.dir = VK_UP;    break;
				case 'S':  if (snake1.dir != VK_UP)    snake1.dir = VK_DOWN;  break;
				case 'A':  if (snake1.dir != VK_RIGHT) snake1.dir = VK_LEFT;  break;
				case 'D': if (snake1.dir != VK_LEFT)  snake1.dir = VK_RIGHT; break;
				case VK_ESCAPE:
					gameover();
					EndBatchDraw();
					closegraph();
					return 0;
				}
			}
		}
		MoveSnake1();
		MoveSnake2();
		CheckEat();
		CheckCollision();
		DrawMap();
		DrawFood();
		DrawSnake1();
		DrawSnake2();
		FlushBatchDraw();
		Sleep(200);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}
