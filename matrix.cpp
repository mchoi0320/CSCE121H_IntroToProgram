#include <iostream>
#include <iomanip>
#include <vector>
#include "matrix.hpp"
using namespace std;

Matrix::Matrix() {}

Matrix::Matrix(int row, int col)
{
    P = row; Q = col;
    vals = new float*[P];
    for (int i=0; i<P; i++)
        vals[i] = new float[Q];
}

Matrix::Matrix(Matrix &old)
{
    P = old.P; Q = old.Q;
    vals = new float*[P];
    for (int i=0; i<P; i++) {
        vals[i] = new float[Q];
        for (int j=0; j<Q; j++) {
            vals[i][j] = old.vals[i][j]; } }
}

Matrix::~Matrix()
{
    delete[] vals;
}

void Matrix::setVal(int row, int col, float val)
{
    vals[row][col] = val;
}

float Matrix::getVal(int row, int col)
{
    return vals[row][col];
}

float Matrix::calcMean(float matrix[][4], int col)
{
    float sum=0, mean;
    for (int i=0; i<P; i++) {
        sum += matrix[col][i]; }
    mean = sum / P;

    return mean;
}

void Matrix::centerData(float initMatrix[][4], float centeredMat[][4])
{
    float mean;
    vector<float> means;
    for (int col=0; col<Q; col++) {
        mean = calcMean(initMatrix, col);
        means.push_back(mean); }

    for (int col=0; col<Q; col++) {
        for (int row=0; row<P; row++) {
            centeredMat[row][col] -= means[col]; } }
}

void Matrix::prod()
{

}

void Matrix::print()
{
    for (int i=0; i<P; i++) {
        for (int j=0; j<Q; j++) {
            cout << left;
            cout << fixed << setprecision(3) << setw(6) << vals[i][j] << ' '; }
        cout << endl; }
}
