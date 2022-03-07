#%%
from random import randint
import matplotlib.pyplot as plt
import numpy as np

# Median filter the given array.
# Returns an array that is _sample_ times smaller than the given one.
# Sample sets the size of the sample window.
# Outliers is the number of elements to remove from top and bottom of each sample window.
def medianFilter(array: float, sample: int, outliers: int):
    # Start _sample_ indexes in
    # Take _sample_ steps
    returnArr = []
    for i in range(sample, len(array) - 1, sample):
        medianArr = []
        # Add 50 samples to the array
        for j in range(i - sample, i):
            medianArr.append(y[j])
        
        # Sort the median array
        medianArr.sort()
        # Remove outliers and average the rest
        median = sum(medianArr[outliers:-outliers]) / (sample - 2 * outliers)
        returnArr.append(median)
    
    return returnArr

#%%
mean, stddev = 0.5, 150

# X-axis config
x = np.arange(1, 1001, 0.2)
# Noise config
noise = np.random.normal(mean, stddev, 5000)
# Data ("signal") to plot with added noise
y = np.arange(10000, 15000, 1) + noise
# Add more spike noise
for i in range(0, len(y)-1):
    r = randint(0, 100)
    if r >= 99:
        y[i] = y[i] + randint(-3000, 3000)

# Apply the filter to the raw signal 
medianFilterArr = medianFilter(y, 50, 5)

# Plot the raw signal
plt.plot(x, y)
# Plot the filtered signal, which is 50 times smaller than the raw
x = np.arange(1, 990, 10)
plt.plot(x, medianFilterArr)

plt.ylabel("Sensor resistance")
plt.xlabel("Time, ms")
plt.title("Raw vs. unfiltered signal")

# %%
