#include <iostream>
#include <fstream>
#include<Windows.h>
using namespace std;

//<====================================>
//             Prototype
//<====================================>
void filetoarray(char array[]);
int sizech(char array[], int limit);
void showtext(char array[]);
void characters(char array[]);
void words(char array[]);
void sentences(char array[]);
void character(char array[]);
void S_words(char array[]);
void S_line(char array[]);
void l_atstart(char array[]);
void l_atend(char array[]);
void l_atindex(char array[]);
void removeword(char str[]);
void replaceword(char str[]);
//<====================================>
//               Main
//<====================================>
int main()
{
	char array[10000] = {};
	filetoarray(array);

	int  choice = 0;
	do {
		system("cls");
		cout << "\n<=============================================================>" << endl;
		cout << "                         1. Text" << endl;
		cout << "                         2. No of Characters" << endl;
		cout << "                         3. Words" << endl;
		cout << "                         4. Sentences" << endl;
		cout << "                         5. Specific Character" << endl;
		cout << "                         6. Specific Words" << endl;
		cout << "                         7. Specific Line" << endl;
		cout << "                         8. Line at start" << endl;
		cout << "                         9. Line at end" << endl;
		cout << "                         10.Line at index" << endl;
		cout << "                         11.Replace Word" << endl;
		cout << "                         12.Remove Word" << endl;
		cout << "                         13.Exit" << endl;
		cout << "<=============================================================>" << endl;
		cout << "Choice: "; cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			showtext(array);
			Sleep(3000);
			break;
		case 2:
			characters(array);
			Sleep(5000);
			break;
		case 3:
			words(array);
			Sleep(5000);
			break;
		case 4:
			sentences(array);
			Sleep(1000);
			break;
		case 5:
			character(array);
			Sleep(3000);
			break;
		case 6:
			S_words(array);
			Sleep(5000);
			break;
		case 7:
			S_line(array);
			Sleep(5000);
			break;
		case 8:
			l_atend(array);
			Sleep(7000);
			break;
		case 9:
			l_atend(array);
			Sleep(7000);
			break;
		case 10:
			l_atindex(array);
			Sleep(7000);
			break;
		case 11:
			replaceword(array);
			Sleep(7000);
			break;
		case 12:
			removeword(array);
			Sleep(7000);
			break;
		case 13:
			cout << "<=============================================================>" << endl;
			cout << "                         Exiting" << endl;
			cout << "<=============================================================>" << endl;
			break;
		default:
			cout << "   Invalid Choice Entered!" << endl;
			break;
		}
		



	} while (choice!=13);


	return 0;
}

//<====================================>
//               Functions
//<====================================>

