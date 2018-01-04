#include "Arduino.h"

// The pins we can use to control the motor (pairs)
#define M1A 7
#define M1B 6

#define M2A 5
#define M2B 4

// the pins we use to control the PWM (Pulse Width Modulation)
#define M1Speed 10
#define M2Speed 11

// Direction (if pressed, go into reverse)
#define dirPin 3

void setup() {
	Serial.begin(9600);

	// All pins are output
	pinMode(M1A, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2A, OUTPUT);
	pinMode(M2B, OUTPUT);

	// This is the direction pin, an input
	pinMode(dirPin, INPUT_PULLUP);
}

void loop() {
	// Read the speed control and convert the 10-bit reading to an 8-bit reading
	int potVal = map(analogRead(A7), 0, 1023, 0, 255);

	// If the value has changed, store the new value and adjust the output
	Serial.println(potVal);

	// Are we pressing reverse switch?
	bool forward = digitalRead(dirPin);
	switch (forward) {
		case true:
			digitalWrite(M1A, HIGH);
			digitalWrite(M1B, LOW);

			digitalWrite(M2A, HIGH);
			digitalWrite(M2B, LOW);
			break;

		case false:
			digitalWrite(M1A, LOW);
			digitalWrite(M1B, HIGH);

			digitalWrite(M2A, LOW);
			digitalWrite(M2B, HIGH);
			break;
	}

	// Set the PWM output from the pot (0 - 255)
	analogWrite(M1Speed, potVal);
	analogWrite(M2Speed, potVal);
}
