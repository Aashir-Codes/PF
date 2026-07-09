#include <iostream>
using namespace std;

// ═══════════════════════════════════════════════════════════════════
//  Part A : Pointer Basics
// ═══════════════════════════════════════════════════════════════════

void A1()
{
	int x = 42;
	int* p = &x;
	cout << "Variable value: " << x << endl;
	cout << "Variable address: " << &x << endl;
	cout << "Pointer value (stores address): " << p << endl;
	cout << "Pointer's own address: " << &p << endl;
}

void A2()
{
	int x, add;
	cout << "Initial value: "; cin >> x;
	cout << "Add to value: ";  cin >> add;

	int* ptr = &x;
	cout << "Before modification:" << endl;
	cout << "x = " << x << ", *ptr = " << *ptr << endl;
	*ptr = *ptr + add;
	cout << "After (*ptr = *ptr + " << add << "):" << endl;
	cout << "x = " << x << ", *ptr = " << *ptr << endl;
}

void A3()
{
	int    a; char b; double c;
	int*   pi = &a;
	char*  pc = &b;
	double* pd = &c;
	cout << "int pointer: "    << sizeof(pi) << " bytes" << endl;
	cout << "char pointer: "   << sizeof(pc) << " bytes" << endl;
	cout << "double pointer: " << sizeof(pd) << " bytes" << endl;
}

void A4()
{
	int* ptr = nullptr;
	cout << "NULL pointer: " << ptr << endl;
	if (!ptr)
		cout << "Cannot dereference NULL pointer!" << endl;

	int x = 42;
	ptr = &x;
	cout << "After initialization: " << ptr << endl;
	cout << "Safe to use: *ptr = " << *ptr << endl;
}

// ═══════════════════════════════════════════════════════════════════
//  Part B : Pointers with Functions
// ═══════════════════════════════════════════════════════════════════

void swapUsingPointers(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void B1()
{
	int a, b;
	cout << "A = "; cin >> a;
	cout << "B = "; cin >> b;
	cout << "Before: A = " << a << ", B = " << b << endl;
	swapUsingPointers(&a, &b);
	cout << "After:  A = " << a << ", B = " << b << endl;
}

void findMax(int* a, int* b, int* mx)
{
	*mx = (*a > *b) ? *a : *b;
}

void B2()
{
	int a, b, mx;
	cout << "&A = "; cin >> a;
	cout << "&B = "; cin >> b;
	findMax(&a, &b, &mx);
	cout << "C have: " << mx << endl;
}

void divideNumbers(int dividend, int divisor, int* quotient, int* remainder)
{
	*quotient  = dividend / divisor;
	*remainder = dividend % divisor;
}

void B3()
{
	int dvd, dvs, q, r;
	cout << "Dividend: ";  cin >> dvd;
	cout << "Divisor: ";   cin >> dvs;
	divideNumbers(dvd, dvs, &q, &r);
	cout << dvd << " / " << dvs << " = " << q << " remainder " << r << endl;
}

// ═══════════════════════════════════════════════════════════════════
//  Part C : Pointers and Arrays
// ═══════════════════════════════════════════════════════════════════

void inputArrayPointer(int* arr, int* size)
{
	cout << "Size: ";     cin >> *size;
	cout << "Elements: ";
	for (int i = 0; i < *size; i++)
		cin >> *(arr + i);
	cout << "Array stored using *(arr+i)" << endl;
	cout << "Array: ";
	for (int i = 0; i < *size; i++)
		cout << *(arr + i) << " ";
	cout << endl;
}

void C1()
{
	int arr[100], size;
	inputArrayPointer(arr, &size);
}

void printArrayPointer(int* arr, int size)
{
	cout << "Using pointer notation:" << endl;
	for (int i = 0; i < size; i++)
		cout << "*(arr+" << i << ")=" << *(arr + i) << " ";
	cout << endl;
}

void C2()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	printArrayPointer(arr, 5);
}

int sumArrayPointer(int* arr, int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += *(arr + i);
	return sum;
}

void C3()
{
	int arr[] = { 5, 10, 15, 20, 25 };
	cout << "Sum: " << sumArrayPointer(arr, 5) << endl;
}

// ═══════════════════════════════════════════════════════════════════
//  Part D : Advanced Pointer Operations  (no [] , no swap functions)
// ═══════════════════════════════════════════════════════════════════

