// Sprint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include "PerfTimer.h"

#include "format_x.h"


int main(int argc, char* argv[])
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	PerfTimer timer;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		Sprint<sprint::flags::NoFlags, -1, -1, 'x', uint32_t>::append(dest, 60, i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Doug:" << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		sprintf_s(dest2, 60, "%x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:" << dest2 << " Time: " << elapsed <<  std::endl;

}

