#ifndef TestC_h
#define TestC_h

#include "Main.h"

void testC( int minSeconds , int minN )
{
    printf("Test C: ");

    std::ofstream fp;
    fp.open("TestC.csv");
    clock_t begin;
    clock_t end;
    long esizej=0,esizes=0;
    double mtimej=0,mtimes=0,etimej=0,etimes=0;


    fp << ";Jacobi (array);;;Gauss-Seidel (array);;;Jacobi (eigen);;;Gauss-Seidel (eigen)\n";
    fp << "N;time;diff;memory;time;diff;memory;time;diff;memory;time;diff;memory\n";

    for(int N=2;N<minN;N++)
    {
        fp << N << ";";
        int s = (N+1)*(N+2)/2;

        auto* matrixj = new Matrix(N);
        auto* matrixs = new Matrix(N);

        auto* ematrixj = new Eigen::SparseMatrix<double,Eigen::RowMajor>(s,s);
        auto* evectorbj = new Eigen::SparseVector<double>(s);
        auto* evectorxj = new Eigen::SparseVector<double>(s);

        auto* ematrixs = new Eigen::SparseMatrix<double,Eigen::RowMajor>(s,s);
        auto* evectorbs = new Eigen::SparseVector<double>(s);
        auto* evectorxs = new Eigen::SparseVector<double>(s);

        fill(matrixj);
        fill(matrixs);
        eigenfill( ematrixj , evectorbj , N );
        eigenfill( ematrixs , evectorbs , N );

        if (mtimej < minSeconds)
        {
            begin = clock();
            jacobi(matrixj,1000);
            end = clock();
            mtimej = double(end - begin) / CLOCKS_PER_SEC;
            fp << mtimej << ";" << multiplication(matrixj,s) << ";" << matrixj->memorysize() << ";";
        }
        else
            fp << "0;0;0;";

        if (mtimes < minSeconds)
        {
            begin = clock();
            seidel(matrixs,1000);
            end = clock();
            mtimes = double(end - begin) / CLOCKS_PER_SEC;
            fp << mtimes << ";" << multiplication(matrixs,s) << ";" << matrixs->memorysize() << ";";
        }
        else
            fp << "0;0;0;";

        if (etimej < minSeconds)
        {
            begin = clock();
            eigenjacobi( s , ematrixj , evectorbj , evectorxj , 1000 );
            end = clock();
            ematrixj->makeCompressed();
            etimej = double(end - begin) / CLOCKS_PER_SEC;
            esizej = ematrixj->data().size() + evectorbj->data().size() + evectorxj->data().size();
            fp << etimej << ";" << eigenmultiplication(evectorxj,s,N) << ";" << esizej << ";";
        }
        else
            fp << "0;0;0;";

        if (etimes< minSeconds)
        {
            begin = clock();
            eigenseidel( s , ematrixs , evectorbs , evectorxs , 1000 );
            end = clock();
            ematrixs->makeCompressed();
            etimes= double(end - begin) / CLOCKS_PER_SEC;
            esizes = ematrixs->data().size() + evectorbs->data().size() + evectorxs->data().size();
            fp << etimes << ";" << eigenmultiplication(evectorxs,s,N) << ";" << esizes << ";";
        }
        else
            fp << "0;0;0;";

        delete(matrixj);
        delete(matrixs);
        delete(ematrixj);
        delete(evectorbj);
        delete(evectorxj);
        delete(ematrixs);
        delete(evectorbs);
        delete(evectorxs);


        fp << "\n";
    }
    fp.close();
    printf("done\n");
}




#endif
