#ifndef FORMAT_BASE_20121216_H
#define FORMAT_BASE_20121216_H

// %[flags][width][.precision][length]specifier 
// Except:
//  (1)the * params to width/precision for printf are runtime params,
//     they are not included here
//  (2)length is ommited in favor of type deduction
// Supported specifiers:
//   d,i == integer			allowed types, integer
//   u == unsigned decimal	allowed types
//   o == unsigned octal
//   x == unsigned hex, lower
//   X == unsigned hex, upper case
//   f == decimal float
//   s == string
#include <cstddef>

#define SPRINT_COMPILETIME_INTTOSTR(i) #i

namespace sprint
{
	enum class flags : char
	{
		NoFlags = 0,
		LeftJustify =	 0x01,
		IncludeSign =	 0x02,
		OctHexPrefix =	 0x04,
		ZeroPad =		 0x08,
	};

	static const int DefaultWidth = -1;
	static const int DefaultPrecision = -1;

	template <flags flags, int width, char precision, char specifier, typename srcT>
	class Sprint
	{
	private:
		static const char* formatStr;

	public:
		std::size_t append(char* dest, const std::size_t destLen, srcT val)
		{
			return sprintf_s(dest, destLen, formatStr, val);
		}



	};

	template <flags flags, int width, char precision, char specifier, typename srcT>
	const char*  Sprint<flags, width, precision, specifier, srcT>::formatStr = 
	{SPRINT_COMPILETIME_INTTOSTR(width), '.',
				SPRINT_COMPILETIME_INTTOSTR(precision),
				specifier, '\0'};
	
}

#endif FORMAT_BASE_20121216_H
