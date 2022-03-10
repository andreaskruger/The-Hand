#%%
# This script reads the specified number of lines
# over serial, and saves the data to a text file.
import serial
import time

### Script config ###
numOfMsg = 500
fileName = "filtered_signal"
serialPort = "COM6"
baudRate = 9600

### Main script. No need to change code below this line. ###
print("Starting serial reading in 3 seconds...")
time.sleep(3)
print("Seria lreading started...")

# Open serial connection
serialCon = serial.Serial(serialPort, baudRate)

# Read the specified number of lines over serial
data = [None] * numOfMsg
for i in range(0,numOfMsg):
    if i % 100 == 0:
        print(f"Read {i} lines...")
        
    data[i] = serialCon.readline()

# Close serial connection
serialCon.close()

print("Serial reading finished!")
print("Press 'Run cell' to dump data into text file.")

#%%
# Dump data into a text file
with open(fileName, "w") as textFile:
    for line in data:
        # Remove unwanted characters
        textFile.writelines(str(line).split('\\')[0][2:] + "\n")
# %%
