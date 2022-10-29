# The-Hand
Kandidatarbete

There are a couple of branches where the one calld "New_breakout_borad" is the most recent version that is being used. 

For the WIFI to work change the file "Talkyboii" and the broadcast adress to the reciever ESP.

The WIFI works with callbacks and a sendfunction, the sendfunction takes values and add them to a struct and that struct is sent to the reciever ESP everyone the senfunction
is being calld. This can be done with almost no delay or lag so no kind of delay() is needed for sending stuff. The callbacks work like interuptFunctions and will not stop
the main program from running, to print things or do anythign with the program on a successfull sent message use the callback funtion Onsend. To print or do anything
everytime a message is recievd to the Main ESP teh callback onrec is used. Here text or interupts or prints can be added. 
The wifi units need to be setup like accesspoints or station points. All documentation is easy to find on "ESPnow".
The WIFI works up to quite far distances, was tested indoor for about 30 meters and no delay or lag was being added for this. The WIFI was also tested from indoors
to the outside through a glass window without anyproblems.
The WIFI works by a peer to peer approach and as soon as the handshake is establishd it will start sending, if that connection is broken it will start looking
and as soon as a new connection is establishd the data will be sent again(this means that "lost data", data being sent while no connection is establishd will be lost).
Code wise this is very convenient due to no need for handling lost connection, just send the data and with the callbacks print a message or ping an error for each message
not succesfully being sent. No need to handle it in the code, same goes for reconnecting as thats being handled automaticly.


The system works by adding all the pins to a pinlist, every pin that is being used is either a flexsensor or a potentiometer. Read the value and add it to the median filter
to keep updating the filter values. 
Then use teh filter and read the angle(the angle is calculated from the resistance and a voltage divider).
The ESP have alot of digitalpins that can be used regardless of anything internal of the ESP, but the ADC pins are split into ADC1 and ADC2 where ADC2 CANNOT BE USED
while the wifi is running(ESPnow which is the lib used for wifi). 
This means that only 2-4 ADC pins were available(keep in mind there are some input only pins). This led to the MUX(multiplexer) being used taking 4 digital input and 
outputting(this output works as an input, changing the 4 inputs decide which of the 16 ADC pins will be read) 16 ADC pins. By just looping all these combinations
of 4 digital input the number of ADC pins added up to sufficient numbers for all flexsensors and potentiometers.


There is a calibration sequence that will first take the values from an open hand, click button, then close hand and click again and the values from a closed grip
will be added to the calibration. 
Same goes for the abduction and adduction, just go through the calibration for each finger.
(Flexsensors is mostly being used for joints in the fingers while potentiometers is being used for abduction and adduction).

Keep in mind that the model(either unity or the physical model) needs to take the same amount of values in the struct as the sender(in the same order for simplicity).

To validate the system (as stated above) Unity is being utalized and a simple C# script is adepted with every joint being an game objt. 
Matlab was also used for validation of the filters by hookin up the filters(using the median filter) and writing values to the serial port and having 
matlab read from the serialport(dont forget to end a line, matlab reads a whole line as one string and when a linebreak is found the next "vlaue" is read).
Matlab is extremly useful here to plot the values for the filters finding a acceptable filtering of noice vs time delay(5-10 samples were found to be adequate for out use,
where 10 samples started to really slow down the system).
It was found that not when not counting the physical model or anything external computing time was never an issue having sub 1ms runtime. When introducing higher samples
of filtering and the execution time of the physical model and mechanical systems a delay of 15-20 ms was the sweetspot in the loop of the ESP.





The over structure of the code goes:
setup{
  initiate the WIFI;
  initiate the Multiplexer;
  initiate the display;
  calibrate sensors for fingers(flexsensors/pots);
}

loop{
  SendID;               //Just keeping track of how many sends we have.
  sendFunction;         //This will use the sendfunction of the WIFI sending a struct. The whole struct needs to be filld(every argumnet of send);
                        //pinList[] is the list of all the sensors. Using getAngle() will read teh value, convert it into an angle and add it to the filter.
                        //The filter is a median filter removeing noice and spikes in the data. Change number of sampels to get a quicker/slower response.
 
 Serial.println();     //prints is for keeping track. Using a visual model like Unity for the hand takes values from the serial port. so Serial.write or print works.
                        //Keep in mind that the hand updates ONLY when new values are given to the model. This can be done in the loop or in the Onsent callback function in Talkyboii to clean up teh code abit.                        
}
