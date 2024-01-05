// morse_code_main.c
// David Gregg
// December 2023

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "morse_code.h"

int main() {
  char plain1[] = "AEIOU";
  char morse1[] = ".- . .. --- ..- ";
  char output_morse1[4096] = "";
  char output_plain1[4096] = "";
  
  char plain2[] = "NO SPOON";
  char morse2[] = "-. --- ... .--. --- --- -. ";
  char output_morse2[4096] = "";
  char output_plain2[4096] = "";
  
  fprintf(stderr, "Test morse encode 1:\n");
  fprintf(stderr, "  plain input1: \"%s\"\n", plain1);
  morse_encode(plain1, output_morse1, morse_table);
  fprintf(stderr, "  student morse output1: \"%s\"\n", output_morse1);
  if (strcmp(output_morse1, morse1) == 0 ) {
    fprintf(stderr, "  Encode correct 1: \"%s\" == \"%s\"\n", output_morse1, morse1);
  }
  else {
    fprintf(stderr, "  Encode error 1: \"%s\" != \"%s\"\n", output_morse1, morse1);
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "Test morse encode 2:\n");
  fprintf(stderr, "  plain input2: \"%s\"\n", plain2);
  morse_encode(plain2, output_morse2, morse_table);
  fprintf(stderr, "  student morse output2: \"%s\"\n", output_morse2);
  if (strcmp(output_morse2, morse2) == 0 ) {
    fprintf(stderr, "  Encode correct 2: \"%s\" == \"%s\"\n", output_morse2, morse2);
  }
  else {
    fprintf(stderr, "  Encode error 2: \"%s\" != \"%s\"\n", output_morse2, morse2);
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "Test morse decode 1:\n");
  fprintf(stderr, "  morse input1: \"%s\"\n", morse1);
  morse_decode(morse1, output_plain1, morse_table);
  fprintf(stderr, "  student plaintext output1: \"%s\"\n", output_plain1);
  if (strcmp(output_plain1, plain1) == 0 ) {
    fprintf(stderr, "  Decode correct 1: \"%s\" == \"%s\"\n", output_plain1, plain1);
  }
  else {
    fprintf(stderr, "  Decode error 1: \"%s\" != \"%s\"\n", output_plain1, plain1);
  }
  fprintf(stderr, "\n");

  fprintf(stderr, "Test morse decode 2:\n");
  fprintf(stderr, "  morse input2: \"%s\"\n", morse2);
  morse_decode(morse2, output_plain2, morse_table);
  fprintf(stderr, "  student plaintext output2: \"%s\"\n", output_plain2);
  if (strcmp(output_plain2, plain2) == 0 ) {
    fprintf(stderr, "  Decode correct 2: \"%s\" == \"%s\"\n", output_plain2, plain2);
  }
  else {
    fprintf(stderr, "  Decode error 2: \"%s\" != \"%s\"\n", output_plain2, plain2);
  }
  fprintf(stderr, "\n");
  
  return 0;
}
