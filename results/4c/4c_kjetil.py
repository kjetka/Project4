import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *


#Compare random v ordered 


i=0
for temp in [1,2.4]:
    i+=1
    output = Popen(["ls"], stdout=PIPE).communicate()[0]
    files = re.findall("c_T_%i.*\.txt" %temp,output,re.IGNORECASE)


    for file in files:
        with open(file,"r") as infile:
            data = {}
            infile.readline()
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



            if "random" in file:
                labell = "Random"
            else: 
                labell = "Ordered "
            figure(i)
            title("$\langle E\\rangle$ for ordered and random initial spins, T = %.1f"%temp)

            plot(data["MCcycles"][1:], data["E"][1:], label = labell)
            #ylim([-1.998, -1.990])
            #yticks( [-1.998, -1.997,-1.996, -1.995, -1.994, -1.993, -1.992, -1.991 ,  -1.990])
            xscale('log')
            xlabel('Monte Carlo cycles')     
            ylabel('Energy')
            #ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
    figure(i)
    if temp == 1:
        #ylim([ -2.01,-1.8])
        legend()
    else:
        legend(loc = 4)
    rcParams['font.size'] = 14

    savefig('ran_order_T%i.pdf'%temp)   

MCcycles,E,E2, M,M2,Mabs,accepted,X,Cv = loadtxt("c_T_1.0L_20.txt",unpack=True, skiprows=2)
plot(MCcycles, E, 'b', label = "ordered initial spin system")

ylabel('Energy $E_{kl}$')
xlabel('Monte Carlo cycles')
xscale('log')
ylim([-2.01,-1.98])
#ax1.set_xlim([0,1e4])

rcParams['font.size'] = 14


legend()
title('$\\langle E \\rangle $ for ordered initial system at T=1 ')
tight_layout()
savefig('order_T1_start.pdf')






output = Popen(["ls"], stdout=PIPE).communicate()[0]
files = re.findall(".*random.*\.txt",output,re.IGNORECASE)



for file in files:
    with open(file,"r") as infile:
        data = {}
        infile.readline()
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
        if "1.0" in file:
            labell = "1.0"
        else:
            labell = "2.4"

        fig1, ax1 =subplots()
        ax2 = ax1.twinx()
        title('Mean energy and magnetic moment at T = %s' %labell)
        ax1.plot(data["MCcycles"], data["E"], 'b', label = ' $\langle E \\rangle$')
        ax2.plot(data["MCcycles"], data["Mabs"], 'brown', label = ' $\langle M \\rangle$')

        ax1.set_ylabel('Energy $E_{kl}$', color = 'b')
        ax1.set_xlabel('Monte Carlo cycles')
        ax2.set_ylabel(r' Magnetic moment', color = 'brown')
        #ax1.legend(loc = 1)
        #ax2.legend(loc = 2)
        if "1.0" in file:
            ax2.set_ylim([0,1.1])
            ax1.set_ylim([-2.1,-0.6])

        ax1.tick_params('y', colors='b')
        ax2.tick_params('y', colors='brown')
        ax1.ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
        
        h1, l1 = ax1.get_legend_handles_labels()
        h2, l2 = ax2.get_legend_handles_labels()
        ax2.legend(h2+h1, l2+l1, loc = 5)
        rcParams['font.size'] = 14
        tight_layout()

        savefig('En_mag_T'+labell+'.pdf')
        #grid('on')

        




