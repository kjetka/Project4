import re
import os
import operator
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from scipy.optimize import curve_fit

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
        #plot(data["Temperatures"][3:-5], data["E_avg"][3:-5], label = "L = " + labell)
        plot(data["Temperatures"][0:-5], data["E_avg"][0:-5], label = "L = " + labell)
        xlabel('Temperature, $\\frac{k_BT}{J}$ ')
        ylabel('Energy $E_{kl}$')

        figure(2)
        plot(data["Temperatures"], data["M_abs"], label = "L = " + labell)
        xlabel('Temperature, $\\frac{k_BT}{J}$')
        ylabel('Magnetic moment')

        figure(3)
        plot(data["Temperatures"], data["X"], label = "L = " + labell)
        xlabel('Temperature, $\\frac{k_BT}{J}$')
        ylabel('susceptibility $\chi$ , $\\frac{J}{k_B^2T}$')

        figure(4)
        plot(data["Temperatures"], data["Cv"], label = "L = " + labell)
        xlabel('Temperature, $\\frac{k_BT}{J}$')
        ylabel('Heat capacity $C_V$, $\\frac{J^2}{k_B^3T^2}$')
       

        index, value = max(enumerate(data["Cv"]), key = operator.itemgetter(1))

        labell = float(labell)
        T_C = data["Temperatures"][index]
        T_C_CV_list[i] = (T_C)
        L_liste.append(txtfile)




        """
        index, value = max(enumerate(data["X"]), key = operator.itemgetter(1))
        T_C = data["Temperatures"][index]
        T_C_X_list[i] = (T_C)
        """
 

"""
figure(1)
legend(loc = 2)
title(r'$ \langle E \rangle$ as function of system size and temperature ')
rcParams['font.size'] = 14
savefig('4e_energy.pdf')

figure(2)
legend(loc = 1)
title(r'$ \langle | M | \rangle$ as function of system size and temperature')
rcParams['font.size'] = 14
savefig('4e_mag.pdf')

figure(3)
legend()
title('Susceptibility as function of system size and temperature ')
rcParams['font.size'] = 14

savefig('4e_x.pdf')

figure(4)
title('Heat capacity as function of system size and temperature ')
legend()
rcParams['font.size'] = 14

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



file = open('../table_T_C.tex','w+')
file.write(' L & $T_C$ \\\\ \\hline    \n    ')
for i in range(len(L_liste)):
    file.write( " %s & %.2f \\\\ \n" %(L_liste[i],T_C_CV_list[i]))
"""
L1 = float(L_liste[-1])
L2 = float(L_liste[-2])
T1 = float(T_C_CV_list[-1])
T2 = float(T_C_CV_list[-2])


Tinfty = T1- ( (T2-T1) /(1./L2-1./L1) ) * 1.0/L1
print Tinfty
"""

def func(x,b,a):
   return (a*x+b)

for i in range(len(L_liste)):
    L_liste[i] = 1./float(L_liste[i])
p0 = [-0.1,2.3]




print T_C_CV_list
p = polyfit(L_liste,T_C_CV_list,1) # (func,xdata,y,p0)
print p[1]
figure()
plot(L_liste, T_C_CV_list, '*-',label = 'Experimental data' )
x = linspace(0,max(L_liste), 100)
plot(x, x*p[0]+p[1], label = 'Linear fit')
title('Linear fit of $T_C$ for different grid sizes')
ylabel('Temperature, $\\frac{k_BT}{J}$ ')
xlabel('Inverse grid size, 1/L')
legend(loc = 2)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
rcParams['font.size'] = 14
savefig('linfit.pdf')


