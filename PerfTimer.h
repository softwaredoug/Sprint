#ifndef PERF_TIMER_2012_12_16_H
#define PERF_TIMER_2012_12_16_H

#include <memory>
#include <stdint.h>

// This is a performance timer intended to run on either Linux or Windows
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
	uint64_t Stop();

	// TODO:
	// uint64_t toMicroSec();
};

#endif