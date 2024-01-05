#ifndef __INFIX_H__
#define __INFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "postfix.h"

double evaluate_infix_expression(char ** expr, int nterms);
char* operator2String(char operator);
double double_stack_peek(struct double_stack*stack);
int is_left_bracket(char op);
int is_right_bracket(char op);
int precedence(char operator);


#endif
