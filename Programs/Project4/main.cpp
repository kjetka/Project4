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


//void metropolisSampling(int N); //the whole prosess
//void metropolisAlgorithm(mat Matrix);
mat makeMatrix();

vec analyticalExpectationValues(double T);

std::random_device rd;
std::mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

double random_spinn();

mat makeMicrostate(int L);
int periodicBC(int i, int limit, int add){
    if ((i+add)>=limit) return 0;
    if ((i+add) <0) return limit-1;
    else return i+add;
}
inline double random_nr(){
    return RandomNumberGenerator(gen);}

void writeToFile( vec & Expectations, int &MCcycle, ofstream &outfile);
void writeHeader(ofstream &outfile, int MCcycles );
int main(){

    int L = 2;
    int MonteCarloCycles = 1e2;

    // Initialize matrix

    mat Microstate = makeMicrostate(L);

    // Speedup: when calc many temperatures - use converged state from last Temp as starting microstate
    vec temperatures = vec({1.0, 2.4});




    double Temperature =temperatures[0];
    double Energy = 0;
    double MagneticMoment = 0;

    for(int x =0; x < L; x++) {
        for (int y = 0; y < L; y++){
            Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
            MagneticMoment +=Microstate(x,y);
        }
    }

    vec Acceptance = zeros<mat>(17);

    for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);

    vec Expectationvalues = zeros<vec>(5); //0: <E>, <E^2>, <M>, <M^2> , <|M|>
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
                Microstate(ix,iy) *= - 1;
                Energy += dE;
                MagneticMoment += -2*Microstate(ix,iy);

                Expectationvalues[0] += Energy*probability;
                Expectationvalues[1] += Energy*Energy* probability;
                Expectationvalues[2] += MagneticMoment* probability;
                Expectationvalues[3] += MagneticMoment*MagneticMoment*probability;
                Expectationvalues[4] += fabs(MagneticMoment)* probability;
            }
        //writeToFile()
        }

    }

    cout <<" <E>, " << "<E^2>, " << "<M>, " << "<M^2>, " << "<|M|>" << endl;
    vec analExpValues = analyticalExpectationValues(Temperature);
    Expectationvalues.print("Expect:");
    analExpValues.print("Analytical:");

    return 0;
}

double random_spinn(){
    double number =  (double) (RandomNumberGenerator(gen));
    if(number>0.5) number = 1;
    else number = -1;
    return number;
}

mat makeMicrostate(int L){
    mat microstate = ones<mat>(L,L);
    for (int j=0;j<L;j++){
        for (int i =0;i<L;i++){
            microstate(i,j) = random_spinn();

        }
    }
    return microstate;
}

vec analyticalExpectationValues(double T){
    vec analExpValue = zeros(5);
    double A = 8*(1/T);
    double sinhA = sinh(A);
    double coshA = cosh(A);
    double expA = exp(A);
    analExpValue[0] = -8 *sinhA/(coshA+3); // <E>
    analExpValue[1] = 64*coshA/(coshA+3); // <E^2>
    analExpValue[2] = 0; // <M>
    analExpValue[3] = 8*expA+8/(coshA+3); // <M^2>
    analExpValue[4] = 2*expA+4/(coshA+3); // <|M|>
    return analExpValue;
}
void writeToFile( vec & Expectations, int &MCcycle, ofstream &outfile){

    outfile << MCcycle << "\t";
    for (int i=0;i<5;i++){
        outfile << Expectations<<"\t";
    }

}

void writeHeader(ofstream &outfile, int MCcycles){
    outfile << "MCcycles: "<< MCcycles<<endl;
    outfile << "MCcycle \t <E> \t <E^2> \t <M> \t <M^2> \t <|M|>" <<endl;
}
