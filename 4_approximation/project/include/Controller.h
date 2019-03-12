#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Main.h"

class Controller
{
public:

    Controller();

    void solve(int firstN, int lastN, int stepN);
    void exportTimeData(std::string filename);

    void approximateAll();
    void exportApproximationData(std::string filename);

    void checkDelta();
    void exportDeltaData(std::string filename);

    void predict(int size);
    void exportPredictedData(std::string filename);

    void experiment(std::string filename, int N);


private:

    std::map<int,double> time[8];
    Eigen::VectorXd coefficients[8];
    double delta[8];
    double predictedValue[8];

    Eigen::VectorXd approximate(std::map<int, double>* data, int level) ;

};






#endif
