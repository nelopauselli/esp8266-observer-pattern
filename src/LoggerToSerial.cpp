#ifndef LOGGER_TO_SERIAL_CLASS
#define LOGGER_TO_SERIAL_CLASS

#include <Arduino.h>
#include "Observer.h"
#include "EventArgs.cpp"

class LoggerToSerial : public Observer<EventArgs>
{
  public:
    void notify(EventArgs args) override
    {
        Serial.print("Temperature: ");
        Serial.print(args.temperature);
        Serial.print(", Humidity: ");
        Serial.println(args.humidity);
    }
};

#endif