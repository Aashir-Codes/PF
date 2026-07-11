// =============================================================
//  gomoku.cpp  —  Gomoku (Five in a Row), Raylib GUI
//
//  Mouse-driven, minimal front-end for the BSCS25079 console
//  engine. Slate chrome + a clean light board, glossy stones,
//  DejaVu Sans typography, undo, and save / load to a .txt file.
//
//  Build (Linux):
//    ./build.sh
//    g++ gomoku.cpp -o gomoku -I/usr/local/include -L/usr/local/lib \
//        -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
//  Build (MinGW / Windows):
//    g++ gomoku.cpp -o gomoku -lraylib -lopengl32 -lgdi32 -lwinmm
//
//  Controls:
//    Mouse  — everything      U — undo      Ctrl+S — save
//    F — fullscreen           Esc — back to menu
// =============================================================

#include "raylib.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// ─────────────────────────────────────────────────────────────
//  Engine (adapted from BSCS25079_PFX_PROJECT2.cpp)
// ─────────────────────────────────────────────────────────────
#define MAXN 30

static char Board[MAXN][MAXN];
static int  R = 15, C = 15;
static int  winC = 5;
static int  NOP  = 2;
static int  turn = 1;                       // 1-based current player
static char Psym[2]   = {'X', 'O'};
static char PNames[2][64] = {"Player 1", "Player 2"};
static int  last_r = -1, last_c = -1;

static bool inb(int r, int c)   { return r >= 0 && r < R && c >= 0 && c < C; }
static bool valid(int r, int c) { return inb(r, c) && Board[r][c] == '.'; }

static int countDir(int r, int c, char s, int dr, int dc) {
    int n = 0, i = r + dr, j = c + dc;
    while (inb(i, j) && Board[i][j] == s) { n++; i += dr; j += dc; }
    return n;
}
static bool win(int r, int c, char s) {
    const int d[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    for (auto &v : d)
        if (1 + countDir(r,c,s,v[0],v[1]) + countDir(r,c,s,-v[0],-v[1]) >= winC) return true;
    return false;
}
static bool boardFull() {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (Board[i][j] == '.') return false;
    return true;
}
static void clearBoard() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++) Board[i][j] = '.';
}

// AI: win → block → play near existing stones → random
static bool canWinAt(char s, int &r, int &c) {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (valid(i, j)) {
                Board[i][j] = s;
                bool w = win(i, j, s);
                Board[i][j] = '.';
                if (w) { r = i; c = j; return true; }
            }
    return false;
}
static bool neighbourMove(int &r, int &c) {
    int best = -1;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (!valid(i, j)) continue;
            int adj = 0;
            for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++) {
                    if (!di && !dj) continue;
                    if (inb(i+di, j+dj) && Board[i+di][j+dj] != '.') adj++;
                }
            if (adj > best) { best = adj; r = i; c = j; }
        }
    return best > 0;
}
static void robotMove(int &r, int &c) {
    if (canWinAt(Psym[1], r, c)) return;
    if (canWinAt(Psym[0], r, c)) return;
    if (neighbourMove(r, c))     return;
    do { r = GetRandomValue(0, R-1); c = GetRandomValue(0, C-1); } while (!valid(r, c));
}

// ─────────────────────────────────────────────────────────────
//  App state
// ─────────────────────────────────────────────────────────────
enum Screen { MENU, SETUP, GAME, GAMEOVER };
static Screen screen = MENU;
enum Mode  { HVH, HVA };
static Mode  mode = HVH;

static bool gameOver = false, isDraw = false;
static int  winner = 0;

struct Cell { int r, c; };
static vector<Cell> winLine;
static vector<Cell> history;

static char p1Name[64] = "Player 1";
static char p2Name[64] = "Player 2";
static int  selN   = 15;
static int  selWin = 5;
static int  activeField = -1;

static float robotTimer = 0.f;
static float placeAnim  = 1.f;

static char  notif[128] = {};
static float notifTimer = 0.f;
static void  setNotif(const char *m, float t = 2.0f) {
    strncpy(notif, m, sizeof(notif)-1); notif[sizeof(notif)-1] = 0; notifTimer = t;
}

static const char *SAVE_PATH = "gomoku_save.txt";

