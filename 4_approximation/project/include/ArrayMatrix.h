#ifndef ARRAY_H
#define ARRAY_H

#include "Main.h"

class ArrayMatrix : public BaseMatrix
{
public:

    explicit ArrayMatrix(int N);
    ~ArrayMatrix();

    void fill() override;
    void gauss(bool faster);
    void seidel(double precision, EigenMatrix *pattern);

private:

    double** a;
    double* b;
    double* x;

    void swapRows(int a, int b);

};

#endif
