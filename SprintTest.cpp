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

namespace
{
	const unsigned int begin = 0;
	const unsigned int end = 0x00ffffff;
	const unsigned int step = 3571;
}


void perfSinglHex()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	std::string dest3;
	std::cout << "Single Hex perf test\n";
	
	PerfTimer timer;
	for (unsigned int i = begin; i < end; i+=step)
	{
		Ape(dest, 60) << "Hello " << asHexL<>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:       " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = begin; i < end; i+=step)
	{
		snprintf(dest2, 60, "Hello %x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:      " << dest2 << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = begin; i < end; i+=step)
	{
        dest3 = str(fmt::Format("Hello {0:x}") << i);
    }
	elapsed = timer3.Stop();

	std::cout << "Format:       " << dest3 << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = begin; i < end; i+=step)
	{
		oss.clear(); oss.str("");
		oss << "Hello " << std::hex << i;
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream: " << oss.str() << " Time: " << elapsed <<  std::endl;
}

void perfSingleOct()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	std::string dest3;
	std::cout << "Single Oct perf test\n";

	PerfTimer timer;
	for (unsigned int i = begin; i < end; i+=step)
	{
		Ape(dest, 60) << "Hello " << asOct<>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:        " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = begin; i < end; i+=step)
	{
		snprintf(dest2, 60, "Hello %o", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:       " << dest2 << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = begin; i < end; i+=step)
	{
        dest3 = str(fmt::Format("Hello {0:o}") << i);
    }
	elapsed = timer3.Stop();

	std::cout << "Format:        " << dest3 << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = begin; i < end; i+=step)
	{
		oss.clear(); oss.str("");
		oss << "Hello " << std::oct << i;
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream:  " << oss.str() << " Time: " << elapsed <<  std::endl;
}

void perfSinglHexPad()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
    std::string dest3;
    std::cout << "Single Hex perf test\n";

	PerfTimer timer;
	for (unsigned int i = begin; i < end; i+=step)
	{
		Ape(dest, 60) << "Hello " << asHexL< bin::Pad<8, '0'>>(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Sprint:      " << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = begin; i < end; i+=step)
	{
		snprintf(dest2, 60, "Hello %08x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:     " << dest << " Time: " << elapsed <<  std::endl;

    PerfTimer timer3;
	for (unsigned int i = begin; i < end; i+=step)
	{
        dest3 = str(fmt::Format("Hello {0:08x}") << i);
    }
	elapsed = timer3.Stop();

	std::cout << "Format:      " << dest3 << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = begin; i < end; i+=step)
	{
		oss.str("");
		oss << "Hello " << std::setw(8) << std::setfill('0') << std::hex << i;
	}
	elapsed = timer4.Stop();

	std::cout << "stringstream: " << oss.str().c_str() << " Time: " << elapsed <<  std::endl;
}


void perfBinCsv()
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	//char dest3[60] = {'\0'};
	std::string dest3;
    std::cout << "Bin->Str CSV perf test\n";

	PerfTimer timer;
	for (unsigned int i = begin; i < end; i+=step)
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
	for (unsigned int i = begin; i < end; i+=step)
	{
		snprintf(dest2, 60, "Hello %x,%o,%X,%08x,%08o,%08X", i, i+1, i+2, i+3,i+4, i+5);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:     " << dest2 << " Time: " << elapsed <<  std::endl;

	fmt::Formatter format;
	PerfTimer timer3;
	for (unsigned int i = begin; i < end; i+=step)
	{
		using fmt::FormatSpec;
		format.Clear();
        format << "Hello ";
        format.Write(i, FormatSpec(0, 'x'));
        format << ",";
        format.Write(i + 1, FormatSpec(0, 'o'));
        format << ",";
        format.Write(i + 2, FormatSpec(0, 'X'));
        format << ",";
        format.Write(i + 3, FormatSpec(8, 'x', '0'));
        format << ",";
        format.Write(i + 4, FormatSpec(8, 'o', '0'));
        format << ",";
        format.Write(i + 5, FormatSpec(8, 'X', '0'));
        format << '\0';
        //strcpy(dest3, format.c_str()); // This is not required because the output buffer is directly accessible*/
        //dest3 = str(fmt::Format("Hello {0:x},{1:o},{2:X},{3:08x},{4:08o},{5:08X}") << i << (i+1) << (i+2) << (i+3) << (i+4) << (i+5));
    }
	elapsed = timer3.Stop();

	std::cout << "Format:      " << format.c_str() << " Time: " << elapsed <<  std::endl;

	std::ostringstream oss;
	PerfTimer timer4;
	for (unsigned int i = begin; i < end; i+=step)
	{
		oss.str("");
		oss << "Hello " << std::nouppercase
            << std::hex << i << ',' 
            << std::oct << (i+1) << ','
            << std::hex << std::uppercase << (i+2) << ','
            << std::hex << std::nouppercase << std::setfill('0') << std::setw(8) << (i+3) << ','
            << std::oct << std::setfill('0') << std::setw(8) <<  (i+4) << ','
            << std::hex << std::setfill('0') << std::setw(8) << std::uppercase << (i+5);
	}
	elapsed = timer4.Stop();
	std::cout << "ostringstream " << oss.str() << " Time: " << elapsed <<  std::endl;

	fmt::Formatter format2;
	PerfTimer timer5;
	for (unsigned int i = begin; i < end; i+= step)
	{
		format2.Clear();
		format2 << "Hello " ;
        format2 << format::sprint::asHexL<>(i) ;
        format2 << ",";
        format2 << format::sprint::asOct<>(i+1);
        format2 << ",";
        format2 << format::sprint::asHexU<>(i+2);
        format2 << ",";
        format2 << format::sprint::asHexL< format::sprint::Pad<8, '0'>>(i+3); 
        format2 << ",";
        format2 << format::sprint::asOct< format::sprint::Pad<8, '0'>>(i+4);
        format2 << ",";
        format2 << format::sprint::asHexU< format::sprint::Pad<8, '0'>>(i+5);
	}
	elapsed = timer5.Stop();

	std::cout << "format w/sprint:" << format2.c_str() << " Time: " << elapsed <<  std::endl;
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
