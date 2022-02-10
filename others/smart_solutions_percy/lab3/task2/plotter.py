import matplotlib.pyplot as plt

temps = []
x_axis = []
t=10
i = 0
file = open("temperatures.txt","r")
for line in file:
    temps.append(line.rstrip('\n'))
    x_axis.append(t*i)
    i=i+1

plt.plot(x_axis,temps)
plt.show()

