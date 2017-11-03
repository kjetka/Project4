from numpy import *
from matplotlib.pyplot import *
figure()
MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T1.0_L20.txt", unpack=True, skiprows=2)

plot(MCcycle, energy)


MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T_random_1.0_L20.txt", unpack=True, skiprows=2)
figure()
plot(MCcycle, energy)

show()