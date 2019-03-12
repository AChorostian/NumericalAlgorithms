#include "Main.h"

VectorMapMatrix::VectorMapMatrix(int N) : BaseMatrix(N) , a(size)
{}

double VectorMapMatrix::getA( int i , int j )
{
    std::map<int,double>::const_iterator iterator = a[i].find(j);
    return (iterator != a[i].end()) ? iterator->second : double(0);
}

double VectorMapMatrix::getB( int i )
{
    std::map<int,double>::const_iterator iterator = b.find(i);
    return (iterator != b.end()) ? iterator->second : double(0);
}

double VectorMapMatrix::getX( int i )
{
    std::map<int,double>::const_iterator iterator = x.find(i);
    return (iterator != x.end()) ? iterator->second : double(0);
}

void VectorMapMatrix::fill()
{
    int w=0;
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
                        a[w][k2] = getA(w,w) + double(1) - 2*double(y)*double(N-y-n)/temp - 2*double(n)*double(N-y-n)/temp - 2*double(y)*double(n)/temp;
                    k2++;
                }
            }
            w++;
        }
    }
}

void VectorMapMatrix::seidel( double prec , EigenMatrix* eigen )
{
    int init=0;
    double diff;
    do
    {
        init++;
        double temp;
        for (int r = 0; r < size; ++r)
        {
            temp = (double) 0;
            for (std::map<int,double>::const_iterator c = a[r].begin(); c != a[r].end(); ++c)
                if (c->first != r)
                    temp += c->second * getX(c->first);
            x[r] = ((getB(r) - temp ) / getA(r,r));
        }
        for (int i=0;i<size;i++)
            diff += abs( eigen->getX(i) - x[i] );
        diff = diff / size;
    }
    while (init <5 || prec < diff );
}

void VectorMapMatrix::print()
{
    for(int i=0;i<size;i++)
    {
        for (int j = 0; j < size; j++)
            printf("%5f\t",getA(i,j));
        std::cout << "|\t" << getB(i) << " = " << getX(i) <<"\n";
    }
}

void VectorMapMatrix::printX()
{
    for(int i=0;i<size;i++)
    {
        printf("%5f   ",abs(getX(i)));
    }
    std::cout << "\n";
}