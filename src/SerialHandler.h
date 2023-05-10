#pragma once

#include "Arduino.h"
#include "TrafficLight.h"
#include "IntersectionControl.h"

namespace TrafficMonitor
{
    class SerialHandler 
    {
    private:
        static bool debugMode;

    public:
        static void begin(long baud); // call inside setup
        static void run(IntersectionControl &ctl);  // call inside loop
        static void end();

    private:
        static void handleNormal(char cmd, IntersectionControl &ctl);
        static void handleDebug(char cmd, IntersectionControl &ctl);
        static void printHelp();
        static void printDebugHelp();
    };
}