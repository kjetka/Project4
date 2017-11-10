#include <iostream>
#include <mpi.h>
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

int main(int argc, char* argv[]){

    int numprocs, my_rank;
//   MPI initializations
    MPI_Init(&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);
    cout << "Hello world, I have rank " << my_rank << " out of "
         << numprocs << endl;
    //  End MPI
    MPI_Finalize ();

    /*

    int L = 2;
    int NSpins = L*L;
    int MonteCarloCycles = 1e6;

    double initialTemp = 2.0;
    double finalTemp = 2.3;
    double stepTemp = 0.05;
    vec meanValues = zeros(5);
    ofstream outfile;

    if(RankProcess == 0){
        outfile.open("../../results/4e/4e_results_L2.txt");
        writeHeader(outfile);
    }

    double TimeStart, TimeEnd, TotalTime;
    TimeStart = MPI_Wtime();

    for(double Temperature = initialTemp; Temperature <= finalTemp; Temperature+=stepTemp){

        samplingMonteCarlo(L, MonteCarloCycles, Temperature, meanValues);

        vec TotalMeanValues = zeros(5);

        for( int i =0; i < 5; i++){
            MPI_Reduce(&meanValues[i], &TotalMeanValues[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        }
        if(RankProcess == 0){
            writeToFile(TotalMeanValues, MonteCarloCycles, NProcesses, Temperature, NSpins, outfile);
        }
    }
    if(RankProcess == 0){
        outfile.close();  // close output file
    }
    TimeEnd = MPI_Wtime();
    TotalTime = TimeEnd-TimeStart;
    if ( RankProcess == 0) {
      cout << "Time = " <<  TotalTime  << " on number of processors: "  << NProcesses  << endl;
    }

    MPI_Finalize();
    return 0;
    */
}

