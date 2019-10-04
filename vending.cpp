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

double getChange(double n)
{
	if (n-0.25>=-0.01) {
		return 0.25; }
	else if (n-0.10>=-0.01) {
		return 0.10; }
	else {
		return 0.05; }
}


int main(int argc, char** argv)
{
	if (argc<2) {
		cout << "Please enter a file name." << endl;
		exit(0); }
	
	ifstream file;
	file.open(argv[1]);

	//vector<string> coins; vector<int> coinsCnt; vector<double> coinsVal;
	//vector<string> items; vector<int> itemsCnt; vector<double> itemsVal;
	string fileInput;
	vector<string> contents;
	while (file >> fileInput) {
		contents.push_back(fileInput); }

	/*for (int i=0; i<contents.size(); i++) {
		cout << contents.at(i) << " "; }
	cout << endl;*/

	cout << "\nWelcome to Choi Vending!" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Please enter your coins." << endl;
	cout << "Once finished, enter \"press _____\" with your desired item." << endl;
	cout << "If you would like change, enter \"change\" at any time." << endl;
	cout << "Enter \"quit\" to exit." << endl;
	cout << "----------------------------------------------------------" << endl;

	/* cout << setw(15) << "\nItems" << setw(15) << "Prices" << endl;
	for (int i=0; i<contents.size(); i++) {
		cout << setw(15) << contents.at(i) } */

	double balance=0;
	//vector<string> inputVals;

	cout << fixed << setprecision(2);

	//string input;

	cout << "Balance: $" << balance << endl; cout << endl;
	cout << ">> "; //cin >> input;
	
	/*getline(cin,input);
	if (input.find("press")) {
		cout << "coins and item" << endl;
		cout << input.find("press") << endl;
		//int i;
		//for (i=0; i<; i++) {
			 } //}
	else {
		cout << "just coins" << endl; }
*/
	string input; string indivInput;

/*	getline(cin, input);
	istringstream ss(input);
	while (ss >> indivInput) {
		cout << indivInput << endl; */
		
		/*if (indivInput == ("quarter" || "dime" || "nickel") {
			coins.push_back(indivInput); } } */

	//cin >> input;
	/* while (getline(cin, input)) {
		vector<string> inputs;
		giveInput(inputs, input);
	//printVector_str(inputs);
	//istringstream ss(input);
	//while (ss >> indivInput) {
		//cout << indivInput << endl;
		for (int i=0; i<inputs.size(); i++) {
			string currentInput = inputs.at(i);
			while (currentInput != "quit") {
				if (currentInput == "quarter") {
					balance += 0.25; }
				else if (currentInput == "dime") {
					balance += 0.10; }
				else if (currentInput == "nickel") {
					balance += 0.05; }
		//	else {
		//		cout << "Uh oh! Please enter a valid coin or command." << endl; } }
		//cout << "Balance: $" << balance << endl; cout << endl;
		//cout << ">> "; cin >> input; }
				else if (currentInput == "change") {
					double changeGiven; double remBalance=balance;
					vector<string> change;
					while (remBalance > 0.01) {
						changeGiven = getChange(remBalance);
						if (changeGiven == 0.25) {
							change.push_back("quarter"); }
						else if (changeGiven == 0.10) {
							change.push_back("dime"); }
						else {
							change.push_back("nickel"); }
					remBalance -= changeGiven;
					balance = 0;
					cout << remBalance << endl; }
					for (int i=0; i<change.size(); i++){
						cout << change.at(i) << " "; }
					cout << endl; }
				else if (currentInput == "press") {
					cout << "Nothing done yet" << endl; }
				else {
					cout << "Uh oh! Please enter a valid coin or command." << endl; } }
		//istringstream ss(input); }
			cout << "Balance: $" << balance << endl; cout << endl;
			cout << ">> "; //cin >> indivInput; 
		//ss.clear();
			getline(cin, input);
			//ss >> indivInput;
			vector<string> inputs;
			giveInput(inputs, input); } } */

	//cout << input << endl;*/
	
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
			/* if (currentInput == "quarter") {
				balance += 0.25; }
			else if (currentInput == "dime") {
				balance += 0.10; }
			else if (currentInput == "nickel") {
				balance += 0.05; } */
			else if (currentInput == "change") {
				if (balance < 0.05) cout << "No outstanding balance." << endl;
				else {
					double changeGiven; double remBalance=balance;
					vector<string> change;
					string changeIs;
					while (remBalance > 0.01) {
						changeGiven = getChange(remBalance);
						if (changeGiven == 0.25) changeIs = "quarter";
						else if (changeGiven == 0.10) changeIs = "dime";
						else changeIs = "nickel";
						change.push_back(changeIs);
						remBalance -= changeGiven; }
						/* if (changeGiven == 0.25) {
							change.push_back("quarter"); }
						else if (changeGiven == 0.10) {
							change.push_back("dime"); }
						else {
							change.push_back("nickel"); }
						remBalance -= changeGiven; } */
						/* int itemPos = itemPosition(contents, changeIs);
						int itemNum = numItems(contents, itemPos);
						if (itemNum > 0) {
							itemNum--;
							updateContents(contents, itemPos+1, to_string(itemNum));
							if (changeGiven == 0.25) {
								change.push_back("quarter"); }
							else if (changeGiven == 0.10) {
								change.push_back("dime"); }
							else {
								change.push_back("nickel"); } }
						else {
							cout << "insufficient change" << endl;
							changeGiven = getChange(remBalance);
							if (changeIs == "quarter") {
								if (n-0.10>=-0.01) {
									change.push_back("dime"); }
								else {
									change.push_back("nickel"); } }
							else if (changeIs == "dime") {
								if (n-0.05>=-0.01) {
									change.push_back("nickel"); } }
							}
						remBalance -= changeGiven; } */
					balance = 0;
					for (int i=0; i<change.size(); i++) {
						/* int itemPos = itemPosition(contents, change.at(i));
						int itemNum = numItems(contents, itemPos); 
						if (itemNum > 0) {
							itemNum--;
							updateContents(contents, itemPos+1, to_string(itemNum); } */
						cout << change.at(i) << " "; } }
				cout << endl; }
			else if (currentInput == "press") {
				string item = inputs.at(i+1);
				if (item == "quarter" || item == "dime" || item == "nickel") {
					cout << "Please choose a valid item." << endl; }
				else {
					int itemPos = itemPosition(contents, item);
					/* for (int i=0; i<contents.size(); i++) {
						if (contents.at(i) == item) itemPos = i; } */
					/* int itemNum = stoi(contents.at(itemPos+1)); */
					int itemNum = numItems(contents, itemPos);
					float itemVal = stof(contents.at(itemPos+2));				
					if (itemNum > 0 && balance >= itemVal) {
						cout << "Dispensed " << item << '.' << endl;
						balance -= itemVal;
						itemNum--; /* contents.at(itemPos+1) = to_string(itemNum); */ updateContents(contents, itemPos+1, to_string(itemNum)); }
					else if (balance < itemVal) {
						cout << "Not enough balance." << endl; }
					else if (itemNum == 0) {
						cout << item << " is out of stock." << endl; } } }
			else {
				if (i > 0 && inputs.at(i-1) == "press") continue;
				else {
					cout << "Uh oh! Please enter a valid coin or command." << endl; } } }
		cout << "Balance: $" << balance << endl; cout << endl;
		cout << ">> "; getline(cin, input); }

	/* cin >> input;		
	while (input != "quit") {
				if (input == "quarter") {
					balance += 0.25; }
				else if (input == "dime") {
					balance += 0.10; }
				else if (input == "nickel") {
					balance += 0.05; }
				if (input == "quarter" || input == "nickel" || input == "dime") {
					balance += addBalance(input); } */
		//	else {
		//		cout << "Uh oh! Please enter a valid coin or command." << endl; } }
		//cout << "Balance: $" << balance << endl; cout << endl;
		//cout << ">> "; cin >> input; }
				/* else if (input == "change") {
					if (balance < 0.05) cout << "No outstanding balance." << endl;
					else {
						double changeGiven; double remBalance=balance;
						vector<string> change;
						while (remBalance > 0.01) {
							changeGiven = getChange(remBalance);
							if (changeGiven == 0.25) {
								change.push_back("quarter"); }
							else if (changeGiven == 0.10) {
								change.push_back("dime"); }
							else {
								change.push_back("nickel"); }
						remBalance -= changeGiven;
						balance = 0; }
						for (int i=0; i<change.size(); i++){
							cout << change.at(i) << " "; }
					cout << endl; } }
				else if (input == "press") {
					cout << "Nothing done yet" << endl; }
				else if (input == "show") {
					cout << "Balance: $" << balance << endl; cout << endl; }
				else {
					cout << "Uh oh! Please enter a valid coin or command." << endl; }
		//istringstream ss(input); }
			cout << "Balance: $" << balance << endl; cout << endl;
			cout << ">> "; cin >> input; } */
}
