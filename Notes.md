# Chapter 0 : Introduction/Getting Started

# Chapter 0 Configs Done
GCC options
```
g++ -lfmt -ggdb -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++23
-ggdb for debug
-O0 by default (no optimization)
-pedantic-errors disable compiler extension (for portable)
-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion see errors
-Werror treat warning as errors
-std=c++23 use c++23 standards
-O2 -DNDEBUG
```

VSCode options see chapter 0

# chapter 1: C++ Basics
When writing programs, add a few lines or a function, compile, resolve any errors, and make sure it works. Don’t wait until you’ve written an entire program before compiling it for the first time!

Focus on getting your code working. Once you are sure you are going to keep some bit of code, then you can spend time removing (or commenting out) temporary/debugging code, adding comments, handling error cases, formatting your code, ensuring best practices are followed, removing redundant logic, etc…

First-draft programs are often messy and imperfect. Most code requires cleanup and refinement to get to great!

# chapter 2: C++ Basics: Functions and Files
Many new programmers shortcut the design process (because it seems like a lot of work and/or it’s not as much fun as writing the code). However, for any non-trivial project, following these steps will save you a lot of time in the long run. A little planning up front saves a lot of debugging at the end.

Spending a little time up front thinking about how to structure your program will lead to better code and less time spent finding and fixing errors.

As you become more comfortable with these concepts and tips, they will start coming more naturally to you. Eventually you will get to the point where you can write entire functions (and short programs) with minimal pre-planning.

A **function** is a reusable sequence of statements designed to do a particular job. Functions you write yourself are called **user-defined** functions.

A **function call** is an expression that tells the CPU to execute a function. The function initiating the function call is the **caller**, and the function being called is the **callee** or **called** function. Do not forget to include parenthesis when making a function call.

The curly braces and statements in a function definition are called the **function body**.

A function that returns a value is called a **value-returning function**. The **return type** of a function indicates the type of value that the function will return. The **return statement** determines the specific **return value** that is returned to the caller. A return value is copied from the function back to the caller -- this process is called **return by value**. Failure to return a value from a non-void function will result in undefined behavior.

The return value from function main is called a **status code**, and it tells the operating system (and any other programs that called yours) whether your program executed successfully or not. By consensus a return value of 0 means success, and a non-zero return value means failure.

Practice **DRY** programming -- “**don’t repeat yourself**”. Make use of variables and functions to remove redundant code.

Functions with a return type of **void** do not return a value to the caller. A function that does not return a value is called a **void function** or **non-value returning function**. Void functions can’t be called where a value is required.

A return statement that is not the last statement in a function is called an **early return**. Such a statement causes the function to return to the caller immediately.

A **function parameter** is a variable used in a function where the value is provided by the caller of the function. An **argument** is the specific value passed from the caller to the function. When an argument is copied into the parameter, this is called **pass by value**.

Function parameters and variables defined inside the function body are called **local variables**. The time in which a variable exists is called its **lifetime**. Variables are created and destroyed at **runtime**, which is when the program is running. A variable’s **scope** determines where it can be seen and used. When a variable can be seen and used, we say it is **in scope**. When it can not be seen, it can not be used, and we say it is **out of scope**. Scope is a **compile-time** property, meaning it is enforced at compile time.

**Whitespace** refers to characters used for formatting purposes. In C++, this includes spaces, tabs, and newlines.

A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually defining the identifier. To write a forward declaration for a function, we use a **function prototype**, which includes the function’s return type, name, and parameters, but no function body, followed by a semicolon.

A **definition** actually implements (for functions and types) or instantiates (for variables) an identifier. A **declaration** is a statement that tells the compiler about the existence of the identifier. In C++, all definitions serve as declarations. **Pure declarations** are declarations that are not also definitions (such as function prototypes).

Most non-trivial programs contain multiple files.

When two identifiers are introduced into the same program in a way that the compiler or linker can’t tell them apart, the compiler or linker will error due to a **naming collision**. A **namespace** guarantees that all identifiers within the namespace are unique. The std namespace is one such namespace.

The **preprocessor** is a process that runs on the code before it is compiled. **Directives** are special instructions to the preprocessor. Directives start with a # symbol and end with a newline. A **macro** is a rule that defines how input text is converted to a replacement output text.

