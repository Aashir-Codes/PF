#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<math.h>
using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;

	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	do
	{

		ReadConsoleInput(hInput, &InputRecord, 1, &Events);

		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{

			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;

			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;

			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = cpos;
	scrn.Y = rpos;

	SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

void hideConsoleCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);

	cursorInfo.bVisible = false;

	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void draw_a_circle(int c_r, int c_c, int r, int min_theta = 0, int maz_theta = 360, char sym = -37)
{

	for (int i = min_theta; i <= maz_theta; i++)
	{

		int row = c_r + (-1) * (r * sin(i * 3.14 / 180));

		int col = c_c + (r * cos(i * 3.14 / 180));

		gotoRowCol(row, col);
		cout << sym;
	}
}

void print_a_circle(int cx, int cy, int r, char sym = -37, float delta = 360)
{

	for (int alpha = 1; alpha <= delta; alpha++)
	{

		int row = cx + (-1) * (r * sin(alpha * 3.14 / 180));

		int col = cy + (r * cos(alpha * 3.14 / 180));

		gotoRowCol(row, col);
		cout << sym;
	}
}

void paintALine(int p1r, int p1c, int p2r, int p2c, char sym = -37, float delta = 0.001)
{

	for (float alpha = 0; alpha <= 1; alpha += delta)
	{

		int r = ceil(p1r * alpha + p2r * (1 - alpha));
		int c = ceil(p1c * alpha + p2c * (1 - alpha));

		if (p1r == p2r)
			r = p1r;

		if (p1c == p2c)
			c = p2c;

		gotoRowCol(r, c);
		cout << sym;
	}
}

void menu()
{
	color(15);
	cout << "\n================================" << endl;

	cout << "       BSCS25079 PROJECT 1            " << endl;

	cout << "================================" << endl;

	 cout << "1.  Fan printing" << endl;
  cout << "2.  Stone Throwing" << endl;
 cout << "3.  Multiple Stone Throwing" << endl;
	 cout << "4.  Circle Printing" << endl;
	 cout << "5.  Circle Expanding" << endl;
	 cout << "6.  Smiley Face" << endl;
	cout << "7.  Spiral Printing" << endl;
	  cout << "8.  Sine wave" << endl;
 cout << "9.  Moving Sine wave" << endl;
	color(15); cout << "10. Moving Character sine wave" << endl;
	color(15); cout << "11. Name Printing" << endl;
	color(15); cout << "12. Growing Name Printing" << endl;
	color(15); cout << "13. Moving Name Printing" << endl;
	color(15);  cout << "14. Bonus" << endl;
	color(15); cout << "0.  Exit" << endl;
	color(15);
	cout << "--------------------------------" << endl;
	cout << "Enter your choice: ";
}

void pplus(int rows, int cols, char sym = -37, float delta = 0.001)
{

	paintALine(0, cols / 2, rows - 1, cols / 2, sym, delta);

	paintALine(rows / 2, 0, rows / 2, cols - 1, sym, delta);
}

void cross(int rows, int cols, char sym = -37, float delta = 0.001)
{

	paintALine(0, 0, rows - 1, cols - 1, sym, delta);

	paintALine(0, cols - 1, rows - 1, 0, sym, delta);
}

void fanDrawing(int rows, int cols, char sym = -37, float delta = 0.001)
{
	float Delay = 500;

	while (true)
	{

		cross(rows, cols, sym, delta);
		Sleep(Delay);

		cross(rows, cols, ' ', delta);

		pplus(rows, cols, sym, delta);
		Sleep(Delay);

		pplus(rows, cols, ' ', delta);

		Delay = Delay * 0.9;
	}
}

void drawFanBlade(int centerR, int centerC, int heightOffset, int widthOffset, char sym, float delta = 0.001)
{

	int r1 = centerR - heightOffset;
	int c1 = centerC - widthOffset;
	int r2 = centerR + heightOffset;
	int c2 = centerC + widthOffset;

	paintALine(r1, c1, r1, c2, sym, delta);

	paintALine(r2, c1, r2, c2, sym, delta);

	paintALine(r1, c1, r2, c1, sym, delta);

	paintALine(r1, c2, r2, c2, sym, delta);

	paintALine(r1, c1, r2, c2, sym, delta);

	paintALine(r1, c2, r2, c1, sym, delta);
}

void q1()
{
	int centerR = 100, centerC = 100;
	int longSide = 25;
	int shortSide = 12;
	float delay = 500.0;
	char sym = -37;

	hideConsoleCursor();
	system("cls");

	color(11);

	while (!_kbhit())
	{

		color(11);
		drawFanBlade(centerR, centerC, longSide, shortSide, sym);
		Sleep(delay);

		drawFanBlade(centerR, centerC, longSide, shortSide, ' ');

		color(14);
		drawFanBlade(centerR, centerC, shortSide, longSide, sym);
		Sleep(delay);

		drawFanBlade(centerR, centerC, shortSide, longSide, ' ');

		if (delay > 15.0)
		{
			delay = delay * 0.85;
		}
	}

	_getch();
	color(7);
	system("cls");
}

void CliffFloorDrawing(int rows, int cols)
{

	paintALine(rows / 5, 0, rows / 5, cols / 6);

	paintALine(rows / 5, cols / 6, rows - 1, cols / 6);

	paintALine(rows - rows / 5, cols / 6, rows - rows / 5, cols - 1);
}

void stoneThrowingSimulation(int rows, int sr, int sc, float vx, char ssym)
{
	int fr = rows - rows / 5;

	int ppr = 0, ppc = 0;

	for (float t = 0; true; t += 0.001)
	{

		int r = ceil(0.5 * 9.8 * t * t + sr);

		int c = ceil(vx * t + sc);

		if (r >= fr)
			r = fr - 1;

		gotoRowCol(r, c);
		cout << ssym;

		gotoRowCol(ppr, ppc);
		cout << ' ';

		if (r == fr - 1)
			break;

		ppr = r;
		ppc = c;
	}
}

void drawCharacter(int r, int c, bool erase = false)
{
	if (erase)
	{
		gotoRowCol(r, c);         cout << " ";
		gotoRowCol(r + 1, c - 1); cout << "   ";
		gotoRowCol(r + 2, c - 1); cout << "   ";
	}
	else
	{
		gotoRowCol(r, c);         cout << "o";
		gotoRowCol(r + 1, c - 1); cout << "\\I/";
		gotoRowCol(r + 2, c - 1); cout << "/ \\";
	}
}

void q2()
{
	int rows = 123, cols = 237;

	hideConsoleCursor();
	system("cls");

	color(10);
	CliffFloorDrawing(rows, cols);

	int cliffFloorR = rows / 5;
	int cliffEdgeC = cols / 6;

	int charR = cliffFloorR - 3;
	int stoneC = 10;
	int startC = cliffEdgeC - 5;
	char sym = -37;

	color(13);
	gotoRowCol(cliffFloorR - 1, stoneC);
	cout << sym;

	color(9);
	for (int c = startC; c >= stoneC + 2; c--)
	{
		drawCharacter(charR, c);
		Sleep(40);
		drawCharacter(charR, c, true);
	}

	int grabC = stoneC + 2;
	drawCharacter(charR, grabC);
	Sleep(500);

	gotoRowCol(cliffFloorR - 1, stoneC);
	cout << ' ';
	Sleep(300);

	drawCharacter(charR, grabC, true);

	color(14);
	for (int c = grabC; c <= cliffEdgeC - 2; c++)
	{
		drawCharacter(charR, c);
		Sleep(40);
		drawCharacter(charR, c, true);
	}

	drawCharacter(charR, cliffEdgeC - 2);
	Sleep(200);

	color(12);
	stoneThrowingSimulation(rows, charR + 1, cliffEdgeC, 10, sym);

	_getch();
	color(7);
	system("cls");
}

void q3()
{
	int rows = 123, cols = 237;

	hideConsoleCursor();
	system("cls");

	color(13);
	CliffFloorDrawing(rows, cols);

	int cliffFloorR = rows / 5;
	int cliffEdgeC = cols / 6;

	int charR = cliffFloorR - 3;
	int startC = cliffEdgeC - 5;
	char sym = -37;

	int stoneCols[5] = { 1, 3, 5, 7 };

	float velocities[5] = { 8.0, 14.0, 22.0, 32.0 };

	int stoneColors[4] = { 9, 10, 11, 14 };

	for (int i = 0; i < 4; i++)
	{
		color(stoneColors[i]);
		gotoRowCol(cliffFloorR - 1, stoneCols[i]);
		cout << sym;
	}

	int currentPosC = startC;

	for (int i = 0; i < 4; i++)
	{
		color(stoneColors[i]);

		for (int c = currentPosC; c >= stoneCols[i] + 2; c--)
		{
			drawCharacter(charR, c);
			Sleep(40);
			drawCharacter(charR, c, true);
		}

		int grabC = stoneCols[i] + 2;
		drawCharacter(charR, grabC);
		Sleep(300);

		gotoRowCol(cliffFloorR - 1, stoneCols[i]);
		cout << ' ';
		Sleep(200);

		drawCharacter(charR, grabC, true);

		for (int c = grabC; c <= cliffEdgeC - 2; c++)
		{
			drawCharacter(charR, c);
			Sleep(40);
			drawCharacter(charR, c, true);
		}

		currentPosC = cliffEdgeC - 2;
		drawCharacter(charR, currentPosC);
		Sleep(200);

		color(12);
		stoneThrowingSimulation(rows, charR + 1, cliffEdgeC, velocities[i], sym);
	}

	_getch();
	color(7);
	system("cls");
}

void drawCircle(int rows, int cols, int cr, int cc, int rad, char sym)
{

	for (int th = 0; th < 360; th++)
	{

		int r = rad * -1 * sin(th * 3.14 / 180) + cr;
		int c = rad * cos(th * 3.14 / 180) + cc;

		gotoRowCol(r, c);
		cout << sym;
	}
}

void q4()
{
	int rows = 123, cols = 237;

	hideConsoleCursor();
	system("cls");

	int centerR = rows / 2;
	int centerC = cols / 2;
	int radius = 30;
	char sym = -37;

	color(14);
	drawCircle(rows, cols, centerR, centerC, radius, sym);

	_getch();
	color(7);
	system("cls");
}

void q5()
{
	int rows = 123, cols = 237;
	char sym = -37;
	int maxRad = rows / 2;
	int currentColor = 3;

	hideConsoleCursor();
	system("cls");

	while (!_kbhit())
	{
		color(currentColor);

		int rad;

		for (rad = 0; rad < maxRad; rad++)
		{
			if (_kbhit()) break;

			drawCircle(rows, cols, rows / 2, cols / 2, rad, sym);
			Sleep(1);
			drawCircle(rows, cols, rows / 2, cols / 2, rad, ' ');
		}

		rad--;

		for (; rad >= 0; rad--)
		{
			if (_kbhit()) break;

			drawCircle(rows, cols, rows / 2, cols / 2, rad, sym);
			Sleep(10);
			drawCircle(rows, cols, rows / 2, cols / 2, rad, ' ');
		}

		currentColor += 2;
		if (currentColor > 15)
		{
			currentColor = 2;
		}
	}

	color(7);
	_getch();
	system("cls");
}

void Task6()
{
	color(14);
	print_a_circle(17, 65, 15);

	color(9);
	print_a_circle(10, 57, 2);
	print_a_circle(10, 70, 2);

	color(10);
	draw_a_circle(17, 65, 8, 180, 360);

	_getch();
	color(7);
}

void Task7()
{
	color(11);
	print_a_circle(17, 65, 16);

	color(12);
	print_a_circle(10, 57, 3);
	print_a_circle(10, 70, 3);

	color(13);
	print_a_circle(16, 64, 2);

	color(14);
	for (int i = 1; i <= 5; i++)
	{
		gotoRowCol(18 + i, 59);

		for (int j = 1; j <= 10; j++)
		{

			if (j == 1 || j == 10 || i == 1 || i == 5)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}

	_getch();
	color(7);
}

void Spiral(int cr, int cc, int MAXRad, int NOA, char sym)
{
	float rad = 0;

	float delta = MAXRad * 1.0 / (360 * NOA);

	for (int t = 1; t <= NOA; t++)
	{

		int currentColor = ((t + 3) % 14) + 1;
		color(currentColor);

		for (int th = 0; th < 360; th++, rad += delta)
		{

			int r = ceil(rad * -1 * sin(th * 3.14 / 180) + cr);
			int c = ceil(rad * cos(th * 3.14 / 180) + cc);

			gotoRowCol(r, c);
			cout << sym;

			if (th % 15 == 0)
			{
				Sleep(1);
			}
		}
	}
}

void q7()
{
	int rows = 123, cols = 237;

	hideConsoleCursor();
	system("cls");

	int centerR = rows / 2;
	int centerC = cols / 2;
	int maxRadius = 50;
	int numberOfArcs = 15;
	char sym = -37;

	Spiral(centerR, centerC, maxRadius, numberOfArcs, sym);

	color(7);
	_getch();
	system("cls");
}

void simpleSineWave(int rows, int cols, int cr, int now, int Amp, char sym)
{

	color(10);

	paintALine(0, 0, rows - 1, 0, sym);

	int horizontalAxisR = rows / 2;
	paintALine(horizontalAxisR, 0, horizontalAxisR, cols - 1, sym);

	float ddelta = 360.0 * now / cols;

	int pr = cr;
	int pc = 0;
	int c = 0;

	int currentColorNum = 5;
	color(currentColorNum);

	for (float d = 0; d <= now * 360; d += ddelta, c++)
	{

		int r = Amp * -1 * sin(d * 3.14 / 180) + cr;

		if (r < 0) r = 0;
		if (r >= rows) r = rows - 1;

		if (c > 0)
		{
			int prevHalfWaves = (int)floor((d - ddelta) / 180.0);
			int currentHalfWaves = (int)floor(d / 180.0);

			if (prevHalfWaves != currentHalfWaves)
			{
				currentColorNum += 2;

				if (currentColorNum == 7 || currentColorNum == 8)
				{
					currentColorNum++;
				}

				if (currentColorNum > 15)
				{
					currentColorNum = 1;
				}
				color(currentColorNum);
			}
		}

		paintALine(pr, pc, r, c, sym);
		Sleep(10);

		pr = r;
		pc = c;
	}
}

void q8()
{
	int rows = 123, cols = 237;
	system("cls");
	hideConsoleCursor();

	int centerRRef = rows / 2;
	int numWavesCount = 5;
	int amplitudeVal = rows / 2 * 0.8;
	char symChar = -37;

	simpleSineWave(rows, cols, centerRRef, numWavesCount, amplitudeVal, symChar);

	_getch();
	color(7);
	system("cls");
}

void continuousSlitheringWave(int endC, float sd, int cr, int now, int Amp, int cols, char sym)
{

	float ddelta = 360.0 * now / cols;

	int pr = -1, pc = -1;

	for (int c = 0; c <= endC; c++)
	{

		float d = c * ddelta + sd;

		int r = Amp * -1 * sin(d * 3.14159 / 180.0) + cr;

		if (r < 0) r = 0;
		if (r >= 123) r = 122;

		if (sym != ' ')
		{
			int colorNum = ((c + 4) % 14) + 1;
			color(colorNum);
		}

		if (pr != -1 && pc != -1)
		{
			paintALine(pr, pc, r, c, sym);
		}
		else
		{
			gotoRowCol(r, c);
			cout << sym;
		}

		pr = r;
		pc = c;
	}
}

void q9()
{
	int rows = 123, cols = 237;
	system("cls");
	hideConsoleCursor();

	int cr = rows / 2;
	int now = 5;
	int Amp = rows / 2 * 0.8;
	char sym = -37;

	float sd = 0;
	int headC = 0;

	while (!_kbhit())
	{

		continuousSlitheringWave(headC, sd, cr, now, Amp, cols, sym);
		Sleep(20);

		continuousSlitheringWave(headC, sd, cr, now, Amp, cols, ' ');

		if (headC < cols - 1)
		{
			headC += 2;
			if (headC >= cols) headC = cols - 1;
		}

		sd += 30;
		if (sd >= 360)
		{
			sd -= 360;
		}
	}

	_getch();
	color(7);
	system("cls");
}

void q10()
{
	int rows = 200, cols = 200;

}

void q13()
{
	int rows = 200, cols = 200;

}

void q14()
{
	int rows = 200, cols = 200;

}

void L2R(int r, int c1, int c2, char sym, int delay)
{
	for (int c = c1; c <= c2; c++)
	{
		gotoRowCol(r, c);
		cout << sym;
		Sleep(delay);
	}
}

void R2L(int r, int c1, int c2, char sym, int delay)
{
	for (int c = c1; c >= c2; c--)
	{
		gotoRowCol(r, c);
		cout << sym;
		Sleep(delay);
	}
}

void T2B(int c, int r1, int r2, char sym, int delay)
{
	for (int r = r1; r <= r2; r++)
	{
		gotoRowCol(r, c);
		cout << sym;
		Sleep(delay);
	}
}

void B2T(int c, int r1, int r2, char sym, int delay)
{
	for (int r = r1; r >= r2; r--)
	{
		gotoRowCol(r, c);
		cout << sym;
		Sleep(delay);
	}
}

void bonus()
{
	system("cls");
	hideConsoleCursor();

	int minR = 2, maxR = 120;
	int minC = 4, maxC = 232;

	int rowSpacing = 3;
	int colSpacing = 6;
	int NOfRectangles = 18;

	char Symbol = 'A';
	int delay = 2;

	for (int rec = 1; rec <= NOfRectangles; rec++)
	{

		color(((rec + 5) % 14) + 1);

		L2R(minR, minC, maxC, Symbol, delay);
		T2B(maxC, minR, maxR, Symbol, delay);
		R2L(maxR, maxC, minC, Symbol, delay);
		B2T(minC, maxR, minR + rowSpacing, Symbol, delay);

		Symbol++;

		minR += rowSpacing;
		maxR -= rowSpacing;
		minC += colSpacing;
		maxC -= colSpacing;
	}

	Sleep(1000);

	for (int rec = NOfRectangles; rec >= 1; rec--)
	{

		minR -= rowSpacing;
		maxR += rowSpacing;
		minC -= colSpacing;
		maxC += colSpacing;
		Symbol--;

		T2B(minC, minR + rowSpacing, maxR, ' ', delay);
		L2R(maxR, minC, maxC, ' ', delay);
		B2T(maxC, maxR, minR, ' ', delay);
		R2L(minR, maxC, minC, ' ', delay);
	}

	_getch();
	color(7);
	system("cls");
}

int main()
{
	int choice;
	menu();

	do
	{
		cin >> choice;

		color(7);

		switch (choice)
		{
		case 1:  q1();    break;
		case 2:  q2();    break;
		case 3:  q3();    break;
		case 4:  q4();    break;
		case 5:  q5();    break;
		case 6:  Task6(); break;
		case 13: Task7(); break;
		case 7:  q7();    break;
		case 8:  q8();    break;
		case 9:  q9();    break;
		case 10: q10();   break;
		case 11: q13();   break;
		case 12: bonus(); break;
		case 0:

			color(14);
			cout << "Exiting program... Goodbye!" << endl;
			color(7);
			break;
		default:

			color(12);
			cout << "Invalid choice! Please try again." << endl;
			color(7);
		}

		if (choice != 0)
		{
			menu();
		}

	} while (choice != 0);

	return 0;
}