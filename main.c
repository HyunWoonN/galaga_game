#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct {
	int x, y;
}POS;

void gotoxy(int x, int y, char* s)

{

	COORD Pos = { x * 2,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	printf("%s", s);

}

void shoot_bullet(POS *ufo, POS *bullet)
{
	bullet[0].x = ufo[0].x;
	bullet[0].y = ufo[0].y - 1;
	bullet[1].x = bullet[0].x;
	bullet[1].y = bullet[0].y;

	for (int i = bullet[0].y; i > 0; i--)
	{
		gotoxy(bullet[0].x, i, "º");
		Sleep(30);
		gotoxy(bullet[0].x, i + 1, " ");
	}
	}
	

/* void remove_bullet(POS* ufo, POS* bullet)
{
	for (int i = bullet[0].y; i > 0; i--)
	{		
		gotoxy(bullet[0].x, i + 1, " ");

	}
}*/

void move_ufo(POS* ufo, POS* bullet) {
	static int dir = -1;
	if (_kbhit())
	{
		int key;
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case 72:
				dir = 0; //위
				break;

			case 80:
				dir = 1;  // 아래
				break;

			case 75:
				dir = 2;	//왼쪽
				break;

			case 77:	//오른쪽
				dir = 3;
				break;
			}
		}
	}

	if (dir != -1)
	{
		int x = ufo[1].x;
		int y = ufo[1].y;
		gotoxy(ufo[1].x, ufo[1].y, " ");
		gotoxy(x, y + 1, " ");
		gotoxy(x - 1, y + 2, "     ");
		gotoxy(x - 2, y + 3, " ");
		gotoxy(x + 2, y + 3, " ");
		gotoxy(x - 1, y + 3, "     ");
		gotoxy(x - 1, y + 4, "     ");
		gotoxy(x, y + 5, " ");
	}
	

	switch (dir)
	{
	case 0:
		ufo[0].y--;
		break;
	case 1:
		ufo[0].y++;
		break;
	case 2:
		ufo[0].x--;
		break;
	case 3:
		ufo[0].x++;
	}
	dir = -1;
}


void draw_ufo(POS *ufo)
{
	int x = ufo[0].x;
	int y = ufo[0].y;
	ufo[1].x = x;
	ufo[1].y = y;
	gotoxy(x, y, "▲");
	gotoxy(x, y+1, "■");
	gotoxy(x-1, y+2, "■■■");
	gotoxy(x-2, y+3, "↙");
	gotoxy(x+2, y+3, "↘");
	gotoxy(x-1, y+3, "▣▣▣");
	gotoxy(x-1, y+4, "◈◈◈");
	gotoxy(x, y+5, "◈");
}
void draw_map()
{

}


int main()
{
	POS ufo[100],bullet[100];
	ufo[0].x = 10;
	ufo[0].y = 10;
	int speed = 100;
	int refreshRate = 50;
	int cnt = 1;
	draw_map();
	while (1)
	{
		move_ufo(ufo,bullet);
		draw_ufo(ufo);
		shoot_bullet(ufo, bullet);
	}
	system("pause");
}