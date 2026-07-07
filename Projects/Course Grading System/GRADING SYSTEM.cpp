#include <iostream>
using namespace std;
int main()
{
	int highest_marks = -1;
	int lowest_marks =100;
	char a, b;
	int i = 0;
	int marks = 0;
	int total = 0;
	int p=0;//pass counter
	int f=0;//fail counter
	int gradeA = 0, gradeB = 0, gradeC = 0, gradeD = 0, gradeE = 0, gradeF = 0;
	
	cout << "enter obtained marks of 6 courses ( 0-99)" << endl;

	while (i <= 10) {
		cin >> a >> b;
		i++;
		a = a - '0';
		b = b - '0';
		marks = a * 10 + b;
		if (marks > 99 || marks < 0) {
			cout << "INVALID NUMBERS " << endl;
			return 0;
	    }


		if (marks > highest_marks) {

			highest_marks = marks;

		}
		if (marks < lowest_marks) {
			lowest_marks = marks;
		}
		
		total += marks;
		
		if (marks < 50) {
			f++;
		}
		else {
			p++;
		}
		if (marks >= 90) {
			gradeA++;
		}
		else if (marks >= 80) {
			gradeB++;
		}
		else if (marks >= 70) {
			gradeC++;
		}
		else if (marks >= 60) {
			gradeD++;
		}
		else if (marks >= 50) {
			gradeE++;
		}
		else {
			gradeF++;
		}
		i++;
	}
	float average = total / 6.0;



	cout << "---------------------------------------------------------" << endl;
	cout << "=========================RESULT==========================" << endl;
	cout << "HIGHEST MARKS :" << highest_marks << endl;
	cout << " LOWEST MARKS :" << lowest_marks << endl;
	cout << "      AVERAGE :" << average << endl;
	cout << "PASSED:" << p<<"\t"<< "FAILED:" << f << endl;
	cout << "GRADE DISTRIBUTION HISTOGRAM" << endl;
	cout << "A(90-100): " << string(gradeA, '*') << endl;
	cout << "B(80-89):  " << string(gradeB, '*') << endl;
    cout << "C(70-79):  " << string(gradeC, '*') << endl;
	cout << "D(60-69):  " << string(gradeD, '*') << endl;
	cout << "E(50-59):  " << string(gradeE, '*') << endl;
	cout << "F(<50):    " << string(gradeF, '*') << endl;

	

	
	return 0;
}


		

