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
#include <stdint.h>

using namespace sprint;

#if _MSC_VER
#define snprintf _snprintf
#endif


TEST(BinToStr, BinNumericFormattingBasic) {
	char buff[50];
	Ape(buff, 50) << asHex<>(10);
    EXPECT_STREQ("a", buff);

	Ape(buff, 50) << asHex< bin::UpperHex >(10);
	EXPECT_STREQ("A", buff);

	Ape(buff, 50) << asOct(8);
	EXPECT_STREQ("10", buff);

	Ape(buff, 50) << asBin(8);
	EXPECT_STREQ("1000", buff);
}

TEST(BinToStr, SameAsSprintf) {
	char apeBuff[50];
	char sprintfBuff[50];

	// max 32-bit unsigned
	uint32_t max32 = 0xFFFFFFFF;
	Ape(apeBuff, 50) << asHex<>(max32);
	snprintf(sprintfBuff, 50, "%x", max32);
	EXPECT_STREQ(apeBuff, sprintfBuff);
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
		Ape(dest, 60) << "Hello " << asHex<>(i);
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
