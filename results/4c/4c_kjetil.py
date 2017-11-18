import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *



font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

matplotlib.rc('font', **font)

#Compare random v ordered 


i=0
for temp in [1,2.4]:
    i+=1
    output = Popen(["ls"], stdout=PIPE).communicate()[0]
    txtfiles = re.findall("c_T_%i.*\.txt" %temp,output,re.IGNORECASE)


    for txtfile in txtfiles:
        with open(txtfile,"r") as infile:
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



            if "random" in txtfile:
                labell = "Random"
            else: 
                labell = "Ordered "
            figure(i)
            title("$\langle E\\rangle$ with different initial states, T = %.1f"%temp, fontsize=14)

            plot(data["MCcycles"][1:], data["E"][1:], label = labell)
            tight_layout()
            #ylim([-1.998, -1.990])
            #yticks( [-1.998, -1.997,-1.996, -1.995, -1.994, -1.993, -1.992, -1.991 ,  -1.990])
            #xscale('log')
            
            xlabel('Number of Monte Carlo cycles')#, logarithmic scale')     
            ylabel(r'Energy $[E_{kl}]$')
            #ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
    figure(i)
    legend()
    savefig('ran_order_T%i.pdf'%temp)   

output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*random.*\.txt",output,re.IGNORECASE)



for txtfile in txtfiles:
    if "1" in txtfile:
        temp = "1.0"
        t = "1_0"
    else: 
        temp = "2.4"
        t = "2_4"
    with open(txtfile,"r") as infile:
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


        fig1, ax1 =subplots()
        ax2 = ax1.twinx()
        title(r'$\langle E \rangle$ and $\langle |M| \rangle$, T = ' + temp, fontsize=14)
        ax1.plot(data["MCcycles"], data["E"], 'b', label = ' $\langle E \\rangle$')
        ax2.plot(data["MCcycles"], data["Mabs"], 'r', label = ' $\langle |M| \\rangle$')
        
        if "1" in txtfile:
            ax1.set_ylim([-2.0,-1.95])
            ax2.set_ylim([0.96,1.01])             
        else: 
            ax2.set_ylim([0.44,0.50])
            ax1.set_ylim([-1.28, -1.22])        
        
        ax1.set_ylabel(r'Energy $[E_{kl}]$', color = 'b')
        ax1.set_xlabel('Number of Monte Carlo cycles')
        ax2.set_ylabel('Magnetic moment', color = 'r')
        tight_layout()
        #ax1.legend(loc = 1)
        #ax2.legend(loc = 2)
        ax1.tick_params('y', colors='b')
        ax2.tick_params('y', colors='brown')
        ax1.ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
        
        h1, l1 = ax1.get_legend_handles_labels()
        h2, l2 = ax2.get_legend_handles_labels()
        ax2.legend(h2+h1, l2+l1, loc = 5)
        savefig('En_mag_T' + t + '.pdf')
        #grid('on')

        


    show()
