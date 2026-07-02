#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;
const int ROWS = 8;
const int COLS = 8;
int turn = 0;
const int MAX_MOVES = 125;
char Board[MAX_MOVES][ROWS][COLS];
int check = 0;
bool white_king_moved = false;
bool black_king_moved = false;
bool white_left_rook_moved = false;
bool white_right_rook_moved = false;
bool black_left_rook_moved = false;
bool black_right_rook_moved = false;

void save_game()
{
	ofstream put("saved_game_chess.txt");
	int k = 0;
	int j = 0;
	put << turn << endl;
	for (k = 0; k < ROWS; k++)
	{
		for (j = 0; j < COLS; j++)
		{
			put << Board[turn][k][j] << " ";
		}
		put << endl;
	}
	cout << "Game Saved Successfully" << endl;
	put.close();
}

void copy_board(int from, int to)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			Board[to][i][j] = Board[from][i][j];
		}
	}
}

void read_save()
{

	ifstream grab("saved_game_chess.txt");
	char che = '0';
	int k = 0;
	int j = 0;
	bool zap = 0;
	grab >> turn;
	for (k = 0; k < ROWS; k++)
	{
		for (j = 0; j < 8; j++)
		{
			grab >> che;
			Board[turn][k][j] = che;
		}
	}
	grab.close();
}

void intialize_board()
{
	ifstream pull("original_cess.txt");
	char che = '0';
	int k = 0;
	int j = 0;
	bool zap = 0;
	for (k = 0; k < ROWS; k++)
	{
		for (j = 0; j < 8; j++)
		{
			for (j = 0; j < 8; j++)
			{
				pull >> che;
				Board[turn][k][j] = che;
			}
		}
	}
	pull.close();
}

