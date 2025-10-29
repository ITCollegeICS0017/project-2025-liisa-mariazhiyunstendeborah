#ifndef CLOCKS_H
#define CLOCKS_H

#include <chrono>

struct IClock {
	virtual std::chrono::system_clock::time_point now() const = 0;
	virtual ~IClock() = default;
};

struct SystemClock : IClock {
	std::chrono::system_clock::time_point now() const override;
};

struct TestClock : IClock {
	std::chrono::system_clock::time_point current;

	explicit TestClock(std::chrono::system_clock::time_point start) : current(start) {}

	std::chrono::system_clock::time_point now() const override;

	void advance(std::chrono::hours h);
};

#endif
