#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct Node
{
    float data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

Stack *initialize()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

void push(Stack *s, float value)
{
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
}

float pop(Stack *s)
{
    if (s->top == NULL)
    {
        printf("Stack is empty\n");
        exit(0);
    }

    Node *n = s->top;
    float value = n->data;
    s->top = n->next;
    free(n);
    return value;
}

int isEmpty(Stack *s)
{
    return s->top == NULL;
}

float peek(Stack *s)
{
    if (s->top == NULL)
    {
        printf("Stack is empty\n");
        exit(0);
    }

    Node *n = s->top;
    float value = n->data;
    return value;
}

void display(Stack *s)
{
    Stack *copy = malloc(sizeof(Stack));
    copy->top = NULL;
    while (!isEmpty(s))
    {
        float x = pop(s);
        printf("%f\t", x);
        push(copy, x);
    }
    while (!isEmpty(copy))
        push(s, pop(copy));
    free(copy);
}

int precedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

char* infixTopostfix(char *infix)
{
    int j = 0;
    char *postfix = malloc(strlen(infix) + 1);
    Stack *operators = initialize();
    char *token = strtok(infix, " ");

    while (token != NULL)
    {
        if (token[0] == '(' && token[1] == '\0')
            push(operators, token[0]);
        else if (token[0] == ')' && token[1] == '\0')
        {
            while (!isEmpty(operators) && peek(operators) != '(')
            {
                postfix[j++] = pop(operators);
                postfix[j++] = ' ';
            }
            pop(operators);
        }

        //checking for single characters
        else if (token[1] == '\0' &&
                 (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
                  token[0] == '/' || token[0] == '%' || token[0] == '^'))
        {
            while (!isEmpty(operators) &&
                    peek(operators) != '(' &&
                    (precedence(peek(operators)) > precedence(token[0]) ||
                    (precedence(peek(operators)) == precedence(token[0]) && token[0] != '^')))
            {
                postfix[j++] = pop(operators);
                postfix[j++] = ' ';
            }
            push(operators, token[0]);
        }
        else //if the token is a number
        {
            strcpy(postfix + j, token);
            j += strlen(token);
            postfix[j++] = ' ';
        }
        //go next token
        token = strtok(NULL, " ");
    }

    while (!isEmpty(operators))
    {
        postfix[j++] = pop(operators);
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0';      //maybe postfix[j] = '\0';
    free(operators);
    return postfix;
}

float evaluation(char op, float n1, float n2)
{
    if (op == '^')
        return pow(n1,n2);
    
    if (op == '*')
        return n1*n2;
    
    if (op == '/')
        return n1/n2;
    
    if (op == '%')
        return fmod(n1,n2);
    
    if (op == '+')
        return n1+n2;
    
    if (op == '-')
        return n1-n2;
    
    return 0;
}

float evaluatePostfix(char *postfix)
{
    Stack *operation = initialize();
    char *token = strtok(postfix, " ");
    float value, n1, n2;

    while (token != NULL)
    {
        if (token[1] == '\0' &&
            (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
             token[0] == '/' || token[0] == '%' || token[0] == '^'))
        {
            n2 = pop(operation);
            n1 = pop(operation);
            value = evaluation(token[0],n1,n2);
            push(operation,value);
        }
        else
            push(operation, atof(token));
        token = strtok(NULL, " ");
    }
    value = pop(operation);
    return value;
}

int main()
{   
    while(1)
    {
    char str[100];
    char original[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    if (strlen(str) > 0 && str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    strcpy(original, str);

    char *postfix = infixTopostfix(str);
    printf("\nPostfix equivalent: %s\n", postfix);
    printf("Its value: %.3f\n", evaluatePostfix(postfix));
    printf("--------------------------------\n\n");
    }

    return 0;
}