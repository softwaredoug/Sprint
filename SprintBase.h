#ifndef SPRINT_BASE_20121230_H
#define SPRINT_BASE_20121230_H

namespace sprint {

// Sprints will
// - have constructors that hold a copy of whats going to be appended
//   to the buffer. For complex types, a pointer or reference should be
//   passed in.
// - they will implement an size_t appendTo(char*, size_t) that will
//   basically do what sprintf would do
//   - return the number of bytes written 
//	 - return -1 on an error
//   - an expected error: the passed in size_t is insufficient or negative
//     that means the end-user did not give Ape a big enough buffer. Do
//     nothing and return -1
//
class SprintBase
{
public: 
	SprintBase() {}

	virtual ~SprintBase() {}

	virtual size_t AppendTo(char* dest, size_t destSize) = 0;
};

}

#endif