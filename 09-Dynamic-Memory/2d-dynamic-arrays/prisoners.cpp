#include <fstream>
#include <iostream>
using namespace std;

int _r, _c;

int **loadInt(const char *fname) {
  ifstream f(fname);
  int r, c;
  f >> r >> c;
  _r = r;
  _c = c;
  int **arr = new int *[r]{};
  for (int i = 0; i < r; i++) {
    arr[i] = new int[c]{};
    for (int j = 0; j < c; j++)
      f >> arr[i][j];
  }
  f.close();
  return arr;
}

char **loadChars(const char *fname) {
  ifstream f(fname);
  int r, c;
  f >> r >> c;
  _r = r;
  _c = c;
  char **grid = new char *[r]{};
  for (int i = 0; i < r; i++) {
    grid[i] = new char[c + 1]{};
    for (int j = 0; j < c; j++)
      f >> grid[i][j];
  }
  f.close();
  return grid;
}

char **loadWords(int &wc) {
  ifstream f("words.txt");
  f >> wc;
  char **words = new char *[wc]{};
  for (int i = 0; i < wc; i++) {
    words[i] = new char[50]{};
    f >> words[i];
  }
  f.close();
  return words;
}

// ─── Problem 01 : Uniform Convolution ───────────────────────────────────────

void problem01() {
  int **arr = loadInt("matrix.txt");

  int pr = _r + 2, pc = _c + 2;
  int **pad = new int *[pr]{};
  for (int i = 0; i < pr; i++)
    pad[i] = new int[pc]{};

  for (int i = 0; i < _r; i++)
    for (int j = 0; j < _c; j++)
      pad[i + 1][j + 1] = arr[i][j];

  cout << "Original:" << endl;
  for (int i = 0; i < _r; i++) {
    for (int j = 0; j < _c; j++)
      cout << arr[i][j] << " ";
    cout << endl;
  }

  int **result = new int *[_r]{};
  for (int i = 0; i < _r; i++)
    result[i] = new int[_c]{};

  for (int i = 0; i < _r; i++)
    for (int j = 0; j < _c; j++) {
      int sum = 0;
      for (int ki = 0; ki < 3; ki++)
        for (int kj = 0; kj < 3; kj++)
          sum += pad[i + ki][j + kj];
      result[i][j] = sum / 9;
    }

  cout << "Convolution Result:" << endl;
  for (int i = 0; i < _r; i++) {
    for (int j = 0; j < _c; j++)
      cout << result[i][j] << " ";
    cout << endl;
  }
}

// ─── Problem 02 : Word Search ────────────────────────────────────────────────

int strLen(const char *s) {
  int len = 0;
  while (s[len])
    len++;
  return len;
}

bool searchDir(char **grid, int ri, int ci, int dr, int dc, const char *word,
               int wlen) {
  for (int k = 0; k < wlen; k++) {
    int nr = ri + k * dr;
    int nc = ci + k * dc;
    if (nr < 0 || nr >= _r || nc < 0 || nc >= _c)
      return false;
    if (grid[nr][nc] != word[k])
      return false;
  }
  return true;
}

