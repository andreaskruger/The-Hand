// This script handels all the serial communication.
// Variables here are read from other scripts.

using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;

public class serial_reader : MonoBehaviour
{

    SerialPort serialStream = new SerialPort("COM5", 115200);
    //public static int[] angles = {0, 0, 0};
    public static int[] angles = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    /// <summary>
    /// Parses the serial stream into three integer values for the angles.
    /// Returns an array of three integers.
    /// </summary>
    /// <param name="msg"></param>
    /// <returns></returns>
    int[] parseSerial(string msg)
    {   
        
       string[] splitMsg = msg.Split(',');
        /*
         int i = 0;
         int[] parsedMsg = new int[10];
         while (i < splitMsg.Length)
         {
             if (splitMsg[i] == "inf")
             {
                 splitMsg[i] = "0";
             }
             parsedMsg[i] = int.Parse(splitMsg[i]);
             i++;
         }
         */
        int[] parsedMsg = { int.Parse(splitMsg[0]), int.Parse(splitMsg[1]), int.Parse(splitMsg[2]), int.Parse(splitMsg[3]), int.Parse(splitMsg[4]), int.Parse(splitMsg[5]),int.Parse(splitMsg[6]), int.Parse(splitMsg[7]), int.Parse(splitMsg[8]), int.Parse(splitMsg[9])};
        return parsedMsg;
    }


    void Start()
    {
        serialStream.Open();
    }

    
    void Update()
    {
        // Read and parse serial input

        //angle = float.Parse(serialStream.ReadLine());
        //angles = parseSerial(serialStream.ReadLine());
  

    }
}
