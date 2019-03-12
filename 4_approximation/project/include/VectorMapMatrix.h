#ifndef VECTORMAP_H
#define VECTORMAP_H

#include "Main.h"

class VectorMapMatrix : public BaseMatrix
{
public:

    explicit VectorMapMatrix(int N);

    void fill() override;
    void seidel(double prec, EigenMatrix* eigen);

    double getA(int i, int j);
    double getB(int i);
    double getX(int i);

    void print();
    void printX();

private:

    std::vector<std::map<int,double>> a;
    std::map<int,double> b;
    std::map<int,double> x;

};

#endif