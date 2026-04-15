#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

typedef struct
{
    Node *top;
}Stack;

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
    int value = n->data;
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
    Node *n = s->top;
    int value = n->data;
    return value;
}

void display(Stack *s)
{
    Stack *copy = malloc(sizeof(Stack));
    while (!isEmpty(s))
    {
        int x = pop(s);
        printf("%d\t", x);
        push(copy, x);
    }
    while (!isEmpty(copy))
        push(s, pop(copy));
}