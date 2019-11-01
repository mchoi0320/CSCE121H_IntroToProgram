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
	/*istringstream ss(polynomial);
	string term;
	while (getline(ss, term, '+')) {
		terms.push_back(term); }
*/
	char delim_plus = '+', delim_minus = '-';
	int term_start=0;
	for (int i=0; i<polynomial.size(); i++) {
		if (polynomial[i] == delim_plus || polynomial[i] == delim_minus) {
			term = polynomial.substr(term_start, i);
			terms.push_back(term);
			term_start = i; } }

	return terms;
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

		else {
			vector<string> terms = separate_terms(inputs[1]);
			print_vec_str(terms); }

		cout << "\n> ";
		getline(cin, line); }
}
