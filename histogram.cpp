#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

int main(int argc, char** argv)
{
	ifstream input;
	input.open(argv[1]);
	int numBins = atoi(argv[2]);
	while (numBins <= 0) {
		cout << "Please re-enter a positive value for the number of bins: ";
		cin >> numBins; }
	
	double val, sum=0, numVal=0;
	vector<double> vals;

	while (input >> val) {
		vals.push_back(val);
		numVal += 1;
		sum += val; }

	cout << "\nNumber of values: " << numVal << endl;
/*	cout << sum << endl;
	int a;
	for (a=0; a<10; a++) {
		cout << vals.at(a) << " "; }
	cout << endl;	*/

	// Mean Calculation
	double mean = sum / numVal;
	cout << "Mean = " << mean << endl;

	// Standard Deviation Calculation
	int i; double diffSq, sumDiffSq=0, stDev;
	for (i=0; i<numVal; i++) {
		diffSq = pow((vals.at(i)-mean),2);
		sumDiffSq += diffSq;
		stDev = sqrt(sumDiffSq / (numVal-1)); }
	cout << "Standard Deviation = " << stDev << endl;

	// Finding Min & Max
	int j; double min=vals.at(0), max=vals.at(0);
	for (j=0; j<numVal; j++) {
		if (vals.at(j) < min) {
			min = vals.at(j); }
		if (vals.at(j) > max) {
			max = vals.at(j); } }
	cout << "Range: " << min << "-" << max << endl;

	//// Histogram
	// Finding the left bound of each bin
	double range = max - min;
	double binRange = range / numBins;
	double lBound=min;
	vector<double> bins;
	while (bins.size() < numBins) {
		bins.push_back(lBound);
		lBound += binRange; }
/*	cout << bins.size() << endl;
	int b;
	for (b=0; b<bins.size(); b++) {
		cout << bins.at(b) << " "; }
	cout << endl;	*/
	// Finding the number of values in each bin
	vector<int> numInBinTotal;
	int numInBin;
	int k, l, m;
	for (k=0; k<bins.size()-1; k++) {
		numInBin=0;
		for (l=0; l<vals.size(); l++) {
			if (vals.at(l) < (bins.at(k)+binRange) && vals.at(l) >= bins.at(k)) {
				numInBin += 1; } }
		numInBinTotal.push_back(numInBin); }
	numInBin=0;
	for (m=0; m<vals.size(); m++) {
		if (vals.at(m) <= (bins.at(bins.size()-1)+binRange) && vals.at(m) >= bins.at(bins.size()-1)) {
			numInBin += 1; } }
	numInBinTotal.push_back(numInBin);
/*	cout << numInBinTotal.size() << endl;
	int c;
	for (c=0; c<numInBinTotal.size(); c++) {
		cout << numInBinTotal.at(c) << " "; }
	cout << endl;	*/
	// Printing the histogram
	cout << "\n-------Histogram-------";
	int n, o;
	for (n=0; n<bins.size(); n++) {
		cout << endl;
		cout << fixed << setprecision(2) << bins.at(n) << '-' << bins.at(n)+binRange << "|";
		for (o=0; o<numInBinTotal.at(n); o++) {
			cout << '*'; } }
	cout << endl;
	cout << setfill('-') << setw(23) << '-' << endl;

	return 0;
}
