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

anal_Cv = zeros(len(MCcycle))
anal_Cv.fill(0.03208) # T=1
#anal_Cv.fill(0.4126) # T=2

anal_X = zeros(len(MCcycle))
anal_X.fill(0.0040)			# T=1. Using  < |M| >


"""
figure()
plot(MCcycle, energy, label="numerical value")
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









fig1, ax1 =subplots()
ax2 = ax1.twinx()
title("Comparing $\langle |M| \\rangle$ with $\langle M \\rangle$ for L=2")

ax1.plot(MCcycle, magnetic_abs,'b',  label="$\langle |M| \\rangle$, numerical")
ax1.plot(MCcycle, anal_M_abs,'b--',label="analytical value")

ax2.plot(MCcycle, magnetic,'r', label="$\langle M \\rangle$, numerical")
ax2.plot(MCcycle, zeros(len(MCcycle)), 'r--',label="analytical value")


ax1.set_xlabel("Number of MC cycles")
ax1.set_ylabel("Magnetic moment", color = 'b' )
ax2.set_ylabel("Magnetic moment", color = 'r')
ax1.tick_params('y', colors='b')
ax2.tick_params('y', colors='r')

ax1.ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
ax2.set_ylim([-0.5,0.07])
h1, l1 = ax1.get_legend_handles_labels()
h2, l2 = ax2.get_legend_handles_labels()
ax1.legend(h2+h1, l2+l1, loc=5)
savefig("L_2_mag_magabs.pdf")





title('Relative energy')
ax1.plot(Encut, relen, 'bo-', label = r'$ E_{rel}$')
ax2.plot(dEncut2, drelEN, 'ro-', label = r'|$\Delta E_{rel}}$ |')

ax1.set_ylabel('Relative energy (meV)', color = 'b')
ax1.set_xlabel('Energy cutoff eV')
ax2.set_ylabel(r' Relative energy meV', color = 'r')
grid('on')





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
"""

"""error = []
for i in range(len(energy)):
	error.append(energy[i] - anal_E[i])
"""
error = [(energy[i]-anal_E[i])/float(anal_E[i]) for i in range(len(energy)) ]


print type(MCcycle), type(error)
print type(error)
figure()
title('Absolute error in energy for the L=2 system')
plot(MCcycle, error)
xlabel('Monte Carlo cycles')
ylabel('Energy, ')
grid('on')
ylim([-0.001, 0.001])
savefig('abs_error.pdf')
show()

