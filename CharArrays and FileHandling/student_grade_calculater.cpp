#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;


//<======================================================>
  //              Arrays and Stuff
//<======================================================>


const int ROWS = 10;   
const int COLS = 20;
char words[ROWS][COLS];
int marks[ROWS][COLS];
int row = 0;
int col = 0;
bool flag = 0;

//<======================================================>
  //             Functions Prototype
//<======================================================>


void FileToArray();
void FileToMarks();
void showdata();  //particularly for showing array data it is 2d array
void text();
void quizzmaxmarks();
void quizz_average();
void quizz_3();
void top_scorer();
void top_scorer_quizz();
void marks_by_name();
int sizech(char array[], int limit);
void marks_by_name_quizz();

//<======================================================>
                     // MAIN
//<======================================================>


int main()
{
    FileToArray();
    FileToMarks();
    int choice = 0;
    

    do {

      system("cls");

        		cout << "\n<=============================================================>" << endl;
        		cout << "                         1. Text" << endl;
                cout << "                         2. Quizz Max/Min marks" << endl;
                cout << "                         3. Quizz Average marks" << endl;
                cout << "                         4. Best 3 quizzes      " << endl;
                cout << "                         5. Quizzes Topper      " << endl;
                cout << "                         6. Quizz Wise Topper      " << endl;
                cout << "                         7. Search By name      " << endl;
                cout << "                         8. Change numbers      " << endl;
          		cout << "                         9. Exit" << endl;
        		cout << "<=============================================================>" << endl;

        cout << "Choice: "; cin >> choice;

        switch (choice) 
        {
        case 1:
            text();
            if (flag==0)
              Sleep(8000);
            break;
        case 2:
            quizzmaxmarks();
            Sleep(8000);
            break;
        case 3:
            quizz_average();
            Sleep(8000);
            break;

        case 4:
            quizz_3();
            Sleep(8000);
            break;
        case 5:
            top_scorer();
            Sleep(8000);
            break;
        case 6:
            top_scorer_quizz();
            Sleep(8000);
            break;
        case 7:
            marks_by_name();
            Sleep(8000);
            break;
        case 8:
            marks_by_name_quizz();
            Sleep(8000);
            break;
        case 9:
            cout << "<=====================================================>" << endl;
            cout << "                     Exiting/n" << endl;
            cout << "<=====================================================>" << endl;
            Sleep(3000);
            break;

        }




    } while (choice!=9);


	return 0;
}
//<======================================================>
                   // Functions
