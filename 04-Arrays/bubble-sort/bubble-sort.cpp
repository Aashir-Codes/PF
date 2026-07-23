#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

//           GLobal

int arr[1000] = {};
int Size = 0;

//  Cross-platform screen clear
void clearScreen() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

//  Functions Prototypes
void Swap(int &a, int &b);
bool is_prime(int num);
int next_composite(int current, int end) {

  for (int i = current + 1; i < end; i++)
    if (!is_prime(i))
      return i;

  return -1;
}

int next_composite(int current[], int start, int end) {

  for (int i = start + 1; i < end; i++)
    if (!is_prime(current[i]))
      return i;

  return -1;
}

int next_prime(int current[], int start, int end) {

  for (int i = start + 1; i < end; i++)
    if (is_prime(current[i]))
      return i;

  return -1;
}

bool bubbling_Ascending_with_jump(int arr[], int start, int end, int jump = 1);
bool bubbling_Dscending_with_jump(int arr[], int start, int end, int jump = 1);
void BubbleSort_Ascending_with_jump(int arr[], int start, int end,
                                    int jump = 1);
void BubbleSort_Dscending_with_jump(int arr[], int start, int end,
                                    int jump = 1);
int next_prime(int current, int end);
void load_file();
void Print(const char msg[], int array[], int size);

// Tasks

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();

int main() {

  int choice = 0;

  do {
    clearScreen();

    cout << "==============================" << endl;
    cout << "        PFX LAB 05 MENU       " << endl;
    cout << "==============================" << endl;
    cout << "  1. Task 1" << endl;
    cout << "  2. Task 2" << endl;
    cout << "  3. Task 3" << endl;
    cout << "  4. Task 4" << endl;
    cout << "  5. Task 5" << endl;
    cout << "  0. Exit" << endl;
    cout << "==============================" << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    clearScreen();

    switch (choice) {
    case 1:
      Task1();
      break;
    case 2:
      Task2();
      break;
    case 3:
      Task3();
      break;
    case 4:
      Task4();
      break;
    case 5:
      Task5();
      break;
    case 0:
      cout << "Exiting..." << endl;
      break;
    default:
      cout << "Invalid choice! Please try again." << endl;
      break;
    }

    if (choice != 0) {
      cout << endl << "Press Enter to continue...";
      cin.ignore();
      cin.get();
    }

  } while (choice != 0);

  return 0;
}

void Task1() {

  load_file();

  BubbleSort_Ascending_with_jump(arr, 0, Size / 2);
  BubbleSort_Dscending_with_jump(arr, Size / 2, Size);
  Print("The Array : [ ", arr, Size);
}

void Task2() {

  BubbleSort_Ascending_with_jump(arr, 0, Size * 0.25);
  BubbleSort_Dscending_with_jump(arr, Size * 0.25, Size * 0.50);
  BubbleSort_Dscending_with_jump(arr, Size * 0.50, Size * 0.75);
  BubbleSort_Ascending_with_jump(arr, Size * 0.75, Size);
  Print("The Array : [ ", arr, Size);
}

void Task3() {
  load_file();

  BubbleSort_Ascending_with_jump(arr, 1, Size * 0.25, 2);
  BubbleSort_Dscending_with_jump(arr, Size * 0.25, Size * 0.50, 2);
  BubbleSort_Dscending_with_jump(arr, (Size * 0.50) + 1, Size * 0.75, 2);
  BubbleSort_Ascending_with_jump(arr, Size * 0.75, Size, 2);
  Print("The Array : [ ", arr, Size);
}

void Task4() {
  load_file();

  for (int i = 0; i < Size - 1; i++) {
    for (int k = 0; k < Size - 1; k++) {

      if (is_prime(k)) {
        int np = next_prime(k, Size);
        if (np == -1)
          continue;

        if (arr[k] < arr[np])
          Swap(arr[k], arr[np]);
      } else {
        int nc = next_composite(k, Size);
        if (nc == -1)
          continue;
        if (arr[k] > arr[nc])
          Swap(arr[k], arr[nc]);
      }
    }
  }

  Print("The Array : [ ", arr, Size);
}

void Task5() {
  load_file();

  for (int i = 0; i < Size - 1; i++) {
    for (int k = 0; k < Size; k++) {

      if (is_prime(arr[k])) {
        int np = next_prime(arr, k, Size);
        if (np == -1)
          continue;

        if (arr[k] > arr[np])
          Swap(arr[k], arr[np]);
      } else {
        int nc = next_composite(arr, k, Size);
        if (nc == -1)
          continue;
        if (arr[k] < arr[nc])
          Swap(arr[k], arr[nc]);
      }
    }
  }

  Print("The Array : [ ", arr, Size);
}
void Swap(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}
void load_file() {

  ifstream Rdr("Load.txt");

  if (!Rdr) {
    cout << "File not found" << endl;
    return;
  }

  for (int i = 0; !Rdr.eof(); i++) {
    Rdr >> arr[i];
    Size++;
  }
  Size--;
  Rdr.close();
}

void Print(const char msg[], int array[], int size) {

  cout << msg;
  for (int i = 0; i < size; i++)
    cout << array[i] << " ";

  cout << "]" << endl;
}

bool bubbling_Ascending_with_jump(int arr[], int start, int end, int jump) {
  bool BH = 0;

  for (int i = start; jump + i < end; i += jump)
    if (arr[i] > arr[i + jump]) {
      Swap(arr[i], arr[i + jump]);
      BH = 1;
    }

  return BH;
}

bool bubbling_Dscending_with_jump(int arr[], int start, int end, int jump) {
  bool BH = 0;

  for (int i = start; i + jump < end; i += jump)
    if (arr[i] < arr[i + jump]) {
      Swap(arr[i], arr[i + jump]);
      BH = 1;
    }
  return BH;
}

void BubbleSort_Ascending_with_jump(int arr[], int start, int end, int jump) {

  while (bubbling_Ascending_with_jump(arr, start, end, jump))
    ;
}

void BubbleSort_Dscending_with_jump(int arr[], int start, int end, int jump) {

  while (bubbling_Dscending_with_jump(arr, start, end, jump))
    ;
}

bool is_prime(int num) {

  if (num < 2)
    return false;

  for (int i = 2; i * i <= num; i++)

  {
    if (num % i == 0)
      return false;
  }

  return true;
}

int next_prime(int current, int end) {
  for (int k = current + 1; k < end; k++)
    if (is_prime(k))
      return k;
  return -1;
}
