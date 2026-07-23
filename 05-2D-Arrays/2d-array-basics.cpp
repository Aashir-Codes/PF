#include <iostream>
using namespace std;
void print(int array[][4], int rows, int column) {

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < column; j++)

		{

			cout << array[i][j];
		}
		cout << "\n";
	}




}
void print(int array[][10], int rows, int column) {

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < column; j++)

		{

			cout << array[i][j] << " " ;
		}
		cout << "\n";
	}




}
void _swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;


}
void swap_array(int array[][4], int a, int b, int column) {


	for (int j = 0; j < column; j++)

	{
		_swap(array[a][j], array[b][j]);

	}


}

void swap_col(int array[][4], int a, int b, int rows) {


	for (int j = 0; j < rows; j++)

	{
		_swap(array[j][a], array[j][b]);

	}


}
void _add(int array[][10], int a, int b, int add[][10], int gray[][10]) {

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++)

		{
			add[i][j] = array[i][j] + gray[i][j];

		}
	}

}
void fill_array(int array[][10], int rows, int column) {

	for (int i = 0; i < rows; i++) {


		for (int j = 0; j < column; j++) {
			cout << "Enter at index:" << "(" << i << "," << j <<
")"; 			cout << endl; 			cin >> array[i][j];
		}
	}


}
int t3() {

	int rows = 0;
	int column = 0;
	int r2 = 0;
	int c2 = 0;
	cout << "Ente rows and column of of matrix 1" << endl;
	cin >> rows >> column;

	cout << "Enter rows and column of of matrix 2" << endl;
	cin >> r2 >> c2;
	if (c2 != column || rows != r2) {
		cout << "Their dimension should be same " << endl;
		cout << "Enter Again !" << endl;
		t3();
	}
	const int a = 10;
	int array[a][a] = {};
	int gray[a][a] = {};
	cout << "Fill first matrix" << endl;
	fill_array(array, rows, column);
	print(array, rows, column);
	cout << "Fill second matrix" << endl;
	fill_array(gray, r2, c2);
	print(gray, r2, c2);
	int add[a][a] = {};
	_add(array, rows, column, add, gray);

	cout << "<<=== Output ===>" << endl;
	print(add, rows, column);

	return 0;
}
int t4() {


	int rows = 0;
	int column = 0;
	int r2 = 0;
	int c2 = 0;
	cout << "Ente rows and column of of matrix 1" << endl;
	cin >> rows >> column;

	cout << "Enter rows and column of of matrix 2" << endl;
	cin >> r2 >> c2;
	if (column!=r2) {
		cout << "column of first matrix should be equal to rows of second matrix " << endl; 		cout << "Enter Again !" << endl;
t4();
	}
	const int a = 10;
	int array[a][a] = {};
	int gray[a][a] = {};
	cout << "Fill first matrix" << endl;
	fill_array(array, rows, column);
	cout << " first matrix" << endl;
	print(array, rows, column);
	cout <<  " second matrix" << endl;
	fill_array(gray, r2, c2);
	print(gray, r2, c2);
	int multiply[a][a] = {};
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < c2; j++) {
			for (int t = 0; t < r2; t++) {

				multiply[i][j] += array[i][t] * gray[t][j];
			}

		}
	}
	cout << "<<=== Output ===>" << endl;
	print(multiply, rows,c2);

	return 0;

}
int t1() {
	const int column = 4;
	const int rows = 2;
	int array[rows][column] = { 1,2,3,4,5,6,7,8 };

	cout << "<             The matrix            >" << endl;
	print(array, rows, column);
	int x = 0, y = 0;


	cout << "enter rows you want to swap" << endl;
	cin >> x >> y;
	x -= 1;
	y -= 1;
	swap_array(array, x, y, column);
	cout << "<             The matrix            >" << endl;
	print(array, rows, column);
	return 0;
}
int t2() {
	const int column = 4;
	const int rows = 2;
	int array[rows][column] = { 1,2,3,4,5,6,7,8 };

	cout << "<             The matrix            >" << endl;
	print(array, rows, column);
	int x = 0, y = 0;

	cout << "enter column you want to swap" << endl;
	cin >> x >> y;
	x -= 1;
	y -= 1;
	swap_col(array, x, y, column);
	cout << "<             The matrix            >" << endl;
	print(array, rows, column);
	return 0;

}
void menu() {
	cout << "<============  lab 13 =================>" << endl; 	
    cout << " <============ 1.Task 1 =================>" << endl; 
    cout << " <============ 2.Task 2 =================>" << endl; 	
    cout << " <============ 3.Task 3 =================>" << endl; 
	cout << " <============ 4.Task 4 =================>" << endl; 	
    cout << " <============ 5. Exit  =================>" << endl;
}
int main() {


	char choice = 0;

	do {
		menu();
		cout << "Enter Choice:";
		cin >> choice;
		switch (choice) {
		case '1':
			t1();
			break;
		case'2':
			t2();
			break;
		case'3':
			t3();
			break;
		case'4':
			t4();
			break;
		case'5':
			cout << "<===================================>" << endl;
			cout << "                 Exiting               " <<
endl; 			cout << "<===================================>"
<< endl;

			return 0;
		}


	} while (choice != '5');





}