void Display_board()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "          <=== Welcome To Chess ===>";

	cout << endl;
	cout << "              1  2  3  4  5  6  7  8" << endl;
	for (int i = 0; i < ROWS; i++)
	{

		cout << "           " << i + 1 << "  ";
		for (int k = 0; k < COLS; k++)
		{
			if (Board[turn][i][k] >= 'a' && Board[turn][i][k] <= 'z')
			{
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (Board[turn][i][k] >= 'A' && Board[turn][i][k] <= 'Z')
			{
				SetConsoleTextAttribute(hConsole, 8);
			}

			cout << Board[turn][i][k] << "  ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}
	cout << "              1  2  3  4  5  6  7  8" << endl;
}

void display_board_()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "          <=== Welcome To Chess ===>";
	cout << endl << "         <=== (The Game Of Kings) ===>";
	cout << endl << "         The Project Of \"Tehseen Ahmad\" ";
	cout << endl;
	cout << "              1  2  3  4  5  6  7  8" << endl;
	for (int i = 0; i < ROWS; i++)
	{

		cout << "           " << i + 1 << "  ";
		for (int k = 0; k < COLS; k++)
		{
			if (Board[turn - 1][i][k] >= 'a' && Board[turn - 1][i][k] <= 'z')
			{
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if (Board[turn - 1][i][k] >= 'A' && Board[turn - 1][i][k] <= 'Z')
			{
				SetConsoleTextAttribute(hConsole, 8);
			}

			cout << Board[turn - 1][i][k] << "  ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}
	cout << "              1  2  3  4  5  6  7  8" << endl;
}

int check_source(int sr, int sc)
{
	if (sr < 0 || sc < 0)
	{
		cout << "Outside Bound" << endl;
		return -1;
	}
	else if (sr > 7 || sc > 7)
	{
		cout << "Way Outside Bound" << endl;
		return -1;
	}
	else if (Board[turn][sr][sc] == '.')
	{
		cout << "Empty Space Not Allowed." << endl;
		return -1;
	}
	if ((turn % 2) == 0)
	{
		if ((Board[turn][sr][sc] > 'z' || Board[turn][sr][sc] < 'a'))
		{
			cout << "Wrong Piece!" << endl;
			return -1;
		}
	}
	else if ((turn % 2) != 0)
	{
		if ((Board[turn][sr][sc] > 'Z' || Board[turn][sr][sc] < 'A'))
		{
			cout << "Wrong Piece" << endl;
			return -1;
		}
	}
	return 1;
}

int check_dest(int dc, int dr)
{
	if (dr < 0 || dc < 0)
	{

		return -1;
	}
	else if (dr > 7 || dc > 7)
	{

		return -1;
	}
	if (turn % 2 == 0)
	{
		if (Board[turn][dr][dc] > 'a' && Board[turn][dr][dc] < 'z')
		{

			return -1;
		}
	}
	else if (turn % 2 != 0)
	{
		if (Board[turn][dr][dc] > 'A' && Board[turn][dr][dc] < 'Z')
		{

			return -1;
		}
	}

	return 1;
}

int check_pawn(int sr, int sc, int dc, int dr)
{
	if (Board[turn][sr][sc] == 'p')
	{
		
		if (sr == 6 && dc == sc && dr == sr - 2 && Board[turn][sr - 1][sc] == '.' )

		{
			return 1;
		}
		if (sr == 6 && dc == sc && dr == sr - 3 && Board[turn][sr - 1][sc] == '.'  && Board[turn][sr - 2][sc] == '.')

		{
			return 1;
		}
		if (dc == sc && dr == sr - 1)
		{
			return 1;
		}
		if ((dc == sc + 1 || dc == sc - 1) && dr == sr - 1 && Board[turn][dr][dc] >= 'A' && Board[turn][dr][dc] <= 'Z')
		{
			return 1;
		}
	}
	else if (Board[turn][sr][sc] == 'P')
	{
		if (sr == 1 && dc == sc && dr == sr + 3 && Board[turn][sr + 1][sc] == '.' && Board[turn][sr + 2][sc] == '.')

		{
			return 1;
		}
		if (sr == 1 && dc == sc && dr == sr + 2 && Board[turn][sr + 1][sc] == '.' )
		{
			return 1;
		}

		if (dc == sc && dr == sr + 1 )
		{
			return 1;
		}

		if ((dc == sc + 1 || dc == sc - 1) && dr == sr + 1 && Board[turn][dr][dc] >= 'a' && Board[turn][dr][dc] <= 'z')
		{
			return 1;
		}
	}

	return 0;
}

int check_rook(int sr, int sc, int dc, int dr)
{

	if (sr != dr && sc != dc)
	{
		return -1;
	}
	if (sr == dr && sc < dc)
	{
		for (int i = sc + 1; i < dc; i++)
		{
			if (Board[turn][sr][i] >= 'A' && Board[turn][sr][i] <= 'Z')
			{
				return -1;
			}
			else if (Board[turn][sr][i] >= 'a' && Board[turn][sr][i] <= 'z')
			{
				return -1;
			}
		}

	}
	if (sr == dr && sc > dc)
	{
		for (int i = sc - 1; i > dc; i--)
		{
			if (Board[turn][sr][i] >= 'A' && Board[turn][sr][i] <= 'Z')
			{
				return -1;
			}
			else if (Board[turn][sr][i] >= 'a' && Board[turn][sr][i] <= 'z')
			{
				return -1;
			}
		}

	}
	if (dc == sc && sr < dr)
	{
		for (int z = sr + 1; z < dr; z++)
		{
			if (Board[turn][z][dc] >= 'A' && Board[turn][z][dc] <= 'Z')
			{
				return -1;
			}
			else if (Board[turn][z][dc] >= 'a' && Board[turn][z][dc] <= 'z')
			{

				return -1;
			}
		}
	}
	if (dc == sc && sr > dr)
	{
		for (int z = sr - 1; z > dr; z--)
		{
			if (Board[turn][z][dc] >= 'A' && Board[turn][z][dc] <= 'Z')
			{
				return -1;
			}
			else if (Board[turn][z][dc] >= 'a' && Board[turn][z][dc] <= 'z')
			{
				return -1;
			}
		}
	}

	return 1;
}

int check_king(int sr, int sc, int dc, int dr)
{
	if (sr - dr == -1 || sr - dr == 1 || sr == dr)
	{
		if (sc - dc == -1 || sc - dc == 1 || sc == dc)
		{
			if (!(sr == dr && sc == dc))
			{
				return 1;
			}
		}
	}
	return -1;
}

int check_bish(int sr, int sc, int dc, int dr)
{
	int cu1 = dr - sr;
	int cu2 = dc - sc;
	if (cu1 < 0)
		cu1 = cu1 * -1;
	if (cu2 < 0)
		cu2 = cu2 * -1;
	if (cu1 != cu2)
		return -1;

	int dx = 0;
	if (dr > sr) {
		dx = 1;
	}
	else {
		dx = -1;
	}

	int dy = 0;
	if (dc > sc) {
		dy = 1;
	}
	else {
		dy = -1;
	}

	for (int j = 1; j < cu1; j++)
	{
		int q = sr + j * dx;
		int p = sc + j * dy;
		if (Board[turn][q][p] != '.')
			return -1;
	}
	return 1;

}

int check_knight(int sr, int sc, int dc, int dr)
{
	int dif1 = dr - sr;
	int dif2 = dc - sc;

	if (dif1 < 0) dif1 = -dif1;
	if (dif2 < 0) dif2 = -dif2;

	if ((dif1 == 2 && dif2 == 1) || (dif1 == 1 && dif2 == 2))
	{
		return 1;
	}

	return -1;
}

void Display_2(int sc, int sr)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "          <=== Welcome To Chess ===>" << endl;


	cout << "              1  2  3  4  5  6  7  8" << endl;

	for (int i = 0; i < ROWS; i++)
	{
		cout << "           " << i + 1 << "  ";
		for (int k = 0; k < COLS; k++)
		{
			int colour = 7;


			if (Board[turn][i][k] >= 'a' && Board[turn][i][k] <= 'z')
				colour = 15;
			else if (Board[turn][i][k] >= 'A' && Board[turn][i][k] <= 'Z')
				colour = 8;

			if ((Board[turn][sr][sc] == 'r' || Board[turn][sr][sc] == 'R') && (check_rook(sr, sc, k, i) == 1 && check_dest(k, i) == 1))
				colour = 4;
			else if ((Board[turn][sr][sc] == 'P' || Board[turn][sr][sc] == 'p') && (check_pawn(sr, sc, k, i) == 1 && check_dest(k, i) == 1))
				colour = 4;
			else if ((Board[turn][sr][sc] == 'b' || Board[turn][sr][sc] == 'B') && (check_bish(sr, sc, k, i) == 1 && check_dest(k, i) == 1))
				colour = 4;
			else if ((Board[turn][sr][sc] == 'q' || Board[turn][sr][sc] == 'Q') && ((check_rook(sr, sc, k, i) == 1) || check_bish(sr, sc, k, i) == 1) && check_dest(k, i))
				colour = 4;
			else if ((Board[turn][sr][sc] == 'k' || Board[turn][sr][sc] == 'K') && (check_king(sr, sc, k, i) == 1) && check_dest(k, i))
				colour = 4;
			else if ((Board[turn][sr][sc] == 'n' || Board[turn][sr][sc] == 'N') && (check_knight(sr, sc, k, i) == 1) && check_dest(k, i))
				colour = 4;
			SetConsoleTextAttribute(hConsole, colour);
			cout << Board[turn][i][k] << "  ";
			SetConsoleTextAttribute(hConsole, 7);
		}
		cout << endl;
	}

	cout << "              1  2  3  4  5  6  7  8" << endl;
}

void find_king(int& r, int& c)
{
	if (turn % 2 == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board[turn][i][j] == 'k')
				{
					r = i;
					c = j;
					return;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board[turn][i][j] == 'K')
				{
					r = i;
					c = j;
					return;
				}
			}
		}
	}
}

