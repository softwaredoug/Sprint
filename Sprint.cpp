// Sprint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include "PerfTimer.h"
#include <string>
#include <utility>
#include "Ape.h"
#include "SprintBin.h"
#include "format/format.h"

#if _MSC_VER
#define snprintf _snprintf
#endif

int main(int argc, char* argv[])
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	char dest3[60] = {'\0'};
	PerfTimer timer;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		Ape(dest, 60) << "Hello " << asHexL<>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Doug:" << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		snprintf(dest2, 60, "Hello %x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:" << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
        fmt::Format("Hello {0:x}") << 1;
    }
	elapsed = timer3.Stop();

	std::cout << "Format:" << dest << " Time: " << elapsed <<  std::endl;


}	
