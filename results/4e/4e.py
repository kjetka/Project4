import re
import os
import operator
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *

#energy, probability = loadtxt("probability.txt", unpack=True, skiprows=1)


output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall("e_L_.*\.txt",output,re.IGNORECASE)
txtfiles.append(txtfiles[0])
del txtfiles[0]

T_C_CV_list = zeros(len(txtfiles))
T_C_X_list = zeros(len(txtfiles))

L_liste = []
i=-1
for txtfile in txtfiles:
    with open(txtfile,"r") as infile:
        i+=1
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

        #print data.keys()

        start = txtfile.find("L_")
        stopp = txtfile.find(".txt")
        labell = txtfile[start+2:stopp]
        figure(1)
        plot(data["Temperatures"][3:-5], data["E_avg"][3:-5], label = "L = " + labell)
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


        index, value = max(enumerate(data["Cv"]), key = operator.itemgetter(1))
        T_C = data["Temperatures"][index]
        T_C_CV_list[i] = (T_C)
        L_liste.append(txtfile)

        index, value = max(enumerate(data["X"]), key = operator.itemgetter(1))
        T_C = data["Temperatures"][index]
        T_C_X_list[i] = (T_C)


"""
figure(1)
legend(loc = 2)
title(r'$ \langle E \rangle$ as function of system size and temperature ')
savefig('4e_energy.pdf')

figure(2)
legend(loc = 1)
title(r'$ \langle | M | \rangle$ as function of system size and temperature')

savefig('4e_mag.pdf')

figure(3)
legend()
title('Susceptibility as function of system size and temperature ')

savefig('4e_x.pdf')

figure(4)
title('Heat capacity as function of system size and temperature ')

legend()
savefig('4e_Cv.pdf')

"""

#L = 100, 80
#a = (2.27-2.28)/(1./100. - 1./80.)
#print 2.28 - 4./80.



for i in range(len(L_liste)):
    L = L_liste[i]
    L = L[4:-1]
    end = L.find(".t")
    L =  L[0:end]
    L_liste[i] = L


print T_C_CV_list
print T_C_X_list


file = open('../table_T_C.tex','w+')
file.write(' L & $T_C$ \\\\ \\hline    \n    ')
for i in range(len(L_liste)):
    file.write( " %s & %.2f \\\\ \n" %(L_liste[i],T_C_CV_list[i]))






