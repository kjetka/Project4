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

std::random_device rd;
std::mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

int periodicBC(int i, int limit, int add){
    if ((i+add)>=limit) return 0;
    if ((i+add) <0) return limit-1;
    else return i+add;
}

double randomSpin();
inline double random_nr(){
    return RandomNumberGenerator(gen);}

mat makeMicrostate(int L, bool initialType);
void writeToFile(vec Means, int &MCcycle, int &TotMCcycles , double& T, int L,  ofstream &outfile);
void writeHeader(ofstream &outfile, int MCcycles );
vec analyticalExpectationValues(double T);
vec calculateProperties(vec meanValues, double T);
void writeToFileTemperature( vec & Means, double & T, vec & properties, ofstream &outfile);
void writeHeaderTemperature(ofstream &outfile);


int main(){

    int L = 20;
    int MonteCarloCycles = 1e4;

    // Initialize matrix

    mat Microstate = makeMicrostate(L, true);
    //mat Microstate = makeMicrostate(L, false);

    // Speedup: when calc many temperatures - use converged state from last Temp as starting microstate
    vec temperatures = vec({1.0, 2.4});

    for(unsigned int i = 0; i<temperatures.size();i++){

        double Temperature =temperatures[i];
        double Energy = 0;
        double MagneticMoment = 0;

        ofstream outfile;
        stringstream stream;
        stream << fixed << setprecision(1  ) << Temperature;
        string Temp_string = stream.str();

        outfile.open("../../results/4b/T_random_"+ Temp_string +"_L" + to_string(L)+  ".txt");
        writeHeader(outfile,  MonteCarloCycles);

        // ---------------------------------------

        ofstream outfileTemperature;
        outfileTemperature.open("../../results/4c/FinalProperties_L" + to_string(L)+  ".txt");
        writeHeaderTemperature(outfileTemperature);


        for(int x =0; x < L; x++) {
            for (int y = 0; y < L; y++){
                Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
                MagneticMoment +=Microstate(x,y);
            }
        }
        Microstate.print("M");
        cout << Energy << endl;
        vec Acceptance = zeros<mat>(17);

        for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);

        vec meanValues = zeros<vec>(5); //0: <E>, <E^2>, <M>, <M^2> , <|M|>
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
                    MagneticMoment += 2*Microstate(ix,iy);

                }

            }
            meanValues[0] += Energy;
            meanValues[1] += Energy*Energy;
            meanValues[2] += MagneticMoment;
            meanValues[3] += MagneticMoment*MagneticMoment;
            meanValues[4] += fabs(MagneticMoment);


            writeToFile(meanValues, MC, MonteCarloCycles, Temperature, L, outfile);

        }


    //writeToFileTemperature(meanValues, Temperature, properties, outfileTemperature);

    // Compare with analytical result for N=2:

    cout <<" <E>, " << "<E^2>, " << "<M>, " << "<M^2>, " << "<|M|>, " << "Cv, " << "X" << endl;
    vec analExpValues = analyticalExpectationValues(Temperature);
    vec properties = calculateProperties(meanValues/MonteCarloCycles, Temperature);
    meanValues = meanValues/(MonteCarloCycles*L*L);
    properties = properties/(L*L);
    meanValues.print("Expect:");
    properties.print();
    analExpValues.print("Analytical:");

}
    return 0;
}

vec calculateProperties(vec ExpectationValues, double T){
    double beta = 1.0/T;
    vec calculatedValues = zeros(2);
    calculatedValues[0] = beta*(ExpectationValues[3] - ExpectationValues[2]*ExpectationValues[2]); // X
    calculatedValues[1] = beta*(ExpectationValues[1] - ExpectationValues[0]*ExpectationValues[0]); // Cv
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

vec analyticalExpectationValues(double T){
    vec analExpValue = zeros(7);
    double A = 8*(1/T);
    double beta = A/8;
    double sinhA = sinh(A);
    double coshA = cosh(A);
    double expA = exp(A);
    analExpValue[0] = -8.0*sinhA/(coshA+3); // <E>
    analExpValue[1] = 64.0*coshA/(coshA+3); // <E^2>
    analExpValue[2] = 0; // <M>
    analExpValue[3] = (8.0*expA+8)/(coshA+3); // <M^2>
    analExpValue[4] = (2.0*expA+4)/(coshA+3); // <|M|>
    analExpValue[5] = beta*(analExpValue[3] - analExpValue[2]*analExpValue[2]); // Cv
    analExpValue[6] = beta*(analExpValue[1] - analExpValue[0]*analExpValue[0]); //X
    return analExpValue/4;
}
void writeToFile(vec Means, int &MCcycle, int& TotMCcycles, double &T, int L, ofstream &outfile){
    Means = Means/(MCcycle);
    vec Means_Cv_X = calculateProperties(Means, T);
    double norm=(double) TotMCcycles;
    outfile << MCcycle << "\t";
    for (int i=0;i<5;i++){
        outfile << Means(i)/(L*L)<<"\t \t";
    }
    for(int i = 0; i<2; i++){
        outfile << Means_Cv_X(i)/(L*L)<<"\t \t";
    }
    outfile<< endl;
}

void writeHeader(ofstream &outfile, int MCcycles){
    outfile << "MCcycles: "<< MCcycles<<endl;
    outfile << "MCcycle \t <E> \t\t <E^2> \t\t <M> \t\t <M^2> \t\t <|M|>" <<endl;
}

void writeToFileTemperature( vec & Means, double &T, vec & properties, ofstream &outfile){
    outfile << T << "\t" << properties[0] << "\t" << properties[1];
    outfile << "\t" << Means[0] << "\t" << Means[2] << "\t";
    outfile<< endl;
}

void writeHeaderTemperature(ofstream &outfile){
    outfile << "Temperature \t Suseptibiliy \t\t Heat Capacity \t\t Mean Energy \t\t Mean Magnetization" <<endl;
}
