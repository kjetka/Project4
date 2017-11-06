from numpy import *
from matplotlib.pyplot import *



#temp = "1"
temp = "2_4"

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs,acconf, Cv, X = loadtxt("T_2.4_L20.txt", unpack=True, skiprows=2)
figure()
hold('on')
plot(MCcycle, energy)
title("Energy with ordered initial")
xlabel("Number of MC cycles")
ylabel("$\\left< E \\right>$ [eV]")
savefig("L_20_energy_T_%s.pdf"%temp)

figure()
plot(MCcycle, magnetic_abs)
title("Magnetic moment with ordered initial")
xlabel("Number of MC cycles")
ylabel("$\\left<\\| M \\| \\right>$ [?]")
savefig("L_20_magnetic_abs_T_%s.pdf"%temp)

MCcycle, energy, energy2, magnetic, magnetic2, magnetic_abs, acconf2, Cv, X = loadtxt("T_2.4_random_L20.txt", unpack=True, skiprows=2)


figure()
plot(MCcycle, acconf, label= "ordered initial")
plot(MCcycle, acconf2, label= "random initial")
title("Accepted configurations")
xlabel("Number of MC cycles")
ylabel("Number of accepted configurations")
legend()
savefig("L_20_accepted_configs_T_%s.pdf"%temp)

# OBS! All values are per spin and normalized!

figure()
hold('on')
plot(MCcycle, energy)
title("Energy with random initial")
xlabel("Number of MC cycles")
ylabel("$\\left< E \\right>$ [eV]")
savefig("L_20_energy_random_T_%s.pdf"%temp)

figure()
plot(MCcycle, magnetic_abs)
title("Magnetic moment with random initial")
xlabel("Number of MC cycles")
ylabel("$\\left<\\| M \\| \\right>$ [?]")
savefig("L_20_magnetic_abs_random_T_%s.pdf"%temp)


show()
