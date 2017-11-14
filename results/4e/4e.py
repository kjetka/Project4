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
        print txtfile

        start = txtfile.find("L_")
        stopp = txtfile.find(".txt")
        labell = txtfile[start+2:stopp]
        figure(1)
        plot(data["Temperatures"], data["E_avg"], label = "L = " + labell)
        xlabel('Temperature, ')
        ylabel('Energy, ')

        figure(2)
        plot(data["Temperatures"], data["M_abs"], label = "L = " + labell)
        xlabel('Temperature, ')
        ylabel('Magnetic moment, ')

        figure(3)
        plot(data["Temperatures"], data["X"], label = "L = " + labell)
        xlabel('Temperature')
        ylabel('susceptibility, ')

        figure(4)
        plot(data["Temperatures"], data["Cv"], label = "L = " + labell)
        xlabel('Temperature')
        ylabel('Heat capacity, ')


figure(1)
legend(loc = 2)
title(r'$ \langle E \rangle$ as function of system size and temperature ')
savefig('4e_energy.pdf')
figure(2)
legend(loc = 4)
title(r'$ \langle | M | \rangle$ as function of system size and temperature')

savefig('4e_mag.pdf')

figure(3)
legend(loc = 2)
title('Susceptibility as function of system size and temperature ')

savefig('4e_x.pdf')

figure(4)
title('Heat capacity as function of system size and temperature ')

legend(loc = 2)
savefig('4e_Cv.pdf')

show()