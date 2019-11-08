#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "matrix.hpp"
using namespace std;

int main(int argc, char** argv)
{
    ifstream file;
    file.open(argv[1]);

    string line, val;
    vector<string> temp;
    while (getline(file, line)) {
        istringstream ss(line);
        while (getline(ss, val, ',')) {
            temp.push_back(val); } }
    
    int i=temp.size()-1;
    while (temp[i].find("setosa") == string::npos) {
        temp.pop_back();
        i--; }

    Matrix matrix(temp.size()/5, 4);
    for (int row=0; row<temp.size()/5; row++) {
        for (int col=0; col<5; col++) {
            if (col < 4) {
                //cout << temp[row*5+col] << endl;
                matrix.setVal(row, col, stof(temp[row*5+col])); } } }

    //matrix.print(); cout << endl;

    Matrix centeredMat = matrix; //centeredMat.print();
    //centeredMat.centerData(matrix, centeredMat);
}