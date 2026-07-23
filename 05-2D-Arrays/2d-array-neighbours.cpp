#include<iostream>
#include<Windows.h>
using namespace std;

const int Rows =10, Cols = 10;
int arr[Rows][Cols] = {};
int arr2[Rows][Cols] = {};
int arr3[Rows][Cols] = {};

int Up(int r, int c, int rows, int cols)
{
	return (r - 1 >= 0) ? arr[r - 1][c] : 0;
}

int Down(int r, int c, int rows, int cols)
{
	return (r + 1 < rows) ? arr[r + 1][c] : 0;
}

int Left(int r, int c, int rows, int cols)
{
	return (c-1 >= 0 ) ? arr[r][c-1] : 0;
}

int Right(int r, int c, int rows, int cols)
{
	return (c + 1 < cols) ? arr[r][c + 1] : 0;
}

int URD ( int r, int c, int rows, int cols)
{
	return (r - 1 >= 0 && c-1 >= 0) ? arr[r-1][c - 1] : 0;
}

int ULD(int r, int c, int rows, int cols)
{
	return (r - 1 >= 0 && c + 1 <cols) ? arr[r - 1][c + 1] : 0;
}

int LRD(int r, int c, int rows, int cols)
{
	return (r + 1 <rows && c - 1 >= 0 ) ? arr[r + 1][c - 1] : 0;
}

int LLD(int r, int c, int rows, int cols)
{
	return (r + 1 < rows && c + 1 < cols) ? arr[r + 1][c + 1] : 0;
}







void print_arr(const char msg[],int _rows, int _cols)
{
	cout << msg<<endl;
	for (int i = 0; i < _rows; i++)
	{
		cout << "Row: "<<i<<" [";
		for (int j = 0; j < _cols; j++)
			cout << arr[i][j] << " ";
		cout << "]" << endl;
	}
}

void print_arr2(const char msg[], int _rows, int _cols)
{
	cout << msg << endl;
	for (int i = 0; i < _rows; i++)
	{
		cout << "Row: " << i << " [";
		for (int j = 0; j < _cols; j++)
			cout << arr2[i][j] << " ";
		cout << "]" << endl;
	}
}

void print_arr3(const char msg[], int _rows, int _cols)
{
	cout << msg << endl;
	for (int i = 0; i < _rows; i++)
	{
		cout << "Row: " << i << " [";
		for (int j = 0; j < _cols; j++)
			cout << arr3[i][j] << " ";
		cout << "]" << endl;
	}
}

void print_1d(const char msg[],int* arr, int size)
{
	cout << msg << " [ ";
	for (int i = 0; i < size; i++)
		cout << arr[i]<<" ";
	cout << "]" << endl;
}

void initialise(int& rows, int& cols)
{
	cout << "Enter the rows/cols: ";
	cin >> rows >> cols;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		 arr[i][j]=rand()%10;
}

void initialise_arr2(int& rows, int& cols)
{
	cout << "Enter the rows/cols: ";
	cin >> rows >> cols;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr2[i][j] = rand() % 10;
}

void input(int& rows, int& cols)
{
	cout << "Enter the rows/cols: ";
	cin >> rows >> cols;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cin>> arr[i][j];
}

bool is_valid(int rows, int cols, int r,int c)
{
	return r >= 0 and r <= rows - 1 and c >= 0 and c <= cols - 1;
}

int* up(int r,int c,int& size)
{
	size = 0;
	int* _arr = new int[r + 1-1];

	for (int i = r-1; i >= 0; i--)
		_arr[size++] = arr[i][c];

	return _arr;
}

int* down(int rows,int r, int c, int& size)
{
	size = 0;
	int* _arr = new int[rows - r-1] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = r+1; i <rows; i++)
		_arr[size++] = arr[i][c];

	return _arr;
}

int* right(int cols, int r, int c, int& size)
{  
	// 0 1 2     0 0  3 - 1= 2
	// 1 2 3
	size = 0;
	int* _arr = new int[cols - c-1] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = c+1; i < cols; i++)
		_arr[size++] = arr[r][i];

	return _arr;
}

int* left(int cols, int r, int c, int& size)
{
	// 0 1 2     0 1  c+1
	// 1 2 3
	size = 0;
	int* _arr = new int[c] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = c-1; i >=0 ; i--)
		_arr[size++] = arr[r][i];

	return _arr;
}

