#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;





//  helping functions

long long n_a = 0;  //number of accounts loaded
long long last_index = 0;
long long t_l = 0;  //transaction loaded
// -------------- transactions ki arrays ---------------------

const long long t = 1000;
long long account[t] = {};
long long account2[t] = {};
long long amount[t] = {};
long long t_t[t] = {};
long long getindex() {

	for (long long i = 0; i < 1000; i++) {
		if (account[i] == 0) {
			return i;
		}

	}

}
long long index = getindex();
//<========== Function Prototypes ============>

//<================== Arrays ===============>
const long long capacity = 2000;
long long account1[capacity] = {};
long long passk[capacity] = {};
long long balance[capacity] = {};
char status[capacity] = {};     //status array for A -->ACTIVE  D--->DEACTIVE     C---->CLOSED
long long failed_A[capacity] = {};   //failed attempts ki array hai
long long locked[capacity] = {};   //aashir ye pdf mai likhi thi in pai kaam ho na hai


long long encrypt_pin(long long pin) {
	return pin - 1111;
}

long long decrypt_pin(long long pin) {
	return pin + 1111;
}
void append_in_array(long long account[], long long passkey[], long long balance[], char status[], long long failed_attempt[], long long locked[], long long capacity) {

	ofstream fout("input.txt");
	for (long long i = 0; i < n_a; i++) {
		long long p = 0;
		fout << account[i] << "|";
		
		p=passkey[i];
		long long pin = encrypt_pin(p);
		fout << pin;

		fout<< "|" << balance[i] << "|" << status[i] << "|" << failed_attempt[i] << "|" << locked[i] << "|" << endl;

	}


}
void gettxt() {

	ifstream fin;
	fin.open("trans.txt");
	if (!fin) {
		cout << "The file not opened" << endl;
	}
	char  ch = 0;
	for (long long i = 0; i < t; i++) {

		fin >> account[i];
		fin >> ch;

		fin >> t_t[i];
		fin >> ch;

		fin >> account2[i];
		fin >> ch;

		fin >> amount[i];
		fin >> ch;

		if (account[i] != 0) {
			t_l++;
		}
	}



}

void load_transactions(long long id_arr[], long long type_arr[], long long src_arr[], long long dst_arr[], long long amt_arr[], long long max_capacity, long long& count) {

	ifstream fin("trans.txt");
	long long i = 0;
	char ch;
	while (fin.eof())

	{
		fin >> account[i];

		fin >> ch;

		fin >> t_t[i];

		fin >> ch;

		fin >> account2[i];

		fin >> ch;

		fin >> amount[i];

		fin >> ch;

		i++;
	
	}
	fin.close();

}
void display_mini_statement(long long account_in_use) {

	gettxt();
	system("cls");
	long long k = 0;
	cout << "<========================================================================>" << endl;
	cout << "    Enter k for Mini Statement: " ;
	cin >> k;
	cout << "<========================================================================>" << endl;
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "<=========================== Mini Statement ! ==========================>" << endl;
	cout << "\n";
	cout << "\n";
	cout << "\n";
	long long count = 0;
	bool flag = true;
	for (long long i = 0; i<t_l && count!=k; i++) {

		if (account[i] == account_in_use && t_t[i] !=0) {
			cout << "Account: " << account[i];
			if (t_t[i] == 1)cout << " Transactiontype:    Withdraw";
			if (t_t[i] == 2)cout << " Transactiontype:     Deposit";
			if (t_t[i] == 3)cout << " Transactiontype: Transferout";
			if (t_t[i] == 4)cout << " Transactiontype:  Transferin";


			if (t_t[i] == 4 || t_t[i] == 1) {
				cout << " Accountfrom: " << account2[i];
			}
			else {
				cout << " AccountTo: " << account2[i];
			}
			cout << " Amount: " << amount[i];
			cout << "\n";
			flag = false;
			count++;
		}
		
	}
	if (flag == true) {

		cout << "<======================== no recent activity ========================>" << endl;

	}
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "<========================================================================>" << endl;





}
void file_to_array(long long account[], long long passkey[], long long balance[], char status[], long long failled_A[], long long locked[], long long capacity);
long long linear_search(long long array[], long long target, long long capacity) {
	for (long long i = 0; i < capacity; i++) {

		if (array[i] == target) {
			return i;
			break;
		}


	}
	return -1;
}
void _balance(long long balance) {
	system("cls");

	cout << "<============================================>" << endl;
	cout << "      The Balance is " << balance << endl;
	cout << "<============================================>" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}
