#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    public:
        // constructor to allocate space on heap
        Matrix(int row, int col);

        // copy constructor
        Matrix(const Matrix &old);

        // destructor
        ~Matrix();

        // setter and getter functions
        void setVal(int row, int col, float val);
        float getVal(int row, int col);

        // operative methods
        void print();
        float calcMean(int col);
        void centerData();
        //void transpose();
        Matrix transpose();
        Matrix normalize();
        friend Matrix prod(Matrix A, Matrix B);

    private:
        int P, Q;       // P = rows & Q = columns
        float* vals;    // array of floats
};

class RotMat : public Matrix {
    public:
        // constructor for (x,y) coordinate
        RotMat(float x, float y);

        // constructor for 2x2 matrix
        RotMat(float d);
};

Matrix prod(Matrix A, Matrix B);

#endif