void l_atindex(char array[]) {
	char target[10000] = {};
	int index = 0;
	cout << "Enter The index you want to put Line: "; cin >> index;
	cout << "\nEnter The Sentence you want to put: "; cin.ignore(); cin.getline(target, 10000);
	cout << "\nThe Senetence is: " << target;
	int size1 = sizech(array, 10000);
	int size2 = sizech(target, 1000) ;
	for (int i = size1; i >= index ; i--)
	{
		array[i + size2] = array[i];
	}
	int j = 0;
	for (int i = index ; i < size2+size1-2; i++)
	{
		array[i] = target[j];
		j++;
	}
	cout << "\nThe Senetence is: " << array;


}
void l_atend(char array[]) {
	char target[10000] = {};
	cout << "Enter The Sentence you want to put: "; cin.ignore(); cin.getline(target, 10000);
	cout << "\nThe Senetence is: " << target;
	int size1 = sizech(array, 10000);
	int size2 = sizech(target, 1000);
	int j = 0;
	for (int i = size1-1; i < size2+size1; i++)
	{
		array[i] = target[j];
		j++;
	}
	array[size1+size2] = '.';
	cout << "\nThe Senetence is: " << array;
}
void l_atstart(char array[]) {
	char target[10000] = {};
	cout << "Enter The Sentence you want to put: "; cin.ignore(); cin.getline(target, 10000);
	cout << "\nThe Senetence is: " << target;
	int size1 = sizech(array, 10000);
	int size2 = sizech(target, 1000)+1;
	for (int i = size1; i >= 0; i--)
	{
		array[i + size2] = array[i];
	}
	for (int i = 0; i < size2-1; i++)
	{
		array[i] = target[i];
	}
	array[size2-1] = ' ';
	cout << "\nThe Senetence is: " << array;
}
void S_line(char array[]) {
	char target[10000] = {};
	cout << "Enter The Sentence you want to Count: "; cin.ignore(); cin.getline(target, 10000);

	cout << "\nThe Senetence is: " << target;
	int size1 = sizech(array, 10000);
	int size2 = sizech(target, 1000);
	bool flag = 0;
	int count = 0;
	for (int i = 0; i < size1; i++)
	{
		flag = false;
		if (array[i] == target[0])
		{
			for (int j = 0; j < size2; j++)
			{
				if (array[i + j] == target[j])
				{
					flag = true;

				}
				else {
					flag = false;
					break;
				}
			}

		}
		if (flag == true)count++;
	}
	if (count != 0)
		cout << "\nFrequecy of the Sentence: " << target << " is " << count;
	else cout << "\nSentence Doesn't exist in the document" << endl;
}
void S_words(char array[]) {

	char target[1000] = {};
	cout << "Enter The Word you want to Count: "; cin.ignore(); cin.getline(target, 1000);

	cout << "\nThe Word is: " << target;
	int size1 = sizech(array,10000);
	int size2 = sizech(target,1000);
	bool flag = 0;
	int count = 0;
	for (int i = 0; i < size1; i++)
	{
		flag = false;
		if (array[i] == target[0]) 
		{
			for (int j = 0; j < size2; j++)
			{
				if (array[i + j] == target[j]) 
				{
					flag = true;

				}
				else {
					flag = false;
					break;
				}
			}
				
		}
		if (flag == true)count++;
	}
	if(count!=0)
	cout << "\nFrequecy of the Word: " << target << " is " << count;
	else cout << "\nWord Doesn't exist in the document" << endl;
}
void character(char array[]) {
	int size = sizech(array, 10000);
	int count = 0;
	char character = 0;
	cout << "Enter The Character: "; cin >> character;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == character)count++;
	}

	cout << "The number of  character in the documents are: " << count;
	if (count == 0)cout << " No Such Symbol/Character Exist" << endl;
}
void sentences(char array[]) {
	int size = sizech(array, 10000);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == '.' || array[i] == '!' || array[i] == '?')count++;
	}

	cout << "The number of Sentences in the documents are: " << count;


}
void characters(char array[]) {
	int size = sizech(array,10000);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == '\n')continue;
		if (array[i] == ' ')continue;
		count++;

	}

	cout << "The number of Characters in the documents are: " << count;

}
void words(char array[]) {
	int size = sizech(array, 10000);
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == '\n' || array[i] == ' ')count++;
	}

	cout << "The number of Words in the documents are: " << count;

}
void showtext(char array[]) {

	cout << "<=============================================================>" << endl;
	cout << " Text:-" << endl;
	cout << array;
	cout << "<=============================================================>" << endl;
}
void filetoarray(char array[])
{



	ifstream Rdr("Document.txt");
	if (!Rdr) {
		cout << "File doesnot open" << endl;
		return;
	}
	int pointer = 0;      //tactic to save the address
	int a = 1000;
	char temparray[10000] = {};
	while (Rdr.getline(temparray,a)) {

		char ch = 0;
		int i = 0;                               //iterator
        int size1 = sizech(array, 10000);
		int size_t = sizech(temparray, 10000);
		int j = 0;
		for (i = pointer; j < size_t; j++)
		{
			array[i] = temparray[j];
			i++;
			pointer++;
		}
		array[pointer] = '\n';
		pointer++;

		for (i = 0; i < size_t; i++)
			temparray[i] = '\0';
	}
	array[pointer] = '\0';
	}
int sizech(char array[], int limit) {
	int size = 0;
	for (int i = 0; i < limit; i++) {

		if (array[i] != '\0')size++;
		if (array[i] == '\0')break;


	}
	return size;

}
void removeword(char str[])
{
	
	    char target[100] = {};
	    cout << "The string you entered: " << str;
	    cout << "\nenter target" << endl;
		cin.ignore();
	    cin.getline(target, 100);
	    cout << endl;
	    cout << "The target: " << target;
	
	    int  size = sizech(str, 1000);
	    int size2 = sizech(target, 100);
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
void replaceword(char str[])
{
	    char target[100] = {};
	    char replace[100] = {};
	
	    cout << "The string you entered: " << str;
		
	    cout << "\nenter target: ";
		cin.ignore();
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