void login(long long array[], long long paskey[], long long capcity, bool& flag, long long& index, char status[], bool& flag1, bool& flag2);
long long pin_masked() {
	const long long pinlength = 4;
	long long pin = 0;

	cout << "Enter 4 digit PIN: ";

	for (long long i = 0; i < pinlength; ++i) {
		char ch = _getch();     //for bonus polong longs jalal bhai

		if (ch >= '0' && ch <= '9') {
			cout << '*';
			pin = pin * 10 + (ch - '0');

		}
		else {
			i--;
		}
	}

	cout << endl;
	return pin;
}
void withdraw(long long& balance, long long account[], long long passkey[], long long Balance[], char status[], long long failed_attempts[], long long locked[], long long capacity, long long index) {
	unsigned long long amount = 0;
	bool flag = true;
	do {
		if (flag == false) {
			cout << "      Enter Valid Amount!       " << endl;
		}
		cout << "Enter the amount you want to Withdraw" << endl;
		cin >> amount;
		if (amount > balance) {
			flag = false;
		}
		else {
			flag = true;
		}
	} while (flag == false);


	balance -= amount;
	system("cls");

	cout << "<============================================>" << endl;
	cout << "      The updated Balance is " << balance << endl;
	cout << "<============================================>" << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	append_in_array(account, passkey, Balance, status, failed_attempts, locked, capacity);
	ofstream fout("trans.txt", ios::app);
	if (!(fout)) {
		cout << "Error in appending transaction file\n";
	}


	fout << account[index] << "|";
	fout << 1 << "|";
	fout << account[index] << "|";
	fout << amount << "|";
	fout << '\n';
	t_l++;
	fout.close();
}
void deposit(long long& balance, long long account[], long long passkey[], long long Balance[], char status[], long long failed_attempts[], long long locked[], long long capacity, long long index) {
	long long amount = 0;

	cout << "Enter the amount you want to Deposit" << endl;
	cin >> amount;
	if (amount < 0) {
		cout << "<============      Invalid amount    =============>" << endl;
		deposit(balance, account, passkey, Balance, status, failed_attempts, locked, capacity, index);
	}

	balance += amount;
	system("cls");

	cout << "<============================================>" << endl;
	cout << "      The updated Balance is " << balance << endl;
	cout << "<============================================>" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	append_in_array(account, passkey, Balance, status, failed_attempts, locked, capacity);
	ofstream fout("trans.txt", ios::app);
	if (!(fout)) {
		cout << "Error in appending transaction file\n";
	}


	fout << account[index] << "|";
	fout << 2 << "|";
	fout << account[index] << "|";
	fout << amount << "|";
	fout << '\n';
	t_l++;
	fout.close();
}
void transfer(long long& balance, long long array[], long long capacity, long long balanceA[], char status[], long long failed_attempts[], long long locked[], long long passkey[], long long index_inuse, bool& flag1) {

	long long amount = 0;
	long long account = 0;
	cout << "Enter the Account you want to send money" << endl;
	cin >> account;
	long long index = linear_search(array, account, capacity);
	if (index == -1) {
		system("cls");
		cout << "The account Does not exist in the Database" << endl;
		transfer(balance, array, capacity, balanceA, status, failed_attempts, locked, passkey, index, flag1);
	}
	else if (status[index] == 'C') {
		system("cls");
		flag1 = false;
		return;
	}
	else if (index == index_inuse) {
		system("cls");
		cout << "You cannot transfer in your own account" << endl;
		transfer(balance, array, capacity, balanceA, status, failed_attempts, locked, passkey, index, flag1);
	}
	else {
		system("cls");
		bool flag = true;
		do {
			if (flag == false) {
				cout << "<------ The Amount you entered is in valid  ----->" << endl;
			}
			cout << "            Enter the amount you want to Deposit" << endl;
			cin >> amount;
			if (amount <= balance && amount >= 0) break;
			else flag = false;
		} while (1);//true

		balance -= amount;
		balanceA[index] += amount;
		system("cls");

		cout << "<============================================>" << endl;
		cout << "      Your updated Balance is " << balance << endl;
		cout << "<============================================>" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		append_in_array(array, passkey, balanceA, status, failed_attempts, locked, capacity);

		ofstream fout("trans.txt", ios::app);
		if (!(fout)) {
			cout << "Error in appending transaction file\n";
		}


		fout << array[index_inuse] << "|";
		fout << 3 << "|";
		fout << account << "|";
		fout << amount << "|";
		fout << '\n';
		t_l++;

		fout << account << "|";
		fout << 4 << "|";
		fout << array[index_inuse] << "|";
		fout << amount << "|";
		fout << '\n';
		t_l++;	
		fout.close();



	}




}
void password_change(long long& pin, long long account[], long long passkey[], long long Balance[], char status[], long long failed_attempts[], long long locked[], long long capacity) {

	long long pin2;

	cout << "<------ Enter orginal pin --------->" << endl;
	pin2 = pin_masked();
	if (pin2 != pin) {
		cout << "<------TRY Again------->" << endl;
		password_change(pin, account, passkey, Balance, status, failed_attempts, locked, capacity);

	}
	else {
		bool flag = true;
		do {
			if (flag == false) {
				cout << "<--- Don't enter same pin --->" << endl;
			}
			cout << "    <------- Enter new pin ------>" << endl;
			pin2 = pin_masked();
			if (pin2 == pin) {
				flag = false;

			}
			else {
				break;
			}
		} while (1);
		pin = pin2;

		cout << "<============================================>" << endl;

		cout << "     Pin changed Successfully" << endl;

		cout << "<============================================>" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		append_in_array(account, passkey, Balance, status, failed_attempts, locked, capacity);
	}


}
void newaccount() {
	cout << "<===================  New Account Registeration ================>" << endl;
	long long accountt = account1[n_a-1]+1;
	char statust = 'D';
	long long balancet = 0;
	long long pin = 0;
	bool flag = true;
	bool flag2 = true;
	
	
	
		account1[n_a] = accountt;
		cout << "              <=========================================>" << endl;
		cout << "                       Accountd id: "<<accountt  << endl;
		cout << "              <=========================================>" << endl;

		pin = pin_masked();
		passk[n_a] = pin;
		status[n_a] = 'D';
		
		cout << "Enter long longial deposit: ";
	
		long long deposit = 0;
		long long counts = 0;
		char ch=0;

		while(1) {
			ch = _getch();
		
			if (ch >= '0' && ch <= '9') {
			
				deposit = deposit * 10 + (ch - '0');
				cout << ch;
				counts++;
			}
			else if (ch==13||ch==32)
			{
				break;
			}
			else if (ch == 8 && counts> 0)
			{				counts--;
				deposit = deposit / 10 ;
				cout << "\b \b";
			}
			else if(ch!=8)
			{
				flag2 = false;
				counts++;
			}
		}

		if (flag2 == 0) {
			cout << "You cannot enter characters " << endl;
			newaccount();

		}
		cout << endl;
		
		balance[n_a] = deposit;
		n_a++;
		cout << "              <=========================================>" << endl;
		cout << "                           Accountd id Created    " << endl;
		cout << "              <=========================================>" << endl;

		append_in_array(account1, passk, balance, status, failed_A, locked, capacity);


	

}
void close() {
	cout << "	<============================ Close Account ==================>" << endl;
	long long accountt = 0;
	cout << "      Enter Account id: ";
	cin >> accountt;
	long long index = 0;
	bool flag = true;
	for (long long i = 0; i < n_a; i++) {
		if (account1[i] == accountt) {
			flag = false;
			index = i;

		}

	}
	if (flag == true) {
		cout << "              <=========================================>" << endl;
		cout << "                      Accountd id already exist     " << endl;
		cout << "              <=========================================>" << endl;
		close();
		return;
	}
	if (status[index] == 'C') {
		cout << "              <=========================================>" << endl;
		cout << "                      Accountd id is already Closed     " << endl;
		cout << "              <=========================================>" << endl;

		return;
	}
	cout << " Do you want to close the account    y/Y   ||  N/n" << endl;
	char choice = '0';
	cin >> choice;
	switch (choice)
	{
	case 'Y':
		status[index] = 'C';
		cout << "<======================= Account Closed Successfully ============================>" << endl;
		break;
	case 'y':
		cout << "<======================= Account Closed Successfully ============================>" << endl;
		status[index] = 'C';
		break;
	case 'N':
		cout << "              <=========================================>" << endl;
		cout << "                      Account id is not Closed    " << endl;
		cout << "              <=========================================>" << endl;


		return;

	case 'n':
		cout << "              <=========================================>" << endl;
		cout << "                      Account id is not Closed    " << endl;
		cout << "              <=========================================>" << endl;

		return;


	default:
		cout << "Invalid Choice !" << endl;
		break;

	}
	append_in_array(account1, passk, balance, status, failed_A, locked, capacity);

}
void deactivate() {

	cout << "	<============== Deactivate / Activate =============>" << endl;
	long long accountt = 0;
	cout << "      Enter Account id: ";
	cin >> accountt;
	long long index = 0;
	bool flag = true;
	char choice = 0;
	for (long long i = 0; i < n_a; i++) {
		if (account1[i] == accountt) {
			flag = false;
			index = i;
			break;
		}

	}
	if (flag == true) {
		cout << "              <=========================================>" << endl;
		cout << "                      Accountd id already exist     " << endl;
		cout << "              <=========================================>" << endl;
		deactivate();
	}
	if (status[index] == 'C') {
		cout << "              <=========================================>" << endl;
		cout << "                    Accountd id is already closed!    " << endl;
		cout << "              <=========================================>" << endl;
		deactivate();
		
	}
	else if (status[index] == 'D') {
		cout << "              <=========================================>" << endl;
		cout << "                    Accountd id  Status: 'D'    " << endl;
		cout << "              <=========================================>" << endl;
		cout << "                         IT IS DEACTIVATED !" << endl;
		cout << "                      DO YOU WANT TO ACTIVATE IT " << endl;
		cout << "                                   Y/N             " << endl;
		cout << "              <=========================================>" << endl;
		cout << "Choice: "; cin >> choice;
		switch (choice)
		{
		case 'Y':
			status[index] = 'A';
			cout << "<======================= Account Activated Successfully ============================>" << endl;
			break;
		case 'y':
			cout << "<======================= Account Activated Successfully ============================>" << endl;
			status[index] = 'A';
			break;
		case 'N':
			cout << "Account is not Activated" << endl;

			return;

		case 'n':
			cout << "Account is not Activated" << endl;
			return;


		default:
			cout << "Invalid Choice !" << endl;
			break;

		}

	}
	else if (status[index] =='A') {
		cout << "              <=========================================>" << endl;
		cout << "                    Accountd id  Status: 'A'    " << endl;
		cout << "              <=========================================>" << endl;
		cout << "                         IT IS ACTIVATED !" << endl;
		cout << "                      DO YOU WANT TO DEACTIVATE IT " << endl;
		cout << "                                   Y/N             " << endl;
		cout << "              <=========================================>" << endl;
		cout << "Choice: "; cin >> choice;
		switch (choice)
		{
		case 'Y':
			status[index] = 'D';
			cout << "<======================= Account DEACTIVATED Successfully ============================>" << endl;
			break;
		case 'y':
			cout << "<======================= Account DEACTIVATED Successfully ============================>" << endl;
			status[index] = 'D';
			break;
		case 'N':
			cout << "<============================  Account is ACTIVE  =========================================>" << endl;

			return;

		case 'n':
			cout << "<============================  Account is ACTIVE  =========================================>" << endl;
		
			return;


		default:
			cout << "Invalid Choice !" << endl;
			break;
			
		}
	}
	else  {
		cout << "              <=========================================>" << endl;
		cout << "                    Accountd id  Status: 'L'    " << endl;
		cout << "              <=========================================>" << endl;
		cout << "                             IT IS Locked !" << endl;
		cout << "                      DO YOU WANT TO ACTIVATE IT " << endl;
		cout << "                                   Y/N             " << endl;
		cout << "              <=========================================>" << endl;
		cout << "Choice: "; cin >> choice;
		
		
		switch (choice)
		{
		case 'Y':
			status[index] = 'A';
			cout << "<======================= Account ACTIVATED Successfully ============================>" << endl;
			break;
		case 'y':
			cout << "<======================= Account  ACTIVATED Successfully ============================>" << endl;
			status[index] = 'A';
			break;
		case 'N':
			cout << "<===========================  Account is Locked ======================================>" << endl;

			return;

		case 'n':
			cout << "<============================= Account is Locked ======================================>" << endl;
			return;


		default:
			cout << "Invalid Choice !" << endl;
			break;
			return;
		}
	}
	append_in_array(account1, passk, balance, status, failed_A, locked, capacity);


}
void account_display() {
	cout << "<===============================================>" << endl;
	cout << "            :Search Account Below:  " << endl;
	long long accountt = 0;
	cout << "<===============================================>" << endl;
	cout << "Enter the Account Number: ";
	cin >> accountt;
	cout << "<===============================================>" << endl;
	bool flag = true;
	long long index = 0;
	for (long long i = 0; i < n_a; i++) {

		if (account1[i] == accountt) {
			flag = false;
			index = i;
			break;
		}


	}
	if (flag == true) {
		cout << "<===============================================>" << endl;
		cout << "     The Account YOU Entered doesn't exist  " << endl;
		cout << "<===============================================>" << endl;
		return;

	}

	cout << "<===============================================>" << endl;
	cout << "     The Account ID: " << account1[index] << endl;
	cout << "            Balance: " << balance[index] << endl;
	cout << "             Status: " << status[index] << endl;
	cout << "<===============================================>" << endl;


}
void account_displayall() {

	cout << "<==================================================================================>" << endl;
	cout << "                       : Accounts oF BanK Crown Ledger:  " << endl;
	cout << "<===================================================================================>" << endl;
	cout << "\n\n";
	cout << "\n\n";
	cout << "<===================================================================================>" << endl;
	for (long long i = 0; i < n_a; i++) {
	
		cout << "     The Account ID: " << account1[i]<<"  ";
		cout << "            Balance: " << balance[i] << "  ";
		cout << "             Status: " << status[i] << "  ";
	
		cout << "\n";

	}
	cout << "<===================================================================================>" << endl;
}
void unlock() {

	cout << "<<=========================== Unlock All Account ==========================>" << endl;
	cout << "\n \n \n  Do You Want To Continue ?" << endl;
	cout << "Y/y Yes" << endl;
	cout << "N/n  No" << endl;
	char choice = 0;
	cin >> choice;
	switch (choice) {
	case 'Y':

		for (long long i = 0; i < n_a; i++) {
			status[i] = 'A';

		}
		cout << "All Account Unlocked" << endl;
		break;
	case 'y':

		for (long long i = 0; i < n_a; i++) {
			status[i] = 'A';

		}
		cout << "All Account Unlocked" << endl;
		break;
	case 'N':
		cout << "All Account status are same as Before" << endl;
		break;
	case 'n':
		cout << "All Account status are same as Before" << endl;
		break;
	default :
		cout << "Invalid choice Entered" << endl;
	}
	append_in_array(account1, passk, balance, status, failed_A, locked, capacity);
}

