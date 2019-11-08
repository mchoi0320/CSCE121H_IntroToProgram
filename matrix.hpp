#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
    public:
        // default constructor
        Matrix();

        // constructor to allocate space on heap
        Matrix(int row, int col);

        // copy constructor
        Matrix(Matrix &old);

        // destructor
        ~Matrix();

        // setter and getter functions
        void setVal(int row, int col, float val);
        float getVal(int row, int col);
        void getMatrix();
        
        // operative methods
        float calcMean(float matrix[][4], int col);
        void centerData(float initMatrix[][4], float centeredMat[][4]);
        float transpose();
        void prod();
        void print();

    private:
        int P, Q;           // P = rows & Q = columns
        float** vals;       // 2D array of floats

};

#endif
