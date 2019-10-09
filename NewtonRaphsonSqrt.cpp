#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

float newton_raphson(float n, float guess)
{
	float f, f_prime;
	
	f = pow(guess,2) - n;
	f_prime = 2 * guess;
	guess = guess - (f / f_prime);

	return guess;
}

float newton_raphson_iter(float n)
{
	float guess = n, f, f_prime;

	int i=0;
	
	if (n < 1 && n > 0) {
		while (pow(guess,2) < 1 && i < 10) {
			guess = newton_raphson(n,guess);
			i++;
			if (i%2 == 0) {
				cout << "iter: " << i << ", est: " << guess << "\n"; } } }

	else {
		while (pow(guess,2) > n && i < 50) {
			guess = newton_raphson(n,guess);
			i++;
			if (i%2 == 0) {
				cout << "iter: " << i << ", est: " << guess << "\n"; } } }
	
	cout << "[iterative] sqrt(" << n << ")=" << guess << "\n\n";
	
	return guess;
}

float newton_raphson_rec(float n, float guess, vector<float> &guesses)
{	
	guess = newton_raphson(n,guess);
	
	guesses.push_back(guess);

	if (n == 0) return 0;

	else if (n == 1) return 1;

	else {
		if (pow(guess,2) - n < 0.000001) return guess;
		else newton_raphson_rec(n,guess,guesses); }
}

int main(int argc, char** argv)
{
	float input = atof(argv[1]);
	if (input < 0) { cout << "Please enter a non-negative value.\n"; exit(0); }

	vector<float> rec_guesses;

	float estimate_iter = newton_raphson_iter(input);
	float estimate_rec = newton_raphson_rec(input,input,rec_guesses);

	for (int i=0; i<rec_guesses.size(); i++) {
		if (i%2 != 0) {
			cout << "recursive estimate: " << rec_guesses[i] << "\n"; } }
	cout << "[recursive] sqrt(" << input << ")=" << estimate_rec << "\n\n";	

	cout << "[built-in]  sqrt(" << input << ")=" << sqrt(input) << "\n";
	cout << "[verifying] " << estimate_iter << "^2=" << pow(estimate_iter,2) << "\n";
	//cout << "[verifying] " << estimate_rec << "^2=" << pow(estimate_rec,2) << "\n";
}