long long user();
long long manager();

int main() {
	char choice = 0;
	bool flag = true;
	long long count = 0;
	do {

		system("cls");
		cout << "<============== Welcome To Bank CrownLedger ==================>" << endl;

		cout << "              \"Where Innovation Meets Trust.\"  " << endl;

		cout << endl;
		cout << endl;
		cout << endl;

		cout << "<======================== MODES =============================>" << endl;
		if (flag == false) {
			cout << "            <-- Invalid Choice entered! -->" << endl;
		}
		flag = true;
		cout << " Manager MODE                 Enter: M  or m" << endl;
		cout << "Customer MODE                 Enter: C  or c" << endl;
		cout << "         EXIT                 Enter: E  or e" << endl;


		cout << "Choice: "; cin >> choice;
		switch (choice) {
		case 'M':
			system("cls");
			manager();
			break;
		case 'm':
			system("cls");
			manager();
			break;
		case 'C':
			system("cls");
			user();
			break;
		case 'c':
			system("cls");
			user();
			break;
		case 'E':
			system("cls");
			cout << "Exiting ........." << endl;
			return 0;
			break;
		case 'e':
			system("cls");
			cout << "Exiting ........." << endl;
			return 0;
			break;
		default:
			flag = false;
			break;
		}
	} while (flag != true);





	return 0;
}

