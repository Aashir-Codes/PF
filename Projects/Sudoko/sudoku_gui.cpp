// Raylib GUI for Sudoku. All game rules live in SudokuGame (sudoku_game.h/.cpp).
//
// Build:  g++ sudoku_gui.cpp sudoku_game.cpp -o sudoku_gui -lraylib -lm -lpthread -ldl -lX11
//
// Main menu: New Game / Load Old Game / How to Play / Quit.
// In game: click a cell, type 1-9, Backspace/Delete erases. The only board
// button is Save Game (writes savegame.txt); ESC returns to the menu, H toggles
// help, F11 fullscreen. Drag & drop a puzzle or save .txt onto the window to load.
#include "raylib.h"
#include "sudoku_game.h"
#include <string>
#include <cstdio>

// ---------- theme: strict monochrome ----------
static const Color COL_BG         = { 255, 255, 255, 255 };
static const Color COL_LINES      = {  26,  26,  26, 255 };
static const Color COL_GIVEN_BG   = { 239, 239, 239, 255 };
static const Color COL_GIVEN_TXT  = {  26,  26,  26, 255 };
static const Color COL_PLAYER_TXT = {  85,  85,  85, 255 };
static const Color COL_HEADER     = {  43,  43,  43, 255 };
static const Color COL_HEADER_TXT = { 245, 245, 245, 255 };
static const Color COL_BTN        = {  58,  58,  58, 255 };
static const Color COL_BTN_HOVER  = {  82,  82,  82, 255 };
static const Color COL_BTN_EDGE   = {  95,  95,  95, 255 };
static const Color COL_ERROR_BG   = { 205, 205, 205, 255 };
static const Color COL_STATUS_TXT = {  60,  60,  60, 255 };

static const int   MAX_ATTEMPTS = 10;
static const float ERROR_TIME   = 0.8f;
static const char* SAVE_PATH    = "savegame.txt";

// A few built-in puzzles for "New Game" (0 = empty cell).
static const char* PUZZLES[] = {
	"530070000600195000098000060800060003400803001700020006060000280000419005000080079",
	"200080300060070084030500209000105408000000000402706000301007040720040060004010003",
	"000000907000420180000705026100904000050000040000507009920108000034059000507000000",
	"030050040008010500460000012070502080000603000040109030250000098001020600080060020",
};
static const int PUZZLE_COUNT = 4;

static Font  uiFont;
static Font  digitFont;
static Sound sndSelect, sndPlace, sndError, sndErase, sndMenu, sndWin, sndLose;
static bool  soundOn = true;

enum Screen    { SCREEN_MENU, SCREEN_GAME };
enum GameState { PLAYING, WON, LOST };

// Wrong-entry feedback: cell darkens and the rejected digit blinks.
struct ErrorFlash {
	bool  active;
	int   row, col, value; // value 0 = just darken (typed on a given cell)
	float t;
};

static void playSfx(Sound s) {
	if (soundOn) PlaySound(s);
}

static void drawTextCentered(Font f, const char* text, Rectangle r, float size, Color c) {
	Vector2 m = MeasureTextEx(f, text, size, 0);
	Vector2 pos = { r.x + (r.width - m.x) / 2, r.y + (r.height - m.y) / 2 };
	DrawTextEx(f, text, pos, size, 0, c);
}

static bool button(Rectangle r, const char* label, float textSize) {
	bool hover = CheckCollisionPointRec(GetMousePosition(), r);
	DrawRectangleRec(r, hover ? COL_BTN_HOVER : COL_BTN);
	DrawRectangleLinesEx(r, 1, COL_BTN_EDGE);
	drawTextCentered(uiFont, label, r, textSize, COL_HEADER_TXT);
	if (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		playSfx(sndMenu);
		return true;
	}
	return false;
}

static void toggleFullscreenMode() {
#if defined(RAYLIB_VERSION_MAJOR) && (RAYLIB_VERSION_MAJOR >= 5)
	ToggleBorderlessWindowed();
#else
	ToggleFullscreen();
#endif
}

// UI scale factor so text and bars grow with the window (fullscreen readability).
static float uiScale(int winH) {
	float s = winH / 800.0f;
	if (s < 0.85f) s = 0.85f;
	if (s > 2.2f)  s = 2.2f;
	return s;
}

// Largest centered square that fits below the header and status line.
static Rectangle boardArea(int winW, int winH, float headerH, float statusH) {
	float top    = headerH + statusH;
	float margin = 16.0f;
	float availW = winW - margin * 2;
	float availH = winH - top - margin;
	float size   = availW < availH ? availW : availH;
	if (size < 100) size = 100;
	Rectangle r = { margin + (availW - size) / 2, top + (availH - size) / 2, size, size };
	return r;
}

