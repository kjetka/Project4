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

    // if true -> the matrix of spins are initialized
    // with random spin oriatation
    // if false -> ordered spin orientation
    bool randomStart;

    // these tests defines when and what you want to print
    // true -> print and false -> don't print
    bool writeEveryMC, writeWhenFinish, writeForTemp;

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
/*
       L = 20;
       MonteCarloCycles = 1e6;
       writeResolution = 1000;
       //temperatures = vec({1, 2.4});
       temperatures = vec({1, 2.4});

       randomStart = false;
       writeEveryMC = true ;
       writeWhenFinish = false;
       writeForTemp = false;

      Solver exercisec(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
      exercisec.algorithm("4c/c_", temperatures,randomStart,  writeEveryMC, writeWhenFinish, writeForTemp);

     // randomStart = false;
     // exercisec.algorithm("4c/c_", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);
*/
    //----------------------------------------------------
    // EXERCISE D
    //----------------------------------------------------


         L = 20;
         MonteCarloCycles = 1e6;
         writeResolution = 1;
         temperatures = vec({1});

         randomStart = true;
         writeEveryMC = false ;
         writeWhenFinish = true;
         writeForTemp = false;

        Solver exercised(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
        exercised.algorithm("4d/d_T_1", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);

        temperatures = vec({2.4});
        exercised.algorithm("4d/d_T_2_4", temperatures,randomStart,   writeEveryMC, writeWhenFinish, writeForTemp);



    //----------------------------------------------------
    // EXERCISE E
    //----------------------------------------------------

/*
    //vec Ls = vec({40, 60, 80, 100});

    MonteCarloCycles = 0.5e6; //must be much smaller than the thermalization time
    writeResolution = 1;
    //temperatures = linspace<vec>(2.0, 2.3, 15);
    //temperatures = linspace<vec>(2.15, 2.75, 25);
    //temperatures = vec({2.1, 2.2,2.23,2.25,2.26, 2.265,2.27,2.275, 2.278, 2.279, 2.28, 2.281,2.282,2.283,2.284, 2.285,2.286, 2.287,2.288,2.289, 2.29,2.30,2.32,2.35,2.38,2.4,2.45,2.5,2.55,2.6});

    //Timing run
    temperatures = vec({2,2,2.3,2.4,2.5});
    vec Ls = vec({100});

    randomStart = true;
    writeEveryMC = false ;
    writeWhenFinish = false;
    writeForTemp = true;

    for(int i = 0; i < Ls.size(); i ++){
        L = Ls[i];

        Solver exercisee(L, MonteCarloCycles, writeResolution, NProcesses, RankProcess);
        string name = "4e/timerun" + to_string(L);
        exercisee.algorithm(name, temperatures,randomStart, writeEveryMC, writeWhenFinish, writeForTemp);

    }
*/
    // End timing
    TimeEnd = MPI_Wtime();
    TotalTime = TimeEnd-TimeStart;
/*
    if ( RankProcess == 0) {
        cout << "Time = " <<  TotalTime  << " on number of processors: "  << NProcesses  << endl;

        ofstream outfiletime;
        outfiletime.open("../../results/4e/timing.txt");
        outfiletime << "Number of processors: "  << NProcesses  << " Time: " <<TotalTime<<endl;
        outfiletime << "Number of temperatures: "  << temperatures.size()  <<endl;
        outfiletime << "MonteCarlo per thread: "  << MonteCarloCycles  <<endl;
        outfiletime.close();
    }
    */
    MPI_Finalize();
    return 0;
}
