#include "HumidityControllerStateMachine.h";
#include <Arduino.h>

HumidityControllerStateMachine::HumidityControllerStateMachine() {
	this->currentState = TEMP_SELECTED;
	
	this->t1 = 11;
	this->t2 = 22;
	this->h1 = 33;
	this->h2 = 44;

	this->targetHumidty = 65; this->useCelcius = false;
}
// 
void HumidityControllerStateMachine::HandleInput(HumidityControllerInput input) {
	switch (this->currentState){
		case IDLE:
			if (input != ENCODER_NONE) {
				this->setState(TEMP_SELECTED);
			}
			break;
		case TEMP_SELECTED:
			if (input == ENCODER_PRESS) {
				this->setState(CHANGING_TEMP);
			} else if (input == ENCODER_RIGHT) {
				this->setState(HUMIDITY_SELECTED);
			}
			break;
		case HUMIDITY_SELECTED:
			if (input == ENCODER_PRESS) {
				this->setState(CHANGING_HUMIDITY);
			} else if (input == ENCODER_LEFT) {
				this->setState(TEMP_SELECTED);
			}
			break;
		case CHANGING_TEMP:
			if (input == ENCODER_PRESS) {
				this->setState(TEMP_SELECTED);
			} else if (input == ENCODER_RIGHT) {
				this->useCelcius = false;
				this->setState(CHANGING_TEMP);
			} else if (input == ENCODER_LEFT) {
				this->useCelcius = true;
				this->setState(CHANGING_TEMP);
			}
			break;
		case CHANGING_HUMIDITY:
			if (input == ENCODER_PRESS) {
				this->setState(HUMIDITY_SELECTED);
			} else if (input == ENCODER_RIGHT) {
				this->targetHumidty++;
				this->setState(CHANGING_HUMIDITY);
			} else if (input == ENCODER_LEFT) {
				this->targetHumidty--;
				this->setState(CHANGING_HUMIDITY);
			}
			break;
	}
}

void HumidityControllerStateMachine::setState(HumidityControllerState state) {
	// if (this->currentState == IDLE && state != IDLE) return;
	
	this->currentState = state;
	this->stateChanged(state);
}

void HumidityControllerStateMachine::idleTimeout() {
	this->setState(IDLE);
}
