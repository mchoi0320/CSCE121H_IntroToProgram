#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main(int argc, char** argv)
{
	int month = atoi(argv[1]); int year = atoi(argv[2]);

	vector<string> monthName;
		monthName.push_back("January"); monthName.push_back("February");
		monthName.push_back("March"); monthName.push_back("April");
		monthName.push_back("May"); monthName.push_back("June");
		monthName.push_back("July"); monthName.push_back("August");
		monthName.push_back("September"); monthName.push_back("October");
		monthName.push_back("November"); monthName.push_back("December");

	// January 1st, 0001 = Monday
	int yearsPassed = year-1;
	int dayWeekJan = ((yearsPassed * 365)+(yearsPassed / 4)-(yearsPassed / 100)+(yearsPassed / 400)+1) % 7; // Determines the first day of a given year

	vector<string> dayWeek;
		dayWeek.push_back("Sun"); dayWeek.push_back("Mon");
		dayWeek.push_back("Tue"); dayWeek.push_back("Wed");
		dayWeek.push_back("Thu"); dayWeek.push_back("Fri");
		dayWeek.push_back("Sat");

	bool leapYear;
	if (year % 100 == 0 && year % 400 != 0) {
		leapYear = false; }
	else if (year % 4 == 0 || year % 400 == 0) {
		leapYear = true; }
	else {
		leapYear = false; }

	int numDays;
	if (month == 1) {
		numDays = 31; }
	if (month == 2) {
		if (leapYear == true) {
			numDays = 29; }
		else {
			numDays = 28; } }
	if (month == 3) {
		numDays = 31; }
	if (month == 4) {
		numDays = 30; }
	if (month == 5) {
		numDays = 31; }
	if (month == 6) {
		numDays = 30; }
	if (month == 7) {
		numDays = 31; }
	if (month == 8) {
		numDays = 31; }
	if (month == 9) {
		numDays = 30; }
	if (month == 10) {
		numDays = 31; }
	if (month == 11) {
		numDays = 30; }
	if (month == 12) {
		numDays = 31; }

	vector<int> daysInMonths;
		daysInMonths.push_back(31);
		if (leapYear == true) {
			daysInMonths.push_back(29); }
		else {
			daysInMonths.push_back(28); }
		daysInMonths.push_back(31); daysInMonths.push_back(30);
		daysInMonths.push_back(31); daysInMonths.push_back(30);
		daysInMonths.push_back(31); daysInMonths.push_back(31);
		daysInMonths.push_back(30); daysInMonths.push_back(31);
		daysInMonths.push_back(30); daysInMonths.push_back(31);

	// Determining the first day of the input month
	int i, firstDay = dayWeekJan;
	for (i=0 ; i<month-1 ; i++) {
		firstDay += daysInMonths.at(i); }
	firstDay = firstDay % 7;

	cout << "\nCalendar for " << monthName.at(month-1) << " " << year << endl;
	cout << " ___________________________" << endl;
	cout << "|Sun|Mon|Tue|Wed|Thu|Fri|Sat|" << endl;
	cout << "|---------------------------|" << endl;

	/*
	int a, b, c;
	for (a=0 ; a<5 ; a++) {
		for (b=0 ; b<2 ; b++) {
			cout << "|";
			for (c=0 ; c<7 ; c++) {
				cout << setw(4) << "|"; }
			cout << endl; }
		cout << "|---------------------------|" << endl; }
	*/

	int a, b, c, d, e, f, g, h, k, m;
	cout << "|";
	for (a=0 ; a<firstDay ; a++) {
		cout << setw(4) << "|"; }
	//////////////
	if (month == 7) {
		for (b=1 ; b<8-firstDay ; b++) {
			if (b == 4) {
				cout << setw(3) << "*4" << "|"; }
			else {
				cout << setw(3) << b << "|"; } } }
	else {
		for (b=1 ; b<8-firstDay ; b++) {
			cout << setw(3) << b << "|"; } }
	cout << "\n|";
	for (c=0 ; c<7 ; c++) {
		cout << setw(4) << "|"; }
	cout << "\n|---------------------------|" << endl;
	//////////////
	cout << "|";
	if (month == 7) {
		for (d=b ; d<b+7 ; d++) {
			if (d == 4) {
				cout << setw(3) << "*4" << "|"; }
			else {
				cout << setw(3) << d << "|"; } } }
	else {
		for (d=b ; d<b+7 ; d++) {
			cout << setw(3) << d << "|"; } }
	cout << "\n|";
	for (c=0 ; c<7 ; c++) {
		cout << setw(4) << "|"; }
	cout << "\n|---------------------------|" << endl;
	//////////////
	cout << "|";
	for (e=d ; e<d+7 ; e++) {
		cout << setw(3) << e << "|"; }
	cout << "\n|";
	for (c=0 ; c<7 ; c++) {
		cout << setw(4) << "|"; }
	cout << "\n|---------------------------|" << endl;
	//////////////
	cout << "|";
	if (month == 12) {
		for (f=e ; f<e+7 ; f++) {
			if (f == 25) {
				cout << setw(3) << "*25" << "|"; }
			else {
				cout << setw(3) << f << "|"; } } }
	else {
		for (f=e ; f<e+7 ; f++) {
			cout << setw(3) << f << "|"; } }
	cout << "\n|";
	for (c=0 ; c<7 ; c++) {
		cout << setw(4) << "|"; }
	cout << "\n|---------------------------|" << endl;
	//////////////
	int numDaysRem = numDays - (f-1); int j=0;
	if (numDaysRem >= 7) {
		cout << "|";
		if (month == 10) {
			for (g=f ; g<f+numDaysRem-(numDaysRem%7) ; g++) {
				//cout << g << endl;
				if (g == 31) {
					cout << setw(3) << "*31" << "|"; }
				else {
			cout << setw(3) << g << "|"; }
				j += 1; } }
		else if (month == 12) {
			for (g=f ; g<f+numDaysRem-(numDaysRem%7) ; g++) {
				if (g == 25) {
					cout << setw(3) << "*25" << "|"; }
				else {
					cout << setw(3) << g << "|"; }
				j += 1; } }
		else {
			for (g=f ; g<f+numDaysRem-(numDaysRem%7) ; g++) {
				cout << setw(3) << g << "|";
				j += 1; } }
		for (h=0 ; h<7-j ; h++) {
			cout << setw(4) << "|"; }
		cout << "\n|";
		for (c=0 ; c<7 ; c++) {
			cout << setw(4) << "|"; } 
		cout << "\n|---------------------------|" << endl; }
	else {
		cout << "|";
		for (g=f ; g<f+numDaysRem ; g++) {
			cout << setw(3) << g << "|";
			j += 1; }
		for (h=0 ; h<7-j ; h++) {
			cout << setw(4) << "|"; }
		cout << "\n|";
		for (c=0 ; c<7 ; c++) {
			cout << setw(4) << "|"; }
		cout << "\n|---------------------------|" << endl; }
	///////////;
	numDaysRem -= 7; int l=0;
	if (numDaysRem > 0) {
		cout << "|";
		if (month == 10) {
			for (k=g ; k<g+numDaysRem ; k++) {
				if (k == 31) {
					cout << setw(3) << "*31" << "|"; }
				else {
					cout << setw(3) << k << "|"; }
				l += 1; } }
		else {
			for (k=g ; k<g+numDaysRem ; k++) {
				cout << setw(3) << k << "|";
				l += 1; } }
		for (m=0 ; m<7-l ; m++) {
			cout << setw(4) << "|"; }
		cout << "\n|";
		for (c=0 ; c<7 ; c++) {
			cout << setw(4) << "|"; }
		cout << "\n|---------------------------|" << endl; }
}
