from numpy import *
from matplotlib.pyplot import*

T = linspace(2.2, 2.4, 1000)

Tc = 2.269

def magnetic(T):
    beta = -(1.0/8.0)
    return (T-Tc)**beta
    
def heat_capa(T):
    alpha = -0.0
    return abs(Tc-T)**alpha

def suscept(T):
    gamma = -(7.0/4.0)
    return abs(Tc-T)**gamma

figure()
plot(T, magnetic(T))
title("magnetic")
xlim([2.2, 2.4])

figure()
plot(T, heat_capa(T))
title("Heat Capacity")
xlim([2.2, 2.4])

figure()
plot(T, suscept(T))
title("Susceptibility")
xlim([2.2, 2.4])

show()