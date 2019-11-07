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
	string sign;
	float coefficient;
	int exponent;
};

float get_coefficient(string term)
{
	char variable = 'x';
	int variable_pos = term.find(variable);

	if (variable_pos == 1) {
        if (term[0] == '+') return 1;
        if (term[0] == '-') return -1; }
	else {
		string coefficient_str = term.substr(1, variable_pos-1);
		float coefficient = stof(coefficient_str);
        if (term[0] == '+') return coefficient;
        if (term[0] == '-') return -coefficient; }
}

int get_exponent(string term)
{
    if (term.find('x') == string::npos) return 0;
	else if (term.find('^') == string::npos) return 1;
	else {
		int exponent_pos = term.find('^') + 1;
		string exponent_str = term.substr(exponent_pos, term.size());
		int exponent = stoi(exponent_str);
		return exponent; }
}

vector<TERM> get_term_components(vector<string> terms)
{
	vector<TERM> terms_components;
	string sign; float coefficient; int exponent;

	for (int i=0; i<terms.size(); i++) {
		sign = terms[i].substr(0, 1);
		/*
		if (terms[i].find('x') == string::npos) {
			coefficient = stof(terms[i].substr(1, terms[i].size())); }
		else {
			int variable_pos = terms[i].find('x');
			coefficient = stof(terms[i].substr(1, variable_pos-1));
			exponent = stoi(terms[i].substr(variable_pos+2, terms[i].size())); }
		*/
        coefficient = get_coefficient(terms[i]);
        exponent = get_exponent(terms[i]);

		terms_components.push_back({});
		terms_components[i].sign = sign;
		terms_components[i].coefficient = coefficient;
		terms_components[i].exponent = exponent; }

	return terms_components;
}

vector<TERM> add_poly(vector<TERM> poly1, vector<TERM> poly2)
{
    vector<TERM> sum;

    int i=0;
    while (!poly1.empty() && !poly2.empty()) {
		//cout << i << endl;
        if (poly1.front().exponent == poly2.front().exponent) {
            float sum_coeff = poly1.front().coefficient + poly2.front().coefficient;
            if (sum_coeff != 0) {
				//cout << "loop" << endl;
				sum.push_back({});
				sum[i].coefficient = sum_coeff;
				//cout << sum[i].coefficient << endl;
				sum[i].exponent = poly1.front().exponent;
				//cout << sum[i].exponent << endl;
				}
			//cout << sum.size() << endl;
            poly1.erase(poly1.begin()); poly2.erase(poly2.begin()); }
        else {
			sum.push_back({});
            if (poly1.front().exponent > poly2.front().exponent) {
                sum[i].coefficient = poly1.front().coefficient;
                sum[i].exponent = poly1.front().exponent;
                poly1.erase(poly1.begin()); }
            if (poly2.front().exponent > poly1.front().exponent) {
                sum[i].coefficient = poly2.front().coefficient;
                sum[i].exponent = poly2.front().exponent;
                poly2.erase(poly2.begin()); } }
        i++; }
		//cout << sum[0].coefficient << ' ' << sum[0].exponent << endl;

    return sum;
}

vector<TERM> multiply_poly(vector<TERM> poly1, vector<TERM> poly2)
{
	vector<TERM> product;
/*
	if (poly1.size() < poly2.size()) {
		vector<TERM> temp = poly1;
		poly1 = poly2;
		poly2 = temp; }
*/	
	float prod_coeff; int prod_exp;
	int a = 0;
	for (int i=0; i<poly1.size(); i++) {
		for (int j=0; j<poly2.size(); j++) {
			prod_coeff = poly1[i].coefficient * poly2[j].coefficient;
			prod_exp = poly1[i].exponent + poly2[j].exponent;
			product.push_back({});
			product[a].coefficient = prod_coeff;
			product[a].exponent = prod_exp;
			a++; } }

	return product;
}

vector<TERM> derive_poly(vector<TERM> poly)
{
	vector<TERM> derivative;

	float deriv_coeff; int deriv_exp;
	for (int i=0; i<poly.size(); i++) {
		deriv_coeff = poly[i].coefficient * poly[i].exponent;
		deriv_exp = poly[i].exponent - 1;
		if (deriv_coeff != 0) {
			derivative.push_back({});
			derivative[i].coefficient = deriv_coeff;
			derivative[i].exponent = deriv_exp; } }

	if (derivative.empty()) {
		derivative.push_back({});
		derivative[0].coefficient = 0; }

	return derivative;
}

void print_polynomial(vector<TERM> poly)
{
	//cout << poly.size() << endl;
    for (int i=0; i<poly.size(); i++) {
		//if (poly[i].coefficient == 0);
        if (poly[i].exponent == 0) {
            if (poly[i].coefficient < 0) {
                cout << poly[i].coefficient; }
            else {
				if (i == 0) cout << poly[i].coefficient;
                else cout << '+' << poly[i].coefficient; } }
        else if (poly[i].exponent == 1) {
            if (poly[i].coefficient < 0) {
				if (poly[i].coefficient == -1) cout << "-x";
                else cout << poly[i].coefficient << 'x'; }
            else {
				if (poly[i].coefficient == 1) {
					if (i == 0) cout << 'x';
					else cout << "+x"; }
				else if (i == 0) cout << poly[i].coefficient << 'x';
                else cout << '+' << poly[i].coefficient << 'x'; } }
        else {
            if (poly[i].coefficient < 0) {
                if (poly[i].coefficient == -1) cout << "-x^";
				else cout << poly[i].coefficient << "x^" << poly[i].exponent; }
            else {
                if (poly[i].coefficient == 1) {
					if (i == 0) cout << "x^" << poly[i].exponent;
					else cout << "+x^" << poly[i].exponent; }
				else if (i == 0) cout << poly[i].coefficient << "x^" << poly[i].exponent;
				else cout << '+' << poly[i].coefficient << "x^" << poly[i].exponent; } } }
    cout << endl;
}

int main()
{
	cout << "> ";
	string line;
	getline(cin, line);

	while (line != "quit") {
		//Poly poly_operation;
		vector<string> inputs = get_input(line);

		if (inputs.size() == 1) {
			print_vec_str(inputs); }

		if (inputs.size() == 2) {
			vector<string> temp = separate_terms(inputs[1]);
			vector<TERM> terms = get_term_components(temp);

			if (inputs[0] == "deriv") {
				vector<TERM> deriv = derive_poly(terms);
				print_polynomial(deriv); }

			if (inputs[0] == "root") {
				cout << "Not yet implemented" << endl; }

			//for (int i=0; i<terms.size(); i++) {
            //    cout << terms[i].coefficient << ' ' << terms[i].exponent << endl; }
            //print_polynomial(terms);
		}
		if (inputs.size() == 3) {
			vector<string> temp_poly1 = separate_terms(inputs[1]);
			vector<string> temp_poly2 = separate_terms(inputs[2]);
            vector<TERM> terms_poly1 = get_term_components(temp_poly1);
            vector<TERM> terms_poly2 = get_term_components(temp_poly2);

			if (inputs[0] == "sum") {
				vector<TERM> sum = add_poly(terms_poly1, terms_poly2);
            	print_polynomial(sum); }
			
			if (inputs[0] == "prod") {
				vector<TERM> prod = multiply_poly(terms_poly1, terms_poly2);
				print_polynomial(prod); }
		
			//for (int i=0; i<sum.size(); i++) {
            //    cout << sum[i].coefficient << ' ' << sum[i].exponent << endl; }
		}

		cout << "\n> ";
		getline(cin, line); }
}
