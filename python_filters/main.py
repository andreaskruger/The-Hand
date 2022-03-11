#%%
from random import randint
from statistics import median
import matplotlib.pyplot as plt
import numpy as np

# Median filter the given array.
# Returns an array that is _sample_ times smaller than the given one.
# Sample sets the size of the sample window.
# Outliers is the number of elements to remove from top and bottom of each sample window.
def medianFilter(array, sample: int, outliers: int):
    # Start _sample_ indexes in
    # Take _sample_ steps
    returnArr = []
    for i in range(sample, len(array) - 1, sample):
        medianArr = []
        # Add 50 samples to the array
        for j in range(i - sample, i):
            medianArr.append(float(array[j]))
        
        # Sort the median array
        medianArr.sort()
        # Remove outliers and average the rest
        median = sum(medianArr[outliers:-outliers]) / (sample - 2 * outliers)
        returnArr.append(median)
    
    return returnArr

# Open file with data
with open("unfiltered_signal", "r") as unfilteredFile:
    unfilteredData = unfilteredFile.readlines()
with open("filtered_signal", "r") as filteredFile:
    filteredData = filteredFile.readlines()

# Convert string to float
for i in range(0, len(unfilteredData) - 1):
    unfilteredData[i] = float(unfilteredData[i])
for i in range(0, len(filteredData) - 1):
    filteredData[i] = float(filteredData[i])
    
print("Files opened successfully!")

#%%
# X-axis config
x = np.arange(0, 500, 1)

# Plot the unfiltered signal
plt.plot(x, unfilteredData, label = "No filter")
# Plot the filtered signal
#plt.plot(x, filteredData, label="Capacitor")

plt.yticks(np.arange(0, 300, 50))
plt.ylabel("Sensor value")
plt.xlabel("Measurement")
plt.title("Unfiltered vs. capacitor filtered signal")

# %%
# Plot the median filtered data, both for both the previous signals
#plt.clf()
medUnfilteredData = medianFilter(unfilteredData, 20, 4)
medFilteredData = medianFilter(filteredData, 20, 4)


# Config x axis
x = np.arange(0, 501, 501%len(medUnfilteredData))

# Plot the unfiltered signal
plt.plot(x, medUnfilteredData, label="No filter")
# Plot the filtered signal
#plt.plot(x, medFilteredData, label="Capacitor")

plt.legend()
plt.ylabel("Sensor value")
plt.xlabel("Measurement")
plt.title("Same data but with median filter")

# %%
