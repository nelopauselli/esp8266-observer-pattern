#include <Arduino.h>

#include "SensorReader.cpp"
#include "LedIndicator.cpp"
#include "LoggerToSerial.cpp"
#include "MqttPublisher.cpp"

SensorReader sensorReader;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    randomSeed(analogRead(A0));

    sensorReader.attach(new LedIndicator());
    sensorReader.attach(new LoggerToSerial());
    sensorReader.attach(new MqttPublisher());
    
    Serial.println("");
    Serial.println("ready");
}

void loop()
{
    sensorReader.work();
}