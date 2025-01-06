#include <LiquidCrystal.h>
#include <Arduino.h>
#include "HumidityControllerStateMachine.h";
#ifndef LCD_CONTROLLER_H
#define LCD_CONTROLLER_H

// Degree Symbol


class LcdController {
	LiquidCrystal lcd;
	public:
		int* t1;
		int* t2;
		int* h1;
		int* h2;
		int* targetH;
		bool* useCelcius;

		LcdController(
			int height, 
			int width, 
			int* t1,
			int* t2,
			int* h1,
			int* h2,
			bool* useCelcius, int* targetH
		);
		void updateDisplay(HumidityControllerState state);
		void idleTimeout();
	private:
		void writeLineOne(char line[]);
		void writeLineTwo(char line[]);
};

#endif