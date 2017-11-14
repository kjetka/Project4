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
#include "mpi.h"
using namespace std;
using namespace arma;


int main(int argc, char* argv[]){

    int NProcesses, RankProcess;
    //   MPI initializations
    MPI_Init(&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &NProcesses);
    MPI_Comm_rank (MPI_COMM_WORLD, &RankProcess);

    int L, MonteCarloCycles, writeResolution;

    vec temperatures;
    bool randomStart, writeEveryMC, writeWhenFinish, writeForTemp;

    double TimeStart, TimeEnd, TotalTime;
    TimeStart = MPI_Wtime();

    //----------------------------------------------------
    // EXERCISE B
    //----------------------------------------------------

    //    L = 2;
    //    MonteCarloCycles = 1e6;
    //    writeResolution = 1000;
    //    temperatures = vec({1});

    //    randomStart = true;
    //    writeEveryMC = true ;
    //    writeWhenFinish = false;
    //    writeForTemp = false;

    //    Solver exerciseb(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
    //    exerciseb.algorithm("4b/b_", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);



    //----------------------------------------------------
    // EXERCISE C
    //----------------------------------------------------

       L = 20;
       MonteCarloCycles = 0.5e4;
       writeResolution = 1000;
       temperatures = vec({1, 2.4});

       randomStart = true;
       writeEveryMC = true ;
       writeWhenFinish = false;
       writeForTemp = false;

      Solver exercisec(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
      exercisec.algorithm("4c/c_test2_", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);

     // randomStart = false;
     // exercisec.algorithm("4c/c_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);

    //----------------------------------------------------
    // EXERCISE D
    //----------------------------------------------------

    //     L = 20;
    //     MonteCarloCycles = 1e6;
    //     writeResolution = 1;
    //     temperatures = vec({1,2.4});

    //     randomStart = true;
    //     writeEveryMC = false ;
    //     writeWhenFinish = true;
    //     writeForTemp = false;

    //    Solver exercised(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
    //    exercised.algorithm("4d/d_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);


    //----------------------------------------------------
    // EXERCISE E
    //----------------------------------------------------

/*
    //vec Ls = vec({40, 60, 80, 100});
    vec Ls = vec({5, 10});

    MonteCarloCycles = 0.5e6;
    writeResolution = 1;
    temperatures = linspace<vec>(2.0, 2.3, 15);
    //temperatures = linspace<vec>(2.15, 2.75, 25);
    temperatures = vec({2.1,2.15,2.2,2.23,2.25,2.27,2.28,2.30,2.32,2.34,2.36,2.38,2.4,2.45,2.5,2.55,2.6,2.65,2.7});

    cout << temperatures.size()<<endl;


    randomStart = true;
    writeEveryMC = false ;
    writeWhenFinish = false;
    writeForTemp = true;

    for(int i = 0; i < Ls.size(); i ++){
        L = Ls[i];

        Solver exercisee(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
        string name = "4e/e_L_" + to_string(L);
        exercisee.algorithm(name, temperatures,randomStart, writeEveryMC, writeWhenFinish, writeForTemp);

    }
    // End timing
    TimeEnd = MPI_Wtime();
    TotalTime = TimeEnd-TimeStart;

    if ( RankProcess == 0) {
        cout << "Time = " <<  TotalTime  << " on number of processors: "  << NProcesses  << endl;
    }

*/
    MPI_Finalize();
    return 0;
}

















