#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "matrix.hpp"
using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3) {
        cout << "Enter the name of both the [iris data file] and the [name of the species] to select records for into the command line." << endl;
        exit(0); }
    
    ifstream file;
    file.open(argv[1]);
    string species = argv[2];

    string line, val;
    vector<string> temp;
    while (getline(file, line)) {
        if (line.find(species) != string::npos) {
            istringstream ss(line);
            while (getline(ss, val, ',')) {
                temp.push_back(val); } } }
    
    Matrix matrix(temp.size()/5, 4);
    for (int row=0; row<temp.size()/5; row++) {
        for (int col=0; col<5; col++) {
            if (col < 4) {
                matrix.setVal(row, col, stof(temp[row*5+col])); } } }

    //matrix.print(); cout << endl;

    Matrix centeredMat(matrix);
    centeredMat.centerData();
    //centeredMat.print(); cout << endl;
    //cout << centeredMat.calcMean(0) << endl;

    //Matrix transposedMat(centeredMat);
    Matrix transposedMat = centeredMat.transpose();
    //transposedMat.transpose();
    //transposedMat.print(); cout << endl;

    cout << "Covariance Matrix:" << endl;    
    Matrix product = prod(transposedMat, centeredMat);
    product.print(); cout << endl;

    cout << "Correlation Matrix:" << endl;    
    Matrix normalizedMat = product.normalize();
    normalizedMat.print(); cout << endl;
    
    matrix.~Matrix();

    exit(0);
}