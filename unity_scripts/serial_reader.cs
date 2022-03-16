// This script handels all the serial communication.
// Variables here are read from other scripts.

using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;

public class serial_reader : MonoBehaviour
{
    //static string[] ports = SerialPort.GetPortNames();
    //static string openPort = ports[0];
    SerialPort serialStream = new SerialPort("COM6", 115200);

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
        int[] parsedMsg = new int[10];

        for (int i = 0; i < splitMsg.Length; i++)
        {
            parsedMsg[i] = (int)float.Parse(splitMsg[i]);
        }

        return parsedMsg;
    }


    void Start()
    {   
        serialStream.Open();
    }
    
    void Update()
    {
        // Read and parse serial input
        //Debug.Log(serial_reader.openPort);
        if (serialStream.IsOpen)
        {
            angles = parseSerial(serialStream.ReadLine());
        }
        
        Debug.Log(angles[0]);
    }

    void OnApplicationQuit()
    {
        serialStream.Close();
    }
}
