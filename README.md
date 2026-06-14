# 🟦 Simple Int Stack — A Stack ADT

A small C++ program that implements a fixed-size integer **stack** as an
abstract data type (ADT) and exhaustively tests it from a driver.

## Overview

This assignment introduces the stack ADT and the discipline of building and
testing a loosely-coupled data structure. The `Stack` is a classic LIFO
(last-in, first-out) container backed by a fixed-size integer array and a single
`top` index. It exposes only four public operations — `push`, `pop`, `peek`, and
`isEmpty` — and hides its storage entirely behind that interface, so it can be
dropped into any other program unchanged.

Because `pop` and `peek` return an `int`, that return value cannot also encode an
error. Instead the stack signals **underflow** (an attempted read of an empty
stack) by *throwing* a `std::underflow_error` exception, and signals **overflow**
(an attempted `push` onto a full stack) by returning `false`. The driver
(`main.cpp`) is one long testbed that drives the stack through every state and
operation, first with explicit checks and then with thousands of random
operations validated against a reference model.

## 🚀 Features

- A self-contained `Stack` ADT (`stack.h` / `stack.cpp`) with exactly the four
  required public methods and only two private attributes (`int items[]` and
  `int top`).
- **Overflow protection:** `push` inserts only when room remains, otherwise
  returns `false` and leaves the stack unchanged.
- **Underflow protection via exceptions:** `pop` and `peek` throw
  `std::underflow_error` on an empty stack rather than returning a bogus `int`.
- **One tunable constant:** `STACK_SIZE` (default `10`) lives in `stack.h` and is
  visible to the driver, so the entire program — and all of its tests — resize
  off a single value.
- A thorough driver that performs both **explicit** state×operation testing and
  **random proportional** testing (`STACK_SIZE × 100` operations) checked against
  an independent model of the stack's contents.

## 🗂 Project Structure

```
.
├── main.cpp     # driver: one long main() — the stack testbed
├── main.h       # all of main's directives (<iostream>, <cstdlib>, <ctime>, stack.h)
├── stack.cpp    # defines the Stack ADT (constructor, push, pop, peek, isEmpty)
├── stack.h      # declares Stack (guard: STACK_H); STACK_SIZE constant
├── essay.md     # AI statement and essay
├── README.md    # this file
└── .gitignore   # tracks only source, headers, .gitignore, and markdown
```

## ⚙️ Requirements & Build

- A C++ compiler (`g++`) on Linux.
- No external libraries (only the standard library).

Build from the project directory:

```bash
g++ -I ./ *.cpp
```

This produces an executable named `a.out`. To name it yourself, add `-o`:

```bash
g++ -I ./ *.cpp -o stack
```

## 🧭 Usage

Run the executable (it takes no arguments):

```
$ g++ -I ./ *.cpp
$ ./a.out
=== EXPLICIT TESTING (stack size 10) ===

-- Empty state --
isEmpty() on empty: PASS (got 1, expect 1)
pop() underflow: PASS (threw: pop called on an empty stack)
peek() underflow: PASS (threw: peek called on an empty stack)

-- Partial state --
push() on empty: PASS (got 1, expect 1)
isEmpty() after push: PASS (got 0, expect 0)
peek() top: PASS (got 42, expect 42)
peek() non-destructive: PASS (got 42 again, expect 42)
pop() returns top: PASS (got 42, expect 42)
isEmpty() after pop: PASS (got 1, expect 1)

-- Full state --
Fill to capacity: PASS (10 of 10 pushes ok)
isEmpty() when full: PASS (got 0, expect 0)
peek() top when full: PASS (got 9, expect 9)
push() overflow rejected: PASS (got 0, expect 0)
top intact after overflow: PASS (got 9, expect 9)

-- Drain full -> empty --
LIFO drain order: PASS (10 of 10 in order)
isEmpty() after drain: PASS (got 1, expect 1)
pop() underflow after drain: PASS (threw)

-- Random testing --
Random ops run: 1000 (push 250, pop 253, peek 248, isEmpty 249)
Stack matched reference model: PASS (0 mismatches)
```

Every line reports a `PASS`/`FAIL` verdict alongside the actual and expected
values. The random section is seeded from the clock, so its per-operation counts
differ from run to run; the final mismatch count should always be `0`.

## 🔧 How It Works

- **`Stack` (`stack.h` / `stack.cpp`)** — stores values in a fixed `int
  items[STACK_SIZE]` array with `top` marking the highest used index (`-1` when
  empty). `push` advances `top` and stores a value only while `top < STACK_SIZE -
  1`; on a full stack it returns `false`. `pop` reads `items[top]`, decrements
  `top`, and returns the value, while `peek` returns it without removing it. Both
  `pop` and `peek` first call `isEmpty()` and throw `std::underflow_error` if the
  stack is empty, so an empty read can never return a meaningless number.
  `isEmpty()` centralizes the empty test as `top < 0`.
- **`main` (`main.cpp`)** — the driver, written as one long `main()` per the
  assignment. It runs in two stages:
  - **Explicit testing** walks the stack through each state — empty (underflow),
    partial, and full (overflow) — and checks every operation in each, including
    a full-to-empty LIFO drain.
  - **Random testing** performs `STACK_SIZE × 100` random operations (1000 at the
    default size) and validates each against a shadow `model[]` array that tracks
    what the stack *should* contain, counting any disagreement.
- **`main.h`** — holds every directive the driver needs so `main.cpp` includes
  only its own header. `stack.cpp` likewise includes only `stack.h`.

## 📄 Notes

- **Resizing:** change the single `STACK_SIZE` constant in `stack.h` and rebuild;
  the driver's bounds, expected values, and random-operation count all scale
  automatically (verified at sizes 1, 3, 10, 100, and 1000 with zero failures).
- **No magic numbers:** test multipliers and sample values are named constants;
  only `-1`, `0`, and `1` appear as literals, where they will not change.
- The program writes only to standard output and reads no input.
