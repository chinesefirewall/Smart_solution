import matplotlib.pyplot as plt

temperatures = []
x_axis = []
t=10
i = 0
file = open("data.txt", "r")
for temp in file:
    temperatures.append(temp.rstrip('\n'))
    x_axis.append(t*i)
    i+=1
    
plt.plot(x_axis, temperatures)
plt.show()