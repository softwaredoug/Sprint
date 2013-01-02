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

using namespace sprint;

#if _MSC_VER
#define snprintf _snprintf
#endif

TEST(DougTest, Foo) {
	char buff[50];
	Ape(buff, 50) << "0x" << asHex(10);
    EXPECT_EQ("0xa", std::string(buff));
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
		Ape(dest, 60) << "Hello " << asHex(i);
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
        fmt::Format("Hello {0:x}") << i;
    }
	elapsed = timer3.Stop();

	std::cout << "Format:" << dest << " Time: " << elapsed <<  std::endl;
	return 0;

}

int main(int argc, char **argv) {
	#ifdef _WIN32
	// Disable message boxes on assertion failures.
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	#endif
	testing::InitGoogleTest(&argc, argv);
	int rVal = RUN_ALL_TESTS();
	perf();
	return rVal;
}
