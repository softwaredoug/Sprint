#include "stdafx.h"
#include <time.h>
#include "PerfTimer.h"

namespace
{
	int toNsecTimestamp(const timespec* ts)
	{
		return ts->tv_nsec + (ts->tv_sec * 1000000000);
	}


	// lhs - rhs in ns
	int deltaTimespecNs(const timespec* lhs, const timespec* rhs)
	{
		return toNsecTimestamp(lhs) - toNsecTimestamp(rhs);
	}

};


class PerfTimer::PerfTimerImpl
{
public:
	timespec begin;
	timespec end;

	PerfTimerImpl()
	{
		clock_gettime(CLOCK_MONOTONIC, &begin);
		clock_gettime(CLOCK_MONOTONIC, &end);
	}

	void Start()
	{
		clock_gettime(CLOCK_MONOTONIC, &begin);
	}

	uint64_t Stop()
	{
		clock_gettime(CLOCK_MONOTONIC, &end);
		return deltaTimespecNs(&end, &begin);
	}
};

PerfTimer::PerfTimer() :
    m_impl(new PerfTimerImpl())
{

}

void PerfTimer::Start()
{
    m_impl->Start();
}

uint64_t PerfTimer::Stop()
{
    return m_impl->Stop();
}

PerfTimer::~PerfTimer()
{
}

