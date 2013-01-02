#include "stdafx.h"
#include "Ape.h"
#include <string>
#include "SprintBase.h"

namespace sprint {


Ape::Ape(char* init, size_t initSize) : 
	m_baseStr(init),  m_totalBytes(initSize), m_cursor(0)
{
}

Ape::Ape(Ape&& other) {
	m_baseStr = other.m_baseStr;
	m_cursor = other.m_cursor;
	m_totalBytes = other.m_totalBytes;

	other.m_baseStr = NULL;
	other.m_cursor = other.m_totalBytes = 0;

}

Ape Ape::operator<<(SprintBase&& val) {
	// Append val onto this, move into temporary
	if (m_cursor < m_totalBytes)
	{
		size_t rVal = val.AppendTo(&m_baseStr[m_cursor], m_totalBytes - m_cursor);
		if (rVal > 0)
		{
			m_cursor += rVal;
		}
	}
	return std::move(*this);
}

Ape Ape::operator<<(const char src[]) {
	char* currDest = &m_baseStr[m_cursor];
	char* end = m_baseStr + m_totalBytes;
	const char* currSrc = &src[0];
	size_t bytesWritten = 0;
	while (currDest < end && *currSrc)
	{
		*currDest++ = *currSrc++;
		++bytesWritten;
	}
	m_cursor += bytesWritten;
	return std::move(*this);
}

}