#ifndef SPRINT_BIN_SETTINGS_20121230_H
#define SPRINT_BIN_SETTINGS_20121230_H


namespace sprint { namespace bin {

	// Configure pad 
	template <unsigned int _minWidth, char _padChar>
	class Pad {
	public:
		static inline std::size_t charWidth(std::size_t charsNeeded)
		{
			return (charsNeeded > _minWidth) ? charsNeeded : _minWidth;
		}
		static inline void pad(char* currPos, std::size_t width, std::size_t charsNeeded)
		{
			// pad width - charsNeeded
			std::size_t remainingChars = width - charsNeeded;
			if (remainingChars > 0)
			{
				while (remainingChars > 0)
				{
					*currPos-- = _padChar;
					remainingChars--;
				}
			}
		}
	};

	// no padding, default
	template <>
	class Pad<0, '\0'> {
	public:
		static inline std::size_t charWidth(std::size_t widthNeeded) {return widthNeeded;}
		static inline void pad(char* , std::size_t , std::size_t )
		{

		}
	};

	typedef Pad<0, '\0'> NoPad;
		
	// Configure the hex case
	enum class HexCase : bool {
		lower = false,
		upper = true,
	};

	template <HexCase>
	class Case {};

	template <>
	class Case<HexCase::upper> {
	public:
		static char lookup[16];
	};

	typedef Case<HexCase::upper> UpperHex;

	char Case<HexCase::upper>::lookup[16] =  { '0', '1', '2', '3', '4', '5', '6', '7', '8',
									  '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	template <>
	class Case<HexCase::lower> {
	public:
		static char lookup[16];

	};

	typedef Case<HexCase::lower> LowerHex;

	char Case<HexCase::lower>::lookup[16] =  { '0', '1', '2', '3', '4', '5', '6', '7', '8',
									  '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	// 2^4 = hex, 2^3 = oct, etc
	enum PowerConsts {
		bin = 1,
		oct = 3,
		hex = 4,
	};

	template <int _p>
	class Power
	{
	public:
		enum 
		{
			pow = _p,
			mask = (1 << _p) - 1,
		};
	};

}}

static_assert( sprint::bin::Power<4>::mask == 0xf, "Power template not correctly calculating mask for hex");
static_assert( sprint::bin::Power<3>::mask == 0x7, "Power template not correctly calculating mask for oct");
static_assert( sprint::bin::Power<1>::mask == 0x1, "Power template not correctly calculating mask for bin");

#endif
