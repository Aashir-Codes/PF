#include <iostream>
#include <fstream>

using namespace std;


int mistakes = 10;
int board[9][9] = {};
int valid[9][9] = {};
void loadarray() {
	
	ifstream fin("input.txt");

	char ch = 0;
	int n = 0;
	
	for (int j = 0; j < 9; j++) 
	{
		
		for (int i = 0; i < 9; i++) {
			fin >> ch;
			n = ch - '0';
			board[j][i] = n;
		}
	
	}
	fin.close();
}
bool isboardfilled() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {

			if (board[i][j] == 0)
				return false;


		}
	}
	return true;
}
bool check_row(int r, int c, int value) {
	int count = 0;

	for (int i = 0; i < 9; i++) {
		if (board[i][c] == value) {
			return false;
		}

	}
	return true;
}
bool check_row1(int r, int c, int value) {
	int count = 0;

	for (int i = 0; i < 9; i++) {
		if (board[i][c] == value) {
			count++;
			if (count > 1) {
				return false;
			}
		}

	}
	return true;
}

bool check_col(int r, int c, int value) {
	int count = 0;

	for (int i = 0; i < 9; i++) {
		if (board[r][i] == value) {
			

			return false;
		}
	}

	
	return true;
}
bool check_col1(int r, int c, int value) {
	int count = 0;

	for (int i = 0; i < 9; i++) {
		if (board[r][i] == value) {
			count++;
			if (count > 1) {
				return false;
			}
		};

	}
	return true;
}

bool check_grid1(int r, int c,int value) {

	int a = r / 3;
	int b = c / 3;
	a *= 3;
	b *= 3;
	
	int count = 0;
	for (int i = a; i < a+3; i++) {
		for (int j = b; j < b+3; j++) {

			if (board[i][j] == value) {
				count++;
				if (count > 1) {
					return false;

				}
			}
		
		
        }
	}

	return true;



}
bool check_grid(int r, int c, int value) {

	int a = r / 3;
	int b = c / 3;
	a *= 3;
	b *= 3;

	int count = 0;
	for (int i = a; i < a + 3; i++) {
		for (int j = b; j < b + 3; j++) {

			if (board[i][j] == value) {
				return false;
			}


		}
	}

	return true;



}
bool _valid(int r, int c, int value) {
	if (valid[r][c] == 1) {
		return false;
	}
	else {
		return true;
	}



}
bool isValidMove(int r, int c, int value) {
	if
		(check_grid(r, c, value) == 0 ||
			check_col(r, c, value) == 0 ||
			check_row(r, c, value) == 0||
		_valid(r,c,value)==0)
	{
		return false;
	}

	else
		return true;


}
bool isend(int r, int c, int value) {
	if
		(check_grid1(r, c, value) == 0 ||
			check_col1(r, c, value) == 0 ||
			check_row1(r, c, value) == 0)
	{
		return false;
	}

	else
		return true;


}
void print() {
	cout << "         <STUDOKO>" << endl;
	cout << "“Think Sharp. Play Smart.”" << endl;
	cout << "Attempt Remainig :" << mistakes << endl;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 3 || j == 6) {
				cout << "|";
			}
			if (board[i][j] == 0) {
				cout << ".  ";
			}
			else
			cout << board[i][j]<<"  ";
			
		}
		
		cout << endl;
		if (i == 2 || i == 5) {
			cout << "---------+---------+--------\n";
		}
	}

}


void place_value(int r, int c, int value) {

	if (isValidMove(r,c,value) == 0) {
		mistakes--;
		cout << "Wrong Entry" << endl;
	}
	else {
		board[r][c] = value;
	}


}
bool win() {
	bool flag = isboardfilled();
	
	if (flag ==  true) {


		for (int i = 0; i < 9; i++) {

			for (int j = 0; j < 9; j++) {

				if (isend(i, j, board[i][j]) == 0) {
					return false;
				}



			}

		}
	}
	else {

		return false;
	}
	
		return true;

}

int main() {
	loadarray();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != 0) {
				valid[i][j] = 1;
		   
			}
			else {
				valid[i][j] = 0;
			}
		}
	}
	int r = 0;
	int c = 0;
	int v = 0;
	bool flag = false;
	bool flag2 = false;
	
	do {
		system("cls");
		flag2 = isboardfilled();
		print();
		if (flag == false  && flag2==false) {
			cout << "               Wrong Entry!   " << endl;
		}
		if (win() == true) {
			cout << "<<=============== You Won ===============>>" << endl;
			return  0;
		}
		flag = true;
		cout << "Enter 10 TO to quit" << endl;
		cout << "enter rows            (1-9)" << endl;
		cin >> r;
		if (r == 10) {
			cout << "<======================= Exiting ======================>" << endl;
			return 0;

		}
		r--;
		cout << "enter column        (1-9)" << endl;
		cin >> c;
		c--;

		cout << "Enter value        (1-9)" << endl;
		cin >> v;
		
		
		
		

		place_value(r, c, v);
		flag = isValidMove(r, c, v);
	} while (mistakes>0);


	cout << "<========== you lose ===========>" << endl;
	return 0;
}