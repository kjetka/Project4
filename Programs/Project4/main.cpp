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
#include "solver.h"
using namespace std;
using namespace arma;



//void metropolisSampling(int N); //the whole prosess
//void metropolisAlgorithm(mat Matrix);






//void algorithm(int L, int MonteCarloCycles, vec temperatures,  str filename);


int main(){
    int L, MonteCarloCycles, writeResolution;

    vec temperatures;
    bool randomStart, writeEveryMC, writeWhenFinish;


/*
    L = 2;
    MonteCarloCycles = 1e7;
    writeResolution = 1000;
    temperatures = vec({1});

    randomStart = true;
    writeEveryMC = true ;
    writeWhenFinish = false;

    Solver opgb(L, MonteCarloCycles, writeResolution);
    opgb.algorithm("4b/opgb", temperatures,randomStart,  writeEveryMC, writeWhenFinish);
*/
    //----------------------------------------------------
    // OPG C
    //----------------------------------------------------


    /*
     L = 20;
     MonteCarloCycles = 1e6;
     writeResolution = 1000;
     temperatures = vec({1, 2.4});

     randomStart = true;
     writeEveryMC = true ;
     writeWhenFinish = false;

    Solver opgc(L, MonteCarloCycles, writeResolution);
    opgc.algorithm("4c/c_", temperatures,randomStart,  writeEveryMC, writeWhenFinish);

    randomStart = false;
    opgc.algorithm("4c/c_", temperatures,randomStart,  writeEveryMC, writeWhenFinish);

    */


    //----------------------------------------------------
    // OPG D
    //----------------------------------------------------
/*
     L = 20;
     MonteCarloCycles = 1e6;
     writeResolution = 1;
     temperatures = vec({1,2.4});

     randomStart = true;
     writeEveryMC = false ;
     writeWhenFinish = true;

    Solver opgc(L, MonteCarloCycles, writeResolution);
    opgc.algorithm("4d/d_", temperatures,randomStart,  writeEveryMC, writeWhenFinish);

*/





    return 0 ;
}

















