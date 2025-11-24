#ifndef CLOCKS_H
#define CLOCKS_H

#include <chrono>

//Clocks for timestamping reports and orders + testing

//Clock interface
struct IClock {
	virtual std::chrono::system_clock::time_point now() const = 0;
	virtual ~IClock() = default;
};

//System clock
struct SystemClock : IClock {
	std::chrono::system_clock::time_point now() const override;
};

//Test clock that has some limited testing functionality like advancing time
struct TestClock : IClock {
	std::chrono::system_clock::time_point current;

	explicit TestClock(std::chrono::system_clock::time_point start) : current(start) {}

	std::chrono::system_clock::time_point now() const override;

	void advance(std::chrono::hours h);
};

#endif
