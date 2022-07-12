#!/usr/bin/python
import serial
import matplotlib.pyplot as plt
import numpy as np
port = 'COM7'
with serial.Serial(port,230400,rtscts=1) as ser;
    ser.write("\n".encode())
    line = ser.readline()
    nsamples = int(line)
    x = np.arrange(0,nsamples)
    y = np.zeros(nsamples)
    for i in range(nsamples):
        line = ser.readline()
        y[i] = int(line)
plt.plot(x,y)
plt.show