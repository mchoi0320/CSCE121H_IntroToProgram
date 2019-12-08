#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "poly_class.hpp"
using namespace std;


//----------class Term----------
Term::Term(string term)
{
    pair<float, int> components = parse_term(term);
    set_coefficient(components.first);
    set_exponent(components.second);
}

Term::Term(float c, int e)
{
    set_coefficient(c);
    set_exponent(e);
}

bool Term::operator==(const Term& t)
{
    return (coefficient == t.coefficient && exponent == t.exponent);
}

bool Term::operator<(const Term& t)
{
    return (exponent < t.exponent);
}

pair<float, int> Term::parse_term(string term)
{
    pair<float, int> components = make_pair(find_coefficient(term), find_exponent(term));
    return components;
}

float Term::find_coefficient(string term)
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

int Term::find_exponent(string term)
{
    if (term.find('x') == string::npos) return 0;
	else if (term.find('^') == string::npos) return 1;
	else {
		int exponent_pos = term.find('^') + 1;
		string exponent_str = term.substr(exponent_pos, term.size());
		int exponent = stoi(exponent_str);
		return exponent; }
}

void Term::set_coefficient(float c)
{
    coefficient = c;
}

void Term::set_exponent(int e)
{
    exponent = e;
}

float Term::get_coefficient()
{
    return coefficient;
}

int Term::get_exponent()
{
    return exponent;
}

void Term::print(int i)
{
    if (exponent == 0) {
        if (coefficient < 0 || i == 0) cout << coefficient;
        else cout << '+' << coefficient; }
    else if (exponent == 1) {
        if (coefficient < 0) {
            if (coefficient == -1) cout << "-x";
            else cout << coefficient << 'x'; }
        else {
            if (coefficient == 1) {
                if (i == 0) cout << 'x';
                else cout << "+x"; }
            else {
                if (i == 0) cout << coefficient << 'x';
                else cout << '+' << coefficient << 'x'; } } }
    else {
        if (coefficient < 0) {
            if (coefficient == -1) cout << "-x^" << exponent;
            else cout << coefficient << "x^" << exponent; }
        else {
            if (coefficient == 1) {
                if (i == 0) cout << "x^" << exponent;
                else cout << "+x^" << exponent; }
            else {
                if (i == 0) cout << coefficient << "x^" << exponent;
                else cout << '+' << coefficient << "x^" << exponent; } } }
}


//----------class Poly----------
Poly::Poly() {}

Poly::Poly(string expr)
{
    parse_expr(expr);
}

Poly::Poly(const Poly& old)
{
    poly = old.poly;
}

void Poly::parse_expr(string expr)
{
    if (expr[0] != '-') expr = '+' + expr;

	int term_start=0;
	for (int i=0; i<expr.size(); i++) {
		if ((expr[i] == '+' || expr[i] == '-') && i != 0) {
			Term t(expr.substr(term_start, i-term_start));
            add_term(t);
			term_start = i; } }
	Term last(expr.substr(term_start, expr.size()-term_start));
	add_term(last);
}

void Poly::add_term(Term t)
{
    poly.push_back(t);
}

void Poly::remove_zeros()
{
    vector<Term>::iterator iter = poly.begin();
    while (iter != poly.end()) {
        if (iter->get_coefficient() == 0) {
            poly.erase(iter); }
        else iter++; }
}

void Poly::descend_sort()
{
    sort(poly.rbegin(), poly.rend());
}

vector<Term> Poly::get_poly()
{
    return poly;
}

float Poly::eval(float x)
{
    float answer=0;
	for (int i=0; i<poly.size(); i++) {
		float temp = pow(x, poly[i].get_exponent());
		temp *= poly[i].get_coefficient();
		answer += temp;	}

	return answer;
}

Poly Poly::add(Poly p)
{
    Poly sum;

	for (int i=0; i<poly.size(); i++) {
		float new_coeff = poly[i].get_coefficient();
		for (int j=0; j<p.get_poly().size(); j++) {
			if (poly[i].get_exponent() == p.get_poly()[j].get_exponent()) {
            	new_coeff += p.get_poly()[j].get_coefficient(); } }
		Term t(new_coeff, poly[i].get_exponent());
        sum.add_term(t); }

	for (int i=0; i<p.get_poly().size(); i++) {
		bool search = true;
		for (int j=0; j<sum.get_poly().size(); j++) {
			if (p.get_poly()[i].get_exponent() == sum.get_poly()[j].get_exponent()) {
				search = false;	} }
		if (search) {
			sum.add_term(p.get_poly()[i]); } }

    sum.remove_zeros();
	sum.descend_sort();

    return sum;
}

Poly Poly::multiply(Poly p)
{
    vector<Poly> temp_product;

    for (int i=0; i<poly.size(); i++) {
        Poly temp;
        for (int j=0; j<p.get_poly().size(); j++) {
            float prod_coeff = poly[i].get_coefficient() * p.get_poly()[j].get_coefficient();
            int prod_exp = poly[i].get_exponent() + p.get_poly()[j].get_exponent();
            Term t(prod_coeff, prod_exp);
            temp.add_term(t); }
        temp_product.push_back(temp); }

    for (int i=1; i<temp_product.size(); i++) {
        temp_product[0] = temp_product[0].add(temp_product[i]); }

    Poly product(temp_product[0]);

    return product;
}

Poly Poly::derive()
{
	Poly derivative;

	float deriv_coeff; int deriv_exp;
	for (int i=0; i<poly.size(); i++) {
		deriv_coeff = poly[i].get_coefficient() * poly[i].get_exponent();
		deriv_exp = poly[i].get_exponent() - 1;
		if (deriv_coeff != 0) {
            Term t(deriv_coeff, deriv_exp);
			derivative.add_term(t); } }

	if (derivative.get_poly().size() == 0) {
        Term t(0, 0);
		derivative.add_term(t); }

	return derivative;
}

float Poly::newton_raphson(float guess)
{
	float f, f_prime;
	
	f = eval(guess);
	f_prime = derive().eval(guess);
	guess = guess - (f / f_prime);

	return guess;
}

float Poly::root()
{
    float guess = 0, diff = 1;
	int i = 0;
	while (diff > 0.000001) {
		float temp = guess;
		guess = newton_raphson(guess);
		diff = abs(temp - guess);
		i++; }

	return guess;
}

void Poly::print()
{
    for (int i=0; i<poly.size(); i++) poly[i].print(i);
    cout << endl;
}