bool Is_empty(char piece)
{
	return piece == '.';
}

bool is_white(char piece)
{
	return piece >= 'a' && piece <= 'z';
}

bool is_black(char piece)
{
	return piece >= 'A' && piece <= 'Z';
}

bool owns_current_player(char piece, int turn)
{
	if (piece == '.') return false;

	if (turn % 2 == 0)
	{

		return is_white(piece);
	}
	else {

		return is_black(piece);
	}
}

int check_check(int r, int c)
{
	if (turn % 2 == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board[turn][i][j] >= 'A' && Board[turn][i][j] <= 'Z')
				{
					if (Board[turn][i][j] == 'P' && check_pawn(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'R' && check_rook(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'N' && check_knight(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'B' && check_bish(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'Q' && (check_bish(i, j, c, r) == 1 || check_rook(i, j, c, r) == 1)) return 1;
					else if (Board[turn][i][j] == 'K' && check_king(i, j, c, r) == 1)
						return 1;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (Board[turn][i][j] >= 'a' && Board[turn][i][j] <= 'z')
				{
					if (Board[turn][i][j] == 'p' && check_pawn(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'r' && check_rook(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'n' && check_knight(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'b' && check_bish(i, j, c, r) == 1)
						return 1;
					else if (Board[turn][i][j] == 'q' && (check_bish(i, j, c, r) == 1 || check_rook(i, j, c, r) == 1))
						return 1;
					else if (Board[turn][i][j] == 'k' && check_king(i, j, c, r) == 1)
						return 1;
				}
			}
		}
	}
	return 0;
}

void move(int dr, int dc, int sr, int sc)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			Board[turn + 1][i][j] = Board[turn][i][j];
		}
	}
	Board[turn + 1][dr][dc] = Board[turn][sr][sc];
	Board[turn + 1][sr][sc] = '.';
	return;
}

bool is_valid_move(char piece, int sr, int sc, int dr, int dc)
{

	if (piece == 'P' || piece == 'p')
		return check_pawn(sr, sc, dc, dr) == 1;

	if (piece == 'R' || piece == 'r')
		return check_rook(sr, sc, dc, dr) == 1;

	if (piece == 'N' || piece == 'n')
		return check_knight(sr, sc, dc, dr) == 1;

	if (piece == 'B' || piece == 'b')
		return check_bish(sr, sc, dc, dr) == 1;

	if (piece == 'Q' || piece == 'q')
		return (check_rook(sr, sc, dc, dr) == 1) || (check_bish(sr, sc, dc, dr) == 1);

	if (piece == 'K' || piece == 'k')
		return check_king(sr, sc, dc, dr) == 1;

	return false;
}

bool has_no_legal_moves()
{
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			char piece = Board[turn][r][c];
			if (!owns_current_player(piece, turn)) continue;

			for (int dr = 0; dr < 8; dr++)
			{
				for (int dc = 0; dc < 8; dc++)
				{

					if (!(check_dest(dc, dr) == 1)) continue;

					if (!is_valid_move(piece, r, c, dr, dc)) continue;


					char src = Board[turn][r][c];
					char dst = Board[turn][dr][dc];
					Board[turn][dr][dc] = src;
					Board[turn][r][c] = '.';


					int k_r = 0, k_c = 0;
					find_king(k_r, k_c);
					bool inCheck = (check_check(k_r, k_c) == 1);


					Board[turn][r][c] = src;
					Board[turn][dr][dc] = dst;


					if (!inCheck) return false;
				}
			}
		}
	}
	return true;
}

