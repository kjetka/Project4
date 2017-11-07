#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <random>
#include "solver.h"

using namespace std;
using namespace arma;


//void metropolisSampling(int N); //the whole prosess
//void metropolisAlgorithm(mat Matrix);





int main(){

    int L = 2;
    int MonteCarloCycles = 3.5e6;

    Solver test(L, MonteCarloCycles);
    test.algorithm();


    return 0;
}























