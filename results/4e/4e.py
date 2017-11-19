import re
import os
import operator
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from scipy.optimize import *

from numpy import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)
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
        plot(data["Temperatures"][0:], data["E_avg"][0:], label = r"$L$ = " + labell)
        xlabel(r'Temperature, $\left[ \frac{k_BT}{J}\right]$ ')
        ylabel(r'$\left< E\right>$ $[E_{kl}]$')
        title('Energy per spin')

        figure(2)
        plot(data["Temperatures"], data["M_abs"], label = r"$L$ = " + labell)
        xlabel(r'Temperature, $\left[ \frac{k_BT}{J}\right]$')
        ylabel(r'$\left< |M| \right>$')
        title('Magnetic moment per spin')

        figure(3)
        plot(data["Temperatures"], data["X"], label = r"$L$ = " + labell)
        xlabel(r'Temperature, $\left[ \frac{k_BT}{J}\right]$')
        ylabel(r' $\chi$ , $\left[ \frac{J}{k_B^2T}\right]$')
        title('Susceptibility per spin')
        
        figure(4)
        plot(data["Temperatures"], data["Cv"], label = r"$L$ = " + labell)
        xlabel(r'Temperature, $\left[ \frac{k_BT}{J}\right]$')
        ylabel(r' $C_V$, $\left[ \frac{J^2}{k_B^3T^2}\right]$')
        title('Heat capacity per spin')

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
 


figure(1)
legend(loc = 2)
#title(r'$ \langle E \rangle$ as function of system size and temperature ')
rcParams['font.size'] = 14
tight_layout()
xlim([2.15,2.4])
savefig('4e_energy.pdf')

figure(2)
legend(loc = 1)
tight_layout()
xlim([2.1,2.6])
#title(r'$ \langle | M | \rangle$ as function of system size and temperature')
rcParams['font.size'] = 14
savefig('4e_mag.pdf')

figure(3)
tight_layout()
xlim([2.1,2.6])
legend()
#title('Susceptibility as function of system size and temperature ')
rcParams['font.size'] = 14

savefig('4e_x.pdf')

figure(4)
#title('Heat capacity as function of system size and temperature ')
tight_layout()

xlim([2.1,2.6])
legend()
rcParams['font.size'] = 14

savefig('4e_Cv.pdf')




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
plot(L_liste, T_C_CV_list, 'o',label = 'Experimental data' )
x = linspace(0,max(L_liste), 100)
plot(x, x*p[0]+p[1], label = 'Linear fit')
#axhline(2.269, 0, 5,linestyle='--', label= r"$T_C^{exact}$ =2.269")
title('Linear regression to find $T_C$',fontsize=14)
ylabel(r'Temperature, $\left[ \frac{k_BT}{J} \right]$ ')
ylim([2.277-0.001,0.009+2.277])
xlabel(r'Inverse grid size, 1/$L$')
xlim([0,0.026])
tight_layout()
legend(loc = 2)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
rcParams['font.size'] = 14
savefig('linfit.pdf')
show()

