from numpy import *
from matplotlib.pyplot import *

#Analytical:
anal_E = zeros(len(MCcycle))
anal_E.fill(-1.9960)

anal_M_abs = zeros(len(MCcycle))
anal_M_abs.fill(0.9987)

anal_Cv = zeros(len(MCcycle))
anal_Cv.fill(3.9933)

anal_X = zeros(len(MCcycle))
anal_X.fill(0.0321)

temp = "1"
#temp = "2_4"

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T1.0_L20.txt", unpack=True, skiprows=2)

figure()
hold('on')
plot(MCcycle, energy, label="numerical")
plot(MCcycle, anal_E,'--',label="analytical value")
title("Energy per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left< E \\right>$ [eV]")
legend()
savefig("L_20_energy_T_%s.pdf"%temp)

figure()
plot(MCcycle, magnetic_abs, label="numerical")
plot(MCcycle, anal_M_abs,'--',label="analytical value")
title("Magnetic moment per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left<\\| M \\| \\right>$ [?]")
legend()
savefig("L_20_magnetic_abs_T_%s.pdf"%temp)

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T_random_1.0_L20.txt", unpack=True, skiprows=2)



# OBS! All values are per spin and normalized!

figure()
hold('on')
plot(MCcycle, energy, label="numerical")
plot(MCcycle, anal_E,'--',label="analytical value")
title("Energy per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left< E \\right>$ [eV]")
legend()
savefig("L_20_energy_random_T_%s.pdf"%temp)

figure()
plot(MCcycle, magnetic_abs, label="numerical")
plot(MCcycle, anal_M_abs,'--',label="analytical value")
title("Magnetic moment per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left<\\| M \\| \\right>$ [?]")
legend()
savefig("L_20_magnetic_abs_random_T_%s.pdf"%temp)


show()
