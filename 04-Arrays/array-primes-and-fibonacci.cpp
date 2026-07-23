#include <iostream>
using namespace std;


//                              Functions Protypes
void PrintArray(char array[], int size);
void PrintArray(int array[], int size);
bool is_prime(int num);
bool is_fibonnaci(int, int[], int);
int Nthprime(int n);
int FindNthprime(int n);
int frequency(char array[], int size, char a);
int frequency(int array[], int size, char a);
int size_of_character_array(char[], int);
void pausw()
{
    cout << "Enter any key to continue" << endl;
    cin.ignore();
    cin.get();
}


//                              Tasks
void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();
void Task8();
void Task9();
void menu()
{

    cout << " ---------------------------------- Menu -------------------------------------" << endl;
    cout << endl;
    cout << endl;

    cout << "1. Task1 (Initialize array with a range inclusive  )" << endl;
    cout << "2. Task2 (Initialize array with a range exclusive)  " << endl;
    cout << "3. Task3 (Initialize array with N primes )" << endl;
    cout << "4. Task4 (Initialize array with random N primes)" << endl;
    cout << "5. Task5 (Frequency array )" << endl;
    cout << "6. Task6 (Frequency of char) " << endl;
    cout << "7. Task6 (Frequency of int)" << endl;
    cout << "8. Task7 (Even/Odd/Prime/fibonacci number)" << endl;
    cout << "9. Task9 (Capital Letters/Lower Letters/Vowels/Consonants)" << endl;
    cout << "10. EXIT" << endl;

    cout << " -----------------------------------------------------------------------------" << endl;


}

int main() {
    int choice = 0;

    do {

        menu();
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            Task1();
            pausw();
            break;
        case 2: 
            system("cls");
            Task1();
            pausw();
            break;
        case 3:
            system("cls");
            Task3();
            pausw();
            break;
        case 4:
            system("cls");
            Task4();
            pausw();
            break;
        case 5:
            system("cls");
            Task5();
            pausw();
            break;

        case 6:
            system("cls");
            Task6();
            pausw();
            break;
        case 7:
            system("cls");
            Task7();
            pausw();
            break;
        case 8:
            system("cls");
            Task8();
            pausw();
            break;
        case 9:
            system("cls");
            Task9();
            pausw();
            break;
        case 10:
            cout << "EXITING" << endl;
            break;
        default:
            cout << "iNVALID CHOICE" << endl;

        }






    }while(choice != 10);






    return 0;
}

void Task1() {
    char array[1000] = {};
    cout << "How many Elements you want in an Array: ";
    int size = 0;
    cin >> size;
    char start = 0;
    char end = 0;
    cout << "Enter Start: ";
    cin >> start;
    cout << "Enter End: ";
    cin >> end;

    int Range_Start = int(start) - 'a';
    int Range_End = int(end) - 'a';
    for (int i = 0; i < size; i++) {
        int num = ((rand() % (Range_End - Range_Start + 1) + Range_Start));
        char a = char(num) + 'a';
        array[i] = a;
    }

    PrintArray(array, size);
}

void Task2() {
    char array[1000] = {};
    cout << "How many Elements you want in an Array: ";
    int size = 0;
    cin >> size;
    char start = 0;
    char end = 0;
    cout << "Enter Start: ";
    cin >> start;
    cout << "Enter End: ";
    cin >> end;

    int Range_Start = int(start) - 'a';
    int Range_End = int(end) - 'a';
    for (int i = 0; i < size; i++) {
        int num = ((rand() % (Range_End - Range_Start - 1) + Range_Start + 1));
        char a = char(num) + 'a';
        array[i] = a;
    }

    PrintArray(array, size);
}

