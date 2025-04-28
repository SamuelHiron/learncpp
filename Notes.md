# Chapter 0 : Introduction/Getting Started

# Chapter 0 Configs Done
GCC options
```
g++ -lfmt -ggdb -pedantic-errors -Wshadow -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++23
-ggdb for debug
-O0 by default (no optimization)
-pedantic-errors disable compiler extension (for portable)
-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion see errors
-Wshadow avoid shadowing (ex global variable name `x` and local variable named `x`)
-Werror treat warning as errors
-std=c++23 use c++23 standards
-O2 -DNDEBUG
```

VSCode options see chapter 0

# chapter 1: C++ Basics
A **statement** is a type of instruction that causes the program to perform some action. Statements are often terminated by a semicolon.

A **function** is a collection of statements that execute sequentially. Every C++ program must include a special function named main. When you run your program, execution starts at the top of the main function.

In programming, the name of a function (or object, type, template, etc…) is called its **identifier**.

The rules that govern how elements of the C++ language are constructed is called **syntax**. A **syntax error** occurs when you violate the grammatical rules of the language.

**Comments** allow the programmer to leave notes in the code. C++ supports two types of comments. Line comments start with a // and run to the end of the line. Block comments start with a /* and go to the paired */ symbol. Don’t nest block comments.

You can use comments to temporarily disable lines or sections of code. This is called commenting out your code.

**Data** is any information that can be moved, processed, or stored by a computer. A single piece of data is called a **value**. Common examples of values include letters (e.g. `a`), numbers (e.g. `5`), and text (e.g. `Hello`).

A **variable** is a named piece of memory that we can use to store values. In order to create a variable, we use a statement called a **definition statement**. When the program is run, each defined variable is **instantiated**, which means it is assigned a memory address.

A **data type** tells the compiler how to interpret a piece of data into a meaningful value. An **integer** is a number that can be written without a fractional component, such as 4, 27, 0, -2, or -12.

**Copy assignment** (via operator=) can be used to assign an already created variable a value.

The process of specifying an initial value for an object is called **initialization**, and the syntax used to initialize an object is called an **initializer**.

Simplified, C++ supports 6 basic types of initialization:

| Initialization Type       | Example        | Note                                      |
|---------------------------|----------------|-------------------------------------------|
| Default-initialization    | `int x;`       | In most cases, leaves variable with indeterminate value |
| Copy-initialization       | `int x = 5;`   |                                           |
| Direct-initialization     | `int x(5);`    |                                           |
| Direct-list-initialization| `int x{5};`    | Narrowing conversions disallowed          |
| Copy-list-initialization  | `int x = {5};` | Narrowing conversions disallowed          |
| Value-initialization      | `int x{};`     | Usually performs zero-initialization      |


Direct-initialization is sometimes called parenthesis-initialization, and list-initialization (including value-initialization) is sometimes called uniform -initialization or brace-initialization. You should **prefer brace-initialization** over the other initialization forms, and prefer initialization over assignment.

Although you can define multiple variables in a single statement, it’s better to define and initialize each variable on its own line, in a separate statement.

`std::cout` and `operator<<` allow us to output the result of an expression to the console.

`std::endl` outputs a newline character, forcing the console cursor to move to the next line, and flushes any pending output to the console. The `'\n'` character also outputs a newline character, but lets the system decide when to flush the output. 

`std::cin` and `operator>>` allow us to get a value from the keyboard.

A variable that has not been given a value is called an **uninitialized variable**. Trying to get the value of an uninitialized variable will result in **undefined behavior**, which can manifest in any number of ways.

C++ reserves a set of names called **keywords**. These have special meaning within the language and may not be used as variable names.

A **literal constant** is a fixed value inserted directly into the source code. Examples are 5 and “Hello world!”.

An **operation** is a process involving zero or more input values, called **operands**. The specific operation to be performed is denoted by the provided **operator**. The result of an operation produces an output value.

**Unary** operators take one operand. **Binary** operators take two operands, often called left and right. **Ternary** operators take three operands. **Nullary** operators take zero operands.

An **expression** is a sequence of literals, variables, operators, and function calls that are evaluated to produce a single output value. The calculation of this output value is called **evaluation**. The value produced is the **result** of the expression.

An **expression statement** is an expression that has been turned into a statement by placing a semicolon at the end of the expression.

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
The smallest unit of memory is a **binary digit**, also called a **bit**. The smallest unit amount of memory that can be addressed (accessed) directly is a **byte**. The modern standard is that a byte equals 8 bits.

A **data type** tells the compiler how to interpret the contents of memory in some meaningful way.

C++ comes with support for many fundamental data types, including floating point numbers, integers, boolean, chars, null pointers, and void.

