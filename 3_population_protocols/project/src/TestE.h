#ifndef TestE_h
#define TestE_h

#include "Main.h"

void testE( int minSeconds , int minN )
{
    printf("Test E: ");

    std::ofstream fp;
    fp.open("TestE.csv");
    clock_t begin;
    clock_t end;
    double timeg=0,timegm=0,timege=0;
    long esize;

    fp << ";Gauss (array matrix);;Gauss (my sparse matrix);;Gauss (eigen sparse matrix)\n";
    fp << "N;time;memory;time;memory;time;memory\n";

    for(int N=2;N<minN;N++)
    {
        fp << N << ";";
        int s = (N+1)*(N+2)/2;

        auto* matrix = new Matrix(N);
        auto* smatrix = new MySparseMatrix(N);

        auto* ematrix = new Eigen::SparseMatrix<double,Eigen::RowMajor>(s,s);
        auto* evectorb = new Eigen::SparseVector<double>(s);
        auto* evectorx = new Eigen::SparseVector<double>(s);


        fill(matrix);
        fill(smatrix);
        eigenfill(ematrix,evectorb,N);

        if (timeg < minSeconds)
        {
            begin = clock();
            gauss( matrix , true );
            end = clock();
            timeg = double(end - begin) / CLOCKS_PER_SEC;
            fp << timeg << ";" << matrix->memorysize() << ";";
        }
        else
            fp << "0;0;";

        if (timegm < minSeconds)
        {
            begin = clock();
            gauss( smatrix , true );
            end = clock();
            timegm = double(end - begin) / CLOCKS_PER_SEC;
            fp << timegm << ";" << smatrix->memorysize() << ";";
        }
        else
            fp << "0;0;";

        if (timege < minSeconds)
        {
            begin = clock();
            calculateEGP( s , ematrix , evectorb , evectorx , true );
            end = clock();
            ematrix->makeCompressed();
            timege = double(end - begin) / CLOCKS_PER_SEC;
            esize = ematrix->data().size() + evectorb->data().size() + evectorx->data().size();
            fp << timege << ";" << esize << ";";
        }
        else
            fp << "0;0;";

        delete(matrix);
        delete(smatrix);
        delete(ematrix);
        delete(evectorb);
        delete(evectorx);


        fp << "\n";
    }
    fp.close();
    printf("done\n");
}




#endif
