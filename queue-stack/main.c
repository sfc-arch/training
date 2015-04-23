#include <assert.h>
#include "list.h"

#define TEST_SIZE 1024

int main(int argc, char const* argv[]) {
    List *queue;
    List *stack;
    int i, popped;
    bool result;

    for(i = 0; i < TEST_SIZE; ++i) {
        push(&queue, i);
        push(&stack, i);
    }

    for(i = 0; i < TEST_SIZE; ++i) {
        result = shift(&queue, &popped);
        assert(result);
        assert(popped == i);
        result = pop(&stack, &popped);
        assert(result);
        assert(popped == TEST_SIZE - 1 - i);
    }

    assert(!shift(&queue, &popped));
    assert(!pop(&stack, &popped));

    delete(queue);
    delete(stack);

    return EXIT_SUCCESS;
}