static void drawBoard(const SudokuGame& game, Rectangle b, int selRow, int selCol,
                      const ErrorFlash& err) {
	float cell = b.width / 9.0f;
	float thin  = cell * 0.02f;  if (thin < 1)  thin = 1;
	float thick = cell * 0.09f;  if (thick < 3) thick = 3;

	DrawRectangleRec(b, COL_BG);

	// cell fills
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			Rectangle cr = { b.x + j * cell, b.y + i * cell, cell, cell };
			if (err.active && err.row == i && err.col == j) {
				DrawRectangleRec(cr, COL_ERROR_BG);
			}
			else if (game.isFixedCell(i, j)) {
				DrawRectangleRec(cr, COL_GIVEN_BG);
			}
		}
	}

	// thin inner lines
	for (int k = 1; k < 9; k++) {
		if (k % 3 == 0) continue;
		DrawLineEx(Vector2{ b.x + k * cell, b.y }, Vector2{ b.x + k * cell, b.y + b.height }, thin, COL_LINES);
		DrawLineEx(Vector2{ b.x, b.y + k * cell }, Vector2{ b.x + b.width, b.y + k * cell }, thin, COL_LINES);
	}
	// thick 3x3 lines + border
	for (int k = 3; k < 9; k += 3) {
		DrawLineEx(Vector2{ b.x + k * cell, b.y }, Vector2{ b.x + k * cell, b.y + b.height }, thick, COL_LINES);
		DrawLineEx(Vector2{ b.x, b.y + k * cell }, Vector2{ b.x + b.width, b.y + k * cell }, thick, COL_LINES);
	}
	DrawRectangleLinesEx(Rectangle{ b.x - thick / 2, b.y - thick / 2, b.width + thick, b.height + thick }, thick, COL_LINES);

	// digits
	float digitSize = cell * 0.52f;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int v = game.getCell(i, j);
			Rectangle cr = { b.x + j * cell, b.y + i * cell, cell, cell };

			// blink the rejected digit inside the flashing cell
			if (err.active && err.row == i && err.col == j) {
				bool visible = ((int)(err.t * 8) % 2) == 0;
				int shown = (err.value != 0) ? err.value : v;
				if (visible && shown != 0) {
					char txt[2] = { (char)('0' + shown), 0 };
					drawTextCentered(digitFont, txt, cr, digitSize, COL_PLAYER_TXT);
				}
				continue;
			}
			if (v != 0) {
				char txt[2] = { (char)('0' + v), 0 };
				drawTextCentered(digitFont, txt, cr, digitSize,
				                 game.isFixedCell(i, j) ? COL_GIVEN_TXT : COL_PLAYER_TXT);
			}
		}
	}

	// selection: thick black outline
	if (selRow >= 0 && selCol >= 0) {
		float selThick = cell * 0.06f; if (selThick < 3) selThick = 3;
		Rectangle cr = { b.x + selCol * cell, b.y + selRow * cell, cell, cell };
		DrawRectangleLinesEx(cr, selThick, COL_LINES);
	}
}

static void drawHelpOverlay(int winW, int winH, float s) {
	static const char* LINES[] = {
		"HOW TO PLAY",
		"",
		"Fill every row, column and 3x3 box with the digits 1-9,",
		"with no digit repeating.",
		"",
		"- Click a cell to select it (arrow keys also move).",
		"- Type 1-9 to place a number.",
		"- Backspace or Delete erases your own numbers.",
		"- Gray cells are given and cannot be changed.",
		"- A wrong number costs one attempt. You have 10.",
		"",
		"Save Game stores your progress in savegame.txt;",
		"load it later from the main menu.",
		"",
		"Shortcuts:  F11 fullscreen   ESC back to menu",
		"            S save   U sound on/off   H this help",
		"Tip: drag & drop a puzzle or save .txt onto the window.",
		"",
		"Click anywhere or press ESC to close",
	};
	int lineCount = (int)(sizeof(LINES) / sizeof(LINES[0]));

	float titleSize = 32 * s;
	float lineSize  = 21 * s;
	float lineStep  = 30 * s;

	DrawRectangle(0, 0, winW, winH, Color{ 0, 0, 0, 160 });
	float panelW = 720 * s, panelH = 70 * s + lineCount * lineStep;
	if (panelW > winW - 40) panelW = (float)winW - 40;
	if (panelH > winH - 40) panelH = (float)winH - 40;
	Rectangle panel = { (winW - panelW) / 2, (winH - panelH) / 2, panelW, panelH };
	DrawRectangleRec(panel, COL_BG);
	DrawRectangleLinesEx(panel, 3, COL_LINES);

	float y = panel.y + 28 * s;
	for (int i = 0; i < lineCount; i++) {
		float size = (i == 0) ? titleSize : lineSize;
		Vector2 m = MeasureTextEx(uiFont, LINES[i], size, 0);
		float x = (i == 0) ? panel.x + (panel.width - m.x) / 2 : panel.x + 36 * s;
		DrawTextEx(uiFont, LINES[i], Vector2{ x, y }, size, 0, COL_LINES);
		y += (i == 0) ? 42 * s : lineStep;
	}
}