//<======================================================>
void marks_by_name() {
    int q = 0;
    cout << "Enter The Name of the Student: ";
    char name[100] = {};
    cin.ignore();
    cin.getline(name, 100);
    int size=sizech(name, 100);
    bool flag = false;
    int index = 0;
    for (int i = 0; i < col; i++) {
        if (words[i][0] == name[0]) 
        {
            for (int j = 0; j < col; j++)
            {
                if (words[i][j] != name[j]) {
                        flag = 0;
                        break;
                }
                if (words[i][size - 1])flag = 1;
            }

        }
        if (flag == 1) {
            index = i;
            break;
        }


    }
    cout << "Name: " << words[index];
    for (int i = 0; i < col; i++)
        cout << "\nQuizz# " << i + 1 << " "<<marks[index][i];



}
void marks_by_name_quizz() {
    int q = 0;
    cout << "Enter The Name of the Student: ";
    char name[100] = {};
    cin.ignore();
    cin.getline(name, 100);
    int size = sizech(name, 100);
    cout << "\nEnter The Quizzno# ";
    cin >> q;
    q--;
    cout << "\n Enter The Number you want to change: ";
    int num = 0;
    cin >> num;
    bool flag = false;
    int index = 0;
    for (int i = 0; i < col; i++) {
        if (words[i][0] == name[0])
        {
            for (int j = 0; j < col; j++)
            {
                if (words[i][j] != name[j]) {
                    flag = 0;
                    break;
                }
                if (words[i][size - 1])flag = 1;
            }

        }
        if (flag == 1) {
            index = i;
            break;
        }


    }
    marks[index][q] = num;
    cout << "\nNumbers updated !" << endl;
    ofstream Wrt("marks.txt");
    if (!Wrt) 
    {
        cout << "\nNot opened\n";
        return ;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {


            Wrt << marks[i][j];
            Wrt << " ";
        }

        Wrt << "\n";
    }
    Wrt.close();

}
int sizech(char array[], int limit) {
    int size = 0;
    for (int i = 0; i < limit; i++) {

        if (array[i] != '\0')size++;
        if (array[i] == '\0')break;


    }
    return size;

}
void top_scorer_quizz()
{
    flag = 1;
    text();
    flag = 0;
    int index = 0;
    cout << "\n<==========================================>" << endl;
    cout << "        TOP SCORERS PER QUIZ" << endl;
    cout << "<==========================================>" << endl;
    for (int i = 0; i < col; i++)
    {
        int  max = marks[0][i];
        for (int j = 1; j < row; j++)
        {

            if (marks[j][i] > max) 
            {
                max = marks[j][i];
                index = j;
            }


        }
        cout << "Quizz# " << i + 1 <<"  "<< words[index] << endl;
    }
    cout << "\n<==========================================>" << endl;

}
void top_scorer()
{
    flag = 1;
    text();
    flag = 0;
    int index = 0;
    float Highest = 0;
    for (int i = 0; i < row; i++)
    {
        float max = 0;
        for (int j = 0; j < col; j++)
        {
            max += marks[i][j];
        }
        if (max > Highest)
        {
            Highest = max;
            index = i;
        }
    }
    float percentage = (Highest * 10) / col;
    cout << "\nThe highest Scorer is: " << words[index];
    cout << "\nThe highest Percentage is: " <<percentage ;
    cout << "\n<==========================================>" << endl;

   
}
void text() {
    cout << "\n<==========================================>" << endl;
    cout << left << setw(8) << "Name" << setw(3) << "Q1" << setw(3) << "Q2" << setw(3) << "Q3" << setw(3) << "Q4" << setw(3) << "Q5" << setw(3) << "Q6" << setw(3) << "Q7" << setw(3) << "Q8" << endl;
    cout << "\n<==========================================>" << endl;
    for (int i = 0; i < row; i++) {
       
            cout <<setw(8)<< words[i];
        for (int j = 0; j<col; j++)
            cout << setw(3) << marks[i][j];
        
        cout << endl;
    }
    cout << "\n<==========================================>" << endl;
}
void quizz_average() {

    cout << "\n<==========================================>" << endl;
    cout << left << setw(10) << "Name:" << right << setw(6) << " Average Marks "<< endl;
    cout << "\n<==========================================>" << endl;
    for (int i = 0; i < row; i++) 
    {
        float max = 0;
        cout << left << setw(8) << "Name: "<<right<<setw(6)<<words[i];
        for (int j = 0; j < col; j++) 
        {
            max += marks[i][j];
        }
        float average = max / col;
        cout << right << setw(6) << average;
        cout << endl;
    }

    cout << "\n<==========================================>" << endl;
}
void quizz_3() {
    cout << "\n<================================================>" << endl;
    cout << left << setw(15) << "Name"
        << right << setw(8) << "Q1"
        << setw(8) << "Q2"
        << setw(8) << "Q3"
        << setw(10) << "Percent" << endl;
    cout << "<=================================================>" << endl;

    for (int i = 0; i < row; i++)
    {
        int temp[1000] = {};  
        for (int j = 0; j < col; j++)
        {
            temp[j] = marks[i][j];

        }
        for (int a = 0; a < col - 1; a++)
        {
            for (int b = a + 1; b < col; b++)
            {
                if (temp[a] < temp[b]) {
                    swap(temp[a], temp[b]);
                }
            }
        }

       
        float percentage = ((temp[0] + temp[1] + temp[2]) * 100) / 30.0;
        cout << left << setw(15) << words[i]
            << right << setw(8) << temp[0]
            << setw(8) << temp[1]
            << setw(8) << temp[2]
            << setw(9) << fixed << setprecision(1) << percentage << "%"
            << endl;
    }

    cout << "<=================================================>" << endl;
}
void quizzmaxmarks() {
    
    cout << "\n<==========================================>" << endl;
    cout << left << setw(10) << "Quizz No:" << right << setw(6) << " Max " << right << setw(6) << " Min " << endl;
     cout << "\n<==========================================>" << endl;
    for (int i = 0; i < col; i++) {
        int max = 0;
        int min = marks[0][i];
        cout << left<<setw(8) << "quizz: "<< setw(1)<<i+1;
        for (int j = 0; j < row; j++){
            if (marks[j][i] > max)
                max = marks[j][i];
            if (marks[j][i] < min)
                min = marks[j][i];
        }
        cout <<right<< setw(6) <<max <<right<< setw(6) << min;
        cout << endl;
    }

    cout << "\n<==========================================>" << endl;
}
void showdata() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
        {
            cout<< marks[i][j]<<" ";
        }
        cout << "\n";
    }
}
void FileToArray() {
    int rowCount = 0;

    ifstream Rdr("data.txt");
    while (Rdr >> words[rowCount]) {
        rowCount++;
        if (rowCount >= ROWS) break; 
    }
    Rdr.close();
}
void FileToMarks() {
    ifstream Rdr("marks.txt");
   
    Rdr >> row;
    Rdr >> col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
        {
            Rdr >> marks[i][j];
        }

    }
    Rdr.close();
}