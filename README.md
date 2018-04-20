# esp8266-observer-pattern
A sample implementation of Observer Pattern

_This code was written using [PlatformIO](https://platformio.org/) and [vscode](https://code.visualstudio.com/). Would you like This code to be compatible with the Arduino IDE?... tell me!_

## Goal
Implement a design pattern in a microcontroller.

## Diagram
![class diagram](https://github.com/nelopauselli/esp8266-observer-pattern/raw/master/doc/diagram.png  "")

## Program 
```cpp
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
```

## Structure of event argument used:
```cpp
struct EventArgs
{
  float temperature;
  float humidity;
};
```

## Define a Subject
```cpp
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
```

## Define a Observer
```cpp
class LoggerToSerialObserver : public Observer<EventArgs>
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
```

## Define other Observer
```cpp
class LedIndicatorObserver : public Observer<EventArgs>
{
  public:
	void notify(EventArgs args) override
	{
		if (args.temperature > 30 || args.humidity > 50)
			digitalWrite(LED_BUILTIN, LOW);
		else
			digitalWrite(LED_BUILTIN, HIGH);
	}
};
```