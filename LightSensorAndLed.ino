int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
int sensorLedPin = 2; // the number of the blinking LED
int button = 3; 	 //select the input pin for the button
int ledLamp = 4; //the output pin for the button led lamp

				 //variables for the button led
int state = HIGH;      // the current state of output pin
int reading;           // the current reading from the button input pin
int previous = LOW;    // the previous reading from the button input pin
long debounce = 200;

//variables for the blinking led and LDR
unsigned long currentMillis;
long previousMillis;

void setup() {
	Serial.begin(9600); //sets serial port for communication
	pinMode(sensorLedPin, OUTPUT);
	pinMode(button, INPUT_PULLUP);
	pinMode(ledLamp, OUTPUT);
}
void loop() {
	reading = digitalRead(button); //check for button push down
	setButtonState();   //set button state
	digitalWrite(ledLamp, state); //turn lamp on or off
	previous = reading;

	currentMillis = millis(); //milliseconds since the Arduino board began running
	sensorValue = analogRead(sensorPin); //read sensor value

	blinkLed(sensorLedPin, sensorValue);
}

//blinks a selected led with interval
void blinkLed(int led, long interval) {

	if (currentMillis - previousMillis == interval)
	{
		previousMillis = currentMillis;

		//toggles the led state HIGH or LOW
		digitalWrite(led, !digitalRead(led));
	}
}

//toogles the button state
void setButtonState() {
	if (reading == HIGH && previous == LOW && millis() - previousMillis > debounce) {
		if (state == HIGH)
			state = LOW;
		else
			state = HIGH;
	}
}

