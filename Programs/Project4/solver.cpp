#include "solver.h"

std::random_device rd;
std::mt19937_64 gen(rd());
// Set up the uniform distribution for x \in [[0, 1]
std::uniform_real_distribution<double> RandomNumberGenerator(0.0,1.0);

Solver::Solver(int L_, int MCcycles, int writeResolution, int NProcesses_, int RankProcess_){
    L = L_;
    MonteCarloCycles = MCcycles;
    NSpins = (double) L*L;
    N = writeResolution;
    NProcesses = NProcesses_;
    RankProcess = RankProcess_;
}

void Solver::algorithm(string folderFilename, vec temperatures, bool randomStart, bool writeEveryMC, bool writeWhenFinish, bool writeForTemp){

    // Equilibration time [MC cylces]:
    int equilibrationTime = 5e5;

    // Initializing matrix of spins
    mat Microstate = makeMicrostate(L, randomStart); // initialType: true -> random spins | false -> ordered spins

    // printing ----------------------------------------------
    ofstream outfile_temp;

    if (writeForTemp && (RankProcess == 0)){
        outfile_temp.open("../../results/"+ folderFilename + ".txt");
        writeHeaderTemperature(outfile_temp);
    }

    // Defines how many points printed to file for plotting
    int promille = MonteCarloCycles/N;

    // -------------------------------------------------------

    for(unsigned int i = 0; i<temperatures.size();i++){
        double Temperature =temperatures[i];

        // Reserving vecotors to get probability of energies
        vector<int> listOfEnergies;
        listOfEnergies.reserve(200);
        vector<int> listOfProbabilityEnergies;
        listOfProbabilityEnergies.reserve(200);

        vector<int> listOfMagnetizations;
        listOfMagnetizations.reserve(200);
        vector<int> listOfProbabilityMagnetizations;
        listOfProbabilityMagnetizations.reserve(200);

        // Vector used when summing result from different
        // processors because of parallellizing
        vec TotalMeanValues = zeros(5);


        double Energy = 0;
        double MagneticMoment = 0;

        // printing ----------------------------------------------
        ofstream outfile;

        if(writeEveryMC){
            stringstream stream;

            stream << fixed << setprecision(1  ) << Temperature;
            string Temp_string = stream.str();
            string Filename =  folderFilename + "T_"+ Temp_string +"L" + to_string(L);
            if (randomStart) Filename += "_random";
            if (RankProcess == 0){
                outfile.open("../../results/" + Filename + ".txt");
            }
        }

        if (writeEveryMC && (RankProcess == 0)){
            writeHeader(outfile,  MonteCarloCycles, Temperature, randomStart);
        }
        // ---------------------------------------------------------

        // Calculating total energy and total magnetic moment for initial
        // system of spins
        for(int x =0; x < L; x++) {
            for (int y = 0; y < L; y++){
                Energy -= Microstate(x,y)*(Microstate(periodicBC(x,L,1),y) + Microstate(x,periodicBC(y,L,1)));
                MagneticMoment +=Microstate(x,y);
            }
        }

        // QUESTION: why 17?
        vec Acceptance = zeros<mat>(17);

        for( int de =-8; de <= 8; de+=4) Acceptance(de+8) = exp(-de/Temperature);

        int acceptedConfigurations=0;

        // The mean values are in the order:
        // <E>, <E^2>, <M>, <M^2>, <|M|>
        vec meanValues = zeros<vec>(5);

        for(int MC =1; MC<MonteCarloCycles; MC++){
            // Finding the percentage of accepted
            // configurations for every L^2th attempt.
            // Need to reset the number here
            //acceptedConfigurations = 0;

            // Make L^2 attempts of changing the configuration
            // for every Monte Carlo cycle
            for (int xy =0; xy<L*L;xy++){
                // Pick a random spin to flip
                int ix =random_nr()*L;
                int iy = random_nr()*L;

                // Calculate the change in energy if the
                // spin is flipped
                int dE =  2*Microstate(ix,iy)*( Microstate(ix , periodicBC(iy,L,1) )
                                                + Microstate(ix, periodicBC(iy,L,-1))
                                                + Microstate(periodicBC(ix,L,1), iy)
                                                + Microstate(periodicBC(ix,L,-1), iy)    );

                double probability = Acceptance(dE + 8);

                // Metropolis algorithm:
                // Desides if the new configuration is accepted
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
            if(RankProcess == 0 && writeWhenFinish && MC >= equilibrationTime){
                if (find(listOfEnergies.begin(),listOfEnergies.end(),Energy) != listOfEnergies.end()){
                    int i = find(listOfEnergies.begin(), listOfEnergies.end(), Energy) - listOfEnergies.begin();
                    listOfProbabilityEnergies[i] +=1;
                }
                else{
                    listOfEnergies.push_back(Energy);
                    listOfProbabilityEnergies.push_back(1);
                }
                if (find(listOfMagnetizations.begin(),listOfMagnetizations.end(),MagneticMoment) != listOfMagnetizations.end()){
                    int j = find(listOfMagnetizations.begin(), listOfMagnetizations.end(), MagneticMoment) - listOfMagnetizations.begin();
                    listOfProbabilityMagnetizations[j] +=1;
                }
                else{
                    listOfMagnetizations.push_back(MagneticMoment);
                    listOfProbabilityMagnetizations.push_back(1);
                }
            }

            // Writing to file: mean values versus MC cycles
            if (writeEveryMC){
                for( int i =0; i < 5; i++){
                    MPI_Reduce(&meanValues[i], &TotalMeanValues[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
                }
                if(RankProcess == 0){
                    if (MC % (promille)==0|| MC ==1) {
                        double  percentAccepted = acceptedConfigurations/NSpins;
                        //writeToFile(TotalMeanValues, NProcesses, percentAccepted, MC, Temperature, L, outfile);
                        writeToFile(TotalMeanValues, NProcesses, acceptedConfigurations, MC, Temperature, L, outfile);
                    }
                }
            }
        } // end of MC loop

        // cout << "variance: " << meanValues[1]/(MonteCarloCycles) << " - " << meanValues[0]/(MonteCarloCycles) << "^2" << endl;

        //Compare with analytical result:

        /*
            cout <<" <E>, " << "<E^2>, " << "<M>, " << "<M^2>, " << "<|M|>, " << "Xv, " << "Cv" << setprecision(8)<< endl;
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
        // Writing the probability to file
        ofstream outfile2;
        ofstream outfile3;
        if (writeWhenFinish && (RankProcess == 0)){

            outfile2.open("../../results/"+ folderFilename+"probability.txt");
            outfile2 << "E" << "\t"<< "P"<< endl;
            for(unsigned int i = 0; i<=listOfEnergies.size(); i++){
                outfile2 << listOfEnergies[i] << "\t" << listOfProbabilityEnergies[i] << endl;
            }
            outfile2.close();

            outfile3.open("../../results/"+ folderFilename+"MagneticPropability.txt");
            outfile3 << "M" << "\t"<< "P"<< endl;
            for(unsigned int i = 0; i<=listOfMagnetizations.size(); i++){
                outfile3 << listOfMagnetizations[i] << "\t" << listOfProbabilityMagnetizations[i] << endl;
            }
            outfile3.close();
        }

        if (RankProcess == 0 && (writeEveryMC)){
            outfile.close();
        }
        // Writing to file: mean values versus temperature
        if (writeForTemp){
            for( int i =0; i < 5; i++){
                MPI_Reduce(&meanValues[i], &TotalMeanValues[i], 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            }

            if (RankProcess == 0){
                writeToFileTemperature(TotalMeanValues, MonteCarloCycles, NProcesses ,Temperature, L*L, outfile_temp);
            }
        }

    } //end of temperature-loop

    if (RankProcess == 0 && writeForTemp){
        outfile_temp.close();
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

vec Solver::calculateProperties(vec MeanValues, double T){
    double beta = 1.0/T;
    vec calculatedValues = zeros(2);
    calculatedValues[0] = beta*(MeanValues[3] - MeanValues[4]*MeanValues[4]); // X uses <M^2>-<|M|>^2
    calculatedValues[1] = beta*beta*(MeanValues[1] - MeanValues[0]*MeanValues[0]);
    return calculatedValues;
}
// Analytical values for L = 2
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

void Solver::writeToFile(vec Means, int NProcesses, double percentAccepted, int &MCcycle, double &T, int L, ofstream &outfile){
    Means = Means/(MCcycle*NProcesses);
    double Nspins = (double) L*L;
    vec Means_Cv_X = calculateProperties(Means, T);

    outfile << MCcycle*NProcesses << "\t";
    for (int i=0;i<5;i++){
        outfile << Means(i)/Nspins<<"\t \t";
    }
    outfile << percentAccepted << "\t \t";
    for(int i = 0; i<2; i++){
        outfile << Means_Cv_X(i)/Nspins<<"\t \t";
    }
    outfile<< endl;
}

void Solver::writeToFileTemperature(vec meanValues, int MonteCarloCycles, int NProcesses ,double &T, int NSpins, ofstream &outfile){

    outfile << T << "\t\t";
    double norm=(double) MonteCarloCycles*NProcesses;
    double Spins=(double) NSpins;   //L*L
    meanValues = meanValues/norm;

    vec meanValues_Cv_X = calculateProperties(meanValues, T);

    outfile << meanValues[0]/Spins << "\t" << meanValues[4]/Spins << "\t\t";
    outfile << meanValues_Cv_X[0]/Spins << "\t" << meanValues_Cv_X[1]/Spins << "\t";
    outfile << endl;

}

void Solver::writeHeaderTemperature(ofstream &outfile){
    outfile << "Temperatures \t <E> \t\t <|M|> \t\t X \t\t Cv" <<endl;
}

void Solver::writeHeader(ofstream &outfile, int MCcycles, double Temperature, bool Randomstart){
    outfile << "MCcycles: "<< MCcycles<< "\t L = "<< L<< "\t T = "<< Temperature <<"\t Randomstart = " << Randomstart<<endl;
    outfile << "MCcycles \t E \t\t E2 \t\t M \t\t M2 \t\t Mabs \t\t accepted\t\t X \t\t Cv" <<endl;
}
