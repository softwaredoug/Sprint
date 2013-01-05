#include "stdafx.h"
#ifdef _MSC_VER // only compile this file in Windows
#include "Windows.h"
#include "PerfTimer.h"

class PerfTimer::PerfTimerImpl
{
private:
	LARGE_INTEGER begin;
	LARGE_INTEGER end;
public:

	PerfTimerImpl()
	{
		QueryPerformanceCounter(&begin);
		QueryPerformanceCounter(&end);
	}

	void Start()
	{
		QueryPerformanceCounter(&begin);
	}

	uint64_t Stop()
	{
		QueryPerformanceCounter(&end);
		return end.QuadPart - begin.QuadPart; 
	}
	
	static double toNanoSecs(tick_t numTicks)
	{
		LARGE_INTEGER ticksPerSecond;
		QueryPerformanceFrequency(&ticksPerSecond);
		
		double ticksPerNanoSeconds = (double)(ticksPerSecond.QuadPart) / (double)(1000000000);
		return numTicks * ticksPerNanoSeconds;
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

double PerfTimer::toNanoSecs(tick_t numTicks)
{
	return PerfTimerImpl::toNanoSecs(numTicks);
}

#endif // MSC_VER