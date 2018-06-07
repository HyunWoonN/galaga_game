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

	for (int i = bullet[0].y; i >= 0; i--)
	{
		gotoxy(bullet[0].x, i, "º");
		Sleep(30);
		gotoxy(bullet[0].x, i, " ");	//수정
	}
}	

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
			{		//수정
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
		if ((ufo[0].x == 2 && dir == 2) || (ufo[0].x == 57 && dir == 3))	//수정
		{
			return;
		}
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
}

void draw_enermy(int a, int b)
{
	gotoxy(a, b, "    ■          ■");
	gotoxy(a, b + 1, "      ■      ■  ");
	gotoxy(a, b + 2, "    ■■■■■■■");
	gotoxy(a, b + 3, "  ■■  ■■■  ■■\n");
	gotoxy(a, b + 4, "■■■■■■■■■■■\n");
	gotoxy(a, b + 5, "■  ■■■■■■■  ■\n");
	gotoxy(a, b + 6, "■  ■          ■  ■\n");
	gotoxy(a, b + 7, "      ■■  ■■      \n");
}

void remove_enermy1(int a, int b)
{
	gotoxy(a - 1, b, "      ");
	gotoxy(a - 1, b + 1, "      ");
	gotoxy(a - 1, b + 2, "      ");
	gotoxy(a - 1, b + 3, "      ");
	gotoxy(a - 1, b + 4, "      ");
	gotoxy(a - 1, b + 5, "      ");
	gotoxy(a - 1, b + 6, "      ");
	gotoxy(a - 1, b + 7, "      ");
	gotoxy(a, b - 1, "                      ");
}

void remove_enermy2(int a, int b)
{
	gotoxy(a + 8, b, "      ");
	gotoxy(a + 8, b + 1, "      ");
	gotoxy(a + 8, b + 2, "      ");
	gotoxy(a + 8, b + 3, "      ");
	gotoxy(a + 8, b + 4, "      ");
	gotoxy(a + 8, b + 5, "      ");
	gotoxy(a + 8, b + 6, "      ");
	gotoxy(a + 8, b + 7, "      ");
	gotoxy(a, b - 1, "                      ");
}

void move_enermy()
{
	int a = 0, b = 0;
	while (b < 21)
	{
		for (a = 0;a < 49;a++)
		{
			draw_enermy(a, b);
			Sleep(300);
			remove_enermy1(a, b);
		}
		b++;
		for (;a > 0;a--)
		{
			draw_enermy(a, b);
			Sleep(300);
			remove_enermy2(a, b);
		}
		b++;
	}
}

int main()
{
	POS ufo[100],bullet[100];
	ufo[0].x = 28;	//수정
	ufo[0].y = 28;
	int speed = 100;
	int refreshRate = 50;
	int cnt = 1;
	move_enermy();
	while (1)
	{
		move_ufo(ufo,bullet);
		draw_ufo(ufo);
		shoot_bullet(ufo, bullet);
	}
	system("pause");
}