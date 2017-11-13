from numpy import *
from matplotlib.pyplot import *

energy, probability = loadtxt("d_T_2_4probability.txt", unpack=True, skiprows=1)

# normalizing probability:

totp = sum(probability)

probability = probability/totp

bar(energy[:-1], probability[:-1], 4, align = "center")
ylim([0,max(probability)+0.01])
title("Energy probability at T = 2.4 K" )
ylabel("P(E)")
xlabel("E")
#xticks(sorted(energy[:-1]))
savefig("d_T_2_4probability.pdf")
show()

print 1595.45 - (-1.99713)**2
print 620.734 - (-1.23759)**2