#! /usr/bin/env python3.9

import os
import sys
import numpy as np
from math import pi, exp, log
from matplotlib import pyplot as plt

#
# This script reads a file and returns the kernel density estimation,
# assuming normal pdf.
#

def plot (X, Y):
    """ This function plots and shows the kernel density estimation.
        It requires the terminal emulator 'kitty'.
    """
    plt.plot(X, Y);
    plt.savefig("/tmp/plt.png")
    os.system("kitty +kitten icat /tmp/plt.png")

def kernel (x):
    """ We use a standard normal kernel.
    """
    return ( exp (-0.5*x**2) ) / ((2*pi)**0.5)

def bandwith (X):
    """ We assume the distribution as normal.
    """
    sigma_hat = np.std(X)
    n = len(X)
    iqr = np.subtract(*np.percentile(X, [75,25]))
    h = 0.9 * min ( sigma_hat, (iqr/1.34) ) * (n**(-0.2))
    return h

def kde (X, x):
    """ Kernel density estimation implementation.
    """
    h = bandwith (X)
    n = len(X);
    f = 0
    for i in range (n):
        f += (1.0/(n*h)) * kernel((x-X[i])/ h)
    return f

def main ():
    for filename in sys.argv[1:len(sys.argv)]:
        X=[]
        new_filename="doc/violin_"+filename.split('_')[1].split('.')[0]+"_uniquac.csv"
        file = open (filename, "r")
        for line in file:
            X.append(log(float(line.strip()))/log(10))
        file.close()
        xmin = 2.0
        xmax = 6.0
        xlin = [xmin-0.01]
        extx = xmax - xmin
        for i in range (10001):
            xlin.append(xmin+i*(extx/10000.0))
        xlin.append(xmax+0.01)
        ylin = [0]
        for x in xlin[1:len(xlin)-1]:
            ylin.append((kde(X,x)))
        ylin.append(0)
        file = open(new_filename, "w")
        file.write("x,yplus,yminus\n")
        for i in range(len(xlin)):
            if ( i%20 == 0 or i==(len(xlin)-1)):
                file.write(str(xlin[i])+","+str(ylin[i])+","+str(-ylin[i])+"\n")
        file.close()

main()
