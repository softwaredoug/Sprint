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


TEST(BinToStr, NumericFormattingBasic) {
	char buff[50];
	Ape(buff, 50) << asHexL<>(10);
    EXPECT_STREQ("a", buff);

	Ape(buff, 50) << asHexU<>(10);
	EXPECT_STREQ("A", buff);

	Ape(buff, 50) << asOct<>(8);
	EXPECT_STREQ("10", buff);

	Ape(buff, 50) << asBin<>(8);
	EXPECT_STREQ("1000", buff);
}

TEST(BinToStr, PadFormatting) {
	char buff[50] = {'\0'};
	char shortBuff[5] = {'\0'};

	using namespace sprint::bin;
	// Check the positive case
	Ape(buff, 50) << asHexL< Pad<8, '0'>>(11);
	EXPECT_STREQ("0000000b", buff);

	Ape(buff, 50) << asBin< Pad<8, ' '>>(11);
	EXPECT_STREQ("    1011", buff);

	Ape(buff, 50) << asHexL< Pad<1, ' '>>(1000);
	EXPECT_STREQ("3e8", buff);

	// Check trying to pad more than buff
	Ape(shortBuff, 5) << asHexL< Pad<8, ' '>>(1);
	EXPECT_STREQ("", shortBuff); 
}

TEST(BinToStr, SameAsSprintf) {
	char apeBuff[50];
	char sprintfBuff[50];

	// max 32-bit unsigned
	uint32_t max32 = 0xFFFFFFFF;
	Ape(apeBuff, 50) << asHexL<>(max32);
	snprintf(sprintfBuff, 50, "%x", max32);
	EXPECT_STREQ(apeBuff, sprintfBuff);
}


// Sprint.cpp : Defines the entry point for the console application.
//


void perfSinglHex()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	char dest3[60] = {'\0'};
	std::cout << "Single Hex perf test\n";
	const unsigned int min = 0xf;
	const unsigned int max = 1000;
	PerfTimer timer;
	for (unsigned int i = min; i < max; ++i)
	{
		Ape(dest, 60) << "Hello " << asHexL<>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:       " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = min; i < max; ++i)
	{
		snprintf(dest2, 60, "Hello %x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:      " << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = min; i < max; ++i)
	{
        fmt::Format("Hello {0:x}") << i;
    }
	elapsed = timer3.Stop();

	std::cout << "Format:       " << dest << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = min; i < max; ++i)
	{
		oss << std::hex << i;
		oss.clear(); oss.str("");
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream:" << dest << " Time: " << elapsed <<  std::endl;
}

void perfSingleOct()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	char dest3[60] = {'\0'};
	std::cout << "Single Oct perf test\n";
	const unsigned int min = 0xf;
	const unsigned int max = 1000;
	PerfTimer timer;
	for (unsigned int i = min; i < max; ++i)
	{
		Ape(dest, 60) << "Hello " << asOct<>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:        " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = min; i < max; ++i)
	{
		snprintf(dest2, 60, "Hello %o", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:       " << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = min; i < max; ++i)
	{
        fmt::Format("Hello {0:o}") << i;
    }
	elapsed = timer3.Stop();

	std::cout << "Format:        " << dest << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = min; i < max; ++i)
	{
		oss << std::oct << i;
		oss.clear(); oss.str("");
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream:  " << dest << " Time: " << elapsed <<  std::endl;
}

void perfSinglHexPad()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
    std::string dest3;
    std::cout << "Single Hex perf test\n";
	const unsigned int min = 0xf;
	const unsigned int max = 1000;
	PerfTimer timer;
	for (unsigned int i = min; i < max; ++i)
	{
		Ape(dest, 60) << "Hello " << asHexL< bin::Pad<8, '0'>>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:      " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = min; i < max; ++i)
	{
		snprintf(dest2, 60, "Hello %08x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:     " << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = min; i < max; ++i)
	{
        dest3 = str(fmt::Format("Hello {0:08x}") << i);
    }
	elapsed = timer3.Stop();

	std::cout << "Format:      " << dest3 << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = min; i < max; ++i)
	{
		oss << std::setw(8) << std::setfill('0') << std::hex << i;
		oss.clear(); oss.str("");
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream: " << oss.str().c_str() << " Time: " << elapsed <<  std::endl;
}


void perfBinCsv()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
    std::string dest3;
    std::cout << "Bin->Str CSV perf test\n";
	const unsigned int min = 0xf;
	const unsigned int max = 1000;
	PerfTimer timer;
	for (unsigned int i = min; i < max; ++i)
	{
		Ape(dest, 60) << "Hello " 
                      << asHexL<>(i) 
                      << ","
                      << asOct<>(i+1)
                      << ","
                      << asHexU<>(i+2)
                      << ","
                      << asHexL< bin::Pad<8, '0'>>(i+3) 
                      << ","
                      << asOct< bin::Pad<8, '0'>>(i+4)
                      << ","
                      << asHexU< bin::Pad<8, '0'>>(i+5);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:      " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = min; i < max; ++i)
	{
		snprintf(dest2, 60, "Hello %x,%o,%X,%08x,%08o,%08X", i, i+1, i+2, i+3,i+4, i+5);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:     " << dest2 << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = min; i < max; ++i)
	{
        dest3 = str(fmt::Format("Hello {0:x},{1:o},{2:X},{3:08x},{4:08o},{5:08X}") << i << (i+1) << (i+2) << (i+3) << (i+4) << (i+5));
    }
	elapsed = timer3.Stop();

	std::cout << "Format:      " << dest3 << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = min; i < max; ++i)
	{
		oss.clear(); oss.str("");
		oss << "Hello " << std::nouppercase
            << std::hex << i << ',' 
            << std::oct << (i+1) << ','
            << std::hex << std::uppercase << (i+2) << ','
            << std::hex << std::nouppercase << std::setfill('0') << std::setw(8) << (i+3) << ','
            << std::oct << std::setfill('0') << std::setw(8) <<  (i+4) << ','
            << std::hex << std::setfill('0') << std::setw(8) << std::uppercase << (i+5);
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream:" << oss.str() << " Time: " << elapsed <<  std::endl;
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
	perfSinglHex();
	perfSingleOct();
	perfSinglHexPad();
    perfBinCsv();
    return rVal;
}
