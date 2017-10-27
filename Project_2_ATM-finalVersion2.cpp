#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
using namespace std;

const int SIZE = 10;
string inp_account;
char firstChar,c;
double value;
int position;
double balance[SIZE];
string accounts [SIZE] = { "C1234567", "C1234568", "C1234569", "C1234560", "C1234561", 
	"S1234567", "S1234568", "S1234569", "S1234560", "S1234561" };  

// randomly assigns values to 10 elements of array "balance"
void randomMoney(){
	int seed = time(0);
	srand(seed);
	const int minValue = 300;							

	for (int x = 0; x <SIZE;x++) {
		balance[x] = (rand()/ (RAND_MAX/ 1000.0))+ minValue;
	}
}

// takes user input and validates input is not a char or less then 0.
int validateInput(){
	while(!(cin >> value)|| value < 0){
		cin.clear();
		while(cin.get() != '\n')
			continue;
		cout << "\nThis is not a valid amount, please try again: $";
	}
	cin.ignore (80,'\n');  cin.clear();
	return value;
}

// verifies user account exist by comparing user input to existing string array, converts first letter to upper case if needed
int verifyAccount (){
	cout << "\nPlease enter your account number: ";
	firstChar=cin.get();
	c=toupper(firstChar);
	cin.putback(c);
	cin>>inp_account;

	for(int i = 0; i < SIZE; i++){
		if(accounts[i].compare(inp_account) == 0 )
			return i ;      // will return the index of the account in the array if the account number exist.
	}	
	return -1 ; // the function will return -1 if the account does not exist.
}

// validates that a value of -1 is not returned to array index position
int validPosition(){
	position = verifyAccount();

	while (position == -1) 	{
		cout << "\nThis is not a valid account number: ";
		cin.ignore(80,'\n'); cin.clear();
		position = verifyAccount();
	}	
	return position ;
}

// takes an index of array and displays its value  
void showBalance(int index) {
	cout << "\nThe new balance is $" << fixed << showpoint <<setprecision(2) << balance [index];
}

// if user deposits 0 the program will end or value will be added to the amount in the designated position.
void deposit (){
	cout <<  "=========================================================\n" << endl 
		<<	"\t*************DEPOSIT*****************\n" << endl
		<<  "=========================================================\n\n";
	validPosition(); {
		cout << "\nEnter the amount you want to deposit: $";
		validateInput();
		if (value == 0){
			exit(0);
		}
		else {balance [position] += value;
		showBalance(position);
		cout << endl << endl;
		}
	}		
}

// calls other functions to display account balances
void verifyBalance (){
	cout <<  "=========================================================\n" << endl
		<<	"\t************CHECK BALANCE***********\n" << endl
		<<  "=========================================================\n\n";
	validPosition();
	showBalance(position);
	cout << endl << endl;
}

// returns if funds are not available or deducts value from given index position in array "balance".
void withdrawal(){
	cout <<  "=========================================================\n" << endl
		<<	"\t************WITHDRAWAL***************\n" << endl
		<<  "=========================================================\n\n";	
	validPosition();	

	while(true){
		cout <<  "\n\nEnter the amount you want to withdraw: $";
		validateInput();
		if(balance[position] < value ){
			cout << "\nThere are not enough funds available in this account for this transaction.\n";
		}
		else{
			balance [position] -= value;
			showBalance(position);
			cout << endl << endl;
			break;
		}
	}
}

// moves amount from savings to checkings or checkings to savings 
void transfer () {
	cout <<  "=========================================================\n" << endl
		<<	"\t*************TRANSFER****************\n" << endl
		<<  "=========================================================\n\n";	
	validPosition();
	if (position >= 5){   // to transfer from saving to cheking accounts
		while(true){
			cout << "\n\nEnter the amount you are withdrawing: $";
			validateInput();
			if(balance[position] < value ){
				cout << "\nThere are not enough funds available in this account for this transaction.\n";
			}
			else{	
				balance[position] -= value;
				showBalance(position);
				cout << " in your Savings Account.\n\n";
				balance[position-5] += value;
				int positionAdjust = position - 5;
				showBalance(positionAdjust);
				cout << " in your Checking Account.\n\n";
				break;
			}
		}
	}
	else{
		while(true){     //to transfer from checking to saving accounts
			cout << "\n\nEnter the amount you are withdrawing: $";
			validateInput();
			if(balance[position] < value ){
				cout << "\nThere are not enough funds available in this account for this transaction.\n";
			}
			else{
				balance[position] -= value;
				showBalance(position);
				cout << " in your Checking Account.\n\n";
				balance[position+5] += value;
				int positionAdjust = position + 5;
				showBalance(positionAdjust);
				cout << " in your Savings Account.\n\n";
				break;
			}
		}
	}
}

int main () {
	randomMoney();  // automatically assigning balances for account numbers, called just once per running of program 
	int mainMenu; 
	
	do{	
		
		// opening menu 
		cout <<  "\n\n=========================================================\n" << endl
			<<  " \tWelcome to SAAT's Banking ATM Machine\n" << endl 
			<<  "=========================================================\n\n";

		cout << "How can I help you today?\n" << endl
			<< "	1) Make a Deposit" << endl
			<< "	2) See your Account Balance" << endl
			<< "	3) Make a Withdrawal  " << endl
			<< "	4) Transfer" << endl
			<< "	5) Exit\n" << endl;

		// gets choice and validates for bad input and choice range
		while( !(cin >> mainMenu) ){
			cin.clear();
			while(cin.get() != '\n')
				continue;
			cout << " Choose a number corresponding to a transaction: ";
		} 
		cin.ignore(80,'\n'); cin.clear();

		switch (mainMenu){
		case 1 : deposit(); break;
		case 2 : verifyBalance(); break;
		case 3 : withdrawal(); break;
		case 4 : transfer(); break;
		case 5 : system ("cls"); break;
		default: cout << " Choose a number corresponding to a transaction: \n\n\n";
		}
	}while (true & mainMenu != 5);
	
	if (mainMenu == 5){
		cout << "Thank you for banking with us!\n";
		system("pause");
	}
	
	return 0;
}