// ─────────────────────────────────────────────────────────────
//  Palette — slate chrome + clean light board
// ─────────────────────────────────────────────────────────────
static const Color BG_TOP     = { 20,  23,  32, 255};
static const Color BG_BOT     = { 13,  15,  21, 255};
static const Color PANEL       = { 22,  25,  34, 255};
static const Color PANEL_HI    = { 30,  34,  45, 255};   // raised card
static const Color PANEL_LINE  = { 44,  49,  63, 255};
static const Color BOARD_BG    = {233, 235, 240, 255};   // light board
static const Color BOARD_EDGE  = {198, 202, 212, 255};
static const Color GRID        = {176, 182, 196, 255};
static const Color STAR        = {150, 158, 176, 255};
static const Color STONE_DARK  = { 30,  33,  42, 255};
static const Color STONE_LITE  = {252, 252, 254, 255};
static const Color ACCENT      = {108, 120, 255, 255};   // indigo
static const Color ACCENT_HI   = {134, 144, 255, 255};
static const Color ACCENT_LO   = { 82,  94, 222, 255};
static const Color ACCENT_SOFT = { 40,  45,  92, 255};   // subtle accent fill
static const Color HL_GOLD     = {242, 184,  86, 255};   // last move
static const Color TEXT        = {230, 233, 242, 255};
static const Color TEXT_DIM    = {132, 139, 156, 255};
static const Color DANGER      = {235, 108, 108, 255};

static const int MARGIN    = 34;
static int SIDEBAR_W = 288;

// ─────────────────────────────────────────────────────────────
//  Typography (DejaVu Sans, loaded at high res + smoothed)
// ─────────────────────────────────────────────────────────────
static Font FREG, FBOLD;

static void loadFonts() {
    const char *reg  = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
    const char *bold = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";
    FREG  = FileExists(reg)  ? LoadFontEx(reg,  72, 0, 0) : GetFontDefault();
    FBOLD = FileExists(bold) ? LoadFontEx(bold, 72, 0, 0) : FREG;
    if (FREG.texture.id)  SetTextureFilter(FREG.texture,  TEXTURE_FILTER_BILINEAR);
    if (FBOLD.texture.id) SetTextureFilter(FBOLD.texture, TEXTURE_FILTER_BILINEAR);
}

// text helpers — regular / bold / measure (spacing-aware)
static float TWs(Font f, const char *t, float fs, float sp) { return MeasureTextEx(f, t, fs, sp).x; }
static float TW (const char *t, int fs) { return MeasureTextEx(FREG, t, (float)fs, 0).x; }
static void  T  (const char *t, float x, float y, int fs, Color c) { DrawTextEx(FREG,  t, {x, y}, (float)fs, 0, c); }
static void  TB (const char *t, float x, float y, int fs, Color c) { DrawTextEx(FBOLD, t, {x, y}, (float)fs, 0, c); }
// centered helpers
static void  TC (const char *t, float cx, float y, int fs, Color c) { T (t, cx - TW(t,fs)/2, y, fs, c); }
static void  TBC(const char *t, float cx, float y, int fs, Color c) { TB(t, cx - TWs(FBOLD,t,(float)fs,0)/2, y, fs, c); }

// ─────────────────────────────────────────────────────────────
//  UI widgets
// ─────────────────────────────────────────────────────────────
enum BtnKind { PRIMARY, GHOST, BTN_RED };

