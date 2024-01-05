// morse_code.h
// David Gregg
// December 2023

extern char* morse_table[];

void morse_encode(char * input, char * output, char ** morse_table);
void morse_decode(char * input, char * output, char ** morse_table);
