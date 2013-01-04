#ifndef PERF_TIMER_2012_12_16_H
#define PERF_TIMER_2012_12_16_H

#include <memory>
#include <stdint.h>

// This is a performance timer intended to run on either Linux or Windows

typedef uint64_t tick_t;

class PerfTimer
{
private:
	class PerfTimerImpl;
	std::unique_ptr<PerfTimerImpl> m_impl;
public:
	PerfTimer();

	virtual ~PerfTimer();

	// Start the timer
	void Start();

	// Stop the timer
	tick_t Stop();

    // Convert ticks to nanoseconds for friendly io
	static double toNanoSecs(tick_t numTicks);
};

#endif
