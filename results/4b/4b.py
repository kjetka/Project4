from numpy import *
from matplotlib.pyplot import *
"""
MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T_1.0_L2.txt", unpack=True, skiprows=2)
"""

#Analytical:
anal_E = zeros(len(MCcycle))
anal_E.fill(-1.9960)

anal_M_abs = zeros(len(MCcycle))
anal_M_abs.fill(0.9987)

anal_Cv = zeros(len(MCcycle))
anal_Cv.fill(3.9933)

anal_X = zeros(len(MCcycle))
anal_X.fill(0.0321)

# OBS! All values are per spin and normalized!

figure()
hold('on')
plot(MCcycle, energy, label="numerical")
plot(MCcycle, anal_E,'--',label="analytical value")
title("Energy per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left< E \\right>$ [eV]")
legend()
savefig("L_2_energy.pdf")

figure()
plot(MCcycle, magnetic_abs, label="numerical")
plot(MCcycle, anal_M_abs,'--',label="analytical value")
title("Magnetic moment per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\left<\\| M \\| \\right>$ [?]")
legend()
savefig("L_2_magnetic_abs.pdf")

figure()
plot(MCcycle, Cv, label="numerical")
plot(MCcycle,anal_Cv,'--',label="analytical value")
title("Heat capacity per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$C_v$ [eV]")
ylim([0.75, 4.25])
legend(loc=4)
savefig("L_2_heat_capasity.pdf")

figure()
plot(MCcycle, X, label="numerical")
plot(MCcycle,anal_X,'--',label="analytical value")
title("Susceptibility per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\\chi$ [eV]")
legend()
savefig("L_2_susceptibility.pdf")


show()
