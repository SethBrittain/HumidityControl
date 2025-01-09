#include <Arduino.h>
#include "HumidityControllerStateMachine.h"
#include "Timers.h"
#include "LcdController.h"

const int ENCODER_DEBOUNCE_MS = 175;
const int IDLE_TIMEOUT_MS = 5 * ONE_SECOND;
const int IDLE_REFRESH_MS = 1 * ONE_MINUTE;

Timer* idleTimeoutTimer;
Timer* idleRefreshTimer;
HumidityControllerStateMachine* hcsm;
LcdController* lcd;


bool ignorePress;
long lastInput;
void setup() {
	ignorePress = false;

	lastInput = 0;
	hcsm = new HumidityControllerStateMachine();
	lcd = new LcdController(2, 16, &hcsm->t1, &hcsm->t2, &hcsm->h1, &hcsm->h2, &hcsm->useCelcius, &hcsm->targetHumidty);

	stateChangedFunctionPtr stateChangeRefresh = [hcsm](){
		lcd->updateDisplay(hcsm->currentState);
	};
	hcsm->stateChanged = stateChangeRefresh;


	TimerCallback idleTimeoutCallback = [hcsm](){
		if (hcsm->currentState != IDLE)
		{
			hcsm->idleTimeout();
		}
	};
	idleTimeoutTimer = new Timer(IDLE_TIMEOUT_MS, idleTimeoutCallback);

	// TimerCallback idleRefreshCallback = [hcsm](){
	// 	// if (hcsm->currentState == IDLE)
	// 	// 	lcd->updateDisplay(IDLE);
	// };
	// idleRefreshTimer = new Timer(IDLE_REFRESH_MS, idleRefreshCallback);

	hcsm->idleTimeout();
}

HumidityControllerInput HandleInput() {
	if (millis() < lastInput + ENCODER_DEBOUNCE_MS)
		return ENCODER_NONE;

	bool pressed = digitalRead(4) == LOW 
		&& digitalRead(3) == HIGH
		&& digitalRead(2) == HIGH;
	
	bool left = digitalRead(4) == HIGH
		&& digitalRead(3) == HIGH
		&& digitalRead(2) == LOW;
	
	bool right = digitalRead(4) == HIGH
		&& digitalRead(3) == LOW
		&& digitalRead(2) == HIGH;

	HumidityControllerInput input;
	if (pressed) {
		if (ignorePress) return ENCODER_NONE;
		input = ENCODER_PRESS;
		ignorePress = true;
	} else if (left) {
		input = ENCODER_LEFT;
	} else if (right) {
		input = ENCODER_RIGHT;
	} else {
		input = ENCODER_NONE;
		ignorePress = false;
	}
	return input;
}

void loop() {
	// Just pin 4 LOW is encoder press
	// Just pin 3 LOW is right
	// Just pin 2 LOW is left

	idleTimeoutTimer->Tick();
	// idleRefreshTimer->Tick();
	
	HumidityControllerInput input = HandleInput();
	if (input != ENCODER_NONE) {
		lastInput = millis();
		idleTimeoutTimer->Bump();
	}
	hcsm->HandleInput(input);

	// if (pin) {
	// 	hcsm->HandleInput(ENCODER_PRESS);
	// } else if (left) {
	// 	hcsm->HandleInput(ENCODER_LEFT);
	// } else if (right) {
	// 	hcsm->HandleInput(ENCODER_RIGHT);
	// } else {
	// 	hcsm->HandleInput(ENCODER_NONE);
	// }
}
