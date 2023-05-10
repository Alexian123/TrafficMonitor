#include "SerialHandler.h"

using namespace TrafficMonitor;

bool SerialHandler::debugMode = false;

void SerialHandler::begin(long baud)
{
    Serial.begin(baud);
    Serial.println("Starting TrafficMonitor...");
}

void SerialHandler::run(IntersectionControl &ctl)
{
    if (Serial.available()) {
        char cmd = Serial.read();
        if (debugMode) {
            handleDebug(cmd, ctl);
        } else {
            handleNormal(cmd, ctl);
        }
    }
}

void SerialHandler::end()
{
    Serial.end();
}

void SerialHandler::handleNormal(char cmd, IntersectionControl &ctl)
{
    switch (cmd) {
        case 'n':   // NORMAL mode
            Serial.println("Running in normal mode.");
            ctl.changeState(ControlState::NORMAL);
            break;
        case 's':   // DISABLED mode
            Serial.println("Stopped.");
            ctl.changeState(ControlState::DISABLED);
            break;
        case 'b':   // BLINK_YELLOW mode
            Serial.println("Running in blink yellow mode.");
            ctl.changeState(ControlState::BLINK_YELLOW);
            break;
        case 'd':   // DEBUG mode
            Serial.println("Running in debug mode.");
            debugMode = true;
            break;
        case 'h':   // help
            printHelp();
            break;
        default:    // invalid cmd
            Serial.println("Invalid command! Try \"h\" for a list of valid commands.");
            break;      	
    }
}

void SerialHandler::handleDebug(char cmd, IntersectionControl &ctl)
{
    switch (cmd) {
        case 'r':   // RED mode
            Serial.println("Red light.");
            ctl.setDebugTLState(TLState::RED);   
            ctl.changeState(ControlState::DEBUG);
            break;
        case 'g':   // GREEN mode
            Serial.println("Green light.");
            ctl.setDebugTLState(TLState::GREEN);
            ctl.changeState(ControlState::DEBUG);
            break;
        case 'y':   // YELLOW mode
            Serial.println("Yellow light.");
            ctl.setDebugTLState(TLState::YELLOW);
            ctl.changeState(ControlState::DEBUG);
            break;
        case 'b':   // toggle blink
            Serial.println("Toggled blink.");
            ctl.setDebugBlinkMode(!ctl.getDebugBlinkMode());
            ctl.changeState(ControlState::DEBUG);
            break;
        case 'e':   // exit DEBUG mode
            Serial.println("Exiting debug mode.");
            debugMode = false;
            break;
        case 'h':   // debug help
            printDebugHelp();
            break;
        default:    // invalid debug cmd
            Serial.println("Invalid debug command! Try \"h\" for a list of valid debug commands.");
            break;
    }
}

void SerialHandler::printHelp()
{
    Serial.println("Available commands:");
    Serial.println("\"h\" - help");
    Serial.println("\"n\" - normal mode");
    Serial.println("\"b\" - blink yellow mode");
    Serial.println("\"d\" - debug mode");
    Serial.println("\"s\" - stop");
}

void SerialHandler::printDebugHelp()
{
    Serial.println("Available debug commands:");
    Serial.println("\"h\" - help");
    Serial.println("\"r\" - red light");
    Serial.println("\"g\" - green light");
    Serial.println("\"y\" - yellow light");
    Serial.println("\"b\" - toggle blink");
    Serial.println("\"e\" - exit debug mode");
}