#include <conio.h>
#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

void getRowColbyLeftClick(int &rpos, int &cpos);
void color(int k);
void hideConsoleCursor();
void gotoRowCol(int rpos, int cpos);
void Print_a_line(int x1, int y1, int x2, int y2, char ch = -37,
                  float delta = 0.01) {
  for (float alpha = 0; alpha <= 1; alpha += delta) {
    int r = x1 * alpha + x2 * (1 - alpha);
    int c = y1 * alpha + y2 * (1 - alpha);

    if (x1 == x2)
      r = x1;
    if (y1 == y2)
      c = y1;
    gotoRowCol(r, c);
    cout << ch;
  }
}

void Rectangle(int Color);
void select_color(const int rows, const int cols, int &Color);

void Task1() {
  Rectangle(4);

  Rectangle(3);

  Rectangle(1);

  Rectangle(5);

  Rectangle(10);

  Rectangle(12);

  Rectangle(11);

  char sym = -37;
  cout << sym;
  int Color = 0;
  int rows = 0, col = 0;
  while (true) {

    getRowColbyLeftClick(rows, col);
    gotoRowCol(rows, col);
    select_color(rows, col, Color);
    color(Color);
    cout << sym;
  }
}

void Task2() {
  int width = 120, height = 30;
  int row, cols;
  float delta = 0.5;
  while (true) {
    Print_a_line(0, 0, 0, 119, -37, 0.001);
    Print_a_line(0, 0, height - 1, width - 1, -37, 0.001);
    Print_a_line(0, 119, 29, 0, -37, 0.001);
    Print_a_line(29, 0, 29, 119, -37, 0.001);

    Sleep(500 * delta);
    system("cls");

    Print_a_line(0, 0, 29, 0, -37, 0.001);
    Print_a_line(0, 0, height - 1, width - 1, -37, 0.001);
    Print_a_line(0, 119, 29, 0, -37, 0.001);
    Print_a_line(0, 119, 29, 119, -37, 0.001);
    Sleep(500 * delta);
    system("cls");
  }
}

void Task3() {
  // Base

  Print_a_line(25, 0, 25, 119, -37, 0.001);
  // Top
  Print_a_line(7, 10, 7, 110, -37, 0.001);

  // left most
  Print_a_line(25, 10, 7, 10, -37, 0.001);
  // left Minaret
  Print_a_line(25, 20, 7, 20, -37, 0.001);
  Print_a_line(25, 30, 7, 30, -37, 0.001);

  // rightside

  // rightmost
  Print_a_line(7, 111, 25, 111, -37, 0.001);
  // right Minaret
  Print_a_line(25, 100, 7, 100, -37, 0.001);
  Print_a_line(25, 90, 7, 90, -37, 0.001);

  // Centre Top

  Print_a_line(25, 40, 2, 40, -37, 0.001);
  Print_a_line(25, 80, 2, 80, -37, 0.001);
  Print_a_line(2, 40, 2, 80, -37, 0.001);

  // Centre

  Print_a_line(25, 50, 10, 50, -37, 0.001);
  Print_a_line(25, 70, 10, 70, -37, 0.001);
  Print_a_line(10, 50, 10, 70, -37, 0.001);

  // Door
  Print_a_line(25, 55, 15, 55, -37, 0.001);
  Print_a_line(25, 65, 15, 65, -37, 0.001);
  Print_a_line(15, 55, 15, 65, -37, 0.001);

  // ITU
  Print_a_line(7, 41, 7, 79, ' ', 0.001);

  // Text
  // Print_a_line(4, 52, 4, 54, -37, 0.001);
  // Print_a_line(4, 53, 6, 53, -37, 0.001);
  // Print_a_line(6, 52, 6, 54, -37, 0.001);

  // Print_a_line(4, 56, 4, 58, -37, 0.001);
  // Print_a_line(4, 57, 6, 57, -37, 0.001);

  // Print_a_line(4, 60, 6, 60, -37, 0.001);
  // Print_a_line(6, 60, 6, 62, -37, 0.001);
  // Print_a_line(6, 62, 4, 62, -37, 0.001);

  _getch();
}

void system_clear() {
#ifndef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

int main() {
  int Choice = 0;

  do {
    cout << "\n1.Paint" << endl;
    cout << "2.Fan" << endl;
    cout << "3.Barqi in Progress" << endl;
    cout << "4. Exiting" << endl;
    cout << "Enter Choice: ";
    cin >> Choice;

    system_clear();

    switch (Choice) {
    case 1:
      Task1();
      break;
    case 2:
      Task2();
      break;
    case 3:
      Task3();
      break;
    case 4:
      cout << " Exiting!!!" << endl;
      break;
    default:
      cout << "Enter Valid Choice" << endl;
      break;
    }

  } while (Choice != 4);

  return 0;
}

void getRowColbyLeftClick(int &rpos, int &cpos) {
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  DWORD Events;
  INPUT_RECORD InputRecord;
  SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
                             ENABLE_EXTENDED_FLAGS);
  do {
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

void color(int k) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, k);
}

void hideConsoleCursor() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(hConsole, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void gotoRowCol(int rpos, int cpos) {
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = cpos;
  scrn.Y = rpos;
  SetConsoleCursorPosition(hOuput, scrn);
}

void Rectangle(int Color) {
  char sym = -37;
  for (int i = 0; i < 3; i++) {
    for (int j = 1; j <= 5; j++) {
      color(Color);
      cout << sym;
    }
    color(0);
    cout << endl;
  }
}

void select_color(const int rows, const int cols, int &Color) {

  if (rows >= 0 and rows <= 2 and cols >= 0 and cols <= 5)
    Color = 4;
  if (rows >= 3 and rows <= 5 and cols >= 0 and cols <= 5)
    Color = 3;
  if (rows >= 6 and rows <= 8 and cols >= 0 and cols <= 5)
    Color = 1;
  if (rows >= 9 and rows <= 11 and cols >= 0 and cols <= 5)
    Color = 5;
  if (rows >= 12 and rows <= 14 and cols >= 0 and cols <= 5)
    Color = 10;
  if (rows >= 15 and rows <= 17 and cols >= 0 and cols <= 5)
    Color = 12;
  if (rows >= 18 and rows <= 20 and cols >= 0 and cols <= 5)
    Color = 11;
}
