#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

        //check if the token is an operator, token[1] == '\0' means the token is a single character
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
    postfix[j - 1] = '\0';
    free(operators);
    return postfix;
}

int main()
{

}
