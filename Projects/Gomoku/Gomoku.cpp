#include <fstream>
#include <iostream>
#include <windows.h>

#include <conio.h>
#include <math.h>

using namespace std;

void gotoRowCol(int rpos, int cpos) {
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = cpos;
  scrn.Y = rpos;
  SetConsoleCursorPosition(hOuput, scrn);
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

void printaline(int r1, int c1, int r2, int c2, char sym = -37,
                float def = 0.1) {

  for (float i = 0; i <= 1; i = i + def) {
    int x = r1 + (r2 - r1) * i;
    int y = c1 + (c2 - c1) * i;
    gotoRowCol(x, y);
    cout << sym;
  }
}

void print_rectangle(int sr, int sc) {
  printaline(sr, sc, sr, sc + 10);
  printaline(sr, sc, sr + 4, sc);
  printaline(sr, sc + 10, sr + 4, sc + 10);
  printaline(sr + 4, sc, sr + 4, sc + 10);
}

void convert(int num, int &cri, int &cci) {
  num = num - 1;

  int Row = num / 10;
  int Col = num % 10;

  cri = 9 - Row;

  if (Row % 2 == 0) {
    cci = Col;
  }

  else {
    cci = 9 - Col;
  }
}

void printnumber() {

  int i = 0;
  int j = 0;

  for (int num = 1; num <= 100; num++) {
    convert(num, i, j);
    gotoRowCol(i * 4 + 2, j * 10 + 4);
    cout << num;
  }
}

void printgrid() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      print_rectangle(i * 4, j * 10);
    }
  }

  printnumber();
}

void load(ifstream &read, int **&ptr, int &rows) {

  read >> rows;
  ptr = new int *[rows];

  for (int i = 0; i < rows; i++) {
    ptr[i] = new int[2];
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 2; j++) {
      read >> ptr[i][j];
    }
  }
}

