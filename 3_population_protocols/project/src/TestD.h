#ifndef TestD_h
#define TestD_h

#include "Main.h"

void testD( int minSeconds , int minN )
{
    printf("Test D: ");

    std::ofstream fp;
    fp.open("TestD.csv");
    clock_t begin;
    clock_t end;
    double mtimeg=0,mtimes6=0,mtimes10=0,mtimes14=0;
    int times;


    fp << ";Fast Gauss (array);;Gauss-Seidel^-6 (array);;;Gauss-Seidel^-10 (array);;;Gauss-Seidel^-14 (array)\n";
    fp << "N;time;diff;time_pre;diff;time;time_pre;diff;time;time_pre;diff;time\n";

    for(int N=2;N<minN;N++)
    {
        fp << N << ";";
        int s = (N+1)*(N+2)/2;

        auto* matrixg = new Matrix(N);
        auto* matrixs6 = new Matrix(N);
        auto* matrixs10 = new Matrix(N);
        auto* matrixs14 = new Matrix(N);
        auto* matrixs6s = new Matrix(N);
        auto* matrixs10s = new Matrix(N);
        auto* matrixs14s = new Matrix(N);

        fill(matrixg);
        fill(matrixs6);
        fill(matrixs10);
        fill(matrixs14);
        fill(matrixs6s);
        fill(matrixs10s);
        fill(matrixs14s);

        if (mtimeg < minSeconds)
        {
            begin = clock();
            gauss( matrixg , true );
            end = clock();
            mtimeg = double(end - begin) / CLOCKS_PER_SEC;
            fp << mtimeg << ";" << multiplication(matrixg,s) << ";";
        }
        else
            fp << "0;0;0;";

        if (mtimes6 < minSeconds)
        {
            begin = clock();
            times=seidelPrec(matrixs6,0.000001);
            end = clock();
            mtimes6 = double(end - begin) / CLOCKS_PER_SEC;
            begin = clock();
            seidel(matrixs6s,times);
            end = clock();
            fp << mtimes6 << ";" << multiplication(matrixs6,s) << ";" << double(end - begin) / CLOCKS_PER_SEC << ";";
        }
        else
            fp << "0;0;0;";

        if (mtimes10 < minSeconds)
        {
            begin = clock();
            times=seidelPrec(matrixs10,0.0000000001);
            end = clock();
            mtimes10 = double(end - begin) / CLOCKS_PER_SEC;
            begin = clock();
            seidel(matrixs10s,times);
            end = clock();
            fp << mtimes10 << ";" << multiplication(matrixs10,s) << ";" << double(end - begin) / CLOCKS_PER_SEC << ";";
        }
        else
            fp << "0;0;0;";

        if (mtimes14 < minSeconds)
        {
            begin = clock();
            times=seidelPrec(matrixs14,0.00000000000001);
            end = clock();
            mtimes14 = double(end - begin) / CLOCKS_PER_SEC;
            begin = clock();
            seidel(matrixs14s,times);
            end = clock();
            fp << mtimes14 << ";" << multiplication(matrixs14,s) << ";" << double(end - begin) / CLOCKS_PER_SEC << ";";
        }
        else
            fp << "0;0;0;";

        delete(matrixg);
        delete(matrixs6);
        delete(matrixs10);
        delete(matrixs14);
        delete(matrixs6s);
        delete(matrixs10s);
        delete(matrixs14s);

        fp << "\n";
    }
    fp.close();
    printf("done\n");
}




#endif
