from __future__ import division
from numpy import *
from matplotlib.pyplot import *

#	MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs,acconf, X, Cv = loadtxt("opgbT_2.4_L2.txt", unpack=True, skiprows=2)


MCcycle ,energy, energy2, magnetic, magnetic2, magnetic_abs, acconf, X, Cv = loadtxt("opgbT_1.0_L2_random.txt", unpack=True, skiprows=2)

#Analytical:
anal_E = zeros(len(MCcycle))
anal_E.fill(-1.9960) # T=1
#anal_E.fill(-1.6436) #T=2

anal_M_abs = zeros(len(MCcycle))
anal_M_abs.fill(0.9987) #T=1
#anal_M_abs.fill(0.8815) #T=2

anal_Cv = zeros(len(MCcycle))
anal_Cv.fill(0.03208) # T=1
#anal_Cv.fill(0.4126) # T=2

anal_X = zeros(len(MCcycle))
anal_X.fill(0.0040)			# T=1
#anal_X.fill(    0.1251)  	# T=2


#sjekk at gaar mot rett verdi :)

# OBS! All values are per spin and normalized!

figure()
plot(MCcycle, energy, label="numerical")
plot(MCcycle, anal_E,'--',label="analytical value")
title("Energy per spin for L=2")
xlabel("Number of MC cycles")
ylim([-2,-1.99])
ylabel("$\langle E \\rangle$ [eV]")
#legend(loc=4)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')

savefig("L_2_energy.pdf")




figure()
plot(MCcycle, magnetic_abs, label="numerical")
plot(MCcycle, anal_M_abs,'--',label="analytical value")
title("$\langle | M | \\rangle$ per spin for L=2")
xlabel("Number of MC cycles")
ylabel("Magnetic moment")
legend(loc=1)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
ylim([0.998,0.999])
savefig("L_2_magnetic_abs.pdf")




figure()
plot(MCcycle, Cv, label="numerical")
plot(MCcycle,anal_Cv,'--',label="analytical value")
title("Heat capacity per spin for L=2")
xlabel("Number of MC cycles")
ylabel("$C_V$ [eV]")
ylim([0.023, 0.038])
legend(loc=4)
savefig("L_2_heat_capasity.pdf")
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')


figure()
plot(MCcycle, X, label="numerical")
plot(MCcycle,anal_X,'--',label="analytical value")
title("Susceptibility per spin vs Monte Carlo cycles")
xlabel("Number of MC cycles")
ylabel("$\chi $, [eV]")
ylim([0.003,0.006])
savefig("L_2_susceptibility.pdf")



