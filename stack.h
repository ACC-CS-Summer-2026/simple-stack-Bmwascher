/* *************************************************
*  Name: Brandon Wascher
*  Assignment: Assignment 4
*  Purpose: Declares the Stack ADT, a simple fixed-size
*           integer stack supporting push, pop, peek,
*           and isEmpty. STACK_SIZE is exposed so a
*           driver can size its tests dynamically.
************************************************* */

#ifndef STACK_H
#define STACK_H

// Standard
#include <stdexcept>

const int STACK_SIZE = 10;

class Stack {

  public:
    /**********************
    * Constructors/Destructor
    ***********************/
    Stack();

    /**********************
    * Getters/Accessors
    ***********************/
    int peek();
    bool isEmpty();

    /**********************
    * Setters/Mutators
    ***********************/
    bool push(int);
    int pop();

    /**********************
    * Printing
    ***********************/

  private:
    /**********************
    * Methods
    ***********************/

    /**********************
    * Attributes
    ***********************/
    int items[STACK_SIZE];
    int top;
};

#endif // STACK_H
