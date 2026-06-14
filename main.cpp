/* *************************************************
*  Name: Brandon Wascher
*  Assignment: Assignment 4
*  Purpose: Test driver for the Stack ADT. Drives the
*           stack through every state and operation to
*           show it is fully functional. All tests
*           scale off STACK_SIZE.
************************************************* */

#include "main.h"

int main() {
    /* *************************************************
    Exercises every Stack operation (push, pop, peek,
    isEmpty) in every state — empty/underflow, partial,
    and full/overflow. First with explicit pass/fail
    checks, then with random proportional testing that
    compares the stack against a reference model. Every
    test scales off STACK_SIZE, so changing that one
    constant adapts the whole driver.

    @param : none
    @return int : exit status (0 on normal completion)
    @exception : none
    @note : all testing lives in main per the spec
    * ************************************************* */

    const int SAMPLE = 42;

    Stack stack;
    int i = 0;
    int value = 0;
    int successCount = 0;
    int orderCount = 0;
    int expected = 0;
    bool empty = false;
    bool pushResult = false;

    std::cout << "=== EXPLICIT TESTING (stack size " << STACK_SIZE
              << ") ===" << std::endl;

    // --- Empty state (underflow) ---
    std::cout << std::endl << "-- Empty state --" << std::endl;

    empty = stack.isEmpty();
    std::cout << "isEmpty() on empty: " << (empty ? "PASS" : "FAIL") << " (got "
              << empty << ", expect 1)" << std::endl;

    try {
        value = stack.pop();
        std::cout << "pop() underflow: FAIL (no throw, got " << value << ")"
                  << std::endl;
    } catch (const std::underflow_error &error) {
        std::cout << "pop() underflow: PASS (threw: " << error.what() << ")"
                  << std::endl;
    }

    try {
        value = stack.peek();
        std::cout << "peek() underflow: FAIL (no throw, got " << value << ")"
                  << std::endl;
    } catch (const std::underflow_error &error) {
        std::cout << "peek() underflow: PASS (threw: " << error.what() << ")"
                  << std::endl;
    }

    // --- Partial state (neither empty nor full) ---
    std::cout << std::endl << "-- Partial state --" << std::endl;

    pushResult = stack.push(SAMPLE);
    std::cout << "push() on empty: " << (pushResult ? "PASS" : "FAIL")
              << " (got " << pushResult << ", expect 1)" << std::endl;

    empty = stack.isEmpty();
    std::cout << "isEmpty() after push: " << (!empty ? "PASS" : "FAIL")
              << " (got " << empty << ", expect 0)" << std::endl;

    value = stack.peek();
    std::cout << "peek() top: " << (value == SAMPLE ? "PASS" : "FAIL")
              << " (got " << value << ", expect " << SAMPLE << ")" << std::endl;

    value = stack.peek();
    std::cout << "peek() non-destructive: "
              << (value == SAMPLE ? "PASS" : "FAIL") << " (got " << value
              << " again, expect " << SAMPLE << ")" << std::endl;

    value = stack.pop();
    std::cout << "pop() returns top: " << (value == SAMPLE ? "PASS" : "FAIL")
              << " (got " << value << ", expect " << SAMPLE << ")" << std::endl;

    empty = stack.isEmpty();
    std::cout << "isEmpty() after pop: " << (empty ? "PASS" : "FAIL")
              << " (got " << empty << ", expect 1)" << std::endl;

    // --- Full state (overflow) ---
    std::cout << std::endl << "-- Full state --" << std::endl;

    successCount = 0;
    for (i = 0; i < STACK_SIZE; i++) {
        successCount += stack.push(i);
    }
    std::cout << "Fill to capacity: "
              << (successCount == STACK_SIZE ? "PASS" : "FAIL") << " ("
              << successCount << " of " << STACK_SIZE << " pushes ok)"
              << std::endl;

    empty = stack.isEmpty();
    std::cout << "isEmpty() when full: " << (!empty ? "PASS" : "FAIL")
              << " (got " << empty << ", expect 0)" << std::endl;

    value = stack.peek();
    std::cout << "peek() top when full: "
              << (value == STACK_SIZE - 1 ? "PASS" : "FAIL") << " (got "
              << value << ", expect " << STACK_SIZE - 1 << ")" << std::endl;

    pushResult = stack.push(SAMPLE);
    std::cout << "push() overflow rejected: " << (!pushResult ? "PASS" : "FAIL")
              << " (got " << pushResult << ", expect 0)" << std::endl;

    value = stack.peek();
    std::cout << "top intact after overflow: "
              << (value == STACK_SIZE - 1 ? "PASS" : "FAIL") << " (got "
              << value << ", expect " << STACK_SIZE - 1 << ")" << std::endl;

    // --- Transition full -> empty (LIFO drain) ---
    std::cout << std::endl << "-- Drain full -> empty --" << std::endl;

    orderCount = 0;
    expected = STACK_SIZE - 1;
    for (i = 0; i < STACK_SIZE; i++) {
        value = stack.pop();
        orderCount += (value == expected);
        expected--;
    }
    std::cout << "LIFO drain order: "
              << (orderCount == STACK_SIZE ? "PASS" : "FAIL") << " ("
              << orderCount << " of " << STACK_SIZE << " in order)"
              << std::endl;

    empty = stack.isEmpty();
    std::cout << "isEmpty() after drain: " << (empty ? "PASS" : "FAIL")
              << " (got " << empty << ", expect 1)" << std::endl;

    try {
        value = stack.pop();
        std::cout << "pop() underflow after drain: FAIL (no throw)"
                  << std::endl;
    } catch (const std::underflow_error &error) {
        std::cout << "pop() underflow after drain: PASS (threw)" << std::endl;
    }

    // --- Random proportional testing ---
    std::cout << std::endl << "-- Random testing --" << std::endl;

    const int OP_COUNT = 4;
    const int OPS_PER_SLOT = 100;
    const int RANDOM_OPS = STACK_SIZE * OPS_PER_SLOT;

    int model[STACK_SIZE] = {0};
    int counts[OP_COUNT] = {0};
    int modelCount = 0;
    int operation = 0;
    int randomValue = 0;
    int expectedValue = 0;
    int failures = 0;
    bool expectedOk = false;
    bool actualOk = false;
    bool threw = false;

    srand(static_cast<unsigned int>(time(nullptr)));

    // operation codes: 0 push, 1 pop, 2 peek, 3 isEmpty
    for (i = 0; i < RANDOM_OPS; i++) {
        operation = rand() % OP_COUNT;
        counts[operation]++;

        if (operation == 0) {
            randomValue = rand();
            actualOk = stack.push(randomValue);
            expectedOk = (modelCount < STACK_SIZE);
            if (expectedOk) {
                model[modelCount] = randomValue;
                modelCount++;
            }
            failures += (actualOk != expectedOk);
        } else if (operation == 1) {
            if (modelCount > 0) {
                expectedValue = model[modelCount - 1];
                value = stack.pop();
                modelCount--;
                failures += (value != expectedValue);
            } else {
                threw = false;
                try {
                    stack.pop();
                } catch (const std::underflow_error &) {
                    threw = true;
                }
                failures += (!threw);
            }
        } else if (operation == 2) {
            if (modelCount > 0) {
                expectedValue = model[modelCount - 1];
                value = stack.peek();
                failures += (value != expectedValue);
            } else {
                threw = false;
                try {
                    stack.peek();
                } catch (const std::underflow_error &) {
                    threw = true;
                }
                failures += (!threw);
            }
        } else {
            empty = stack.isEmpty();
            failures += (empty != (modelCount == 0));
        }
    }

    std::cout << "Random ops run: " << RANDOM_OPS << " (push " << counts[0]
              << ", pop " << counts[1] << ", peek " << counts[2] << ", isEmpty "
              << counts[3] << ")" << std::endl;
    std::cout << "Stack matched reference model: "
              << (failures == 0 ? "PASS" : "FAIL") << " (" << failures
              << " mismatches)" << std::endl;

    return 0;
}
