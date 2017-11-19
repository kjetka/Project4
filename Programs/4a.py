from __future__ import division 
from numpy import *
#from scipy.integrate import quad 
from matplotlib.pyplot import *
from scipy.optimize import curve_fit



spinner = [-1,1]
alle_mikro = []
E_alle_mikro = []
Mag_alle_mikro= []
for a in spinner:
	for b in spinner:
		for c in spinner:
			for d in spinner:
				mikro = [a,b,c,d]
				alle_mikro.append(mikro)
				E_mikro = 2*a*b + 2*c*d + 2*a*c + 2*b*d
				E_alle_mikro.append(E_mikro)
				Mag_alle_mikro.append(a+b+c+d)


indexer = linspace(0,15,16)
sortert = argsort( Mag_alle_mikro)


Mag_sort = zeros(16)
Mikro_sort = zeros((16,4))
E_sort = zeros(16)

for i in range(16):
	j = sortert[i]
	Mag_sort[i] = Mag_alle_mikro[j]
	Mikro_sort[i] = alle_mikro[j]
	E_sort[i] = E_alle_mikro[j]


with open('../results/table_micro.tex', 'w+') as file:
	file.write("	Microstate & Spinn  & Energi & Magnetization	\\\\ \\hline \n")
	
	for i in range(16):
		mikro = Mikro_sort[i]
		string = " %i & "%(i+1)
		spinn_str = " "
		str_slutt = " "
		for j in range(4):
			spinn = mikro[j]
			if spinn ==1:
				spinn_str += "$\\uparrow$ "
			if spinn ==-1:
				spinn_str += "$\\downarrow $ "
			if j==1:
				spinn_str += '\\newline'
			string += " "
		if E_sort[i] ==0:
			str_slutt += "& $%i $ &$ %i$   \\\\"%(-E_sort[i], Mag_sort[i]) 
		else: 
			str_slutt += "& $%i \\text{J}$ &$ %i$   \\\\"%(-E_sort[i], Mag_sort[i]) 
		str_slutt += "\\hline"
		file.write(string + spinn_str+str_slutt + '\n')







