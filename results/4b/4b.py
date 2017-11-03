from numpy import *
from matplotlib.pyplot import *

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, Cv, X = loadtxt("T1.0_L2.txt", unpack=True, skiprows=2)

plot(MCcycle, energy)
show()