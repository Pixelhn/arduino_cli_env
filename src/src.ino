#include <Arduino.h>

void setup()
{
	Serial.begin(115200);
	Serial.println("setup");

	pinMode(4, OUTPUT);
}

void loop()
{
	Serial.println("loop");
	digitalWrite(4, 0); 
	delay(1000);
	digitalWrite(4, 1);
	delay(1000);
}