#include "stdafx.h"
#ifdef SPRINT_POSIX
#include <time.h>
#include <iostream>
#include <assert.h>
#include "PerfTimer.h"

namespace
{
	int64_t toNsecTimestamp(const timespec* ts)
	{
        int64_t sec64 = ts->tv_sec;
		return ts->tv_nsec + (sec64 * 1000000000);
	}


	// lhs - rhs in ns
	int64_t deltaTimespecNs(const timespec* lhs, const timespec* rhs)
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

	tick_t Stop()
	{
		clock_gettime(CLOCK_MONOTONIC, &end);
	    int64_t rVal = deltaTimespecNs(&end, &begin);
        assert(rVal > 0); 
        return rVal;
	}

	static double toNanoSecs(tick_t numTicks)
    {
        return numTicks;
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

tick_t PerfTimer::Stop()
{
    return m_impl->Stop();
}

PerfTimer::~PerfTimer()
{
}

double PerfTimer::toNanoSecs(tick_t numTicks)
{
    return PerfTimerImpl::toNanoSecs(numTicks);
}
#endif