void perform_castling(int type)
{
	if (type == 1)
	{
		if (turn % 2 == 0)
		{
			if (white_king_moved || white_right_rook_moved)
			{
				cout << "Cannot Castle: King or Rook has moved." << endl;
			}
			else if (Board[turn][7][5] != '.' || Board[turn][7][6] != '.')
			{
				cout << "Cannot Castle: Path is not clear." << endl;
			}
			else
			{
				for (int v = 0; v < 8; v++)
					for (int o = 0; o < 8; o++)
						Board[turn + 1][v][o] = Board[turn][v][o];

				Board[turn + 1][7][5] = 'k';
				Board[turn + 1][7][4] = '.';
				Board[turn + 1][7][7] = '.';

				if (check_check(7, 5) == 1)
				{
					cout << "There is a check in castling." << endl;
				}
				else
				{
					Board[turn + 1][7][6] = 'k';
					Board[turn + 1][7][5] = 'r';
					Board[turn + 1][7][4] = '.';
					Board[turn + 1][7][7] = '.';

					if (check_check(7, 6) == 1)
					{
						cout << "Cannot Castle: You are in check in castling." << endl;
					}
					else
					{
						white_king_moved = true;
						white_right_rook_moved = true;
						turn++;
						system("cls");
					}
				}
			}
		}
		else
		{
			if (black_king_moved || black_right_rook_moved)
			{
				cout << "Cannot Castle: King or Rook has moved." << endl;
			}
			else if (Board[turn][0][5] != '.' || Board[turn][0][6] != '.')
			{
				cout << "Cannot Castle: Path is not clear." << endl;
			}
			else
			{
				for (int v = 0; v < 8; v++)
					for (int o = 0; o < 8; o++)
						Board[turn + 1][v][o] = Board[turn][v][o];

				Board[turn + 1][0][5] = 'K';

				if (check_check(0, 5) == 1)
				{
					cout << "There is a check in castling." << endl;
				}
				else
				{
					Board[turn + 1][0][6] = 'K';
					Board[turn + 1][0][5] = 'R';
					Board[turn + 1][0][4] = '.';
					Board[turn + 1][0][7] = '.';

					if (check_check(0, 6) == 1)
					{
						cout << "Cannot Castle: You are in check in castling." << endl;
					}
					else
					{
						black_king_moved = true;
						black_right_rook_moved = true;
						turn++;
						system("cls");
					}
				}
			}
		}
	}
	else if (type == 2)
	{
		if (turn % 2 == 0)
		{
			if (white_king_moved || white_left_rook_moved)
			{
				cout << "Cannot Castle: King or Rook has moved." << endl;
			}
			else if (Board[turn][7][1] != '.' || Board[turn][7][2] != '.' || Board[turn][7][3] != '.')
			{
				cout << "Cannot Castle: Path is not clear." << endl;
			}
			else
			{
				for (int v = 0; v < 8; v++)
					for (int o = 0; o < 8; o++)
						Board[turn + 1][v][o] = Board[turn][v][o];

				Board[turn + 1][7][3] = 'k';

				if (check_check(7, 3) == 1)
				{
					cout << "There is a check in castling." << endl;
				}
				else
				{
					Board[turn + 1][7][2] = 'k';
					Board[turn + 1][7][3] = 'r';
					Board[turn + 1][7][4] = '.';
					Board[turn + 1][7][0] = '.';

					if (check_check(7, 2) == 1)
					{
						cout << "Cannot Castle: You are in check in castling." << endl;
					}
					else
					{
						white_king_moved = true;
						white_left_rook_moved = true;
						turn++;
						system("cls");
					}
				}
			}
		}
		else
		{
			if (black_king_moved || black_left_rook_moved)
			{
				cout << "Cannot Castle: King or Rook has moved." << endl;
			}
			else if (Board[turn][0][1] != '.' || Board[turn][0][2] != '.' || Board[turn][0][3] != '.')
			{
				cout << "Cannot Castle: Path is not clear." << endl;
			}
			else
			{
				for (int v = 0; v < 8; v++)
					for (int o = 0; o < 8; o++)
						Board[turn + 1][v][o] = Board[turn][v][o];

				Board[turn + 1][0][3] = 'K';

				if (check_check(0, 3) == 1)
				{
					cout << "King in Danger During Castling" << endl;
				}
				else
				{
					Board[turn + 1][0][2] = 'K';
					Board[turn + 1][0][3] = 'R';
					Board[turn + 1][0][4] = '.';
					Board[turn + 1][0][0] = '.';

					if (check_check(0, 2) == 1)
					{
						cout << "Cannot Castle: You are in check in castling." << endl;
					}
					else
					{
						black_king_moved = true;
						black_left_rook_moved = true;
						turn++;
						system("cls");
					}
				}
			}
		}
	}
}

