from numpy import *
from matplotlib.pyplot import *

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs,acconf, Cv, X = loadtxt("T_1.0_L20.txt", unpack=True, skiprows=2)

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, acconf2, Cv, X = loadtxt("T_2.4_L20.txt", unpack=True, skiprows=2)


figure()
semilogy(MCcycle, acconf, label= "T = 1.0")
semilogy(MCcycle, acconf2, label= "T= 2.4")
title("Accepted configurations")
xlabel("Number of MC cycles")
ylabel("Number of accepted configurations")
legend(loc=4)
savefig("L_20_accepted_configs.pdf")