#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstdlib>
using namespace std;


void printVector_str(vector<string> vec)
{
	for (int i=0; i<vec.size(); i++) {
		cout << vec.at(i) << endl; }
}

int itemPosition(vector<string> vec, string n)
{
	int i, itemPos;
	for (i=0; i<vec.size(); i++) {
		if (vec.at(i) == n) itemPos = i; }
	return itemPos;
}

int numItems(vector<string> vec, int pos)
{
	return stoi(vec.at(pos+1));
}

void updateContents(vector<string> & contents, int pos, string n)
{
	contents.at(pos) = n;
}

double addBalance(string n)
{
	if (n == "quarter") {
		return 0.25; }
	else if (n == "dime") {
		return 0.10; }
	else {
		return 0.05; }
}

double getChange(double balance, vector<string> & contents, vector<string> & change)
{
	int posQuarter = itemPosition(contents, "quarter"); int numQuarters = numItems(contents, posQuarter);
	int posDime = itemPosition(contents, "dime"); int numDimes = numItems(contents, posDime);
	int posNickel = itemPosition(contents, "nickel"); int numNickels = numItems(contents, posNickel);
	
	double n = balance;
	
/* 	int a = 0;
	while(numQuarters > 0 && n - .25 >= 0)
	{
		change.push_back("quarter");
		n -= .25;
		a++;
		numQuarters--;
		cout << n << endl;
	}
	int b = 0;
	cout << numDimes << endl;
	while(numDimes > 0 && n - .10 >= 0)
	{
		change.push_back("dime");
		n -= .10;
		b++;
		numDimes--;
		cout << n << endl;
	}
	int c = 0;
	while(numNickels > 0 && n - .05 >= 0)
	{
		change.push_back("nickel");
		n -= .05;
		c++;
		numNickels;
		cout << n << endl;
	}

	cout << n << endl;

	if(n>0.001)
	{
		cout << "Insufficent change.\n";
	}
	else
	{
		cout << "[Returned: ";
		for(int i = 0; i<change.size()-1; i++)
		{
			cout << change[i] << " ";
		}
		cout << change[change.size()-1] << "]\n";
	}

	printVector_str(contents); */

	int numQChange = n / 0.25; int a=0;
	for (int i=0; i<numQChange; i++) {
		if (numQuarters > 0) {
			change.push_back("quarter");
			a++;
			/* numQuarters--; */ } }
	n -= 0.25 * a;
	int numDChange = n / 0.10; int b=0;
	for (int i=0; i<numDChange; i++) {
		if (numDimes > 0) {
			change.push_back("dime");
			b++;
			/* numDimes--; */ } } 
	n -= 0.10 * b;
	int numNChange = n / 0.05; int c=0;
	for (int i=0; i<numNChange; i++) {
		if (numNickels > 0) {
			change.push_back("nickel");
			c++;
			/* numNickels--; */ } } 
	n -= 0.05 * c;
	
	if (n > 0.001) {
		cout << "[Insufficient change in machine.]" << endl;
		return balance; }
	else {
		cout << "[Returned: ";
		for (int i=0; i<change.size()-1; i++) {
			cout << change.at(i) << ", "; }
		cout << change.at(change.size()-1) << ']' << endl;
		numQuarters -= a; updateContents(contents, posQuarter+1, to_string(numQuarters));
		numDimes -= b; updateContents(contents, posDime+1, to_string(numDimes));
		numNickels -= c; updateContents(contents, posNickel+1, to_string(numNickels));
		return 0; }
}


int main(int argc, char** argv)
{
	if (argc<2) {
		cout << "Please enter a file name." << endl;
		exit(0); }
	
	ifstream file;
	file.open(argv[1]);

	string fileInput;
	vector<string> contents;
	while (file >> fileInput) {
		contents.push_back(fileInput); }

	cout << "\nWelcome to Choi Vending!" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Please enter your coins." << endl;
	cout << "Once finished, enter \"press _____\" with your desired item." << endl;
	cout << "If you would like change, enter \"change\" at any time." << endl;
	cout << "Enter \"quit\" to exit." << endl;
	cout << "----------------------------------------------------------" << endl;

/* 	cout << setw(15) << "\nItems" << setw(15) << "Prices" << endl;
	for (int i=0; i<contents.size()/3; i++) {
		cout << setw(15) << contents.at(i) } */

	double balance=0;

	cout << fixed << setprecision(2);

	cout << "Balance: $" << balance << endl; cout << endl;
	cout << ">> "; 
	
	string input; string indivInput;
	
	getline(cin, input);
	while (input.find("quit") == string::npos) {
		vector<string> inputs;
		istringstream ss(input);
		while (ss >> indivInput) {
			inputs.push_back(indivInput); }
		for (int i=0; i<inputs.size(); i++) {
			string currentInput = inputs.at(i);
			if (currentInput == "quarter" || currentInput == "dime" || currentInput == "nickel") {
				if (i > 0 && inputs.at(i-1) == "press") {
					continue; }
				else {
					balance += addBalance(currentInput);
					int itemPos = itemPosition(contents, currentInput);
					int itemNum = numItems(contents, itemPos);
					itemNum++;
					updateContents(contents, itemPos+1, to_string(itemNum)); } }
			else if (currentInput == "change") {
				if (balance < 0.05) cout << "[No outstanding balance.]" << endl;
				else {
					vector<string> change;
					balance = getChange(balance, contents, change); } }
			else if (currentInput == "press") {
				string item = inputs.at(i+1);
				if (item == "quarter" || item == "dime" || item == "nickel") {
					cout << "[Please choose a valid item.]" << endl; }
				else {
					int itemPos = itemPosition(contents, item);
					int itemNum = numItems(contents, itemPos);
					float itemVal = stof(contents.at(itemPos+2));				
					if (itemNum > 0 && balance >= itemVal) {
						cout << "[Dispensed: " << item << ']' << endl;
						balance -= itemVal;
						itemNum--; updateContents(contents, itemPos+1, to_string(itemNum)); }
					else if (balance < itemVal) {
						cout << "[Not enough balance.]" << endl; }
					else if (itemNum == 0) {
						item[0] = toupper(item[0]);
						cout << '[' << item << " is out of stock.]" << endl; } } }
			else {
				if (i > 0 && inputs.at(i-1) == "press") continue;
				else {
					cout << "[Uh oh! Please enter a valid coin or command.]" << endl; } } }
		cout << "Balance: $" << balance << endl; cout << endl;
		cout << ">> "; getline(cin, input); }
		
	if (balance > 0) {
		vector<string> change;
		getChange(balance, contents, change);
		cout << "Balance: $" << balance << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "Don't forget your change. Thank you!" << endl; }
	else {
		cout << "----------------------------------------------------------" << endl;
		cout << "Thank you!" << endl; }
}
