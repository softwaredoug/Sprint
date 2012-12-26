#ifndef FORMAT_X_20121206
#define FORMAT_X_20121206
#include "format_base.h"
#include <stdint.h>

template <>
class Format<'x', uint32_t>
// 32 bits has 8 nibbles
{
public:
	static char lookup[16];

	static inline size_t charLen(uint32_t val)
	{
		size_t rVal = 0;
		while (val)
		{
			++rVal;
			val = val >> 4;
		}
		return rVal;
	}

	// Append to dest, returning num chars written
	static size_t append(char* dest, const size_t destLen, uint32_t val)
	{
		size_t charsNeeded = charLen(val);
		char* cursor = dest + (charsNeeded);
		*cursor-- = '\0';
		*cursor = '0';
		while (val)
		{
			int lookupKey = val & 0xf;
			*cursor-- = lookup[val & 0xf];
			val = val >> 4;
		}
		return charsNeeded;
	}

	// Append using move semantics

};

#endif