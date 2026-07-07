#include <iostream>
using namespace std;


void inputArray(int arr[][10], int& rows, int& cols) {
   cout << "Enter rows and columns: ";
   cin >> rows >> cols;

   cout << "\nEnter elements:\n";
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           cin >> arr[i][j];
       }
   }
}
void displayArray(int arr[][10], int rows, int cols) {
   cout << "\nArray elements are:\n";
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           cout << arr[i][j] << " ";
       }
       cout << endl;
   }
}
int sumArray(int array[][10], int& rows, int& column) {
   cout << "Enter rows and Column" << endl;
   cin >> rows >> column;
   int ans = 0;
   int sum = 0;
   cout << "Enter the numbers " << endl;
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < column; j++) {
          
           cin >> array[i][j];
           sum += array[i][j];
       }
       
   }
   return sum;
}
void row_sum(int array[][10], int& rows, int& column, int array2[]) {
   int count = 0;
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < column; j++) {

           array2[i] += array[i][j];


       }

       count++;
   }

   cout << "<<==========================================>>" << endl;
   cout << "                    Row sum:" << endl;
   for (int i = 0; i < count; i++) {
       cout << array2[i] << " " << endl;

   }
   cout << endl;
   cout << "<<==========================================>>" << endl;
}
void column_sum(int array[][10], int& rows, int& column, int array2[]) {
   int count = 0;
   for (int i = 0; i < column; i++) {
       for (int j = 0; j < rows; j++) {

           array2[i] += array[j][i];


       }
       count++;

   }

   cout << "<<==========================================>>" << endl;
   cout << "                 The Column sum is: ";

   for (int i = 0; i < count; i++) {
       cout << array2[i] << "  ";

   }

   cout << endl;
   cout << "<<==========================================>>" << endl;
}
void diagonalArray(int arr[][10], int& rows, int& cols) {
   cout << "Enter rows and columns: ";
   cin >> rows >> cols;
   if (rows != cols) {

       diagonalArray(arr, rows, cols);
   }
   int sum1 = 0;
   int sum2 = 0;
   cout << "Enter elements:\n";
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           cin >> arr[i][j];
           if (i == j) {
               sum1 += arr[i][j];
           }
           if (i + j == cols - 1) {
               sum2 += arr[i][j];
           }
       }
   }
   cout << "Diagonal Sums: " << sum1 << " " << sum2 << endl;
}
void diagonalArray2(int arr[][10], int& rows, int& cols) {

   if (rows != cols) {
       cout << "Enter Rows and Column Equal" << endl;
       diagonalArray2(arr, rows, cols);
   }
   const int a = 10;
   int array[a] = {};
   int count = 0;
   for (int i = 0; i < rows; i++) {
       int sum1 = 0;
       int sum2 = 0;
       for (int j = 0; j < rows; j++) {

           if (i == j) {
               sum1 += arr[i][j];
           }
           if (i + j == cols - 1) {
               sum2 += arr[i][j];
           }


       }
       array[i] = sum1 + sum2;
       count++;

   }
   cout << "The diagonal matrix sum " << endl;
   for (int i = 0; i < count; i++) {
       cout << array[i] << "\t";
   }

}
void transpose_Array(int arr[][10], int& rows, int& cols) {


   cout << "<===== Transpose  =======>" << endl;
   for (int i = 0; i < cols; i++) {
       for (int j = 0; j < rows; j++) {
           cout << arr[j][i]<<" ";
       }
       cout << endl;
   }
}
int sizech(char array[], int limit) {
   int size = 0;
   for (int i = 0; i < limit; i++) {

       if (array[i] != '\0')size++;
       if (array[i] == '\0')break;


   }
   return size;

}
void movearray(char array[], int size, int index) {


   for (int i = index; i < size; i++) {

       array[i] = array[i + 1];

   }
   array[size] = '\0';


}
void removeword(char str[],char target[],int size,int size2 )
{
   int index_s = 0;
   for (int i = 0; i <= size - size2; i++) {

       bool flag = false;
       if (str[i] == target[0]) {

           for (int j = 0; j < size2; j++) {
               if (str[i + j] != target[j])break;
               if (j == size2 - 1) flag = true;


           }

       }
       if (flag == true) {
           index_s = i;
           for (int k = index_s; k <= size - size2; k++)
           {

               str[k] = str[k + size2];
           }
           size -= size2;
       }

   }
   cout << endl;
   cout << "Result: " << str;
}
void replaceword(char str[], char target[],char replace[],int size1,int size2,int size3)
{

   int index_s = 0;
   for (int i = 0; i <= size1 - size2; i++) {

       bool flag = false;
       if (str[i] == target[0]) {

           for (int j = 0; j < size2; j++) {
               if (str[i + j] != target[j])break;
               if (j == size2 - 1) flag = true;


           }

       }
       if (flag == true) {
           index_s = i;
           for (int k = index_s; k < size1 - size2; k++)
           {

               str[k] = str[k + size2];

           }
           size1 -= size2;

           int j = 0;
           for (int k = size1 - 1; k >= index_s; k--)
           {

               str[k + size3] = str[k];

           }
           size1 += size3;
           j = 0;
           for (int l = index_s; j < size3; l++) {

               str[l] = replace[j];
               j++;
           }

       }

   }
   cout << endl;
   cout << "Result: " << str;

}



