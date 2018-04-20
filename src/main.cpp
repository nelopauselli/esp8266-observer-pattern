#include <Arduino.h>

#include "SensorReader.cpp"
#include "LoggerToSerialObserver.cpp"
#include "LedIndicatorObserver.cpp"
#include "MqttPublisherObserver.cpp"

SensorReader reader;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    randomSeed(analogRead(A0));

    reader.attach(new LedIndicatorObserver());
    reader.attach(new LoggerToSerialObserver());
    reader.attach(new MqttPublisherObserver());
    
    Serial.println("");
    Serial.println("ready");
}

void loop()
{
    reader.work();
}