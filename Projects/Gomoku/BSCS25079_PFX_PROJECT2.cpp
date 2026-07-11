#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <thread>

using namespace std;

// Portable "clear screen" (cls on Windows, clear on Linux/macOS).
void clr() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Pause execution for the given number of milliseconds (for animation).
void wait_ms(int ms) { this_thread::sleep_for(chrono::milliseconds(ms)); }

// ----------------------   #define  --------------------------

#define MAXROW 100
#define MAXCOLS 100

// ----------------------   GLOBAL   --------------------------

char _Board[MAXROW][MAXCOLS] = {};
const int capacity = 3;
char Psym[capacity] = {};
char PNames[capacity][MAXCOLS] = {};
int NOP = 0;
int turn = 0;
int winC = 0;
int R = 0, C = 0;

int temp_r = 0, temp_c = 0;
int off = 0;

// Coordinates of the most recently placed piece (-1 = none yet).
// Used to highlight/animate the last move in Board_display().
int last_r = -1, last_c = -1;
// -------------------   HELPING FUNCTIONS   ---------------------------

void assign_names_and_symbols();
void intialise_board();
void toss();
void turn_change();

//---------------------- NECESSARY FUNCTIONS --------------------------
void init();
void Board_display();
bool valid(int _r, int _c);
void Update(int _r, int _c);
void input(int &r, int &c);

//----------------------      Validation    ---------------------------

bool input_validation(char ch);

bool vertical(int r, int c, char _Psym, int _winC);
bool horizontal(int r, int c, char _Psym, int _winC);
bool diagonal_anti(int r, int c, char _Psym, int _winC);
bool diagonal_main(int r, int c, char _Psym, int _winC);
bool win(int r, int c, char Playersym, int winc);
bool draw();

//----------------------        ROBOT         ---------------------------

void R_init();
bool is_human_winng(int &r, int &c);
bool is_computer_winning(int &r, int &c);
void random(int &r, int &c);

void random(int &r, int &c) {
  do {
    r = rand() % R;
    c = rand() % C;
  } while (!valid(r, c));
}

// Returns true if placing 'sym' at some empty cell completes a line of 'winC'.
// The cell is temporarily filled so win() sees the bead, then restored.
bool can_win_at(char sym, int &r, int &c) {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      if (valid(i, j)) {
        _Board[i][j] = sym;
        bool wins = win(i, j, sym, winC);
        _Board[i][j] = '.';
        if (wins) {
          r = i, c = j;
          return true;
        }
      }

  return false;
}

bool is_computer_winning(int &r, int &c) { return can_win_at('A', r, c); }

bool is_human_winng(int &r, int &c) { return can_win_at(Psym[0], r, c); }

void Annie_move(int &r, int &c) {
  if (is_human_winng(r, c))
    ;
  else if (is_computer_winning(r, c))
    ;
  else
    random(r, c);
}

//<=====================        MODES         ==========================>

void HumanVsHuman();
void HumanVsRobot();

// <====================         MAIN         ==========================>
int main() {
  srand((unsigned)time(0));
  int choice = 0;
  do {
    cout << "\n<-------------------------------------------->" << endl;
    cout << "\n<-------------      MENU     ---------------->" << endl;
    cout << "\n<-------------------------------------------->" << endl;
    cout << "1. Human vs Robot (AI)" << endl;
    cout << "2. Human vs Human" << endl;
    cout << "3. Exit" << endl;
    cout << "\n<-------------------------------------------->" << endl;

    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      clr();
      HumanVsRobot();
      break;
    case 2:
      clr();
      HumanVsHuman();
      break;
    case 3:
      cout << "Exiting!" << endl;
      break;
    default:
      cout << "Invalid choice!" << endl;
    }

  } while (choice != 3);

  return 0;
}

void HumanVsRobot() {
  int r, c;
  bool game_won = 0;
  R_init();
  do {
    clr();
    Board_display();

    bool flag = false;
    if (turn == 1) {
      do {
        input(r, c);
        flag = valid(r, c);

        if (!flag) {
          clr();
          Board_display();
          cout << "Error: Enter Correct Coordinates" << endl;
        }

      } while (!flag);
    } else {
      cout << "\n" << PNames[turn - 1] << " is thinking";
      for (int d = 0; d < 3; d++) {
        cout << "." << flush;
        wait_ms(350);
      }
      Annie_move(r, c);
    }

    Update(r, c);

    // Animation: redraw the board with the new piece highlighted (>X<)
    // and pause so the player can see which move was just made.
    clr();
    Board_display();
    wait_ms(700);

    if (win(r, c, Psym[turn - 1], winC)) {
      cout << "Winner: " << PNames[turn - 1];
      game_won = true;
    } else
      turn_change();

  } while (!draw() && !game_won);

  cout << "\nEnter Any key to continue! " << endl;
  cin.ignore();
  cin.get();
}
void HumanVsHuman() {
  int r, c;
  bool game_won = 0;
  init();
  do {
    clr();
    Board_display();

    bool flag = false;

    do {
      input(r, c);
      flag = valid(r, c);

      if (!flag) {
        clr();
        Board_display();
        cout << "Error: Enter Correct Coordinates" << endl;
      }

    } while (!flag);

    Update(r, c);

    // Animation: redraw the board with the new piece highlighted (>X<)
    // and pause so players can see which move was just made.
    clr();
    Board_display();
    wait_ms(700);

    if (win(r, c, Psym[turn - 1], winC)) {
      cout << "Winner: " << PNames[turn - 1];
      game_won = true;
    } else
      turn_change();

  } while (!draw() && !game_won);

  cout << "Enter Any key to continue! " << endl;
  cin.ignore();
  cin.get();
}

