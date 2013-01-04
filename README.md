(WORK IN PROGRESS, NOT READY FOR PRODUCTION)

Sprint
======
Type-safe and high-performance string formatting library. Example:

 
    char buff[50];
    unsigned int i = 0xffffffff;
    Ape(buff, 50) << "Here's some Hex: " << asHexL<>(i); 

Internally, "Ape" simply apes the buffer. It holds a char pointer, a length, and the current write position. The overloaded << operator takes an object known as a "Sprint" and passes the buffer's current position and remaining length in for formatting. In the above example `asHexL<>(i)` is Sprint built-in to the library to format as lowercase hex. Convenience << implementations exist to allow direct appending of string literals and integers. 

###Specify Formatting at Compile Time, not Run Time
The built-in Sprints all specify how the formatting should occur at compile time. This strategy allows specialization of formatting for specific use-cases. For example, the implementation of `asHexL<Pad(8,'0')>` can theoretically be a different string formatting implementation highly optimized for that specific case.

More importantly, 

###The compiler catches formatting bugs
Because we don't rely on format strings, and instead rely on the semantics of C++, the compiler catches are bugs for us. And it does it in a way thats almost two orders of magnitude faster than ostringstream, the other option that allows the compiler to catch formatting bugs.

###Better Performance than sprintf
Because we don't need format strings, we can get up to an order of magnitude of performance gain over MSCV's snprintf. We can get at least 3 or 4 times faster than libc's snprintf. These are initial benchmarks with hex and oct formatting.

###Other Great Libraries
This library trades-off size for speed. Due to the use of lots of compile-time features, its likely that this library will cause your binaries to grow compared to other implementations.

If format strings is more your speed, I recommend the [format library](https://github.com/vitaut/format) by Victor Zverovich.
