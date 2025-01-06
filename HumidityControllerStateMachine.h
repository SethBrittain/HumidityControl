#include "EventTimers.h";

#ifndef HUMIDITY_CONTROLLER_STATE_MACHINE_H
#define HUMIDITY_CONTROLLER_STATE_MACHINE_H

enum HumidityControllerState
{
  IDLE,
  NONE_SELECTED,
  HUMIDITY_SELECTED,
  TEMP_SELECTED,
  CHANGING_TEMP,
  CHANGING_HUMIDITY
};

enum HumidityControllerInput
{	
	ENCODER_NONE,
	ENCODER_PRESS,
	ENCODER_RIGHT,
	ENCODER_LEFT
};

class HumidityControllerStateMachine
{
	public:
		HumidityControllerState currentState;
		void (*stateChanged)(HumidityControllerState);
		int t1;
		int t2;
		int h1;
		int h2;
		int targetHumidty;
		bool useCelcius;
		HumidityControllerStateMachine();
		void HandleInput(HumidityControllerInput input);
		void idleTimeout();
	private:
		void HumidityControllerStateMachine::setState(HumidityControllerState state);
};

#endif