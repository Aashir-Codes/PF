#ifndef SUDOKU_GAME_H
#define SUDOKU_GAME_H

#include <string>

// Pure game logic: no cin/cout, no screen clearing.
// Any frontend (console, Qt, SFML, web) drives the game through this class.
class SudokuGame {
public:
	static const int SIZE = 9;

	// Result of a move attempt, so the UI can show a specific message.
	enum MoveResult {
		MOVE_OK,            // value placed
		MOVE_OUT_OF_RANGE,  // row/col/value outside 1-9
		MOVE_FIXED_CELL,    // cell is part of the original puzzle
		MOVE_CONFLICT       // value already in row, column or 3x3 box
	};

	SudokuGame();

	// Loads a puzzle (81 digits, 0 = empty). Also accepts save files
	// created by saveToFile. Returns false if the file can't be opened
	// or is malformed.
	bool loadFromFile(const std::string& path);

	// Same, but from a string of 81 digits (whitespace ignored).
	bool loadFromString(const std::string& digits);

	// Writes the full game state (board, given cells, attempts left)
	// as a text file that loadFromFile can restore.
	bool saveToFile(const std::string& path) const;

	// All coordinates here are 0-indexed (0-8). Wrong moves cost a mistake.
	MoveResult placeValue(int row, int col, int value);

	// Erase a player-placed value (given cells can't be erased).
	bool clearCell(int row, int col);

	int  getCell(int row, int col) const;    // 0 = empty
	bool isFixedCell(int row, int col) const; // true = original puzzle cell

	int  mistakesLeft() const;
	bool isBoardFilled() const;
	bool isWon() const;   // board filled and every row/col/box duplicate-free
	bool isLost() const;  // no mistakes remaining

private:
	int  board[SIZE][SIZE];
	bool fixed[SIZE][SIZE];
	int  mistakes;

	bool inRange(int row, int col) const;
	bool rowHas(int row, int value) const;
	bool colHas(int col, int value) const;
	bool boxHas(int row, int col, int value) const;
	bool cellIsDuplicate(int row, int col) const;
};

#endif
