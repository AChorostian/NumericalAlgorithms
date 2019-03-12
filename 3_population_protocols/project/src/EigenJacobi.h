#ifndef EigenJacobi_h
#define EigenJacobi_h

#include "Main.h"

void eigenjacobi( int size , Eigen::SparseMatrix<double,Eigen::RowMajor>* m , Eigen::SparseVector<double>* vb , Eigen::SparseVector<double>* vx , int times )
{
    //double *tempX = new double[size];
    auto* tempX = new Eigen::SparseVector<double>(size) ;

    for(int t=0; t<times; t++)
    {
        for(int i=0; i<size; i++)
        {
            tempX->coeffRef(i) = vb->coeffRef(i);
            for(int j=0; j<size; j++)
            {
                if (j!=i)
                {
                    tempX->coeffRef(i) += m->coeffRef(i,j) * vx->coeffRef(j);
                }
            }
            tempX->coeffRef(i) = tempX->coeffRef(i) / abs(m->coeffRef(i,i));
        }
        for(int k=0; k<size; k++)
        {
            vx->coeffRef( k ) = tempX->coeffRef(k);
        }
    }
}

#endif
