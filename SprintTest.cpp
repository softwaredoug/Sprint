#include <gtest/gtest.h>

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include "PerfTimer.h"
#include <string>
#include <utility>
#include "Ape.h"
#include "SprintBin.h"
#include "format.h"

#ifndef sprintf_s
#define sprintf_s snprintf
#endif

TEST(DougTest, Foo) {
    EXPECT_EQ("","");
}


// Sprint.cpp : Defines the entry point for the console application.
//


int perf()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	char dest3[60] = {'\0'};
	PerfTimer timer;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		Ape(dest, 60) + "Hello " + SpBin< Power<4> >(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Doug:" << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		sprintf_s(dest2, 60, "Hello %x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:" << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
        fmt::Format("Hello {0:x}") << i;
    }
	elapsed = timer3.Stop();

	std::cout << "Format:" << dest << " Time: " << elapsed <<  std::endl;


}
