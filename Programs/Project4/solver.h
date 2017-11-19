#ifndef SOLVER_H
#define SOLVER_H
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include "mpi.h"

using namespace std;
using namespace arma;



class Solver{
private:
    int L=0;
    int MonteCarloCycles = 0;
    int N=1;
    double NSpins;
    int NProcesses;
    int RankProcess;
public:
    Solver(int L_, int MCcycles, int writeIntervall, int NProcesses_, int RankProcess_);

    void algorithm(string folderFilename, vec temperatures, bool randomStart, bool writeEveryMC, bool writeWhenFinish, bool writeForTemp);

    int periodicBC(int i, int limit, int add);
    double randomSpin();
    mat makeMicrostate(int L, bool initialType);
    vec calculateProperties(vec MeanValues, double T);
    double random_nr();

    vec analyticalExpectationValues(double T);

    void writeHeader(ofstream &outfile, int MCcycles, double Temperature, bool Randomstart);
    void writeToFile(vec Means, int NProcesses, double percentAccepted, int &MCcycle, double &T, int L, ofstream &outfile);

    void writeHeaderTemperature(ofstream &outfile);
    void writeToFileTemperature(vec meanValues, int MonteCarloCycles, int NProcesses ,double &T, int NSpins, ofstream &outfile);



};

#endif // SOLVER_H
