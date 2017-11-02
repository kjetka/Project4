#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>
#include <random>

using namespace std;
using namespace arma;


void metropolisSampling(int N); //the whole prosess
void metropolisAlgorithm(mat Matrix);
mat makeMatrix();

std::random_device rd;
std::mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

double random_();
void random_pos(int &ix, int &iy, double size_matrix);

mat makeMicrostate(int L);
int periodicBC(int i, int limit, int add){
    if ((i+add)>=limit) return 0;
    else return i+add;
}

int main(){
    int ix,iy;
    // Initialize matrix
    //int spinn = random_();
    int L = 2;
    mat Microstate = makeMicrostate(L);

    vec temperatures = vec({1.0, 2.4});
    int MonteCarloCycles = 2;

    double Energi_state = 0;
    for(int x =0; x < L; x++) {
      for (int y = 0; y < L; y++){
          Energi_state -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
      }
    }



    //for(int i = 0; i<temperatures.size();i++){
    double Temperature =temperatures[0];
    vec EnergyDifference = zeros<mat>(17);
    for( int de =-8; de <= 8; de+=4) EnergyDifference(de+8) = exp(-de/Temperature);

        //vec Expectationvalues = zeros<vec>(5);
    for(int MC =1; MC<MonteCarloCycles; MC++){
        int local_dEnergy = 0;
        random_pos( ix,  iy, L);
        Microstate(ix,iy) = - Microstate(ix,iy);

        /*
        for(int x =0; x < L; x++) {
          for (int y = 0; y < L; y++){

              //Microstate(x,y) = random_(); //Brute force  - alt 1 lecture notes Kjetil
          }
        }*/

          }





        /*
        double E = 0;
        double M = 0;
        double M2 = 0;
        double E2 = 0;
        double sups = 0;
        double E_tot = 0;

        for(int i = 0; i <= MonteCarloCycles; i++){
            metropolisSampling(N);
            E += E;
        }
        E_tot = (1.0/MonteCarloCycles)*E;
        */





    return 0;
}

double random_(){
    double number =  (double) (RandomNumberGenerator(gen));
    if(number>0.5) number = 1;
    else number = -1;
    return number;
}

void random_pos(int& ix, int &iy, double size_matrix){
    ix = RandomNumberGenerator(gen)*size_matrix;
    iy =  RandomNumberGenerator(gen)*size_matrix;
}

void metropolisSampling(int N){
    //Matrix = makeMatrix(N);
    //suggest a new move
    //metropolisAlgorithm(Matrix);
    //update averages
}

mat makeMicrostate(int L){
    mat microstate = ones<mat>(L,L);
    for (int j=0;j<L;j++){
        for (int i =0;i<L;i++){
            microstate(i,j) = random_();

        }
    }
return microstate;
}

void metropolisAlgorithm(mat Matrix){
    //for(int i = 0; )
}

/*mat makeMatrix(int N, bool initial){ // true -> ordered initial | false -> random initial
    if(initial == true){
        return mat Matrix = ones(N,N); // returns a NxN matrix with only ones
    }else{
        return mat Matrix = rand(N,N); // returns a NxN matrix with random numbers either 1 or -1
    }


}
*/
