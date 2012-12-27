#include "stdafx.h"
#include "format_base.h"
#include "format_x.h"

#define SPRINT_COMPILETIME_INTTOSTR(i) #i	

namespace sprint
{

	char Sprint<sprint::flags::NoFlags, -1, -1, 'x', uint32_t>::lookup[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
	'9', 'a', 'b', 'c', 'd', 'e', 'f'};


}