static void drawGameOverOverlay(int winW, int winH, bool won, float s) {
	DrawRectangle(0, 0, winW, winH, Color{ 0, 0, 0, 160 });
	float panelW = 560 * s, panelH = 240 * s;
	Rectangle panel = { (winW - panelW) / 2, (winH - panelH) / 2, panelW, panelH };
	DrawRectangleRec(panel, COL_BG);
	DrawRectangleLinesEx(panel, 3, COL_LINES);
	Rectangle titleR = { panel.x, panel.y + 34 * s, panel.width, 56 * s };
	drawTextCentered(uiFont, won ? "You Won!" : "Out of Attempts!", titleR, 44 * s, COL_LINES);
	Rectangle hintR = { panel.x, panel.y + 130 * s, panel.width, 36 * s };
	drawTextCentered(uiFont, "Press ESC for the menu or N for a new game", hintR, 21 * s, COL_PLAYER_TXT);
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	InitWindow(900, 780, "Sudoku");
	SetWindowMinSize(700, 600);
	SetTargetFPS(60);
	SetExitKey(KEY_NULL); // ESC navigates, never quits directly

	InitAudioDevice();
	sndSelect = LoadSound("assets/sfx/select.ogg");
	sndPlace  = LoadSound("assets/sfx/place.ogg");
	sndError  = LoadSound("assets/sfx/error.ogg");
	sndErase  = LoadSound("assets/sfx/erase.ogg");
	sndMenu   = LoadSound("assets/sfx/menu.ogg");
	sndWin    = LoadSound("assets/sfx/win.ogg");
	sndLose   = LoadSound("assets/sfx/lose.ogg");
	SetSoundVolume(sndSelect, 0.5f);

	uiFont    = LoadFontEx("assets/fonts/Poppins-Medium.ttf", 72, NULL, 0);
	digitFont = LoadFontEx("assets/fonts/Poppins-Regular.ttf", 128, NULL, 0);
	SetTextureFilter(uiFont.texture, TEXTURE_FILTER_BILINEAR);
	SetTextureFilter(digitFont.texture, TEXTURE_FILTER_BILINEAR);

	SudokuGame game;
	int         puzzleIndex = -1;
	Screen      screen = SCREEN_MENU;
	GameState   state = PLAYING;
	bool        gameActive = false; // a game exists behind the menu (Resume)
	int         selRow = -1, selCol = -1;
	bool        showHelp = false;
	bool        quitRequested = false;
	ErrorFlash  err = { false, 0, 0, 0, 0 };
	std::string message;
	float       msgTimer = 0;

	while (!WindowShouldClose() && !quitRequested) {
		float dt   = GetFrameTime();
		int   winW = GetScreenWidth();
		int   winH = GetScreenHeight();
		float s    = uiScale(winH);

		if (err.active) {
			err.t += dt;
			if (err.t >= ERROR_TIME) err.active = false;
		}
		if (msgTimer > 0) msgTimer -= dt;

		// ---------- global shortcuts ----------
		if (IsKeyPressed(KEY_F11)) toggleFullscreenMode();
		if (IsKeyPressed(KEY_U)) {
			soundOn = !soundOn;
			message = soundOn ? "Sound on" : "Sound off";
			msgTimer = 2;
		}
		if (IsKeyPressed(KEY_H)) showHelp = !showHelp;

		bool doNewGame = false, doLoadSave = false, doSave = false;

		// drag & drop a puzzle or save file (works on both screens)
		if (IsFileDropped()) {
			FilePathList files = LoadDroppedFiles();
			if (files.count > 0) {
				if (game.loadFromFile(files.paths[0])) {
					screen = SCREEN_GAME; state = PLAYING; gameActive = true;
					selRow = selCol = -1; err.active = false;
					if (game.isLost()) state = LOST;
					else if (game.isWon()) state = WON;
					message = std::string("Loaded ") + GetFileName(files.paths[0]);
				}
				else {
					message = "Invalid file (puzzle needs 81 digits, 0 = empty)";
				}
				msgTimer = 3;
			}
			UnloadDroppedFiles(files);
		}

		// ================================================================
		//                          MAIN MENU
		// ================================================================
		if (screen == SCREEN_MENU) {
			if (showHelp && (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
				showHelp = false;
			}
			if (!showHelp) {
				if (IsKeyPressed(KEY_N)) doNewGame = true;
				if (IsKeyPressed(KEY_L)) doLoadSave = true;
				if (IsKeyPressed(KEY_ESCAPE) && gameActive) screen = SCREEN_GAME;
			}

			BeginDrawing();
			ClearBackground(COL_BG);

			// dark strips top and bottom, echoing the board theme
			float stripH = 14 * s;
			DrawRectangle(0, 0, winW, (int)stripH, COL_HEADER);
			DrawRectangle(0, winH - (int)stripH, winW, (int)stripH, COL_HEADER);

			// centered layout: title + buttons block, centered as one group
			const char* labels[4];
			int actions[4]; // 1 new, 3 load save, 4 help, 5 quit
			int count = 0;
			labels[count] = "New Game";        actions[count++] = 1;
			labels[count] = "Load Old Game";   actions[count++] = 3;
			labels[count] = "How to Play";     actions[count++] = 4;
			labels[count] = "Quit";            actions[count++] = 5;

			float titleSize = 84 * s;
			float subSize   = 24 * s;
			float btnW = 420 * s, btnH = 62 * s, gap = 18 * s;
			float blockH = titleSize + 14 * s + subSize + 46 * s + count * btnH + (count - 1) * gap;
			float y = (winH - blockH) / 2;

			Vector2 tm = MeasureTextEx(uiFont, "SUDOKU", titleSize, 0);
			DrawTextEx(uiFont, "SUDOKU", Vector2{ (winW - tm.x) / 2, y }, titleSize, 0, COL_LINES);
			y += titleSize + 14 * s;
			const char* sub = "\"Think Sharp. Play Smart.\"";
			Vector2 sm = MeasureTextEx(uiFont, sub, subSize, 0);
			DrawTextEx(uiFont, sub, Vector2{ (winW - sm.x) / 2, y }, subSize, 0, COL_PLAYER_TXT);
			y += subSize + 46 * s;

			int clicked = -1;
			for (int i = 0; i < count; i++) {
				Rectangle r = { (winW - btnW) / 2, y, btnW, btnH };
				if (!showHelp && button(r, labels[i], 26 * s)) clicked = actions[i];
				y += btnH + gap;
			}

			if (msgTimer > 0 && !message.empty()) {
				Vector2 m = MeasureTextEx(uiFont, message.c_str(), 22 * s, 0);
				DrawTextEx(uiFont, message.c_str(),
				           Vector2{ (winW - m.x) / 2, winH - stripH - 34 * s }, 22 * s, 0, COL_STATUS_TXT);
			}

			if (showHelp) drawHelpOverlay(winW, winH, s);
			EndDrawing();

			if (clicked == 0) screen = SCREEN_GAME;
			if (clicked == 1) doNewGame = true;
			if (clicked == 3) doLoadSave = true;
			if (clicked == 4) showHelp = true;
			if (clicked == 5) quitRequested = true;
		}
		// ================================================================
		//                            GAME
		// ================================================================
		else {
			float headerH = 68 * s;
			float statusH = 48 * s;
			Rectangle board = boardArea(winW, winH, headerH, statusH);
			float cellSize = board.width / 9.0f;

			if (showHelp) {
				if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					showHelp = false;
				}
			}
			else {
				if (IsKeyPressed(KEY_ESCAPE)) screen = SCREEN_MENU;
				if (IsKeyPressed(KEY_N)) doNewGame = true;
				if (IsKeyPressed(KEY_S)) doSave = true;
			}

			// gameplay input
			if (!showHelp && screen == SCREEN_GAME && state == PLAYING) {
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					Vector2 mp = GetMousePosition();
					if (CheckCollisionPointRec(mp, board)) {
						int c = (int)((mp.x - board.x) / cellSize);
						int r = (int)((mp.y - board.y) / cellSize);
						if (r > 8) r = 8;
						if (c > 8) c = 8;
						if (r != selRow || c != selCol) playSfx(sndSelect);
						selRow = r; selCol = c;
					}
				}
				if (selRow >= 0) {
					if (IsKeyPressed(KEY_UP)    && selRow > 0) selRow--;
					if (IsKeyPressed(KEY_DOWN)  && selRow < 8) selRow++;
					if (IsKeyPressed(KEY_LEFT)  && selCol > 0) selCol--;
					if (IsKeyPressed(KEY_RIGHT) && selCol < 8) selCol++;
				}

				int typed = 0;
				for (int d = 1; d <= 9; d++) {
					if (IsKeyPressed(KEY_ZERO + d) || IsKeyPressed(KEY_KP_0 + d)) typed = d;
				}

				if (typed != 0 && selRow >= 0) {
					if (game.isFixedCell(selRow, selCol)) {
						// typing on a given cell: feedback only, no attempt lost
						err.active = true; err.row = selRow; err.col = selCol;
						err.value = 0; err.t = 0;
						playSfx(sndError);
					}
					else {
						SudokuGame::MoveResult res = game.placeValue(selRow, selCol, typed);
						if (res == SudokuGame::MOVE_OK) {
							playSfx(sndPlace);
							if (game.isWon()) { state = WON; playSfx(sndWin); }
						}
						else if (res == SudokuGame::MOVE_CONFLICT) {
							err.active = true; err.row = selRow; err.col = selCol;
							err.value = typed; err.t = 0;
							playSfx(sndError);
							if (game.isLost()) { state = LOST; playSfx(sndLose); }
						}
					}
				}

				if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressed(KEY_DELETE)) && selRow >= 0) {
					if (game.getCell(selRow, selCol) != 0 && game.clearCell(selRow, selCol)) {
						playSfx(sndErase);
					}
				}
			}

			// ---------- draw ----------
			BeginDrawing();
			ClearBackground(COL_BG);

			DrawRectangle(0, 0, winW, (int)headerH, COL_HEADER);
			DrawTextEx(uiFont, "SUDOKU", Vector2{ 24 * s, (headerH - 34 * s) / 2 }, 34 * s, 0, COL_HEADER_TXT);

			// only a Save Game button lives on the board; ESC returns to the menu,
			// H toggles the How-to-Play overlay.
			float bh = 44 * s, by = (headerH - bh) / 2;
			float bx = winW - 24 * s - 160 * s;
			bool clickSave = button(Rectangle{ bx, by, 160 * s, bh }, "Save Game", 22 * s);

			// status line: attempts + transient message
			char status[64];
			snprintf(status, sizeof(status), "Attempts: %d / %d", game.mistakesLeft(), MAX_ATTEMPTS);
			DrawTextEx(uiFont, status, Vector2{ 24 * s, headerH + 8 * s }, 34 * s, 0, COL_STATUS_TXT);
			if (msgTimer > 0 && !message.empty()) {
				Vector2 m = MeasureTextEx(uiFont, message.c_str(), 24 * s, 0);
				DrawTextEx(uiFont, message.c_str(),
				           Vector2{ winW - m.x - 24 * s, headerH + 10 * s }, 24 * s, 0, COL_STATUS_TXT);
			}

			drawBoard(game, board, (state == PLAYING && !showHelp) ? selRow : -1,
			          (state == PLAYING && !showHelp) ? selCol : -1, err);

			if (state != PLAYING) drawGameOverOverlay(winW, winH, state == WON, s);
			if (showHelp) drawHelpOverlay(winW, winH, s);

			EndDrawing();

			if (!showHelp) {
				if (clickSave) doSave = true;
			}
		}

		// ---------- shared actions ----------
		if (doNewGame) {
			int next = GetRandomValue(0, PUZZLE_COUNT - 1);
			if (next == puzzleIndex) next = (next + 1) % PUZZLE_COUNT;
			puzzleIndex = next;
			game.loadFromString(PUZZLES[puzzleIndex]);
			screen = SCREEN_GAME; state = PLAYING; gameActive = true;
			selRow = selCol = -1; err.active = false;
			message = "New game started"; msgTimer = 2;
		}
		if (doLoadSave) {
			if (game.loadFromFile(SAVE_PATH)) {
				screen = SCREEN_GAME; gameActive = true;
				state = PLAYING;
				if (game.isLost()) state = LOST;
				else if (game.isWon()) state = WON;
				selRow = selCol = -1; err.active = false;
				message = "Saved game loaded";
			}
			else {
				message = "Could not load savegame.txt";
			}
			msgTimer = 3;
		}
		if (doSave) {
			if (game.saveToFile(SAVE_PATH)) {
				message = "Game saved to savegame.txt";
			}
			else {
				message = "Could not write savegame.txt";
			}
			msgTimer = 3;
		}
	}

	UnloadFont(uiFont);
	UnloadFont(digitFont);
	UnloadSound(sndSelect); UnloadSound(sndPlace); UnloadSound(sndError);
	UnloadSound(sndErase);  UnloadSound(sndMenu);  UnloadSound(sndWin);
	UnloadSound(sndLose);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
