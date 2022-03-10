#include <Arduino.h>
#include <Arduino.h>
#include "MedianFilter.h"

// Create median filter objects, once for each sensor
MedianFilter<float, 50> mf0;
MedianFilter<float, 50> mf1;
//MedianFilter<float, 50> mf2;
//MedianFilter<float, 50> mf3;
//MedianFilter<float, 50> mf4;
//MedianFilter<float, 50> mf5;
//MedianFilter<float, 50> mf6;
//MedianFilter<float, 50> mf7;
//MedianFilter<float, 50> mf8;
//MedianFilter<float, 50> mf9;

float getFilteredAngle(float fingerAngles,int i){    

	//thumbIP_angle, 
	if (i == 0){
    mf0.addSample(fingerAngles);
    float FilterAngle0 = mf0.getMedian();
    return FilterAngle0;
    }

    // thumbMCP_angle
    else if (i == 1){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

    /*
    // f1PIP_angle
    else if (i == 2){ 
    mf1.addSample(fingerAngles);
    float FilterAngle2 = mf1.getMedian();
    return FilterAngle2;
    }

	// f1MCP_angle
    else if (i == 3){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f2PIP_angle
    else if (i == 4){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f2MCP_angle
    else if (i == 5){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f3PIP_angle
    else if (i == 6){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f3MCP_angle
    else if (i == 7){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f4PIP_angle
    else if (i == 8){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }

	// f4MCP_angle
    else if (i == 9){ 
    mf1.addSample(fingerAngles);
    float FilterAngle1 = mf1.getMedian();
    return FilterAngle1;
    }
    */
}