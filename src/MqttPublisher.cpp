#ifndef MQTT_PUBLISHER_CLASS
#define MQTT_PUBLISHER_CLASS

#include "Arduino.h"
#include "Observer.h"
#include "EventArgs.cpp"

#define SIZE 10

class MqttPublisher : public Observer<EventArgs>
{
  public:
	void notify(EventArgs args) override
	{
		temperature[index] = args.temperature;
		humidity[index] = args.humidity;

		index++;

		if (index == SIZE)
		{
			//TODO: calculate average and publish it in mqtt
			Serial.println("publishing in mqtt...");

			index = 0;
		}
	}

  private:
	float temperature[SIZE];
	float humidity[SIZE];
	int index = 0;
};

#endif