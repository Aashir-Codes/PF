# Sudoku Game

A console-based Sudoku game written in C++.

## Features
- Load Sudoku puzzles from file
- Interactive gameplay
- Input validation
- Win/lose conditions

## How to Run
1. Compile: `g++ sudoku.cpp -o sudoku`
2. Create an `input.txt` file with a 9x9 Sudoku puzzle (use 0 for empty cells)
3. Run: `./sudoku`

## Game Rules
- Enter row, column, and value (1-9)
- You have 10 attempts
- Enter 10 to quit

## Sample Input File Format
```
530070000
600195000
098000060
800060003
400803001
700020006
060000280
000419005
000080079
```
```

## Step 5: Create .gitignore File

Create a file named `.gitignore`:
```
# Executables
*.exe
*.out
sudoku

# Input files (optional - remove if you want to include it)
input.txt

# IDE files
.vscode/
.idea/
*.o