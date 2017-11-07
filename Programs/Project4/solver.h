#ifndef SOLVER_H
#define SOLVER_H
#include <ctime>
#include <ratio>
#include <chrono>
#include <cmath>
#include <armadillo>
#include <random>

using namespace arma;
using namespace std;

random_device rd;
mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);



class Solver{

private:
    int MCcycles=0;
    int L=0;

public:
   Solver(int L_, int MCcycles_);

   double randomSpin();

   mat makeMicrostate(int L, bool initialType);
   void writeToFile(vec Means, int acceptedConfigurations, int &MCcycle, int &TotMCcycles , double& T, int L,  ofstream &outfile);
   void writeHeader(ofstream &outfile, int MCcycles );
   vec analyticalExpectationValues(double T);
   vec calculateProperties(vec meanValues, double T);

   int periodicBC(int i, int limit, int add);
   void algorithm();


};

/*
inline double random_nr(){
     return RandomNumberGenerator(gen);}
*/

#endif // SOLVER_H
