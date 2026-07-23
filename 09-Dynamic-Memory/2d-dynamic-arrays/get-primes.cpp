#include <fstream>
#include <iostream>
using namespace std;

int _r, _c;
int **load() {
  ifstream Rdr("input.txt");

  int c, r;

  Rdr >> r;
  Rdr >> c;

  _r = r;
  _c = c;

  int **arr = new int *[r]{};

  for (int i = 0; i < r; i++) {
    arr[i] = new int[c]{};
    for (int j = 0; j < c; j++)
      Rdr >> arr[i][j];
  }
  Rdr.close();
  return arr;
}

bool isprime(int num) {
  if (num < 2)
    return false;

  for (int i = 2; i <= num / 2; i++) {
    if (num % i == 0)
      return false;
  }

  return true;
}

int main() {
  int **original = load();
  cout << "Orignal Array: " << endl;

  for (int i = 0; i < _r; i++) {
    for (int j = 0; j < _c; j++)
      cout << original[i][j] << " ";
    cout << endl;
  }

  int ***primes = new int **[_r] {};

  for (int i = 0; i < _r; i++) {
    int count = 0;
    for (int j = 0; j < _c; j++) {
      if (isprime(original[i][j])) {
        count++;
      }
    }

    primes[i] = new int *[count + 1]{new int(count)};
  }

  for (int i = 0; i < _r; i++) {
    int k = 1;
    for (int j = 0; j < _c; j++) {
      if (isprime(original[i][j])) {
        primes[i][k++] = &original[i][j];
      }
    }
  }

  cout << "The Number Of Prime number in the 2-D ARRAY: " << endl;

  for (int i = 0; i < _r; i++) {

    for (int j = 1; j <= *primes[i][0]; j++)
      cout << *primes[i][j] << " ";

    cout << endl;
  }

  return 0;
}
