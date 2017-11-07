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


//void metropolisSampling(int N); //the whole prosess
//void metropolisAlgorithm(mat Matrix);





int main(){

    int L = 20;
    int MonteCarloCycles = 1e5;

    Solver test(L, MonteCarloCycles);
    test.algorithm();


    mat Microstate = makeMicrostate(L, false); // initialType: true -> random spins | false -> ordered spins
    //mat Microstate = makeMicrostate(L, false);
    string initial_type = "_";
    //string initial_type = "_random_";
// can use 'set' instead of 'vector' - should take less time
    vector<int> listOfEnergies;
            listOfEnergies.reserve(200);
    vector<int> listOfProbabilityEnergies;
            listOfProbabilityEnergies.reserve(200);
    int numberOfEnergies;

    // Speedup: when calc many temperatures - use converged state from last Temp as starting microstate
    vec temperatures = vec({2.4});










            }
            meanValues[0] += Energy;
            meanValues[1] += Energy*Energy;
            meanValues[2] += MagneticMoment;
            meanValues[3] += MagneticMoment*MagneticMoment;
            meanValues[4] += fabs(MagneticMoment);


            // Counting the different energies to find probability
            if (find(listOfEnergies.begin(),listOfEnergies.end(),Energy) != listOfEnergies.end()){
                int i = find(listOfEnergies.begin(), listOfEnergies.end(), Energy) - listOfEnergies.begin();
                listOfProbabilityEnergies[i] +=1;
            }else{
                listOfEnergies.push_back(Energy);
                numberOfEnergies +=1;
                listOfProbabilityEnergies.push_back(1);
            }
            //cout << numberOfEnergies << endl;
/*
            if (MC % N == 0 || MC == 1){ // writes every Nth value to file
                writeToFile(meanValues, acceptedConfigurations, MC, MonteCarloCycles, Temperature, L, outfile);
            }
*/
            meanValues[0] += Energy;
            meanValues[1] += Energy*Energy;
            meanValues[2] += MagneticMoment;
            meanValues[3] += MagneticMoment*MagneticMoment;
            meanValues[4] += fabs(MagneticMoment);


            //writeToFile(meanValues, MC, MonteCarloCycles, Temperature, L, outfile);




    }
    ofstream outfile2;
    outfile2.open("../../results/4d/probability.txt");
    outfile2 << "Energy:" << "\t"<< "Probability:"<< endl;
            for(int i = 0; i<=listOfEnergies.size(); i++){
        outfile2 << listOfEnergies[i] << "\t" << listOfProbabilityEnergies[i] << endl;
    }
    outfile2.close();
}




