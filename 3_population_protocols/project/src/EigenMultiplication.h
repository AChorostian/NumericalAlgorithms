#ifndef EigenMultiplication_h
#define EigenMultiplication_h

#include "Main.h"

double eigenmultiplication( Eigen::SparseVector<double>* vx , int size , int N )
{
    auto* matrix = new Eigen::SparseMatrix<double,Eigen::RowMajor>(size,size);
    auto* vectorb = new Eigen::SparseVector<double>(size);

    eigenfill( matrix , vectorb , N );

    double tempB;
    double diff=0;
    for(int i=0; i<size ; i++)
    {
        tempB=0;

        for(int j=0; j<size ; j++)
        {
            tempB += matrix->coeff(i,j) * vx->coeff(j);
        }

        if(i!=size-1)
            diff += abs(tempB);
        else
            diff += abs(1-tempB);

    }

    return diff/size;
}



#endif
