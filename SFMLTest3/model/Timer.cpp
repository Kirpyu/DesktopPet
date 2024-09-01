#include "Timer.h"

namespace widget {
	Timer::Timer(sf::Time t) : wait_time(t) {
		elapsed_time += clock.restart();
	}

	Timer::~Timer() {

	}

	//while the game is running, the timer takes the amount of time that has elapsed, then if it is
	//already greater than the wait time, then return true, clock restarts and reset the time elapsed
	bool Timer::timerElapsed() {
		elapsed_time = clock.getElapsedTime();
		if (elapsed_time >= wait_time) {
			clock.restart();
			return true;
		}
		return false;
	}
}
