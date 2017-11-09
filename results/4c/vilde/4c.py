from numpy import *
from matplotlib.pyplot import *



temp = "1"
temp = "2_4"

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs,acconf, Cv, X = loadtxt("T_2.4_L20.txt", unpack=True, skiprows=2)




figure(1)
hold('on')
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
plot(MCcycle, energy)
title("Energy with ordered initial")
xlabel("Number of MC cycles")
ylabel(r' $ \left< \right>$ < E >  [eV]')
savefig("L_20_energy_T_%s.pdf"%temp)

show()


figure(2)
plot(MCcycle, magnetic_abs)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')

title("Magnetic moment with ordered initial")
xlabel("Number of MC cycles")
ylabel(r"$< | M | >$ [?]")
savefig("L_20_magnetic_abs_T_%s.pdf"%temp)

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, acconf2, Cv, X = loadtxt("T_2.4_random_L20.txt", unpack=True, skiprows=2)


figure(3)
plot(MCcycle, acconf, label= "ordered initial")
plot(MCcycle, acconf2, label= "random initial")
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')

title("Accepted configurations")
xlabel("Number of MC cycles")
ylabel("Number of accepted configurations")
legend()
savefig("L_20_accepted_configs_T_%s.pdf"%temp)

# OBS! All values are per spin and normalized!

figure(4)
hold('on')
plot(MCcycle, energy)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')

title("Energy with random initial")
xlabel("Number of MC cycles")
ylabel(r"< E > [eV]")
savefig("L_20_energy_random_T_%s.pdf"%temp)

figure(5)
plot(MCcycle, magnetic_abs)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')

title("Magnetic moment with random initial")
xlabel("Number of MC cycles")
ylabel(r"$<| M | >$ [?]")
savefig("L_20_magnetic_abs_random_T_%s.pdf"%temp)


