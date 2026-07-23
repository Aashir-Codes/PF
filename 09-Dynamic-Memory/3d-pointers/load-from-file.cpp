#include <iostream>
#include <fstream>

using namespace std;

int* regrow1d(int* &arr, int& size)
{
	int* newptr = new int [size + 1] {};

	for (int i = 0; i < size; i++)
		newptr[i] = arr[i];

	delete[] arr;
	
	return newptr;
}

int*** load(int &n,int* &Rows,int& size)
{
	int*** matrixes = nullptr;

	ifstream Rdr("Matrix.txt");

	if (!Rdr.is_open())
	{
		cout << "File Not Opened ! " << endl;
		exit(1);
	}

	 n = 0;  // :  It will hold n number of matixes

	 Rdr >> n;

	 matrixes = new int** [n] {};  //   :Intialised  with a null ptr  


	 for (int i = 0; i < n; i++)
	 {
		 int rows, cols;
		 Rdr >> rows;


		 matrixes[i] = new int* [rows] {};

		 Rows = regrow1d(Rows, size);

		 Rows[size++] = rows;

		 for (int j = 0; j < rows; j++)
		 {
			Rdr  >> cols  ;
			matrixes[i][j] = new int [cols+1] {cols};
			for (int k = 1; k <= cols; k++)
			{
				int temp = 0;
				Rdr >> temp;
				matrixes[i][j][k] = temp;
			 }
		 }
	 }


	Rdr.close();



	return matrixes;
}

void print(int ***matrixes, int n,int* rows, int size)
{
	for (int i = 0; i < n; i++)
	{
		cout << "\n       Matrix: " << i + 1 << endl;
		for (int j = 0; j < rows[i]; j++)
		{
			for (int k = 1; k <= matrixes[i][j][0]; k++)
			{
				cout << matrixes[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}

void destructor(int***& matrixes, int& n, int*& Rows, int size)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < Rows[i]; j++)
			delete[] matrixes[i][j];
	}


	for (int i = 0; i < n; i++)
		delete[] matrixes[i];

	delete[] matrixes;

	delete[] Rows;
}



int main()
{

	int*** matrixes = nullptr;
	int* Rows = nullptr;
	int size=0;
	int n=0;

	matrixes = load(n, Rows, size);

	print(matrixes, n, Rows, size);

	destructor(matrixes, n, Rows, size);

	return 0;
}