static bool Button(Rectangle r, const char *txt, int fs, BtnKind kind = GHOST, bool enabled = true) {
    Vector2 m = GetMousePosition();
    bool hover = enabled && CheckCollisionPointRec(m, r);
    bool press = hover && IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    Color bg, tc = TEXT, border = {0,0,0,0};
    if (kind == PRIMARY) {
        bg = press ? ACCENT_LO : (hover ? ACCENT_HI : ACCENT);
        tc = WHITE;
    } else if (kind == BTN_RED) {
        bg = press ? DANGER : (hover ? Fade(DANGER, 0.20f) : PANEL_HI);
        tc = press ? WHITE : DANGER;  border = Fade(DANGER, hover ? 0.9f : 0.45f);
    } else {
        bg = press ? PANEL_LINE : (hover ? PANEL_HI : PANEL);
        border = hover ? ACCENT : PANEL_LINE;
    }
    if (!enabled) { bg = Fade(PANEL, 0.5f); tc = Fade(TEXT_DIM, 0.6f); border = Fade(PANEL_LINE, 0.5f); }

    DrawRectangleRounded(r, 0.32f, 10, bg);
    if (kind != PRIMARY || !enabled)
        DrawRectangleRoundedLinesEx(r, 0.32f, 10, 1.5f, border);

    T(txt, r.x + (r.width - TW(txt,fs))/2, r.y + (r.height - fs)/2 - 1, fs, tc);
    return enabled && hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

static bool Chip(Rectangle r, const char *txt, int fs, bool selected) {
    Vector2 m = GetMousePosition();
    bool hover = CheckCollisionPointRec(m, r);
    Color bg = selected ? ACCENT_SOFT : (hover ? PANEL_HI : PANEL);
    DrawRectangleRounded(r, 0.36f, 10, bg);
    DrawRectangleRoundedLinesEx(r, 0.36f, 10, 1.5f,
        selected ? ACCENT : Fade(PANEL_LINE, hover ? 1.f : 0.6f));
    T(txt, r.x + (r.width - TW(txt,fs))/2, r.y + (r.height - fs)/2 - 1, fs,
      selected ? TEXT : TEXT_DIM);
    return hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

static void TextField(const char *label, char *buf, int bufSz, Rectangle r, int id) {
    Vector2 m = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        bool inside = CheckCollisionPointRec(m, r);
        if (inside) activeField = id;
        else if (activeField == id) activeField = -1;
    }
    bool focused = (activeField == id);
    if (focused) {
        int len = (int)strlen(buf), k = GetCharPressed();
        while (k > 0) {
            if (k >= 32 && k < 127 && len < bufSz-1) { buf[len++] = (char)k; buf[len] = 0; }
            k = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && len > 0) buf[len-1] = 0;
    }
    T(label, r.x, r.y - 22, 15, TEXT_DIM);
    DrawRectangleRounded(r, 0.28f, 8, PANEL);
    DrawRectangleRoundedLinesEx(r, 0.28f, 8, 1.5f, focused ? ACCENT : PANEL_LINE);
    char disp[80];
    bool caret = focused && fmodf(GetTime(), 1.0f) < 0.5f;
    snprintf(disp, sizeof(disp), "%s%s", buf, caret ? "|" : "");
    T(disp, r.x + 14, r.y + r.height/2 - 9, 17, TEXT);
}

// glossy stone with soft shadow
static void drawStone(float cx, float cy, float rad, int player, float scale = 1.f) {
    rad *= scale;
    if (rad < 1) return;
    bool dark = (player == 0);
    DrawCircle((int)(cx + rad*0.05f), (int)(cy + rad*0.16f), rad, Fade(BLACK, 0.30f)); // shadow
    DrawCircle((int)cx, (int)cy, rad, dark ? STONE_DARK : STONE_LITE);                 // body
    if (dark) {
        DrawRing({cx, cy}, rad-2, rad, 0, 360, 48, Fade((Color){96,104,132,255}, 0.45f));
        DrawCircle((int)(cx - rad*0.30f), (int)(cy - rad*0.34f), rad*0.34f, Fade((Color){126,134,162,255}, 0.5f));
    } else {
        DrawRing({cx, cy}, rad-2, rad, 0, 360, 48, Fade((Color){198,202,214,255}, 0.9f));
        DrawCircle((int)(cx - rad*0.30f), (int)(cy - rad*0.34f), rad*0.34f, Fade(WHITE, 0.95f));
    }
}

static int playerOf(char ch) { return (ch == Psym[0]) ? 0 : 1; }

static void drawBackground() {
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), BG_TOP, BG_BOT);
}

// ─────────────────────────────────────────────────────────────
//  Game flow
// ─────────────────────────────────────────────────────────────
static void startNewGame() {
    R = C = selN;
    winC = min(selWin, R);
    NOP = 2;
    strncpy(PNames[0], p1Name[0] ? p1Name : "Player 1", 63); PNames[0][63] = 0;
    Psym[0] = 'X';
    if (mode == HVA) { strcpy(PNames[1], "Annie (AI)"); Psym[1] = 'A'; }
    else { strncpy(PNames[1], p2Name[0] ? p2Name : "Player 2", 63); PNames[1][63] = 0; Psym[1] = 'O'; }
    clearBoard();
    history.clear(); winLine.clear();
    turn = GetRandomValue(1, 2);
    last_r = last_c = -1;
    gameOver = isDraw = false; winner = 0;
    robotTimer = 0.f; placeAnim = 1.f;
}

