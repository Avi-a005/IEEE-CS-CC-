#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000

typedef struct {
    int stack[MAX_SIZE];
    int min_stack[MAX_SIZE];
    int max_stack[MAX_SIZE];
    int top;
    int min_top;
    int max_top;
} MinMaxStack;

void initialize(MinMaxStack* s) {
    s->top = -1;
    s->min_top = -1;
    s->max_top = -1;
}

void push(MinMaxStack* s, int x) {
    if (s->top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    s->stack[++(s->top)] = x;
    
    if (s->min_top == -1 || x <= s->min_stack[s->min_top]) {
        s->min_stack[++(s->min_top)] = x;
    }
    
    if (s->max_top == -1 || x >= s->max_stack[s->max_top]) {
        s->max_stack[++(s->max_top)] = x;
    }
}

int pop(MinMaxStack* s) {
    if (s->top < 0) {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    int popped = s->stack[s->top--];
    
    if (popped == s->min_stack[s->min_top]) {
        s->min_top--;
    }
    
    if (popped == s->max_stack[s->max_top]) {
        s->max_top--;
    }
    
    return popped;
}

int top(MinMaxStack* s) {
    if (s->top < 0) {
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    return s->stack[s->top];
}

int getMin(MinMaxStack* s) {
    if (s->min_top < 0) {
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    return s->min_stack[s->min_top];
}

int getMax(MinMaxStack* s) {
    if (s->max_top < 0) {
        printf("Stack is Empty\n");
        return INT_MIN;
    }
    return s->max_stack[s->max_top];
}

int main() {
    MinMaxStack s;
    initialize(&s);
    int choice, value;

    while (1) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Get Minimum\n");
        printf("5. Get Maximum\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                value = pop(&s);
                if (value != INT_MIN)
                    printf("Popped value: %d\n", value);
                break;
            case 3:
                value = top(&s);
                if (value != INT_MIN)
                    printf("Top value: %d\n", value);
                break;
            case 4:
                value = getMin(&s);
                if (value != INT_MIN)
                    printf("Minimum value: %d\n", value);
                break;
            case 5:
                value = getMax(&s);
                if (value != INT_MIN)
                    printf("Maximum value: %d\n", value);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
