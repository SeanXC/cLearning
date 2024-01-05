//   packed_string.h
//   David Gregg
//   December 2020

#ifndef PACKED_STRING_H
#define PACKED_STRING_H

// pack the 7-bit values of the string into memory
unsigned char * string_to_packed(char * string);

// unpack bytes of memory containing 7-bit characters into a string
char * packed_to_string(unsigned char * packed_string);

#endif
