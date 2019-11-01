#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include "print_vec.hpp"
#include "poly_class.hpp"
using namespace std;

vector<string> get_input(string line)
{
	vector<string> inputs;
	istringstream ss(line);
	string input;
	while (ss >> input) {
		inputs.push_back(input); }

	return inputs;
}

vector<string> separate_terms(string polynomial)
{
	vector<string> terms;
	string term;

	int term_start=0;
	for (int i=0; i<polynomial.size(); i++) {
		if ((polynomial[i] == '+' || polynomial[i] == '-') && i != 0) {
			term = polynomial.substr(term_start, i-term_start);
			terms.push_back(term);
			term_start = i; } }
	string last_term = polynomial.substr(term_start, polynomial.size()-term_start);
	terms.push_back(last_term);

	if (terms[0].find('+') && terms[0].find('-') == string::npos) {
		terms[0] = '+' + terms[0]; }

	return terms;
}

struct TERM {
	char sign;
	float coefficient;
	int exponent;
};

float get_coefficient(string term)
{
	char variable = 'x';
	int variable_pos = term.find(variable);

	if (variable_pos == 1) return 1;
	else {
		string coefficient_str = term.substr(1, variable_pos-1);
		float coefficient = stof(coefficient_str);
		return coefficient; }
}

int get_exponent(string term)
{
	if (term.find('^') == string::npos) return 1;
	else {
		int exponent_pos = term.find('^') + 1;
		string exponent_str = term.substr(exponent_pos, term.size());
		int exponent = stoi(exponent_str);
		return exponent; }
}

vector<TERM> get_term_components(vector<string> terms)
{
	vector<TERM> terms_components;
}

int main()
{
	cout << "> ";
	string line;
	getline(cin, line);

	while (line != "quit") {
		vector<string> inputs = get_input(line);

		if (inputs.size() == 1) {
			print_vec_str(inputs); }

		if (inputs.size() == 2) {
			//code for deriv and root
			vector<string> terms = separate_terms(inputs[1]);
			//print_vec_str(terms);
			//cout << get_coefficient(terms[0]) << endl;
			//cout << get_exponent(terms[0]) << endl;
			}
		if (inputs.size() == 3) {
			vector<string> terms_poly1 = separate_terms(inputs[1]);
			vector<string> terms_poly2 = separate_terms(inputs[2]);
			//print_vec_str(terms_poly1);
			//print_vec_str(terms_poly2);
			}

		cout << "\n> ";
		getline(cin, line); }
}