void reverseArray(int* arr, int size)
{
	int* lo = arr;
	int* hi = arr + size - 1;
	while (lo < hi)
	{
		int tmp = *lo;
		*lo = *hi;
		*hi = tmp;
		lo++; hi--;
	}
}

void D1()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	int size = 5;
	cout << "Original: ";
	for (int i = 0; i < size; i++) cout << *(arr + i) << " ";
	cout << endl;
	reverseArray(arr, size);
	cout << "Reversed: ";
	for (int i = 0; i < size; i++) cout << *(arr + i) << " ";
	cout << endl;
}

int findMaxPointer(int* arr, int size)
{
	int mx = *arr;
	for (int i = 1; i < size; i++)
		if (*(arr + i) > mx) mx = *(arr + i);
	return mx;
}

void D2()
{
	int arr[] = { 45, 12, 78, 23, 90 };
	cout << "Maximum: " << findMaxPointer(arr, 5) << endl;
}

int countOccurrencesPointer(int* arr, int size, int target)
{
	int count = 0;
	for (int i = 0; i < size; i++)
		if (*(arr + i) == target) count++;
	return count;
}

void D3()
{
	int arr[] = { 5, 2, 5, 3, 5, 7, 5 };
	int target = 5;
	cout << "Element " << target << " occurs "
		 << countOccurrencesPointer(arr, 7, target) << " times" << endl;
}

void copyArrayPointer(int* src, int* dst, int size)
{
	for (int i = 0; i < size; i++)
		*(dst + i) = *(src + i);
}

void D4()
{
	int src[] = { 10, 20, 30, 40, 50 };
	int dst[5];
	copyArrayPointer(src, dst, 5);
	cout << "Destination: {";
	for (int i = 0; i < 5; i++)
	{
		cout << *(dst + i);
		if (i < 4) cout << ", ";
	}
	cout << "}" << endl;
}

void D5()
{
	int arr[] = { 100, 200, 300, 400 };
	int size = 4;
	for (int i = 0; i < size; i++)
		cout << "[" << i << "] " << (void*)(arr + i) << ": " << *(arr + i) << endl;
	cout << "Addresses differ by " << sizeof(int) << " bytes" << endl;
}

// ═══════════════════════════════════════════════════════════════════
//  Main Menu
// ═══════════════════════════════════════════════════════════════════

int main()
{
	int choice;
	do
	{
		cout << "\n--- Pointers Lab Menu ---" << endl;
		cout << "Part A : Pointer Basics" << endl;
		cout << "  1. Declare and Initialize Pointers" << endl;
		cout << "  2. Dereferencing Pointers" << endl;
		cout << "  3. Pointer to Different Data Types" << endl;
		cout << "  4. NULL Pointers" << endl;
		cout << "Part B : Pointers with Functions" << endl;
		cout << "  5. Swap Using Pointers" << endl;
		cout << "  6. Find Maximum Using Pointers" << endl;
		cout << "  7. Divide with Quotient and Remainder" << endl;
		cout << "Part C : Pointers and Arrays" << endl;
		cout << "  8. Input Array Using Pointer" << endl;
		cout << "  9. Print Array Using Pointer" << endl;
		cout << " 10. Sum Array Using Pointer" << endl;
		cout << "Part D : Advanced Pointer Operations" << endl;
		cout << " 11. Reverse Array" << endl;
		cout << " 12. Find Maximum" << endl;
		cout << " 13. Count Occurrences" << endl;
		cout << " 14. Copy Array" << endl;
		cout << " 15. Print Array Addresses" << endl;
		cout << "  0. Exit" << endl;
		cout << "Choice: ";
		cin >> choice;

		switch (choice)
		{
		case  1: A1(); break;
		case  2: A2(); break;
		case  3: A3(); break;
		case  4: A4(); break;
		case  5: B1(); break;
		case  6: B2(); break;
		case  7: B3(); break;
		case  8: C1(); break;
		case  9: C2(); break;
		case 10: C3(); break;
		case 11: D1(); break;
		case 12: D2(); break;
		case 13: D3(); break;
		case 14: D4(); break;
		case 15: D5(); break;
		case  0: break;
		default: cout << "Invalid choice." << endl;
		}
	} while (choice != 0);

	return 0;
}
