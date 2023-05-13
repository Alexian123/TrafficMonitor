#pragma once

#include "Arduino.h"

namespace TrafficMonitor
{
    enum TLState
    {
        OFF     = 0x0,    // 0b000
        RED     = 0x1,    // 0b001
        GREEN   = 0x2,    // 0b010
        YELLOW  = 0x4,    // 0b100
    };

    class TrafficLight
    {
    private:
        const byte rPin;
        const byte gPin;
        const byte yPin;

        TLState state = OFF;
        bool blinkMode = false;

        // blink timing
        byte ledState = LOW;
        int onTime = 1000;  // ms
        int offTime = 1000; // ms
        long lastMillis = 0; 
    public:
        TrafficLight(byte rPin, byte yPin, byte gPin);
        ~TrafficLight();

        void run(); // call inside loop

        // Getters & setters
        void setState(TLState state);
        TLState getState() const;
        void setBlinkMode(bool blinkMode);
        bool getBlinkMode() const;
        void setOnTime(int onTime);
        int getOnTime() const;
        void setOffTime(int offTime);
        int getOffTime() const;

    private:
        void light(TLState newState) const; // constant light
        void blink();                       // blinking light
    };
}