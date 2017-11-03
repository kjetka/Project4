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

void writeToFile(vec & Means, int &MCcycle, int &TotMCcycles ,  ofstream &outfile);
void writeHeader(ofstream &outfile, int MCcycles );


int main(){

    int L = 10;
    int MonteCarloCycles = 1e6;

    // Initialize matrix

    mat Microstate = makeMicrostate(L);

    // Speedup: when calc many temperatures - use converged state from last Temp as starting microstate
    vec temperatures = vec({1.0, 2.4});





    double Temperature =temperatures[0];
    double Energy = 0;
    double MagneticMoment = 0;

    ofstream outfile;
    stringstream stream;
    stream << fixed << setprecision(1  ) << Temperature;
    string Temp_string = stream.str();

    outfile.open("../../results/4b/T"+ Temp_string +"_L" + to_string(L)+  ".txt");
    writeHeader(outfile,  MonteCarloCycles);

    for(int x =0; x < L; x++) {
        for (int y = 0; y < L; y++){
            Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
            MagneticMoment +=Microstate(x,y);
        }
    }

    vec Acceptance = zeros<mat>(17);

    for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);

    vec Meanvalues = zeros<vec>(5); //0: <E>, <E^2>, <M>, <M^2> , <|M|>
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

                Meanvalues[0] += Energy;
                Meanvalues[1] +=Energy*Energy;
                Meanvalues[2] += MagneticMoment;
                Meanvalues[3] += MagneticMoment*MagneticMoment;
                Meanvalues[4] += fabs(MagneticMoment);
            }
        }
    writeToFile(Meanvalues, MC, MonteCarloCycles,  outfile);

    }





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

void writeToFile( vec & Means, int  &MCcycle, int &TotMCcycles, ofstream &outfile){
    double norm =(double) TotMCcycles;
    outfile << (int) MCcycle << "\t \t";
    for (int i=0;i<5;i++){
        outfile << Means(i)/norm<<"\t \t";
    }
    outfile<< endl;
}

void writeHeader(ofstream &outfile, int MCcycles){
    outfile << "MCcycles: "<< MCcycles<<endl;
    outfile << "MCcycle \t <E> \t\t <E^2> \t\t <M> \t\t <M^2> \t\t <|M|>" <<endl;
}
