// =============================================================
//  chess_gui.cpp  —  Raylib GUI  (Marble theme, fully responsive)
//
//  HOW TO BUILD:
//    g++ chess_gui.cpp -o chess -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
//
//  SETUP (one-time):
//    1. Copy main.cpp → engine.cpp
//    2. In engine.cpp rename:  int main()  →  int _engine_unused()
//    3. Put piece PNGs in  assets/pieces/
//       Names: wK wQ wR wB wN wP bK bQ bR bB bN bP  (each .png)
// =============================================================

#include "raylib.h"
#include "engine.cpp"
#include <cstring>
#include <cmath>

// =============================================================
//  RESPONSIVE LAYOUT
//  All sizes are computed once at startup from the monitor size.
//  Nothing is hardcoded — runs correctly on any screen.
// =============================================================
struct Layout {
    int square;      // pixels per board square
    int boardPx;     // board pixel size  (square * 8)
    int margin;      // outer gap
    int labelW;      // space for rank/file labels
    int boardX;      // board left edge
    int boardY;      // board top  edge
    int panelX;      // side panel left edge
    int panelW;      // side panel width
    int winW;        // total window width
    int winH;        // total window height
    int fontSize;    // base font size (scales with square)
};

// Global layout — filled in main() before anything draws
static Layout L;

void buildLayout()
{
    int mw = GetMonitorWidth(0);
    int mh = GetMonitorHeight(0);

    // Board fills ~78% of monitor height, rounded down to a multiple of 8
    int boardH = (int)(mh * 0.78f);
    L.square   = (boardH / 8) & ~1;   // even number, nicer divisions
    if (L.square < 50) L.square = 50; // minimum so it's still playable
    if (L.square > 110) L.square = 110; // cap so panel doesn't get tiny

    L.boardPx  = L.square * 8;
    L.margin   = L.square / 3;
    L.labelW   = L.square / 4;
    L.boardX   = L.labelW + L.margin;
    L.boardY   = L.labelW + L.margin;
    L.panelW   = L.square * 3;        // panel is always 3 squares wide
    L.panelX   = L.boardX + L.boardPx + L.margin;
    L.winW     = L.panelX + L.panelW + L.margin / 2;
    L.winH     = L.boardY + L.boardPx + L.labelW + L.margin;
    L.fontSize = L.square / 6;        // scales with square size
    if (L.fontSize < 12) L.fontSize = 12;
}

// =============================================================
//  MARBLE PALETTE  (colours don't need to scale)
// =============================================================
static const Color BG           = {  18,  18,  24, 255 };
static const Color LIGHT_SQ     = { 210, 210, 215, 255 };
static const Color DARK_SQ      = {  90,  90, 100, 255 };
static const Color SEL_TINT     = {  80, 200, 120, 110 };
static const Color DOT_COL      = {  80, 210, 120, 200 };
static const Color CAPTURE_COL  = { 210,  70,  70, 180 };
static const Color CHECK_COL    = { 220,  50,  50, 160 };
static const Color LAST_MOVE    = { 200, 200,  60,  80 };
static const Color PANEL_BG     = {  26,  26,  34, 255 };
static const Color PANEL_BORDER = {  50,  50,  64, 255 };
static const Color BTN_IDLE     = {  44,  44,  58, 255 };
static const Color BTN_HOV      = {  66,  66,  86, 255 };
static const Color BTN_ACT      = {  88, 160, 110, 255 };
static const Color TXT_MAIN     = { 230, 230, 235, 255 };
static const Color TXT_DIM      = { 130, 130, 145, 255 };
static const Color ACCENT       = {  88, 200, 130, 255 };

// =============================================================
//  PIECE TEXTURES
// =============================================================
static Texture2D tex[128] = {};

void loadTextures()
{
    const char* names[12] = {"wK","wQ","wR","wB","wN","wP",
                              "bK","bQ","bR","bB","bN","bP"};
    const char  chars[12] = {'K','Q','R','B','N','P',
                              'k','q','r','b','n','p'};
    char path[64];
    for (int i = 0; i < 12; i++) {
        snprintf(path, sizeof(path), "assets/pieces/%s.png", names[i]);
        if (FileExists(path)) {
            tex[(int)chars[i]] = LoadTexture(path);
            SetTextureFilter(tex[(int)chars[i]], TEXTURE_FILTER_BILINEAR);
        }
    }
}