int can_castle()
{

	if (turn % 2 == 0)
	{

		if (!white_king_moved && !white_right_rook_moved &&
			Board[turn][7][5] == '.' && Board[turn][7][6] == '.' &&
			check_check(7, 4) == 0 && check_check(7, 5) == 0 && check_check(7, 6) == 0)
		{
			return 1;
		}

		if (!white_king_moved && !white_left_rook_moved &&
			Board[turn][7][1] == '.' && Board[turn][7][2] == '.' && Board[turn][7][3] == '.' &&
			check_check(7, 4) == 0 && check_check(7, 3) == 0 && check_check(7, 2) == 0)
		{
			return 2;
		}
	}

	else
	{

		if (!black_king_moved && !black_right_rook_moved &&
			Board[turn][0][5] == '.' && Board[turn][0][6] == '.' &&
			check_check(0, 4) == 0 && check_check(0, 5) == 0 && check_check(0, 6) == 0)
		{
			return 1;
		}

		if (!black_king_moved && !black_left_rook_moved &&
			Board[turn][0][1] == '.' && Board[turn][0][2] == '.' && Board[turn][0][3] == '.' &&
			check_check(0, 4) == 0 && check_check(0, 3) == 0 && check_check(0, 2) == 0)
		{
			return 2;
		}
	}

	return -1;
}