//<===============Functions=================>

void file_to_array(long long account[], long long passkey[], long long balance[], char status[], long long failled_Attempt[], long long locked[], long long capacity) {
	ifstream fin;
	fin.open("input.txt");
	if (!fin) {
		cout << "The file not opened" << endl;
	}
	char  ch = 0;
	long long count = 0;
	for (long long i = 0; i < capacity; i++) {
		long long p = 0;
		fin >> account[i];
		fin >> ch;

		fin >> p;
		long long pin = decrypt_pin(p);
		passkey[i]=pin;
		fin >> ch;

		fin >> balance[i];
		fin >> ch;

		fin >> status[i];
		fin >> ch;

		fin >> failled_Attempt[i];
		fin >> ch;

		fin >> locked[i];
		fin >> ch;
		if (account[i] == 0) {
			count++;
			if (count == 1) {
				n_a = i;
			}


		}

	}


}

long long user() {
	system("cls");
	cout << "<=========================================>" << endl;
	cout << "                Customer Mode      " << endl;
	cout << "<=========================================>" << endl;
	cout << "        Your Money. Your Control.   " << endl;



	//<================== Arrays ===============>
	const long long capacity = 2000;
	long long account[capacity] = {};
	long long passkey[capacity] = {};
	long long balance[capacity] = {};
	char status[capacity] = {};     //status array for A -->ACTIVE  D--->DEACTIVE     C---->CLOSED
	long long failed_A[capacity] = {};   //failed attempts ki array hai
	long long  locked[capacity] = {};   //aashir ye pdf mai likhi thi in pai kaam ho na hai



	file_to_array(account, passkey, balance, status, failed_A, locked, capacity);  //file sai arrray;

	long long index = -1;
	bool flag = false;
	bool flag_account = 0;
	bool flag1 = 0;
	bool flag2 = 0;
	login(account, passkey, capacity, flag, index, status, flag1, flag2);
	if (flag1 == true) {
		return 0;
	}
	if (flag == false) {
		status[index] = 'L';
		cout << "\n \n \n<-------------- The Account is locked ----------------->" << endl;
		cout << "        The Acoount's password  is incorrect" << endl;
		cout << "<---------------- CONTACT MANAGER! ------------------>" << endl;
		append_in_array(account, passkey, balance, status, failed_A, locked, capacity);
		return 0;
	}
	else if (status[index] == 'D') {
		system("cls");
		cout << "<==========================================================> " << endl;
		cout << "                         Customer Mode      " << endl;
		cout << "<==========================================================>" << endl;
		cout << "                    Your Money. Your Control.   " << endl;
		cout << "<==========================================================>" << endl;
		cout << "\n";
		cout << "\n";
		cout << "<--------------------=  Login successful  =----------------->" << endl;

		cout << "<=============- Your Account is Deactivated -==============>\n\n\n" << endl;
		
		char choice = 0;
		
		
		do {
			cout << "<==========================================================>" << endl;
			cout << "                           Menu   " << endl;
			cout << "<==========================================================>" << endl;
			cout << "\n\n               <======= 1.Balance  =======>" << endl;
			cout << "               <======= 2.Logout  ========>" << endl;
			cout << "<==========================================================>" << endl;
			cout << "Choice: ";
			cin >> choice;
			switch (choice) {
			case '1':
				_balance(balance[index]);
				break;
			case'2':
				cout << "<==========================================================> " << endl;
				cout << "                            Exiting                   " << endl;
				cout << "<==========================================================> " << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				break;
				
			default:
				cout << "<==========================================================> " << endl;
				cout << "                       Invalid Choice!                   " << endl;
				cout << "<==========================================================> " << endl;
				
			}
		} while (choice!='2');


	}
	else {
		system("cls");
		cout << "<==========================================================> " << endl;
		cout << "                         Customer Mode      " << endl;
		cout << "<==========================================================>" << endl;
		cout << "                    Your Money. Your Control.   " << endl;
		cout << "<==========================================================>" << endl;
		cout << "\n";
		cout << "\n";
		cout << "<--------------------=  Login successful  =----------------->" << endl;

		char choice = 0;
		do {

			cout << "                   1.  <===  WithDraw        ===>" << endl;
			cout << "                   2.  <===  Balance         ===>" << endl;
			cout << "                   3.  <===  Deposit         ===>" << endl;
			cout << "                   4.  <===  Transfer        ===>" << endl;
			cout << "                   5.  <===  Mini statement  ===>" << endl;
			cout << "                   6.  <===  Change password ===>" << endl;
			cout << "                   9.  <===  Logout          ===>" << endl;
			cout << "Choice: ";
			cin >> choice;
			switch (choice) {
			case '1':
				withdraw(balance[index], account, passkey, balance, status, failed_A, locked, capacity, index);
				break;
			case '2':
				_balance(balance[index]);
				break;
			case '3':
				deposit(balance[index], account, passkey, balance, status, failed_A, locked, capacity, index);
				break;
			case '4':
				flag = true;
				transfer(balance[index], account, capacity, balance, status, failed_A, locked, passkey, index, flag);
				if (flag == false) {
					cout << "<================== The Account Is Closed =============>\n\n\n" << endl;

					break;
				}
				break;
			case '9':
				cout << "<==========================================================> " << endl;
				cout << "                            Exiting                   " << endl;
				cout << "<==========================================================> " << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				break;
			case '6':
				password_change(passkey[index], account, passkey, balance, status, failed_A, locked, capacity);
				break;
			case '5':
				display_mini_statement(account[index]);
				break;
			default:
				system("cls");
				cout << "Invalid choice" << endl;
			}

		} while (choice != '9');





	}

	return 0;
}
long long manager() {
	cout << "<=========================================>" << endl;
	cout << "                Manager Mode    " << endl;
	cout << "<=========================================>" << endl;
	cout << "         Navigate. Control. Succeed.      " << endl;
	cout << "<=========================================>" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	file_to_array(account1, passk, balance, status, failed_A, locked, capacity);  //file sai arrray;
	long long p = 0;
	ifstream rdr("Admin.txt");
	rdr >> p;
	long long realpin = decrypt_pin(p);
	long long pin = pin_masked();
	if (realpin != pin) {
		cout << "Enter Valid pin" << endl;
		manager();

	}

	system("cls");
	cout << "              <=========================================>" << endl;
	cout << "                               Manager Mode    " << endl;
	cout << "              <=========================================>" << endl;
	cout << "                          Navigate. Control. Succeed.      " << endl;
	cout << "              <=========================================>" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "<===========================  login succesful ===============================>" << endl;





	bool flag = false;
	char choice;
	do {
		cout << "                   1.  <===  Open account        ===>" << endl;
		cout << "                   2.  <===  Close account       ===>" << endl;
		cout << "                   3.  <===  Deactivate/Activate ===>" << endl;
		cout << "                   4.  <===  Search Account      ===>" << endl;
		cout << "                   5.  <===  Display All Account ===>" << endl;
		cout << "                   6.  <===  Unlock Account      ===>" << endl;
		cout << "                   9.  <===  Logout              ===>" << endl;
		cout << "Choice: ";	cin >> choice;
		switch (choice) {
		case'1':
			system("cls");
			newaccount();
			break;
		case '2':
			
			system("cls");
			close();
			

			break;
		case '3':

			system("cls");
			deactivate();
			break;
		case'4':
			system("cls");
			account_display();
			break;
		case '5':
			system("cls");
			account_displayall();
			break;
		case '6':
			system("cls");
			unlock();
			break;
		case '9':
			cout << "              <=========================================>" << endl;
			cout << "                               Exiting   " << endl;
			cout << "              <=========================================>" << endl;
			
			break;
		default:
			cout << " <============== Invalid Choice  ============>" << endl;
			break;
		}



	} while (choice != '9');
	return 0;

}
void login(long long array[], long long passkey[], long long capacity, bool& flag, long long& index, char status[], bool& flag1, bool& flag2) {
	long long account = 0;
	long long passk = 0;
	long long count = 0;
	cout << "Enter Account Number: ";
	cin >> account;
	index = linear_search(array, account, capacity);
	if (index == -1) {
		cout << "<================== No Such Account Exists! ===================>" << endl;
		login(array, passkey, capacity, flag, index, status, flag1, flag2);

	}
	if (status[index] == 'C') {
		cout << "<================== Your Account is Closed ===================>" << endl;
		flag1 = true;
		return;

	}
	if (status[index] == 'L') {
		cout << "<================== Your Account is Locked ===================>" << endl;
		flag1 = 1;
		return;

	}

	else {
		do {

			cout << "<------------Attempt Remaining : " << 3 - count << " ---------->" << endl;

			passk = pin_masked();

			if (passkey[index] == passk) {

				flag = true;
				break;

			}
			count++;
		} while (count < 3);
	}
}