// Let's write a stack in C language

// WHY
//   Sometimes some interviewer asked me to write C program.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum { false, true } bool;

typedef struct {
    int *st;
    int capacity;

    // indx where
    // st[bottom] means the oldest data pushed
    // when empty, bottom will be -1
    int bottom;
} Stack;

// creator
Stack createStack(int capacity)
{
    Stack st;

    st.capacity = capacity;
    st.st = malloc(sizeof(int) * capacity);
    st.bottom = -1;

    return st;
}

Stack destroyStack(Stack *stack)
{
    free(stack->st);
}

bool is_full(const Stack *stack)
{
    return (stack->bottom == stack->capacity - 1);
}

bool is_empty(const Stack *stack)
{
    return (stack->bottom == - 1);
}

// returns false when stack is full
// otherwise returns true;
bool push(Stack *stack, int val)
{
    if (is_full(stack))
        return false;

    stack->bottom++;
    stack->st[stack->bottom] = val;

    return true;
}

// returns false when stack is empty
// otherwise returns true with val set to top
bool pop(Stack *stack, int *val)
{
    if (is_empty(stack))
        return false;

    *val = stack->st[stack->bottom];

    stack->bottom--;    // after this, -1 means empty

    return true;
}

bool assert_empty_full(Stack *stack, bool empty, bool full)
{
    bool res = false;
    res = is_empty(stack);
    assert(res == empty);
    res = is_full(stack);
    assert(res == full);
}

int main(void)
{
    Stack stack = createStack(3);

    bool res = false;

    for (int k = 0; k < 2; k++)
    {
        printf("start of pushing\n");
        assert_empty_full(&stack, true, false);

        res = push(&stack, 100);
        assert(res == true);

        res = is_empty(&stack);
        assert(res == false);
        res = is_full(&stack);
        assert(res == false);

        res = push(&stack, 200);
        assert(res == true);

        res = push(&stack, 300);
        assert(res == true);

        res = push(&stack, 400);
        assert(res == false);

        printf("end of pushing\n");

        assert_empty_full(&stack, false, true);

        int val = -1;

        printf("start of popping\n");

        res = pop(&stack, &val);
        assert(res == true);
        assert(val == 300);

        res = pop(&stack, &val);
        assert(res == true);
        assert(val == 200);

        res = pop(&stack, &val);
        assert(res == true);
        assert(val == 100);

        res = pop(&stack, &val);
        assert(res == false);

        printf("end of popping\n");

        assert_empty_full(&stack, true, false);
    }

    destroyStack(&stack);
}

