from __future__ import division
from numpy import *
from matplotlib.pyplot import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)

#	MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs,acconf, X, Cv = loadtxt("opgbT_2.4_L2.txt", unpack=True, skiprows=2)


MCcycle ,energy, energy2, magnetic, magnetic2, magnetic_abs, acconf, X, Cv = loadtxt("b_T_1.0L2_random.txt", unpack=True, skiprows=2)

#Analytical:
anal_E = zeros(len(MCcycle))
anal_E.fill(-1.9960) # T=1
#anal_E.fill(-1.6436) #T=2

anal_M_abs = zeros(len(MCcycle))
anal_M_abs.fill(0.9987) #T=1 

neg_anal_M_abs = zeros(len(MCcycle))
neg_anal_M_abs.fill(-0.9987) #T=1 

anal_Cv = zeros(len(MCcycle))
anal_Cv.fill(0.03208) # T=1
#anal_Cv.fill(0.4126) # T=2

anal_X = zeros(len(MCcycle))
anal_X.fill(0.0040)			# T=1. Using  < |M| >


#sjekk at gaar mot rett verdi :)

# OBS! All values are per spin and normalized!

figure()
plot(MCcycle, energy, label="numerical value")
plot(MCcycle, anal_E,'--',label="analytical value")
title("Energy per spin for L=2")
xlabel("Number of MC cycles")
ylim([-2,-1.99])
ylabel("$\langle E \\rangle\, [E_{kl}]$ ")
#legend(loc=4)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
tight_layout()
savefig("L_2_energy.pdf")




figure()
plot(MCcycle, magnetic_abs, label="numerical")
plot(MCcycle, anal_M_abs,'--',label="analytical value")
title("$\langle | M | \\rangle$ per spin for L=2")
xlabel("Number of MC cycles")
ylabel("Magnetic moment")
legend(loc=1)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
ylim([0.9984,0.9994])
tight_layout()
savefig("L_2_magnetic_abs.pdf")

figure()
plot(MCcycle, magnetic, label="numerical")
plot(MCcycle, neg_anal_M_abs,'--',label="analytical value")
title("$\langle M \\rangle$ per spin for L=2")
xlabel("Number of MC cycles")
ylabel("Magnetic moment")
legend(loc=1)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
ylim([-0.25,0.25])
tight_layout()
savefig("L_2_magnetic.pdf")




"""


title('Relative energy')
ax1.plot(Encut, relen, 'bo-', label = r'$ E_{rel}$')
ax2.plot(dEncut2, drelEN, 'ro-', label = r'|$\Delta E_{rel}}$ |')

ax1.set_ylabel('Relative energy (meV)', color = 'b')
ax1.set_xlabel('Energy cutoff eV')
ax2.set_ylabel(r' Relative energy meV', color = 'r')
grid('on')



"""


figure()
plot(MCcycle, Cv, label="numerical")
plot(MCcycle,anal_Cv,'--',label="analytical value")
title("Heat capacity per spin for L=2")
xlabel("Number of MC cycles")
ylabel(r"$C_V\,[\frac{J^2}{k_B^3T^2}]$")
ylim([0.022, 0.038])
legend(loc=4)
tight_layout()
savefig("L_2_heat_capasity.pdf")
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')


figure()
plot(MCcycle, X, label="numerical")
plot(MCcycle,anal_X,'--',label="analytical value")
title("Susceptibility per spin for L=2")
xlabel("Number of MC cycles")
ylabel(r"$\chi \, [\frac{J}{k_B^2T}]$")
ylim([0.002,0.005])
tight_layout()
savefig("L_2_susceptibility.pdf")

show()

