#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    double items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, double value) {
    if (s->top < MAX_SIZE - 1) {
        s->items[++s->top] = value;
    } else {
        printf("Stack overflow!\n");
    }
}

double pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->items[s->top--];
    } else {
        printf("Stack underflow!\n");
        return 0;
    }
}

double evaluateRPN(char *expression) {
    Stack stack;
    initStack(&stack);
    char *token = strtok(expression, " ");

    while (token) {
        if (strcmp(token, "+") == 0) {
            double b = pop(&stack);
            double a = pop(&stack);
            push(&stack, a + b);
        } else if (strcmp(token, "-") == 0) {
            double b = pop(&stack);
            double a = pop(&stack);
            push(&stack, a - b);
        } else if (strcmp(token, "*") == 0) {
            double b = pop(&stack);
            double a = pop(&stack);
            push(&stack, a * b);
        } else if (strcmp(token, "/") == 0) {
            double b = pop(&stack);
            double a = pop(&stack);
            if (b != 0) {
                push(&stack, a / b);
            } else {
                printf("Error: Division by zero!\n");
            }
        } else if (strcmp(token, "sin") == 0) {
            double a = pop(&stack);
            push(&stack, sin(a));
        } else if (strcmp(token, "cos") == 0) {
            double a = pop(&stack);
            push(&stack, cos(a));
        } else if (strcmp(token, "tan") == 0) {
            double a = pop(&stack);
            push(&stack, tan(a));
        } else {
            push(&stack, atof(token));  // Convert string to double
        }
        token = strtok(NULL, " ");
    }

    return pop(&stack);
}

int main() {
    char expression[256];

    printf("Calculadora RPN Avançada\n");
    printf("Digite a expressão (use espaço para separar os tokens, ex: '3 4 +')\n");
    printf("Funções: sin, cos, tan\n");
    printf("Para sair, digite 'sair'\n");

    while (1) {
        printf("> ");
        fgets(expression, sizeof(expression), stdin);
        expression[strcspn(expression, "\n")] = 0;  // Remove newline

        if (strcmp(expression, "sair") == 0) {
            break;
        }

        double result = evaluateRPN(expression);
        printf("Resultado: %.2lf\n", result);
    }

    return 0;
}