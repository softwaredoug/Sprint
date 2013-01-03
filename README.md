Sprint
======

Experimental type-safe and high-performance string formatting library internally using move semantics. Example:


char buff[50];
unsigned int i = 0xffffffff;
Ape(buff) << "Here's some Hex" << asHex(i); 
