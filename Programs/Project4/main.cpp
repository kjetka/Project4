#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <mpi.h>
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


int main(int argc, char* argv[]){

    int NProcesses, RankProcess;
    //   MPI initializations
    MPI_Init(&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &NProcesses);
    MPI_Comm_rank (MPI_COMM_WORLD, &RankProcess);

    int L, MonteCarloCycles, writeResolution, NSpin;

    vec temperatures;
    bool randomStart, writeEveryMC, writeWhenFinish, writeForTemp;


    //----------------------------------------------------
    // EXERCISE B
    //----------------------------------------------------
/*
    L = 2;
    NSpin = L*L;
    MonteCarloCycles = 1e7;
    writeResolution = 1000;
    temperatures = vec({1});

    randomStart = true;
    writeEveryMC = true ;
    writeWhenFinish = false;

    Solver exerciseb(L, MonteCarloCycles, writeResolution);
    exerciseb.algorithm("4b/opgb", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);
*/
    //----------------------------------------------------
    // EXERCISE C
    //----------------------------------------------------
/*
     L = 20;
     NSpin = L*L;
     MonteCarloCycles = 1e7;
     writeResolution = 1000;
     temperatures = vec({1, 2.4});

     randomStart = true;
     writeEveryMC = true ;
     writeWhenFinish = false;
     writeForTemp = false;

    Solver exercisec(L, MonteCarloCycles, writeResolution);
    exercisec.algorithm("4c/c_", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);

    randomStart = false;
    exercisec.algorithm("4c/c_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);
*/

    //----------------------------------------------------
    // EXERCISE D
    //----------------------------------------------------
/*
     L = 20; 
     NSpin = L*L;
     MonteCarloCycles = 1e6;
     writeResolution = 1;
     temperatures = vec({1,2.4});

     randomStart = true;
     writeEveryMC = false ;
     writeWhenFinish = true;
     writeForTemp = false;

    Solver exercised(L, MonteCarloCycles, writeResolution);
    exercised.algorithm("4d/d_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);

*/


    //----------------------------------------------------
    // EXERCISE E
    //----------------------------------------------------

     L = 20;
     NSpin = L*L;
     MonteCarloCycles = 1e6;
     writeResolution = 1;
     temperatures = vec({1,2.4});

     randomStart = true;
     writeEveryMC = false ;
     writeWhenFinish = true;
     writeForTemp = false;

    Solver exercised(L, MonteCarloCycles, writeResolution);
    exercised.algorithm("4d/d_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);


    return 0 ;
}