void Task3() {
    cout << (is_prime(4));
    int  array[1000] = {};
    cout << "How many Elements you want in an Array: ";
    int size = 0;
    cin >> size;
    int start = 0;
    cout << "Enter start: ";
    cin >> start;
    if (!is_prime(start)) {
        cout << "It is not a prime number" << endl;
        return;
    }
    int range = FindNthprime(start);
    for (int i = 0; i < size; i++) {
        array[i] = Nthprime(range);
        range++;
    }

    PrintArray(array, size);

}
void Task4() {

    int  array[1000] = {};
    cout << "How many Elements you want in an Array: ";
    int size = 0;
    cin >> size;


    int start = 0;
    int end = 0;
    cout << "\nEnter Start: ";
    cin >> start;
    cout << "\nEnter End: ";
    cin >> end;


    for (int i = 0; i < size; i++) {
        int num = ((rand() % (end - start + 1) + start));

        array[i] = Nthprime(num);
    }

    PrintArray(array, size);


}
void Task5() {
    char array[1000] = {};

    cout << "How many Elements you want in an Array: ";
    int size = 0;
    cin >> size;
    char start = 0;
    char end = 0;
    cout << "Enter Start: ";
    cin >> start;
    cout << "Enter End: ";
    cin >> end;

    int Range_Start = int(start) - 'a';
    int Range_End = int(end) - 'a';
    for (int i = 0; i < size; i++) {
        int num = ((rand() % (Range_End - Range_Start + 1) + Range_Start));
        char a = char(num) + 'a';
        array[i] = a;
    }


    int indexes[1000] = {};
    char temp = start;
    cout << "Randomly Generated Array: ";
    PrintArray(array, size);

    cout << "Alphabets in Range:   [";
    for (int i = Range_Start; i <= Range_End; i++) {
        cout << temp << " ";
        temp++;
    }
    cout << "]";
    cout << endl;
    temp = start;
    cout << "Alphabets Frequency: ";
    for (int i = 0; i < size; i++) {
        indexes[i] = frequency(array, size, temp);
        temp++;
    }


    PrintArray(indexes, size);
}
void Task6()
{
    int Array[1000] = {};


    int size;
    cout << "(Max 1000 and enter -1 to end) Enter enteries :   ";
    for (size = 0; size < 1000; size++)
    {
        cin >> Array[size];

        if (Array[size] == -1) break;

    }

    cout << "Enter Element you want to find frequency of: ";
    int target = 0;
    cin >> target;

    cout << "The Frequency of Target :  " << target << " is " << frequency(Array, size, target);

}
void Task7() {
    char Array[1000] = {};
    cout << "Enter Message:   ";
    cin.getline(Array, 1000);

    int size = size_of_character_array(Array, 1000);
    cout << "\nEnter Element you want to find frequency of: ";
    char target = 0;
    cin >> target;

    cout << "The Frequency of Target :  " << target << " is " << frequency(Array, size, target);


}
void Task8() {
    int Array[1000] = {};
    int even[1000] = {};
    int odd[1000] = {};
    int prime[1000] = {};
    int fibonnci[100] = {};

    int size;
    cout << "(Max 1000 and enter -1 to end) Enter enteries :   ";
    for (size = 0; size < 1000; size++)
    {
        cin >> Array[size];

        if (Array[size] == -1) break;

    }

    int Size_E = 0;
    int Size_O = 0;
    int Size_P = 0;
    int Size_F = 0;

    for (int i = 0; i < size; i++)
    {
        if (Array[i] % 2 == 0) {
            even[Size_E] = Array[i];
            Size_E++;
        }

        if (Array[i] % 2 != 0) {
            odd[Size_O] = Array[i];
            Size_O++;
        }
        if (is_prime(Array[i])) {
            prime[Size_P] = Array[i];
            Size_P++;

        }
        if (is_fibonnaci(Array[i], Array, size)) {
            fibonnci[Size_F] = Array[i];
            Size_F++;
        }

    }
    cout << endl;
    cout << "Even Found: " << Size_E;
    PrintArray(even, Size_E);
    cout << endl;

    cout << "Odd Found: " << Size_O;
    PrintArray(odd, Size_O);

    cout << endl;
    cout << "Prime Found: " << Size_P;
    PrintArray(prime, Size_P);

    cout << endl;
    cout << "Fibbonaci Found: " << Size_F;
    PrintArray(fibonnci, Size_F);
}
void Task9()
{
    char array[1000] = {};
    int size = 0;
    cout << " [Max 1000 character or end with a (.) ] Enter the Message: ";

    char input = 0;
    for (int i = 0; i < 1000; i++)
    {
        cin >> input;

        if (input == '.')break;
        array[i] = input;
        size++;

    }
    int capital = 0;
    int lower = 0;
    int vowels = 0;
    int consanants = 0;
    for (int i = 0; i < size; i++)
    {
        if (int(array[i]) >= int('A') and int(array[i]) <= int('Z'))capital++;
        if (int(array[i]) >= int('a') and int(array[i]) <= int('z'))lower++;
        if (array[i] == 'a' || array[i] == 'A' || array[i] == 'e' || array[i] == 'E' || array[i] == 'i' || array[i] == 'I' || array[i] == 'o' || array[i] == 'O' || array[i] == 'u' || array[i] == 'U')vowels++;
        else consanants++;
    }


    cout << "Capital: " << capital << endl;
    cout << "Lower: " << lower << endl;
    cout << "Vowels: " << vowels << endl;
    cout << "Consonants: " << consanants << endl;

}
void PrintArray(char array[], int size) {
    cout << " [ ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << "]";
    cout << endl;
}

void PrintArray(int array[], int size) {
    cout << " [ ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << "]";
    cout << endl;
}


int FindNthprime(int n) {
    int count = 0;
    for (int i = 2; true; i++) {
        if (is_prime(i)) {
            count++;
            if (i == n) return count;
        };
    }

}

int Nthprime(int n) {
    int count = 0;
    for (int i = 2; true; i++) {
        if (is_prime(i)) {
            count++;
            if (count == n) return i;
        };
    }

}
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int frequency(char array[], int size, char a) {
    int count = 0;
    for (int i = 0; i < size; i++)
        if (array[i] == a) count++;

    return count;
}

int frequency(int array[], int size, char a) {
    int count = 0;
    for (int i = 0; i < size; i++)
        if (array[i] == a) count++;

    return count;
}


int size_of_character_array(char array[], int limit) {
    
    int count = 0;
     
    for (int i = 0; i < limit; i++)
        if (array[i] == '\0') break; 
        else count++;

    return count;
}

bool is_fibonnaci(int target, int array[], int size) {


    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            if (array[j] + array[i] == target)return true;
    }
    return false;
}