**Header files** are files designed to propagate declarations to code files. When using the `#include` directive, the `#include` directive is replaced by the contents of the included file. When including headers, use angled brackets when including system headers (e.g. those in the C++ standard library), and use double quotes when including user-defined headers (the ones you write). When including system headers, include the versions with no .h extension if they exist.

**Header guards** prevent the contents of a header from being included more than once into a given code file. They do not prevent the contents of a header from being included into multiple different code files.
`#pragma once` in header file



# chapter 3: Debugging C++ Programs
A **syntax error** is an error that occurs when you write a statement that is not valid according to the grammar of the C++ language. The compiler will catch these.

A **semantic error** occurs when a statement is syntactically valid, but does not do what the programmer intended.

The process of finding and removing errors from a program is called **debugging**.

We can use a five step process to approach debugging:

1. Find the root cause.
2. Understand the problem.
3. Determine a fix.
4. Repair the issue.
5. Retest.

Finding an error is usually the hardest part of debugging.

**Static analysis tools** are tools that analyze your code and look for semantic issues that may indicate problems with your code.

Being able to reliably reproduce an issue is the first and most important step in debugging.

There are a number of tactics we can use to help find issues:

- Commenting out code.
- Using output statements to validate your code flow.
- Printing values.

When using print statements to debug, use _std::cerr_ instead of _std::cout_. But even better, avoid debugging via print statements.

A **log file** is a file that records events that occur in a program. The process of writing information to a log file is called **logging**.

The process of restructuring your code without changing how it behaves is called **refactoring**. This is typically done to make your program more organized, modular, or performant.

**Unit testing** is a software testing method by which small units of source code are tested to determine whether they are correct.

**Defensive programming** is a technique whereby the programmer tries to anticipate all of the ways the software could be misused. These misuses can often be detected and mitigated.

All of the information tracked in a program (variable values, which functions have been called, the current point of execution) is part of the **program state**.

A **debugger** is a tool that allows the programmer to control how a program executes and examine the program state while the program is running. An **integrated debugger** is a debugger that integrates into the code editor.

**Stepping** is the name for a set of related debugging features that allow you to step through your code statement by statement.

**Step into** executes the next statement in the normal execution path of the program, and then pauses execution. If the statement contains a function call, _step into_ causes the program to jump to the top of the function being called.

**Step over** executes the next statement in the normal execution path of the program, and then pauses execution. If the statement contains a function call, _step over_ executes the function and returns control to you after the function has been executed.

**Step out** executes all remaining code in the function currently being executed and then returns control to you when the function has returned.

**Run to cursor** executes the program until execution reaches the statement selected by your mouse cursor.

**Continue** runs the program, until the program terminates or a breakpoint is hit. **Start** is the same as continue, just from the beginning of the program.

A **breakpoint** is a special marker that tells the debugger to stop execution of the program when the breakpoint is reached.

The **set next statement** command allows us to change the point of execution to some other statement (sometimes informally called jumping). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.

**Watching a variable** allows you to inspect the value of a variable while the program is executing in debug mode. The **watch window** allows you to examine the value of variables or expressions.

The **call stack** is a list of all the active functions that have been executed to get to the current point of execution. The **call stack window** is a debugger window that shows the call stack.

# chapter 4: Fundamental Data Types


# chapter 5: Constants and Strings


# chapter 6: Operators



# chapter O: Bit Manipulation (optional chapter)



# chapter 7: Scope, Duration and Linkage



# chapter 8: Control Flow


# chapter 9: Error Detection and Handling



# chapter 10: Type Conversion, Type Aliases, and Type Deduction


# chapter 11: Function Overloading and Function Templates


# chapter F: Constexpr functions


# chapter 12: Compound Types: References and Pointers


# chapter 13: Compound Types: Enums and Structs



# chapter 14: Introduction to Classes




# chapter 15: More on Classes




# chapter 16: Dynamic arrays: std::vector




# chapter 17: Fixed-size arrays: std::array and C-style arrays




# chapter 18: Iterators and Algorithms




# chapter 19: Dynamic Allocation


# chapter 20: Functions

# chapter 21: Operator Overloading

# chapter 22: Move Semantics and Smart Pointers

# chapter 23: Object Relationships

# chapter 24: Inheritance

# chapter 25: Virtual Functions

# chapter 26: Templates and Classes

# chapter 27: Exceptions


# chapter 28: Input and Output (I/O)


# Appendix A: Miscellaneous Subjects

# Appendix B: C++ Updates

# Appendix C: The End ?
