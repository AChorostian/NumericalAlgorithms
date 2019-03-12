#ifndef EIGENMATRIX_H
#define EIGENMATRIX_H

#include "Main.h"

class EigenMatrix : BaseMatrix
{
public:

    explicit EigenMatrix(int N);
    ~EigenMatrix();

    void fill() override;
    void sparseLU();

    double getX(int i);

private:

    Eigen::SparseMatrix<double> a;
    Eigen::VectorXd b;
    Eigen::VectorXd x;

};

#endif
