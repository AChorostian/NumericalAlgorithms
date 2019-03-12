#ifndef TestB_h
#define TestB_h

#include "Main.h"

void testB( int minSeconds , int minN )
{
    printf("Test B: ");

    std::ofstream fp;
    fp.open("TestB.csv");
    clock_t begin;
    clock_t end;
    long esizes=0,esizef=0;
    double mtimes=0,mtimef=0,etimes=0,etimef=0;


    fp << ";Gauss slow (array);;;Gauss fast (array);;;Gauss slow (eigen);;;Gauss fast (eigen)\n";
    fp << "N;time;diff;memory;time;diff;memory;time;diff;memory;time;diff;memory\n";

    for(int N=2;N<minN;N++)
    {
        fp << N << ";";
        int s = (N+1)*(N+2)/2;

        auto* matrixs = new Matrix(N);
        auto* matrixf = new Matrix(N);

        auto* ematrixs = new Eigen::SparseMatrix<double,Eigen::RowMajor>(s,s);
        auto* evectorbs = new Eigen::SparseVector<double>(s);
        auto* evectorxs = new Eigen::SparseVector<double>(s);

        auto* ematrixf = new Eigen::SparseMatrix<double,Eigen::RowMajor>(s,s);
        auto* evectorbf = new Eigen::SparseVector<double>(s);
        auto* evectorxf = new Eigen::SparseVector<double>(s);

        fill(matrixs);
        fill(matrixf);
        eigenfill( ematrixs , evectorbs , N );
        eigenfill( ematrixf , evectorbf , N );

        if (mtimes < minSeconds)
        {
            begin = clock();
            gauss(matrixs, false);
            end = clock();
            mtimes = double(end - begin) / CLOCKS_PER_SEC;
            fp << mtimes << ";" << multiplication(matrixs,s) << ";" << matrixs->memorysize() << ";";
        }
        else
            fp << "0;0;0;";
        delete(matrixs);

        if (mtimef < minSeconds)
        {
            begin = clock();
            gauss(matrixf, true);
            end = clock();
            mtimef = double(end - begin) / CLOCKS_PER_SEC;
            fp << mtimef << ";" << multiplication(matrixf,s) << ";" << matrixf->memorysize() << ";";
        }
        else
            fp << "0;0;0;";
        delete(matrixf);

        if (etimes < minSeconds)
        {
            begin = clock();
            calculateEGP( s , ematrixs , evectorbs , evectorxs , false );
            end = clock();
            ematrixs->makeCompressed();
            etimes = double(end - begin) / CLOCKS_PER_SEC;
            esizes = ematrixs->data().size() + evectorbs->data().size() + evectorxs->data().size();
            fp << etimes << ";" << eigenmultiplication(evectorxs,s,N) << ";" << esizes << ";";
        }
        else
            fp << "0;0;0;";
        delete(ematrixs);
        delete(evectorbs);
        delete(evectorxs);

        if (etimef < minSeconds)
        {
            begin = clock();
            calculateEGP( s , ematrixf , evectorbf , evectorxf , true );
            end = clock();
            ematrixf->makeCompressed();
            etimef = double(end - begin) / CLOCKS_PER_SEC;
            esizef = ematrixf->data().size() + evectorbf->data().size() + evectorxf->data().size();
            fp << etimef << ";" << eigenmultiplication(evectorxf,s,N) << ";" << esizef << ";";
        }
        else
            fp << "0;0;0;";
        delete(ematrixf);
        delete(evectorbf);
        delete(evectorxf);

        fp << "\n";
    }
    fp.close();
    printf("done\n");
}




#endif
