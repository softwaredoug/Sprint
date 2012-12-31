#ifndef SPRINT_BIN_SETTINGS_20121230_H
#define SPRINT_BIN_SETTINGS_20121230_H


namespace sprint {
	enum class HexCase {
		lower = false,
		upper = true,
	};

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
			mask = (1 << (_p + 1)) - 1,
		};
	};

}

#endif