void unloadTextures()
{
    const char* chars = "KQRBNPkqrbnp";
    for (int i = 0; chars[i]; i++)
        if (tex[(int)chars[i]].id > 0)
            UnloadTexture(tex[(int)chars[i]]);
}

// =============================================================
//  COORD HELPERS  (use L.* everywhere, not hardcoded numbers)
// =============================================================
bool pixelToSquare(int px, int py, int& row, int& col)
{
    int bx = px - L.boardX;
    int by = py - L.boardY;
    if (bx < 0 || by < 0 || bx >= L.boardPx || by >= L.boardPx) return false;
    col = bx / L.square;
    row = by / L.square;
    return true;
}

Rectangle squareRect(int row, int col)
{
    return { (float)(L.boardX + col * L.square),
             (float)(L.boardY + row * L.square),
             (float)L.square, (float)L.square };
}

// =============================================================
//  DRAW HELPERS
// =============================================================
void drawPiece(char piece, int row, int col)
{
    if (piece == '.') return;
    Rectangle r  = squareRect(row, col);
    Texture2D t  = tex[(int)piece];

    if (t.id > 0) {
        float pad  = L.square * 0.06f;
        float size = L.square - pad * 2;
        DrawTexturePro(t,
            { 0, 0, (float)t.width, (float)t.height },
            { r.x + pad, r.y + pad, size, size },
            { 0, 0 }, 0.0f, WHITE);
    } else {
        // Fallback letter — scales with square size
        Color c  = isupper(piece) ? Color{245,245,245,255}
                                  : Color{ 30, 30, 30,255};
        int   fs = (int)(L.square * 0.38f);
        int   tx = (int)(r.x + L.square/2 - MeasureText(TextFormat("%c",piece),fs)/2);
        int   ty = (int)(r.y + L.square/2 - fs/2);
        DrawText(TextFormat("%c", piece), tx+1, ty+1, fs, BLACK);
        DrawText(TextFormat("%c", piece), tx,   ty,   fs, c);
    }
}

bool drawButton(const char* label, int x, int y, int w, int h, bool active = false)
{
    Rectangle r    = { (float)x, (float)y, (float)w, (float)h };
    Vector2 mouse  = GetMousePosition();
    bool hover     = CheckCollisionPointRec(mouse, r);
    bool clicked   = hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    Color face = active ? BTN_ACT : (hover ? BTN_HOV : BTN_IDLE);
    DrawRectangleRec(r, face);
    DrawRectangleLinesEx(r, 1.0f, active ? ACCENT : PANEL_BORDER);

    int fs = L.fontSize;
    int tw = MeasureText(label, fs);
    DrawText(label, x + (w - tw)/2, y + (h - fs)/2, fs, TXT_MAIN);
    return clicked;
}

// =============================================================
//  GUI STATE
// =============================================================
struct GuiState {
    enum Screen { MENU, GAME, RESULT } screen = MENU;
    enum Mode   { PVP,  PVB  }        mode   = PVP;

    bool hasSel     = false;
    int  selRow     = -1, selCol = -1;

    Move legalMoves[256];
    int  legalCount = 0;

    int  lastSR = -1, lastSC = -1, lastDR = -1, lastDC = -1;

    bool humanIsWhite = true;
    int  difficulty   = 2;

    bool awaitingPromo = false;
    int  promoRow = -1, promoCol = -1;
    char promoPiece = 'P';

    const char* resultMsg = "";

    float botDelay = 0.0f;
    bool  botMoved = false;
};

// =============================================================
//  LEGAL MOVE CACHE
// =============================================================
void rebuildLegal(GuiState& g)
{
    g.legalCount = 0;
    if (!g.hasSel) return;
    Move all[256];
    int n = generateMoves(all, 256);
    for (int i = 0; i < n; i++)
        if (all[i].s_r == g.selRow && all[i].s_c == g.selCol)
            g.legalMoves[g.legalCount++] = all[i];
}

