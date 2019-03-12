#ifndef MySparseMatrix_h
#define MySparseMatrix_h

#include "Main.h"

class MySparseMatrix
{
public:
    
    MySparseMatrix( int size )
    {
        this->size = size;
        this->msize = (size+1)*(size+2)/2;
        this->matrixAsize = 0;
        this->vectorBsize = 0;
        this->vectorXsize = 0;
    }
    void print( bool onlyB )
    {
        for(int i=0; i<msize ; i++)
        {
            if (onlyB == false)
                for(int j=0; j<msize ; j++)
                {
                    printMatrixA(i,j);
                }
            printf("|    ");
            printVectorX(i);
            if (onlyB == false) printf("\n");
        }
        printf("\n");
    }
    
    void setMatrixA( int i , int j , double value )
    {
        bool found = false;
        for ( int v=0; v<matrixAsize; v++ )
        {
            if ( i == matrixAI[v] && j == matrixAJ[v] )
            {
                matrixAV[v] = value;
                found = true;
                break;
            }
        }
        if (value != 0 && found == false )
        {
            matrixAI.push_back( i );
            matrixAJ.push_back( j );
            matrixAV.push_back( value );
            matrixAsize++;
        }
    }
    void setVectorB( int i , double value )
    {
        bool found = false;
        for ( int v=0; v<vectorBsize; v++ )
        {
            if ( i == vectorBI[v] )
            {
                vectorBV[v] = value;
                found = true;
                break;
            }
        }
        if (value != 0 && found == false )
        {
            vectorBI.push_back( i );
            vectorBV.push_back( value );
            vectorBsize++;
        }
    }
    void setVectorX( int i , double value )
    {
        bool found = false;
        for ( int v=0; v<vectorXsize; v++ )
        {
            if ( i == vectorXI[v] )
            {
                vectorXV[v] = value;
                found = true;
                break;
            }
        }
        if (value != 0 && found == false )
        {
            vectorXI.push_back( i );
            vectorXV.push_back( value );
            vectorXsize++;
        }
    }
    
    double getMatrixA( int i , int j )
    {
        for ( int v=0; v<matrixAsize; v++ )
        {
            if ( i == matrixAI[v] && j == matrixAJ[v] )
            {
                return matrixAV[v];
            }
        }
        return 0;
    }
    void printMatrixA( int i , int j )
    {
        bool flag=false;
        for ( int v=0; v<matrixAsize; v++ )
        {
            if ( i == matrixAI[v] && j == matrixAJ[v] )
            {
                printf("%.2f",matrixAV[v]);
                flag=true;
                break;
            }
        }
        if (!flag) printf("\t\t");
        else printf("\t");
    }
    double getVectorB( int i )
    {
        for ( int v=0; v<vectorBsize; v++ )
        {
            if ( i == vectorBI[v] )
            {
                return vectorBV[v];
            }
        }
        return 0;
    }
    void printVectorB( int i )
    {
        for ( int v=0; v<vectorBsize; v++ )
        {
            if ( i == vectorBI[v] )
            {
                printf("%.2f",vectorBV[v]);
                break;
            }
        }
        printf("\t");
    }
    double getVectorX( int i )
    {
        for ( int v=0; v<vectorXsize; v++ )
        {
            if ( i == vectorXI[v] )
            {
                return vectorXV[v];
            }
        }
        return 0;
    }
    void printVectorX( int i )
    {
        
        for ( int v=0; v<vectorXsize; v++ )
        {
            if ( i == vectorXI[v] )
            {
                printf("%.2f\t",vectorXV[v]);
            }
        }
        printf("\t");
    }
    
    int getSize(){ return this->size; }
    int getMSize(){ return this->msize; }
    
    void fillWithZeros(){}
    
    void swapRows(int a, int b)
    {
        double tempVal;
        
        for ( int k=0; k<msize; k++ )
        {
            if (getMatrixA( a , k ) != getMatrixA( b , k ))
            {
                tempVal = getMatrixA( a , k );
                setMatrixA( a , k , getMatrixA( b , k ) );
                setMatrixA( b , k , tempVal );
            }
        }
        if (getVectorB( a ) != getVectorB( b ))
        {
            tempVal = getVectorB( a );
            setVectorB( a , getVectorB( b ) );
            setVectorB( b , tempVal );
        }
    }
    
    long memorysize()
    {
        long r = sizeof(size) + sizeof(msize);
        r += sizeof(matrixAsize) + sizeof(vectorBsize) + sizeof(vectorXsize);
        r += matrixAI.size() + matrixAJ.size() + matrixAV.size();
        r += vectorBI.size() + vectorBV.size();
        r += vectorXI.size() + vectorXV.size();
        return r;
    }
    
private:
    
    unsigned short matrixAsize;
    unsigned short size,msize,vectorBsize,vectorXsize;
    
    std::vector<unsigned short> matrixAI;
    std::vector<unsigned short> matrixAJ;
    std::vector<double>  matrixAV;
    
    std::vector<unsigned short> vectorBI;
    std::vector<double>  vectorBV;
    
    std::vector<unsigned short> vectorXI;
    std::vector<double>  vectorXV;
    
};

#endif
