#include "stdafx.h"
#ifdef __posix__
#include <time.h>

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

}


class PerfTimer::PerfTimerImpl
{
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
}


#endif