#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "matrix.hpp"
using namespace std;
/*
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
*/
Matrix::Matrix(int row, int col)
{
    P = row; Q = col;
    vals = new float[row * col];
}

Matrix::Matrix(const Matrix &old)
{
    P = old.P; Q = old.Q;
    vals = new float[P * Q];

    for (int i=0; i<P*Q; i++) {
        vals[i] = old.vals[i]; }
}

Matrix::~Matrix()
{
    delete[] vals;
}

void Matrix::setVal(int row, int col, float val)
{
    /*if (row < P && col < Q) {
        vals[(row * Q) + col] = val; }
    else {
        cout << "Error: out of bounds" << endl;
        exit(0); }*/
    assert(row < P && col < Q);
    vals[(row * Q) + col] = val;
}

float Matrix::getVal(int row, int col)
{
    /*if (row < P && col < Q) {
        return vals[(row * Q) + col]; }
    else {
        cout << "Error: out of bounds" << endl;
        exit(0); }*/
    assert(row < P && col < Q);
    return vals[(row * Q) + col];
}

float Matrix::calcMean(int col)
{
    float sum=0, mean;
    for (int row=0; row<P; row++) {
        sum += getVal(row, col); }
    mean = sum / P;

    return mean;
}

void Matrix::centerData()
{
    float mean;
    vector<float> means;
    for (int col=0; col<Q; col++) {
        mean = calcMean(col);
        means.push_back(mean); }

    for (int col=0; col<Q; col++) {
        for (int row=0; row<P; row++) {
            setVal(row, col, getVal(row, col) - means[col]); } }
}
/*
void Matrix::transpose()
{
    float *newVals = new float(Q * P);
    
    for (int row=0; row<P; row++) {
        for (int col=0; col<Q; col++) {
            newVals[row+col*P] = getVal(row,col); } }
    vals = newVals;
    
    int temp=P; P=Q; Q=temp;
}
*/
Matrix Matrix::transpose()
{
    Matrix mat(Q, P);
    for (int row=0; row<Q; row++) {
        for (int col=0; col<P; col++) {
            mat.setVal(row, col, getVal(col, row)); } }
    
    return mat;
}

Matrix Matrix::normalize()
{
    assert(P == Q);
    Matrix mat(P, Q);
    for (int row=0; row<P; row++) {
        for (int col=0; col<Q; col++) {
            mat.setVal(row, col, getVal(row, col) / sqrt(getVal(row, row) * getVal(col, col))); } }

    return mat;
}

void Matrix::print()
{
    for (int row=0; row<P; row++) {
        for (int col=0; col<Q; col++) {
            //cout << left;
            cout << fixed << setprecision(3) << setw(6) << vals[(row * Q) + col] << ' '; }
        cout << endl; }
}

Matrix prod(Matrix A, Matrix B)
{
    assert(A.Q == B.P);
    Matrix mat(A.P, B.Q);
    for (int i=0; i<A.P; i++) {
        for (int j=0; j<B.Q; j++) {
            mat.setVal(i, j, 0);
            for (int k=0; k<A.Q; k++) {
                mat.setVal(i, j, mat.getVal(i, j) + (A.getVal(i, k) * B.getVal(k, j))); } } }

    return mat;
}

RotMat::RotMat(float x, float y) : Matrix(1, 2)
{
    setVal(0, 0, x);
    setVal(0, 1, y);
}

RotMat::RotMat(float d) : Matrix(2, 2)
{
    float r = d * M_PI / 180;
	setVal(0, 0,  cos(r));
	setVal(0, 1, -sin(r));
	setVal(1, 0,  sin(r));
	setVal(1, 1,  cos(r));
}
