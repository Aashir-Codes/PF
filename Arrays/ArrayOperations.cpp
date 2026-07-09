#include<iostream>
#include <fstream>
using namespace std;


int arr[10000] = {};
char Arr[1000] = {};
int _Size = 0;
int Size = 0;


int Frequency(int arr[], int size, int target)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (arr[i] == target)
			count++;

	return count;
}


bool bubbling(int arr[], int size)
{
	bool Bubbled = 0;
	for (int i = 0; i+1 < size; i++)
	{
		if (Frequency(arr, size, arr[i]) < Frequency(arr, size, arr[i + 1]))
			swap(arr[i], arr[i + 1]),Bubbled=1;
	}

	return Bubbled;


}


void Bubble_Sort(int arr[], int size)
{
	while (bubbling(arr, size));
}

void Print(const char msg[], int arr[], int size)
{

	cout << msg << " [ ";
	for (int i = 0; i < Size; i++)
		cout << arr[i] << " ";
	cout << "]" << endl;
}

void Print(const char msg[], char arr[], int size)
{

	cout << msg << " [ ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << "]" << endl;
}


void Load()
{
	ifstream Rdr("Load.txt");

	if (!Rdr) {
		cout << "File not opened!" << endl;
		exit(1);
	}

	
	while (!Rdr.eof() && Size < 10000)
	{
		Rdr >> arr[Size];
		Size++;
	}

	Size--;
	Rdr.close();


}


void Load_char()
{
	ifstream Rdr("Load.txt");

	if (!Rdr) {
		cout << "File not opened!" << endl;
		exit(1);
	}

	
	while (!Rdr.eof() && _Size < 10000)
	{
		char a = 0;
		Rdr >> a;
		if (a == 'm' || a == 'b' || a == 'a')
		{
			Arr[_Size] = a;
			_Size++;
		}
	}

	Rdr.close();


}

bool is_in_the_arr(int target, int arr[], int size)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == target)return true;

	return false;

}


bool bubbling_even_odd(int arr[], int size)
{
	bool Bubbled = 0;
	for (int i = 0; i + 1 < size; i++)
	{
		if (arr[i] % 2 != 0 && arr[i+1] % 2 == 0)
			swap(arr[i], arr[i + 1]), Bubbled = 1;
	}

	return Bubbled;
}

void Bubble_Sort_even_odd(int arr[], int size)
{
	while (bubbling_even_odd(arr, size));
}


bool Bubbling(int arr[], int size)
{
	bool Bubbled = 0;
	for (int i = 0; i + 1 < size; i++)
	{
		if (arr[i] < arr[i+1] )
			swap(arr[i], arr[i + 1]), Bubbled = 1;
	}

	return Bubbled;
}

void _Bubble_Sort(int arr[], int size)
{
	while (Bubbling(arr, size));
}


bool Bubbling_Asc(int arr[], int size)
{
	bool Bubbled = 0;
	for (int i = 0; i + 1 < size; i++)
	{
		if (arr[i] > arr[i + 1])
			swap(arr[i], arr[i + 1]), Bubbled = 1;
	}

	return Bubbled;
}

void _Bubble_Sort_Asc(int arr[], int size)
{
	while (Bubbling_Asc(arr, size));
}



bool bubbling_wrt_number(int arr[], int size, int value)
{
	bool Bubbled = 0;
	for (int i = 0; i + 1 < size; i++)
	{
		if (arr[i] == value)
			continue;
		if (arr[i] > value && arr[i+1]<value)
			swap(arr[i], arr[i + 1]), Bubbled = 1;
	}

	return Bubbled;
}

void Bubble_Sort_number(int arr[], int size, int value)
{
	while (bubbling_wrt_number(arr, size,value));
}


bool bubbling_m_a(char arr[], int size)
{
	bool Bubbled = 0;
	for (int i = 0; i + 1 < size; i++)
	{
		
	
		if (arr[i] == 'a' && arr[i + 1] != 'a')
			swap(arr[i], arr[i + 1]), Bubbled = 1;
		if (arr[i] == 'b' && arr[i - 1] != 'b')
			swap(arr[i], arr[i - 1]), Bubbled = 1;
	}

	return Bubbled;
}

void Bubble_Sort_m_a(char arr[], int size)
{
	while (bubbling_m_a(arr, size));
}


void Task1()
{
	Load();
	Bubble_Sort(arr, Size);
	Print("The Array: ", arr, Size);
}


void Task2()
{
	Load();
	int unique_arr[100] = {};
	int distinct_arr[100] = {};
	int unique_size = 0;
	int distinct_size = 0;

	for (int i = 0; i < Size; i++)
	{
		if (Frequency(arr, Size, arr[i]) == 1)
		{
			unique_arr[unique_size] = arr[i];
			unique_size++;
		}
		if (!is_in_the_arr(arr[i], distinct_arr, distinct_size))
		{
			distinct_arr[distinct_size] = arr[i];
			distinct_size++;
		}

	}


	Print("Unique arr: ", unique_arr, unique_size);
	Print("Distinct arr: ", distinct_arr, distinct_size);

}

void Task3() {

	Load();
	Bubble_Sort_even_odd(arr, Size);
	Print("Even / odd : ", arr, Size);
}

void Task4() {

	Load();
	Bubble_Sort_even_odd(arr, Size);
	Print("one's / zero's : ", arr, Size);
}

void Task5()
{
	Load();
	cout << "Enter the number: ";
	int n;
	cin >> n;
	Bubble_Sort_number(arr, Size, n);
	cout << endl;
	Print("one / zero : ", arr, Size);
}

