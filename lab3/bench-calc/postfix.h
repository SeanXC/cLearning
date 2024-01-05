#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "stack.h"


int is_operator(char *token);

double evaluate_postfix_expression(char ** expr, int nterms);

#endif
