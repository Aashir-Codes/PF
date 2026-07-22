# Sudoku — Logic & Architecture

This document explains how the Sudoku project works internally: the game rules,
the data model, and how the frontends drive it. It is a companion to the
user-facing `Readme.md`.

## Overview

The project separates **rules** from **presentation**:

| File | Role |
|---|---|
| `sudoku_game.h` / `sudoku_game.cpp` | Pure game logic — the `SudokuGame` class. No I/O, no rendering. |
| `sudoku_gui.cpp` | raylib GUI frontend (menu + board). |
| `sudoko.cpp` | Original console frontend. |

Both frontends share the exact same `SudokuGame`, so the rules can never drift
between them. `SudokuGame` never calls `cin`/`cout` or draws anything — it only
holds state and answers questions ("is this move legal?", "have they won?").

```
            +---------------------+
            |     SudokuGame      |   <- rules & state (headless)
            |  board / fixed /    |
            |  mistakes           |
            +----------+----------+
                       |
        +--------------+--------------+
        |                             |
 +------v------+              +-------v-------+
 | sudoku_gui  |              |   sudoko      |
 | (raylib)    |              |  (console)    |
 +-------------+              +---------------+
```

## The data model (`SudokuGame`)

Three pieces of state describe an entire game:

- `int  board[9][9]` — current digits, `0` = empty.
- `bool fixed[9][9]` — `true` for cells that came from the original puzzle
  (the "givens"). These are shaded gray and can never be edited or erased.
- `int  mistakes` — attempts remaining, starts at **10**.

A cell is one of three things:
1. **Given** (`fixed == true`) — immutable clue.
2. **Player-filled** (`fixed == false`, `board != 0`).
3. **Empty** (`board == 0`).

## Loading a puzzle

There are two accepted text formats, both handled by `loadFromFile`:

1. **Plain puzzle** — 81 digits (`0` = empty), whitespace/newlines ignored.
   Parsed by `loadFromString`: it scans characters, keeps the first 81 digits,
   fills the board, and marks every non-zero cell as `fixed`. Mistakes reset to 10.
   Returns `false` if fewer than 81 digits are found.

2. **Save file** — first line is the magic marker `SUDOKU-SAVE`, then the
   attempts-left count, then 9 lines of board digits, then 9 lines of
   given-cell flags (`1`/`0`). This restores an in-progress game exactly,
   including which cells were givens and how many attempts are left.

`loadFromFile` reads the first line, strips a trailing `\r`/space (Windows
files), and branches on whether it equals the magic marker. Loads write into
temporary arrays first and only commit if the whole file validates, so a
malformed file leaves the current game untouched.

## Saving a game

`saveToFile` writes the save-file format described above: magic marker,
`mistakes`, the 9×9 board, then the 9×9 `fixed` flags. Because the given-cell
flags are stored explicitly, a reloaded save knows which numbers the player is
allowed to change — information that can't be recovered from the board alone.

## Making a move — `placeValue(row, col, value)`

This is the heart of the rules. It returns a `MoveResult` so the UI can react:

| Result | Meaning | Costs an attempt? |
|---|---|---|
| `MOVE_OK` | Value placed successfully | No |
| `MOVE_OUT_OF_RANGE` | row/col off-board or value not 1–9 | No |
| `MOVE_FIXED_CELL` | Tried to overwrite a given cell | **Yes** |
| `MOVE_CONFLICT` | Digit duplicates its row, column, or 3×3 box | **Yes** |

Algorithm:

1. Reject out-of-range coordinates or values (no penalty).
2. If the cell is `fixed`, decrement `mistakes` and return `MOVE_FIXED_CELL`.
3. Temporarily clear the cell's current value. This lets a player overwrite
   their **own** earlier entry without it being flagged as a self-conflict.
4. Check `rowHas` / `colHas` / `boxHas`. If the value already exists elsewhere
   in the same row, column, or 3×3 box, restore the old value, decrement
   `mistakes`, and return `MOVE_CONFLICT`.
5. Otherwise write the value and return `MOVE_OK`.

`clearCell(row, col)` erases a player-placed value; it refuses on given cells
and returns `false`.

### Constraint checks

- `rowHas(row, value)` — scans the 9 cells of that row.
- `colHas(col, value)` — scans the 9 cells of that column.
- `boxHas(row, col, value)` — computes the 3×3 box origin with
  `(row/3)*3`, `(col/3)*3` and scans the 9 cells of that box.

These enforce the classic Sudoku rule: each digit 1–9 appears once per row,
once per column, and once per box.

## Win / loss detection

- `isBoardFilled()` — no cell is `0`.
- `isWon()` — board is filled **and** no cell is a duplicate. `cellIsDuplicate`
  counts occurrences of a cell's value in its row, column, and box; more than
  one anywhere means a duplicate. (Because `placeValue` blocks conflicts on
  entry, a filled board is normally already valid, but the check is
  authoritative.)
- `isLost()` — `mistakes <= 0`.
- `mistakesLeft()` — attempts remaining, shown as the "Attempts" counter.

## GUI flow (`sudoku_gui.cpp`)

The GUI is a single render loop with two screens.

### Screens

- `SCREEN_MENU` — title, subtitle, and the four menu buttons:
  **New Game**, **Load Old Game**, **How to Play**, **Quit**.
- `SCREEN_GAME` — the header (title + a single **Save Game** button), the
  **Attempts** status line, and the 9×9 board.

`GameState` tracks `PLAYING` / `WON` / `LOST` and drives the game-over overlay.

### Menu actions

- **New Game** (`N`) — picks a random built-in puzzle (avoiding an immediate
  repeat) via `loadFromString`.
- **Load Old Game** (`L`) — restores `savegame.txt` via `loadFromFile`; if the
  loaded state is already won/lost it shows the matching overlay.
- **How to Play** (`H`) — the help overlay (also reachable in-game with `H`).
- **Quit** — exits the loop.

### In-game input (only while `PLAYING`)

- Left-click a cell, or arrow keys, to move the selection.
- `1`–`9` (top row or keypad) → `placeValue`. On a given cell it just flashes
  feedback (no penalty in the UI path); a conflict flashes and costs an attempt.
- `Backspace`/`Delete` → `clearCell`.
- The **Save Game** button writes `savegame.txt`.

### Feedback & rendering

- `ErrorFlash` darkens the offending cell and blinks the rejected digit for a
  short time after a bad move.
- The board auto-sizes to the largest centered square that fits below the
  header/status area, so everything scales when the window resizes or goes
  fullscreen (`uiScale` grows fonts and bars with window height).
- Sound effects play for select / place / error / erase / menu / win / lose
  (toggle with `U`).

### Global shortcuts

`F11` fullscreen · `ESC` back to menu (from the game) · `H` help ·
`U` sound on/off · `N` new game · `S` save. You can also **drag & drop** a
puzzle or save `.txt` onto the window to load it on either screen.

## Extending the game

Because all rules live in `SudokuGame`, adding a new frontend (Qt, SFML, web,
etc.) means only driving this API: `loadFrom*`, `placeValue`, `clearCell`,
`getCell`, `isFixedCell`, `mistakesLeft`, `isWon`, `isLost`, and `saveToFile`.
No rule logic needs to be reimplemented or duplicated.
