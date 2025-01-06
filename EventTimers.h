#include <stdlib.h>

#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

typedef void (*timeoutFunctionPtr)();

typedef struct {
	public:
		bool enabled;
		bool oneShot;
		int duration;
		timeoutFunctionPtr timeout;
		unsigned long lastRun;
} Timer;

class TimerManager {
	public:
		// The number of timers added
		int timerCount = 0;
		TimerManager();
		void tickTimers(unsigned long currentTime);
		Timer* addTimer(int delay, timeoutFunctionPtr fn, bool enabled, bool oneShot);
		void startTimer(Timer* t);
		void stopTimer(Timer* t);
	private:
		Timer** timers;
};

#endif