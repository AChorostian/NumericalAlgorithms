#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include "Main.h"

class BaseMatrix
{
public:

    explicit BaseMatrix(int N);
    virtual ~BaseMatrix() = default;

    virtual void fill() {}

protected:

    int N;
    int size;

};

#endif
