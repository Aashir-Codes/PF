# Sudoku Game

A Sudoku game written in C++ with two frontends: a raylib GUI and the original console version. All game rules live in `sudoku_game.h` / `sudoku_game.cpp`, shared by both.

## GUI Version (raylib)

### Build & Run
```
g++ sudoku_gui.cpp sudoku_game.cpp -o sudoku_gui -lraylib -lm -lpthread -ldl -lX11
./sudoku_gui
```

### Controls
- Click a cell to select it (arrow keys also move the selection)
- Type `1`-`9` to place a number, `Backspace`/`Delete` to erase your own numbers
- Gray cells are given and cannot be changed
- A wrong number costs one attempt — you have 10

### Main Menu
**New Game** · **Load Old Game** (restores `savegame.txt`) · **How to Play** · **Quit**

The only button on the board itself is **Save Game**; `ESC` returns to the menu.

### Shortcuts
| Action | Button | Key |
|---|---|---|
| New game (random built-in puzzle) | New Game | `N` |
| Load saved game (`savegame.txt`) | Load Old Game | `L` |
| Save current game | Save Game | `S` |
| Instructions | How to Play | `H` |
| Back to menu | — | `ESC` |
| Fullscreen toggle | — | `F11` |
| Sound on/off | — | `U` |

You can also **drag & drop** a puzzle or save `.txt` file onto the window to load it.
Minimize/maximize/close use the normal OS title bar; the window is freely resizable and the board scales with it.

## Console Version

```
g++ sudoko.cpp sudoku_game.cpp -o sudoku
./sudoku
```
Enter row, column, and value (1-9). Enter 10 to quit.

## Puzzle File Format

81 digits, `0` = empty cell. Whitespace/newlines are ignored:
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

## Assets
- Sound effects: [Kenney Interface Sounds](https://kenney.nl/assets/interface-sounds) (CC0 / public domain)
- Font: [Poppins](https://fonts.google.com/specimen/Poppins) (SIL Open Font License)
