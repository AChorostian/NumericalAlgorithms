#ifndef Matrix_h
#define Matrix_h

#include "Main.h"

class Matrix
{
public:
    
    Matrix( int size )
    {
        this->size = size;
        this->msize = (size+1)*(size+2)/2;
        
        matrixA = new double*[msize];
        for(int i = 0; i < msize; i++)
            matrixA[i] = new double[msize];
        vectorB = new double[msize];
        vectorX = new double[msize];
    }
    ~Matrix()
    {
        for(int i=0;i<msize;i++)
            delete(matrixA[i]);
        delete(matrixA);
        delete(vectorB);
        delete(vectorX);
    }
    void print( bool onlyB )
    {
        for(int i=0; i<msize ; i++)
        {
            if (!onlyB)
                for(int j=0; j<msize ; j++)
                {
                     printf("%.2f\t",matrixA[i][j]);
                }
            printf("|    %.5f",vectorX[i]);
            if (!onlyB) printf("\n");
        }
        printf("\n");
    }
    
    void setMatrixA( int i , int j , double value ){ this->matrixA[i][j] = value; }
    void setVectorB( int i , double value ){ this->vectorB[i] = value; }
    void setVectorX( int i , double value ){ this->vectorX[i] = value; }
    
    double getMatrixA( int i , int j ){ return this->matrixA[i][j]; }
    double getVectorB( int i ){ return this->vectorB[i]; }
    double getVectorX( int i ){ return this->vectorX[i]; }
    
    int getSize(){ return this->size; }
    int getMSize(){ return this->msize; }
    
    void fillWithZeros()
    {
        for(int i=0; i<msize ; i++)
        {
            for(int j=0; j<msize ; j++)
                matrixA[i][j]=0;
            vectorB[i]=0;
            //vectorX[i]=0;
        }
    }
    
    void swapRows(int a, int b)
    {
        double* tempRow = matrixA[a];
        matrixA[a] = matrixA[b];
        matrixA[b] = tempRow;
        
        if (vectorB[a] != 0 || vectorB[b] != 0)
        {
            double tempVal = vectorB[a];
            vectorB[a] = vectorB[b];
            vectorB[b] = tempVal;
        }
    }
    
    long memorysize()
    {
        long r = sizeof(size) + sizeof(msize);
        r += msize*msize*sizeof(double) + msize*sizeof(double) + msize*sizeof(double);
        r += sizeof(matrixA)*(msize+1) + sizeof(vectorB) + sizeof(vectorX);
        return r;
    }
    
private:
    
    unsigned short size,msize;
    double** matrixA;
    double*  vectorB;
    double*  vectorX;
    
};

#endif
