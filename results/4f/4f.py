from numpy import *
from matplotlib.pyplot import*

L = [40 ,60, 80, 100]

a = linspace(0,200,100)

#Need the right values here:
L_Tc = [1, 2, 3, 4]

def Tc_infty(L,a,L_Tc):
    return a*L**(-1)+L_Tc

for i in range(len(L)):
    a = a
    plot(a, Tc_infty(L[i],a,L_Tc[i]), label="L=%g"%L[i])

xlabel("a")
ylabel(r"$T_C(\infty)$")