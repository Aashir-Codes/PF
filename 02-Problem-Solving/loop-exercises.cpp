#include <iostream>
#include <cstdlib>
using namespace std;

void pause() {
    cout<<"Enter any key to continue!"<<endl;
    cin.ignore();
    cin.get();
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();
void Task6();
void Task7();
void Task8();
void Task9();
void Task10();
void Task11();
void Task12();
void Task13();
void Task14();

void menu() {
    cout << "<========================================================>" << endl;
    cout << "                       Menu" << endl;
    cout << "<========================================================>" << endl;
    cout << "1. Table with while loop and for loop" << endl;
    cout << "2. Reverse table with while loop and for loop" << endl;
    cout << "3.  Table with jump" << endl;
    cout << "4. Reverse Table with jump" << endl;
    cout << "5. cube of a number" << endl;
    cout << "6. cube of numbers in the range " << endl;
    cout << "7. Pattern Printing" << endl;
    cout << "8. Sequence Printing" << endl;
    cout << "9. Celsius /Kelvin / Fahrenheit" << endl;
    cout << "10. Swap numbers" << endl;
    cout << "11. Average of K numbers" << endl;
    cout << "12. Sum of K numbers" << endl;
    cout << "13. Sum of multiples of 3 / 5 in range " << endl;
    cout << "14. Printing sum of multiples under 100 " << endl;
    cout << "15. Exit" << endl;
    cout << "<========================================================>" << endl;
}


int main() {

    int choice=0;

    do {
        menu();
        cout<<"Choice: ";
        cin>>choice;

        switch (choice) {

            case 1:
                clearScreen();
                Task1();
                pause();
                break;
            case 2:
                clearScreen();
                Task2();
                pause();
                break;
            case 3:
                clearScreen();
                Task3();
                pause();
                break;
            case 4:
                clearScreen();
                Task4();
                pause();
                break;
            case 5:
                clearScreen();
                Task5();
                pause();
                break;
            case 6:
                clearScreen();
                Task6();
                pause();
                break;
            case 7:
                clearScreen();
                Task7();
                pause();
                break;
            case 8:
                clearScreen();
                Task8();
                pause();
                break;
            case 9:
                clearScreen();
                Task9();
                pause();
                break;
            case 10:
                clearScreen();
                Task10();
                pause();
                break;
            case 11:
                clearScreen();
                Task11();
                pause();
                break;
            case 12:
                clearScreen();
                Task12();
                pause();
                break;
            case 13:
                clearScreen();
                Task13();
                pause();
                break;
            case 14:
                clearScreen();
                Task14();
                pause();
                break;
            case 15:
                cout<<"exiting! "<<endl;
                break;

            default:
                cout<<"invalide choice!"<<endl;











        }



    }while (choice != 15);


    return 0;
}

void Task1() {

    int start,end, table;

    cout<<"Enter the number you want  table of : ";
    cin>>table;

    cout<<"\nEnter the start: ";
    cin>>start;
    cout<<"\nEnter the end: ";
    cin>>end;

    cout<<"\n          Table oF (using for loop) "<<table<<endl;
    for (int i = start; i <= end; i++) {
        cout<<table<<" * "<<i<<"  = "<<table*i<<endl;

    }
    cout<<endl;


    cout<<"\n          Table oF   (using while loop) "<<table<<endl;

    while (start<=end) {

        cout<<table<<" * "<<start<<" "<<" ="<<table*start<<endl;
start++;
    }



}

void Task2() {

    int start,end, table;

    cout<<"Enter the number you want  table of : ";
    cin>>table;

    cout<<"\nEnter the start: ";
    cin>>start;
    cout<<"\nEnter the end: ";
    cin>>end;

    cout<<"\n          Table oF (using for loop) "<<table<<endl;
    for (int i = end; i >= start; i--) {
        cout<<table<<" * "<<i<<"  = "<<table*i<<endl;

    }
    cout<<endl;


    cout<<"\n          Table oF   (using while loop) "<<table<<endl;

    while (end>=start) {

        cout<<table<<" * "<<end<<" "<<" ="<<table*end<<endl;
        end--;
    }



}

void Task3() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;

    cout<<"Enter the jump: ";
    int jump=0;
    cin>>jump;

    cout<<"\n          Table of "<<n<<endl;
    while (i<=j) {

        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
        i +=jump;
    }
}

