#ifndef MonteCarlo_h
#define MonteCarlo_h

#include "Main.h"

class MonteCarlo
{
public:
    MonteCarlo( int n )
    {
        this->n = n;
        this->size = (n+1)*(n+2)/2;
        this->results = new double[size];
    }
    void experiment( int times , bool debug )
    {
        int x=0;
        for(int yes=0; yes<=n ; yes++)
        {
            for(int no=0; no<=n-yes ; no++)
            {
                int sum=0;
                for(int t=0; t<times; t++)
                {
                    // dane: no , yes , n
                    int rno=no;
                    int ryes=yes;
                    int rn=n;
                    if (debug) std:: cout << "proba nr " << t+1 << " (" << yes << "," << no << ")\n";
                    while (rno != rn && ryes != rn)
                    {
                        if (rno==0 && ryes==0) break;
                        if (debug) std::cout<< "    rn: " << rn << " ryes: " << ryes << " rno: " << rno;
                        int r = myrand(rn);
                        if (r <= rno)
                        {
                            if (debug==true) std::cout<< " wylosowalem " << r ;
                            rno--;
                            rn--;
                            int r = myrand(rn);
                            if (r <= rno)
                            {
                                // no no
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                rno++;
                            }
                            else if (r >rno && r<=rno+ryes)
                            {
                                // no yes
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                ryes--;
                            }
                            else
                            {
                                // no u
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                rno+=2;
                            }
                        }
                        else if (r >rno && r<=rno+ryes)
                        {
                            if (debug==true) std::cout<< "wylosowalem " << r ;
                            ryes--;
                            rn--;
                            int r = myrand(rn);
                            if (r <= rno)
                            {
                                // yes no
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                rno--;
                            }
                            else if (r >rno && r<=rno+ryes)
                            {
                                // yes yes
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                ryes++;
                            }
                            else
                            {
                                // yes u
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                ryes+=2;
                            }
                        }
                        else
                        {
                            if (debug==true) std::cout<< "wylosowalem " << r ;
                            rn--;
                            int r = myrand(rn);
                            if (r <= rno)
                            {
                                // u no
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                rno++;
                            }
                            else if (r >rno && r<=rno+ryes)
                            {
                                // u yes
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                                ryes++;
                            }
                            else
                            {
                                // u u
                                if (debug==true) std::cout<< " i " << r << "\n";
                                rn++;
                            }
                        }
                    }
                    
                    if ( ryes == rn )
                        sum++;
                    
                }
                results[x] = double(sum) / double(times);
                x++;
            }
        }
    }
    double getResult( int i )
    {
        return results[i];
    }
    void print()
    {
        for (int i=0; i<size ; i++)
        {
            printf("|    %.5f",results[i]);
        }
    }
private:

    int myrand( int max )
    {
        auto randy = std::bind(std::uniform_int_distribution<>(1, max), std::mt19937(clock()));
        return randy();
    }
    
    int n;
    int size;
    
    double *results;
    
};



#endif
