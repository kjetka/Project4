from numpy import *
from matplotlib.pyplot import*

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)

L = [40 ,60, 80, 100]

a = linspace(-1,0.2,100)
a = linspace(-4, 3,100)
#Need the right values here:
L_Tc = [2.28, 2.27, 2.28, 2.27]
Tc_infty_L = zeros([len(L),len(a)])

def Tc_infty(L,a,L_Tc):
    return a*L**(-1)+L_Tc

for i in range(len(L)):
    plot(a, Tc_infty(L[i],a,L_Tc[i]), label="L=%g"%L[i])
    Tc_infty_L[i] = Tc_infty(L[i],a,L_Tc[i])
    #if i > 0:
    #    idx = argwhere(diff(sign(Tc_infty_L[i] - Tc_infty_L[i-1])) != 0).reshape(-1) + 0
    #    plot(a[idx], Tc_infty_L[i,idx], 'ro')

axhline(2.269, min(a), max(a),linestyle='--', label= r"$T_C^{exact}$ =2.269")
title("Finding the critical temperature")
xlabel("a")
ylabel(r"$T_C(\infty)$")
tight_layout()
#legend(loc=2)
savefig('critical_t.pdf')