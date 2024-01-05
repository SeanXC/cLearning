//   nybble_array.c
//   David Gregg
//   December 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "nybble_array.h"


// create a new array of nybbles with space for "size"
// nybbles and initialize the values of the array to zero
struct nybble_array * nybble_array_new(int size) {

    struct nybble_array *new_array = malloc(sizeof(struct nybble_array));
    new_array->size_in_nybbles = size;
    new_array->size_in_bytes = size / 2;
    if ((size%2) != 0)
    {
        new_array->size_in_bytes++;
    }
    new_array->data_bytes= malloc(new_array->size_in_bytes);
    for(int i=0; i< new_array->size_in_bytes; i++)
    {
        new_array->data_bytes[i] = 0;
    }
    return new_array;
}

// return the nybble value at position index
unsigned get_nybble_value(struct nybble_array * this, int index) {
    int byteIndex = index / 2;
    unsigned char copyByte = this->data_bytes[byteIndex];
    if (index % 2 == 0) {
        return copyByte & 0x0F;
    } else {
        return (copyByte >> 4) & 0x0F;
    }
}

// set the nybble at position index to value
void set_nybble_value(struct nybble_array * this, int index, unsigned value) {
    int byteIndex = index / 2;
    value &= 0x0F;  // Ensure value is only a nybble
    if (index % 2 == 0) {
        this->data_bytes[byteIndex] = (this->data_bytes[byteIndex] & 0xF0) | value;
    } else {
        this->data_bytes[byteIndex] = (this->data_bytes[byteIndex] & 0x0F) | (value << 4);
    }
}
// free the memory used by a nybble array
void nybble_array_free(struct nybble_array * this) {
    if (this != NULL)
    {
        if (this->data_bytes != NULL)
        {
            free(this->data_bytes);
        }
        free(this);
    }
}

// given an array of unsigned integers with values 0 to 15 create
// a new nybble_array with the same values
struct nybble_array * unsigned_to_nybble_array(unsigned * array, int size) {
    struct nybble_array *new_array = nybble_array_new(size);
    if (!new_array) return NULL;
    for (int i = 0; i < size; i++) {
        set_nybble_value(new_array, i, array[i]);
    }
    return new_array;
}

// given an array of nybbles, create a new array of unsigned integers
// with the same values
unsigned * nybble_array_to_unsigned(struct nybble_array * this) {
    if (!this) return NULL;
    unsigned *new_array = malloc(this->size_in_nybbles * sizeof(unsigned));
    if (!new_array) return NULL;
    for (int i = 0; i < this->size_in_nybbles; i++) {
        new_array[i] = get_nybble_value(this, i);
    }
    return new_array;
}

// print the raw byte content of the nybble array
void print_raw_bytes_nybble_array(struct nybble_array * this) {
    for ( int i = 0; i < this->size_in_bytes; i++ ) {
        printf("%x ", this->data_bytes[i]);
    }
    printf("\n");
}

