#include <fstream>
#include <iostream>

using namespace std;

int *Load() {
  int count = 0, var;
  ifstream rdr("file.txt");
  while (rdr >> var)
    count++;
  rdr.close();

  int *arr = new int[count + 1];
  arr[0] = count;

  ifstream rdr2("file.txt");
  for (int i = 1; i <= count; i++)
    rdr2 >> arr[i];
  rdr2.close();

  return arr;
}

int binary_count(int num) {
  if (num == 0)
    return 1;
  int count = 0;
  while (num > 0) {
    count++;
    num /= 2;
  }
  return count;
}

int **arrmap(int *a) {
  int **arr = new int *[a[0]];

  for (int i = 0; i < a[0]; i++) {
    int bits = binary_count(a[i + 1]);

    arr[i] = new int[bits + 1];
    arr[i][0] = bits;

    int temp = a[i + 1];

    for (int j = bits; j >= 1; j--) {
      arr[i][j] = temp % 2;
      temp /= 2;
    }
  }

  return arr;
}

void display(int **arr, int *a) {
  cout << "Number\tBitmap" << endl;
  cout << "------\t------" << endl;
  for (int i = 0; i < a[0]; i++) {
    cout << a[i + 1] << "\t";
    for (int j = 1; j <= arr[i][0]; j++)
      cout << arr[i][j];
    cout << endl;
  }
}

void freeMap(int **arr, int count) {
  for (int i = 0; i < count; i++)
    delete[] arr[i];
  delete[] arr;
}

int main() {
  int *a = Load();

  if (a[0] == 0) {
    cout << "No data found in file.txt" << endl;
    delete[] a;
    return 1;
  }

  cout << "Numbers loaded: " << a[0] << endl;

  int **bitmap = arrmap(a);
  display(bitmap, a);

  freeMap(bitmap, a[0]);
  delete[] a;

  return 0;
}
