#include "stack.h"

struct double_stack * double_stack_new(int max_size) 
{
    struct double_stack *result;
    result = malloc(sizeof(struct double_stack));

    result -> items = malloc(max_size * sizeof(double));

    result -> max_size = max_size;
    result -> top = -1  ;
    return result;
    
}

// push a value onto the stack
void double_stack_push(struct double_stack * this, double value) {
    if(this->top>=(this->max_size-1))
    {
        double *result = malloc(sizeof(double)*2*this -> max_size);
        for(int i =0; i < this->max_size; i++)
        {
            result[i] = this->items[i];
        }
        free(this->items);
        this->items = result;
        this->max_size = this -> max_size*2;
    }
    this->top++;
    this->items[this->top] = value;

}

// pop a value from the stack
double double_stack_pop(struct double_stack * this) {
    if(this->top==-1)
        return -1.0;
    double tmp = this->items[this->top];
    this->top--;
    return tmp;
}