void printarr(int **ptr, int rows, int cols) {

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << ptr[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
}

void init(char **&name, char *&sym, int *&turn) {

  name = new char *[2];
  sym = new char[2];
  turn = new int[2];

  for (int i = 0; i < 2; i++) {
    name[i] = new char[30];
    cout << "Player " << i + 1 << " Enter Your Name : ";
    cin.getline(name[i], 30);
    cout << "Player " << i + 1 << " Enter Your  Symbol : ";
    cin >> sym[i];
    cin.ignore();
  }

  turn[0] = rand() % 2;

  if (turn[0] == 0) {
    turn[1] = 1;
  } else {
    turn[1] = 0;
  }
}

void printdice(int sc, int sr) {

  printaline(0.30 * sr, sc * 0.70, 0.30 * sr, 0.75 * sc);
  printaline(0.30 * sr, sc * 0.70, 0.40 * sr, 0.70 * sc);

  printaline(0.30 * sr, sc * 0.75, 0.41 * sr, 0.75 * sc);
  printaline(0.40 * sr, sc * 0.70, 0.40 * sr, 0.75 * sc);
}

void rollturn(char *name, int &movesum, int &current) {

  int sc = 234;
  int sr = 61;
  int dice = 0;
  movesum = 0;
  int sixcount = 0;

  while (true) {

    gotoRowCol(0.25 * sr, sc * 0.65);
    cout << name << " Press Any Key When you are ready!";

    while (true) {

      if (_kbhit()) {
        _getch();
        break;
      }
      Sleep(50);
    }

    printdice(sc, sr);

    while (true) {
      if (!_kbhit()) {
        dice = rand() % 6 + 1;
        gotoRowCol(0.35 * sr, sc * 0.73);
        cout << dice;

      }

      else {
        _getch();

        gotoRowCol(0.35 * sr, sc * 0.73);
        cout << dice;
        if (dice == 6) {
          sixcount++;
        }
        movesum = movesum + dice;
        break;
      }
      Sleep(100);
    }

    if (sixcount == 3) {
      movesum = 0;
      break;
    }
    if (dice != 6) {
      break;
    }
  }

  gotoRowCol(0.45 * sr, sc * 0.70);
  cout << name << " Rolled : " << dice;
  gotoRowCol(0.46 * sr, sc * 0.70);
  cout << name << " MoveSum: " << movesum;

  current = current + movesum;
}

bool laddercheck(int **ladder, int nol, int &currentpos) {

  for (int i = 0; i < nol; i++) {

    if (currentpos == ladder[i][0]) {

      currentpos = ladder[i][1];
      return true;
      ;
    }
  }

  return false;
}

bool snakecheck(int **snake, int nos, int &currentpos) {

  for (int i = 0; i < nos; i++) {

    if (currentpos == snake[i][0]) {

      currentpos = snake[i][1];
      return true;
      ;
    }
  }

  return false;
}

bool wincheck(int currentpos) {

  if (currentpos >= 100) {

    return true;
  }

  return false;
}

int main() {

  srand(time(0));
  int sc = 234;
  int sr = 61;

  int **snake = nullptr;
  int **ladder = nullptr;
  char **name = nullptr;
  char *sym = nullptr;
  int *turn = nullptr;
  int nos = 0;
  int nol = 0;

  int c1 = 0;
  int c2 = 0;

  int pr1 = 0;
  int pc1 = 0;

  int pr2 = 0;
  int pc2 = 0;

  ifstream read("board.txt");
  load(read, snake, nos);
  load(read, ladder, nol);
  init(name, sym, turn);
  system("cls");
  printgrid();

  int i = 0;

  while (true) {

    if (i == 0) {
      int movesum = 0;
      int br = 0, bc = 0;

      int old_r = pr1;
      int old_c = pc1;

      rollturn(name[turn[i]], movesum, c1);
      convert(c1, br, bc);

      if (c1 != 0) {
        gotoRowCol(old_r * 4 + 1, old_c * 10 + 3);
        cout << " ";
      }

      if (laddercheck(ladder, nol, c1)) {
        convert(c1, br, bc);
        gotoRowCol(br * 4 + 1, bc * 10 + 3);
        color(2);
        cout << sym[turn[i]];
        color(7);

      }

      else if (snakecheck(snake, nos, c1)) {
        convert(c1, br, bc);
        gotoRowCol(br * 4 + 1, bc * 10 + 3);
        color(2);
        cout << sym[turn[i]];
        color(7);
      } else {
        gotoRowCol(br * 4 + 1, bc * 10 + 3);
        color(2);
        cout << sym[turn[i]];
        color(7);
      }

      if (wincheck(c1)) {

        gotoRowCol(0.75 * sr, sc * 0.65);
        color(2);
        cout << " === " << name[turn[i]] << " Wins" << " === ";
        color(7);
        exit(0);
      }

      pr1 = br;
      pc1 = bc;
    } else if (i == 1) {
      int movesum = 0;
      int br = 0, bc = 0;

      int old_r = pr2;
      int old_c = pc2;

      rollturn(name[turn[i]], movesum, c2);
      convert(c2, br, bc);

      if (c2 != 0) {
        gotoRowCol(old_r * 4 + 1, old_c * 10 + 5);
        cout << " ";
      }

      if (laddercheck(ladder, nol, c2)) {
        convert(c2, br, bc);
        gotoRowCol(br * 4 + 1, bc * 10 + 5);
        color(4);
        cout << sym[turn[i]];
        color(7);

      }

      else if (snakecheck(snake, nos, c2)) {
        convert(c2, br, bc);
        gotoRowCol(br * 4 + 1, bc * 10 + 5);
        color(4);
        cout << sym[turn[i]];
        color(7);
      } else {
        gotoRowCol(br * 4 + 1, bc * 10 + 5);
        color(4);
        cout << sym[turn[i]];
        color(7);
      }

      if (wincheck(c2)) {

        gotoRowCol(0.75 * sr, sc * 0.65);
        color(4);
        cout << " === " << name[turn[i]] << " Wins" << " === ";
        color(7);
        exit(0);
      }
      pr2 = br;
      pc2 = bc;
    }

    /// turn change

    if (i == 1) {
      i = 0;
    } else {
      i = 1;
    }
  }

  _getch();

  return 0;
}
