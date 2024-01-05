//   packed_string_main.c
//   David Gregg
//   December 2022

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "packed_string.h"

// Note: parts of this function are deliberately badly written to
// obscure the meaning
int main() {
  // keep track of the number of errors encountered
  int nerrors = 0;
  
  // create a string to encode
  char str[] = "Into every generation a slayer is born";
  int x = strlen(str);

  // pack the string
  unsigned char * packed = string_to_packed(str);
  int t = (x << 3) - x;
  t = (t >> 3) + (t % 8 != 0);
  //printf("x:%d t:%d\n", x, t);

  // print out the packed string as a sequence of bytes in hexadecimal format
  printf("Original string: %s\n", str);
  printf("Packed string in hexadecimal: ");
  for ( int i = 0; i < t; i++ ) {
    printf("0x%x,", packed[i]);
  }
  printf("\n");

  // check the array of packed values
  unsigned char correct_packed_big_endian[] = {0x92,0xec,0xbf,0xb0,0x54,0xdb,0xd3,0x4f,0x3c,0x17,0x3a,0x6e,0xe9,0xa7,0x86,0x5e,0x5f,0xb7,0x60,0xa1,0x82,0xce,0x6e,0x1c,0xfa,0x69,0xc1,0x4b,0xce,0x9,0x1f,0xb4,0xee,0xc0};
  unsigned char correct_packed_little_endian[] = {0x49,0x37,0xfd,0xd,0x2a,0xdb,0xcb,0xf2,0x3c,0xe8,0x5c,0x76,0x97,0xe5,0x61,0x7a,0xfa,0xed,0x6,0x85,0x41,0x73,0x76,0x38,0x5f,0x96,0x83,0xd2,0x73,0x90,0xf8,0x2d,0x77,0x3}; 
  for ( int i = 0; i < x; i++ ) {
    if ( packed[i] != correct_packed_big_endian[i] &&
	 packed[i] != correct_packed_little_endian[i]) {
      fprintf(stderr,
	      "Error: Bad match between packed[%d]:%x and correct (big endian) [%d]:%x or correct (little endian) [%d]:%x\n",
	      i, packed[i], i, correct_packed_big_endian[i],
	      i, correct_packed_little_endian[i]);
      nerrors++;
    }
  }
  fprintf(stderr, "%d errors encountered while packing\n", nerrors);

  //unpack the characters
  char * unpacked;
  unpacked = packed_to_string(packed);

  // check that the result of unpacking is the same as the original
  nerrors = 0;
  for ( int i = 0; i < x; i++ ) {
    if ( unpacked[i] != str[i] ) {
      fprintf(stderr, "Error: Bad match between %c and %c at %d\n",
	      unpacked[i], str[i], i);
      nerrors++;
    }
  }
  fprintf(stderr, "%d errors encountered while unpacking\n", nerrors);
  return 0;
}
