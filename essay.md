# AI Statement and Essay

## 1. AI usage on this assignment

I used Claude Code (an AI coding assistant) throughout this assignment. I used it
to draft the `Stack` ADT and the test driver to the assignment's specification,
to explain concepts I wanted to be sure of (how exceptions signal an error when
an `int` return cannot, and what keeps an ADT encapsulated), to scaffold the
required comment and formatting structure, and to run verification builds and
tests as I went. I made the design decisions myself — using exceptions rather
than pass-by-reference for `pop`/`peek`, a `const int` instead of a `#define` for
`STACK_SIZE`, and a hybrid "PASS/FAIL plus actual-vs-expected" testing output —
and the AI did the mechanical drafting around those decisions. I worked in small,
tested, committed steps so I understood each piece before moving on.

## 2. An AI error I caught and corrected

On this assignment I did not catch a real error in the AI's work. I think the
main reason is the nature of the problem: a simple integer stack is a small,
well-defined ADT with only four short operations over a fixed array, and the
requirements were spelled out explicitly, so there was very little room for the
AI to go wrong. Just as importantly, I did not take the code on faith — every
method was tested in isolation right after it was written, and then the whole
stack was checked by thousands of random operations compared against a separate
reference model. If the AI had made a logic error, that verification would have
exposed it as a failed check or a model mismatch, and none appeared. I am not
claiming AI cannot make mistakes; on this narrow, heavily-tested problem it
simply did not.

## 3. AI code that was correct but I improved

I did not have a case where I took correct AI code and substantially rewrote it.
The reason is that I made the important design decisions *before* the code was
written rather than after. I chose the error-handling strategy, the constant
style, the structure of the testing (explicit coverage of every state and
operation, then random testing that scales with the stack size and is validated
against a model), and the output format up front. Because those judgment calls
were already made, the first drafts matched what I wanted, so the improvement
happened in the design stage instead of as edits to finished code.

## 4. Something I learned by using AI

I learned what the `-Wall` and `-Wextra` compiler flags do, which I had not been
taught. While the AI was compile-checking the code with `g++ -Wall -Wextra`, I
asked what those flags were. They do not change what the program does; they raise
how much the compiler reports. By default `g++` only prints outright errors and
stays quiet about a lot of suspicious-but-legal code. `-Wall` turns on the
standard recommended set of warnings — things like an unused variable, a
non-`void` function that falls off the end without returning, or a comparison
between a signed and an unsigned integer — and `-Wextra` adds stricter checks on
top, such as unused function parameters. This matters in this course because the
grading build (`g++ -I ./ *.cpp`) uses no warning flags, and any compiler warning
is an automatic zero, so building with these flags locally surfaces sloppy code
before it ever reaches grading. I now build with them on as a habit.

## 5. Could I have done better without AI?

I could have written a correct integer stack without AI, because it is a small
ADT and I understand how it works — the array, the `top` index, the overflow and
underflow conditions, and why exceptions are needed when a return value cannot
carry an error. What AI changed was the speed and the thoroughness. It handled
the repetitive mechanical work (the comment blocks, the formatting, the long test
driver) far faster than I would have by hand, which let me spend my attention on
the design decisions and on testing. It also taught me the `-Wall`/`-Wextra`
practice I would not have picked up on my own here. So without AI I think I could
have reached working code, but more slowly and with less exhaustive testing; the
understanding behind the work would be the same either way, because I made the
decisions and verified the results myself.
