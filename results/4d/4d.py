from numpy import *
from matplotlib.pyplot import *

energy, probability = loadtxt("probability.txt", unpack=True, skiprows=1)

# normalizing probability:

totp = sum(probability)

probability = probability/totp

bar(energy[:-1], probability[:-1], 4)
ylim([0,max(probability)+0.01])
ylabel("P(E)")
xlabel("E")
savefig("L20_MCc1e5_T2_4.pdf")
show()

energy = sorted(energy)