bool isLegalDest(const GuiState& g, int row, int col)
{
    for (int i = 0; i < g.legalCount; i++)
        if (g.legalMoves[i].d_r == row && g.legalMoves[i].d_c == col)
            return true;
    return false;
}

// =============================================================
//  INIT GAME
// =============================================================
void startGame(GuiState& g)
{
    FileToArray();
    check_king_White(); check_king_Black();
    turn = 1; Count = 0; undo = 0;
    Stalemate = 0; Exit = 0;
    epRow = -1; epCol = -1;
    for (int i = 0; i < 4; i++) rook[i] = 0;
    for (int i = 0; i < 2; i++) king[i] = 0;
    History();

    g.hasSel = false; g.legalCount = 0;
    g.awaitingPromo = false; g.resultMsg = "";
    g.lastSR = g.lastSC = g.lastDR = g.lastDC = -1;
    g.botDelay = 0.0f; g.botMoved = false;
    g.screen = GuiState::GAME;
}

// =============================================================
//  GAME OVER
// =============================================================
void checkGameOver(GuiState& g)
{
    if (checkmate()) {
        g.resultMsg = (turn == 1) ? "Black wins by checkmate!"
                                  : "White wins by checkmate!";
        g.screen = GuiState::RESULT;
    } else if (stalemate()) {
        g.resultMsg = "Stalemate — it's a draw!";
        g.screen = GuiState::RESULT;
    }
}

// =============================================================
//  APPLY MOVES
// =============================================================
void applyHumanMove(GuiState& g, int dr, int dc)
{
    char piece = board[g.selRow][g.selCol];
    bool isPromo = ((piece == 'P' && dr == 0) || (piece == 'p' && dr == 7));

    if (isPromo) {
        g.awaitingPromo = true;
        g.promoRow = dr; g.promoCol = dc;
        g.promoPiece = piece;
        return;
    }

    History();
    makeMove({ g.selRow, g.selCol, dr, dc }, false);
    check_king_White(); check_king_Black();
    turn = !turn;
    History();

    g.lastSR = g.selRow; g.lastSC = g.selCol;
    g.lastDR = dr;       g.lastDC = dc;
    g.hasSel = false; g.legalCount = 0;
    g.botDelay = 0.35f;
}

void applyPromotion(GuiState& g, char chosen)
{
    History();
    makeMove({ g.selRow, g.selCol, g.promoRow, g.promoCol }, false);
    board[g.promoRow][g.promoCol] = chosen;
    check_king_White(); check_king_Black();
    turn = !turn;
    History();

    g.lastSR = g.selRow;   g.lastSC = g.selCol;
    g.lastDR = g.promoRow; g.lastDC = g.promoCol;
    g.hasSel = false; g.legalCount = 0;
    g.awaitingPromo = false;
    g.botDelay = 0.35f;
}

// =============================================================
//  BOT TURN
// =============================================================
void doBotTurn(GuiState& g)
{
    Move m;
    if      (g.difficulty == 1) m = pickRandomMove();
    else if (g.difficulty == 2) m = pickGreedyMove();
    else                        m = pickBestMoveMinimax(3);

    History();
    makeMove(m, true);
    check_king_White(); check_king_Black();
    turn = !turn;
    History();

    g.lastSR = m.s_r; g.lastSC = m.s_c;
    g.lastDR = m.d_r; g.lastDC = m.d_c;
    g.botMoved = true;
}

// =============================================================
//  HANDLE BOARD CLICK
// =============================================================
void handleClick(GuiState& g, int row, int col)
{
    if (g.awaitingPromo) return;

    if (!g.hasSel) {
        if (board[row][col] == '.') return;
        if (check_BlackWhite(row, col) != (int)turn) return;
        g.hasSel = true;
        g.selRow = row; g.selCol = col;
        rebuildLegal(g);
        return;
    }

    if (board[row][col] != '.' && check_BlackWhite(row, col) == (int)turn) {
        g.selRow = row; g.selCol = col;
        rebuildLegal(g);
        return;
    }

    if (!isLegalDest(g, row, col)) {
        g.hasSel = false; g.legalCount = 0;
        return;
    }

    applyHumanMove(g, row, col);
    checkGameOver(g);
}

