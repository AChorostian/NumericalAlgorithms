#ifndef EigenFiller_h
#define EigenFiller_h

#include "Main.h"


void eigenfill( Eigen::SparseMatrix<double,Eigen::RowMajor>* m , Eigen::SparseVector<double>* vb , int N )
{
    int w=0;

    vb->coeffRef( ((N+1)*(N+2)/2)-1 ) = 1;

    for(int y=0; y<=N ; y++)
    {
        for(int n=0; n<=N-y ; n++)
        {
            if ( !(( y==0 && (n==0 || n==N) ) || (y==N && n==0)) )
                m->coeffRef(w,w) = -1;
            
            double moreY = (double(y)/double(N)) * (double(N-y-n) / double(N-1)) + (double(N-y-n)/double(N)) * (double(y)/double(N-1));
            double moreN = (double(n)/double(N)) * (double(N-y-n) / double(N-1)) + (double(N-y-n)/double(N)) * (double(n)/double(N-1));
            double moreU = (double(y)/double(N)) * (double(n)/double(N-1)) + (double(n)/double(N)) * (double(y)/double(N-1));
            double stays = double(1) - moreY - moreU - moreN;
            
            int k2=0;
            for(int y2=0; y2<=N; y2++)
            {
                for(int n2=0; n2<=N-y2; n2++)
                {
                    if (y+1==y2 && n==n2)
                        m->coeffRef(w,k2) = moreY;
                    if (y==y2 && n+1==n2)
                        m->coeffRef(w,k2) = moreN;
                    if (y==y2+1 && n==n2+1)
                        m->coeffRef(w,k2) = moreU;
                    if (y==y2 && n==n2)
                        m->coeffRef(w,k2) = m->coeffRef(w,w)+stays;
                    k2++;
                }
            }
            w++;
        }
    }

}

void eprint( Eigen::SparseVector<double>* vx , int size )
{
    for(int i=0; i<size ; i++)
    {
        printf("|    %.5f",vx->coeff(i));
    }
    printf("\n");
}


#endif
