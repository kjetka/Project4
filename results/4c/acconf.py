import re
import os
from subprocess import Popen, PIPE
from numpy import *
from matplotlib.pyplot import *

font = {'family' : 'normal',
        'weight' : 'normal',
        'size'   : 14}

output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*random.*\.txt",output,re.IGNORECASE)

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
        if "T_1" in txtfile:
            labell = "1.0"
        else:
            labell = "2.4"

        plot(data["MCcycles"], data["accepted"], label= 'T = '+labell)


figure(10)
title("Accepted configurations")
xlabel("Number of MC cycles")
ylabel("% of accepted configurations")
legend(loc=4)
ticklabel_format(style='sci',scilimits=(-3,3),axis='x')
savefig("L_20_accepted_configs.pdf")
show()