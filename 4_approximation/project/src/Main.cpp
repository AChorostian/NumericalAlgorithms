//
//  zad4 - Aproksymacja
//
//  Created by Andrzej Chorostian on 16/01/2019.
//  Copyright © 2019 Andrzej Chorostian. All rights reserved.
//

#include "Main.h"

int main(int argc, const char * argv[])
{
    Controller controller;

    controller.solve(20,100,5);
    controller.exportTimeData("timedata.csv");

    controller.approximateAll();
    controller.exportApproximationData("approxdata.csv");

    controller.checkDelta();
    controller.exportDeltaData("deltadata.csv");

    controller.predict( (700+1)*(700+2)/2 );
    controller.exportPredictedData("predicteddata.csv");

    controller.experiment("experiment.csv" , 700);


    return 0;
}
