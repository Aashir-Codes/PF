#include <fstream>
#include <iostream>

using namespace std;

const int ROWS = 10;
const int COLS = 20;

char words[ROWS][COLS];
int i = 0;

void FiletoArray() {
  int rowCount = 0;
  ifstream Rdr("file.txt");
  Rdr >> i;
  while (Rdr >> words[rowCount]) {
    rowCount++;
    if (rowCount >= ROWS)
      break;
  }
  Rdr.close();
}

int Size(char array[], int limiter);
bool CharGreater(char array1[], char array2[], int &size1, int &size2);
void _swap(char array[], char array1[], int &size, int &size1);
void sort();
void word();
void Equal();
void Swap(char &a, char &b);
bool CharSmaller(char array1[], char array2[], int &size1, int &size2);

int main() {
  FiletoArray();

  char choice = 0;
  do {
    cout << "                           Menu:\n";
    cout << "              1- Swap two character arrays\n";
    cout << "              2- Check if two character arrays are equal\n";
    cout << "              3- Sort character arrays from file\n";
    cout << "              4- Count occurrences of a word in a string\n";
    cout << "              5- Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case '1': {
      char array1[100] = {};
      char array2[100] = {};
      cout << "Enter First Name: ";
      cin.ignore();
      cin.getline(array1, 100);
      cout << "Enter Second Name: ";
      cin.getline(array2, 100);
      int size1 = Size(array1, 100);
      int size2 = Size(array2, 100);
      _swap(array1, array2, size1, size2);
      cout << "After Swapping: \n";
      cout << "First Name: " << array1 << "\n";
      cout << "Second Name: " << array2 << "\n";
      break;
    }
    case '2':
      cin.ignore();
      Equal();
      break;
    case '3':
      sort();
      cout << "Sorted character arrays from file: \n";
      for (int k = 0; k < i; k++) {
        cout << words[k] << "\n";
      }
      break;
    case '4':
      word();
      break;
    case '5':
      cout << "Exiting the program.\n";
      break;
    default:
      cout << "Invalid choice. Please try again.\n";
      break;
    }
  } while (choice != '5');

  return 0;
}

void Swap(char &a, char &b) {
  char temp = a;
  a = b;
  b = temp;
}

void _swap(char array[], char array1[], int &size, int &size1) {
  int max = (size < size1) ? size1 : size;
  for (int i = 0; i < max; i++) {
    Swap(array[i], array1[i]);
  }
  int temp = size;
  size = size1;
  size1 = temp;
}

void Equal() {
  char array1[100] = {};
  char array2[100] = {};

  cout << "Enter First Name: ";
  cin.getline(array1, 100);
  cout << "Enter Second Name: ";
  cin.getline(array2, 100);

  int size1 = Size(array1, 100);
  int size2 = Size(array2, 100);
  bool flag = false;

  if (size1 != size2) {
    flag = true;
  } else {
    for (int i = 0; i < size1; i++) {
      if (array1[i] != array2[i]) {
        flag = true;
        break;
      }
    }
  }

  if (flag) {
    cout << "The character arrays are not equal\n";
  } else {
    cout << "The character arrays are equal\n";
  }
}

bool CharSmaller(char array1[], char array2[], int &size1, int &size2) {
  int minSize = (size1 < size2) ? size1 : size2;
  for (int i = 0; i < minSize; i++) {
    if (array1[i] < array2[i]) {
      return true;
    } else if (array1[i] > array2[i]) {
      return false;
    }
  }
  return size1 < size2;
}

bool CharGreater(char array1[], char array2[], int &size1, int &size2) {
  int minSize = (size1 < size2) ? size1 : size2;
  for (int i = 0; i < minSize; i++) {
    if (array1[i] > array2[i]) {
      return true;
    } else if (array1[i] < array2[i]) {
      return false;
    }
  }
  return size1 > size2;
}

int Size(char array[], int limiter) {
  int i = 0;
  while (array[i] != '\0') {
    i++;
  }
  return i;
}

void sort() {
  for (int i = 0; i < ROWS - 1; i++) {
    for (int j = i + 1; j < ROWS; j++) {
      int size1 = Size(words[i], COLS);
      int size2 = Size(words[j], COLS);
      if (CharGreater(words[i], words[j], size1, size2)) {
        _swap(words[i], words[j], size1, size2);
      }
    }
  }
}

void word() {
  char target[100] = {};
  char str[1000] = {};

  cout << "The string: ";
  cin.ignore();
  cin.getline(str, 1000);
  cout << "Enter target: ";
  cin.getline(target, 100);

  int size1 = Size(str, 1000);
  int size2 = Size(target, 100);
  int counter = 0;

  for (int i = 0; i <= size1 - size2; i++) {
    bool flag = true;
    for (int j = 0; j < size2; j++) {
      if (str[i + j] != target[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      counter++;
    }
  }
  cout << "Result: " << counter << "\n";
}
