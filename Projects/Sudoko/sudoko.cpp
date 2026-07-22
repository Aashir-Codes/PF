// Console frontend for the Sudoku game.
// All game rules live in SudokuGame (sudoku_game.h/.cpp) so a graphical
// UI can reuse them without touching this file.
#include <iostream>
#include <cstdlib>
#include "sudoku_game.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void printBoard(const SudokuGame& game) {
	cout << "         <SUDOKU>" << endl;
	cout << "\"Think Sharp. Play Smart.\"" << endl;
	cout << "Attempts Remaining: " << game.mistakesLeft() << endl;
	for (int i = 0; i < SudokuGame::SIZE; i++) {
		for (int j = 0; j < SudokuGame::SIZE; j++) {
			if (j == 3 || j == 6) {
				cout << "|";
			}
			int value = game.getCell(i, j);
			if (value == 0) {
				cout << ".  ";
			}
			else {
				cout << value << "  ";
			}
		}
		cout << endl;
		if (i == 2 || i == 5) {
			cout << "---------+---------+--------\n";
		}
	}
}

// Reads one number; returns false if the input wasn't a number.
bool readNumber(const char* label, int& out) {
	cout << label << endl;
	cin >> out;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		return false;
	}
	return true;
}

int main() {
	SudokuGame game;
	if (!game.loadFromFile("input.txt")) {
		cout << "Could not load input.txt (needs 81 digits, 0 = empty)." << endl;
		return 1;
	}

	const char* message = "";

	while (true) {
		clearScreen();
		printBoard(game);
		cout << message << endl;
		message = "";

		if (game.isWon()) {
			cout << "<<=============== You Won ===============>>" << endl;
			return 0;
		}
		if (game.isLost()) {
			cout << "<========== You Lose ===========>" << endl;
			return 0;
		}

		cout << "Enter 10 to quit" << endl;
		int r = 0, c = 0, v = 0;
		if (!readNumber("Enter row     (1-9)", r)) {
			message = "               Invalid input!";
			continue;
		}
		if (r == 10) {
			cout << "<======================= Exiting ======================>" << endl;
			return 0;
		}
		if (!readNumber("Enter column  (1-9)", c) ||
		    !readNumber("Enter value   (1-9)", v)) {
			message = "               Invalid input!";
			continue;
		}

		switch (game.placeValue(r - 1, c - 1, v)) {
		case SudokuGame::MOVE_OK:
			break;
		case SudokuGame::MOVE_OUT_OF_RANGE:
			message = "               Invalid input! Use 1-9.";
			break;
		case SudokuGame::MOVE_FIXED_CELL:
			message = "               Wrong Entry! That cell is part of the puzzle.";
			break;
		case SudokuGame::MOVE_CONFLICT:
			message = "               Wrong Entry! Value conflicts with row, column or box.";
			break;
		}
	}
}