static void captureWinLine(int r, int c, char s) {
    winLine.clear();
    const int d[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    for (auto &v : d) {
        int f = countDir(r, c, s, v[0], v[1]);
        int b = countDir(r, c, s, -v[0], -v[1]);
        if (1 + f + b >= winC) {
            for (int k = -b; k <= f; k++) winLine.push_back({r + k*v[0], c + k*v[1]});
            return;
        }
    }
}

static void placePiece(int r, int c) {
    Board[r][c] = Psym[turn-1];
    history.push_back({r, c});
    last_r = r; last_c = c; placeAnim = 0.f;
    char s = Psym[turn-1];
    if (win(r, c, s))       { captureWinLine(r, c, s); gameOver = true; winner = turn; screen = GAMEOVER; }
    else if (boardFull())   { gameOver = true; isDraw = true; screen = GAMEOVER; }
    else                    { turn = (turn % NOP) + 1; }
}

static void undoMove() {
    if (history.empty()) { setNotif("Nothing to undo"); return; }
    int steps = (mode == HVA && history.size() >= 2) ? 2 : 1;
    for (int k = 0; k < steps && !history.empty(); k++) {
        Cell m = history.back(); history.pop_back();
        Board[m.r][m.c] = '.';
    }
    if (history.empty()) { last_r = last_c = -1; turn = 1; }
    else {
        last_r = history.back().r; last_c = history.back().c;
        turn = (playerOf(Board[last_r][last_c]) + 1) % NOP + 1;
    }
    gameOver = isDraw = false; winner = 0; winLine.clear();
    robotTimer = 0.f;
    setNotif("Move undone");
}

// ─────────────────────────────────────────────────────────────
//  Save / Load (plain text)
// ─────────────────────────────────────────────────────────────
static void saveGame() {
    ofstream f(SAVE_PATH);
    if (!f) { setNotif("Save failed"); return; }
    f << (int)mode << " " << R << " " << C << " " << winC << " " << turn << " " << NOP << "\n";
    for (int p = 0; p < NOP; p++) f << PNames[p] << "\n" << Psym[p] << "\n";
    for (int i = 0; i < R; i++) { for (int j = 0; j < C; j++) f << Board[i][j]; f << "\n"; }
    f << history.size() << "\n";
    for (auto &m : history) f << m.r << " " << m.c << "\n";
    setNotif("Game saved");
}

static bool loadGame() {
    ifstream f(SAVE_PATH);
    if (!f) { setNotif("No saved game found"); return false; }
    int m;
    if (!(f >> m >> R >> C >> winC >> turn >> NOP)) { setNotif("Save file corrupt"); return false; }
    if (R < 1 || R > MAXN || C < 1 || C > MAXN || NOP < 1 || NOP > 2) { setNotif("Save file corrupt"); return false; }
    mode = (Mode)m;
    f.ignore();
    for (int p = 0; p < NOP; p++) {
        f.getline(PNames[p], 63);
        string sy; getline(f, sy); Psym[p] = sy.empty() ? '?' : sy[0];
    }
    clearBoard();
    for (int i = 0; i < R; i++) {
        string row; getline(f, row);
        for (int j = 0; j < C && j < (int)row.size(); j++) Board[i][j] = row[j];
    }
    history.clear();
    int n = 0; f >> n;
    for (int k = 0; k < n; k++) { Cell c; if (f >> c.r >> c.c) history.push_back(c); }
    last_r = last_c = -1;
    if (!history.empty()) { last_r = history.back().r; last_c = history.back().c; }
    gameOver = isDraw = false; winner = 0; winLine.clear();
    robotTimer = 0.f; placeAnim = 1.f;
    screen = GAME;
    setNotif("Game loaded");
    return true;
}

// ─────────────────────────────────────────────────────────────
//  Board geometry
// ─────────────────────────────────────────────────────────────
struct Geo { float ox, oy, gap, rad; };
static Geo boardGeo() {
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    int regionW = sw - SIDEBAR_W - MARGIN*2;
    int regionH = sh - MARGIN*2;
    int px = min(regionW, regionH);
    Geo g;
    g.gap = (float)px / (max(R, C) - 1);
    g.rad = g.gap * 0.44f;
    float bw = g.gap * (C-1), bh = g.gap * (R-1);
    g.ox = MARGIN + (regionW - bw) / 2.f;
    g.oy = MARGIN + (regionH - bh) / 2.f;
    return g;
}

// ─────────────────────────────────────────────────────────────
//  Screen: MENU
// ─────────────────────────────────────────────────────────────
static void drawMenu(bool &running) {
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    float cx = sw / 2.f;

    // title
    int tfs = (int)min(96.f, sw * 0.095f);
    const char *title = "GOMOKU";
    float sp = tfs * 0.06f;
    float tw = TWs(FBOLD, title, (float)tfs, sp);
    float ty = sh * 0.17f;
    DrawTextEx(FBOLD, title, {cx - tw/2, ty}, (float)tfs, sp, TEXT);
    // flanking stones
    float sr = tfs * 0.26f;
    drawStone(cx - tw/2 - sr*2.2f, ty + tfs*0.5f, sr, 0);
    drawStone(cx + tw/2 + sr*2.2f, ty + tfs*0.5f, sr, 1);
    // accent rule + tagline
    DrawRectangleRounded({cx - 34, ty + tfs + 14, 68, 4}, 1.f, 6, ACCENT);
    const char *tag = "F I V E   I N   A   R O W";
    TC(tag, cx, ty + tfs + 30, 15, TEXT_DIM);

    // button group card
    float bw = 360, bh = 58, gap = 14;
    float cardX = cx - bw/2 - 26, cardY = sh*0.44f - 26;
    float cardW = bw + 52, cardH = bh*3 + gap*2 + 52;
    DrawRectangleRounded({cardX, cardY, cardW, cardH}, 0.08f, 12, Fade(PANEL, 0.6f));
    DrawRectangleRoundedLinesEx({cardX, cardY, cardW, cardH}, 0.08f, 12, 1.5f, PANEL_LINE);

    float x = cx - bw/2, y = sh * 0.44f;
    int bf = 21;
    if (Button({x, y, bw, bh}, "New Game", bf, PRIMARY)) { activeField = -1; screen = SETUP; }
    y += bh + gap;
    bool hasSave = FileExists(SAVE_PATH);
    if (Button({x, y, bw, bh}, "Continue Saved Game", bf, GHOST, hasSave) && hasSave) loadGame();
    y += bh + gap;
    if (Button({x, y, bw, bh}, "Quit", bf, BTN_RED)) running = false;

    TC("Mouse to play   ·   F fullscreen   ·   Esc menu", cx, sh - 44, 14, TEXT_DIM);
}

// ─────────────────────────────────────────────────────────────
//  Screen: SETUP
// ─────────────────────────────────────────────────────────────
static void drawSetup() {
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    float cx = sw / 2.f;
    TBC("NEW GAME", cx, sh*0.07f, 40, TEXT);

    float panelW = 470, px = cx - panelW/2;
    float y = sh*0.19f;

    T("MODE", px, y, 14, TEXT_DIM); y += 24;
    float half = (panelW - 12) / 2;
    if (Chip({px, y, half, 50}, "Human vs Human", 18, mode == HVH)) mode = HVH;
    if (Chip({px + half + 12, y, half, 50}, "Human vs AI", 18, mode == HVA)) mode = HVA;
    y += 78;

    TextField("PLAYER 1 NAME", p1Name, 64, {px, y + 22, panelW, 46}, 1);
    y += 92;
    if (mode == HVH) { TextField("PLAYER 2 NAME", p2Name, 64, {px, y + 22, panelW, 46}, 2); y += 92; }
    else             { T("Opponent:  Annie (AI)", px, y, 16, TEXT_DIM); y += 46; }

    T("BOARD SIZE", px, y, 14, TEXT_DIM); y += 24;
    int sizes[] = {9, 13, 15, 19};
    float cw = (panelW - 3*12) / 4;
    for (int i = 0; i < 4; i++)
        if (Chip({px + i*(cw+12), y, cw, 48}, TextFormat("%dx%d", sizes[i], sizes[i]),
                 16, selN == sizes[i])) { selN = sizes[i]; if (selWin > selN) selWin = selN; }
    y += 76;

    T("WIN LENGTH", px, y, 14, TEXT_DIM); y += 24;
    int wins[] = {3, 4, 5, 6};
    for (int i = 0; i < 4; i++) {
        Rectangle r = {px + i*(cw+12), y, cw, 48};
        if (wins[i] <= selN) { if (Chip(r, TextFormat("%d", wins[i]), 16, selWin == wins[i])) selWin = wins[i]; }
        else { DrawRectangleRounded(r, 0.36f, 10, Fade(PANEL, 0.4f));
               TC(TextFormat("%d", wins[i]), r.x + r.width/2, r.y + 15, 16, Fade(TEXT_DIM, 0.4f)); }
    }
    y += 82;

    float bw = (panelW - 12) / 2;
    if (Button({px, y, bw, 54}, "Back", 20, GHOST)) { screen = MENU; activeField = -1; }
    if (Button({px + bw + 12, y, bw, 54}, "Start Game", 20, PRIMARY)) { startNewGame(); screen = GAME; activeField = -1; }
}

// ─────────────────────────────────────────────────────────────
//  Screen: GAME
// ─────────────────────────────────────────────────────────────
static void drawSidebar() {
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    float x = sw - SIDEBAR_W;
    DrawRectangle((int)x, 0, SIDEBAR_W, sh, PANEL);
    DrawLineEx({x, 0}, {x, (float)sh}, 1.f, PANEL_LINE);

    float px = x + 26, y = 32;
    TB("GOMOKU", px, y, 30, TEXT); y += 36;
    T(TextFormat("%d in a row   ·   %dx%d", winC, R, C), px, y, 14, TEXT_DIM); y += 34;
    DrawLineEx({px, y}, {(float)sw - 26, y}, 1.f, PANEL_LINE); y += 22;

    for (int p = 0; p < NOP; p++) {
        bool active = !gameOver && (turn-1) == p;
        Rectangle card = {px, y, (float)SIDEBAR_W - 52, 62};
        DrawRectangleRounded(card, 0.24f, 8, active ? ACCENT_SOFT : PANEL_HI);
        if (active) DrawRectangleRoundedLinesEx(card, 0.24f, 8, 1.6f, ACCENT);
        drawStone(card.x + 31, card.y + 31, 15, p);
        T(PNames[p], card.x + 58, card.y + 13, 18, active ? TEXT : TEXT_DIM);
        T(active ? "your turn" : TextFormat("symbol  %c", Psym[p]),
          card.x + 58, card.y + 36, 13, active ? ACCENT_HI : TEXT_DIM);
        y += 74;
    }

    y += 6;
    T(TextFormat("Moves played:  %d", (int)history.size()), px, y, 14, TEXT_DIM); y += 26;
    if (mode == HVA && !gameOver && turn == 2) {
        int d = ((int)(GetTime()*3)) % 4;
        char think[16] = "thinking";
        for (int i = 0; i < d; i++) strcat(think, ".");
        T(think, px, y, 15, ACCENT_HI);
    }
    y += 24;
    DrawLineEx({px, y}, {(float)sw - 26, y}, 1.f, PANEL_LINE); y += 20;

    float bw = SIDEBAR_W - 52, bh = 46, g = 12;
    bool human = !(mode == HVA && turn == 2);
    if (Button({px, y, bw, bh}, "Undo", 17, GHOST, !gameOver && human && !history.empty())) undoMove();
    y += bh + g;
    if (Button({px, y, bw, bh}, "Save Game", 17, GHOST)) saveGame();
    y += bh + g;
    if (Button({px, y, bw, bh}, "Load Game", 17, GHOST, FileExists(SAVE_PATH))) loadGame();
    y += bh + g;
    if (Button({px, y, bw, bh}, "New Game", 17, PRIMARY)) screen = SETUP;
    y += bh + g;
    if (Button({px, y, bw, bh}, "Main Menu", 17, GHOST)) screen = MENU;
}

static void drawBoard() {
    Geo g = boardGeo();
    float bw = g.gap * (C-1), bh = g.gap * (R-1);
    float pad = g.gap * 0.6f;
    Rectangle card = {g.ox - pad, g.oy - pad, bw + pad*2, bh + pad*2};

    // drop shadow + board card
    DrawRectangleRounded({card.x + 6, card.y + 10, card.width, card.height}, 0.04f, 10, Fade(BLACK, 0.28f));
    DrawRectangleRounded(card, 0.04f, 10, BOARD_BG);
    DrawRectangleRoundedLinesEx(card, 0.04f, 10, 1.5f, BOARD_EDGE);

    // grid
    for (int i = 0; i < R; i++) DrawLineEx({g.ox, g.oy + i*g.gap}, {g.ox + bw, g.oy + i*g.gap}, 1.3f, GRID);
    for (int j = 0; j < C; j++) DrawLineEx({g.ox + j*g.gap, g.oy}, {g.ox + j*g.gap, g.oy + bh}, 1.3f, GRID);

    // star points
    auto star = [&](int i, int j){ DrawCircle((int)(g.ox + j*g.gap), (int)(g.oy + i*g.gap), 4, STAR); };
    if (R==15 && C==15)      { int a[]={3,7,11}; for(int i:a)for(int j:a)star(i,j); }
    else if (R==19 && C==19) { int a[]={3,9,15}; for(int i:a)for(int j:a)star(i,j); }
    else if (R==13 && C==13) { int a[]={3,6,9};  for(int i:a)for(int j:a)star(i,j); }
    else if (R==9  && C==9)  { star(4,4); int a[]={2,6}; for(int i:a)for(int j:a)star(i,j); }

    // stones
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            if (Board[i][j] == '.') continue;
            float cx = g.ox + j*g.gap, cy = g.oy + i*g.gap;
            float sc = (i == last_r && j == last_c) ? (0.62f + 0.38f*placeAnim) : 1.f;
            drawStone(cx, cy, g.rad, playerOf(Board[i][j]), sc);
        }

    // last-move ring
    if (last_r >= 0 && Board[last_r][last_c] != '.' && !gameOver) {
        float cx = g.ox + last_c*g.gap, cy = g.oy + last_r*g.gap;
        DrawRing({cx, cy}, g.rad*0.30f, g.rad*0.44f, 0, 360, 32, HL_GOLD);
    }

    // winning line
    if (gameOver && !winLine.empty()) {
        float pulse = 0.5f + 0.5f*sinf(GetTime()*4);
        Cell a = winLine.front(), b = winLine.back();
        DrawLineEx({g.ox + a.c*g.gap, g.oy + a.r*g.gap}, {g.ox + b.c*g.gap, g.oy + b.r*g.gap},
                   4.f, Fade(ACCENT, 0.35f));
        for (auto &c : winLine) {
            float cx = g.ox + c.c*g.gap, cy = g.oy + c.r*g.gap;
            DrawRing({cx, cy}, g.rad*1.04f, g.rad*1.04f + 3, 0, 360, 40, Fade(ACCENT, 0.55f + 0.45f*pulse));
        }
    }

    // hover preview
    bool human = !(mode == HVA && turn == 2);
    if (!gameOver && human) {
        Vector2 m = GetMousePosition();
        int j = (int)roundf((m.x - g.ox) / g.gap);
        int i = (int)roundf((m.y - g.oy) / g.gap);
        if (inb(i, j) && Board[i][j] == '.' && m.x < GetScreenWidth() - SIDEBAR_W) {
            float cx = g.ox + j*g.gap, cy = g.oy + i*g.gap;
            drawStone(cx, cy, g.rad, turn-1, 1.f);
            DrawCircle((int)cx, (int)cy, (int)g.rad, Fade(BOARD_BG, 0.42f)); // ghost it
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) placePiece(i, j);
        }
    }
}

