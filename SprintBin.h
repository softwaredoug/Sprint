#ifndef FORMAT_X_20121206
#define FORMAT_X_20121206
#include "SprintBase.h"
#include <cstddef>
#include <stdint.h>
#include "SprintBinSettings.h"


namespace sprint {

// TODO:
//  (1) add padding pad<char>
//  (2) define for arbitrary integer size
//  (3) add sign: sign<char>
//  (4) add upper/lower for binary
//  (5) minimize potential code bloat
//  (6) test
template <typename PowerT>
class SpBin : public SprintBase
{
private:
	uint32_t m_val;
public:
	SpBin(uint32_t val) : m_val(val)
	{

	}
	static char lookup[16];


	static inline std::size_t charLen(uint32_t val)
	{
		std::size_t rVal = 0;
		while (val)
		{
			++rVal;
			val = val >> PowerT::pow;
		}
		return rVal;
	}

	// Append to dest, returning num chars written
	size_t AppendTo(char* dest, size_t destLen)
	{
		std::size_t charsNeeded = charLen(m_val);
		char* cursor = dest + (charsNeeded);
		*cursor-- = '\0';
		*cursor = '0';
		while (m_val)
		{
			int lookupKey = m_val & PowerT::mask;
			*cursor-- = lookup[m_val & PowerT::mask];
			m_val = m_val >> PowerT::pow;
		}
		return charsNeeded;
	}

	// Append using move semantics

};

template<typename PowerT>
char SpBin<PowerT>::lookup[16] =  { '0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'a', 'b', 'c', 'd', 'e', 'f'};
}

namespace sprint {

typedef SpBin< bin::Power<4> > asHex;
typedef SpBin< bin::Power<3> > asOct;
typedef SpBin< bin::Power<1> > asBin;
}

#endif