int* travesal_right_up(int rows, int r, int c, int& size)
{
	// 0 1 2     0 1  c+1
	// 1 2 3
	// 1 2 2
	size = 0;
	int* _arr = new int[rows] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = r,j=c; i >= 0 && j>=0;i--,j--)
		_arr[size++] = arr[i][j];

	return _arr;
}

int* travesal_right_down(int rows,int cols, int r, int c, int& size)
{
	// 0 1 2     0 1  c+1
	// 1 2 3
	// 1 2 2

	size = 0;
	int* _arr = new int[rows] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = r,j=c; i < rows && j<cols; i++,j++)
		_arr[size++] = arr[i][j];

	return _arr;
}

int* travesal_left_up(int rows,int cols, int r, int c, int& size)
{
	//  
	// 0 1 2     0 1  c+1
	// 1 2 3
	// 1 2 2                    -: i == j-1 :-
	size = 0;
	int* _arr = new int[rows] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = r, j = c; i >= 0 && j < cols; i--, j++)
		_arr[size++] = arr[i][j];

	return _arr;
}

int* travesal_left_down(int cols, int rows, int r, int c, int& size)
{
	
	// 0 1 2     0 1  c+1
	// 1 2 3
	// 1 2 2                    -: i == j-1 :-
	size = 0;
	int* _arr = new int[rows] {};  // 5 , 2 ---> 5 - 2 = 3    2 3 4 

	for (int i = r, j = c; i < rows&& j >=0 ; i++, j--)
		_arr[size++] = arr[i][j];

	return _arr;
}





void Task1()
{
	int rows, cols;
	int* _arr = nullptr;
	int size = 0;
	initialise(rows, cols);
	
	int r, c,choice;


	do {
		print_arr("The arr: ", rows, cols);

		cout << "\n<============================================>" << endl;
		cout << "                  Menu" << endl;
		cout << "<============================================>" << endl;
		cout << "0. Exit" << endl;
		cout << "1. Up" << endl;
		cout << "2. Down" << endl;
		cout << "3. Left" << endl;
		cout << "4. Right" << endl;
		cout << "5. Upper-Right" << endl;
		cout << "6. Upper-Left" << endl;
		cout << "7. Lower-Right" << endl;
		cout << "8. Lower-Left" << endl;
		cout << "9. Reintialise Matrix" << endl;
		cout << "<============================================>" << endl;

		cout << "Choice: ";
		cin >> choice;

		if (choice != 9 and choice != 0)
		{
			cout << "Enter coordinates: ";
			cin >> r >> c;
		}
		if (choice != 9 && choice != 0 && !is_valid(rows, cols, r, c))
		{
			cout << "Coordinates are out of the matrix" << endl;
			continue;
		}


		switch (choice)
		{

		case 0:
			delete[] _arr;
			return;
		case 1:
			_arr = up(r, c, size);
			system("cls");
			print_1d("up: ", _arr, size);
			break;

		case 2:
			_arr = down(rows, r, c, size);
			system("cls");
			print_1d("down: ", _arr, size);
			break;
		case 3:
		    _arr = left(cols, r, c, size);
			system("cls");
			print_1d("left: ", _arr, size);
			break;
		case 4:
			_arr = right(cols, r, c, size);
			system("cls");
			print_1d("right: ", _arr, size);
			break;

		case 5:
			_arr = travesal_right_up(rows, r, c, size);
			system("cls");
			print_1d("right_up: ", _arr, size);
			break;
		case 6:
			_arr = travesal_left_up(rows,cols, r, c, size);
			system("cls");
			print_1d("left_up: ", _arr, size);
			break;
		case 7:
			_arr = travesal_right_down(rows, cols, r, c, size);
			system("cls");
			print_1d("right_down: ", _arr, size);
			break;

		case 8:
			_arr = travesal_left_down(cols,rows, r, c, size);
			system("cls");
			print_1d("left_down: ", _arr, size);
			break;
		case 9:
			system("cls");
			initialise(rows, cols);
			break;
		}
		

	
	} while (choice != 0);
}

void Task2()
{
	int rows1 = 0, cols1 = 0;
	int rows2 = 0, cols2 = 0;

	initialise(rows1, cols1);
	print_arr("", rows1, cols1);
	initialise_arr2(rows2, cols2);
	print_arr2("", rows2, cols2);

	if (rows1 != rows2 || cols1 != cols2)
	{
		cout << "\nError:  Dimension should be same for addition";
		return ;
	}


	for (int i = 0; i < rows1; i++)
		for (int j = 0; j < cols1; j++)
			arr[i][j] += arr2[i][j];

	print_arr("The Addition: ", rows1, cols1);
}

