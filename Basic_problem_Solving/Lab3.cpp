#include <cstdlib>
#include <iostream>
#include <windows.h>

using namespace std;

void pause() {
  cout << "Enter any key to continue" << endl;
  cin.ignore();
  cin.get();
}

void RockPaperScissors();
bool valid(char p);
void frequency();
void max_min();
void composite();
void prime();
bool is_prime(int num);
void nth_prime();
void prime_numbers();
void largest_prime_factor();
int _max(int a, int b, int c);
int middle(int a, int b, int c);
void middle_number();
void largest();
int _min(int a, int b, int c);
void patter_print();
void Clock();

void menu() {

  cout << "<=============================================>" << endl;
  cout << "                     Menu" << endl;
  cout << "<=============================================>" << endl;
  cout << "1. Rock Paper Pointers" << endl;
  cout << "2. Clock" << endl;
  cout << "3. Frequency " << endl;
  cout << "4. max/min" << endl;
  cout << "5. composite number" << endl;
  cout << "6. prime number" << endl;
  cout << "7. Nth Prime numeber " << endl;
  cout << "8. largest prime factor" << endl;
  cout << "9. Max  bw 3  numbers" << endl;
  cout << "10. middle bw 3 numebrs" << endl;
  cout << "11. PATTERN PRINTING" << endl;
  cout << "12. exit" << endl;
  cout << "<=============================================>" << endl;
}

int main() {

  int choice = 0;
  do {

    menu();

    cout << "Choice: ";
    cin >> choice;
    cout << endl;

    switch (choice) {

    case 1:
      system("cls");
      RockPaperScissors();
      pause();
      break;
    case 2:
      system("cls");
      clock();
      pause();
      break;
    case 3:
      system("cls");
      frequency();
      pause();
      break;
    case 4:
      system("cls");
      max_min();
      pause();
      break;
    case 5:

      system("cls");
      composite();
      pause();
      break;

    case 6:
      system("cls");
      prime();
      pause();
      break;

    case 7:

      system("cls");
      nth_prime();
      pause();
      break;
    case 8:
      system("cls");
      largest_prime_factor();
      pause();
      break;

    case 9:

      system("cls");
      largest();
      pause();
      break;
    case 10:

      system("cls");
      middle_number();
      pause();
      break;

    case 11:
      system("cls");
      patter_print();
      pause();
      break;

    case 12:
      cout << "Exiting!" << endl;
      break;
    default:
      cout << "Invalid choice" << endl;
      break;
    }

  } while (choice != 12);

  return 0;
}

void Clock() {

  int h = 0;
  int m = 0;
  int s = 57;

  for (int i = 0; true; i++) {

    system("cls");
    cout << "\r" << h << " : " << m << " : " << s;
    cout << "                                                   " << "\r" << h
         << " : " << m << " : " << s;
    cout << "\r" << h << " : " << m << " : " << s << endl;
    cout << "                                                   " << "\r" << h
         << " : " << m << " : " << s;
    cout << "                                                   " << "\r" << h
         << " : " << m << " : " << s << endl;
    cout << "\r" << h << " : " << m << " : " << s << endl;
    cout << "\r" << h << " : " << m << " : " << s << endl;
    cout << "\r" << h << " : " << m << " : " << s << endl;

    Sleep(1000);

    s++;
    if (s == 60) {
      m += 1;
      s = 0;
    }
    if (m == 60) {
      h += 1;
      m = 0;
      s = 0;
    }
    if (h == 24) {
      h = 0;
      m = 0;
      s = 0;
    }
  }
}