int q0() {
   int rows = 0;
   int column = 0;

   int array[10][10] = {};

   inputArray(array, rows, column);
   displayArray(array, rows, column);

   return 0;
}
int q0p1() {

   int rows = 0;
   int column = 0;
   int array[10][10] = {};

   int sum = sumArray(array, rows, column);

   cout << "<<==========================================>>" << endl;
   cout << "                 The sum is: " << sum << endl;
   cout << "<<==========================================>>" << endl;
   return 0;
}
int q0p2()
{
   int rows = 0;
   int column = 0;

   int array[10][10] = {};

   inputArray(array, rows, column);
   const int a = 10;
   int r_sum[a] = {};
   int c_sum[a] = {};
   row_sum(array, rows, column, r_sum);
   column_sum(array, rows, column, c_sum);

   return 0;

}
int q0p3() {
   int rows = 0;
   int column = 0;

   int array[10][10] = {};

   diagonalArray(array, rows, column);
   cout << "<------------------- Part 2 -------------------->" << endl;

   diagonalArray2(array, rows, column);




   return 0;
}
int q0p4() {
   int array[10][10] = {};
   int rows = 0;
   int column = 0;
   inputArray(array, rows, column);
   cout << "<==== Before =====>" << endl;
   displayArray(array, rows, column);
   transpose_Array(array, rows, column);

   return 0;

}
int q2p2() {


   char str[100];
   char target = 0;
   cout << "oringinal string: ";
   cin.ignore();
   cin.getline(str, 100);
   cout << "\nYou entered: " << str << endl;
   cout << "hello enter the character you want to remove: ";
   cin >> target;
   int size = sizech(str, 100);
   while (1)
   {
       bool flag = true;
       for (int i = 0; i < size; i++) {

           if (str[i] == target) {
               movearray(str, size, i);
               flag = false;
           }

       }
       if (flag == true)break;

   }
   cout << "Result: ";
   cout << str;



   return 0;
}
int q2p1() {

   char array[] = "Hello world";
   int size = sizeof array / sizeof array[0];
   for (int i = 0; i < size; i++) {

       array[i] = array[i + 1];

   }
   array[size - 2] = '\0';



   cout << array;


   return 0;
}
int q2p3() {
   char str[1000] = {};
   char target[100] = {};
   cout << "Enter oringinal string :" << endl;
   cin.ignore();
   cin.getline(str, 1000);

   cout << "The string you entered: " << str;
   cout << "\nenter target" << endl;
   cin.getline(target, 100);
   cout << endl;
   cout << "The target: " << target;
   int index_s = 0;

   int  size = sizech(str, 1000);
   int size2 = sizech(target, 100);

   removeword(str, target, size, size2);
  

   return 0;
}
int q2p4()
{

   char str[1000] = {};
   char target[100] = {};
   char replace[100] = {};
   cout << "Enter oringinal string :" << endl;
   cin.ignore();
   cin.getline(str, 1000);
   cout << "The string you entered: " << str;
   cout << "\nenter target: ";
   cin.getline(target, 100);
   cout << endl;
   cout << "The target: " << target;
   cout << endl;
   cout << "Enter the word to replace: ";

   cin.getline(replace, 100);
   cout << endl;
   cout << "\nThe Word To Replace: " << replace<<endl;


   int index_s = 0;

   int size1 = sizech(str, 1000);
   int size2 = sizech(target, 100);
   int size3 = sizech(replace, 100);


   replaceword(str, target, replace, size1, size2, size3);

   return 0;
}















void menu() {
   cout << "Enter your choice: \n";
   cout << "1 - Question 0 \n";
   cout << "2 - Question 0 part 1 \n";
   cout << "3 - Question 0 Part 2 \n";
   cout << "4 - Question 0 Part 3 \n";
   cout << "5 - Question 0 Part 4 \n";
   cout << "6 - Question 2 part 1 \n";
   cout << "7 - Question 2 Part 2 \n";
   cout << "8 - Question 2 Part 3 \n";
   cout << "9 - Question 2 Part 4 \n";
   cout << "10 - Exit \n";
}

int main() {
   int choice;

   do {
       cout << "\n----------------------------------------\n";
       menu();
       cout << "Choice: "; cin >> choice;

       system("cls");

       switch (choice) {
       case 1:q0(); break;
       case 2:q0p1(); break;
       case 3:q0p2(); break;
       case 4:q0p3(); break;
       case 5:q0p4(); break;
       case 7:q2p2(); break;
       case 6:q2p1(); break;
       case 8:q2p3(); break;
       case 9:q2p4(); break;
       case 10: cout << "Exiting program...\n"; break;
       default: cout << "Invalid choice. Try again.\n"; break;
       }
   } while (choice != 10);











   return 0;
}

