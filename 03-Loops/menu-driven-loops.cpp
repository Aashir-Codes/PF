#include <iostream>
#include <unistd.h>


// Author: Aashir
// Topic: Loops in C++
// Description: Menu-driven program demonstrating all loop types
//system("clear")    clears the terminal


using namespace std;

void print_numbers();
void SumofN();
void Factorial();
void Table();
void Even();
void Powercal();
void reverse();
void count();
void SumofDigit();
void palindrome();
void highest();
void ReduceToZero();
void guess();
void square();
void right_triangle();
void num_right_triangle();
void inverted_right_triangle();
void Triangle();
void chessboard();
void primenumber();


void menu() {

    cout<<"<==========================================>"<<endl;
    cout<<"                Menu "<<endl;
    cout<<"<==========================================>"<<endl;
    cout<<"1. Print Numbers"<<endl;
    cout<<"2. Factorial"<<endl;
    cout<<"3. Table"<<endl;
    cout<<"4. Even Numbers"<<endl;
    cout<<"5. Palindrome"<<endl;
    cout<<"6. Highest Digit"<<endl;
    cout<<"7. Reduce To Zero"<<endl;
    cout<<"8. Power (x^y)"<<endl;
    cout<<"9. Reverse Number"<<endl;
    cout<<"10. Count Digits"<<endl;
    cout<<"11. SumofDigit of Digits"<<endl;
    cout<<"12. SumofDigit of N Numbers"<<endl;
    cout<<"14. Triangle "<<endl;
    cout<<"15. Inverted Right Triangle "<<endl;
    cout<<"16. Chessboard "<<endl;
    cout<<"17. Number's  Triangle"<<endl;
    cout<<"18. Right Triangle "<<endl;
    cout<<"19. Square "<<endl;
    cout<<"20. Guess"<<endl;
    cout<<"21. Prime number"<<endl;
    cout<<"13. Exit"<<endl;
    cout<<"<==========================================>"<<endl;
}

int main() {



    int choice = 0;
    do {
        menu();
        cout<<"Choice: ";
        cin>>choice;
        cout<<endl;

        switch (choice) {
            case 1:
                system("clear");  
                print_numbers();
                sleep(2);
                break;
            case 2:
                system("clear");
                Factorial();
                sleep(2);
                break;
            case 3:
                system("clear");
                Table();
                sleep(2);
                break;
            case 4:
                system("clear");
                Even();
                sleep(2);
                break;
            case 5:
                system("clear");
                palindrome();
                sleep(2);
                break;
            case 6:
                system("clear");
                highest();
                sleep(2);
                break;
            case 7:
                system("clear");
                ReduceToZero();
                sleep(2);
                break;
            case 8:
                system("clear");
                Powercal();
                sleep(2);
                break;
            case 9:
                system("clear");
                reverse();
                sleep(2);
                break;
            case 10:
                system("clear");
                count();
                sleep(2);
                break;
            case 11:
                system("clear");
                SumofDigit();
                sleep(2);
                break;
            case 12:
                system("clear");
                SumofN();
                sleep(2);
                break;
            case 13:
                cout<<"Exiting... Goodbye!"<<endl;
                sleep(2);
                break;
            case 14:
                system("clear");
                Triangle();
                sleep(2);
                break;
            case 15:
                system("clear");
                inverted_right_triangle() ;
                sleep(2);
                break;
            case 16:
                system("clear");
                chessboard();
                sleep(2);
                break;
            case 17:
                system("clear");
                num_right_triangle();
                sleep(2);
                break;
            case 18:
                system("clear");
                right_triangle();
                sleep(2);
                break;
            case 19:
                system("clear");
                square();
                sleep(2);
                break;
            case 20:
                system("clear");
                guess();
                sleep(2);
                break;
            case 21:
                system("clear");
                primenumber();
                sleep(2);
                break;

            default:
                cout<<"Invalid Choice! Please try again."<<endl;
                sleep(2);
                break;

        }
    } while(choice != 13); 
    return 0;
}


void chessboard() {
    int n=0;
    cout<<"The height of monument: ";
    cin>>n;

    for (int i=0;i<n;i++)
    {
    if (i%2==0)cout<<"*#*#";
    else cout<<"#*#*";
        cout<<endl;
    }
}

void Triangle() {
    cout<<"Enter the height: ";
    int n=0;
    cin>>n;

    for (int i=0;i< n;i++)
    {
        for (int j=n;j>i;j--)
            cout<<"   ";
        for (int j=0;j<=i;j++)
            cout<<" * ";
        for (int j=0;j<i;j++)
            cout<<" * ";
cout<<endl;
    }

}

void inverted_right_triangle() {
    cout<<"Enter the height of triangle: "<<endl;
    int n=0;
    cin>>n;

    for (int i=0;i< n;i++) {
        for (int j=n;j>i;j--)
            cout<<" *";
        cout<<endl;

    }
}

void right_triangle() {
    cout<<"Enter the height of triangle: "<<endl;
    int n=0;
    cin>>n;

    for (int i=0;i<=n;i++) {
        for (int j=0;j<i;j++)
            cout<<" *";
        cout<<endl;

    }
}

