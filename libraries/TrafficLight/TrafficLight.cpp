#include <Arduino.h>
#include <TrafficLight.h>

#define BIT0 0x1
#define BIT1 0x2
#define BIT2 0x4

using namespace TrafficMonitor;

TrafficLight::TrafficLight(byte rPin, byte gPin, byte yPin)
    : rPin(rPin), gPin(gPin), yPin(yPin)
{
}

TrafficLight::~TrafficLight()
{
}

void TrafficLight::run()
{
    if (blinkMode) {
        blink();
    } else {
        light(state);
    }
}

void TrafficLight::light(TLState newState) const
{
    digitalWrite(rPin, newState & BIT0);
    digitalWrite(gPin, newState & BIT1);
    digitalWrite(yPin, newState & BIT2);
}

void TrafficLight::blink()
{
    long currentMillis = millis();
    if ((ledState == HIGH) && (currentMillis - lastMillis >= onTime)) {
        ledState = LOW;
        lastMillis = currentMillis;
        light(TLState::OFF);
    } else if ((ledState == LOW) && (currentMillis - lastMillis >= offTime)) {
        ledState = HIGH;
        lastMillis = currentMillis;
        light(state);
    }
}

void TrafficLight::setState(TLState state)
{
    this -> state = state;
}

TLState TrafficLight::getState() const
{
    return state;
}

void TrafficLight::setBlinkMode(bool blinkMode)
{
    this -> blinkMode = blinkMode;
}

bool TrafficLight::getBlinkMode() const
{
    return blinkMode;
}

void TrafficLight::setOnTime(int onTime)
{
    this -> onTime = onTime;
}

int TrafficLight::getOnTime() const
{
    return onTime;
}

void TrafficLight::setOffTime(int offTime)
{
    this -> offTime = offTime;
}

int TrafficLight::getOffTime() const
{
    return offTime;
}