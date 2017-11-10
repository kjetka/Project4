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
}


void samplingMonteCarlo(int L, int MonteCarloCycles, double Temperature, vec &meanValues){
    double Energy = 0;
    double MagneticMoment = 0;

    mat Microstate = makeMicrostate(L, false); // initialType: true -> random spins | false -> ordered spins

    for(int x =0; x < L; x++) {
        for (int y = 0; y < L; y++){
            Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
            MagneticMoment +=Microstate(x,y);
        }
    }
    vec Acceptance = zeros<mat>(17);

    for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);
    int acceptedConfigurations = 0;
    for(int MC =1; MC<MonteCarloCycles; MC++){
        for (int xy =0; xy<L*L;xy++){
            // Flipping state ix,iy
            // QUESTION
            int ix =random_nr()*L;
            int iy = random_nr()*L;
            // This is slow, as periodicBC has an if else loop...
            int dE =  2*Microstate(ix,iy)*(
                        Microstate(ix , periodicBC(iy,L,1) )
                        + Microstate(ix , periodicBC(iy,L,-1))
                        + Microstate(periodicBC(ix,L,1),  iy)
                        + Microstate(periodicBC(ix,L,-1), iy)    );

            // Very slow!
            double probability = Acceptance(dE + 8);
            if (random_nr() <= probability){
                acceptedConfigurations += 1;
                Microstate(ix,iy) *= - 1;
                Energy += dE;
                MagneticMoment += 2*Microstate(ix,iy);

            }

        }
        meanValues[0] += Energy;
        meanValues[1] += Energy*Energy;
        meanValues[2] += MagneticMoment;
        meanValues[3] += MagneticMoment*MagneticMoment;
        meanValues[4] += fabs(MagneticMoment);
    }
}

vec calculateProperties(vec ExpectationValues, double T){
    double beta = 1.0/T;
    vec calculatedValues = zeros(2);
    calculatedValues[0] = beta*(ExpectationValues[3] - ExpectationValues[4]*ExpectationValues[4]); // X (using <|M|>)
    calculatedValues[1] = beta*beta*(ExpectationValues[1] - ExpectationValues[0]*ExpectationValues[0]); // Cv unit: [k]++
    return calculatedValues;
}

double randomSpin(){
    double number =  (double) (RandomNumberGenerator(gen));
    if(number>0.5) number = 1;
    else number = -1;
    return number;
}

mat makeMicrostate(int L, bool initialType){ // initialType: true -> random spins | false -> ordered spins
    mat microstate = ones<mat>(L,L);
    if(initialType == true){
        for (int j=0;j<L;j++){
            for (int i =0;i<L;i++){
                microstate(i,j) = randomSpin();

            }
        }
    }
    return microstate;
}


void writeToFile(vec meanValues, int MonteCarloCycles, int NProcesses ,double &T, int NSpins, ofstream &outfile){

    outfile << T << "\t\t";
    double norm=(double) MonteCarloCycles*NProcesses;
    double Spins=(double) NSpins;
    meanValues = meanValues/norm;

    vec meanValues_Cv_X = calculateProperties(meanValues, T);

    outfile << meanValues[0]/Spins << "\t" << meanValues[4]/Spins << "\t\t";
    outfile << meanValues_Cv_X[0]/Spins << "\t" << meanValues_Cv_X[1]/Spins << "\t";
    outfile << endl;
}

void writeHeader(ofstream &outfile){
    outfile << "Temperatures \t <E> \t\t <|M|> \t\t X \t\t Cv" <<endl;
}

