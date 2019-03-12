#ifndef Filler_h
#define Filler_h

#include "Main.h"

template <typename T>
void fill( T* matrix )
{
    int N = matrix->getSize();
    int msize= matrix->getMSize();;
    int w=0;
    
    matrix->fillWithZeros();
    matrix->setVectorB(msize-1,1);
    
    for(int y=0; y<=N ; y++)
    {
        for(int n=0; n<=N-y ; n++)
        {
            if ( !(( y==0 && (n==0 || n==N) ) || (y==N && n==0)) )
                matrix->setMatrixA(w,w,-1);
            
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
                        matrix->setMatrixA(w,k2,moreY);
                    if (y==y2 && n+1==n2)
                        matrix->setMatrixA(w,k2,moreN);
                    if (y==y2+1 && n==n2+1)
                        matrix->setMatrixA(w,k2,moreU);
                    if (y==y2 && n==n2)
                        matrix->setMatrixA(w,k2,matrix->getMatrixA(w,w)+stays);
                    k2++;
                }
            }
            w++;
        }
    }
}


#endif
