from numpy import*
from matplotlib.pyplot import*

def boltsmann(T, E):
    return exp(-(1.0/T)*E)

temperatures = [1.0, 2.0, 3.0, 4.0, 5.0]
#temperatures = [1.0]

E = linspace(-10,2,1000)

Z = zeros(len(temperatures))

N = 4

for i in range(len(temperatures)):
    Z[i] = sum(boltsmann(temperatures[i],E))

for j in range(len(temperatures)):    
    plot(E,N*boltsmann(temperatures[j], E)/Z[j], label='Temperature = %g [k]'%temperatures[j])

legend()
xlabel('Energy')
ylabel('Number of occurrences')
    