void safe_kill(int& sr, int& sc, int& dr, int& dc)
{
	char temp1, temp2;
	if (turn % 2 == 0)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] >= 'A' && Board[turn][j][c] <= 'Z')
						{
							char piece = Board[turn][sr][sc];
							bool valid = false;
							if (piece == 'p' && check_pawn(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'b' && check_bish(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'r' && check_rook(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1)) valid = true;
							else if (piece == 'n' && check_knight(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'k' && check_king(sr, sc, c, j) == 1) valid = true;

							if (valid && check_dest(c, j) == 1)
							{
								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] >= 'a' && Board[turn][j][c] <= 'z')
						{
							char piece = Board[turn][sr][sc];
							bool valid = false;
							if (piece == 'P' && check_pawn(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'B' && check_bish(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'R' && check_rook(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'Q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1)) valid = true;
							else if (piece == 'N' && check_knight(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'K' && check_king(sr, sc, c, j) == 1) valid = true;

							if (valid && check_dest(c, j) == 1)
							{
								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
}

void un_safe_kill(int& sr, int& sc, int& dr, int& dc)
{
	char temp1, temp2;
	if (turn % 2 == 0)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] >= 'A' && Board[turn][j][c] <= 'Z')
						{
							char piece = Board[turn][sr][sc];
							bool valid = false;
							if (piece == 'p' && check_pawn(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'b' && check_bish(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'r' && check_rook(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1)) valid = true;
							else if (piece == 'n' && check_knight(sr, sc, c, j) == 1) valid = true;

							if (valid && check_dest(c, j) == 1)
							{
								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) == 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] >= 'a' && Board[turn][j][c] <= 'z')
						{
							char piece = Board[turn][sr][sc];
							bool valid = false;
							if (piece == 'P' && check_pawn(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'B' && check_bish(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'R' && check_rook(sr, sc, c, j) == 1) valid = true;
							else if (piece == 'Q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1)) valid = true;
							else if (piece == 'N' && check_knight(sr, sc, c, j) == 1) valid = true;

							if (valid && check_dest(c, j) == 1)
							{
								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) == 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
}

void normal_move(int& sr, int& sc, int& dr, int& dc)
{
	char temp1, temp2;

	if (turn % 2 == 0)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] == '.')
						{
							if (Board[turn][sr][sc] == 'p' && check_pawn(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'b' && check_bish(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'r' && check_rook(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1) && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'n' && check_knight(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'k' && check_king(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{

								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] == '.')
						{
							if (Board[turn][sr][sc] == 'P' && check_pawn(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'B' && check_bish(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'R' && check_rook(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'Q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1) && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'N' && check_knight(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'K' && check_king(sr, sc, c, j) == 1 && check_dest(c, j) == 1)
							{

								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
}

void enter_enemy_space(int& sr, int& sc, int& dr, int& dc)
{
	char temp1, temp2;

	if (turn % 2 == 0)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] == '.')
						{
							if (Board[turn][sr][sc] == 'p' && check_pawn(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j < i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'b' && check_bish(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j < i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'r' && check_rook(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j < i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1) && check_dest(c, j) == 1)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'n' && check_knight(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j < i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'k' && check_king(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j < i)
							{

								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int k = 0; k < COLS; k++)
			{
				sr = i; sc = k;
				for (int j = 0; j < ROWS; j++)
				{
					for (int c = 0; c < COLS; c++)
					{
						if (Board[turn][j][c] == '.')
						{
							if (Board[turn][sr][sc] == 'P' && check_pawn(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j > i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'B' && check_bish(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j > i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'R' && check_rook(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j > i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'Q' && (check_rook(sr, sc, c, j) == 1 || check_bish(sr, sc, c, j) == 1) && check_dest(c, j) == 1 && j > i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'N' && check_knight(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j > i)
							{
								dr = j; dc = c; return;
							}
							else if (Board[turn][sr][sc] == 'K' && check_king(sr, sc, c, j) == 1 && check_dest(c, j) == 1 && j > i)
							{

								temp1 = Board[turn][sr][sc];
								temp2 = Board[turn][j][c];
								Board[turn][sr][sc] = '.';
								Board[turn][j][c] = temp1;

								if (check_check(j, c) != 1)
								{
									dr = j; dc = c;
									Board[turn][sr][sc] = temp1;
									Board[turn][j][c] = temp2;
									return;
								}

								Board[turn][sr][sc] = temp1;
								Board[turn][j][c] = temp2;
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	intialize_board();
	int chos = 0;
	int saf_kil_sr = -1, saf_kil_sc = -1;
	int die_kil_sr = -1, die_kil_sc = -1;
	int safe_kil_dr = -1, safe_kil_dc = -1;
	int die_kil_dr = -1, die_kil_dc = -1;
	int castle_side = -1;

	while (true)
	{
		cout << "Welcome To Chess!" << endl;
		cout << endl << "1 - Start New Game\n2 - Load Saved Game\nChoice: ";
		cin >> chos;
		system("cls");
		if (chos == 2) { read_save(); break; }
		else if (chos == 1) { intialize_board(); break; }
	}
	cout << endl;
	int d_r, d_c;
	int is_bot = 0;
	int done = 0;
	int k_c = 0, k_r = 0;
	int s_r, s_c;
	int is_human = 0;
	int choice = 0;
	char charct;
	int check = 0;
	int bot_col = -1;
	cout << "Wanna Play With bot?" << endl;
	while (true)
	{
		cout << "1 - bot\n2 - Human\n choice:";
		cin >> is_bot;
		if (is_bot == 1 || is_bot == 2)
		{
			if (is_bot == 2) is_bot = -1;
			break;
		}
	}
	bot_col = 1;

	while (true)
	{
		find_king(k_r, k_c);
		Display_board();

		if (is_bot == 1 && ((turn % 2 == 0 && bot_col == 2) || (turn % 2 == 1 && bot_col == 1)))
			is_human = -1;
		else
			is_human = 1;
		if (is_human == 1)
		{
			cout << "Menu:" << endl;
			if (turn % 2 == 0) cout << "White's Turn!" << endl;
			else cout << "Black's Turn!" << endl;

			cout << "1 - Wanna Play\n2 - Wanna Quit\n3 - Wanna Save\n4 - Wanna Undo\n5 - Wanna Redo\n6 - Castling\nChoice: ";
			cin >> choice;
			if (choice == 2)
			{
				break;
			}
			else if (choice == 4)
			{
				if (turn - 1 >= 0) { turn--; system("cls"); }
				else { cout << "Cannot Undo Further!" << endl; }
			}
			else if (choice == 5)
			{
				if (turn + 1 < MAX_MOVES && Board[turn + 1][0][0] != '\0') { turn++; system("cls"); }
				else { cout << "Cannot Redo Further!" << endl; }
			}
			else if (choice == 3)
			{
				save_game();
			}
			else if (choice == 6)
			{
				system("cls");
				int type = 0;
				while (true)
				{
					cout << "Enter The Castling Type (1 - King Side, 2 - Queen Side): ";
					cin >> type;
					if (type == 1 || type == 2) break;
					cout << "Invalid Castling Type. Please try again." << endl;
				}
				perform_castling(type);
			}
			else if (choice == 1)
			{
				while (true)
				{
					cout << "Enter The Source Row And Source Column: ";
					cin >> s_r >> s_c;
					s_r--; s_c--;
					if (check_source(s_r, s_c) == 1)
					{
						cout << "Successful Input" << endl;
						break;
					}
				}
				system("cls");

				while (true)
				{
					Display_2(s_c, s_r);
					cout << "Enter The Destination Row and Destination Column: ";
					cin >> d_r >> d_c;
					d_r--; d_c--;

					if (Board[turn][s_r][s_c] == 'p' || Board[turn][s_r][s_c] == 'P')
					{
						if (check_pawn(s_r, s_c, d_c, d_r) == 1 && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					else if (Board[turn][s_r][s_c] == 'r' || Board[turn][s_r][s_c] == 'R')
					{
						if (check_rook(s_r, s_c, d_c, d_r) == 1 && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								system("cls");
								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					else if (Board[turn][s_r][s_c] == 'k' || Board[turn][s_r][s_c] == 'K')
					{
						if (check_king(s_r, s_c, d_c, d_r) == 1 && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								system("cls");
								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					else if (Board[turn][s_r][s_c] == 'B' || Board[turn][s_r][s_c] == 'b')
					{
						if (check_bish(s_r, s_c, d_c, d_r) == 1 && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								system("cls");
								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					else if (Board[turn][s_r][s_c] == 'N' || Board[turn][s_r][s_c] == 'n')
					{
						if (check_knight(s_r, s_c, d_c, d_r) == 1 && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								system("cls");
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;

								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					else if (Board[turn][s_r][s_c] == 'Q' || Board[turn][s_r][s_c] == 'q')
					{
						if ((check_rook(s_r, s_c, d_c, d_r) == 1 || check_bish(s_r, s_c, d_c, d_r) == 1) && check_dest(d_c, d_r) == 1)
						{
							char srcPiece = Board[turn][s_r][s_c];
							char destPiece = Board[turn][d_r][d_c];
							Board[turn][d_r][d_c] = srcPiece;
							Board[turn][s_r][s_c] = '.';
							find_king(k_r, k_c);
							if (check_check(k_r, k_c) == 1)
							{
								system("cls");
								cout << "Invalid: That move leaves your king in check!" << endl;
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;

								break;
							}
							else
							{
								Board[turn][s_r][s_c] = srcPiece;
								Board[turn][d_r][d_c] = destPiece;
								done = 1;
								break;
							}
						}
					}
					if (!done)
					{
						cout << "Invalid Movement" << endl;
						system("cls");
					}
				}
				if (done == 1)
				{
					if (Board[turn][s_r][s_c] == 'k') { white_king_moved = true; }
					else if (Board[turn][s_r][s_c] == 'K') { black_king_moved = true; }
					else if (Board[turn][s_r][s_c] == 'r' && s_c == 0) { white_left_rook_moved = true; }
					else if (Board[turn][s_r][s_c] == 'r' && s_c == 7) { white_right_rook_moved = true; }
					else if (Board[turn][s_r][s_c] == 'R' && s_c == 0) { black_left_rook_moved = true; }
					else if (Board[turn][s_r][s_c] == 'R' && s_c == 7) { black_right_rook_moved = true; }

					move(d_r, d_c, s_r, s_c);
					turn = turn + 1;
					system("cls");
					if (d_r == 7 && Board[turn][d_r][d_c] == 'P')
					{
						cout << "Promote Your Pawn to (Q, R, B, N): ";
						cin >> charct;
						if (charct == 'Q' || charct == 'q')
							Board[turn][d_r][d_c] = 'Q';
						else if (charct == 'R' || charct == 'r')
							Board[turn][d_r][d_c] = 'R';
						else if (charct == 'B' || charct == 'b')
							Board[turn][d_r][d_c] = 'B';
						else if (charct == 'N' || charct == 'n')
							Board[turn][d_r][d_c] = 'N';
						else cout << "Invalid promotion choice!" << endl;
					}
					else if (d_r == 0 && Board[turn][d_r][d_c] == 'p')
					{
						cout << "Promote Your Pawn to (Q, R, B, N): ";
						cin >> charct;
						if (charct == 'Q' || charct == 'q')
							Board[turn][d_r][d_c] = 'q';
						else if (charct == 'R' || charct == 'r')
							Board[turn][d_r][d_c] = 'r';
						else if (charct == 'B' || charct == 'b')
							Board[turn][d_r][d_c] = 'b';
						else if (charct == 'N' || charct == 'n')
							Board[turn][d_r][d_c] = 'n';
						else cout << "Invalid promotion choice!" << endl;
					}
				}

				find_king(k_r, k_c);
				check = check_check(k_r, k_c);
				done = 0;
				int stale = has_no_legal_moves();
				if (stale == 1)
				{
					Display_board();
					if (check == 1)
					{
						cout << "Checkmate! ";
						if (turn % 2 == 0) cout << "Black Wins!" << endl;
						else cout << "White Wins!" << endl;
					}
					else
					{
						cout << "Stalemate! It's a Draw!" << endl;
					}
					break;
				}
				else
				{
					if (check == 1) cout << "You Have a Check!" << endl;
				}
			}
		}
		else
		{
			system("cls");
			saf_kil_sr = -1; saf_kil_sc = -1;
			die_kil_sr = -1; die_kil_sc = -1;
			safe_kil_dr = -1; safe_kil_dc = -1;
			die_kil_dr = -1; die_kil_dc = -1;

			int  start_r = -1, start_c = -1, dest_r = -1, dest_c = -1;
			int can_cast = can_castle();

			safe_kill(saf_kil_sr, saf_kil_sc, safe_kil_dr, safe_kil_dc);

			if (saf_kil_sr != -1 && saf_kil_sc != -1 && safe_kil_dr != -1 && safe_kil_dc != -1)
			{
				s_r = saf_kil_sr; s_c = saf_kil_sc;
				d_r = safe_kil_dr; d_c = safe_kil_dc;
				move(d_r, d_c, s_r, s_c);
				if (turn % 2 == 0)
				{
					if (d_r == 0 && Board[turn + 1][d_r][d_c] == 'p') Board[turn + 1][d_r][d_c] = 'q';
				}
				else
				{
					if (d_r == 7 && Board[turn + 1][d_r][d_c] == 'P') Board[turn + 1][d_r][d_c] = 'Q';
				}

				turn = turn + 1;

			}
			else if (die_kil_sr != -1 && die_kil_sc != -1 && die_kil_dr != -1 && die_kil_dc != -1)
			{
				s_r = die_kil_sr; s_c = die_kil_sc;
				d_r = die_kil_dr; d_c = die_kil_dc;
				move(d_r, d_c, s_r, s_c);
				if (turn % 2 == 0)
				{
					if (d_r == 0 && Board[turn + 1][d_r][d_c] == 'p') Board[turn + 1][d_r][d_c] = 'q';
				}
				else
				{
					if (d_r == 7 && Board[turn + 1][d_r][d_c] == 'P') Board[turn + 1][d_r][d_c] = 'Q';
				}
				turn = turn + 1;

			}
			else if (can_cast != -1)
			{
				if (can_cast == 1) perform_castling(1);
				else if (can_cast == 2) perform_castling(2);
			}

			else
			{
				normal_move(s_r, s_c, d_r, d_c);
				move(d_r, d_c, s_r, s_c);
				if (turn % 2 == 0)
				{
					if (d_r == 0 && Board[turn + 1][d_r][d_c] == 'p') Board[turn + 1][d_r][d_c] = 'q';
				}
				else
				{
					if (d_r == 7 && Board[turn + 1][d_r][d_c] == 'P') Board[turn + 1][d_r][d_c] = 'Q';
				}

				turn = turn + 1;

			}

		}
	}
	return 0;
}