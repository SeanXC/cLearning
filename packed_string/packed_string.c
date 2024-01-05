//   packed_string.c
//   David Gregg
//   December 2022

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "packed_string.h"


// pack the 7-bit values of the string into memory
unsigned char * string_to_packed(char * string)
{
    int string_length = strlen(string);
    int packed_in_bytes = (string_length * 7)/8;
    if ((string_length * 7)%8 != 0)
    {
        packed_in_bytes++;
    }
    unsigned  char *result = malloc(packed_in_bytes);
    int packed_index = 0;
    int mask = 127; // the mask to get lower 7 bits 1111111;
    int size_in_byte = 8;
    for(int i = 0; i< string_length; i++)
    {
        int bit_pos = 7*i;
        unsigned char copy_letter = string[i] & mask;
        result [packed_index] = copy_letter << bit_pos;
        if(bit_pos >= size_in_byte)
        {
            bit_pos = bit_pos - size_in_byte;
        }
        packed_index++;
        if (bit_pos > 0) {
            result[packed_index] = copy_letter >> (7 - bit_pos);
        }
    }
}



// unpack bytes of memory containing 7-bit characters into a string
char * packed_to_string(unsigned char * packed_string) {
    // Check if the input packed string is NULL. If so, return NULL.
    if (packed_string == NULL) return NULL;
int original_length = (strlen(packed_string) * 8)/7;
    // Allocate memory for the unpacked string, including space for the null terminator.
    char *unpacked_string = malloc(original_length + 1);
    if (unpacked_string == NULL) return NULL;  // Check for successful allocation.

    // Initialize variables for tracking our position in the packed string.
    int packed_index = 0, bit_index = 0;

    // Iterate over each character in the original string (before packing).
    for (int i = 0; i < original_length; i++) {
        // Extract the current 7 bits from the packed string.
        unsigned char temp = packed_string[packed_index] >> bit_index;

        // If the next 7 bits span across two bytes in the packed string, handle that.
        if (bit_index + 7 >= 8) {
            packed_index++;  // Move to the next byte in the packed string.
            temp |= packed_string[packed_index] << (8 - bit_index);  // Extract the remaining bits from the next byte.
        }

        // Store the extracted 7 bits in the unpacked string.
        unpacked_string[i] = temp & 0x7F;  // Mask to ensure only 7 bits are stored.

        // Update the bit index for the next iteration.
        bit_index = (bit_index + 7) % 8;
    }

    // Null-terminate the unpacked string.
    unpacked_string[original_length] = '\0';

    return unpacked_string;  // Return the unpacked string.
}


