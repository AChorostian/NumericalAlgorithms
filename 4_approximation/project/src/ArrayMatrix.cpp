#include "Main.h"

ArrayMatrix::ArrayMatrix(int N) : BaseMatrix(N)
{
    a = new double *[size];
    for (int i = 0; i < size; i++)
        a[i] = new double[size];
    b = new double[size];
    x = new double[size];
}

ArrayMatrix::~ArrayMatrix()
{
    for (int i = 0; i < size; i++)
        delete (a[i]);
    delete (a);
    delete (b);
    delete (x);
}

void ArrayMatrix::fill()
{
    int w=0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            a[i][j] = 0;
        b[i] = 0;
    }
    b[size-1] = 1;
    double temp = double(N)*double(N-1);
    for(int y=0; y<=N ; y++)
    {
        for(int n=0; n<=N-y ; n++)
        {
            if ( !(( y==0 && (n==0 || n==N) ) || (y==N && n==0)) )
                a[w][w] = -1;
            int k2=0;
            for(int y2=0; y2<=N; y2++)
            {
                for(int n2=0; n2<=N-y2; n2++)
                {
                    if (y+1==y2 && n==n2)
                        a[w][k2] = 2*double(y)*double(N-y-n)/temp;
                    if (y==y2 && n+1==n2)
                        a[w][k2] = 2*double(n)*double(N-y-n)/temp;
                    if (y==y2+1 && n==n2+1)
                        a[w][k2] = 2*double(y)*double(n)/temp;
                    if (y==y2 && n==n2)
                        a[w][k2] = a[w][w] + double(1) - 2*double(y)*double(N-y-n)/temp - 2*double(n)*double(N-y-n)/temp - 2*double(y)*double(n)/temp;
                    k2++;
                }
            }
            w++;
        }
    }
}

void ArrayMatrix::swapRows(int rowA, int rowB)
{
    double *tempRow = a[rowA];
    a[rowA] = a[rowB];
    a[rowB] = tempRow;
    if (b[rowA] != 0 || b[rowB] != 0)
    {
        double tempVal = b[rowA];
        b[rowA] = b[rowB];
        b[rowB] = tempVal;
    }
}

void ArrayMatrix::gauss(bool faster)
{
    for (int n = 1; n < size ; n++)
    {
        int maxIndex = n - 1;
        double maxValue = a[n-1][n-1];

        for (int i = n-1; i < size; i++)
        {
            if ( abs(a[i][n-1]) > abs(maxValue) )
            {
                maxIndex = i;
                maxValue = a[i][n-1];
            }
        }
        if ( maxIndex != n-1 )
            swapRows( maxIndex , n-1 );
        for (int y = n; y < size; y++)
        {
            if ( !faster || a[y][n-1] != 0)
            {
                double temp = a[y][n - 1] / a[n - 1][n - 1];
                for (int x = n - 1; x < size; x++)
                    a[y][x] = a[y][x] - ( temp * a[n-1][x] );
                b[y] = b[y] - ( temp * b[n-1] );
            }
        }
    }
    for (int i = size - 1; i >= 0; i--)
    {
        x[i] = b[i] / a[i][i];
        for (int j = size - 1; j > i; j--)
        {
            a[i][j] = a[i][j] / a[i][i];
            x[i] = x[i] - ( a[i][j] * x[j] );
        }
    }
}

void ArrayMatrix::seidel( double precision , EigenMatrix* pattern )
{
    int init=0;
    double diff;
    double tempX;
    do
    {
        init++;
        for(int i=0; i<size; i++)
        {
            tempX = b[i];
            for(int j=0; j<size; j++)
                if (j!=i)
                    tempX += a[i][j] * x[j];
            x[i] = tempX / abs(a[i][i]);
        }
        diff =0;
        for (int i=0;i<size;i++)
            diff += abs( pattern->getX(i) - x[i] );
        diff = diff / size;
    }
    while (init <5 || precision < diff);
}