void Task6()
{

	Load_char();
	cout << endl;
	Bubble_Sort_m_a(Arr, _Size);
	Print("one / zero : ", Arr, _Size);

}

void Task7()
{
	Load();
	int index = 0;

	if (Size % 2 == 0)
	{
		index = (Size + 1) / 2;
	}
	else
	{
		index = (Size / 2) + 1;
	}
	_Bubble_Sort(arr, Size);
	cout << "The median of an Array: " << arr[index];

}

void Task8()
{
	int arr1[100] = {};
	int arr2[100] = {};

	int size1 = 0;
	int size2 = 0;



	cout << "Enter Size (max: 100): ";
	cin >> size1;
	cout << endl;
	cout << "Enter Size (max: 100): ";
	cin >> size2;
	cout << endl;


	cout << "Enter enteries of Array one: ";

	for (int i = 0; i < size1; i++)
	{
		cin >> arr1[i];
		arr[Size] = arr1[i];
		Size++;
	}

	cout << "Enter enteries of Array two: ";

	for (int i = 0; i < size2; i++)
	{
		cin >> arr2[i];
		arr[Size] = arr2[i];
		Size++;
	}

	Print("The Concatenated Array: ", arr, Size);

}

void Task9()
{
	int arr1[100] = {};
	int arr2[100] = {};

	int size1 = 0;
	int size2 = 0;



	cout << "Enter Size (max: 100): ";
	cin >> size1;
	cout << endl;
	cout << "Enter Size (max: 100): ";
	cin >> size2;
	cout << endl;


	cout << "Enter enteries of Array one: ";

	for (int i = 0; i < size1; i++)
	{
		cin >> arr1[i];
		arr[Size] = arr1[i];
		Size++;
	}

	cout << "Enter enteries of Array two: ";

	for (int i = 0; i < size2; i++)
	{
		cin >> arr2[i];
		arr[Size] = arr2[i];
		Size++;
	}

	Print("The Concatenated Array: ", arr, Size);
	_Bubble_Sort_Asc(arr, Size);
	Print("The Sorted Array: ", arr, Size);
}

void Task10()
{
	int arr1[100] = {};
	int arr2[100] = {};

	int size1 = 0;
	int size2 = 0;



	cout << "Enter Size (max: 100): ";
	cin >> size1;
	cout << endl;
	cout << "Enter Size (max: 100): ";
	cin >> size2;
	cout << endl;


	cout << "Enter enteries of Array one: ";

	for (int i = 0; i < size1; i++)
	{
		cin >> arr1[i];

	}

	cout << "Enter enteries of Array two: ";

	for (int i = 0; i < size2; i++)
	{
		cin >> arr2[i];

	}




	int ptr1 = 0;
	int ptr2 = 0;

	for (int i = 0; i < size1 + size2; i++)
	{
		if (arr1[ptr1] < arr2[ptr2])
		{
			arr[i] = arr1[ptr1];
			ptr1++;
			Size++;
		}
		else {
			arr[i] = arr2[ptr2];
			ptr2++;
			Size++;
		}
	}

	Print("The Array: ", arr, Size);
}

void Task11()
{
	Load();

	int index = 0;

	for (int i = 0; i < Size; i++)
	{
		int Sum_right = 0, Sum_left = 0;
		for (int j = 0; j < i; j++)
			Sum_right += arr[j];

		for (int j = i + 1; j < Size; j++)
			Sum_left += arr[j];

		if (Sum_right == Sum_left)
		{
			index = i;
			break;

		}

	}

	cout << "The Equilbrium index: " << index << endl;

}

// Reset the global buffers so each task starts fresh, no matter the order
// the user picks them in. (Cross-platform: no OS-specific calls used here.)
void Reset()
{
	Size = 0;
	_Size = 0;
	for (int i = 0; i < 10000; i++) arr[i] = 0;
	for (int i = 0; i < 1000; i++)  Arr[i] = 0;
}

void ShowMenu()
{
	cout << "\n========================================\n";
	cout << "        PFX ASM 06  -  Main Menu\n";
	cout << "========================================\n";
	cout << " 1.  Sort by frequency (descending)\n";
	cout << " 2.  Unique & distinct elements\n";
	cout << " 3.  Segregate even / odd\n";
	cout << " 4.  Segregate ones / zeros\n";
	cout << " 5.  Partition array around a number\n";
	cout << " 6.  Sort characters (a / b / m)\n";
	cout << " 7.  Median of the array\n";
	cout << " 8.  Concatenate two arrays\n";
	cout << " 9.  Concatenate & sort (ascending)\n";
	cout << "10.  Merge two sorted arrays\n";
	cout << "11.  Equilibrium index\n";
	cout << " 0.  Exit\n";
	cout << "----------------------------------------\n";
	cout << "Enter your choice: ";
}

int main()
{
	int choice = -1;

	do
	{
		ShowMenu();

		if (!(cin >> choice))       // handle non-numeric input portably
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nInvalid input, please enter a number.\n";
			continue;
		}

		cout << endl;
		Reset();                    // fresh state for every run

		switch (choice)
		{
		case 1:  Task1();  break;
		case 2:  Task2();  break;
		case 3:  Task3();  break;
		case 4:  Task4();  break;
		case 5:  Task5();  break;
		case 6:  Task6();  break;
		case 7:  Task7();  break;
		case 8:  Task8();  break;
		case 9:  Task9();  break;
		case 10: Task10(); break;
		case 11: Task11(); break;
		case 0:  cout << "Exiting... Goodbye!\n"; break;
		default: cout << "Invalid choice, try again.\n"; break;
		}

		cout << endl;

	} while (choice != 0);

	return 0;
}

