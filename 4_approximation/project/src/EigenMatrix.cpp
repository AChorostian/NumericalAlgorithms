#include "Main.h"


EigenMatrix::EigenMatrix(int N) : BaseMatrix(N), a(size,size), b(size), x(size)
{}

EigenMatrix::~EigenMatrix()
{
    a.resize(0,0);
    b.resize(0);
    x.resize(0);
}

void EigenMatrix::fill()
{
    int w=0;
    for(int i=0; i<size-1; i++)
        b.coeffRef(i) = 0;
    b.coeffRef(size-1) = 1;
    double temp = double(N)*double(N-1);
    for(int y=0; y<=N ; y++)
    {
        for(int n=0; n<=N-y ; n++)
        {
            if ( !(( y==0 && (n==0 || n==N) ) || (y==N && n==0)) )
                a.coeffRef(w,w) = -1;
            int k2=0;
            for(int y2=0; y2<=N; y2++)
            {
                for(int n2=0; n2<=N-y2; n2++)
                {
                    if (y+1==y2 && n==n2)
                        a.coeffRef(w,k2) = 2*double(y)*double(N-y-n)/temp;
                    if (y==y2 && n+1==n2)
                        a.coeffRef(w,k2) = 2*double(n)*double(N-y-n)/temp;
                    if (y==y2+1 && n==n2+1)
                        a.coeffRef(w,k2) = 2*double(y)*double(n)/temp;
                    if (y==y2 && n==n2)
                        a.coeffRef(w,k2) = a.coeffRef(w,w) + double(1) - 2*double(y)*double(N-y-n)/temp - 2*double(n)*double(N-y-n)/temp - 2*double(y)*double(n)/temp;
                    k2++;
                }
            }
            w++;
        }
    }
}

void EigenMatrix::sparseLU()
{
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(a);
    x = solver.solve(b);
}

double EigenMatrix::getX(int i)
{
    return double(x[i]);
}