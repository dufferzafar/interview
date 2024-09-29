
# APT Portfolio

## Code Review
As a software developer, one of your many roles will be to review code written by your team members; your peers and one day, your juniors. Code review is important because it helps identify and fix potential bugs or issues, improves code quality, and promotes collaboration and knowledge sharing among team members. (Thank you ChatGPT).

What follows is a function, that given:

a list of timestamps, and
a matrix of timestamps

verifies that all the values in the i-th row of the matrix correspond to the same second of the same date as the i-th entry of the list.

The code also contains a small driver (main function) that acts as a unit test for the validation function defined before it.

However, the code is a first draft written by one of your team mates, and it could do with some improvements.

1) Can you help your team mate out by: 1) Making all the possible changes that will help improve this code.

2) Also describe in comments why a certain change is needed and how is it an improvement over the first draft.
Question 2

## Brainfuck Interpreter

Brianfuck (BF) is an esoteric programming language created in 1993 by Urban Müller. While it is Turing complete, it is not intended for practical use, but to challenge and amuse programmers. BF simply requires one to break commands into microscopic steps. Your task is to develop a BF interpreter from scratch.

Before we begin

Apart from correctness, your submission will also be evaluated by a person on code quality, clarity, and design, so feel free to write down you design and thought process in comments.

Some general advice:

• Write code that is correct and easy to read. To achieve this, write short code, name your variables and data structures intelligibly, and make use of modern C++ features. Write functions; avoid macros.

• Performance considerations are secondary, but we value craft.

• Although this programming language is small,it can be tricky.Make sure you take some time read all the information below and have fully understood the semantics and behaviour of BF.

• One last piece of advice: when your tests are passing, you're not done - read your code again, and improve its readability and structure, thinking about the person that has to understand, maintain and reuse your code in their own programs.

The BF language

Overview:

There are eight single-character commands > < + - . , [  ] which are explained below; 
a BF program is a sequence of commands, possibly mixed with other characters which must be ignored.

An array of at least 30000 cells, each 1 byte and initialized to zero, serves as main memory.

A data pointer begins at the first byte in the array.

An instruction pounter begins in the first command.

Command	Meaning

Increment the data pointer (to point to the next cell to the right)
<	decrement the data pointer (to point to the next cell to the left)
+	increment the value of the byte at the data pointer
-	decrement the value of the byte at the data pointer
.	output the byte at the data pointer
,	accept one byte of input,storing its value in the byte at the data pointer.
[	if the byte at the data pointer is zero,jump it forward to the command after the matching ] command
]	if the byte at the data pointer is not zero,jump it back to the command after the matching [ command.

Note:

[ and ] match as parentheses usually do: each [ matches exactly one ] and vice versa; 
the [ comes first, and there can be no unmatched [ or ] between the two.
An Important Note:
• The source code will be provided as input on stdin.
• The input read by the comma (,) command (see above) will be available in a file whose path will be the first command line argument 
(ie argv[1]).
• While unusual, this is due to limitations of the Hackerrank platform.

Examples:
As a first, simple example, the following subroutine will add the current cell's value to the next cell, 1 at a time, in a loop:

[->+<]

Each time the loop is executed:

1. the current cell is decremented;
2. the data pointer moves to the right;
3. that next cell is incremented;
4. and the data pointer moves left again.

This sequence is repeated until the starting cell is 0.

Addition: 3+5=8 A simple addition program is shown below:

+++ Increment value at cell C0 to 3.

This will hold the final value as well.

> +++++ Move data pointer right,

increment value at cell c1 to 5; 

Hello World!

The following program prints "Hello World!" and a newline to the screen. 
For readability, the code is spread across many lines and comments have been added; 
remember that BF ignores all characters except the eight commands so no special syntax for comments is needed, and the comments must not contain any command characters.

++++++++        Set cell #0 to 8
[
  >++++        Add 4 to Cell #1; this will always set Cell #1 to 4  
  [             as the cell will be cleared by the loop 
  >++           Add 2 to cell #2
  >+++          Add 3 to cell #3
  >+++          Add 3 to cell #4
  >+            Add 1 to cell #5
  <<<<-         Decrement the loop counter in cell #1
  ]             Loop till cell #1 is zero;number of iterations is 4
 >+           Add 1 to cell #2
 >+           Add 1 to cell #3
 >-           Subtract 1 from cell #4
 >>+          Add 1 to cell #6
[<]           Move back to the first zero cell you find;
this will be the cell #1 which was cleared by the previous loop

## Subjective questions

```cpp
auto l1 = (1.2/8.0);
auto x1 = (32/256.0);
auto r1 = (x1 * 1.2);
auto l2 = (1.2/7);
auto x2 = (21.0/147);
auto r2 = (x2 * 1.2);
auto l3 = (1.2/7);
auto x3 = (32/224.0);
auto r3 = (x3 * 1.2);

cout << "l1= " << type_name<decltype(l1)>() << " " << std::format("{}", l1) 
    << " x1= " << type_name<decltype(x1)>() << " " << std::format("{}", x1) 
    << " r1= " << type_name<decltype(r1)>() << " " << std::format("{}", r1) 
    << " eq ? " << (l1==r1) << std::endl;

cout << "l2= " << type_name<decltype(l2)>() << " " << std::format("{}", l2) 
    << " x2= " << type_name<decltype(x2)>() << " " << std::format("{}", x2) 
    << " r2= " << type_name<decltype(r2)>() << " " << std::format("{}", r2) 
    << " eq ? " << (l2==r2) << std::endl;

cout << "l3= " << type_name<decltype(l3)>() << " " << std::format("{}", l3)
    << " x3= " << type_name<decltype(x3)>() << " " << std::format("{}", x3) 
    << " r3= " << type_name<decltype(r3)>() << " " << std::format("{}", r3)
    << " eq ? " << (l3==r3) << std::endl;
```
