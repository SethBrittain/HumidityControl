#include <Arduino.h>
#include "EventTimers.h";
#include "LcdController.h";
#include "SPI_H.h";
#include "HumidityControllerStateMachine.h";

// Time in ms
const unsigned int ONE_SECOND = 1000;
const unsigned int ONE_MINUTE = ONE_SECOND * 60;
const unsigned int ONE_HOUR = ONE_MINUTE * 60;

// How often temp and humidity should be updated
const unsigned long CHECK_INTERVAL = 5 * 1000;
unsigned long checkTimer = 0;

int EncoderTracking;
Timer* updateDisplayTimer; Timer* idleTimeoutTimer; Timer* buttonPress; Timer* buttonIgnore;

// Object that handles the humidity controller state
HumidityControllerStateMachine* hcsm;

// Object that handles timers
TimerManager* tm;

// Object that handles the LCD
LcdController* lcdc;

// Initializes the encoder knob for input
void initEncoder(){
}

void pollDisplay(HumidityControllerState state) {
	lcdc->updateDisplay(state);
}

void disableLED(){
	digitalWrite(13, LOW);
}

void doNothing(){}

void setup() {
	// Serial.begin(9600);
	pinMode(13, OUTPUT);
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	// Initialize Encoder Knob
	initEncoder();

	hcsm = new HumidityControllerStateMachine();
	tm = new TimerManager();
	
	lcdc = new LcdController(2, 16, &(hcsm->t1), &(hcsm->t2), &(hcsm->h1), &(hcsm->h2), &(hcsm->useCelcius), &(hcsm->targetHumidty));
	hcsm->stateChanged = &pollDisplay;

	// buttonIgnore = tm->addTimer(500, &toggleLED, false, true);
	buttonPress = tm->addTimer(ONE_SECOND, &disableLED, false, true);
	
	//Add Humidity Controller State Machine
	// idleTimeoutTimer = tm->addTimer(5 * ONE_SECOND, (timeoutFunctionPtr)(&(hcsm->idleTimeout)), true, true);
}

// Called every loop to handle encoder input including no input
bool pushed = false;
void handleEncoderInput() {
	if (digitalRead(4) == LOW && digitalRead(3) == HIGH && digitalRead(2) == HIGH) { // Pressed
		digitalWrite(13, HIGH);
		tm->startTimer(buttonPress);
		// if(buttonIgnore->enabled) return;

		// if (!buttonPress->enabled) {
		// 	tm->startTimer(buttonPress);
		// } else {
		// 	toggleLED();
		// 	hcsm->HandleInput(ENCODER_PRESS);
		// 	tm->startTimer(buttonIgnore);
		// 	tm->stopTimer(buttonPress);
	} else if (digitalRead(4) == HIGH && digitalRead(3) == LOW && digitalRead(2) == HIGH) { // Right
		hcsm->HandleInput(ENCODER_LEFT);
	} else if (digitalRead(4) == HIGH && digitalRead(3) == HIGH && digitalRead(2) == LOW) { // Left
		hcsm->HandleInput(ENCODER_RIGHT); 
	} else { // Idle
		hcsm->HandleInput(ENCODER_NONE);
		// tm->startTimer(idleTimeoutTimer);
		return;
	}
}

void loop() {
	// Serial.print("Pin 2: "); Serial.print(digitalRead(2) == HIGH ? "HIGH" : "LOW");
	// Serial.print("\tPin 3: "); Serial.print(digitalRead(3) == HIGH ? "HIGH" : "LOW");
	// Serial.print("\tPin 4: "); Serial.println(digitalRead(4) == HIGH ? "HIGH" : "LOW");
	// Keep timers running
	tm->tickTimers(millis());
	// switch (hcsm->currentState) {
	// 	case IDLE:
	// 		Serial.println("IDLE");
	// 		break;
	// 	case TEMP_SELECTED:
	// 		Serial.println("TEMP_SELECTED");
	// 		break;
	// 	case HUMIDITY_SELECTED:
	// 		Serial.println("HUMIDITY_SELECTED");
	// 		break;
	// 	case CHANGING_TEMP:
	// 		Serial.println("CHANGING_TEMP");
	// 		break;
	// 	case CHANGING_HUMIDITY:
	// 		Serial.println("CHANGING_HUMIDITY");
	// 		break;
	// }
	handleEncoderInput();
}