// =============================================================
//  DRAW BOARD
// =============================================================
void drawBoard(const GuiState& g)
{
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Rectangle r = squareRect(row, col);
            Color sq = ((row + col) % 2 == 0) ? LIGHT_SQ : DARK_SQ;
            DrawRectangleRec(r, sq);

            if ((row == g.lastSR && col == g.lastSC) ||
                (row == g.lastDR && col == g.lastDC))
                DrawRectangleRec(r, LAST_MOVE);
        }
    }

    if (check()) {
        int kr = (turn == 1) ? K_r : k_r;
        int kc = (turn == 1) ? K_c : k_c;
        DrawRectangleRec(squareRect(kr, kc), CHECK_COL);
    }

    if (g.hasSel)
        DrawRectangleRec(squareRect(g.selRow, g.selCol), SEL_TINT);

    for (int i = 0; i < g.legalCount; i++) {
        int dr = g.legalMoves[i].d_r;
        int dc = g.legalMoves[i].d_c;
        Rectangle r = squareRect(dr, dc);
        float cx = r.x + L.square / 2.0f;
        float cy = r.y + L.square / 2.0f;
        if (board[dr][dc] != '.')
            DrawRingLines({ cx, cy },
                L.square/2.0f - 5, L.square/2.0f - 1, 0, 360, 32, CAPTURE_COL);
        else
            DrawCircle((int)cx, (int)cy, L.square / 6.5f, DOT_COL);
    }

    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            drawPiece(board[row][col], row, col);

    // Board border
    DrawRectangleLinesEx(
        { (float)(L.boardX-1), (float)(L.boardY-1),
          (float)(L.boardPx+2), (float)(L.boardPx+2) },
        2.0f, PANEL_BORDER);

    // Rank numbers left side (8 at top, 1 at bottom — standard chess)
    int lfs = L.fontSize - 2;
    for (int i = 0; i < 8; i++)
        DrawText(TextFormat("%d", 8 - i),
            L.boardX - L.labelW,
            L.boardY + i * L.square + L.square/2 - lfs/2,
            lfs, TXT_DIM);

    // File letters bottom
    const char* files = "abcdefgh";
    for (int i = 0; i < 8; i++)
        DrawText(TextFormat("%c", files[i]),
            L.boardX + i * L.square + L.square/2 - MeasureText("a", lfs)/2,
            L.boardY + L.boardPx + 4,
            lfs, TXT_DIM);
}

// =============================================================
//  DRAW SIDE PANEL
// =============================================================
char drawPanel(GuiState& g)
{
    DrawRectangle(L.panelX, 0, L.panelW + L.margin, L.winH, PANEL_BG);
    DrawLine(L.panelX, 0, L.panelX, L.winH, PANEL_BORDER);

    int px  = L.panelX + L.square / 4;
    int py  = L.margin;
    int bw  = L.panelW - L.square / 2;
    int bh  = (int)(L.square * 0.42f);
    int gap = bh / 4;
    int fs  = L.fontSize;

    // Title
    int titleFs = (int)(fs * 1.8f);
    DrawText("CHESS", px, py, titleFs, ACCENT);
    py += titleFs + gap * 2;

    // Turn + check
    const char* turnStr = (turn == 1) ? "White to move" : "Black to move";
    Color turnCol = (turn == 1) ? WHITE : Color{180,180,200,255};
    DrawText(turnStr, px, py, fs, turnCol);
    py += fs + gap;

    if (check()) {
        DrawRectangle(px - 4, py - 2, bw + 8, fs + 8, Color{180,40,40,60});
        DrawText("  CHECK!", px, py, fs, Color{255,100,100,255});
        py += fs + gap;
    }
    py += gap;

    DrawLine(px - 4, py, px + bw + 4, py, PANEL_BORDER);
    py += gap * 2;

    char action = 0;
    if (drawButton("Undo",      px, py, bw, bh)) action = 'u'; py += bh + gap;
    if (drawButton("Redo",      px, py, bw, bh)) action = 'r'; py += bh + gap;
    if (drawButton("Save",      px, py, bw, bh)) action = 's'; py += bh + gap;
    if (drawButton("Main Menu", px, py, bw, bh)) action = 'm'; py += bh + gap * 2;

    DrawLine(px - 4, py, px + bw + 4, py, PANEL_BORDER);
    py += gap * 2;

    if (g.mode == GuiState::PVB) {
        const char* diffs[4] = { "", "Easy", "Medium", "Hard" };
        DrawText("BOT SETTINGS", px, py, fs - 2, TXT_DIM);        py += fs + gap;
        DrawText(TextFormat("Difficulty: %s", diffs[g.difficulty]),
                 px, py, fs, TXT_MAIN);                            py += fs + gap;
        DrawText(g.humanIsWhite ? "You play: White" : "You play: Black",
                 px, py, fs, TXT_MAIN);
    }

    return action;
}

