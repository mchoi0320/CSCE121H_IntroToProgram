#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
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

int main()
{
	cout << "> ";
	string line;
	getline(cin, line);

	while (line != "quit") {
		vector<string> inputs = get_input(line);

		if (inputs.size() == 1) {
			Poly poly(inputs[0]);
			poly.print(); }

		if (inputs.size() == 2) {
			Poly poly(inputs[1]);

			if (inputs[0] == "deriv") {
				Poly derivative(poly.derive());
				cout << "DERIV" << endl;
				cout << "P     = "; poly.print();
				cout << "dP/dx = "; derivative.print(); }

			if (inputs[0] == "root") {
				float root = poly.root();
				cout << "ROOT" << endl;
				cout << "P = "; poly.print();
				cout << "root(P)=r=" << root << ", P(r)=" << poly.eval(root) << endl; } }
				
		if (inputs.size() == 3) {
			Poly poly1(inputs[1]);
			Poly poly2(inputs[2]);
			
			if (inputs[0] == "sum") {
				Poly sum(poly1.add(poly2));
				cout << "SUM" << endl;
				cout << "P   = "; poly1.print();
				cout << "Q   = "; poly2.print();
				cout << "P+Q = "; sum.print(); }
			
			if (inputs[0] == "prod") {
				Poly product(poly1.multiply(poly2));
				cout << "PROD" << endl;
				cout << "P   = "; poly1.print();
				cout << "Q   = "; poly2.print();
				cout << "P*Q = "; product.print(); } }

		cout << "\n> ";
		getline(cin, line); }
}
