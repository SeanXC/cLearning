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

void morse_encode(char * input, char * output, char ** morse_table) {
    int out_index =0;
    for(int i = 0; input[i]!= '\0'; i++)
    {
        if(input[i] == ' ')
        {
            output[out_index++] = '_';
            output[out_index++] = ' ';
        }

            int letter_index = input[i] - 'A';
            strcpy(&output[out_index], morse_table[letter_index]);
            out_index += strlen(morse_table[letter_index]);
            output[out_index++] = ' ';
    }
}

void morse_decode(char * input, char * output, char ** morse_table) {
    int input_index = 0;
    int output_index = 0;
    while (input[input_index] != '\0')
    {
        if (input[input_index] == '_')
        {
            output[output_index++] = ' ';
            input_index += 2; //skip the first 2 empty input
        }
        else
        {
            char morse_char[10];
            int morse_index = 0;
            while (input[input_index] != ' ' && input[input_index] != '\0')
            {
                morse_char[morse_index++] = input[input_index++];
            }
            if (input[input_index] == ' ') input_index++;
            for (int i = 0; i < strlen(input); i++)
            {
                if (strcmp(morse_char, morse_table[i]) == 0)
                {
                    output[output_index++] = 'A' + i;
                    break;
                }
            }
        }
    }
}

