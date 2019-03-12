#include "Main.h"

Controller::Controller() = default;

void Controller::solve(int firstN, int lastN, int stepN)
{
    int size;
    double begin, end;

    for(int N=firstN; N<=lastN; N+=stepN)
    {
        size = (N+1)*(N+2)/2;

        begin = clock();
        auto* matrixGauss = new ArrayMatrix(N);
        matrixGauss->fill();
        end = clock();
        time[0][size] = (end - begin) / CLOCKS_PER_SEC;

        auto* matrixUpgradedGauss = new ArrayMatrix(N);
        matrixUpgradedGauss->fill();

        auto* matrixGaussSeidel = new ArrayMatrix(N);
        matrixGaussSeidel->fill();

        begin = clock();
        auto* matrixEigen = new EigenMatrix(N);
        matrixEigen->fill();
        end = clock();
        time[1][size] = (end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        auto* matrixVectorMap = new VectorMapMatrix(N);
        matrixVectorMap->fill();
        end = clock();
        time[2][size] = (end - begin) / CLOCKS_PER_SEC;

        // =========================================

        begin = clock();
        matrixGauss->gauss(false);
        end = clock();
        time[3][size] = (end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        matrixUpgradedGauss->gauss(true);
        end = clock();
        time[4][size] = (end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        matrixEigen->sparseLU();
        end = clock();
        time[5][size] = (end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        matrixGaussSeidel->seidel(0.0000000001,matrixEigen);
        end = clock();
        time[6][size] = (end - begin) / CLOCKS_PER_SEC;

        begin = clock();
        matrixVectorMap->seidel(0.0000000001,matrixEigen);
        end = clock();
        time[7][size] = (end - begin) / CLOCKS_PER_SEC;

        delete matrixGauss;
        delete matrixUpgradedGauss;
        delete matrixEigen;
        delete matrixGaussSeidel;
        delete matrixVectorMap;
    }
}

void Controller::exportTimeData(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    file << "size;building ArrayMatrix;building EigenMatrix;building VectorMapMatrix;solving Gauss;solving UpgradedGauss;solving Eigen;solving GaussSeidel;solving VectorMapMatrix\n";

    for (auto &i : time[0]) {
        file << i.first << ";" << time[0][i.first] << ";" << time[1][i.first] << ";" << time[2][i.first] << ";" << time[3][i.first];
        file << ";" << time[4][i.first] << ";" << time[5][i.first] << ";" << time[6][i.first] << ";" << time[7][i.first] << "\n";
    }
    file.close();
}

void Controller::approximateAll()
{
    coefficients[0] = approximate(&time[0],2);
    coefficients[1] = approximate(&time[1],2);
    coefficients[2] = approximate(&time[2],2);

    coefficients[3] = approximate(&time[3],3);
    coefficients[4] = approximate(&time[4],2);
    coefficients[5] = approximate(&time[5],1);
    coefficients[6] = approximate(&time[6],2);
    coefficients[7] = approximate(&time[7],2);
}

Eigen::VectorXd Controller::approximate(std::map<int, double>* data, int level)
{
    int n = int(data->size());
    Eigen::SparseMatrix<double> a(level+1,level+1);
    Eigen::VectorXd b(level+1);
    Eigen::VectorXd x;
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    double arguments[n];
    double values[n];
    std::map<int, double>::iterator itr;
    int i=0;
    for (auto &element : *data)
    {
        arguments[i] = element.first;
        values[i] = element.second;
        i++;
    }
    Eigen::VectorXd temp(level * 2 + 1);
    for (int k = 0; k < level * 2 + 1; k++)
    {
        temp[k] = 0;
        for (int i = 0; i < n; i++)
            temp[k] += pow(arguments[i], k);
    }
    for (int i = 0; i < level + 1; i++)
        for (int j = 0; j < level + 1; j++)
            a.coeffRef(i, j) = temp[i + j];

    for (int k = 0; k < level+1; k++)
    {
        b.coeffRef(k) = 0;
        for (int i = 0; i < n; i++)
            b.coeffRef(k) += values[i] * pow(arguments[i], k);
    }
    temp.resize(0);
    solver.compute(a);
    x = solver.solve(b);
    a.resize(0,0);
    b.resize(0);
    return x;
}
void Controller::exportApproximationData(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    file << "Name;*x^0;*x^1;*x^2;*x^3\n";
    file << "Array Building;" << coefficients[0][0] << ";" << coefficients[0][1] << ";" << coefficients[0][2] << "\n";
    file << "Eigen Building;" << coefficients[1][0] << ";" << coefficients[1][1] << ";" << coefficients[1][2] << "\n";
    file << "VectorMap Building;" << coefficients[2][0] << ";" << coefficients[2][1] << ";" << coefficients[2][2] << "\n";
    file << "Gauss solving;" << coefficients[3][0] << ";" << coefficients[3][1] << ";" << coefficients[3][2] << ";" << coefficients[3][3] << "\n";
    file << "Upgraded Gauss solving;" << coefficients[4][0] << ";" << coefficients[4][1] << ";" << coefficients[4][2] << "\n";
    file << "Eigen solving;" << coefficients[5][0] << ";" << coefficients[5][1] << "\n";
    file << "Seidel solving;" << coefficients[6][0] << ";" << coefficients[6][1] << ";" << coefficients[6][2] << "\n";
    file << "VectorMap solving;" << coefficients[7][0] << ";" << coefficients[7][1] << ";" << coefficients[7][2] << "\n";
    file.close();
}

void Controller::checkDelta()
{
    double functionValue, x;

    for (auto &element : time[0])
    {
        x = element.first;
        functionValue = coefficients[0][0] + x * coefficients[0][1] + x * x * coefficients[0][2];
        delta[0] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[0] = delta[0] / double(time[0].size());
    for (auto &element : time[1])
    {
        x = element.first;
        functionValue = coefficients[1][0] + x * coefficients[1][1] + x * x * coefficients[1][2];
        delta[1] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[1] = delta[1] / double(time[1].size());
    for (auto &element : time[2])
    {
        x = element.first;
        functionValue = coefficients[2][0] + x * coefficients[2][1] + x * x * coefficients[2][2];
        delta[2] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[2] = delta[2] / double(time[2].size());
    for (auto &element : time[3])
    {
        x = element.first;
        functionValue = coefficients[3][0] + x * coefficients[3][1] + x * x * coefficients[3][2] + x * x * x * coefficients[3][3];
        delta[3] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[3] = delta[3] / double(time[3].size());
    for (auto &element : time[4])
    {
        x = element.first;
        functionValue = coefficients[4][0] + x * coefficients[4][1] + x * x * coefficients[4][2];
        delta[4] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[4] = delta[4] / double(time[4].size());
    for (auto &element : time[5])
    {
        x = element.first;
        functionValue = coefficients[5][0] + x * coefficients[5][1];
        delta[5] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[5] = delta[5] / double(time[5].size());
    for (auto &element : time[6])
    {
        x = element.first;
        functionValue = coefficients[6][0] + x * coefficients[6][1] + x * x * coefficients[6][2];
        delta[6] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[6] = delta[6] / double(time[6].size());
    for (auto &element : time[7])
    {
        x = element.first;
        functionValue = coefficients[7][0] + x * coefficients[7][1] + x * x * coefficients[7][2];
        delta[7] += abs(abs(functionValue - element.second) / functionValue); // relative difference
    }
    delta[7] = delta[7] / double(time[7].size());
}
void Controller::exportDeltaData(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    file << "Name;delta\n";
    file << "Array Building;" << delta[0] << "\n";
    file << "Eigen Building;" << delta[1] << "\n";
    file << "VectorMap Building;" << delta[2] << "\n";
    file << "Gauss solving;" << delta[3] << "\n";
    file << "Upgraded Gauss solving;" << delta[4] << "\n";
    file << "Eigen solving;" << delta[5] << "\n";
    file << "Seidel solving;" << delta[6] << "\n";
    file << "VectorMap solving;" << delta[7] << "\n";
    file.close();
}

void Controller::predict(int size)
{
    double x=size;

    predictedValue[0] = coefficients[0][0] + x * coefficients[0][1] + x * x * coefficients[0][2];
    predictedValue[1] = coefficients[1][0] + x * coefficients[1][1] + x * x * coefficients[1][2];
    predictedValue[2] = coefficients[2][0] + x * coefficients[2][1] + x * x * coefficients[2][2];
    predictedValue[3] = coefficients[3][0] + x * coefficients[3][1] + x * x * coefficients[3][2] + x * x * x * coefficients[3][3];
    predictedValue[4] = coefficients[4][0] + x * coefficients[4][1] + x * x * coefficients[4][2];
    predictedValue[5] = coefficients[5][0] + x * coefficients[5][1];
    predictedValue[6] = coefficients[6][0] + x * coefficients[6][1] + x * x * coefficients[6][2];
    predictedValue[7] = coefficients[7][0] + x * coefficients[7][1] + x * x * coefficients[7][2];
}
void Controller::exportPredictedData(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    file << "Name;predicted time\n";
    file << "Array Building;" << predictedValue[0] << "\n";
    file << "Eigen Building;" << predictedValue[1] << "\n";
    file << "VectorMap Building;" << predictedValue[2] << "\n";
    file << "Gauss solving;" << predictedValue[3] << "\n";
    file << "Upgraded Gauss solving;" << predictedValue[4] << "\n";
    file << "Eigen solving;" << predictedValue[5] << "\n";
    file << "Seidel solving;" << predictedValue[6] << "\n";
    file << "VectorMap solving;" << predictedValue[7] << "\n";
    file.close();
}
void Controller::experiment(std::string filename, int N)
{
    double begin, end;
    std::ofstream file;
    file.open(filename);
    file << "Name;Eigen SparseLU\n";
    file << "size;" << (N+1)*(N+2)/2 << "\n";

    auto* matrixEigen = new EigenMatrix(N);
    matrixEigen->fill();

    begin = clock();
    matrixEigen->sparseLU();
    end = clock();

    file << "real time;" << (end - begin) / CLOCKS_PER_SEC << "\n";

    file << "Name;VectorMap Seidel\n";
    file << "size;" << (N+1)*(N+2)/2 << "\n";

    auto* matrixVectorMap = new VectorMapMatrix(N);
    matrixVectorMap->fill();

    begin = clock();
    matrixVectorMap->seidel(0.0000000001,matrixEigen);
    end = clock();

    file << "real time;" << (end - begin) / CLOCKS_PER_SEC << "\n";

    file.close();
}