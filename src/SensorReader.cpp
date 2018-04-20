#ifndef SENSOR_READER_CLASS
#define SENSOR_READER_CLASS

#include <Arduino.h>
#include "Subject.h"
#include "EventArgs.cpp"

#define INTERVAL 2000

class SensorReader : public Subject<EventArgs>
{
  public:
    void work()
    {
        if (lastRead + INTERVAL < millis())
        {
            // Reading simulation
            EventArgs args;
            args.temperature = random(15, 35);
            args.humidity = random(20, 80);

            Subject::notify(args);

            lastRead = millis();
        }
    }

  private:
    long lastRead = 0;
};

#endif