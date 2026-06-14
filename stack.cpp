/* *************************************************
*  Name: Brandon Wascher
*  Assignment: Assignment 4
*  Purpose: Defines the Stack ADT operations declared
*           in stack.h: construction plus push, pop,
*           peek, and isEmpty over a fixed int array.
************************************************* */

#include "stack.h"

Stack::Stack() {
    /* *************************************************
    Constructs an empty stack by marking the top index as
    -1. The fixed array needs no initialization because
    only positions at or below top are ever read.

    @param : none
    @return : none
    @exception : none
    @note : top < 0 is the empty sentinel isEmpty tests
    * ************************************************* */

    top = -1;
}

bool Stack::push(int value) {
    /* *************************************************
    Inserts a value on top of the stack. Succeeds only
    while the stack is not full; on overflow it leaves
    the stack unchanged and reports failure.

    @param int value : the value to place on top
    @return bool : true if pushed, false on overflow
    @exception : none
    @note : full means top has reached the last index
    * ************************************************* */

    bool pushed = false;

    if (top < STACK_SIZE - 1) {
        top++;
        items[top] = value;
        pushed = true;
    }

    return pushed;
}

bool Stack::isEmpty() {
    /* *************************************************
    Reports whether the stack holds no values.

    @param : none
    @return bool : true when the stack is empty
    @exception : none
    @note : empty is represented by top < 0
    * ************************************************* */

    return top < 0;
}
