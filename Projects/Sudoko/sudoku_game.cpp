#include "sudoku_game.h"
#include <fstream>
#include <sstream>

// Save file layout (plain text):
//   SUDOKU-SAVE
//   <attempts left>
//   9 lines of 81 board digits
//   9 lines of 81 given-cell flags (1 = original puzzle cell)
static const char* SAVE_MAGIC = "SUDOKU-SAVE";

SudokuGame::SudokuGame() : mistakes(10) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = 0;
			fixed[i][j] = false;
		}
	}
}

bool SudokuGame::loadFromFile(const std::string& path) {
	std::ifstream fin(path.c_str());
	if (!fin) {
		return false;
	}

	// Save file? First line is the magic marker.
	std::string firstLine;
	std::getline(fin, firstLine);
	// strip a possible trailing \r from files edited on Windows
	while (!firstLine.empty() && (firstLine[firstLine.size() - 1] == '\r' ||
	                              firstLine[firstLine.size() - 1] == ' ')) {
		firstLine.erase(firstLine.size() - 1);
	}

	if (firstLine == SAVE_MAGIC) {
		int savedMistakes = 0;
		if (!(fin >> savedMistakes) || savedMistakes < 0 || savedMistakes > 10) {
			return false;
		}
		int tempBoard[SIZE][SIZE];
		bool tempFixed[SIZE][SIZE];
		char ch = 0;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (!(fin >> ch) || ch < '0' || ch > '9') {
					return false;
				}
				tempBoard[i][j] = ch - '0';
			}
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (!(fin >> ch) || (ch != '0' && ch != '1')) {
					return false;
				}
				tempFixed[i][j] = (ch == '1');
				// a given cell can't be empty
				if (tempFixed[i][j] && tempBoard[i][j] == 0) {
					return false;
				}
			}
		}
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				board[i][j] = tempBoard[i][j];
				fixed[i][j] = tempFixed[i][j];
			}
		}
		mistakes = savedMistakes;
		return true;
	}

	// Plain puzzle: read 81 digits, starting with the line already consumed.
	std::string rest = firstLine;
	std::string line;
	while (std::getline(fin, line)) {
		rest += line;
	}
	return loadFromString(rest);
}

bool SudokuGame::loadFromString(const std::string& digits) {
	int cell = 0;
	int temp[SIZE][SIZE];
	for (size_t k = 0; k < digits.size() && cell < SIZE * SIZE; k++) {
		char ch = digits[k];
		if (ch >= '0' && ch <= '9') {
			temp[cell / SIZE][cell % SIZE] = ch - '0';
			cell++;
		}
	}
	if (cell != SIZE * SIZE) {
		return false;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = temp[i][j];
			fixed[i][j] = (board[i][j] != 0);
		}
	}
	mistakes = 10;
	return true;
}

bool SudokuGame::saveToFile(const std::string& path) const {
	std::ofstream fout(path.c_str());
	if (!fout) {
		return false;
	}
	fout << SAVE_MAGIC << "\n";
	fout << mistakes << "\n";
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fout << board[i][j];
		}
		fout << "\n";
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			fout << (fixed[i][j] ? '1' : '0');
		}
		fout << "\n";
	}
	return fout.good();
}

bool SudokuGame::inRange(int row, int col) const {
	return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

bool SudokuGame::rowHas(int row, int value) const {
	for (int j = 0; j < SIZE; j++) {
		if (board[row][j] == value) {
			return true;
		}
	}
	return false;
}

bool SudokuGame::colHas(int col, int value) const {
	for (int i = 0; i < SIZE; i++) {
		if (board[i][col] == value) {
			return true;
		}
	}
	return false;
}

bool SudokuGame::boxHas(int row, int col, int value) const {
	int startRow = (row / 3) * 3;
	int startCol = (col / 3) * 3;
	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (board[i][j] == value) {
				return true;
			}
		}
	}
	return false;
}

SudokuGame::MoveResult SudokuGame::placeValue(int row, int col, int value) {
	if (!inRange(row, col) || value < 1 || value > 9) {
		return MOVE_OUT_OF_RANGE;
	}
	if (fixed[row][col]) {
		mistakes--;
		return MOVE_FIXED_CELL;
	}

	// Take the cell's current value out of play so a player can
	// overwrite their own earlier entry without it conflicting with itself.
	int previous = board[row][col];
	board[row][col] = 0;

	if (rowHas(row, value) || colHas(col, value) || boxHas(row, col, value)) {
		board[row][col] = previous;
		mistakes--;
		return MOVE_CONFLICT;
	}

	board[row][col] = value;
	return MOVE_OK;
}

bool SudokuGame::clearCell(int row, int col) {
	if (!inRange(row, col) || fixed[row][col]) {
		return false;
	}
	board[row][col] = 0;
	return true;
}

int SudokuGame::getCell(int row, int col) const {
	if (!inRange(row, col)) {
		return 0;
	}
	return board[row][col];
}

bool SudokuGame::isFixedCell(int row, int col) const {
	if (!inRange(row, col)) {
		return false;
	}
	return fixed[row][col];
}

int SudokuGame::mistakesLeft() const {
	return mistakes;
}

bool SudokuGame::isBoardFilled() const {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

bool SudokuGame::cellIsDuplicate(int row, int col) const {
	int value = board[row][col];
	if (value == 0) {
		return false;
	}

	int count = 0;
	for (int j = 0; j < SIZE; j++) {
		if (board[row][j] == value) {
			count++;
		}
	}
	if (count > 1) {
		return true;
	}

	count = 0;
	for (int i = 0; i < SIZE; i++) {
		if (board[i][col] == value) {
			count++;
		}
	}
	if (count > 1) {
		return true;
	}

	int startRow = (row / 3) * 3;
	int startCol = (col / 3) * 3;
	count = 0;
	for (int i = startRow; i < startRow + 3; i++) {
		for (int j = startCol; j < startCol + 3; j++) {
			if (board[i][j] == value) {
				count++;
			}
		}
	}
	return count > 1;
}

bool SudokuGame::isWon() const {
	if (!isBoardFilled()) {
		return false;
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (cellIsDuplicate(i, j)) {
				return false;
			}
		}
	}
	return true;
}

bool SudokuGame::isLost() const {
	return mistakes <= 0;
}
