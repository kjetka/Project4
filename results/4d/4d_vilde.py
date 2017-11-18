from numpy import *
from matplotlib.pyplot import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)
"""
energy, probability = loadtxt("d_T_1probability.txt", unpack=True, skiprows=1)

# normalizing probability:
figure()
totp = sum(probability)

probability = probability/totp

bar(energy[:-1], probability[:-1], 4, align = "center")
ylim([0,max(probability)+0.01])
title("Energy probability at T = 1.0 K" )
ylabel("P(E)")
xlabel("E")
tight_layout()
#xticks(sorted(energy[:-1]))
savefig("d_T_1probability.pdf")
show()

figure()
energy, probability = loadtxt("d_T_2_4probability.txt", unpack=True, skiprows=1)

# normalizing probability:

totp = sum(probability)

probability = probability/totp

bar(energy[:-1], probability[:-1], 4, align = "center")
ylim([0,max(probability)+0.01])
title("Energy probability at T = 2.4 K" )
ylabel("P(E)")
xlabel("E")
tight_layout()
#xticks(sorted(energy[:-1]))
savefig("d_T_2_4probability.pdf")
show()
"""

magnetic, probability = loadtxt("d_T_1MagneticPropability.txt", unpack=True, skiprows=1)

# normalizing probability:
figure(figsize=(6,4))
totp = sum(probability)

probability = probability/totp

bar(magnetic, probability, 2, align = "center")

#ylim([0,max(probability)+0.01])
title("Magnetic Moment Probability at T = 1.0 K" )
ylabel("P(M)")
xlabel("M")

tight_layout()
#xticks(sorted(energy[:-1]))
savefig("d_T_1magneticprobability.pdf")

figure(figsize=(7,4))
magnetic, probability = loadtxt("d_T_2_4MagneticPropability.txt", unpack=True, skiprows=1)

# normalizing probability:

totp = sum(probability)

probability = probability/totp

bar(magnetic, probability, 2, align = "center")
#ylim([0,max(probability)+0.01])
title("Magnetic Moment probability at T = 2.4 K" )
ylabel("P(M)")
xlabel("M")
tight_layout()
#xticks(sorted(energy[:-1]))
savefig("d_T_2_4Magneticprobability.pdf")
show()

figure(figsize=(7,4))
magnetic, probability = loadtxt("d_T_2_5MagneticPropability.txt", unpack=True, skiprows=1)

# normalizing probability:

totp = sum(probability)

probability = probability/totp

bar(magnetic, probability, 2, align = "center")
#ylim([0,max(probability)+0.01])
title("Magnetic Moment probability at T = 2.5 K" )
ylabel("P(M)")
xlabel("M")
tight_layout()
#xticks(sorted(energy[:-1]))
savefig("d_T_2_5Magneticprobability.pdf")
show()