void Task3()
{
	int rows1 = 0, cols1 = 0;
	int rows2 = 0, cols2 = 0;

	initialise(rows1, cols1);
	print_arr("", rows1, cols1);
	initialise_arr2(rows2, cols2);
	print_arr2("", rows2, cols2);

	if (rows1 != rows2 || cols1 != cols2)
	{
		cout << "\nError:  Dimension should be same for Subtraction";
		return ;
	}


	for (int i = 0; i < rows1; i++)
		for (int j = 0; j < cols1; j++)
			arr[i][j] -= arr2[i][j];

	print_arr("The Subtraction: ", rows1, cols1);

}

void Task4()
{
	int rows1 = 0, cols1 = 0;
	int rows2 = 0, cols2 = 0;

	initialise(rows1, cols1);
	print_arr("", rows1, cols1);
	initialise_arr2(rows2, cols2);
	print_arr2("", rows2, cols2);

	if (cols1 != rows2)
	{
		cout << "\nError: cols of first matrix must equal rows of second";
		return;
	}

	for (int i = 0; i < rows1; i++)
	{
		for (int j = 0; j < cols2; j++) 
		{
			arr3[i][j] = 0;
			for (int k = 0; k < cols1; k++)
			{
				arr3[i][j] += arr[i][k] * arr2[k][j];
			}
		}
	}

	print_arr3("The Multiplication: ", rows1, cols2);  // not cols1

}

void Task5()
{
	int rows1 = 0, cols1 = 0;
	int rows2 = 0, cols2 = 0;

	initialise(rows1, cols1);
	print_arr("", rows1, cols1);
	initialise_arr2(rows2, cols2);
	print_arr2("", rows2, cols2);

	if (rows1 != rows2 || cols1 != cols2)
	{
		cout << "\nError:  Dimension should be same for Subtraction";
		return ;
	}


	for (int i = 0; i < rows1; i++)
		for (int j = 0; j < cols1; j++)
			arr3[i][j] = (arr[i][j] == arr2[i][j]) ? arr[i][j] : 0;

	print_arr3("The Common numbers: ", rows1, cols1);
}

void Task6()
{
	int rows = 0, cols = 0;
	initialise(rows, cols);
	print_arr("The arr: ", rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr2[i][j] = Up(i, j, rows, cols) + Down(i, j, rows, cols) + Left(i, j, rows, cols) + Right(i, j, rows, cols) + URD(i, j, rows, cols) + ULD(i, j, rows, cols) + LRD(i, j, rows, cols) + LLD(i, j, rows, cols);;



	print_arr2("The arr: ", rows, cols);

}

void Task7()
{
	int rows = 0, cols = 0;
	initialise(rows, cols);
	print_arr("The arr: ", rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			arr2[i][j] = Up(i, j, rows, cols) + Down(i, j, rows, cols) + Left(i, j, rows, cols) + Right(i, j, rows, cols);



	print_arr2("The arr: ", rows, cols);

}

int main()
{ 
	
	int  choice=0;


	do {
		
		system("cls");
		cout << "\n<============================================>" << endl;
		cout << "                  Menu" << endl;
		cout << "<============================================>" << endl;
		cout << "0. Exit" << endl;
		cout << "1. Task1" << endl;
		cout << "2. Task2" << endl;
		cout << "3. Task3" << endl;
		cout << "4. Task4" << endl;
		cout << "5. Task5" << endl;
		cout << "6. Task6" << endl;
		cout << "7. Task7" << endl;
		cout << "<============================================>" << endl;

		cout << "Choice: ";
		cin >> choice;


		switch (choice)
		{

		case 0:
			system("cls");
			cout << "Exiting!" << endl;
			return 0;
		case 1:
			system("cls");
			Task1();
			break;

		case 2:
			system("cls");
			Task2();
			break;
		case 3:
			system("cls");
			Task3();
			break;
		case 4:
			system("cls");
			Task4();
			break;

		case 5:
			system("cls");
			Task5();
			break;
		case 6:
			Task6();
			break;
		case 7:
			system("cls");
			Task7();
			break;

		default:
			system("cls");
			cout << "Invalid Choice!" << endl;
			break;




			cout << "Enter any key to continue!" << endl;
			cin.ignore();
			cin.get();
		}



	} while (choice != 0);

	return 0;
}