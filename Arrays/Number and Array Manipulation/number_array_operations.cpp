#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int arr[1000] = {};
int Size = 0;

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();


int Reverse_Num(int num);
void Load();
void Print(int [], int );
void Swap(int& , int& );
void Reverse(int arr[], int Size);
bool is_palindrome(int arr[], int Size);
int compile(int num, int num2)
{
	num = num * 10 + num2;
	return num;
}

void ClearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int main()
{
	int choice = 0;

	do
	{
		ClearScreen();
		cout << "============ MENU ============" << endl;
		cout << " 1. Reverse a Number" << endl;
		cout << " 2. Reverse an Array (from file)" << endl;
		cout << " 3. Check Array Palindrome" << endl;
		cout << " 4. Check Number Palindrome" << endl;
		cout << " 5. Nth Fibonacci Number" << endl;
		cout << " 6. Combine Array into a Number" << endl;
		cout << " 7. Reverse Binary Number" << endl;
		cout << " 0. Exit" << endl;
		cout << "=============================" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1: Task1(); break;
		case 2: Task2(); break;
		case 3: Task3(); break;
		case 4: Task4(); break;
		case 5: Task5(); break;
		case 6: Task6(); break;
		case 7: Task7(); break;
		case 0: cout << "Exiting..." << endl; break;
		default: cout << "Invalid choice! Please try again." << endl;
		}

		if (choice != 0)
		{
			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
		}

	} while (choice != 0);

	return  0;
}

void Task1()
{

	int num = 0;
	cout << "Enter the number : ";
	cin >> num;
	cout << endl;
	

	cout << "The new number: " << Reverse_Num(num);

}

void Task2()
{
	Load();
	Reverse(arr, Size);
	Print(arr, Size);

}

void Task3()
{
	Load();


	if (is_palindrome(arr, Size))
	{
		cout << "   The loaded Array is Palindrome" << endl;
	}
	else {
		cout << "   The loaded Array is not  Palindrome" << endl;
	}
}
void Task4()
{
	int num = 0;
	cout << "Enter the numebr : ";
	cin >> num;

	if (num == Reverse_Num(num)) {
		cout << "Palindrome" << endl;
	}
	else {
		cout << "Not Palindrome" << endl;
	}

}

void Task5() {


	cout << "which nth Fibonacci number you want: ";
	int n = 0;
	cin >> n;
	cout << endl;

	if (n <= 0) {
		cout << "Please enter a positive number." << endl;
		return;
	}

	int zero = 0;
	int one = 1;
	int num = zero;   // Fib(1) = 0

	for (int count = 2; count <= n; count++)
	{
		num = one + zero;
		zero = one;
		one = num;
	}

	cout << n << " Fibonacci number is " << num << endl;


}
void Task6() {
	Load();

	long long int num = 0;

	for (int i = 0; i < Size; i++)
	{
		num = compile(num, arr[i]);
	}

	cout << "The number is " << num << endl;
}

void Task7()
{


	int num = 0;
	cout << "Enter the number : ";
	cin >> num;
	cout << endl;


	int rev_num = 0;
	bool flag = 0;
	int count = 0;
	while (num != 0)
	{
		if (num % 2 == 0 && flag == 0) {
			count++;
		}
		else {
			flag = 1;
			int temp = num % 2;
			rev_num = rev_num * 10 + temp;
		}
		num /= 2;
	}
	if (count != 0)
	{
		for (int i = 1; i <= count; i++)
			rev_num *= 10;

		cout << "Rev num : " << rev_num << endl;
		return;
	}

	cout << "Rev num : " << Reverse_Num(rev_num) << endl;

}
void Load()
{
	ifstream  Rdr("input.txt");
	int i = 0;
	Size = 0;
	while (!Rdr.eof())
	{
		Rdr >> arr[i];
		Rdr.ignore();
		i++;
		Size++;

	}

	Size--;

	Rdr.close();
}

void Print(int arr[], int Size)
{
	cout << "[ ";
	for (int i = 0; i < Size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "] " << endl;
}
void Swap(int& a, int& b) {
	int temp = b;
	b = a;
	a = temp;
}


void Reverse(int arr[], int Size)
{
	int start = 0;
	int end = Size - 1;


	while (start <= end)
	{
		Swap(arr[start], arr[end]);
		start++;
		end--;
	}
}
bool is_palindrome(int arr[], int Size) {

	int start = 0;
	int end = Size - 1;


	while (start <= end)
	{
		if (arr[start] != arr[end]) return false;
		start++;
		end--;
	}

	return true;

}


int Reverse_Num(int num)
{
	int rev_num = 0;
	while (num != 0)
	{
		int temp = num % 10;
		num /= 10;
		rev_num = rev_num * 10 + temp;

	}

	return rev_num;
}