#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}


void paintALine(int p1r, int p1c, int p2r, int p2c,
    char sym =-37, float delta = 0.01)
{
    for (float alpha = 0.0f; alpha <= 1.0f; alpha += delta)
    {
        int r = ceil(p1r * alpha + p2r * (1 - alpha));
        int c = ceil(p1c * alpha + p2c * (1 - alpha));

        if (p1r == p2r) r = p1r;
        if (p1c == p2c) c = p1c;

        gotoRowCol(r, c);
        cout << sym;
    }
}


void pPlus(int startR, int startC, int sizeR, int sizeC,
    char sym = -37, float delta = 0.005)
{

    paintALine(startR, startC + sizeC / 2,
        startR + sizeR - 1, startC + sizeC / 2, sym, delta);

    paintALine(startR + sizeR / 2, startC,
        startR + sizeR / 2, startC + sizeC - 1, sym, delta);
}

void cross(int startR, int startC, int sizeR, int sizeC,
    char sym =-37, float delta = 0.005)
{

    paintALine(startR, startC,
        startR + sizeR - 1, startC + sizeC - 1, sym, delta);
  
    paintALine(startR, startC + sizeC - 1,
        startR + sizeR - 1, startC, sym, delta);
}


void fans()
{
    hideConsoleCursor();
  

    float delay = 400.0;
    float delta = 0.005;
    char  sym = -37;

    int sizeR = 9;
    int sizeC = 17;

    
    int positions[5][2] =
    {
        {  2, 10 },
        {  2, 55 },
        { 18, 10 },
        { 18, 55 },
         {12,35}
    };

    bool isPlus = true;

    while (!_kbhit())
    {
        for (int i = 0; i < 5; i++)
        {
            if (isPlus)
                pPlus(positions[i][0], positions[i][1], sizeR, sizeC, sym, delta);
            else
                cross(positions[i][0], positions[i][1], sizeR, sizeC, sym, delta);
        }

        Sleep((DWORD)delay);

        for (int i = 0; i < 5; i++)
        {
            if (isPlus)
                pPlus(positions[i][0], positions[i][1], sizeR, sizeC, ' ', delta);
            else
                cross(positions[i][0], positions[i][1], sizeR, sizeC, ' ', delta);
        }

        isPlus = !isPlus;

      
        if (delay > 50.0)
            delay -= 50.0;
    }

    _getch();
}

void draw_a_circle(int c_r, int c_c, int r, int min_theta = 0,int maz_theta=360,char sym=-37)
{
    for (int i = min_theta; i <= maz_theta; i++)
    {
        int row = c_r + (-1) * (r * sin(i * 3.14 / 180));
        int col = c_c + (r * cos(i * 3.14 / 180));
        gotoRowCol(row, col);
        cout << sym;
    }
}

void print_a_circle(int cx, int cy, int r, char sym = -37, float delta = 360)
{

    for (int alpha = 1; alpha <= delta; alpha++)
    {
        int row = cx + (-1) * (r * sin(alpha * 3.14 / 180));
        int col = cy + (r * cos(alpha * 3.14 / 180));
        gotoRowCol(row, col);
        cout << sym;
    }
}

void drawRainbow()
{
    color(4);
    print_a_circle(17, 30, 10, -37, 180);
    color(6);
    print_a_circle(17, 30, 11, -37, 180);
    color(14);
    print_a_circle(17, 30, 12, -37, 180);
    color(10);
    print_a_circle(17, 30, 13, -37, 180);
    color(9);
    print_a_circle(17, 30, 14, -37, 180);
    color(1);
    print_a_circle(17, 30, 15, -37, 180);
    color(13);
    print_a_circle(17, 30, 16, -37, 180);
    color(7);
}
int main()
{
    
    






    int choice;

    do
    {
        system("cls");
        color(7);

        cout << "1. Rainbow\n2. Fans\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
          
            system("mode con lines=50 cols=120");
            hideConsoleCursor();


            drawRainbow();

            _getch();
            system("mode con lines=30 cols=85");
            break;
        }
        case 2:
        {
            system("cls");
            fans();
          //  system("mode con lines=30 cols=85");
            break;
        }
        case 3:
        {
            color(7);
            cout << "Closing Program!!\n";
            return 0;
        }
        default:
            cout << "\nInvalid choice. Press any key to try again.";
            _getch();
        }

    } while (choice != 3);

    return 0;
}