static void tickRobot() {
    if (mode == HVA && !gameOver && turn == 2) {
        robotTimer += GetFrameTime();
        if (robotTimer > 0.55f) { int r, c; robotMove(r, c); placePiece(r, c); robotTimer = 0.f; }
    }
}

static void drawGame() { drawBoard(); drawSidebar(); tickRobot(); }

// ─────────────────────────────────────────────────────────────
//  Screen: GAME OVER
// ─────────────────────────────────────────────────────────────
static void drawGameOver() {
    drawBoard(); drawSidebar();
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    // dim only the board area, keep sidebar readable
    DrawRectangle(0, 0, sw - SIDEBAR_W, sh, Fade(BG_BOT, 0.72f));

    float cx = (sw - SIDEBAR_W) / 2.f, cy = sh * 0.36f;
    Rectangle panel = {cx - 230, cy - 30, 460, 190};
    DrawRectangleRounded(panel, 0.12f, 12, PANEL);
    DrawRectangleRoundedLinesEx(panel, 0.12f, 12, 1.5f, PANEL_LINE);

    const char *msg = isDraw ? "It's a Draw" : TextFormat("%s wins!", PNames[winner-1]);
    TBC(msg, cx, cy, 40, isDraw ? TEXT : HL_GOLD);
    TC(isDraw ? "the board is full" : TextFormat("%d in a row", winC), cx, cy + 52, 17, TEXT_DIM);

    float bw = 190, bh = 52, g = 16;
    if (Button({cx - bw - g/2, cy + 90, bw, bh}, "Play Again", 19, PRIMARY)) { startNewGame(); screen = GAME; }
    if (Button({cx + g/2, cy + 90, bw, bh}, "Main Menu", 19, GHOST)) screen = MENU;
}

