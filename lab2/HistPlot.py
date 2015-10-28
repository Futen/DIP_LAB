#! /usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

x = np.arange(0,256)
y = np.zeros(256)
f = open("T_hist.txt",'r')
index = 0
for line in f:
    line = line.split("\n")[0]
    y[index] = int(float(line))
    index+=1
f.close()
#print x
#print y
plt.plot(x,y)
plt.xlabel("intensity")
plt.ylabel("map to")
plt.title("Histogram")
plt.show()
'''
f = open("hist_equ.txt",'r')
index = 0
for line in f:
    line = line.split("\n")[0]
    y[index] = int(float(line))
    index+=1
f.close()
#print x
#print y
plt.plot(x,y)
plt.xlabel("intensity")
plt.ylabel("times")
plt.title("Histogram")
plt.show()
'''
