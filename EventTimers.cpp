// #include <stdlib.h>
// #include <Arduino.h>
// #include "EventTimers.h"

// // Should be called in the loop function
// // Keeps track of the timers and calls the timeout function when the timer is up and resets the timer
// void TimerManager::TickTimers() {
// 	for (int i = 0; i < this->Count(); i++) {
// 		int currentTime = this->getMillis();
// 		Timer* currentTimer = this->timers[i];
// 		if (!currentTimer->enabled) continue; // Skip disabled timers

// 		if (currentTime > currentTimer->lastRun + currentTimer->duration) {
// 			if (currentTimer->oneShot) {
// 				stopTimer(currentTimer);
// 			}
// 			currentTimer->lastRun = currentTime;
// 			(currentTimer->timeout)();
// 		}
// 	}
// }

// // Adds a timer to the timer manager
// Timer* TimerManager::AddTimer(int delay, timeoutFunctionType fn, bool enabled, bool oneShot) {
// 	Timer* t = new Timer();
// 	t->enabled = enabled;
// 	t->oneShot = oneShot;
// 	t->duration = delay;
// 	t->timeout = fn;
// 	t->lastRun = this->getMillis();

// 	this->timers.push_back(t);
// 	return t;
// }

// void TimerManager::StartTimer(Timer* t) {
// 	t->lastRun = millis();
// 	t->enabled = true;
// }
// void TimerManager::StopTimer(Timer* t) {
// 	t->enabled = false;
// }

// int TimerManager::Count() {
// 	return this->timers.size();
// }

// TimerManager::TimerManager(millisFunctionPtr mill) : timers(std::vector<Timer*>()), millis{ mill }{}