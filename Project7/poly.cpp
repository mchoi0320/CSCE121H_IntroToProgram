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

bool sort_by_deg(TERM a, TERM b) { return (a.exponent > b.exponent); }

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

vector<TERM> add_poly(vector<TERM> poly1, vector<TERM> poly2)
{
    vector<TERM> sum;

    /*int i=0;
    while (!poly1.empty() && !poly2.empty()) {
        if (poly1.front().exponent == poly2.front().exponent) {
            float sum_coeff = poly1.front().coefficient + poly2.front().coefficient;
            //if (sum_coeff != 0.0) {
				sum.push_back({});
				sum[i].coefficient = sum_coeff;
				sum[i].exponent = poly1.front().exponent; //}
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
        i++; }*/

	for (int i=0; i<poly1.size(); i++) {
		float new_coeff = poly1[i].coefficient;
		for (int j=0; j<poly2.size(); j++) {
			if (poly1[i].exponent == poly2[j].exponent) {
            	new_coeff += poly2[j].coefficient; } }
		TERM t;
		t.coefficient = new_coeff;
		t.exponent = poly1[i].exponent;
			sum.push_back(t); }

	for (int i=0; i<poly2.size(); i++) {
		bool search = true;
		for (int j=0; j<sum.size(); j++) {
			if (poly2[i].exponent == sum[j].exponent) {
				search = false;	} }
		if (search) {
			sum.push_back(poly2[i]); } }

	vector<TERM>::iterator iter = sum.begin();
	while (iter != sum.end()) {
		if (iter->coefficient == 0) {
			iter = sum.erase(iter); }
		else iter++; }

	sort(sum.begin(), sum.end(), sort_by_deg);

/*	while (!poly1.empty()) {
		sum.push_back(poly1[0]);
		poly1.erase(poly1.begin()); }

	while (!poly2.empty()) {
		sum.push_back(poly2[0]);
		poly2.erase(poly2.begin()); }

	if (sum.empty()) {
		sum.push_back({});
		sum[0].coefficient = 0; }*/

    return sum;
}

vector<TERM> multiply_poly(vector<TERM> poly1, vector<TERM> poly2)
{
	vector<vector<TERM> > product;
	float prod_coeff; int prod_exp;
	for (int i=0; i<poly1.size(); i++) {
		vector<TERM> temp_prod;
		for (int j=0; j<poly2.size(); j++) {
			prod_coeff = poly1[i].coefficient * poly2[j].coefficient;
			prod_exp = poly1[i].exponent + poly2[j].exponent;
			temp_prod.push_back({});
			temp_prod[j].coefficient = prod_coeff;
			temp_prod[j].exponent = prod_exp; }
		product.emplace_back(temp_prod); }

	int len = product.size();
	for (int i=1; i<len; i++) {
		product[0] = add_poly(product[0], product[i]); }

	vector<TERM> fin_product = product[0];

	return fin_product;
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

float eval_poly(vector<TERM> poly, float x)
{
	float answer=0;
	for (int i=0; i<poly.size(); i++) {
		float temp = pow(x, poly[i].exponent);
		//cout << poly[i].exponent << ' ' << temp << endl;
		temp *= poly[i].coefficient;
		//cout << poly[i].coefficient << ' ' << temp << endl;
		answer += temp;	}
	//cout << answer << endl;

	return answer;
}

float newton_raphson(vector<TERM> poly, float guess)
{
	float f, f_prime;
	
	f = eval_poly(poly, guess);
	f_prime = eval_poly(derive_poly(poly), guess);
	guess = guess - (f / f_prime);

	return guess;
}

float root_poly(vector<TERM> poly)
{
	/*bool search = true;
	int i = -100;
	float temp1, temp2;
	int x1, x2;
	while (search && i <= 100) {
		temp1 = eval_poly(poly, i);
		temp2 = eval_poly(poly, i+1);
		if ((temp1 > 0 && temp2 < 0) || (temp1 < 0 && temp2 > 0)) {
			x1 = i;
			x2 = i+1;
			search = false; }
		i++; }*/

	/*if (x1 < x2) {
		float temp = x1;
		x1 = x2;
		x2 = temp; }
	
	float guess = x1;*/

	float guess = 0;
	//(x1 > x2) ? guess = x1 : guess = x2;

	//cout << guess << endl;
	
	//float temp = eval_poly(poly, 2);
	//cout << temp << endl;

	//float guess = 20;
	float diff = 1;
	int j = 0;
	while (diff > 0.000001 && j < 100) {
	//for (int i=0; i<100; i++) {
		float temp = guess;
		//cout << temp << ' ' << guess << endl;
		guess = newton_raphson(poly, guess);
		//cout << guess << endl;
		diff = abs(temp - guess);
		//cout << diff << endl;
		j++; }

	return guess;
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
			cout << inputs[0] << endl; }

		if (inputs.size() == 2) {
			vector<string> temp = separate_terms(inputs[1]);
			vector<TERM> terms = get_term_components(temp);

			if (inputs[0] == "deriv") {
				vector<TERM> deriv = derive_poly(terms);
				cout << "DERIV" << endl;
				cout << "P     = " << inputs[1] << endl;
				cout << "dP/dx = ";
				print_polynomial(deriv); }

			if (inputs[0] == "root") {
				//cout << "Not yet implemented" << endl;
				float root = root_poly(terms);
				cout << "ROOT" << endl;
				cout << "P = " << inputs[1] << endl;
				cout << "root(P)=r=" << root << ", P(r)=" << eval_poly(terms, root) << endl; }

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
				cout << "SUM" << endl;
				cout << "P   = " << inputs[1] << endl;
				cout << "Q   = " << inputs[2] << endl;
				cout << "P+Q = ";
				print_polynomial(sum); }
			
			if (inputs[0] == "prod") {
				vector<TERM> prod = multiply_poly(terms_poly1, terms_poly2);
				cout << "PROD" << endl;
				cout << "P   = " << inputs[1] << endl;
				cout << "Q   = " << inputs[2] << endl;
				cout << "P*Q = ";
				print_polynomial(prod);
				/*for (int i=0; i<prod.size(); i++) {
            		cout << prod[i].coefficient << ' ' << prod[i].exponent << endl; }*/ }
		
			//for (int i=0; i<sum.size(); i++) {
            //    cout << sum[i].coefficient << ' ' << sum[i].exponent << endl; }
		}

		cout << "\n> ";
		getline(cin, line); }
}
