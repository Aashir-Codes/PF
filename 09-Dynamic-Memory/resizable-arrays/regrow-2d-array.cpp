#include <iostream>
using namespace std;

int** regrowRow(int** ptr2d, int& r, int& c) {
	int** nptr2d = nullptr;
	nptr2d = new int* [r + 1];
	for (int i = 0; i < r; i++)
		nptr2d[i] = ptr2d[i];
	nptr2d[r] = new int[c];
	delete[] ptr2d;
	r++;
	return nptr2d;
}

int** regrowCol(int** ptr2d, int& r, int& c) {
	int** nptr2d = nullptr;
	nptr2d = new int* [r];
	for (int j = 0; j < r; j++)
		nptr2d[j] = new int[c + 1];
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			nptr2d[i][j] = ptr2d[i][j];
	for (int i = 0; i < r; i++)
		delete[] ptr2d[i];
	delete[] ptr2d;
	c++;
	return nptr2d;
}


void Q4() {
	int row, col;
	int** arr = nullptr;
	cout << "Enter number of rows: ";
	cin >> row;
	cout << "Enter number of columns: ";
	cin >> col;
	arr = new int* [row];
	for (int i = 0; i < row; i++) {
		arr[i] = new int[col];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "Enter element (" << i << "," << j << "): ";
			cin >> arr[i][j];
		}
		cout << endl;
	}
	cout << "\nEnter Row : ";
	arr = regrowRow(arr, row, col);
	for (int i = 0; i < col; i++)
	{
		cin >> arr[row - 1][i];
	}
	arr = regrowCol(arr, row, col);
	cout << "\nEnter col : ";
	for (int i = 0; i < row; i++)
	{
		cin >> arr[i][col - 1];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < row; i++)
	{
		delete[] arr[i];
	}

	delete[] arr;


}
void Q2() {
	int row, col;
	int** arr = nullptr;
	cout << "Enter number of rows: ";
	cin >> row;
	cout << "Enter number of columns: ";
	cin >> col;
	arr = new int* [row];
	int size = row * col;

	for (int i = 0; i < row; i++)
	{
		arr[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "Enter element (" << i << "," << j << "): ";
			cin >> arr[i][j];
		}
		cout << endl;
	}

	arr=regrowRow(arr, row, col);
	for (int i = 0; i < col; i++) {
		cin >> arr[row-1][i];
	}
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}
void Q3()
{
	int row, col;
	int** arr = nullptr;
	cout << "Enter number of rows: ";
	cin >> row;
	cout << "Enter number of columns: ";
	cin >> col;
	arr = new int* [row];
	int size = row * col;

	for (int i = 0; i < row; i++)
	{
		arr[i] = new int[col];
	}
	cout << "enter element" << endl;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			
			cin >> arr[i][j];
		}
		cout << endl;
	}

	arr = regrowCol(arr, row, col);
	for (int i = 0; i < col; i++) {
		cin >> arr[i][col-1];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}
void Q1()
{

	int row, col;
	int** arr = nullptr;
	cout << "Enter number of rows: ";
	cin >> row;
	cout << "Enter number of columns: ";
	cin >> col;
	arr = new int* [row];


	for (int i = 0; i < row; i++)
	{
		arr[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << "Enter element (" << i << "," << j << "): ";
			cin >> arr[i][j];
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < row; i++)
	{
		delete[] arr[i];
	}

	delete[] arr;

}
int main()
{
	char choice = 0;
	do
	{
		cout << " <=========================================================>" << endl;
		cout << "                             Menu" << endl;
		cout << "                            1.Q1" << endl;
		cout << "                            2.Q2" << endl;
		cout << "                            3.Q3" << endl;
		cout << "                            4.Q4" << endl;
		cout << "                            5.exit" << endl;
		cout << " <=========================================================>" << endl;

		cin >> choice;
		switch (choice) {
		case '1':
			Q1();
			break;
		case '2':
			Q2();
			break;
		case '3':
			Q3();
			break;
		case '4':
			Q4();
			break;
		case '5':
			cout << " <=================== Exiting =================>" << endl;
			break;
		default:
			cout << "invalid choice" << endl;


		}

	} while (choice != '5');
	return 0;
}