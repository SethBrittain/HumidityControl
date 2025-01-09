#ifndef TIMERS_H
#define TIMERS_H

// Time in ms
const unsigned int ONE_SECOND = 1000;
const unsigned int ONE_MINUTE = ONE_SECOND * 60;
const unsigned int ONE_HOUR = ONE_MINUTE * 60;

typedef void (*TimerCallback)();

class Timer {
	private:
		int lastRun;
		int durationMillis;
		TimerCallback callback;
	public:
		Timer(int durationMillis, TimerCallback);
		void Bump();
		void Tick();
};

#endif