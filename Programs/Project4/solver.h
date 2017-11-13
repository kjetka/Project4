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
    int NProcesses;
    int RankProcess;
public:
    Solver(int L_, int MCcycles, int writeIntervall, int NProcesses_, int RankProcess_);

    void algorithm(string folderFilename, vec temperatures, bool randomStart, bool writeEveryMC, bool writeWhenFinish, bool writeForTemp);

    int periodicBC(int i, int limit, int add);
    double randomSpin();
    mat makeMicrostate(int L, bool initialType);
    vec calculateProperties(vec ExpectationValues, double T);

vec analyticalExpectationValues(double T);

void writeToFile(vec Means, int NProcesses, int acceptedConfigurations, int &MCcycle, double &T, int L, ofstream &outfile);


void writeHeader(ofstream &outfile, int MCcycles, double Temperature, bool Randomstart);

void writeHeaderTemperature(ofstream &outfile);
void writeToFileTemperature(vec meanValues, int MonteCarloCycles, int NProcesses ,double &T, int NSpins, ofstream &outfile);


 double random_nr();

};
/*
inline double random_nr(){
    return RandomNumberGenerator(gen);}
*/

#endif // SOLVER_H
