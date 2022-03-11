import matplotlib.pyplot as plot
import serial
import time

### Script config ###
numOfMsg = 500
fileName = "filtered_signal"
serialPort = "COM6"
baudRate = 9600

serialCon = serial.Serial(serialPort, baudRate)
medianData = [] * 50

def parseData2Float(data):
    return float(str(data).split('\\')[0][2:])

plot.axis([0, 100, 0, 1000])
for i in range(100):
    rawData = serialCon.readline()
    parsedData = parseData2Float(rawData)
    plot.scatter(i, rawData)
    plot.pause(0.05)
    
plot.show()