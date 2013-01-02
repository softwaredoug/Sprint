#ifndef APE_20121230_H
#define APE_20121230_H

#include <stdint.h>
#include <cstddef>

namespace sprint {

class SprintBase;

// Ape associated with buffer you passed in,
// it "apes" the buffer.
//
// It acts as a kind of stringbuilder object, constantly
// using Sprints passed into it via the + operator to append to
// internal buffer.
//
// Sprints are just little objects that take a char* and size and
// append whatever they hold to the char*
//
// As it uses the magic of rvalue references, the performance
// of this is incredible
//
// Its intended to be used in an expression, ie:
//
// char dest[60];
// Ape(dest, 60) + S("Hello my name is ") + Ss(name) + " my age is:" + Si(age);
//
class Ape {
public:
	// ownership to this memory is retained by
	// client code, we are only aping it for you for 
	// formatting
	Ape(char* init, size_t initSize);

	Ape(Ape&& other);

	// Append
	Ape operator << (SprintBase&& spr);

	// Possibly also take a const char* for 
	Ape operator << (const char* val);

private:
	char* m_baseStr;
	size_t m_totalBytes;
	size_t m_cursor;
};

}
#endif