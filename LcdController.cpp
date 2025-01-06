#include <LiquidCrystal.h>
#include <Arduino.h>
#include <stdio.h>
#include "LcdController.h";
#include "HumidityControllerStateMachine.h";

LcdController::LcdController(
	int height, 
	int width, 
	int* t1,
	int* t2,
	int* h1,
	int* h2,
	bool* useCelcius, int* targetH
) : lcd(19, 18, 5, 6, 7, 8) {
	this->lcd.begin(width, height);
	this->lcd.home();
	this->lcd.clear();
	this->useCelcius = useCelcius;
	this->t1 = t1;
	this->t2 = t2;
	this->h1 = h1;
	this->h2 = h2;
	this->useCelcius = useCelcius;
	this->targetH = targetH;
}

void LcdController::updateDisplay(HumidityControllerState state)
{
	this->lcd.clear();
	this->lcd.setCursor(0, 0);
	char lineOne[17];
	char lineTwo[17];
	memset(lineOne, 0, 17);
	memset(lineTwo, 0, 17);
	switch(state){
		case IDLE:
			// this->lcd.noDisplay();
			break;
		case NONE_SELECTED:
			break;
		case TEMP_SELECTED:
			sprintf(lineOne, ">Temp: %d%s%d%c%s", *(this->t1), ".", *(this->t2), 0xDF, this->useCelcius ? "C" : "F");
			sprintf(lineTwo, "Humi: %d.%d%", *(this->h1), *(this->h2));
			break;
		case HUMIDITY_SELECTED:
			sprintf(lineOne, "Temp: %d%s%d%c%s", *(this->t1), ".", *(this->t2), 0xDF, this->useCelcius ? "C" : "F");
			sprintf(lineTwo, ">Humi: %d.%d%", *(this->h1), *(this->h2));
			break;
		case CHANGING_TEMP:
			sprintf(lineOne, "    %cC    %cF    ", 0xDF, 0xDF);
			sprintf(lineTwo, this->useCelcius ? "       ^" : "           ^");
			break;
		case CHANGING_HUMIDITY:
			sprintf(lineOne, "");
			sprintf(lineTwo, "Set Humi.: >%d<", *(this->targetH));
			// lineOne = "Temp: ";// + String(*(this->t1)) + String(".") + String(*(this->t2)) + char(0xDF) + String(this->useCelcius ? "C" : "F");
			// lineTwo = String("Set Humi.: >");// + *(this->targetH) + String("%<");
			break;
	}

	this->writeLineOne(lineOne);
	this->writeLineTwo(lineTwo);
}

void LcdController::writeLineOne(char line[]) {
	this->lcd.setCursor(0,0);
	this->lcd.print(String(line));
}
void LcdController::writeLineTwo(char line[]) {
	this->lcd.setCursor(0,1);
	this->lcd.print(String(line));
}