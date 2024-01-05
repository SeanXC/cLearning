#include "bitset.h"

// include the standard library header files that we use in this
// program, which are denoted by angle brackets < >
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// define constant dummy values to avoid compiler warnings
static const int dummy_integer_value = -99;
static struct bitset * dummy_pointer_value = NULL;

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset *result = (struct bitset *)malloc(sizeof(struct bitset));
    result->universe_size = size;
    int  size_in_word = size / 64;
    if(size % 64 > 0)
    {
        size_in_word ++;
    }
    result->bits = malloc(size_in_word * sizeof(uint64_t));
    for(int i =0; i<size_in_word; i++)
    {
        result->bits[i] = 0;
    }
    result->size_in_words = size_in_word;
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this)
{
    return this->universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this)
{
    int count = 0;
    for(int i = 0; i < this->size_in_words; i++)
    {
        uint64_t set = this->bits[i];
        uint64_t mask = 1ull;
        while (set)
        {
//            if (set & mask)
//            {
//                count++;
//            }
//            mask = mask << 1;
            count = count +(set&mask);
            set = set>>1;
        }
    }
    return  count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int word_size = sizeof(uint64_t) * 8;
    uint64_t  mask = 1ull;
    int word_index = item / word_size;
    int bit_index = item % word_size;
    mask = mask << bit_index;
    if(this->bits[word_index] & mask)
    {
        return 1;
    } else
        return 0;
    //  return (this->bits[word_index] & mask);
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    int word_size = sizeof(uint64_t) * 8;
    int word_index = item / word_size;
    int bit_index = item % word_size;
    uint64_t  mask = 1ull;
    mask = mask << bit_index;
    this->bits[word_index] |= mask;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    int word_size = sizeof(uint64_t) * 8;
    int word_index = item / word_size;
    int bit_index = item % word_size;
    uint64_t  mask = 1ull;
    mask = mask << bit_index;
    mask = ~mask;
    this->bits[word_index] &= mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
                  struct bitset * src2)
{
    for(int i =0; i< src1->size_in_words; i++)
    {
        dest->bits[i] = src1->bits[i]|src2->bits[i];
    }
}
// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
                      struct bitset * src2)
{
    for(int i =0; i< src1->size_in_words; i++)
    {
        dest->bits[i] = src1->bits[i]& src2->bits[i];
    }
}
