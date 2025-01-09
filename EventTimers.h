// #include <stdlib.h>

// #ifndef TIMER_MANAGER_H
// #define TIMER_MANAGER_H

// // Time in ms
// const unsigned int ONE_SECOND = 1000;
// const unsigned int ONE_MINUTE = ONE_SECOND * 60;
// const unsigned int ONE_HOUR = ONE_MINUTE * 60;

// typedef int (*millisFunctionPtr)();
// typedef void (*timeoutFunctionType)();

// typedef struct {
// 	public:
// 		bool enabled;
// 		bool oneShot;
// 		int duration;
// 		timeoutFunctionType timeout;
// 		unsigned long lastRun;
// } Timer;

// class TimerManager {
// 	public:	
// 		millisFunctionPtr getMillis;
// 		Timer* AddTimer(int delay, timeoutFunctionType fn, bool enabled, bool oneShot);
// 		int Count();
		
// 		void TickTimers();
// 		void StartTimer(Timer* t);
// 		void StopTimer(Timer* t);

// 		TimerManager(millisFunctionPtr mill);
// 	private:
// 		std::vector<Timer*> timers;
// };

// #endif