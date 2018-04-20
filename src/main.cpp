#include <Arduino.h>

#include "SensorReader.cpp"
#include "LedIndicator.cpp"
#include "LoggerToSerial.cpp"
#include "MqttPublisher.cpp"

SensorReader reader;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    randomSeed(analogRead(A0));

    reader.attach(new LedIndicator());
    reader.attach(new LoggerToSerial());
    reader.attach(new MqttPublisher());
    
    Serial.println("");
    Serial.println("ready");
}

void loop()
{
    reader.work();
}