void Task4() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;

    cout<<"Enter the jump: ";
    int jump=0;
    cin>>jump;

    cout<<"\n          Table of "<<n<<endl;
    while (i<=j) {

        cout<<n<<" * "<<j<<" = "<<n*j<<endl;
        j -=jump;
    }
}

void Task5() {

    cout<<"Enter the number you want cube of: ";
    int num=0;
    cin>>num;

    num =num*num*num;
    cout<<"The cube of entered number is : "<<num<<endl;

}

void Task6() {

    cout<<"Enter the  range (start/end) : ";
    int start=0,end=0;
    cin>>start>>end;
    cout<<endl;
    int num=0;


   for (int i = start; i <= end; i++) {
       num=i;
       num =num*num*num;
       cout<<"\nThe cube of number: "<<i<<" is : "<<num<<endl;

   }
}

void Task7()
{
    cout<<"Enter  the height: "<<endl;
    int height=0;
    cin>>height;


cout<<"The Square:-  "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=0; j<height; j++) {
            cout<<"* ";
        }
        cout<<endl;
    }

    cout<<"Half triangle left: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=0; j<i+1; j++) {
            cout<<"* ";
        }
        cout<<endl;
    }

    cout<<"half triangle right: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=height; j>i; j--) {
            cout<<"  ";
        }
        for (int j=0; j<i+1; j++) {
            cout<<"* ";
        }

        cout<<endl;
    }

    cout<<"Half triangle left top: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=height; j>i; j--) {
            cout<<" *";
        }

        cout<<endl;
    }


    cout<<"Half triangle right: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=1; j<i+1; j++) {
            cout<<"  ";
        }
        for (int j=height; j>i; j--) {
            cout<<"* ";
        }
        cout<<endl;
    }

    cout<<"Full triangle right: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=height; j>i; j--) {
            cout<<" ";
        }
        for (int j=0; j<i+1; j++) {
            cout<<"* ";
        }

        cout<<endl;
    }

    cout<<"Full triangle right downward: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=1; j<=i; j++) {
            cout<<" ";
        }
        for (int j=height; j>i; j--) {
            cout<<"* ";
        }

        cout<<endl;
    }

    cout<<"Full triangle right: "<<endl;
    for (int i=0; i<height; i++) {
        for (int j=height; j>i; j--) {
            cout<<"*";
        }
        for (int j=0; j<i; j++) {
            cout<<" ";
        }
        for (int j=0; j<i; j++) {
            cout<<" ";
        }
        for (int j=height; j>i; j--) {
            cout<<"*";
        }


        cout<<endl;
    }

    cout<<"The crown:-  "<<endl;

    for (int i=1;i<=height*4+1;i++) {
        if (i==1  || i==(height*2)+1  || i== (height*4)+1){
            cout<<"*";
        }
        else {
            cout<<" ";
        }
    }
    cout<<endl;

    for (int i=0;i<height;i++ ) {
        for (int j=0;j<=i;j++) {
            cout<<"*";
        }
        for (int j=height;j>i;j--) {
            cout<<" ";
        }
        for (int j=height-1;j>i;j--) {
            cout<<" ";
        }
        for (int j=0;j<=i;j++) {
            cout<<"*";
        }
        for (int j=0;j<i;j++) {
            cout<<"*";
        }
        for (int j=height;j>i;j--) {
            cout<<" ";
        }
        for (int j=height-1;j>i;j--) {
            cout<<" ";
        }
        for (int j=0;j<=i;j++) {
            cout<<"*";
        }
        cout<<endl;
    }

    for (int i=1;i<height;i++)
    {
        for (int j=1;j<=height*4+1;j++)
        {
            cout<<"*";
        }
        cout<<endl;
    }



}