void num_right_triangle() {
    cout<<"Enter the height of triangle: "<<endl;
    int n=0;
    cin>>n;

    for (int i=0;i<=n;i++) {
        for (int j=0;j<i;j++)
            cout<<j+1<<" ";
        cout<<endl;

    }
}

void square() {
    cout<<"Enter the height: ";
    int n=0;
    cin>>n;
    cout<<endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            cout<<" * ";
        cout<<endl;
    }
}

void guess() {

    int n=0;

    while (n!=27) {
        cout<<"Enter the Magic number: "<<endl;
        cin>>n;
        if (n==27)break;
        cout<<"OOPS! wrong number"<<endl;
    }
    cout<<"BIngo!"<<endl;
}

void print_numbers() {
    cout<<"Enter the number you want to print till: ";
    int n = 0;
    cin>>n;
    cout<<endl;

    for (int i = 1; i <= n; i++) {
        cout<<i<<"  ";
    }
    cout<<endl;
}

void SumofN() {
    cout<<"Enter the number you want SumofN till: ";
    int n = 0;
    cin>>n;
    cout<<endl;
    int SumofN = 0;

    for (int i = 1; i <= n; i++) {
        SumofN += i;
    }
    cout<<"SumofDigit: "<<SumofN<<endl;
}

void Factorial() {
    cout<<"Enter the number you want Factorial of: ";
    int n = 0;
    cin>>n;
    cout<<endl;

    if (n < 0) {
        cout<<"Factorial of "<<n<<" is invalid"<<endl;
        return;
    }

    int factorial = 1;
    while (n > 0) {
        factorial *= n;
        n--;
    }
    cout<<"Factorial: "<<factorial<<endl;
}

void Table() {
    cout<<"Enter the number you want table of: ";
    int n = 0;
    cin>>n;

    cout<<"<================= Table OF "<<n<<" ================>"<<endl;
    for (int i = 1; i <= 10; i++) {
        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
    }
}

void Even() {
    cout<<"Enter the number: ";
    int n = 0;
    cin>>n;

    cout<<"Even numbers: "<<endl;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            cout<<i<<" ";
        }
    }
    cout<<endl;
}

void Powercal() {
    cout<<"Enter the base: ";
    int base = 0;
    cin>>base;
    cout<<"Enter the power: ";
    int power = 0;
    cin>>power;

    int ans = 1;
    for (int i = 1; i <= power; i++) {
        ans *= base;
    }
    cout<<"The Answer is: "<<ans<<endl;
}

void reverse() {
    int num = 0;
    cout<<"Enter the number you want to reverse: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    num = 0;
    while(temp != 0) {
        int base = temp % 10;
        temp /= 10;
        num = num * 10 + base;
    }
    cout<<"The reversed number is: "<<num<<endl;
}

void count() {
    int num = 0;
    cout<<"Enter the number: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    num = 0;
    while(temp != 0) {
        temp /= 10;
        num++;
    }
    cout<<"The digit count is: "<<num<<endl;
}

void SumofDigit() {
    int num = 0;
    cout<<"Enter the number you want to break and have SumofN: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    num = 0;
    while(temp != 0) {
        int base = temp % 10;
        temp /= 10;
        num += base;
    }
    cout<<"The SumofN of digits is: "<<num<<endl;
}

void palindrome() {
    int num = 0;
    cout<<"Enter the number you want to check: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    int temp2 = 0;
    while(temp != 0) {
        int base = temp % 10;
        temp /= 10;
        temp2 = temp2 * 10 + base;
    }

    if (num == temp2) {
        cout<<"The number "<<num<<" is a Palindrome!"<<endl;
    } else {
        cout<<"The number "<<num<<" is NOT a palindrome."<<endl;
    }
}

void highest() {
    int num = 0;
    cout<<"Enter the number to find its largest digit: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    num = 0;

    while(temp != 0) {
        int base = temp % 10;
        temp /= 10;
        if (base > num) {
            num = base;
        }
    }
    cout<<"The highest digit is: "<<num<<endl;
}

void ReduceToZero() {
    int num = 0;
    cout<<"Enter the number you want to reduce to zero: ";
    cin>>num;
    cout<<endl;

    int temp = num;
    num = 0;
    if (temp>=0)
    {
        while(temp != 0) {
            temp--;
            num++;
        }
    }
    else {
        while(temp != 0) {
            temp++;
            num++;
        }
    }
    cout<<"The number will be zeroed in: "<<num<<" steps"<<endl;
}
void primenumber() {
    int array[500]={};

    int size=0;
    cout<<"Enter the range till that prime number will be shown: ";
    cin>>size;
    cout<<endl;
    int pointer =0;

    for (int i = 2; i <= size; i++) {
        bool flag=1;
        for (int j = 2; j <= i/2; j++)
        {

            if (i % j == 0) {
                flag=0;
                break;
            }


        }
    if (flag==1)
    {
    array[pointer]=i;
     pointer++;
    }


    }
    cout<<"The prime numbers are: "<<endl;
for (int i=0;i<pointer;i++)
    cout<<array[i]<<" ";
cout<<endl;
}