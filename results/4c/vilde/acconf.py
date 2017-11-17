import re
import os
from subprocess import Popen, PIPE
from numpy import *
from matplotlib.pyplot import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

MCcycle ,energy, energy2, magnetic, magnetic2, magnetic_abs, acconf1, X, Cv = loadtxt("c_T_1.0L20_random.txt", unpack=True, skiprows=2)

MCcycle ,energy, energy2, magnetic, magnetic2, magnetic_abs, acconf2, X, Cv = loadtxt("c_T_2.4L20_random.txt", unpack=True, skiprows=2)


figure()
semilogy(MCcycle, acconf1,label= "T = 1.0 K")
semilogy(MCcycle, acconf2, label= "T = 2.4 K")
title("Total accepted configurations")
xlabel("Number of MC cycles")
ylabel("Number of accepted configurations")
legend(loc=4)
tight_layout()
ticklabel_format(style='sci',axis='x')
savefig("../L_20_total_accepted.pdf")
        


