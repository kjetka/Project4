from numpy import *
from matplotlib.pyplot import *


T, energy, magnetic_abs, X, Cv = loadtxt("4e_results_L2.txt", unpack=True, skiprows=1)

figure()
hold('on')
plot(T, energy)
title("Energy")
xlabel("Temperature")
ylabel("$\\left< E \\right>$ [eV]")
tight_layout()
savefig("L2_energy_temp.pdf")

figure()
plot(T, magnetic_abs)
title("Magnetic moment")
xlabel("temperature")
ylabel("$\\left<\| M \| \\right>$ [?]")
tight_layout()
savefig("L2_magnetic_temp.pdf")

figure()
plot(T, Cv, label= "ordered initial")
title("Heat capacity")
xlabel("Temperature")
ylabel(r"$C_V$")
legend()
tight_layout()
savefig("L2_heatcapacity_temp.pdf")

figure()
hold('on')
plot(T, X)
title("Susceptibility")
xlabel("Temperature")
ylabel(r"$ \chi $ []")
tight_layout()
savefig("L2_susceptibility_temp.pdf")

show()