// ─────────────────────────────────────────────────────────────
//  Toast
// ─────────────────────────────────────────────────────────────
static void drawToast() {
    if (notifTimer <= 0.f) return;
    notifTimer -= GetFrameTime();
    float a = min(1.f, notifTimer * 2.5f);
    int sw = GetScreenWidth(), sh = GetScreenHeight();
    float tw = TW(notif, 16);
    float w = tw + 44, x = (sw - SIDEBAR_W)/2.f - w/2, y = sh - 74;
    DrawRectangleRounded({x, y, w, 42}, 0.5f, 8, Fade(PANEL_HI, a));
    DrawRectangleRoundedLinesEx({x, y, w, 42}, 0.5f, 8, 1.5f, Fade(ACCENT, a));
    T(notif, x + 22, y + 12, 16, Fade(TEXT, a));
}

// ─────────────────────────────────────────────────────────────
//  main
// ─────────────────────────────────────────────────────────────
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(1160, 800, "Gomoku — Five in a Row");
    SetWindowMinSize(900, 660);
    SetTargetFPS(60);
    loadFonts();

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F)) {
            if (IsWindowFullscreen()) { ToggleFullscreen(); SetWindowSize(1160, 800); }
            else { int mon = GetCurrentMonitor();
                   SetWindowSize(GetMonitorWidth(mon), GetMonitorHeight(mon)); ToggleFullscreen(); }
        }
        if (screen == GAME) {
            if (IsKeyPressed(KEY_U) && !gameOver && !(mode==HVA && turn==2)) undoMove();
            if ((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL)) && IsKeyPressed(KEY_S)) saveGame();
            if (IsKeyPressed(KEY_ESCAPE)) screen = MENU;
        } else if (screen != MENU && IsKeyPressed(KEY_ESCAPE)) { screen = MENU; activeField = -1; }

        if (placeAnim < 1.f) placeAnim = min(1.f, placeAnim + GetFrameTime() * 7.f);

        BeginDrawing();
        ClearBackground(BG_BOT);
        drawBackground();
        switch (screen) {
            case MENU:     { bool run = true; drawMenu(run); if (!run) { EndDrawing(); goto quit; } } break;
            case SETUP:    drawSetup();    break;
            case GAME:     drawGame();     break;
            case GAMEOVER: drawGameOver(); break;
        }
        drawToast();
        EndDrawing();
    }
quit:
    if (FREG.texture.id  && FREG.texture.id  != GetFontDefault().texture.id) UnloadFont(FREG);
    if (FBOLD.texture.id && FBOLD.texture.id != FREG.texture.id
                         && FBOLD.texture.id != GetFontDefault().texture.id) UnloadFont(FBOLD);
    CloseWindow();
    return 0;
}
