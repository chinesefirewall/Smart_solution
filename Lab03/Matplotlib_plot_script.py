import matplotlib.pyplot as plt
import numpy as np
file = open('temps.txt')
temps= list()
for line in file:
    temps.append(line)


#matplotlib.use('Agg')
plt.figure()
plt.plot(temps)
plt.show()
    
    
    
    