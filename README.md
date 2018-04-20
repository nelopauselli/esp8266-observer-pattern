# esp8266-observer-pattern
A sample implementation of Observer Pattern

_This code was written using [PlatformIO](https://platformio.org/) and [vscode](https://code.visualstudio.com/). Would you like This code to be compatible with the Arduino IDE?... tell me!_

## Goal
Implement Observer Design Pattern in a microcontroller.

> Can we use design patterns in our code for microcontrollers? ... obviously yes (otherwise we would not be here).

> OK, show me the code!

## Diagram
![class diagram](https://github.com/nelopauselli/esp8266-observer-pattern/raw/master/doc/diagram.png  "")

> I said "code", not diagram!

## Program 
```cpp
#include ...

SensorReader sensorReader;

void setup()
{
    ...

    sensorReader.attach(new LedIndicator());
    sensorReader.attach(new LoggerToSerial());
    sensorReader.attach(new MqttPublisher());
    
    ...
}

void loop()
{
    sensorReader.work();
}
```

## Define a Subject
> We define a class inheriting **Subject** with the type of notification argument
```cpp
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
```

## Structure of the event argument used:

```cpp
struct EventArgs
{
  float temperature;
  float humidity;
};
```
> Yes, it's a struct but could be a class too

## Define Observers
> We define different classes inheriting **Observer**

### Observer which send information over Serial
```cpp
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
```

### Observer that turn on or off a LED
```cpp
class LedIndicator : public Observer<EventArgs>
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