void Task8() {

    cout<<"ODD number under 100"<<endl;
    for (int i=1;i<=100;i++)
        if (i%2!=0)
            cout<<i<<", ";

    cout<<endl;
    cout<<"\nEven number under 100"<<endl;
    for (int i=0;i<=100;i++)
        if (i%2==0)
            cout<<i<<", ";
    cout<<endl;
cout<<"\nEven number under 100 (Reverse)"<<endl;
    for (int i=100;i>=0;i--)
        if (i%2==0)
            cout<<i<<", ";

    cout<<endl;
    cout<<"\nOdd number under 100 (Reverse)"<<endl;
 for (int i=100;i>=0;i--)
     if (i%2!=0)
         cout<<i<<", ";

    cout<<"\nDecrease by division of 2 "<<endl;
    for (int i=100;i>0;) {
        cout<<i<<", ";
        i/=2;
    }

    cout<<endl;
}

void Task9() {
    int choice=0;
    do {
        cout<<"1. Celsius "<<endl;
        cout<<"2. Fahrenheit "<<endl;
        cout<<"3. Kelvin "<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter what temperature unit u want to give input in: ";
        cin>>choice;
        float input=0;
        double output=0;
        switch (choice) {
            case 1:
                cout<<"\n Enter the  temperature: ";
                cin>>input;
                output=(9.0/5.0*input)+32;
                cout<<"The Fahrenheit: ";
                cout<<output<<endl;
                output=input+273.2;
                cout<<"The  Kelvin: ";
                cout<<output<<endl;
                break;
            case 2:
                cout<<"\n Enter the  temperature: ";
                cin>>input;
                output=(input-32)*5.0/9.0;
                cout<<"The Celsius: "<< output<<endl;
                output=output+273.2;
                cout<<"THe Kelvin: ";
                cout<<output<<endl;
                break;
            case 3:
                cout<<"\n Enter the  temperature: ";
                cin>>input;
                output=input - 273.2;
                cout<<"The Celsius: ";
                cout<<output<<endl;
                output=(9.0/5.0*input)+32;
                cout<<"The Fahrenheit: ";
                cout<<output<<endl;
                break;
            case 4:
                cout<<"exiting"<<endl;
                cout<<endl;
                break;

            default:
                cout<<"Invalid choice"<<endl;

        }
    }while (choice!=4);


}

void Task10() {
    int number=0;
    int number2=0;
    int temp=0;

    cout<<"\nenter number1: ";
    cin>>number;
    cout<<"\nenter number2: ";
    cin>>number2;
temp =number;
    number=number2;
    number2=temp;
    cout<<"Number one: "<< number<<endl;
    cout<<"Number two: "<<number2<<endl;

}

void Task11() {
    int k=0;
    cout<<"Enter value of K: "<<endl;
    cin>>k;

    float sum=0;
    float temp=0;
    for (int i=1;i<=k;i++) {
        cin>>temp;
        sum+=temp;
    }
    float result=sum/k;
    cout<<"The Average of the k numbers is "<<result<<endl;

}

void Task12() {
    int k=0;
    cout<<"Enter value of K: "<<endl;
    cin>>k;

    int sum=0;
    int temp=0;
    cout<<"\n Enter values "<<endl;
    for (int i=1;i<=k;i++) {
        cin>>temp;
        sum+=temp;
    }

    cout<<"The Sum of the k numbers is "<<sum<<endl;

}

void Task13() {

    int N=0;
    cout<<"Enter value of N: "<<endl;
    cin>>N;
    if (N<0 ) {
        cout<<"Invalid number"<<endl;
        return;
    }
    int sum=0;
    cout<<"\n Enter values "<<endl;
    for (int i=1;i<N;i++) {
        if (i%3==0 || i%5==0)
            sum+=i;
    }
    cout<<"The Sum of the numbers multiple of 3/5 is "<<sum<<endl;

}

void Task14() {

    int N=0;
    cout<<"Enter value of N: "<<endl;
    cin>>N;
    if (N<0 ) {
        cout<<"Invalid number"<<endl;
        return;
    }
    cout<<"Enter the multiples :  ";
    int num1,num2;
    cin>>num1;
    cin>>num2;
    int sum=0;
    for (int i=1;i<N;i++) {
        if (i%num1==0 || i%num2==0)
            sum+=i;
    }
    cout<<"The Sum of the numbers multiple of numebers is "<<sum<<endl;

}