**Void** is used to indicate no type. It is primarily used to indicate that a function does not return a value.

Different types take different amounts of memory, and the amount of memory used may vary by machine.

Related content
See [4.3 -- Object sizes and the sizeof operator](https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/) for a table indicating the minimum size for each fundamental type.

The **sizeof** operator can be used to return the size of a type in bytes.

**Signed integers** are used for holding positive and negative whole numbers, including 0. The set of values that a specific data type can hold is called its **range**. When using integers, keep an eye out for overflow and integer division problems.

**Unsigned integers** only hold positive numbers (and 0), and should generally be avoided unless you’re doing bit-level manipulation.

**Fixed-width integers** are integers with guaranteed sizes, but they may not exist on all architectures. The fast and least integers are the fastest and smallest integers that are at least some size. `std::int8_t` and `std::uint8_t` should generally be avoided, as they tend to behave like chars instead of integers.

**size_t** is an unsigned integral type that is used to represent the size or length of objects.

**Scientific notation** is a shorthand way of writing lengthy numbers. C++ supports scientific notation in conjunction with floating point numbers. The digits in the significand (the part before the e) are called the **significant digits**.

**Floating point** is a set of types designed to hold real numbers (including those with a fractional component). The **precision** of a number defines how many significant digits it can represent without information loss. A **rounding error** can occur when too many significant digits are stored in a floating point number that can’t hold that much precision. Rounding errors happen all the time, even with simple numbers such as 0.1. Because of this, you shouldn’t compare floating point numbers directly.

The **Boolean** type is used to store a `true` or `false` value.

**If statements** allow us to execute one or more lines of code if some condition is true. The conditional expression of an if-statement is interpreted as a boolean value. An **else statement** can be used to execute a statement when a prior if-statement condition evaluates to false.

**Char** is used to store values that are interpreted as an ASCII character. When using chars, be careful not to mix up ASCII code values and numbers. Printing a char as an integer value requires use of `static_cast.`

Angled brackets are typically used in C++ to represent something that needs a parameterizable type. This is used with `static_cast` to determine what data type the argument should be converted to (e.g. `static_cast<int>(x)` will return the value of `x` as an `int`).

Here are some tips:
- Don’t try to write the whole solution at once. Write one function, then test it to make sure it works as expected. Then proceed.
- Use your debugger to help figure out where things are going wrong.
- Go back and review the answers to quizzes from prior lessons in the chapter, as they’ll often contain similar concepts.


Note: The `^` symbol isn’t an exponent in C++. Implement the formula using multiplication instead of exponentiation.

# chapter 5: Constants and Strings
A **constant** is a value that may not be changed during the program’s execution. C++ supports two types of constants: named constants, and literals.

A **named constant** is a constant value that is associated with an identifier. A **Literal constant** is a constant value not associated with an identifier.

A variable whose value can not be changed is called a **constant variable**. The **const** keyword can be used to make a variable constant. Constant variables must be initialized. Avoid using `const` when passing by value or returning by value.

A **type qualifier** is a keyword that is applied to a type that modifies how that type behaves. As of C++23, C++ only supports `const` and `volatile` as type qualifiers.

A **constant expression** is an expression that can be evaluated at compile-time. An expression that is not a constant expression is sometimes called a **runtime expression**.

A **compile-time constant** is a constant whose value is known at compile-time. A **runtime constant** is a constant whose initialization value isn’t known until runtime.

A **constexpr** variable must be a compile-time constant, and initialized with a constant expression. Function parameters cannot be constexpr.

**Literals** are values inserted directly into the code. Literals have types, and literal suffixes can be used to change the type of a literal from the default type.

A **magic number** is a literal (usually a number) that either has an unclear meaning or may need to be changed later. Don’t use magic numbers in your code. Instead, use symbolic constants.

In everyday life, we count using **decimal** numbers, which have 10 digits. Computers use **binary**, which only has 2 digits. C++ also supports **octal** (base 8) and **hexadecimal** (base 16). These are all examples of **numeral systems**, which are collections of symbols (digits) used to represent numbers.

A **string** is a collection of sequential characters that is used to represent text (such as names, words, and sentences). String literals are always placed between double quotes. String literals in C++ are C-style strings, which have a strange type that is hard to work with.

**std::string** offers an easy and safe way to deal with text strings. std::string lives in the `<string>` header. `std::string` is expensive to initialize (or assign to) and copy.

**std::string_view** provides read-only access to an existing string (a C-style string literal, a std::string, or a char array) without making a copy. A `std::string_view` that is viewing a string that has been destroyed is sometimes called a **dangling** view. When a `std::string` is modified, all views into that `std::string` are **invalidated**, meaning those views are now invalid. Using an invalidated view (other than to revalidate it) will produce undefined behavior. std::string_view lives in the `<string_view>` header. 

