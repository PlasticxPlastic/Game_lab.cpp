#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
using namespace std;



void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y) {
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void erase_ship(int x, int y) {
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void draw_bullet(int x, int y)
{
	setcolor(4, 2);
	gotoxy(x, y);
	printf("^");
}

void erase_bullet(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf(" ");
}

void draw_ship(int x, int y) {
	setcolor(2, 4);
	gotoxy(x, y);
	printf(" <-0-> ");
}

int main() {
	int status;
	int bulletX[5], bulletY[5], bulletcount = 0, bulletstatus[5];
	setcursor(0);
	char ch = ' ';
	int x = 32, y = 20;
	status = 0;
	for (int i = 0; i < 5; i++)
		bulletstatus[i] = 0;
	draw_ship(x, y);
	do {
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 's')
				status = 0;
			if (ch == 'a')
				status = 1;
			if (ch == 'd')
				status = 2;
			if (ch == ' ' && bulletcount >= 0 && bulletcount <= 5)
			{
				bulletstatus[bulletcount] = 1;
				bulletX[bulletcount] = x + 3;
				bulletY[bulletcount] = y - 1;
				bulletcount++;
			}
			if (bulletcount >= 5 && bulletstatus[4] == 0)
			{
				bulletcount = 0;
			}
		}
		if (status == 1 && x > 0)
		{
			erase_ship(x, y);
			draw_ship(--x, y);
		}
		if (status == 2 && x < 80)
		{
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		if (status == 0)
		{
			erase_ship(x, y);
			draw_ship(x, y);
		}
		for (int i = 0; i < 5; i++)
		{
			if (bulletstatus[i] == 1)
			{
				erase_bullet(bulletX[i], bulletY[i]);
				if (bulletY[i] > 0)
					draw_bullet(bulletX[i], --bulletY[i]);
				else
					bulletstatus[i] = 0;
			}
		}
		fflush(stdin);
		Sleep(50);
	} while (ch != 'x');
	return 0;
}
