#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "morse_code.h"

const int letter_count = 26;

char morse_a[] = ".-";
char morse_b[] = "-...";
char morse_c[] = "-.-.";
char morse_d[] = "-..";
char morse_e[] = ".";
char morse_f[] = "..-.";
char morse_g[] = "--.";
char morse_h[] = "....";
char morse_i[] = "..";
char morse_j[] = ".---";
char morse_k[] = "-.-";
char morse_l[] = ".-..";
char morse_m[] = "--";
char morse_n[] = "-.";
char morse_o[] = "---";
char morse_p[] = ".--.";
char morse_q[] = "--.-";
char morse_r[] = ".-.";
char morse_s[] = "...";
char morse_t[] = "-";
char morse_u[] = "..-";
char morse_v[] = "...-";
char morse_w[] = ".--";
char morse_x[] = "-..-";
char morse_y[] = "-.--";
char morse_z[] = "--..";

char* morse_table[] = {morse_a, morse_b, morse_c, morse_d,
                       morse_e, morse_f, morse_g, morse_h, morse_i, morse_j, morse_k,
                       morse_l, morse_m, morse_n, morse_o, morse_p, morse_q, morse_r,
                       morse_s, morse_t, morse_u, morse_v, morse_w, morse_x, morse_y,
                       morse_z};

// Function to encode a string of text into Morse code
void morse_encode(char *input, char *output, char **morse_table)
{
    int out_index = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == ' ')
        {
            output[out_index++] = '_';  // Encode space as underscore in Morse code
            output[out_index++] = ' ';  // Add a space after the underscore
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')
        {
            int letter_index = input[i] - 'A';  // Calculate the index in the Morse code table
            strcpy(&output[out_index], morse_table[letter_index]);  // Copy Morse code for the letter
            out_index += strlen(morse_table[letter_index]);  // Move the output index
            output[out_index++] = ' ';  // Add a space after the Morse code for letter separation
        }
    }
    output[out_index] = '\0';  // Null-terminate the output string
}

// Function to decode a string of Morse code back into text
void morse_decode(char *input, char *output, char **morse_table)
{
    int input_index = 0, output_index = 0;
    while (input[input_index] != '\0')
    {
        if (input[input_index] == '_')
        {
            output[output_index++] = ' ';  // Decode underscore back to space
            input_index += 2;  // Skip the underscore and the following space
        }
        else
        {
            char morse_char[10];  // Temporary storage for the Morse code of one character
            int morse_index = 0;
            // Collect Morse code for one character
            while (input[input_index] != ' ' && input[input_index] != '\0')
            {
                morse_char[morse_index++] = input[input_index++];
            }
            morse_char[morse_index] = '\0';  // Null-terminate the Morse code string
            if (input[input_index] == ' ') input_index++;  // Move past the space after Morse code
            // Find the letter corresponding to the Morse code
            for (int i = 0; i < letter_count; i++)
            {
                if (strcmp(morse_char, morse_table[i]) == 0)
                {
                    output[output_index++] = 'A' + i;  // Decode Morse code to letter
                    break;
                }
            }
        }
    }
    output[output_index] = '\0';  // Null-terminate the output string
}

