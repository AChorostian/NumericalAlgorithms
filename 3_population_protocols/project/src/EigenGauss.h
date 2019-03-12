#ifndef EigenGauss_h
#define EigenGauss_h

#include "Main.h"


void calculateEGP( int size , Eigen::SparseMatrix<double,Eigen::RowMajor>* m , Eigen::SparseVector<double>* vb , Eigen::SparseVector<double>* vx , bool faster)
{
    for (int n = 1; n < size ; n++)
    {

        // wybieranie max elementu
        int maxIndex = n - 1;
        double maxValue = m->coeff( n-1 , n-1 );

        for (int i = n-1; i < size; i++)
        {
            if ( abs(m->coeff(i,n-1)) > abs(maxValue) )
            {
                maxIndex = i;
                maxValue = m->coeff(i,n-1);
            }
        }
        if ( maxIndex != n-1 )
        {
            // zamiana max elementu

            auto* temp1 = new Eigen::SparseVector<double>(size) ;
            auto* temp2 = new Eigen::SparseVector<double>(size) ;
            *temp1 = m->row(maxIndex);
            *temp2 = m->row(n-1);
            m->row(maxIndex) = *temp2;
            m->row(n-1) = *temp1;
            //m->row(maxIndex).swap(m->row(n-1));
        }

        // liczenie gaussa
        for (int y = n; y < size; y++)
        {
            if ( !faster || m->coeff(y,n-1) != 0) // pomijanie dla 0
            {
                double a = m->coeff( y , n - 1  ) / m->coeff( n - 1 , n - 1 );
                for (int x = n - 1; x < size; x++)
                    m->coeffRef( y , x ) = m->coeff( y , x ) - ( a * m->coeff( n-1 , x ) );
                vb->coeffRef(y) = vb->coeffRef(y) - (a * vb->coeffRef(n - 1) );
            }
        }
    }
    // wyciaganie wyniku z macierzy trojkatnej
    for (int y = size - 1; y >= 0; y--)
    {
        vx->coeffRef(y) = vb->coeffRef(y) / m->coeff(y,y);

        for (int x = size - 1; x > y; x--)
        {
            m->coeffRef( y , x ) = m->coeff(y,x) / m->coeff(y,y);
            vx->coeffRef(y) = vx->coeffRef(y) - (m->coeff(y,x) * vx->coeffRef(x));
        }
    }
}

#endif
