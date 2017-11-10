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

using namespace std;
using namespace arma;



class Solver{
private:
    int L=0;
    int MonteCarloCycles = 0;
    int N=1;
public:
    Solver(int L_, int MCcycles, int writeIntervall);

    void algorithm(string folderFilename, vec temperatures, bool randomStart, bool writeEveryMC, bool writeWhenFinish, bool writeForTemp);

    int periodicBC(int i, int limit, int add);
    double randomSpin();
    mat makeMicrostate(int L, bool initialType);
    vec calculateProperties(vec ExpectationValues, double T);

vec analyticalExpectationValues(double T);

void writeToFile(vec Means, int acceptedConfigurations, int &MCcycle, int& TotMCcycles, double &T, int L, ofstream &outfile);


void writeHeader(ofstream &outfile, int MCcycles, double Temperature, bool Randomstart);


 double random_nr();

};
/*
inline double random_nr(){
    return RandomNumberGenerator(gen);}
*/

#endif // SOLVER_H
