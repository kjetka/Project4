import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *

#energy, probability = loadtxt("probability.txt", unpack=True, skiprows=1)


output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*\.txt",output,re.IGNORECASE)
print txtfiles

for txtfile in txtfiles:
    with open(txtfile,"r") as infile:
        data = {}
        #infile.readline()
        identifiers = infile.readline().split()
        for identifier in identifiers:
            data[identifier] = []

        lines = infile.readlines()
        for line in lines: 
            values = line.split()
            for identifier,value in zip(identifiers,values):
                data[identifier].append(float(value))

        for key in data.keys():
            data[key] = array(data[key])

        print data.keys()
        data["P"] = data["P"]/(sum(data["P"]))
        print txtfile
       
        figure()
        if "T_1" in txtfile:
        	titlee = "1.0"
        	xlim([-800,-700])
        if "T_2" in txtfile:
			titlee = "2.4"

        title("Probability distribution for L=20 at T = " + titlee)
        bar(data["E"][:-1], data["P"][:-1],4)
        ylim([0,max(data["P"])+0.01])
        ylabel("Probability")
        xlabel("Energy $E_{kl}$")
	savefig('PD_T_' + titlee[0:1]+'MC_1e6'+'.pdf')


# normalizing probability:

"""
totp = sum(probability)

probability = probability/totp

bar(energy[:-1], probability[:-1], 4)
ylim([0,max(probability)+0.01])
ylabel("P(E)")
xlabel("E")
savefig("L20_MCc1e5_T2_4.pdf")
show()

energy = sorted(energy)
"""