// =============================================================
//  PROMOTION POPUP  (sizes scale with L.square)
// =============================================================
char drawPromoPopup(bool isWhite)
{
    int bw  = (int)(L.square * 0.9f);
    int bh  = (int)(L.square * 0.5f);
    int pad = 12;
    int pw  = 4 * bw + 5 * pad;
    int ph  = bh + 60;
    int px  = L.boardX + (L.boardPx - pw) / 2;
    int py  = L.boardY + (L.boardPx - ph) / 2;

    DrawRectangle(px - 4, py - 4, pw + 8, ph + 8, ACCENT);
    DrawRectangle(px, py, pw, ph, Color{28,28,36,248});
    DrawText("Promote pawn to:", px + pad, py + 10, L.fontSize, TXT_MAIN);

    const char* labels[4] = { "Queen","Rook","Bishop","Knight" };
    const char  wc[4]     = { 'Q',   'R',   'B',    'N'     };
    const char  bc[4]     = { 'q',   'r',   'b',    'n'     };

    int bY = py + 44;
    for (int i = 0; i < 4; i++) {
        int bX = px + pad + i * (bw + pad);
        if (drawButton(labels[i], bX, bY, bw, bh))
            return isWhite ? wc[i] : bc[i];
    }
    return 0;
}

// =============================================================
//  MAIN MENU  (font sizes scale with L.square)
// =============================================================
void drawMenu(GuiState& g)
{
    ClearBackground(BG);

    int cx  = L.winW / 2;
    int bw  = (int)(L.square * 3.2f);
    int bh  = (int)(L.square * 0.52f);
    int gap = bh / 3;

    int titleFs = (int)(L.square * 0.75f);
    int subFs   = L.fontSize;

    int tw = MeasureText("CHESS", titleFs);
    DrawText("CHESS", cx - tw/2, L.margin, titleFs, ACCENT);

    const char* sub = "Minimax AI  |  3 Difficulty Levels";
    int sw = MeasureText(sub, subFs);
    DrawText(sub, cx - sw/2, L.margin + titleFs + 8, subFs, TXT_DIM);

    int by = L.margin + titleFs + subFs + gap * 3;

    if (drawButton("New Game  (Player vs Player)", cx - bw/2, by, bw, bh))
    { g.mode = GuiState::PVP; startGame(g); }
    by += bh + gap;

    if (drawButton("Load Saved Game", cx - bw/2, by, bw, bh)) {
        saveload();
        check_king_White(); check_king_Black();
        Count=0; undo=0; epRow=-1; epCol=-1;
        for(int i=0;i<4;i++) rook[i]=0;
        for(int i=0;i<2;i++) king[i]=0;
        Stalemate=0; History();
        g.hasSel=false; g.legalCount=0;
        g.awaitingPromo=false; g.resultMsg="";
        g.lastSR=g.lastSC=g.lastDR=g.lastDC=-1;
        g.mode=GuiState::PVP;
        g.screen=GuiState::GAME;
    }
    by += bh + gap * 2;

    DrawLine(cx - bw/2, by, cx + bw/2, by, PANEL_BORDER);
    by += gap * 2;

    int labelFs = subFs - 2;
    DrawText("BOT SETTINGS", cx - bw/2, by, labelFs, TXT_DIM);
    by += labelFs + gap;

    const char* sideLabel = g.humanIsWhite
        ? "Your colour:  White  (click to change)"
        : "Your colour:  Black  (click to change)";
    if (drawButton(sideLabel, cx - bw/2, by, bw, bh))
        g.humanIsWhite = !g.humanIsWhite;
    by += bh + gap;

    const char* diffs[4] = {"","Easy","Medium","Hard"};
    const char* diffLabel = TextFormat("Difficulty:  %s  (click to change)",
                                        diffs[g.difficulty]);
    if (drawButton(diffLabel, cx - bw/2, by, bw, bh))
        g.difficulty = (g.difficulty % 3) + 1;
    by += bh + gap;

    if (drawButton("Play vs Bot", cx - bw/2, by, bw, bh))
    { g.mode = GuiState::PVB; startGame(g); }
}

