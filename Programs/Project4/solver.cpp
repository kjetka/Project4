#include "solver.h"

std::random_device rd;
std::mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

Solver::Solver(int L_, int MCcycles, int writeIntervall){
    L = L_;
    MonteCarloCycles = MCcycles;
    N = writeIntervall;
}

void Solver::algorithm(string folderFilename, vec temperatures, bool randomStart, bool writeEveryMC, bool writeWhenFinish){

    // Print to file for every Nth-value:

    // Initialize matrix
    int promille = MonteCarloCycles/1000;
    mat Microstate = makeMicrostate(L, randomStart); // initialType: true -> random spins | false -> ordered spins
    //mat Microstate = makeMicrostate(L, false);
    string initial_type = "_";
    //string initial_type = "_random_";

    // Speedup: when calc many temperatures - use converged state from last Temp as starting microstate
    for(unsigned int i = 0; i<temperatures.size();i++){
        double Temperature =temperatures[i];

        // can use 'set' instead of 'vector' - should take less time
        vector<int> listOfEnergies;
        listOfEnergies.reserve(200);
        vector<int> listOfProbabilityEnergies;
        listOfProbabilityEnergies.reserve(200);
        int numberOfEnergies;


        double Energy = 0;
        double MagneticMoment = 0;
        ofstream outfile;
        stringstream stream;
        stream << fixed << setprecision(1  ) << Temperature;
        string Temp_string = stream.str();
        string Filename =  folderFilename + "T_"+ Temp_string + initial_type +"L" + to_string(L);
        if (randomStart) Filename += "_random";
        outfile.open("../../results/" + Filename + ".txt");

        if (writeEveryMC){
            writeHeader(outfile,  MonteCarloCycles, Temperature, randomStart);
        }

        for(int x =0; x < L; x++) {
            for (int y = 0; y < L; y++){
                Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
                MagneticMoment +=Microstate(x,y);
            }
        }

        vec Acceptance = zeros<mat>(17);

        for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);

        int acceptedConfigurations = 0;
        vec meanValues = zeros<vec>(5); //0: <E>, <E^2>, <M>, <M^2> , <|M|>

        for(int MC =1; MC<MonteCarloCycles; MC++){
            for (int xy =0; xy<L*L;xy++){
                // Flipping state ix,iy
                // QUESTION
                int ix =random_nr()*L;
                int iy = random_nr()*L;
                // This is slow, as periodicBC has an if else loop...
                int dE =  2*Microstate(ix,iy)*( Microstate(ix , periodicBC(iy,L,1) )
                                              + Microstate(ix, periodicBC(iy,L,-1))
                                              + Microstate(periodicBC(ix,L,1), iy)
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

            // Counting the different energies to find probability
            if (find(listOfEnergies.begin(),listOfEnergies.end(),Energy) != listOfEnergies.end()){
                int i = find(listOfEnergies.begin(), listOfEnergies.end(), Energy) - listOfEnergies.begin();
                listOfProbabilityEnergies[i] +=1;
            }
            else{
                listOfEnergies.push_back(Energy);
                numberOfEnergies +=1;
                listOfProbabilityEnergies.push_back(1);
            }
            //cout << numberOfEnergies << endl;
            if (writeEveryMC){
                //if (MC % N == 0 || MC == 1){ // writes every Nth value to file
                if (MC % (promille)==0|| MC ==1) {
                    writeToFile(meanValues, acceptedConfigurations, MC, MonteCarloCycles, Temperature, L, outfile);
                }
            }
        }

        //Compare with analytical result:

            /*
            cout <<" <E>, " << "<E^2>, " << "<M>, " << "<M^2>, " << "<|M|>, " << "Cv, " << "X" << setprecision(8)<< endl;
            vec analExpValues = analyticalExpectationValues(Temperature);

            vec properties = calculateProperties(meanValues/MonteCarloCycles, Temperature);
            meanValues = meanValues/(MonteCarloCycles*L*L);
            properties = properties/(L*L);
            meanValues.print("Expect:");
            properties.print("Properties");
            cout <<"stop"<<endl;

            analExpValues.print("Analytical:");
        cout <<"stop"<<endl;
            */




    //string folderFilename = "4d/probability";
    if (writeWhenFinish){
        //ofstream outfile2;
        //outfile2.open("../../results/"+ folderFilename+".txt");
        outfile << "E" << "\t"<< "P"<< endl;
                for(int i = 0; i<=listOfEnergies.size(); i++){
                    outfile << listOfEnergies[i] << "\t" << listOfProbabilityEnergies[i] << endl;
                }
    }
    outfile.close();
    }
}



int Solver::periodicBC(int i, int limit, int add){
    if ((i+add)>=limit) return 0;
    if ((i+add) <0) return limit-1;
    else return i+add;
}


double Solver::randomSpin(){
    double number =  (double) (RandomNumberGenerator(gen));
    if(number>0.5) number = 1;
    else number = -1;
    return number;
}

double Solver::random_nr(){
    return RandomNumberGenerator(gen);
}

mat Solver::makeMicrostate(int L, bool initialType){ // initialType: true -> random spins | false -> ordered spins
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


vec Solver::calculateProperties(vec ExpectationValues, double T){
    double beta = 1.0/T;
    vec calculatedValues = zeros(2);
    calculatedValues[0] = beta*(ExpectationValues[3] - ExpectationValues[4]*ExpectationValues[4]); // X uses <M^2>-<|M|>^2
    calculatedValues[1] = beta*beta*(ExpectationValues[1] - ExpectationValues[0]*ExpectationValues[0]); // Cv unit: [k]++
    return calculatedValues;
}

vec Solver::analyticalExpectationValues(double T){
    cout << "-------------------------" <<endl;
    cout << "T = "<< T <<endl;
    vec analExpValue = zeros(7);
    double A = 8.0*(1/T);
    double beta = 1.0/T;
    double sinhA = sinh(A);
    double coshA = cosh(A);
    double expA = exp(A);
    analExpValue[0] = -8.0*sinhA/(coshA+3); // <E>
    analExpValue[1] = 64.0*coshA/(coshA+3); // <E^2>
    analExpValue[2] = 0; // <M>
    analExpValue[3] = (8.0*expA+8)/(coshA+3); // <M^2>
    analExpValue[4] = (2.0*expA+4)/(coshA+3); // <|M|>
    analExpValue[5] = beta*(analExpValue[3] - analExpValue[4]*analExpValue[4]); //X
    analExpValue[6] = beta*beta*(analExpValue[1] - analExpValue[0]*analExpValue[0]); // Cv unit:[k]++
    return analExpValue/4;
}

void Solver::writeToFile(vec Means, int acceptedConfigurations, int &MCcycle, int& TotMCcycles, double &T, int L, ofstream &outfile){
    Means = Means/(MCcycle);

    vec Means_Cv_X = calculateProperties(Means, T);
    //double norm=(double) TotMCcycles;

    outfile << MCcycle << "\t";
    for (int i=0;i<5;i++){
        outfile << Means(i)/(L*L)<<"\t \t";
    }
    outfile << acceptedConfigurations << "\t \t";
    for(int i = 0; i<2; i++){
        outfile << Means_Cv_X(i)/(L*L)<<"\t \t";
    }
    outfile<< endl;
}

void Solver::writeHeader(ofstream &outfile, int MCcycles, double Temperature, bool Randomstart){
    outfile << "MCcycles: "<< MCcycles<< "\t L = "<< L<< "\t T = "<< Temperature <<"\t Randomstart = " << Randomstart<<endl;
    outfile << "MCcycles \t E \t\t E2 \t\t M \t\t M2 \t\t Mabs \t\t accepted\t\t X \t\t Cv" <<endl;
}
