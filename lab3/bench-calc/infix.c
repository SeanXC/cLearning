#include "infix.h"
#include "postfix.h"
#include "stack.h"
#include <assert.h>

char* operator2String(char operator)
{
    char* result = malloc(sizeof(char)*2);
    result[0]=operator;
    result[1]='\0';
    return result;
}

double double_stack_peek(struct double_stack*stack)
{
    assert(!double_stack_empty(stack));
    return stack->items[stack->top];
}

int is_left_bracket(char op)
{
    return op=='(';
}
int is_right_bracket(char op)
{
    return op ==')';
}

int precedence(char operator)
{
    switch(operator)
    {
        case '^':
            return 3;
        case 'X':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}


// evaluate expression stored as an array of string tokens
double evaluate_infix_expression(char ** args, int nargs)
{
    struct double_stack *opStack = double_stack_new(nargs);
    int post_nargs = 0;
    char **postfix = malloc(sizeof(char *) * nargs);

    for (int i = 0; i < nargs; i++)
    {
        if(!is_operator(args[i]) && !is_left_bracket(args[i][0]) && !is_right_bracket(args[i][0]))
        {
            postfix[post_nargs++] = args[i];
        } else if(is_left_bracket(args[i][0]))
        {
            double_stack_push(opStack, (double)'(');
        }


        else if(is_right_bracket(args[i][0]))
        {
            while((char)double_stack_peek(opStack) != (double )'(')
            {
                postfix[post_nargs++] = operator2String((char)double_stack_pop(opStack));
            }
            double_stack_pop(opStack);
        }

        else if(is_operator(args[i]))
        {
            while (!double_stack_empty(opStack) && (precedence((char)double_stack_peek(opStack))
                                                    >= precedence(args[i][0])))
            {
                postfix[post_nargs++] = operator2String((char)double_stack_pop(opStack));
            }
            double_stack_push(opStack, (double)args[i][0]);
        }

    }
    while(!double_stack_empty(opStack))
    {
        postfix[post_nargs++] = operator2String((char)double_stack_pop(opStack));
    }


    return evaluate_postfix_expression(postfix, post_nargs);

}