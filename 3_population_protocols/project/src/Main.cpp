//
//  zad3
//
//  Created by Andrzej on 02/12/2018.
//  Copyright © 2018 Andrzej. All rights reserved.
//
//  układ: macierz ( Wiersze , Kolumny )
//  (N+1)*(N+2)/2; // rozmiar macierzy kwadratowej
//

#include "Main.h"

int main(int argc, const char * argv[]) {

    int minSeconds = 500;
    int minN = 100;
    
    testA();
    testB(minSeconds,minN);
    testC(minSeconds,minN);
    testD(minSeconds,minN);
    testE(minSeconds,minN);
    
    return 0;
}
