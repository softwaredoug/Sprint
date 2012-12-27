#include "stdafx.h"
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

	uint64_t Stop()
	{
		clock_gettime(CLOCK_MONOTONIC, &end);
	    int64_t rVal = deltaTimespecNs(&end, &begin);
        assert(rVal > 0); 
        return rVal;
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

