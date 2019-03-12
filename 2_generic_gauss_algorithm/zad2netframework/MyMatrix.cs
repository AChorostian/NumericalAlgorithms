using System;

// Dodatkowa biblioteka dostarczająca możliwość wykonywania operacji
// arytmetycznych na nieokreślonych typach w klasie generycznej
using MiscUtil;

namespace zad2netframework
{
    public class MyMatrix<T>
    {
        public T[,] matrixA;
        public T[] vectorB;
        public T[] vectorX;
        public T[] vectorXgauss;
        public int dimensions;
        public int[] column;

        public MyMatrix(int dimensions)
        {
            this.dimensions = dimensions;
            matrixA = new T[dimensions, dimensions];
            vectorX = new T[dimensions];
            vectorB = new T[dimensions];
            vectorXgauss = new T[dimensions];
            column = new int[dimensions];
            for (int i = 0; i < dimensions; i++)
                column[i] = i;
        }

        public void Multiplication()
        {
            for (int y = 0; y < dimensions; y++)
                for (int x = 0; x < dimensions; x++)
                    vectorB[y] = Operator.Add(vectorB[y], Operator.Multiply(matrixA[x, y], vectorX[x]));
        }
        public void CalculateStep( int n )
        {
            for (int y = n; y < dimensions; y++)
            {
                T a = Operator.Divide(matrixA[column[n - 1], y], matrixA[column[n - 1], n - 1]);
                for (int x = n - 1; x < dimensions; x++)
                    matrixA[column[x], y] = Operator.Subtract(matrixA[column[x], y], Operator.Multiply(a, matrixA[column[x], n - 1]));
                vectorB[y] = Operator.Subtract(vectorB[y], Operator.Multiply(a, vectorB[n - 1]));
            }
        }

        public void CalculateG()
        {
            for (int n = 1; n < dimensions; n++)
                CalculateStep(n);
            CalculateResult();
        }

        public void CalculateGP()
        {
            for (int n = 1; n < dimensions; n++)
            {
                int number = n - 1;
                T max = matrixA[column[n - 1], n - 1];
                for (int i = n-1; i < dimensions; i++)
                {
                    T actual = Absolute(matrixA[column[n - 1] , i]);
                    if (Operator.GreaterThan<T>(actual, max))
                    {
                        max = actual;
                        number = i;
                    }
                }
                if (Operator.NotEqual(number, n - 1))
                {
                    for (int l = n - 1; l < dimensions; l++)
                    {
                        T tempA = matrixA[column[l], number];
                        matrixA[column[l], number] = matrixA[column[l], n-1];
                        matrixA[column[l], n - 1] = tempA;
                    }
                    T tempB = vectorB[number];
                    vectorB[number] = vectorB[n - 1];
                    vectorB[n - 1] = tempB;
                }
                CalculateStep(n);
            }
            CalculateResult();
        }

        public void CalculateGF()
        {
            for (int n = 1; n < dimensions; n++)
            {

                int number = column[n - 1];
                int numberr = n - 1;
                T max = matrixA[column[n - 1], n - 1];
                for (int i = n-1; i < dimensions; i++)
                {
                    for (int j = n - 1; j < dimensions; j++)
                    {
                        T actual = Absolute(matrixA[column[i], j]);
                        if (Operator.GreaterThan<T>(actual, max))
                        {
                            max = actual;
                            number = i;
                            numberr = j;
                        }
                    }
                }
                if (Operator.NotEqual(number, column[n] - 1) && Operator.NotEqual(numberr, n - 1))
                {
                    for (int l = n - 1; l < dimensions; l++)
                    {
                        T tempA = matrixA[column[l], numberr];
                        matrixA[column[l], numberr] = matrixA[column[l], n - 1];
                        matrixA[column[l], n - 1] = tempA;
                    }
                    T tempB = vectorB[numberr];
                    vectorB[numberr] = vectorB[n - 1];
                    vectorB[n - 1] = tempB;

                    int temp = column[number];
                    column[number] = column[n - 1];
                    column[n - 1] = temp;
                }
                CalculateStep(n);
            }
            CalculateResult();
        }

        public void CalculateResult()
        {
            for (int y = dimensions - 1; y >= 0; y--)
            {
                vectorXgauss[column[y]] = Operator.Divide(vectorB[y], matrixA[column[y], y]);
                for (int x = dimensions - 1; x > y; x--)
                {
                    matrixA[column[x], y] = Operator.Divide(matrixA[column[x], y], matrixA[column[y], y]);
                    vectorXgauss[column[y]] = Operator.Subtract(vectorXgauss[column[y]], Operator.Multiply(matrixA[column[x], y], vectorXgauss[column[x]]));
                }
            }
            for (int i = 0; i < dimensions; i++)
                vectorB[i] = vectorXgauss[i];
        }

        public T CalculateDiff()
        {
            T sum = Operator.Subtract(vectorX[0], vectorX[0]);
            for (int y = 0; y < dimensions; y++)
            {
                //Console.WriteLine( vectorX[y] + "\t=\t" + vectorB[y] );
                T diff = Absolute(Operator.Subtract( vectorX[y] , vectorB[y] ));
                //Console.WriteLine("roznica: " + diff);
                sum = Operator.Add( sum , diff);
            }
            return sum;
        }

        public T Absolute(T obj)
        {
            T zero = Operator.Subtract(obj, obj);
            if (Operator.LessThan(obj, zero))
                obj = Operator.Subtract(obj, Operator.Add(obj, obj));
            return obj;
        }

        public void SetMatrixA(int x, int y, T value) { matrixA[x, y] = value; }
        public void SetVectorB(int y, T value) { vectorB[y] = value; }
        public void SetVectorX(int y, T value) { vectorX[y] = value; }

        public T GetMatrixA(int x, int y) { return matrixA[x, y]; }
        public T GetVectorB(int y) { return vectorB[y]; }
        public T GetVectorX(int y) { return vectorX[y]; }
    }
}
