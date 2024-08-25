#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Stack {
    int top;
    unsigned capacity;
    char* array;
} Stack;

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

char pop(Stack* stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

char peek(Stack* stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top];
}

int isMatchingPair(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
        return 0;
}

int isBalanced(char exp[]) {
    int i = 0;

    Stack* stack = createStack(strlen(exp));
    if (!stack)
        return 0;

    while (exp[i]) {
        if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[') {
            push(stack, exp[i]);
        }

        if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
            if (isEmpty(stack))
                return 0;

            if (!isMatchingPair(pop(stack), exp[i]))
                return 0;
        }
        i++;
    }

    return isEmpty(stack);
}

void generateBalancedExpression(char* exp, int length) {
    Stack* stack = createStack(length);
    int index = 0;

    for (int i = 0; i < length / 2; i++) {
        char open = "({[}"[rand() % 3];
        char close = (open == '(') ? ')' : (open == '{') ? '}' : ']';

        push(stack, open);
        exp[index++] = open;
        exp[index++] = close;
    }
    exp[index] = '\0';

    free(stack->array);
    free(stack);
}

void generateUnbalancedExpression(char* exp, int length) {
    char* base = "({[]})";
    for (int i = 0; i < length; i++) {
        exp[i] = base[rand() % strlen(base)];
    }
    exp[length] = '\0';
}

int main() {
    srand(time(0)); // Inicializa o gerador de numeros aleatorios

    int length = 10;
    char balancedExp[length + 1];
    char unbalancedExp[length + 1];

    // Gera e testa expressoes balanceadas
    generateBalancedExpression(balancedExp, length);
    printf("Expressao gerada: %s\n", balancedExp);
    if (isBalanced(balancedExp))
        printf("A expressao esta balanceada.\n");
    else
        printf("A expressao balanceada nao esta balanceada.\n");

    // Gera e testa expressoes nao balanceadas
    generateUnbalancedExpression(unbalancedExp, length);
    printf("Expressao gerada: %s\n", unbalancedExp);
    if (isBalanced(unbalancedExp))
        printf("A expressao nao esta balanceada.\n");
    else
        printf("A expressao nao esta balanceada.\n");

    return 0;
}
