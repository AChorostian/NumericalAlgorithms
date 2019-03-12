#include "Main.h"

BaseMatrix::BaseMatrix(int N)
{
    this->N = N;
    this->size = (N+1)*(N+2)/2;
}