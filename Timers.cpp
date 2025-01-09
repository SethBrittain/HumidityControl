#include "Timers.h"
#include "Arduino.h"

Timer::Timer(int durationMillis, TimerCallback callback) : durationMillis(durationMillis), callback(callback) {
	lastRun = millis();
}

void Timer::Tick() {
	if (millis() > lastRun + durationMillis) {
		this->lastRun = millis();
		this->callback();
	}
}

void Timer::Bump() {
	this->lastRun = millis();
}