// =============================================================
//  RESULT SCREEN
// =============================================================
void drawResult(GuiState& g)
{
    drawBoard(g);
    DrawRectangle(0, 0, L.winW, L.winH, Color{0,0,0,170});

    int cx  = L.winW / 2;
    int rfs = (int)(L.square * 0.45f);
    int tw  = MeasureText(g.resultMsg, rfs);
    DrawText(g.resultMsg, cx - tw/2, L.winH/2 - rfs * 2, rfs, WHITE);

    int bw = (int)(L.square * 2.8f);
    int bh = (int)(L.square * 0.5f);
    if (drawButton("Back to Main Menu", cx - bw/2, L.winH/2 + rfs/2, bw, bh))
        g.screen = GuiState::MENU;
}

// =============================================================
//  MAIN
// =============================================================
int main()
{
    srand((unsigned)time(0));

    // Must call before InitWindow so GetMonitorWidth works
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(800, 600, "Chess");   // temporary size — replaced immediately

    buildLayout();   // measure monitor → compute all sizes

    SetWindowSize(L.winW, L.winH);
    SetWindowTitle("Chess");

    // Centre window on screen
    int mw = GetMonitorWidth(0);
    int mh = GetMonitorHeight(0);
    SetWindowPosition((mw - L.winW) / 2, (mh - L.winH) / 2);

    SetTargetFPS(60);
    loadTextures();

    GuiState g;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BG);

        if (g.screen == GuiState::MENU)   { drawMenu(g);   EndDrawing(); continue; }
        if (g.screen == GuiState::RESULT) { drawResult(g); EndDrawing(); continue; }

        // ── IN GAME ─────────────────────────────────────────────

        bool humanTurn = (g.mode == GuiState::PVP) ||
                         (turn == 1 &&  g.humanIsWhite) ||
                         (turn == 0 && !g.humanIsWhite);

        // Bot move with a short delay so it feels natural
        if (!humanTurn && !g.awaitingPromo) {
            if (g.botDelay > 0.0f) {
                g.botDelay -= dt;
            } else if (!g.botMoved) {
                doBotTurn(g);
                checkGameOver(g);
            } else {
                g.botMoved = false;
            }
        } else {
            g.botDelay = 0.0f;
            g.botMoved = false;
        }

        drawBoard(g);

        char action = drawPanel(g);
        if (action == 'u') { Undo(); check_king_White(); check_king_Black();
                              g.hasSel=false; g.legalCount=0; }
        if (action == 'r') { Redo(); check_king_White(); check_king_Black();
                              g.hasSel=false; g.legalCount=0; }
        if (action == 's') { save(); }
        if (action == 'm') { g.screen = GuiState::MENU; }

        if (humanTurn && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mr = 0, mc = 0;
            if (pixelToSquare((int)GetMousePosition().x,
                              (int)GetMousePosition().y, mr, mc))
                handleClick(g, mr, mc);
        }

        if (g.awaitingPromo) {
            char chosen = drawPromoPopup(g.promoPiece == 'P');
            if (chosen) {
                applyPromotion(g, chosen);
                checkGameOver(g);
            }
        }

        if (humanTurn && !g.awaitingPromo)
            checkGameOver(g);

        EndDrawing();
    }

    unloadTextures();
    CloseWindow();
    return 0;
}
