#ifndef FORMAT_BASE_20121216_H
#define FORMAT_BASE_20121216_H

// %[flags][width][.precision][length]specifier 
#include <cstddef>


template <char specifier, typename srcT>
class Format
{
	char* operator()(char* dest, std::size_t destLen)
	{
		return dest;
	}
};

#endif FORMAT_BASE_20121216_H
