#include <iostream>
using namespace std;


//==========================================================================================
                                     //Functions Prototypes
//==========================================================================================

//                                         :Question1:
void Task1();
void Task2();
void Task3();

//                                         :Question2:

void Task4();

void Task5();

void Task6();

//                                         :Question3:

void Task7();
void Task8();

//                                         :Question4:
void Task9();
 //                                         :Question5:
void Task10();
void Task11();
void Task12();
//                                           :question 6:
void Task13();


void menu() {
    cout << "<========================================================>" << endl;
    cout << "                       Menu" << endl;
    cout << "<========================================================>" << endl;
    cout << "1. Roll no / name / Section" << endl;
    cout << "2. Quote" << endl;
    cout << "3. Contact Card" << endl;
    cout << "4. Table of 5" << endl;
    cout << "5. Table by user" << endl;
    cout << "6. Table using while loop" << endl;
    cout << "7. Table with start/end" << endl;
    cout << "8. Even number Table" << endl;
    cout << "9. Odd number Table" << endl;
    cout << "10. Table from Reverse" << endl;
    cout << "11. Table with jump" << endl;
    cout << "12. Reverse Table with jump" << endl;
    cout << "13. Sequences" << endl;
    cout << "14. Exit" << endl;
    cout << "<========================================================>" << endl;
}


int main()

{

int choice=0;
    do {
        menu();
        cout<<"Choice: ";
        cin>>choice;

        switch(choice) {
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
            case 6:
                Task6();
                break;

            case 7:
                Task7();
                break;
            case 8:
                Task8();
                break;
            case 9:
                Task9();
                break;
            case 10:
                Task10();
                break;
            case 11:
                Task11();
                break;
            case 12:
                Task12();
                break;
            case 13:
                Task13();
                break;
            case 14:
                cout<<"Exiting!"<<endl;
                break;


        }


    }while(choice!=14);




    return 0;
}


void Task1() //using print statement
{

    cout<<"Muhammad Aashir Khan | "<<"BSCS25079 | "<<"Section A"<<endl;
}

void Task2() //using print statement
{
    cout<< "Programming is not about what you know; it's about what you can figure out."<<endl;
}

void Task3()  //using print statements
{
    cout<<"==========================="<<endl;
    cout<<"Name     :  Ali Maqsood"<<endl;
    cout<<"Email    :  ali@gmail.com"<<endl;
    cout<<"Phone No :  03331234567 "<<endl;
    cout<<"========================="<<endl;
}

void Task4() {
    cout<<"         \" Table of 5 \" " <<endl;
   cout<<"5 * 1 =  5"<<endl;
   cout<<"5 * 2 =  10 "<<endl;
   cout<<"5 * 3 =  15 "<<endl;
   cout<<"5 * 4 =  20 "<<endl;
   cout<<"5 * 5 =  25 "<<endl;
   cout<<"5 * 7 =  30 "<<endl;
   cout<<"5 * 8 =  35 "<<endl;
   cout<<"5 * 9 =  40 "<<endl;
   cout<<"5 * 10 =  50 "<<endl;
}

void Task5() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;

    cout<<"          Table of "<<n<<endl;

    cout<<n<<" * "<<" 1 "<<" = "<<n*1<<endl;
    cout<<n<<" * "<<" 2 "<<" = "<<n*2<<endl;
    cout<<n<<" * "<<" 3 "<<" = "<<n*3<<endl;
    cout<<n<<" * "<<" 4 "<<" = "<<n*4<<endl;
    cout<<n<<" * "<<" 5 "<<" = "<<n*5<<endl;
    cout<<n<<" * "<<" 6 "<<" = "<<n*6<<endl;
    cout<<n<<" * "<<" 7 "<<" = "<<n*7<<endl;
    cout<<n<<" * "<<" 8 "<<" = "<<n*8<<endl;
    cout<<n<<" * "<<" 9 "<<" = "<<n*9<<endl;
    cout<<n<<" * "<<"10 "<<" = "<<n*10<<endl;


}

void Task6() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;

    cout<<"          Table of "<<n<<endl;

    int i=1;
    while (i<=10) {
        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
        i++;
    }

}

void Task7() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;
    cout<<"\n          Table of "<<n<<endl;


    while (i<=j) {
        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
        i++;
    }

}

void Task8() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;
    cout<<"\n          Table of "<<n<<endl;


    while (i<=j) {
        if (i%2==0)
        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
        i++;
    }

}

void Task9() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;
    cout<<"\n          Table of "<<n<<endl;


    while (i<=j) {
        if (i%2 !=0)
        cout<<n<<" * "<<i<<" = "<<n*i<<endl;
        i++;
    }

}

void Task10() {
    int n =0;

    cout<<"Enter the number you want table of: ";
    cin>>n;
    int i=0;
    cout<<"\nEnter the start:";
    cin>>i;
    int j=0;
    cout<<"\nEnter the end:";
    cin>>j;
    cout<<"\n          Table of "<<n<<endl;


    while (i>=j) {

            cout<<n<<" * "<<i<<" = "<<n*i<<endl;
      i --;
    }

}

void Task11() {
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

void Task12() {
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

void Task13() {
    cout<<" odd 1-100"<<endl;
    int i = 1;
    while (i < 100) {
        cout << i << " ";
        i += 2;
    }
    cout << "\n\n";

    i = 0;
    cout<<" odd 100-1"<<endl;
    while (i < 100) {
        cout << i << " ";
        i += 2;
    }
    cout << "\n\n";
    cout<<" odd 100-1"<<endl;
    i = 99;
    while (i >= 1) {
        cout << i << " ";
        i -= 2;
    }
    cout << "\n\n";
    cout<<" even 100-1"<<endl;
    i = 98;
    while (i >= 0) {
        cout << i << " ";
        i -= 2;
    }
}
