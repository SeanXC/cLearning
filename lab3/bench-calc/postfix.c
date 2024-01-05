#include "postfix.h"
#include <string.h>
#include <math.h>

int is_operator(char *token) {
    if (strlen(token) == 1) {
        switch(token[0]) {
            case '+':
            case '-':
            case 'X':
            case '/':
            case '^':
                return 1;
            default:
                return 0;
        }
    }
    return 0;
}

double evaluate_postfix_expression(char ** args, int nargs) {
    struct double_stack *my_stack = double_stack_new(nargs);
    double num2, num1, result;

    for(int i = 0; i < nargs; i++) {
        if(!is_operator(args[i])) {
            //it is an operand
            double number = atof(args[i]);
            double_stack_push(my_stack, number);
        } else {
            //token is a operator
            switch (args[i][0]) {
                case '+':
                    num2 = double_stack_pop(my_stack);
                    num1 = double_stack_pop(my_stack);
                    result = num1 + num2;
                    double_stack_push(my_stack, result);
                    break;

                case '-':
                    num2 = double_stack_pop(my_stack);
                    num1 = double_stack_pop(my_stack);
                    result = num1 - num2;
                    double_stack_push(my_stack, result);
                    break;

                case 'X':
                    num2 = double_stack_pop(my_stack);
                    num1 = double_stack_pop(my_stack);
                    result = num1 * num2;
                    double_stack_push(my_stack, result);
                    break;

                case '/':
                    num2 = double_stack_pop(my_stack);
                    num1 = double_stack_pop(my_stack);
                    result = num1 / num2;
                    double_stack_push(my_stack, result);
                    break;

                case '^':
                    num2 = double_stack_pop(my_stack);
                    num1 = double_stack_pop(my_stack);
                    result = pow(num1, num2);
                    double_stack_push(my_stack, result);
                    break;
            }
        }
    }
    return double_stack_pop(my_stack);
}
