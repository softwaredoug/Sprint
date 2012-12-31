// Sprint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdint.h>
#include "PerfTimer.h"
#include <string>
#include "Ape.h"
#include "SprintBin.h"

class Sprint2
{
	uint32_t val;
public:
	Sprint2(uint32_t valToFormat) : val(valToFormat) {}

	void AppendTo(std::string& str)
	{
		char asStr[9];
		_itoa_s(val, &asStr[0], 9, 16); 
		str.append(asStr, 9);
	}
};

std::string operator + (std::string&& lhs, Sprint2&& rhs)
{
	rhs.AppendTo(lhs);
	return std::move(lhs);

}


int main(int argc, char* argv[])
{
	using namespace sprint;
	char dest[60] = {'\0'};
	char dest2[60] = {'\0'};
	PerfTimer timer;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		Ape(dest2, 60) + "Hello " + SpBin< Power<4> >(i);
	}
	uint64_t elapsed = timer.Stop();
	std::cout << "Doug:" << dest << " Time: " << elapsed <<  std::endl;

	PerfTimer timer2;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		sprintf_s(dest2, 60, "Hello %x", i);
	}
	elapsed = timer2.Stop();

	std::cout << "SprintF:" << dest2 << " Time: " << elapsed <<  std::endl;

	std::string foo = "";
	PerfTimer timer3;
	for (unsigned int i = 0xf; i < 100; ++i)
	{
		foo = std::string() + Sprint2(i);
	}
	elapsed = timer3.Stop();

	std::cout << "Sprint2" << foo << " Time: " << elapsed << std::endl;	

}

