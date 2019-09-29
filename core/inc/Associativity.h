#ifndef ASSOCIATIVITY_H
#define ASSOCIATIVITY_H
enum Associativity{
	left=0x0001,
	right=0x0002,
	none=0x0004,
	pre=0x0008,
	post=0x0010,
	one=0x0020,
	bracket=0x0040
};
#define BINARY (left|right|none|one)
#endif