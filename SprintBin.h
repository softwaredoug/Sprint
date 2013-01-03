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
template <typename PowerT, typename CaseT = bin::LowerHex, typename PadT = bin::NoPad>
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
		std::size_t width = PadT::charWidth(charsNeeded);
		if (width > destLen)
		{
			return 0;
		}
		char* cursor = dest + (width);
		*cursor-- = '\0';
		*cursor = '0';
		while (m_val)
		{
			int lookupKey = m_val & PowerT::mask;
			*cursor-- = CaseT::lookup[m_val & PowerT::mask];
			m_val = m_val >> PowerT::pow;
		}
		PadT::pad(cursor, width, charsNeeded);
		return width;
	}

	// Append using move semantics

};

// Specialize for padding

}

namespace sprint {

// default hex formatters


// configurable versions, use inheritance
template <typename PadT = bin::NoPad> 
class asHexL : public SpBin< bin::Power<4>, bin::LowerHex, PadT> 
	{ 
	public:
		asHexL(uint32_t val) : SpBin<bin::Power<4>, bin::LowerHex, PadT>(val) {}
	};


template <typename PadT = bin::NoPad> 
class asHexU : public SpBin< bin::Power<4>, bin::UpperHex, PadT> 
	{ 
	public:
		asHexU(uint32_t val) : SpBin<bin::Power<4>, bin::UpperHex, PadT>(val) {}
	};

template <typename PadT = bin::NoPad> 
class asOct : public SpBin< bin::Power<3>, bin::LowerHex, PadT> 
	{ 
	public:
		asOct(uint32_t val) : SpBin<bin::Power<3>, bin::LowerHex, PadT>(val) {}
	};


template <typename PadT = bin::NoPad> 
class asBin : public SpBin< bin::Power<1>, bin::LowerHex, PadT> 
	{ 
	public:
		asBin(uint32_t val) : SpBin<bin::Power<1>, bin::LowerHex, PadT>(val) {}
	};
}
#endif
