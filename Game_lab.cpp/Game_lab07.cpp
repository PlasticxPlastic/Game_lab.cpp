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

char cursor(int x, int y) {
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (
        !ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

        return '\0';
    else
        return buf[0];

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
    setcolor(4, 0);
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
    setcolor(3, 0);
    gotoxy(x, y);
    printf(" <-0-> ");
}

struct Star
{
    int x, y;
}star[20];

void draw_star(int x, int y)
{
    setcolor(7,0);
    gotoxy(x, y);
    printf("*");
}

void erase_star(int x, int y)
{
    setcolor(0, 0);
    gotoxy(x, y);
    printf(" ");
}

void scorepoint(int score)
{
    gotoxy(80, 2);
    printf("Score : %d", score);
}

void checkhit(int xbullet, int ybullet, int&score) {
    char check = cursor(xbullet, ybullet - 1);
    if (check == '*')
    {
        Beep(1000, 4);
        erase_star(xbullet, ybullet - 1);
        srand(time(NULL));
        draw_star((rand() % 70 + 10), (rand() % 5 + 2));
        scorepoint(++score);
    }
}

int main() {
    int status, score = 0;
    size_t bulletX[5], bulletY[5], bulletcount = 0, bulletstatus[5];
    setcursor(0);
    char ch = ' ';
    int x = 32, y = 20;
    status = 0;
    for (size_t i = 0; i < 5; i++)
        bulletstatus[i] = 0;
    srand(time(NULL));
    for (int i = 0; i < 20; i++)
    {
        star[i].x = (rand() % 70 + 10);
        star[i].y = (rand() % 5 + 2);
    }
    for (int i = 0; i < 20; i++)
    {
        draw_star(star[i].x, star[i].y);
    }
    scorepoint(score);
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
                checkhit(bulletX[i], bulletY[i], score);
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