Because C-style string literals exist for the entire program, it is okay to set a `std::string_view` to a C-style string literal, and even return such a `std::string_view` from a function.

A **substring** is a contiguous sequence of characters within an existing string.

get a complete line with no stop at whitespace
```cpp
std::getline(std::cin >> std::ws, name);
```

# chapter 6: Operators
Always use parentheses to disambiguate the precedence of operators if there is any question or opportunity for confusion.

The arithmetic operators all work like they do in normal mathematics. The remainder (%) operator returns the remainder from an integer division, same sign as the first operand.

The increment and decrement operators can be used to easily increment or decrement numbers. Avoid the postfix versions of these operators whenever possible. 
Prefer (`++i`)

Beware of side effects, particularly when it comes to the order that function parameters are evaluated. Do not use a variable that has a side effect applied more than once in a given statement. `f(x, ++x) undefined behavior diferent result on gcc and clang`

The comma operator can compress multiple statements into one. Writing the statements separately is usually better.

The **conditional operator** (`?:`) (also sometimes called the **arithmetic if** operator) is a ternary operator (an operator that takes 3 operands). Given a conditional operation of the form `c ? x : y`, if conditional `c` evaluates to `true` then `x` will be evaluated, otherwise `y` will be evaluated. The conditional operator typically needs to be parenthesized as follows:
- Parenthesize the entire conditional operator when used in a compound expression (an expression with other operators).
- For readability, parenthesize the condition if it contains any operators (other than the function call operator).

Relational operators can be used to compare floating point numbers. Beware using equality and inequality on floating point numbers.

Logical operators allow us to form compound conditional statements.


# chapter O: Bit Manipulation (optional chapter)



# chapter 7: Scope, Duration and Linkage
We covered a lot of material in this chapter. Good job, you’re doing great!

A **compound statement** or **block** is a group of zero or more statements that is treated by the compiler as if it were a single statement. Blocks begin with a `{` symbol, end with a `}` symbol, with the statements to be executed placed in between. Blocks can be used anywhere a single statement is allowed. No semicolon is needed at the end of a block. Blocks are often used in conjunction with `if statements` to execute multiple statements.

**User-defined namespaces** are namespaces that are defined by you for your own declarations. Namespaces provided by C++ (such as the `global namespace`) or by libraries (such as `namespace std`) are not considered user-defined namespaces.

You can access a declaration in a namespace via the **scope resolution operator (::)**. The scope resolution operator tells the compiler that the identifier specified by the right-hand operand should be looked for in the scope of the left-hand operand. If no left-hand operand is provided, the global namespace is assumed.

Local variables are variables defined within a function (including function parameters). Local variables have **block scope**, meaning they are in-scope from their point of definition to the end of the block they are defined within. Local variables have **automatic storage duration**, meaning they are created at the point of definition and destroyed at the end of the block they are defined in.

A name declared in a nested block can **shadow** or **name hide** an identically named variable in an outer block. This should be avoided.

Global variables are variables defined outside of a function. Global variables have **file scope**, which means they are visible from the point of declaration until the end of the file in which they are declared. Global variables have **static duration**, which means they are created when the program starts, and destroyed when it ends. Avoid dynamic initialization of static variables whenever possible.

An identifier’s **linkage** determines whether other declarations of that name refer to the same object or not. Local variables have no linkage. Identifiers with **internal linkage** can be seen and used within a single file, but are not accessible from other files. Identifiers with **external linkage** can be seen and used both from the file in which they are defined, and from other code files (via a forward declaration).

Avoid non-const global variables whenever possible. Const globals are generally seen as acceptable. Use **inline variables** for global constants if your compiler is C++17 capable.

Local variables can be given static duration via the **static** keyword.

A **qualified name** is a name that includes an associated scope (e.g. `std::string`). An **unqualified name** is a name that does not include a scoping qualifier (e.g. `string`).

**Using statements** (including **using declarations** and **using directives**) can be used to avoid having to qualify identifiers with an explicit namespace. A **using declaration** allows us to use an unqualified name (with no scope) as an alias for a qualified name. A **using directive** imports all of the identifiers from a namespace into the scope of the using directive. Both of these should generally be avoided.

**Inline expansion** is a process where a function call is replaced by the code from the called function’s definition. A function that is declared using the `inline` keyword is called an **inline function**.

Inline functions and variables have two primary requirements:

- The compiler needs to be able to see the full definition of an inline function or variable in each translation unit where the function is used (a forward declaration will not suffice on its own). The definition can occur after the point of use if a forward declaration is also provided.
- Every definition for an inline function or variable must be identical, otherwise undefined behavior will result.