void patter_print() {
  cout << "Enter the height: ";
  int height = 0;
  cin >> height;
  cout << endl;

  cout << "The right angle triangle with numbers" << endl;
  for (int i = 0; i <= height; i++) {
    for (int j = 0; j < i; j++) {
      cout << j + 1 << " ";
    }
    cout << endl;
  }

  cout << endl;
  cout << endl;

  cout << "The upside down triangle with numbers " << endl;
  for (int i = 0; i <= height; i++) {
    int k = 1;
    for (int j = height; j > i; j--) {
      cout << k << " ";
      k++;
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
  cout << "Right angle triangle with Alphabets" << endl;
  char A = 'A';
  for (int i = 1; i <= height; i++) {
    for (int j = 0; j < i; j++) {
      cout << A << " ";
    }
    A++;
    cout << endl;
  }
}

void middle_number() {
  cout << "Enter three numbers: " << endl;
  int num = 0;
  int num2 = 0;
  int num3 = 0;
  cin >> num >> num2 >> num3;
  int Middle = middle(num, num2, num3);

  cout << "The middle number is: " << Middle;
}

int middle(int a, int b, int c) {
  int maximum = max(a, b, c);
  cout << maximum << endl;
  int minimum = min(a, b, c);
  cout << minimum << endl;
  int middle = 0;

  if (a != maximum && a != minimum)
    return a;
  if (b != maximum && b != minimum)
    return b;
  if (c != maximum && c != minimum)
    return c;

  return maximum;
}

int _max(int a, int b, int c) {
  int max = (a > b) ? a : b;
  max = (max > c) ? max : c;
  return max;
}

int _min(int a, int b, int c) {
  int min = (a > b) ? b : a;
  min = (min > c) ? c : min;
  return min;
}

void largest() {
  cout << "Enter three numbers: " << endl;

  int num = 0;
  int num2 = 0;
  int num3 = 0;
  cin >> num >> num2 >> num3;
  num2 = max(num, num2, num3);
  cout << "\nLargest: " << num2 << endl;
}

void largest_prime_factor() {
  int largest = 0;
  int num = 0;
  cout << "Enter the number: ";
  cin >> num;

  for (int i = 2; i <= num; i++) {
    if ((is_prime(i) && (num % i == 0))) {
      if (i > largest)
        largest = i;
    }
  }
  cout << "Largest prime factor: " << largest << endl;
}

void prime_numbers() {
  cout << "Enter the number (range 1-1000) : ";
  int num = 0;
  cin >> num;
  cout << endl;
  int count = 0;
  int answer = 0;
  for (int i = 2; i <= num; i++)
    if (is_prime(i)) {
      cout << i << " ";
    }
}

void nth_prime() {

  cout << "Enter the number (range 1-1000) : ";
  int num = 0;
  cin >> num;
  cout << endl;
  int count = 0;
  int answer = 0;
  for (int i = 2; i <= 1000; i++)
    if (is_prime(i)) {
      count++;
      if (count == num) {
        answer = i;
        break;
      }
    }

  cout << "The " << num << " th prime number is: " << answer << endl;
}

bool is_prime(int num) {

  for (int i = 2; i <= num / 2; i++)
    if (num % i == 0) {
      return 0;
    }

  return 1;
}

void prime() {
  cout << "Enter the number: ";
  int num = 0;
  cin >> num;
  cout << endl;
  bool flag = is_prime(num);

  if (flag)
    cout << "It is not a prime number " << endl;
  else
    cout << "it is  a prime number" << endl;
}

void composite() {
  cout << "Enter the number: ";
  int num = 0;
  cin >> num;
  cout << endl;
  int count = 0;

  for (int i = 1; i <= num / 2; i++)
    if (num % i == 0)
      count++;

  if (count > 1)
    cout << "It is a composite number " << endl;
  else
    cout << "it is not a composite number" << endl;
}

void max_min() {
  cout << "Enter the numbers: ";
  int min = 0;
  int max = 0;
  int num = 0;
  while (1) {
    cin >> num;
    if (num == -1)
      break;
    if (num > max)
      max = num;
    if (num < min)
      min = num;
  }
  cout << "Maximum number: " << max << endl;
  cout << "Minimum number: " << min << endl;
}

void frequency() {
  cout << "Enter the numbers: ";
  int num = 0;
  int even = 0;
  int odd = 0;
  while (1) {
    cin >> num;
    if (num == -1)
      break;
    if (num % 2 == 0) {
      even++;
    } else {
      odd++;
    }
  }
  cout << "\nEven: " << even << endl;
  cout << "\nOdd: " << odd << endl;
}

void RockPaperScissors() {

  char p1 = 0;
  char p2 = 0;
  int count1 = 0, count2 = 0;
  cout << "         -: (R)ock or (P)aper or (S)cissors :- ";

  cout << "\nEnter the number of matches :";
  int matches = 0;
  cin >> matches;
  for (int i = 0; i < matches; i++) {
    cout << "\nMatch " << i + 1 << ": ";
    while (true) {
      cout << "\nPlayer 1 choice: ";
      cin >> p1;
      if (valid(p1)) {
        break;
      };

      cout << "Invalid Choice!" << endl;
      cout << "S || R || P" << endl;
    }
    while (true) {
      cout << "\nPlayer 2 choice: ";
      cin >> p2;
      if (valid(p2)) {
        break;
      };
      cout << "Invalid Choice!" << endl;
      cout << "S || R || P" << endl;
    }

    if (p1 == p2) {
      cout << "Draw!" << endl;
    } else if ((p1 == 'R' && p2 == 'S') || (p2 == 'R' && p1 == 'P') ||
               (p2 == 'R' && p1 == 'P')) {
      cout << "match winner player 1" << endl;
      count1++;
    } else if ((p2 == 'R' && p1 == 'S') || (p1 == 'R' && p2 == 'P') ||
               (p1 == 'R' && p2 == 'P')) {
      cout << "match winner player 2" << endl;
      count2++;
    }
  }
  if (count1 > count2)
    cout << "PLayer 1 wins " << endl;
  else if (count1 == count2)
    cout << "it is draw " << endl;
  else
    cout << "player 2 wins " << endl;
}

bool valid(char p) {

  switch (p) {
  case 'R':
    return true;
  case 'P':
    return true;
  case 'S':
    return true;
  default:
    return false;
  }
}