void input(int &r, int &c) {

  cout << "Enter ( row , col ): ";
  cin >> r >> c;
}

void init() {
  do {
    cout << "\nEnter How many Playes are Playing Max (3): ";
    cin >> NOP;
  } while (NOP < 2 || NOP > capacity);

  assign_names_and_symbols();

  cout << "\nEnter Win Count For Beads: ";
  cin >> winC;

  cout << "\nEnter the Dimensions Rows / Cols :  ";
  cin >> R >> C;

  intialise_board();
  toss();
  clr();
}

void assign_names_and_symbols() {
  cout << "Assigning Names and Symbols" << endl;

  for (int i = 1; i <= NOP; i++) {
    clr();
    cout << " Player no: " << i << endl;
    cout << "Enter name Max(50 ch): ";
    cin.ignore();
    cin.getline(PNames[i - 1], 50);

    cout << "Enter symbol: ";
    cin >> Psym[i - 1];
    clr();
  }
}

void intialise_board() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      _Board[i][j] = '.';
}

void Board_display() {
  cout << "               Player: " << turn << " Turn" << endl;
  cout << "               Name: " << PNames[turn - 1] << " ( " << Psym[turn - 1]
       << " )" << endl;
  cout << endl;
  cout << endl;

  char sym = -37;

  for (int i = 0; i < C * 4 + 1; i++)
    cout << sym;
  cout << endl;

  for (int i = 0; i < C * 4 + 1; i++)
    cout << '-';
  cout << endl;

  for (int i = 0; i < R; i++) {
    cout << '|';
    for (int j = 0; j < C; j++) {
      // Highlight the most recently placed piece as >X< so the move stands out.
      if (i == last_r && j == last_c)
        cout << ">" << _Board[i][j] << "<" << '|';
      else
        cout << " " << _Board[i][j] << " " << '|';
    }
    cout << endl;
    for (int i = 0; i < C * 4 + 1; i++)
      cout << '-';
    cout << endl;
  }

  for (int i = 0; i < C * 4 + 1; i++)
    cout << sym;
  cout << endl;
}

void toss() { turn = (rand() % NOP) + 1; }

void turn_change() { turn = (turn % NOP) + 1; }

bool valid(int _r, int _c) {
  return _r >= 0 and _r < R and _c >= 0 and _c < C and _Board[_r][_c] == '.';
}

void Update(int _r, int _c) {
  _Board[_r][_c] = Psym[turn - 1];
  last_r = _r; // remember this move so it can be highlighted
  last_c = _c;
}

//----------------------        ROBOT         ---------------------------

void R_init() {
  NOP = 2;

  cout << "Enter name Max(50 ch): ";
  cin.ignore();
  cin.getline(PNames[0], 50);

  cout << "Enter symbol: ";
  cin >> Psym[0];
  clr();

  char arr[] = "Annie";
  int size = 0;
  for (size = 0; arr[size++] != '\0';)
    ;

  for (int i = 0; i < size; i++)
    PNames[1][i] = arr[i];

  Psym[1] = 'A';

  cout << "\nEnter Win Count For Beads: ";
  cin >> winC;

  cout << "\nEnter the Dimensions Rows / Cols :  ";
  cin >> R >> C;

  intialise_board();
  toss();
  clr();
}

//----------------------      Validation    ---------------------------

bool input_validation(char ch) { return ch <= '9' and ch >= '0'; }

bool win(int r, int c, char Playersym, int winc) {
  return vertical(r, c, Playersym, winc) || horizontal(r, c, Playersym, winc) ||
         diagonal_main(r, c, Playersym, winc) ||
         diagonal_anti(r, c, Playersym, winc);
}

bool draw() {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      if (_Board[i][j] == '.')
        return false;

  return true;
}

bool vertical(int r, int c, char _Psym, int _winC) {
  int count = 0;

  for (int i = r; i >= 0; i--) {
    if (_Board[i][c] != _Psym)
      break;
    count++;
  }

  for (int i = r + 1; i < R; i++) {
    if (_Board[i][c] != _Psym)
      break;
    count++;
  }

  return count >= _winC;
}

bool horizontal(int r, int c, char _Psym, int _winC) {
  int count = 0;

  for (int i = c; i >= 0; i--) {
    if (_Board[r][i] != _Psym)
      break;
    count++;
  }

  for (int i = c + 1; i < C; i++) {
    if (_Board[r][i] != _Psym)
      break;
    count++;
  }

  return count >= _winC;
}

bool diagonal_main(int r, int c, char _Psym, int _winC) {
  int count = 0;

  for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
    if (_Board[i][j] != _Psym)
      break;
    count++;
  }

  for (int i = r + 1, j = c + 1; i < R && j < C; i++, j++) {
    if (_Board[i][j] != _Psym)
      break;
    count++;
  }

  return count >= _winC;
}

bool diagonal_anti(int r, int c, char _Psym, int _winC) {
  int count = 0;

  for (int i = r, j = c; i >= 0 && j < C; i--, j++) {
    if (_Board[i][j] != _Psym)
      break;
    count++;
  }

  for (int i = r + 1, j = c - 1; i < R && j >= 0; i++, j--) {
    if (_Board[i][j] != _Psym)
      break;
    count++;
  }

  return count >= _winC;
}
