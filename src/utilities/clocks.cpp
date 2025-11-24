#include "clocks.h"

std::chrono::system_clock::time_point SystemClock::now() const {
	return std::chrono::system_clock::now();
}

std::chrono::system_clock::time_point TestClock::now() const {
return current;
}

//input hours are added to current time
void TestClock::advance(std::chrono::hours h) {
current += h;
}
