from numpy import *
from matplotlib.pyplot import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)

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
