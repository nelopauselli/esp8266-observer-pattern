#ifndef LED_INDICATOR_CLASS
#define LED_INDICATOR_CLASS

#include "Arduino.h"
#include "Observer.h"
#include "EventArgs.cpp"

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

#endif