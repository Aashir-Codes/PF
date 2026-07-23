#include <iostream>
#include <fstream>
using namespace std;


const int Rows = 100;
const int Cols = 100;
int arr[Rows][Cols] = {};
int Size = 0;
int Arr[Rows * Cols] = {};
int _size = 0;


void Loadfile(const char name[], int rows, int cols)
{
	ifstream Rdr(name);

	if (!Rdr)
	{
		cout << "File not opened!" << endl;
		exit(1);
	}

	int i = 0, j = 0;

	while ((!Rdr.eof()) && Size < (Rows * Cols))
	{
		Rdr >> arr[i][j];
		j++;
		if (j == cols) { j = 0; i++; }
		Size++;
	}

	Rdr.close();
}

void Print2D(const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		cout << " [ ";
		for (int j = 0; j < cols; j++)
			cout << arr[i][j] << " ";
		cout << "]" << endl;
	}
	cout << endl;
}

void Print1d(const char message[])
{
	cout << message << " : [";
	for (int i = 0; i < _size; i++)
		cout << Arr[i] << " ";
	cout << "]" << endl;
}

int Row_Sum(int rows, int cols)
{
	int sum = 0;
	for (int i = 0; i < cols; i++)
		sum += arr[rows][i];
	return sum;
}

int Cols_Sum(int rows, int cols)
{
	int sum = 0;
	for (int i = 0; i < rows; i++)
		sum += arr[i][cols];
	return sum;
}

void ResetArrays()
{
	Size = 0;
	_size = 0;
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			arr[i][j] = 0;
	for (int i = 0; i < Rows * Cols; i++)
		Arr[i] = 0;
}


// Forward declarations
void Flatten_RowMajor();
void Flatten_RowMajor_Reverse();
void Flatten_ColMajor();
void Flatten_ColMajor_Reverse();
void Flatten_Zigzag_RowWise();
void Flatten_Zigzag_RowWise_Reverse();
void Flatten_Zigzag_ColWise();
void Flatten_Zigzag_ColWise_Reverse();
void Calculate_RowCol_Sums();


int main()
{
	int choice;

	do
	{
		cout << "\n========== 2D Array Operations Menu ==========\n";
		cout << "1. Flatten Row-Major          (Left to Right, Top to Bottom)\n";
		cout << "2. Flatten Row-Major Reverse  (Right to Left, Bottom to Top)\n";
		cout << "3. Flatten Column-Major        (Top to Bottom, Left to Right)\n";
		cout << "4. Flatten Column-Major Reverse(Bottom to Top, Right to Left)\n";
		cout << "5. Flatten Zigzag Row-Wise     (Snake Row Traversal)\n";
		cout << "6. Flatten Zigzag Row Reverse  (Reverse Snake Row Traversal)\n";
		cout << "7. Flatten Zigzag Col-Wise     (Snake Column Traversal)\n";
		cout << "8. Flatten Zigzag Col Reverse  (Reverse Snake Column Traversal)\n";
		cout << "9. Calculate Row and Column Sums\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1: Flatten_RowMajor();              break;
		case 2: Flatten_RowMajor_Reverse();      break;
		case 3: Flatten_ColMajor();              break;
		case 4: Flatten_ColMajor_Reverse();      break;
		case 5: Flatten_Zigzag_RowWise();        break;
		case 6: Flatten_Zigzag_RowWise_Reverse();break;
		case 7: Flatten_Zigzag_ColWise();        break;
		case 8: Flatten_Zigzag_ColWise_Reverse();break;
		case 9: Calculate_RowCol_Sums();         break;
		case 0: cout << "Exiting...\n";          break;
		default: cout << "Invalid choice! Please try again.\n";
		}

	} while (choice != 0);

	return 0;
}


// Task 1 — Load from file, flatten row by row left-to-right, top-to-bottom
void Flatten_RowMajor()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			Arr[_size] = arr[i][j], _size++;

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 2 — Load from file, flatten row by row right-to-left, bottom-to-top
void Flatten_RowMajor_Reverse()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = R - 1; i >= 0; i--)
		for (int j = C - 1; j >= 0; j--)
			Arr[_size] = arr[i][j], _size++;

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 3 — Load from file, flatten column by column top-to-bottom, left-to-right
void Flatten_ColMajor()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = 0; i < C; i++)
		for (int j = 0; j < R; j++)
			Arr[_size] = arr[j][i], _size++;

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 4 — Load from file, flatten column by column bottom-to-top, right-to-left
void Flatten_ColMajor_Reverse()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = C - 1; i >= 0; i--)
		for (int j = R - 1; j >= 0; j--)
			Arr[_size] = arr[j][i], _size++;

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 5 — Load from file, zigzag/snake traversal row-wise (odd rows reversed)
void Flatten_Zigzag_RowWise()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = 0; i < R; i++)
	{
		if (i % 2 != 0)
			for (int j = C - 1; j >= 0; j--)
				Arr[_size] = arr[i][j], _size++;
		else
			for (int j = 0; j < C; j++)
				Arr[_size] = arr[i][j], _size++;
	}

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 6 — Load from file, reverse zigzag row-wise starting from last row
void Flatten_Zigzag_RowWise_Reverse()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = R - 1; i >= 0; i--)
	{
		if (i % 2 == 0)
			for (int j = C - 1; j >= 0; j--)
				Arr[_size] = arr[i][j], _size++;
		else
			for (int j = 0; j < C; j++)
				Arr[_size] = arr[i][j], _size++;
	}

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 7 — Load from file, zigzag/snake traversal column-wise (odd columns reversed)
void Flatten_Zigzag_ColWise()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = 0; i < C; i++)
	{
		if (i % 2 == 0)
			for (int j = 0; j < R; j++)
				Arr[_size] = arr[j][i], _size++;
		else
			for (int j = R - 1; j >= 0; j--)
				Arr[_size] = arr[j][i], _size++;
	}

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 8 — Load from file, reverse zigzag column-wise starting from last column
void Flatten_Zigzag_ColWise_Reverse()
{
	ResetArrays();
	int R, C;
	cout << "Enter Rows: ";    cin >> R;
	cout << "Enter Columns: "; cin >> C;

	Loadfile("Load.txt", R, C);

	for (int i = C - 1; i >= 0; i--)
	{
		if (i % 2 != 0)
			for (int j = 0; j < R; j++)
				Arr[_size] = arr[j][i], _size++;
		else
			for (int j = R - 1; j >= 0; j--)
				Arr[_size] = arr[j][i], _size++;
	}

	Print1d("1D Array");
	cout << "2D array:-" << endl;
	Print2D(R, C);
}


// Task 9 — Take user input for 2D array, compute and display row sums and column sums
void Calculate_RowCol_Sums()
{
	ResetArrays();
	int R, C;
	cout << "Enter Number of Rows/Cols: ";
	cin >> R >> C;
	cout << endl;

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			cin >> arr[i][j];

	for (int i = 0; i < R; i++)
		Arr[i] = Row_Sum(i, C);

	for (int i = 0; i < C; i++)
		Arr[i + R] = Cols_Sum(R, i);

	cout << "\nRow list: ";
	for (int i = 0; i < R; i++)
		cout << Arr[i] << " ";

	cout << "\nCol list: ";
	for (int i = 0; i < C; i++)
		cout << Arr[i + R] << " ";

	cout << endl;
}
