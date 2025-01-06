#include <stdlib.h>
#include "EventTimers.h"
#include <Arduino.h>

// Should be called in the loop function
// Keeps track of the timers and calls the timeout function when the timer is up and resets the timer
void TimerManager::tickTimers(unsigned long currentTime) {
	for (int i = 0; i < this->timerCount; i++) {
		Timer* currentTimer = this->timers[i];
		if (!currentTimer->enabled) continue; // Skip disabled timers

		if (currentTime > currentTimer->lastRun + currentTimer->duration) {
			if (currentTimer->oneShot) {
				stopTimer(currentTimer);
			}
			currentTimer->lastRun = currentTime;
			(currentTimer->timeout)();
		}
	}
}

// Adds a timer to the timer manager
Timer* TimerManager::addTimer(int delay, timeoutFunctionPtr fn, bool enabled, bool oneShot) {
	Timer* t = (Timer*)malloc(sizeof(Timer));
	t->enabled = enabled;
	t->oneShot = oneShot;
	t->duration = delay;
	t->timeout = fn;
	t->lastRun = delay;
	this->timers = (Timer**)realloc(this->timers, sizeof(Timer*) * (this->timerCount + 1));
	this->timers[this->timerCount] = t;
	this->timerCount++;
}

void TimerManager::startTimer(Timer* t) {
	t->lastRun = millis();
	t->enabled = true;
}
void TimerManager::stopTimer(Timer* t) {
	t->enabled = false;
}

TimerManager::TimerManager(){}