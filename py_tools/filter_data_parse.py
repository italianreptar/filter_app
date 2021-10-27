# -*- coding: utf-8 -*-
"""
@description: Script to load and plot output CSV data from the test filter app.

@author: cznapolitano (italianreptar)
"""

import numpy as np
import pandas as pd
import json
from scipy.signal import lfilter
from matplotlib import pyplot as plt

def main():
    df = pd.read_csv("..\\build\\data.csv")
    arr = np.asarray(df)
    tc = arr[:,0]
    xc = arr[:,1]
    yc = arr[:,2]
    yc2 = arr[:,3]
    
    plt.figure(1)
    plt.plot(tc, xc, tc, yc, tc, yc2)
    
    f1 = 10
    f2 = 1.5
    tp = np.arange(0, 10.01, 0.01)
    xp = np.sin(2*np.pi*f1*tp) + np.sin(2*np.pi*f2*tp);
    b = np.ones(3,)/3.0
    a = np.ones(1,)
    yp = lfilter(b, a, xp)
    
    with open("..\\build\\filter_coeffs.json") as jh:
        jj = json.load(jh)
    lpf_coeffs = jj["LowPassFilter"]
    b = lpf_coeffs["b"]
    a = lpf_coeffs["a"]
    yp2 = lfilter(b, a, xp)
    
    plt.figure(2)
    plt.plot(tp, xp, tp, yp, tp, yp2)
    
    if np.any(abs(yc - yp)>1e-8):
        print("Difference greater than threshold!")
    if np.any(abs(yc2 - yp2)>1e-8):
        print("Difference greater than threshold!!")

if __name__ == "__main__":
    main()