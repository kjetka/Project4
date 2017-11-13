import re
import os
from subprocess import Popen, PIPE
from numpy import *
from matplotlib.pyplot import *

output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*T_2.*\.txt",output,re.IGNORECASE)

print txtfiles

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
        

        figure(10)
        if "random" in txtfile:
             llabel="random"
        else:
             llabel = "ordered"
        plot(data["MCcycles"], data["accepted"], label= llabel)
figure(10)
title("Accepted configurations - T = 2.4")
xlabel("Number of MC cycles")
ylabel("% accepted of attempted configurations")
legend(loc=4)
ticklabel_format(style='sci',axis='x')
savefig("L_20_accepted_T2_4.pdf")
        