In modern C++, the term inline has evolved to mean “multiple definitions are allowed”. Thus, an inline function is one that is allowed to be defined in multiple files. C++17 introduced **inline variables**, which are variables that are allowed to be defined in multiple files.

Inline functions and variables are particularly useful for **header-only libraries**, which are one or more header files that implement some capability (no .cpp files are included).

Finally, C++ supports **unnamed namespaces**, which implicitly treat all contents of the namespace as if it had internal linkage. C++ also supports **inline namespaces**, which provide some primitive versioning capabilities for namespaces.


# chapter 8: Control Flow


# chapter 9: Error Detection and Handling
### Chapter Review

The specific sequence of statements that the CPU executes in a program is called the program’s **execution path**. A **straight-line program** takes the same path every time it is run.

**Control flow statements** (also called **Flow control statements**) allow the programmer to change the normal path of execution. When a control flow statement causes the program to begin executing some non-sequential instruction sequence, this is called a **branch**.

A **conditional statement** is a statement that specifies whether some associated statement(s) should be executed or not.

**If statements** allow us to execute an associated statement based on whether some condition is `true`. **Else statements** execute if the associated condition is `false`. You can chain together multiple if and else statements.

A **dangling else** occurs when it is ambiguous which `if statement` an `else statement` is connected to. `Dangling else` statements are matched up with the last unmatched `if statement` in the same block. Thus, we trivially avoid `dangling else` statements by ensuring the body of an `if statement` is placed in a block.

A **null statement** is a statement that consists of just a semicolon. It does nothing, and is used when the language requires a statement to exist but the programmer does not need the statement to do anything.

**Switch statements** provide a cleaner and faster method for selecting between a number of matching items. Switch statements only work with integral types. **Case labels** are used to identify the values for the evaluated condition to match. The statements beneath a **default label** are executed if no matching case label can be found.

When execution flows from a statement underneath a label into statements underneath a subsequent label, this is called **fallthrough**. A `break statement` (or `return statement`) can be used to prevent fallthrough. The [[fallthrough]] attribute can be used to document intentional fallthrough.

**Goto statements** allow the program to jump to somewhere else in the code, either forward or backwards. These should generally be avoided, as they can create **spaghetti code**, which occurs when a program has a path of execution that resembles a bowl of spaghetti.

**While loops** allow the program to loop as long as a given condition evaluates to `true`. The condition is evaluated before the loop executes.

An **infinite loop** is a loop that has a condition that always evaluates to `true`. These loops will loop forever unless another control flow statement is used to stop them.

A **loop variable** (also called a **counter**) is an integer variable used to count how many times a loop has executed. Each execution of a loop is called an **iteration**.

**Do while loops** are similar to while loops, but the condition is evaluated after the loop executes instead of before.

**For loops** are the most used loop, and are ideal when you need to loop a specific number of times. An **off-by-one error** occurs when the loop iterates one too many or one too few times.

**Break statements** allow us to break out of a switch, while, do while, or for loop (also `range-based for loops`, which we haven’t covered yet). **Continue statements** allow us to move immediately to the next loop iteration.

**Halts** allow us to terminate our program. **Normal termination** means the program has exited in an expected way (and the `status code` will indicate whether it succeeded or not). **std::exit()** is automatically called at the end of `main`, or it can be called explicitly to terminate the program. It does some cleanup, but does not cleanup any local variables, or unwind the call stack.

**Abnormal termination** occurs when the program encountered some kind of unexpected error and had to be shut down. **std::abort** can be called for an abnormal termination.

An **algorithm** is a finite sequence of instructions that can be followed to solve some problem or produce some useful result. An algorithm is considered to be **stateful** if it retains some information across calls. Conversely, a **stateless** algorithm does not store any information (and must be given all the information it needs to work with when it is called). When applied to algorithms, the term **state** refers to the current values held in stateful variables.

An algorithm is considered **deterministic** if for a given input (the value provided for `start`) it will always produce the same output sequence.

A **pseudo-random number generator (PRNG)** is an algorithm that generates a sequence of numbers whose properties simulate a sequence of random numbers. When a PRNG is instantiated, an initial value (or set of values) called a **random seed** (or **seed** for short) can be provided to initialize the state of the PRNG. When a PRNG has been initialized with a seed, we say it has been **seeded**. The size of the seed value can be smaller than the size of the state of the PRNG. When this happens, we say the PRNG has been **underseeded**. The length of the sequence before a PRNG begins to repeat itself is known as the **period**.

A **random number distribution** converts the output of a PRNG into some other distribution of numbers. A **uniform distribution** is a random number distribution that produces outputs between two numbers X and Y (inclusive) with equal probability.

**Use that if you want to have random number in your code :**
https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/


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