void problem02() {
  char **puzzle = loadChars("puzzle.txt");
  int wc;
  char **words = loadWords(wc);

  int dirs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                    {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  cout << "Puzzle:" << endl;
  for (int i = 0; i < _r; i++) {
    for (int j = 0; j < _c; j++)
      cout << puzzle[i][j] << " ";
    cout << endl;
  }
  cout << endl;

  for (int w = 0; w < wc; w++) {
    int wlen = strLen(words[w]);
    bool found = false;
    for (int i = 0; i < _r && !found; i++)
      for (int j = 0; j < _c && !found; j++)
        for (int d = 0; d < 8 && !found; d++)
          if (searchDir(puzzle, i, j, dirs[d][0], dirs[d][1], words[w], wlen)) {
            cout << words[w] << " -> (" << i << ", " << j << ")" << endl;
            found = true;
          }
    if (!found)
      cout << words[w] << " not found" << endl;
  }
}

// ─── Problem 03 : Prisoner Escape ────────────────────────────────────────────

int _path_r[1000], _path_c[1000], _plen;

bool **makeBoolGrid() {
  bool **vis = new bool *[_r]{};
  for (int i = 0; i < _r; i++)
    vis[i] = new bool[_c]{};
  return vis;
}

// Variant 01 : reach specific destination (dr, dc)
bool dfs1(int **grid, bool **vis, int cr, int cc, int dr, int dc) {
  if (cr < 0 || cr >= _r || cc < 0 || cc >= _c)
    return false;
  if (grid[cr][cc] == 1 || vis[cr][cc])
    return false;

  vis[cr][cc] = true;
  _path_r[_plen] = cr;
  _path_c[_plen] = cc;
  _plen++;

  if (cr == dr && cc == dc)
    return true;

  int drs[] = {-1, 1, 0, 0};
  int dcs[] = {0, 0, -1, 1};
  for (int d = 0; d < 4; d++)
    if (dfs1(grid, vis, cr + drs[d], cc + dcs[d], dr, dc))
      return true;

  vis[cr][cc] = false;
  _plen--;
  return false;
}

// Variant 02 : reach any open boundary cell (hole)
bool dfs2(int **grid, bool **vis, int cr, int cc) {
  if (cr < 0 || cr >= _r || cc < 0 || cc >= _c)
    return false;
  if (grid[cr][cc] == 1 || vis[cr][cc])
    return false;

  vis[cr][cc] = true;
  _path_r[_plen] = cr;
  _path_c[_plen] = cc;
  _plen++;

  if (cr == 0 || cr == _r - 1 || cc == 0 || cc == _c - 1)
    return true;

  int drs[] = {-1, 1, 0, 0};
  int dcs[] = {0, 0, -1, 1};
  for (int d = 0; d < 4; d++)
    if (dfs2(grid, vis, cr + drs[d], cc + dcs[d]))
      return true;

  vis[cr][cc] = false;
  _plen--;
  return false;
}

void printPath() {
  for (int i = 0; i < _plen; i++)
    cout << "(" << _path_r[i] << "," << _path_c[i] << ")";
  cout << endl;
}

void problem03() {
  // hardcoded positions — change to match your grid file
  int sr1 = 1, sc1 = 1, dr = 4, dc = 4;
  int sr2 = 2, sc2 = 2;

  cout << "Variant 01 : Reach destination (" << dr << "," << dc << ")" << endl;
  {
    int **grid = loadInt("grid.txt");
    bool **vis = makeBoolGrid();
    _plen = 0;

    if (dfs1(grid, vis, sr1, sc1, dr, dc)) {
      cout << "Escaped! Path: ";
      printPath();
    } else
      cout << "No path to destination." << endl;
  }

  cout << "\nVariant 02 : Reach any boundary hole" << endl;
  {
    int **grid = loadInt("grid.txt");
    bool **vis = makeBoolGrid();
    _plen = 0;

    if (dfs2(grid, vis, sr2, sc2)) {
      cout << "Escaped! Path: ";
      printPath();
    } else
      cout << "Cannot escape." << endl;
  }
}

// ─── Main Menu ───────────────────────────────────────────────────────────────

int main() {
  int choice;
  do {
    cout << "\n--- Lab 10 Menu ---" << endl;
    cout << "1. Uniform Convolution" << endl;
    cout << "2. Word Search" << endl;
    cout << "3. Prisoner Escape" << endl;
    cout << "0. Exit" << endl;
    cout << "Choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      problem01();
      break;
    case 2:
      problem02();
      break;
    case 3:
      problem03();
      break;
    case 0:
      break;
    default:
      cout << "Invalid choice." << endl;
    }
  } while (choice != 0);

  return 0;
}
