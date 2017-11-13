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

    //     L = 20;
    //     MonteCarloCycles = 1e5;
    //     writeResolution = 1000;
    //     temperatures = vec({1, 2.4});

    //     randomStart = true;
    //     writeEveryMC = true ;
    //     writeWhenFinish = false;
    //     writeForTemp = false;

    //    Solver exercisec(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
    //    exercisec.algorithm("4c/c_", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);

    //    randomStart = false;
    //    exercisec.algorithm("4c/c_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);

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

    //vec Ls = vec({40, 60, 80, 100});
    vec Ls = vec({5, 10});

    MonteCarloCycles = 1e3;
    writeResolution = 1;
    temperatures = linspace<vec>(2.0, 2.3, 6);

    for (int i =0;i<size(temperatures)[0]; i++)
        cout << temperatures[i]<<endl;

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

    MPI_Finalize();
    return 0;
}

















