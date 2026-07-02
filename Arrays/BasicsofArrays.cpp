#include <iostream>


using namespace std;

//                    Functions Prototypes
void Take_input(int array[], int size);
void Print_array(int arr[],int size);
void clear_screen();
void pause();

void TASK1();
void TASK2();
void TASK3();

bool is_prime(int n);
void inclusive_exclusive();

void menu() {
    cout<<"<=======================================>"<<endl;
    cout<<"                Menu"<<endl;
    cout<<"<=======================================>"<<endl;
    cout<<"1. Task 1 "<<endl;
    cout<<"2. Inclusive / Exclusive "<<endl;
    cout<<"3. Task 2 "<<endl;
    cout<<"4. Task 3"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"<=======================================>"<<endl;
}


int main() {


    int choice=0;

    do {

        menu();
        cout<<"Choice: ";
        cin>>choice;

        switch (choice) {

            case 1:
                clear_screen();
                TASK1();
                pause();
                break;
            case 2:
                clear_screen();
                inclusive_exclusive();
                pause();
                break;
            case 3:
                clear_screen();
                TASK2();
                pause();
                break;
            case 4:
                clear_screen();
                TASK3();
                pause();
                break;
            case 5:
                cout<<"Exiting"<<endl;
                break;
            default:
                cout<<" Invalid Choice "<<endl;


        }


    }while (choice != 5);

     return 0;
 }

void TASK3() {


    int array[1000]={};


    int size=0;

    cout<<"Enter the size: ";
    cin>>size;
    cout<<endl;
cout<<"Enter values: ";
    Take_input(array, size);

    int max=array[0];
    int min=array[0];
    int sec_max=0;
    int sec_min=0;

    for (int i=0;i<size;i++) {
        if (max<array[i]) {
            sec_max=max;
            max=array[i];

        }
        if (sec_max < array[i] && array[i] < max) {
            sec_max=array[i];
        }
        if (min>array[i]) {
            sec_min=min;
            min=array[i];

        }
        if (sec_min > array[i] && array[i] > min) {
            sec_min=array[i];
        }
    }
    cout<<"MAX: "<<max<<endl;
    cout<<"Second Max: "<<sec_max<<endl;
    cout<<"Min: "<<min<<endl;
    cout<<"Second Min: "<<sec_min<<endl;

}

void TASK2() {

    cout<<" Searching"<<endl;
    int array[1000]={};


    int size=0;

    cout<<"Enter the  Values:  ";

    for (size =0;true;size++)
    {
        cin>>array[size];
        if (array[size]==-1)break;
    }

    cout<<"Enter the  Target:  ";
    int target;
    cin>>target;


    Print_array (array, size);
    int first=0;
    int last=0;
    int kth_index=0;
    for (int i =0;i<size;i++) {
        if (array[i]==target) {
            first=i;

            break;
        }

    }

    cout<<"The index of first occurrence of target: "<<first<<endl;


    for (int i =size-1;i>=0;i--) {
        if (array[i]==target) {
            last=i;

            break;
        }

    }

    cout<<"The index of last occurrence of target: "<<last<<endl;

    cout<<"Enter which occurrence you want : ";
    int times;
    cin>>times;
    int count =0;
    for (int i =0;i<size;i++) {
        if (array[i]==target) {

            count++;
            if (count==times) {
                kth_index=i;
                break;
            }

        }

    }

    cout<<"The "<<times<<" occurence of the "<<target<<" is : "<<kth_index<<endl;

    cout<<"Enter which occurrence you want (From Last) : ";
    times=0;
    cin>>times;
    count =0;
    for (int i =size;i>=0;i--) {
        if (array[i]==target) {

            count++;
            if (count==times) {
                kth_index=i;
                break;
            }

        }

    }

    cout<<"The "<<times<<" occurrence of the "<<target<<" is : "<<kth_index<<endl;
}

void TASK1() {
    cout<<"Arrays Declaration"<<endl;


    int array[1000]={};
    cout<<"Enter Size of Array  (MAX 1000):   ";
    int size;
    cin>>size;

    cout<<"\n Random Numbers"<<endl;
    for (int i=0;i<size ;i++) {

        array[i]=rand()%100;;
    }

    Print_array (array, size);

    cout<<"\n Index Numbers "<<endl;
    for (int i=0;i<size ;i++) {

        array[i]=i;
    }

    Print_array (array, size);
    cout<<"\n Multiple of 2"<<endl;
    int counter=0;
    int iterator=0;
    for (int i=0;counter!=size ;i++) {
        if (i%2==0) {
            array[iterator]=i;
            counter++;
            iterator++;
        }
    }
    Print_array (array, size);
    cout<<"\n Multiple of 5 "<<endl;
    counter=0;
    iterator=0;
    for (int i=0;counter!=size ;i++) {
        if (i%5==0) {
            array[iterator]=i;
            counter++;
            iterator++;
        }
    }
    Print_array (array, size);

    cout<<"\n Multiple of 2 excluding zero"<<endl;
    counter=0;
    iterator=0;
    for (int i=2;counter!=size ;i++) {
        if (i%2==0) {
            array[iterator]=i;
            counter++;
            iterator++;
        }
    }
    Print_array (array, size);
    counter=0;
    iterator=0;
    cout<<"\n ODD Numbers"<<endl;
    for (int i=0;counter!=size ;i++) {
        if (i%2!=0) {
            array[iterator]=i;
            counter++;
            iterator++;
        }
    }
    Print_array (array, size);


    cout<<"\n Prime Numbers"<<endl;
    counter=0;
    iterator=0;
    for (int i=2;counter!=size ;i++) {
        if (is_prime(i)) {
            array[iterator]=i;
            counter++;
            iterator++;
        }
    }
    Print_array (array, size);
    cout<<"\n Alphabets"<<endl;
    char Array[26]={};
    char alphabet='a';
    for (int k=0;k<26 ;k++) {

        Array[k]=alphabet;
        alphabet++;
    }
    cout<<"[ ";
    for (int i = 0; i < 26; i++) {
        cout << Array[i] << " ";
    }
    cout<<"]";
    cout<<endl;


}

bool is_prime(int n)
 {
   for (int i=2;i<=(n)/2;i++) {
       if (n%i==0) return false;
   }

    return true;

}

void Take_input(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }
}
void Print_array(int arr[],int size) {
    cout<<"[ ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout<<"] ";
    cout<<endl;
}


void inclusive_exclusive() {
    int array[1000]={};
    int iterator=0;
    int start=0;
    int end=0;
    cout<<"Enter the start: ";
    cin>>start;
    cout<<"Enter the end: ";
    cin>>end;

    int size=end-start+1;
    int Size=end-start;

    cout<<"\n Range Inclusive"<<endl;
    for (int k=start;k<=end;k++)
    {
        array[iterator]=k;
        iterator++;
    }
    Print_array (array, size);


    cout<<"\n Range Exclusive"<<endl;
    iterator=0;
    for (int i=start;i<end ;i++) {


        array[iterator]=i;
        iterator++;

    }
    Print_array (array, Size);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {

    cout<<"Enter any key to continue"<<endl;
    cin.ignore();
    cin.get();
}

