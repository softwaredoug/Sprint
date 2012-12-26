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

#endif // MSC_VER