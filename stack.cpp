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
