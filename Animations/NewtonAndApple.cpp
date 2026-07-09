#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>

using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
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

void print_a_line(int x1, int y1, int x2, int y2, char sym = -37, float delta = 0.0001)
{

    for (float alpha = 0; alpha <= 1; alpha += delta)
    {
        int r = ceil((x1 * (1 - alpha)) + (x2 * (alpha)));

        int c = ceil((y1 * (1 - alpha)) + (y2 * (alpha)));


        if (x1 == x2)r = x1;
        if (y1 == y2)c = y1;

        gotoRowCol(r, c);
        cout << sym;
    }
}

void print_a_circle(int cx, int cy,int r, char sym = -37, float delta = 360)
{

    for (int alpha = 1; alpha <= delta ; alpha++)
    {
        int row = cx + (-1) * (r * sin(alpha * 3.14 / 180));
        int col = cy + (r * cos(alpha * 3.14 / 180));
        gotoRowCol(row, col);
        cout << sym;
    }
}

void Building()
{
    print_a_line(5, 5, 35, 5, -37, 0.001);
    print_a_line(8, 25, 35, 25, -37, 0.001);
    print_a_line(9, 5, 9, 25, -37, 0.001);
    gotoRowCol(7, 6);
    cout << 'A';
    gotoRowCol(7, 7);
    cout << 'R';
    gotoRowCol(7, 8);
    cout << 'F';
    gotoRowCol(7, 9);
    cout << 'A';
    print_a_line(4, 5, 8, 25, -37, 0.001);

    print_a_line(35, 5, 35, 25, -37, 0.001);

    print_a_line(11, 6, 11, 15, -37, 0.001);
    print_a_line(13, 6, 13, 15, -37, 0.001);
    print_a_line(15, 6, 15, 15, -37, 0.001);

}

void Tree()
{

    print_a_circle(20, 80, 7);
    color(4);
    print_a_circle(17, 76, 1);
    color(15);

    for (int i = 27; i <= 35; i++)
        print_a_line(i, 78, i, 81, -37, 0.01);


}


void apple_falling(int sr, int sc, float vx, float delta = 0.05, char sym = -37)
{
    int D_r = 32;
    print_a_circle(20, 80, 7,' ');
    for (float t = 0; true; t += delta)
    {
        int r = ceil(0.5 * 9.8 * t * t + sr);
        int c = sc;


        gotoRowCol(r, c);
        color(4);
        print_a_circle(r, c,1);
        color(15);
        if (r == D_r)break;

        Sleep(40);              // let this frame stay on screen so the fall is visible

        gotoRowCol(r, c);
        print_a_circle(r, c, 1,' ');



    }



}

void Floor()
{
    color(10);
    print_a_line(35, 26, 35, 77, -37, 0.01);
    color(15);
}

void Newton(int x,int y)
{
   //    \O/
   //     0
   //    / \
  
    gotoRowCol(x, y);
    cout << '0';

    gotoRowCol(x + 1, y + 1);
    cout << '\\';

    gotoRowCol(x + 1, y - 1);
    cout << '/';

    gotoRowCol(x - 1, y);
    cout << 'O';

    gotoRowCol(x - 1, y - 1);
    cout << '\\';

    gotoRowCol(x - 1, y + 1);
    cout << '/';
}

void Rip(int x, int y)
{   
     //           o-<
    
    gotoRowCol(x, y);
    cout << '-';

    gotoRowCol(x, --y);
    cout << 'o';

    gotoRowCol(x, ++y);
    cout << '<';



}

void clear(int x,int y)
{
    //    \O/
    //     |
    //    / \
  
    gotoRowCol(x, y);
    cout << ' ';

    gotoRowCol(x+1, y+1);
    cout << ' ';

    gotoRowCol(x + 1, y - 1);
    cout << ' ';

    gotoRowCol(x - 1, y);
    cout << ' ';

   
    gotoRowCol(x - 1, y-1);
    cout << ' ';

    gotoRowCol(x - 1, y + 1);
    cout << ' ';



}
// 40 x 120

int main()
{
    int Rows = 40, Cols = 120;

    
   Building();
   Tree();
   Floor();

   int x = 32, y = 56;
 
   while (true)
   {
     

       if (_kbhit())
       {
    
           char ch = _getch();
           if (ch == 'A' || ch == 'a')
           {
               clear(x, y);
               Newton(x, --y);
           }
           if (ch == 'D' || ch == 'd')
           {
               clear(x, y);
               Newton(x, ++y);
           }

      //     cout << x<<" "<<y;
           if (x == 32 && y == 76)
           {
               apple_falling(17, 76, 0);
               clear(x,y);
               Rip(x, y);
               break;
           }


       }
   }
  // 35 25 -->  35 78  green

  
  
    _getch();

    


	return 0;
}