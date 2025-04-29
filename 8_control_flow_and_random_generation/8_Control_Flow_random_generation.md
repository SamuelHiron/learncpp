# Control Flow 
## 8.1 [Control flow introduction](https://www.learncpp.com/cpp-tutorial/control-flow-introduction/)
When a program is run, the CPU begins execution at the top of `main()`, executes some number of statements (in sequential order by default), and then the program terminates at the end of `main()`. The specific sequence of statements that the CPU executes is called the program’s **execution path** (or **path**, for short).

Consider the following program:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;

    std::cout << "You entered " << x << '\n';

    return 0;
}
```
The execution path of this program includes lines 5, 7, 8, 10, and 12, in that order. This is an example of a **straight-line program**. Straight-line programs take the same path (execute the same statements in the same order) every time they are run.

However, often this is not what we desire. For example, if we ask the user for input, and the user enters something invalid, ideally we’d like to ask the user to make another choice. This is not possible in a straight-line program. In fact, the user may repeatedly enter invalid input, so the number of times we might need to ask them to make another selection isn’t knowable until runtime.

Fortunately, C++ provides a number of different **control flow statements** (also called **flow control statements**), which are statements that allow the programmer to change the normal path of execution through the program. You’ve already seen an example of this with if-statements (introduced in lesson [4.10 -- Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/)) that let us execute a statement only if a conditional expression is true.

When a control flow statement causes point of execution to change to a non-sequential statement, this is called **branching**.
### Categories of flow control statements

|Category|Meaning|Implemented in C++ by|
|---|---|---|
|Conditional statements|Causes a sequence of code to execute only if some condition is met.|if, else, switch|
|Jumps|Tells the CPU to start executing the statements at some other location.|goto, break, continue|
|Function calls|Jump to some other location and back.|function calls, return|
|Loops|Repeatedly execute some sequence of code zero or more times, until some condition is met.|while, do-while, for, ranged-for|
|Halts|Terminate the program.|std::exit(), std::abort()|
|Exceptions|A special kind of flow control structure designed for error handling.|try, throw, catch|

We’ll cover all of these categories in detail throughout this chapter, with the exception of exceptions (ha) which we’ll devote an entire future chapter to ([chapter 27](https://www.learncpp.com#Chapter27)).

Prior to this chapter, the number of things you could have a program do was fairly limited. Being able to control the flow of your program (particularly using loops) makes any number of interesting things possible! No longer will you be restricted to toy programs -- you will be able to write programs that have real utility.

This is where the real fun begins. So let’s get to it!

## 8.2 [If statements and blocks](https://www.learncpp.com/cpp-tutorial/if-statements-and-blocks/)
The first category of control flow statements we’ll talk about is conditional statements. A **conditional statement** is a statement that specifies whether some associated statement(s) should be executed or not.

C++ supports two basic kinds of conditionals: `if statements` (which we introduced in lesson [4.10 -- Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/), and will talk about further here) and `switch statements` (which we’ll cover in a couple of lessons).

### Quick if-statement recap

The most basic kind of conditional statement in C++ is the `if statement`. An `if statement` takes the form:

if (condition)
    true_statement;

or with an optional `else statement`:

if (condition)
    true_statement;
else
    false_statement;

If the `condition` evaluates to `true`, the `true_statement` executes. If the `condition` evaluates to `false` and the optional `else statement` exists, the `false_statement` executes.

Here is a simple program that uses an `if statement` with the optional `else statement`:

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x > 10)
        std::cout << x << " is greater than 10\n";
    else
        std::cout << x << " is not greater than 10\n";
```
### If or else with multiple conditional statements
```cpp
else
        std::cout << "You are not tall enough to ride.\n";
        std::cout << "Too bad!\n"; // focus on this line
```
This program doesn’t work as expected because the `true_statement` and `false_statement` can only be a single statement. The indentation is deceiving us here -- the above program executes as if it had been written as follows:
```cpp
	else
        std::cout << "You are not tall enough to ride.\n";
        
    std::cout << "Too bad!\n"; // focus on this line
```
This makes it clearer that “Too bad!” will always execute.

However, it’s common to want to execute multiple statements based on some condition. To do so, we can use a compound statement (block):
```cpp
    else
    { // note addition of block here
        std::cout << "You are not tall enough to ride.\n";
        std::cout << "Too bad!\n";
    }
```
### Implicit blocks

If the programmer does not declare a block in the statement portion of an `if statement` or `else statement`, the compiler will implicitly declare one. Thus:

```
if (condition)
    true_statement;
else
    false_statement;
```

is actually the equivalent of:

```
if (condition)
{
    true_statement;
}
else
{
    false_statement;
}
```
Most of the time, this doesn’t matter. However, new programmers sometimes try to define variables in the implicit block, like this:
```cpp
	if (true)
        int x{ 5 };
    else
        int x{ 6 };
    std::cout << x << '\n';
```
This won’t compile, with the compiler generating an error that identifier `x` isn’t defined. This is because the above example is the equivalent of:
```cpp
    if (true)
    {
        int x{ 5 };
    } // x destroyed here
    else
    {
        int x{ 6 };
    } // x destroyed here

    std::cout << x << '\n'; // x isn't in scope here
```
In this context, it’s clearer that variable `x` has block scope and is destroyed at the end of the block. By the time we get to the `std::cout` line, `x` doesn’t exist.
### To block or not to block single statements
There is debate within the programmer community as to whether single statements following an `if` or `else` should be explicitly enclosed in blocks or not.
There are many reasons given as rationale for using blocks.

1. Not using blocks makes it easier to inadvertently add statements that look like they are conditional but aren’t. Consider:
```cpp
if (age >= minDrinkingAge)
    purchaseBeer();
```
Now let’s say we’re in a hurry and modify this program to add another ability:
```cpp
if (age >= minDrinkingAge)
    purchaseBeer();
    gamble(); // will always execute
```
Oops, we’ve just allowed minors to gamble. Have fun in jail!

2. Not using blocks can make programs more difficult to debug. Let’s say we have the following snippet:
```cpp
if (age >= minDrinkingAge)
    addBeerToCart(); // conditionally executes

checkout(); // always executes
```
Let’s say we suspect something is wrong with the `addBeerToCart()` function, so we comment it out:
```cpp
if (age >= minDrinkingAge)
//    addBeerToCart();

checkout(); // conditionally executes now
```
Now we’ve made `checkout()` conditional, which we certainly didn’t intend.
Neither of the above occur if you always use blocks after an `if` or `else`.

3. `if constexpr` (a variant of the if-statement added in C++23) requires the use of blocks. Thus using blocks ensures consistency between `if` and `if constexpr`.

The best argument for not using blocks around single statements is that adding blocks makes you able to see less of your code at one time by spacing it out vertically, which makes your code less readable and can lead to other, more serious mistakes.

The community seems to be more in favor of always using blocks than not, though this recommendation certainly isn’t ubiquitous.
### Best practice
Consider putting single statements associated with an `if` or `else` in blocks (particularly while you are learning). More experienced C++ developers sometimes disregard this practice in favor of tighter vertical spacing.

A reasonable middle-ground alternative is to put single-lines on the same line as the `if` or `else`:
```cpp
if (age >= minDrinkingAge) purchaseBeer();
else std::cout << "No drinky for you\n".
```

This avoids both of the above downsides mentioned above at some minor cost to readability.

One fair criticism of the single-line method is that it produces code that is harder to debug:
- Because the conditional and associated statement will execute as part of the same step, it is more difficult to tell whether the statement actually executed or was skipped.
- Because the conditional and associated statement are on the same line, you can’t breakpoint just the associated statement (to stop execution only when the statement actually executes).

However, if either of the above points are hindering when debugging, you can insert a newline between the conditional and the statement (so they are on separate lines), do your debugging, then remove the newline afterward.
### If-else vs if-if
New programmers sometimes wonder when they should use if-else (if followed by one or more else-statements) or if-if (if followed by one or more additional if-statements).
- Use if-else when you only want to execute the code after the first `true` condition.
- Use if-if when you want to execute the code after all `true` conditions.

Here’s a program that demonstrates this:
```cpp
#include <iostream>

void ifelse(bool a, bool b, bool c)
{
    if (a)      // always evaluates
        std::cout << "a";
    else if (b) // only evaluates when prior if-statement condition is false
        std::cout << "b";
    else if (c) // only evaluates when prior if-statement condition is false
        std::cout << "c";
    std::cout << '\n';
}

void ifif(bool a, bool b, bool c)
{
    if (a) // always evaluates
        std::cout << "a";
    if (b) // always evaluates
        std::cout << "b";
    if (c) // always evaluates
        std::cout << "c";
    std::cout << '\n';
}

int main()
{
    ifelse(false, true, true);
    ifif(false, true, true);

    return 0;
}
```
In the call to `ifelse(false, true, true)`, `a` is `false`, so we do not execute the associated statement, and the associated `else` is executed instead. `b` is true, so we print `b`. Since this `if` condition was true, the associated `else` will not execute (and neither would any other `else` statements immediately following that one). Note that we only executed the code immediately after the first `true` condition (`b`).

In the call to `ifif(false, true, true)`, `a` is false, so we do not execute the associated statement, and move to the next `if`. `b` is true, so we print `b` and move to the next `if`. `c` is true, so we print `c`. Note that we executed the code after all `true` conditions (`b` and `c`).

Now look at this somewhat similar function:

```cpp
char getFirstMatchingChar(bool a, bool b, bool c)
{
    if (a) // always evaluates
        return 'a';
    else if (b) // only evaluates when prior if-statement condition is false
        return 'b';
    else if (c) // only evaluates when prior if-statement condition is false
        return 'c';

    return 0;
}
```

Since we’re using if-else, it’s clear we only want to execute the code after the first `true` condition. But when every associated statement returns a value, we can write this instead:

```cpp
char getFirstMatchingChar(bool a, bool b, bool c)
{
    if (a) // always evaluates
        return 'a'; // returns when if-statement is true
    if (b) // only evaluates when prior if-statement condition is false
        return 'b'; // returns when if-statement is true
    if (c) // only evaluates when prior if-statement condition is false
        return 'c'; // returns when if-statement is true

    return 0;
}
```

While this might superficially look like we want to execute the code after every `true` condition, as soon as we find the first `true` condition, the associated statement will cause the function to return. The remaining if-statements never have a chance to evaluate. Therefore, this behaves equivalently to the prior version. When every associated statement returns a value, many programmers prefer to omit the `else` keywords, as doing so avoids unnecessary clutter and the conditions line up better.

#### Key insight
When all associated statements return a value, you can always just use if-if since `else` provides no value.

We’ll continue our exploration of if-statements in the next lesson.
## 8.3 [Common if statement problems](https://www.learncpp.com/cpp-tutorial/common-if-statement-problems/)
This lesson is a continuation of lesson [8.2 -- If statements and blocks](https://www.learncpp.com/cpp-tutorial/if-statements-and-blocks/). In this lesson, we’ll take a look at some common problems that occur when using if-statements.
### Nested if-statements and the dangling else problem
It is possible to nest if-statements within other if-statements:
```cpp
 if (x >= 0) // outer if statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";
```
Now consider the following program:
```cpp
    if (x >= 0) // outer if-statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if-statement
            std::cout << x << " is between 0 and 20\n";

    // which if statement does this else belong to?
    else
        std::cout << x << " is negative\n";
```
The above program introduces a source of potential ambiguity called a **dangling else** problem. Is the else-statement in the above program matched up with the outer or inner if-statement?

The answer is that an else-statement is paired up with the last unmatched if-statement in the same block. Thus, in the program above, the else-statement is matched up with the inner if-statement, as if the program had been written like this:
```cpp
if (x >= 0) // outer if statement
    {
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";
        else // attached to inner if statement
            std::cout << x << " is negative\n";
    }
```
This causes the above program to produce incorrect output:
Enter a number: 21
21 is negative

To avoid such ambiguities when nesting if-statements, it is a good idea to explicitly enclose the inner if-statement within a block. This allows us to attach an else-statement to either the inner or the outer if-statement without ambiguity:
```cpp
    if (x >= 0)
    {
        if (x <= 20)
            std::cout << x << " is between 0 and 20\n";
        else // attached to inner if statement
            std::cout << x << " is greater than 20\n";
    }
    else // attached to outer if statement
        std::cout << x << " is negative\n";
```
The else-statement within the block attaches to the inner if-statement, and the else-statement outside of the block attaches to the outer if-statement.

### Flattening nested if-statements
Nested if-statements can often be flattened by either restructuring the logic or by using logical operators (covered in lesson [6.8 -- Logical operators](https://www.learncpp.com/cpp-tutorial/logical-operators/)). Code that is less nested is less error prone.

For example, the above example can be flattened as follows:
```cpp
if (x < 0)
        std::cout << x << " is negative\n";
    else if (x <= 20) // only executes if x >= 0
        std::cout << x << " is between 0 and 20\n";
    else // only executes if x > 20
        std::cout << x << " is greater than 20\n";
```
Here’s another example that uses logical operators to check multiple conditions within a single if-statement:
```cpp
if (x > 0 && y > 0) // && is logical and -- checks if both conditions are true
        std::cout << "Both numbers are positive\n";
    else if (x > 0 || y > 0) // || is logical or -- checks if either condition is true
        std::cout << "One of the numbers is positive\n";
    else
        std::cout << "Neither number is positive\n";
```

### Null statements

A **null statement** is an expression statement that consists of just a semicolon:
```cpp
if (x > 10)
    ; // this is a null statement
```
Null statements do nothing. They are typically used when the language requires a statement to exist but the programmer doesn’t need one. For readability, null statements are typically placed on their own lines. We’ll see examples of intentional null statements later in this chapter, when we cover loops.

Null statements are rarely intentionally used with if-statements. However, they can unintentionally cause problems for new (or careless) programmers. Consider the following snippet:

```cpp
if (nuclearCodesActivated()); // note the semicolon at the end of this line
    blowUpTheWorld();
```

In the above snippet, the programmer accidentally put a semicolon on the end of the if-statement (a common mistake since semicolons end many statements). This unassuming error compiles fine, and causes the snippet to execute as if it had been written like this:

```cpp
if (nuclearCodesActivated())
    ; // the semicolon acts as a null statement
blowUpTheWorld(); // and this line always gets executed!
```
#### Warning
Be careful not to “terminate” your if-statement with a semicolon, otherwise the statement(s) you wanted to execute conditionally will execute unconditionally instead (even if they are inside a block).
#### Tip
In Python, the `pass` keyword serves as a null statement. It is often used as a placeholder for code that will be implemented later. Because it is a word rather than a symbol, `pass` is less prone to inadvertent misuse and more searchable (allowing you to easily find those placeholders later).

```python
for x in [0, 1, 2]:
  pass               # To be completed in the future
```

In C++, we can mimic `pass` by using the preprocessor:
```cpp
#define PASS

void foo(int x, int y)
{
    if (x > y)
        PASS;
    else
        PASS;
}

int main()
{
    foo(4, 7);

    return 0;
}
```

For consistency with other C++ statements, our `PASS` requires a trailing semicolon. `PASS` gets stripped out by the preprocessor, and the trailing semicolon is interpreted by the compiler as a null statement.

### Operator== vs Operator= inside the conditional
Inside your conditional, you should be using `operator==` when testing for equality, not `operator=` (which is assignment). Consider the following program:
```cpp
	if (x = 0) // oops, we used an assignment here instead of a test for equality
        std::cout << "You entered 0\n";
    else
        std::cout << "You entered 1\n";
```
This program will compile and run, but will produce the wrong result in some cases:

Enter 0 or 1: 0
You entered 1

In fact, this program will always produce the result `You entered 1`. This happens because `x = 0` first assigns the value `0` to `x`, then evaluates to the value of `x`, which is now `0`, which is Boolean `false`. Since the conditional is always `false`, the else-statement always executes.

## 8.4 [Constexpr if statements](https://www.learncpp.com/cpp-tutorial/constexpr-if-statements/)
Normally, the conditional of an if-statement is evaluated at runtime.

However, consider the case where the conditional is a constant expression, such as in the following example:
```cpp
	constexpr double gravity{ 9.8 };

	// reminder: low-precision floating point literals of the same type can be tested for equality
	if (gravity == 9.8) // constant expression, always true
		std::cout << "Gravity is normal.\n";   // will always be executed
	else
		std::cout << "We are not on Earth.\n"; // will never be executed
```
Because `gravity` is constexpr and initialized with value `9.8`, the conditional `gravity == 9.8` must evaluate to `true`. As a result, the else-statement will never be executed.

Evaluating a constexpr conditional at runtime is wasteful (since the result will never vary). It is also wasteful to compile code into the executable that can never be executed.

### Constexpr if statements C++17

C++17 introduces the **constexpr if statement**, which requires the conditional to be a constant expression. The conditional of a constexpr-if-statement will be evaluated at compile-time.

If the constexpr conditional evaluates to `true`, the entire if-else will be replaced by the true-statement. If the constexpr conditional evaluates to `false`, the entire if-else will be replaced by the false-statement (if it exists) or nothing (if there is no else).

To use a constexpr-if-statement, we add the `constexpr` keyword after the `if`:
```cpp
	constexpr double gravity{ 9.8 };

	if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
	else
		std::cout << "We are not on Earth.\n";
```
When the above code is compiled, the compiler will evaluate the conditional at compile time, see that it is always `true`, and keep only the single statement `std::cout << "Gravity is normal.\n";`.

In other words, it will compile this:
```cpp
	constexpr double gravity{ 9.8 };

	std::cout << "Gravity is normal.\n";
```

#### Best practice
Favor constexpr if statements over non-constexpr if statements when the conditional is a constant expression.

### Modern compilers and if statements with constexpr conditionals C++17

For optimization purposes, modern compilers will generally treat non-constexpr if-statements that have constexpr conditionals as if they were constexpr-if-statements. However, they are not required to do so.

A compiler that encounters a non-constexpr if-statement with a constexpr conditional may issue a warning advising you to use `if constexpr` instead. This will ensure that compile-time evaluation will occur (even if optimizations are disabled).

## 8.5 [Switch statement basics](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/)
Although it is possible to chain many if-else-statements together, this is both difficult to read and inefficient. Consider the following program:
```cpp
void printDigitName(int x)
{
    if (x == 1)
        std::cout << "One";
    else if (x == 2)
        std::cout << "Two";
    else if (x == 3)
        std::cout << "Three";
    else
        std::cout << "Unknown";
```
Variable `x` in `printDigitName()` will be evaluated up to three times depending on the value passed in (which is inefficient), and the reader has to be sure that it is `x` being evaluated each time (not some other variable).
Because testing a variable or expression for equality against a set of different values is common, C++ provides an alternative conditional statement called a switch-statement that is specialized for this purpose. Here is the same program as above using a switch:
```cpp
void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
```
The idea behind a **switch statement** is simple: an expression (sometimes called the condition) is evaluated to produce a value.

Then one of the following occurs:
- If the expression’s value is equal to the value after any of the case-labels, the statements after the matching case-label are executed.
- If no matching value can be found and a default label exists, the statements after the default label are executed.
- If no matching value can be found and there is no default label, the switch is skipped.

Let’s examine each of these concepts in more detail.

### Starting a switch
We start a switch-statement by using the `switch` keyword, followed by parentheses with the conditional expression that we would like to evaluate inside. Often the expression is just a single variable, but it can be any valid expression.

The condition in a switch must evaluate to an integral type (see lesson [4.1 -- Introduction to fundamental data types](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/) if you need a reminder which fundamental types are considered integral types) or an enumerated type (covered in future lessons [13.2 -- Unscoped enumerations](https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/) and [13.6 -- Scoped enumerations (enum classes)](https://www.learncpp.com/cpp-tutorial/scoped-enumerations-enum-classes/)), or be convertible to one. Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.

#### For advanced readers
Why does the switch type only allow for integral (or enumerated) types? The answer is because switch statements are designed to be highly optimized. Historically, the most common way for compilers to implement switch statements is via [Jump tables](https://en.wikipedia.org/wiki/Branch_table) -- and jump tables only work with integral values.

For those of you already familiar with arrays, a jump table works much like an array, an integral value is used as the array index to “jump” directly to a result. This can be much more efficient than doing a bunch of sequential comparisons.

Of course, compilers don’t have to implement switches using jump tables, and sometimes they don’t. There is technically no reason that C++ couldn’t relax the restriction so that other types could be used as well, they just haven’t done so yet (as of C++23).

Following the conditional expression, we declare a block. Inside the block, we use labels to define all of the values we want to test for equality. There are two kinds of labels used with switch statements, which we’ll discuss subsequently.

### Case labels

The first kind of label is the **case label**, which is declared using the `case` keyword and followed by a constant expression. The constant expression must either match the type of the condition or must be convertible to that type.

If the value of the conditional expression equals the expression after a `case label`, execution begins at the first statement after that `case label` and then continues sequentially.

Here’s an example of the condition matching a `case label`:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 2
    {
    case 1:
        std::cout << "One";
        return;
    case 2: // which matches the case statement here
        std::cout << "Two"; // so execution starts here
        return; // and then we return to the caller
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2); // Two
    std::cout << '\n';

    return 0;
}
```
In the above program, `x` is evaluated to produce value `2`. Because there is a case label with value `2`, execution jumps to the statement underneath that matching case label. The program prints `Two`, and then the `return statement` is executed, which returns back to the caller.

There is no practical limit to the number of case labels you can have, but all case labels in a switch must be unique. That is, you can not do this:
```cpp
switch (x)
{
case 54:
case 54:  // error: already used value 54!
case '6': // error: '6' converts to integer value 54, which is already used
}
```

If the conditional expression does not match any of the case labels, no cases are executed. We’ll show an example of this shortly.
### The default label
The second kind of label is the **default label** (often called the **default case**), which is declared using the `default` keyword. If the conditional expression does not match any case label and a default label exists, execution begins at the first statement after the default label.

Here’s an example of the condition matching the default label:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default: // which does not match to any case labels
        std::cout << "Unknown"; // so execution starts here
        return; // and then we return to the caller
    }
}

int main()
{
    printDigitName(5); // Unknown
    std::cout << '\n';

    return 0;
}
```
The default label is optional, and there can only be one default label per switch statement. By convention, the default case is placed last in the switch block.

#### Best practice
Place the default case last in the switch block.

### No matching case label and no default case
If the value of the conditional expression does not match any of the case labels, and no default case has been provided, then no cases inside the switch are executed. Execution continues after the end of the switch block.
```cpp
#include <iostream>

void printDigitName(int x) // 5
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    // no matching case exists and there is no default case
    }

    // so execution continues here
    std::cout << "Hello";
}
```
In the above example, `x` evalutes to `5`, but there is no case label matching `5`, nor is there a default case. As a result, no cases execute. Execution continues after the switch block, printing `Hello`.

### Taking a break

In the above examples, we used return-statements to stop execution of the statements after our labels. However, this also exits the entire function.

A **break statement** (declared using the `break` keyword) tells the compiler that we are done executing statements within the switch, and that execution should continue with the statement after the end of the switch block. This allows us to exit a switch-statement without exiting the entire function.

Here’s a slightly modified example rewritten using `break` instead of `return`:
```cpp
#include <iostream>

void printDigitName(int x) // 3 => Three Ah-Ah-Ah
{
    switch (x) // x evaluates to 3
    {
    case 1:
        std::cout << "One";
        break;
    case 2:
        std::cout << "Two";
        break;
    case 3:
        std::cout << "Three"; // execution starts here
        break; // jump to the end of the switch block
    default:
        std::cout << "Unknown";
        break;
    }

    // execution continues here
    std::cout << " Ah-Ah-Ah!";
}
```

#### Best practice
Each set of statements underneath a label should end in a break-statement or a return-statement. This includes the statements underneath the last label in the switch.

So what happens if you don’t end a set of statements under a label with a `break` or `return`? We’ll explore that topic, and others, in the next lesson.

### Labels are conventionally not indented

In lesson [2.9 -- Naming collisions and an introduction to namespaces](https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/), we noted that code is typically indented one level to help identify that it’s part of a nested scope region. Since the curly braces of the switch defines a new scope region, we’d normally indent everything inside the curly braces one level.

A label, on the other hand, does not define a nested scope. Therefore, the code following a label is conventionally not indented.

However, if we indent both the labels and the subsequent statements to the same level, we end up with something like this:

```cpp
// Unreadable version
void printDigitName(int x)
{
    switch (x)
    {
        case 1:
        std::cout << "One";
        return;
        case 2:
        std::cout << "Two";
        return;
        case 3:
        std::cout << "Three";
        return;
        default:
        std::cout << "Unknown";
        return;
    }
}
```

This makes it really hard to determine where each case starts and ends.

We have two choices here. First, we can indent the statements following the labels anyway:

```cpp
// Acceptable but not preferred version
void printDigitName(int x)
{
    switch (x)
    {
        case 1: // indented from switch block
            std::cout << "One"; // indented from label (misleading)
            return;
        case 2:
            std::cout << "Two";
            return;
        case 3:
            std::cout << "Three";
            return;
        default:
            std::cout << "Unknown";
            return;
    }
}
```

While this is certainly more readable than the prior version, it implies that the statements beneath each label are in a nested scope, which is not the case (we’ll see examples of this in the next lesson, where a variable we define in one case can be used in another case). This formatting is considered acceptable (as it is readable), but it is not preferred.

Conventionally, labels are simply not indented:
```cpp
// Preferred version
void printDigitName(int x)
{
    switch (x)
    {
    case 1: // not indented from switch statement
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}
```
This makes it easy to identify each label. And because the statements are only indented one level from the switch block, it correctly implies that the statements are all part of the scope of the switch block.

In future lessons, we’ll encounter other types of labels -- these are also conventionally not indented for the same reason.
#### Best practice
Prefer not to indent labels. This allows them to stand out from the surrounding code without implying that they are defining a nested scope region.

### Switch vs if-else

Switch statements are best used when there is a single expression (with a non-boolean integral type or an enumerated type) we want to evaluate for equality against a small number of values. If the number of case labels gets too large, the switch can be hard to read.

Compared to the equivalent if-else statements, a switch-statement can be more readable, makes it clearer that it is the same expression being tested for equality in each case, and has the advantage of only evaluating the expression once (making it more efficient).

However, if-else is significantly more flexible. Some cases where if or if-else is typically better:
- Testing an expression for comparisons other than equality (e.g. `x > 5`)
- Testing multiple conditions (e.g. `x == 5 && y == 6`)
- Determining whether a value is within a range (e.g. `x >= 5 && x <= 10`)
- The expression has a type that switch doesn’t support (e.g. `d == 4.0`).
- The expression evaluates to a `bool`.

#### Best practice
Prefer a switch-statement over if-else statements when testing a single expression (with a non-boolean integral type or an enumerated type) for equality against a small set of values.

## 8.6 [Switch fallthrough and scoping](https://www.learncpp.com/cpp-tutorial/switch-fallthrough-and-scoping/)
This lesson continues our exploration of switch statements that we started in the prior lesson [8.5 -- Switch statement basics](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/). In the prior lesson, we mentioned that each set of statements underneath a label should end in a `break statement` or a `return statement`.

In this lesson, we’ll explore why, and talk about some switch scoping issues that sometimes trip up new programmers.

### Fallthrough
When a switch expression matches a case label or optional default label, execution begins at the first statement following the matching label. Execution will then continue sequentially until one of the following termination conditions happens:

- The end of the switch block is reached.
- Another control flow statement (typically a `break` or `return`) causes the switch block or function to exit.
- Something else interrupts the normal flow of the program (e.g. the OS shuts the program down, the universe implodes, etc…)

Note that the presence of another case label is _not_ one of these terminating conditions -- thus, without a `break` or `return`, execution will overflow into subsequent cases.

Here is a program that exhibits this behavior:

```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }
```

This program outputs the following:

2
3
4
5

This is probably not what we wanted! When execution flows from a statement underneath a label into statements underneath a subsequent label, this is called **fallthrough**.
#### Warning
Once the statements underneath a case or default label have started executing, they will overflow (fallthrough) into subsequent cases. break or return statements are typically used to prevent this.

Since fallthrough is rarely desired or intentional, many compilers and code analysis tools will flag fallthrough as a warning.
### The `[[fallthrough]] `attribute

Commenting intentional fallthrough is a common convention to tell other developers that fallthrough is intended. While this works for other developers, the compiler and code analysis tools don’t know how to interpret comments, so it won’t get rid of the warnings.

To help address this, C++17 adds a new attribute called `[[fallthrough]]`.

**Attributes** are a modern C++ feature that allows the programmer to provide the compiler with some additional data about the code. To specify an attribute, the attribute name is placed between double brackets. Attributes are not statements -- rather, they can be used almost anywhere where they are contextually relevant.

The `[[fallthrough]]` attribute modifies a `null statement` to indicate that fallthrough is intentional (and no warnings should be triggered):

```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }
```
This program prints:

2
3

And it should not generate any warnings about the fallthrough.
#### Best practice
Use the `[[fallthrough]]` attribute (along with a null statement) to indicate intentional fallthrough.
### Sequential case labels
You can use the logical OR operator to combine multiple tests into a single statement:
```cpp
bool isVowel(char c)
{
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
        c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
}
```

This suffers from the same challenges that we presented in the introduction to switch statements: `c` gets evaluated multiple times and the reader has to make sure it is `c` that is being evaluated each time.

You can do something similar using switch statements by placing multiple case labels in sequence:
```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```
Remember, execution begins at the first statement after a matching case label. Case labels aren’t statements (they’re labels), so they don’t count.

The first statement after _all_ of the case statements in the above program is `return true`, so if any case labels match, the function will return `true`.

Thus, we can “stack” case labels to make all of those case labels share the same set of statements afterward. This is not considered fallthrough behavior, so use of comments or `[[fallthrough]]` is not needed here.

### Labels do not define a new scope
With `if statements`, you can only have a single statement after the if-condition, and that statement is considered to be implicitly inside a block:

```cpp
if (x > 10)
    std::cout << x << " is greater than 10\n"; // this line implicitly considered to be inside a block
```

However, with switch statements, the statements after labels are all scoped to the switch block. No implicit blocks are created.

```cpp
switch (1)
{
case 1: // does not create an implicit block
    foo(); // this is part of the switch scope, not an implicit block to case 1
    break; // this is part of the switch scope, not an implicit block to case 1
default:
    std::cout << "default case\n";
    break;
}
```

In the above example, the 2 statements between the `case 1` and the default label are scoped as part of the switch block, not a block implicit to `case 1`.

### Variable declaration and initialization inside case statements

You can declare or define (but not initialize) variables inside the switch, both before and after the case labels:
```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```
Although variable `y` was defined in `case 1`, it was used in `case 2` as well. All statements inside the switch are considered to be part of the same scope. Thus, a variable declared or defined in one case can be used in a later case, even if the case in which the variable is defined is never executed (because the switch jumped over it)!

However, initialization of variables _does_ require the definition to execute. Initialization of variables is disallowed in any case that is not the last case (because the switch could jump over the initializer if there is a subsequent case defined, in which case the variable would be undefined, and accessing it would result in undefined behavior). Initialization is also disallowed before the first case, as those statements will never be executed, as there is no way for the switch to reach them.

If a case needs to define and/or initialize a new variable, the best practice is to do so inside an explicit block underneath the case statement:
```cpp
switch (1)
{
case 1:
{ // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
}

default:
    std::cout << "default case\n";
    break;
}
```

#### Best practice
If defining variables used in a case statement, do so in a block inside the case. 
## 8.7 [Goto statements](https://www.learncpp.com/cpp-tutorial/goto-statements/)
The next kind of control flow statement we’ll cover is the unconditional jump. An unconditional jump causes execution to jump to another spot in the code. The term “unconditional” means the jump always happens (unlike an if-statement or switch-statement, where the jump only happens conditionally based on the result of an expression).

In C++, unconditional jumps are implemented via a **goto statement**, and the spot to jump to is identified through use of a **statement label**. Just like with switch case labels, statement labels are conventionally not indented.

The following is an example of a goto statement and statement label:

```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
```
In this program, the user is asked to enter a non-negative number. However, if a negative number is entered, the program utilizes a goto statement to jump back to the `tryAgain` label. The user is then asked again to enter a new number. In this way, we can continually ask the user for input until he or she enters something valid.

### Statement labels have function scope
In the chapter on object scope ([chapter 7](https://www.learncpp.com#Chapter7)), we covered two kinds of scope: local (block) scope, and file (global) scope. Statement labels utilize a third kind of scope: **function scope**, which means the label is visible throughout the function even before its point of declaration. The goto statement and its corresponding `statement label` must appear in the same function.

While the above example shows a goto statement that jumps backwards (to a preceding point in the function), goto statements can also jump forward:
```cpp
#include <iostream>

void printCats(bool skip)
{
    if (skip)
        goto end; // jump forward; statement label 'end' is visible here due to it having function scope

    std::cout << "cats\n";
end:
    ; // statement labels must be associated with a statement
}

int main()
{
    printCats(true);  // jumps over the print statement and doesn't print anything
    printCats(false); // prints "cats"
```
Beyond the jumping forward, there are a couple of interesting things worth mentioning in the program above.

First, note that statement labels must be associated with a statement (hence their name: they label a statement). Because the end of the function had no statement, we had to use a null statement so we had a statement to label. Second, we were able to jump to the statement labeled by `end` even though we hadn’t declared `end` yet due to statement labels having function scope. No forward declaration of statement labels is necessary. Third, it’s worth explicitly mentioning that the above program is poor form -- it would have been better to use an if-statement to skip the print statement than a goto statement to jump over it.

There are two primary limitations to jumping: You can jump only within the bounds of a single function (you can’t jump out of one function and into another), and if you jump forward, you can’t jump forward over the initialization of any variable that is still in scope at the location being jumped to. For example:
```cpp
int main()
{
    goto skip;   // error: this jump is illegal because...
    int x { 5 }; // this initialized variable is still in scope at statement label 'skip'
skip:
    x += 3;      // what would this even evaluate to if x wasn't initialized?
```
Note that you can jump backwards over a variable initialization, and the variable will be re-initialized when the initialization is executed.

### Avoid using goto

Use of `goto` is shunned in C++ (and other modern high level languages as well). [Edsger W. Dijkstra](https://en.wikipedia.org/wiki/Edsger_Dijkstra), a noted computer scientist, laid out the case for avoiding goto in a famous but difficult to read paper called [Go To Statement Considered Harmful](http://www.cs.utexas.edu/users/EWD/ewd02xx/EWD215.PDF). The primary problem with goto is that it allows a programmer to jump around the code arbitrarily. This creates what is not-so-affectionately known as spaghetti code. **Spaghetti code** is code that has a path of execution that resembles a bowl of spaghetti (all tangled and twisted), making it extremely difficult to follow the logic of such code.

As Dijkstra says somewhat humorously, “the quality of programmers is a decreasing function of the density of go to statements in the programs they produce”.

Almost any code written using a goto statement can be more clearly written using other constructs in C++, such as if-statements and loops. One notable exception is when you need to exit a nested loop but not the entire function -- in such a case, a goto to just beyond the loops is probably the cleanest solution.

#### For advanced readers
Here’s a contrived example of using a goto to exit a nested loop without exiting the function:
```cpp
#include <iostream>

int main()
{
    for (int i = 1; i < 5; ++i)
    {
        for (int j = 1; j < 5; ++j)
        {
            std::cout << i << " * " << j << " is " << i*j << '\n';

            // If the product is divisible by 9, jump to the "end" label
            if (i*j % 9 == 0)
            {
                std::cout << "Found product divisible by 9.  Ending early.\n";
                goto end;
            }
        }

        std::cout << "Incrementing the first factor.\n";
    }

end:
    std::cout << "And we're done." << '\n';
```
#### Best practice
Avoid goto statements (unless the alternatives are significantly worse for code readability).

## 8.8 [Introduction to loops and while statements](https://www.learncpp.com/cpp-tutorial/introduction-to-loops-and-while-statements/)

### While statements

The **while statement** (also called a **while loop**) is the simplest of the three loop types that C++ provides, and it has a definition very similar to that of an if-statement:

while (condition)
    statement;

A `while statement` is declared using the **while** keyword. When a while-statement is executed, the expression _condition_ is evaluated. If the condition evaluates to `true`, the associated _statement_ executes.

However, unlike an if-statement, once the statement has finished executing, control returns to the top of the while-statement and the process is repeated. This means a while-statement will keep looping as long as the condition continues to evaluate to `true`.

Note that if the condition initially evaluates to `false`, the associated statement will not execute at all.

### Infinite loops

On the other hand, if the expression always evaluates to `true`, the while loop will execute forever. This is called an **infinite loop**.
### Intentional infinite loops

We can declare an intentional infinite loop like this:
```cpp
while (true)
{
  // this loop will execute forever
}
```
The only way to exit an infinite loop is through a return-statement, a break-statement, an exit-statement, a goto-statement, an exception being thrown, or the user killing the program.
It is common to see this kind of loop in web server applications that run continuously and service web requests.

#### Best practice
Favor `while(true)` for intentional infinite loops.

### Unintentional infinite loops
Unintentionally placing a semicolon after the condition of a while-loop is a good way to hang your program.
```cpp
while (count <= 10); // note the semicolon here
    {
```
The program executes as if we had written this:
```cpp
while (count <= 10) // this is an infinite loop
        ;               // whose body is a null statement

    { // this is no longer associated with the while loop
```
Because the loop condition evaluates to `true`, the loop body executes. But the loop body is a null-statement, which does nothing. Then the loop condition evaluates again. Since `count` is never incremented, the condition can never evaluate to `false`, so the loop will run forever doing nothing. Our program will appear as if it is hung.

Unlike if-statements, where a semicolon after the condition is always a mistake, you will occasionally see while-statements that do this intentionally. For example, if we want to continuously call a function until it returns `false`, we can write that concisely as follows:

```cpp
while (keepRunning()); // will keep calling this function until it returns false
```

Of course, if the function never returns `false`, you’ll get an infinite loop.
#### Warning
Be careful about placing a semicolon after the condition of a while-statement, as it will result in an infinite loop unless the condition some way to evaluate to `false`.

### Loop variables and naming

A **loop variable** is a variable that is used to control how many times a loop executes. For example, given `while (count <= 10)`, `count` is a loop variable. While most loop variables have type `int`, you will occasionally see other types (e.g. `char`).

Loop variables are often given simple names, with `i`, `j`, and `k` being the most common.

#### As an aside…
The use of `i`, `j`, and `k` for loop variable names arose because these are the first three shortest names for integral variables in the Fortran programming language. The convention has persisted since.

However, if you want to know where in your program a loop variable is used, and you use the search function on `i`, `j`, or `k`, the search function will return half of the lines in your program! For this reason, some developers prefer loop variable names like `iii`, `jjj`, or `kkk`. Because these names are more unique, this makes searching for loop variables much easier, and helps them stand out as loop variables. An even better idea is to use “real” variable names, such as `count`, `index`, or a name that gives more detail about what you’re counting (e.g. `userCount`).

The most common type of loop variable is called a **counter**, which is a loop variable that counts how many times a loop has executed. In the examples above, the variable `count` is a counter.
### Integral loop variables should be signed

Integral loop variables should almost always be signed, as unsigned integers can lead to unexpected issues. Consider the following code:
```cpp
unsigned int count{ 10 }; // note: unsigned

    // count from 10 down to 0
    while (count >= 0)
    {
        --count;
    }
```
Take a look at the above example and see if you can spot the error. It’s not very obvious if you haven’t seen this before.

It turns out, this program is an infinite loop. but then loop variable `count` overflows, and starts counting down from `4294967295` (assuming 32-bit integers). Why? Because the loop condition `count >= 0` will never be false! When count is `0`, `0 >= 0` is true. Then `--count` is executed, and count wraps around back to `4294967295`. And since `4294967295 >= 0` is `true`, the program continues. Because `count` is unsigned, it can never be negative, and because it can never be negative, the loop won’t terminate.

#### Best practice
Integral loop variables should generally be a signed integral type.

### Doing something every N iterations
Each time a loop executes, it is called an **iteration**.
Often, we want to do something every 2nd, 3rd, or 4th iteration, such as print a newline. This can easily be done by using the remainder operator (%) on our counter.
### Nested loops
It is also possible to nest loops inside of other loops.
```cpp
void printUpto(int outer)
{
    // loop between 1 and outer
    // note: inner will be created and destroyed at the end of the block
    int inner{ 1 };
    while (inner <= outer)
    {
        std::cout << inner << ' ';
        ++inner;
    }
} // inner destroyed here

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // This function prints numbers between 1 and outer
        printUpto(outer);

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }
```
Now let’s move to the more confusing example:
```cpp
// outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // inner loops between 1 and outer
        // note: inner will be created and destroyed at the end of the block
        int inner{ 1 };
        while (inner <= outer)
        {
            std::cout << inner << ' ';
            ++inner;
        }

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    } // inner destroyed here
```
This program has the exact same output:
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5

Because we have a while-loop nested directly within another while-loop, this looks a bit more confusing. However, all we’ve done is put the code that used to be inside the `printUpto()` function directly inside the outer loop body.

## 8.9 [Do while statements](https://www.learncpp.com/cpp-tutorial/do-while-statements/)
Consider the case where we want to show the user a menu and ask them to make a selection -- and if the user chooses an invalid selection, to ask them again. Clearly the menu and selection should go inside a loop of some kind (so we can keep asking the user until they enter valid input), but what kind of loop should we choose?

Since a while loop evaluates the condition up front, it’s an awkward choice. We could solve the issue like this:
```cpp
// selection must be declared outside while-loop, so we can use it later
    int selection {}; // value initialized to 0

    while (selection < 1 || selection > 4)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';
```
But this only works because our initial value of `0` for `selection` isn’t in the set of valid values (`1, 2, 3 or 4`). What if `0` was a valid choice? We’d have to pick a different initializer to represent “invalid” -- and now we’re introducing magic numbers ([5.2 -- Literals](https://www.learncpp.com/cpp-tutorial/literals/)) into our code.

We could instead add a new variable to track validity, like so:
```cpp
int selection {};
    bool invalid { true }; // new variable just to gate the loop

    while (invalid)
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";

        std::cin >> selection;
        invalid = (selection < 1 || selection > 4);
    }

    // do something with selection here
    // such as a switch statement
```
While this avoids the magic number, it introduces a new variable just to ensure the loop runs once, and that adds complexity and the possibility of additional errors.
### Do while statements

To help solve problems like the above, C++ offers the do-while statement:
```cpp
do
    statement; // can be a single statement or a compound statement
while (condition);
```
A **do while statement** is a looping construct that works just like a while loop, except the statement always executes at least once. After the statement has been executed, the do-while loop checks the condition. If the condition evaluates to `true`, the path of execution jumps back to the top of the do-while loop and executes it again.

Here is our example above using a do-while loop instead of a while loop:
```cpp
    // selection must be declared outside of the do-while-loop, so we can use it later
    int selection {};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection < 1 || selection > 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';
```

In this way, we’ve avoided both magic numbers and additional variables.

One thing worth discussing in the above example is that the `selection` variable must be declared outside of the do block. If the `selection` variable were to be declared inside the do block, it would be destroyed when the do block terminates, which happens before the conditional is evaluated. But we need the variable in the while conditional -- consequently, the `selection` variable must be declared outside the do block (even if it wasn’t used later in the body of the function).

In practice, do-while loops aren’t commonly used. Having the condition at the bottom of the loop obscures the loop condition, which can lead to errors. Many developers recommend avoiding do-while loops altogether as a result. We’ll take a softer stance and advocate for preferring while loops over do-while when given an equal choice.
#### Best practice
Favor while loops over do-while when given an equal choice.

## 8.10 [For statements](https://www.learncpp.com/cpp-tutorial/for-statements/)
By far, the most utilized loop statement in C++ is the for-statement. The **for statement** (also called a **for loop**) is preferred when we have an obvious loop variable because it lets us easily and concisely define, initialize, test, and change the value of loop variables.

As of C++11, there are two different kinds of for-loops. We’ll cover the classic for-statement in this lesson, and the newer range-based for-statement in a future lesson ([16.8 -- Range-based for loops (for-each)](https://www.learncpp.com/cpp-tutorial/range-based-for-loops-for-each/)) once we’ve covered some other prerequisite topics.

The for-statement looks pretty simple in abstract:

```cpp
for (init-statement; condition; end-expression)
   statement;
```

The easiest way to initially understand how a for-statement works is to convert it into an equivalent while-statement:
```cpp
{ // note the block here
    init-statement; // used to define variables used in the loop
    while (condition)
    {
        statement; 
        end-expression; // used to modify the loop variable prior to reassessment of the condition
    }
} // variables defined inside the loop go out of scope here
```
### Evaluation of for-statements

A for-statement is evaluated in 3 parts:

First, the init-statement is executed. This only happens once when the loop is initiated. The init-statement is typically used for variable definition and initialization. These variables have “loop scope”, which really just is a form of block scope where these variables exist from the point of definition through the end of the loop statement. In our while-loop equivalent, you can see that the init-statement is inside a block that contains the loop, so the variables defined in the init-statement go out of scope when the block containing the loop ends.

Second, with each loop iteration, the condition is evaluated. If this evaluates to `true`, the statement is executed. If this evaluates to `false`, the loop terminates and execution continues with the next statement beyond the loop.

Finally, after the statement is executed, the end-expression is evaluated. Typically, this expression is used to increment or decrement the loop variables defined in the init-statement. After the end-expression has been evaluated, execution returns to the second step (and the condition is evaluated again).


#### Key insight

The order of execution for the different parts of a for-statement is as follows:
- Init-statement
- Condition (if this is false, the loop terminates here).
- Loop body
- End-expression (then jumps back to condition)

Note that the end-expression executes _after_ the loop statement, and then the condition is re-evaluated.
Let’s take a look at a sample for-loop and discuss how it works:

```cpp
#include <iostream>

int main()
{
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

First, we declare a loop variable named `i`, and initialize it with the value `1`.

Second, `i <= 10` is evaluated, and since `i` is `1`, this evaluates to `true`. Consequently, the statement executes, which prints `1` and a space.

Finally, `++i` is evaluated, which increments `i` to `2`. Then the loop goes back to the second step.

Now, `i<= 10` is evaluated again. Since `i` has value `2`, this evaluates to `true`, so the loop iterates again. The statement prints `2` and a space, and `i` is incremented to `3`. The loop continues to iterate until eventually `i` is incremented to `11`, at which point `i <= 10` evaluates to`false`, and the loop exits.

Consequently, this program prints the result:

1 2 3 4 5 6 7 8 9 10

For the sake of example, let’s convert the above for-loop into an equivalent while-loop:
```cpp
#include <iostream>

int main()
{
    { // the block here ensures block scope for i
        int i{ 1 }; // our init-statement
        while (i <= 10) // our condition
        {
            std::cout << i << ' '; // our statement
            ++i; // our end-expression
        }
    }

    std::cout << '\n';
}
```

That doesn’t look so bad, does it? Note that the outer braces are necessary here, because `i` goes out of scope when the loop ends.

For-loops can be hard for new programmers to read -- however, experienced programmers love them because they are a very compact way to do loops with a counter, with all of the necessary information about the loop variables, loop conditions, and loop variable modifiers presented up front. This helps reduce errors.

### More for-loop examples

Here’s an example of a function that uses a for-loop to calculate integer exponents:

```cpp
#include <cstdint> // for fixed-width integers

// returns the value base ^ exponent -- watch out for overflow!
std::int64_t pow(int base, int exponent)
{
    std::int64_t total{ 1 };

    for (int i{ 0 }; i < exponent; ++i)
        total *= base;

    return total;
}
```
This function returns the value base^exponent (base to the exponent power).

This is a straightforward incrementing for-loop, with `i` looping from `0` up to (but excluding) `exponent`.

Although most for-loops increment the loop variable by 1, we can decrement it as well:
```cpp
 for (int i{ 9 }; i >= 0; --i)
        std::cout << i << ' ';
```
Alternately, we can change the value of our loop variable by more than 1 with each iteration:
```cpp
    for (int i{ 0 }; i <= 10; i += 2) // increment by 2 each iteration
        std::cout << i << ' ';
```


### The perils of `operator!=` in for-loop conditions

When writing a loop condition involving a value, we can often write the condition in many different ways. The following two loops execute identically:
```cpp
for (int i { 0 }; i < 10; ++i) // uses <
         std::cout << i;

    for (int i { 0 }; i != 10; ++i) // uses !=
         std::cout << i;
```

So which should we prefer? The former is the better choice, as it will terminate even if `i` jumps over the value `10`, whereas the latter will not. The following example demonstrates this:
```cpp
 for (int i { 0 }; i < 10; ++i) // uses <, still terminates
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

    for (int i { 0 }; i != 10; ++i) // uses !=, infinite loop
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }
```
#### Best practice
Avoid `operator!=` when doing numeric comparisons in the for-loop condition. Prefer `operator<` or `operator<=` where possible

#### Off-by-one errors
One of the biggest problems that new programmers have with for-loops (and other loops that utilize counters) are off-by-one errors. **Off-by-one errors** occur when the loop iterates one too many or one too few times to produce the desired result.
```cpp
// oops, we used operator< instead of operator<=
    for (int i{ 1 }; i < 5; ++i)
    {
        std::cout << i << ' ';
    }
```
This program is supposed to print `1 2 3 4 5`, but it only prints `1 2 3 4` because we used the wrong relational operator.

Although the most common cause for these errors is using the wrong relational operator, they can sometimes occur by using pre-increment or pre-decrement instead of post-increment or post-decrement, or vice-versa.
### Omitted expressions
It is possible to write _for loops_ that omit any or all of the statements or expressions. For example, in the following example, we’ll omit the init-statement and end-expression, leaving only the condition
```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }
```

Rather than having the _for loop_ do the initialization and incrementing, we’ve done it manually. We have done so purely for academic purposes in this example, but there are cases where not defining a loop variable (because you already have one) or not incrementing it in the end-expression (because you’re incrementing it some other way) is desired.

Although you do not see it very often, it is worth noting that the following example produces an infinite loop:
```cpp
for (;;)
    statement;
```
The above example is equivalent to:
```cpp
while (true)
    statement;
```

This might be a little unexpected, as you’d probably expect an omitted condition-expression to be treated as `false`. However, the C++ standard explicitly (and inconsistently) defines that an omitted condition-expression in a for-loop should be treated as `true`.

We recommend avoiding this form of the for loop altogether and using `while (true)` instead.

### For-loops with multiple counters

Although for-loops typically iterate over only one variable, sometimes for-loops need to work with multiple variables. To assist with this, the programmer can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression:
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```
This loop defines and initializes two new variables: `x` and `y`. It iterates `x` over the range `0` to `9`, and after each iteration `x` is incremented and `y` is decremented.

This is about the only place in C++ where defining multiple variables in the same statement, and use of the comma operator is considered an acceptable practice.
#### Related content
We cover the comma operator in lesson [6.5 -- The comma operator](https://www.learncpp.com/cpp-tutorial/the-comma-operator/).
#### Best practice

Defining multiple variables (in the init-statement) and using the comma operator (in the end-expression) is acceptable inside a for-statement.

### Nested for-loops

Like other types of loops, for-loops can be nested inside other loops. In the following example, we’re nesting a for-loop inside another for-loop:

```cpp
#include <iostream>

int main()
{
	for (char c{ 'a' }; c <= 'e'; ++c) // outer loop on letters
	{
		std::cout << c; // print our letter first

		for (int i{ 0 }; i < 3; ++i) // inner loop on all numbers
			std::cout << i;

		std::cout << '\n';
	}
```

### Variables used only inside a loop should be defined inside the loop

New programmers often think that creating variables is expensive, so that it is better to create a variable once (and then assign values to it) than create it many times (and use initialization). That leads to loops that look like some variation of the following:
```cpp
	int i {}; // i defined outside loop
    for (i = 0; i < 10; ++i) // i assigned value
    {
        std::cout << i << ' ';
    }

    // i can still be accessed here
```
However, creating a variable has no cost -- it is the initialization that has a cost, and there is typically no cost difference between initialization and assignment. The above example makes `i` available beyond the loop. Unless using a variable beyond the loop is required, defining a variable outside the loop is likely to have two consequences:
1. It makes our program more complex, as we have to read more code to see where the variable is used.
2. It may actually be slower because the compiler may not be able to optimize a variable with a larger scope as effectively.

Consistent with our best practice to define variables in the smallest reasonable scope possible, a variable that is only used within a loop should be defined inside the loop rather than outside.
#### Best practice
Variables used only inside a loop should be defined inside the scope of the loop.

### Conclusion

For-statements are the most commonly used loop in the C++ language because they place all of the necessary information about loop variables, loop condition, and loop variable modifies at the top of the loops, which helps reduce errors. Even though its syntax is typically a bit confusing to new programmers, you will see for-loops so often that you will understand them in no time at all!

For-statements excel when you have a counter variable. If you do not have a counter, a while-statement is probably a better choice.
#### Best practice
Prefer for-loops over while-loops when there is an obvious loop variable.  
Prefer while-loops over for-loops when there is no obvious loop variable.

## 8.11 [Break and continue](https://www.learncpp.com/cpp-tutorial/break-and-continue/)

### Break
Although you have already seen the `break` statement in the context of `switch` statements ([8.5 -- Switch statement basics](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/)), it deserves a fuller treatment since it can be used with other types of control flow statements as well. The **break statement** causes a while loop, do-while loop, for loop, or switch statement to end, with execution continuing with the next statement after the loop or switch being broken out of.

### Breaking a switch

In the context of a `switch` statement, a `break` is typically used at the end of each case to signify the case is finished (which prevents fallthrough into subsequent cases):
```cpp
switch (ch)
    {
    case '+':
        std::cout << x << " + " << y << " = " << x + y << '\n';
        break; // don't fall-through to next case
    case '-':
        std::cout << x << " - " << y << " = " << x - y << '\n';
        break; // don't fall-through to next case
    case '*':
        std::cout << x << " * " << y << " = " << x * y << '\n';
        break; // don't fall-through to next case
    case '/':
        std::cout << x << " / " << y << " = " << x / y << '\n';
        break;
    }
```
See lesson [8.6 -- Switch fallthrough and scoping](https://www.learncpp.com/cpp-tutorial/switch-fallthrough-and-scoping/) for more information about fallthrough, along with some additional examples.

### Breaking a loop
In the context of a loop, a `break` statement can be used to end the loop early. Execution continues with the next statement after the end of the loop.
```cpp
// Allow the user to enter up to 10 numbers
    for (int count{ 0 }; count < 10; ++count)
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break; // exit the loop now

        // otherwise add number to our sum
        sum += num;
    }

    // execution will continue here after the break
```

A `break` is also a common way to get out of an intentional infinite loop:
```cpp
 while (true) // infinite loop
    {
        std::cout << "Enter 0 to exit or any other integer to continue: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break;
    }
```
### Break vs return

New programmers sometimes have trouble understanding the difference between `break` and `return`. A `break` statement terminates the switch or loop, and execution continues at the first statement beyond the switch or loop. A `return` statement terminates the entire function that the loop is within, and execution continues at point where the function was called.
```cpp
int breakOrReturn()
{
    while (true) // infinite loop
    {
        std::cout << "Enter 'b' to break or 'r' to return: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'b')
            break; // execution will continue at the first statement beyond the loop

        if (ch == 'r')
            return 1; // return will cause the function to immediately return to the caller (in this case, main())
    }

    // breaking the loop causes execution to resume here
```
### Continue

The **continue statement** provides a convenient way to end the current iteration of a loop without terminating the entire loop.

Here’s an example of using continue:
```cpp
for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue; // go to next iteration

        // If the number is not divisible by 4, keep going
        std::cout << count << '\n';

        // The continue statement jumps to here
    }
```
This program prints all of the numbers from 0 to 9 that aren’t divisible by 4

A `continue` statement works by causing the current point of execution to jump to the bottom of the current loop.

In the case of a for-loop, the end-statement of the for-loop (in the above example, `++count`) still executes after a continue (since this happens after the end of the loop body).

Be careful when using a `continue` statement with while or do-while loops. These loops typically change the value of variables used in the condition inside the loop body. If use of a `continue` statement causes these lines to be skipped, then the loop can become infinite!
```cpp
while (count < 10)
    {
        if (count == 5)
            continue; // jump to end of loop body

        std::cout << count << '\n';

        ++count; // this statement is never executed after count reaches 5

        // The continue statement jumps to here
    }
```
### The debate over use of break and continue
Many textbooks caution readers not to use `break` and `continue` in loops, both because it causes the execution flow to jump around, and because it can make the flow of logic harder to follow. For example, a `break` in the middle of a complicated piece of logic could either be missed, or it may not be obvious under what conditions it should be triggered.

However, used judiciously, `break` and `continue` can help make loops more readable by keeping the number of nested blocks down and reducing the need for complicated looping logic.

For example, consider the following program:
```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates
    bool keepLooping { true }; // controls whether the loop ends or not
    while (keepLooping)
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            keepLooping = false;
        else
        {
            ++count;
            std::cout << "We've iterated " << count << " times\n";
        }
    }
```
This program uses a Boolean variable to control whether the loop continues or not, as well as a nested block that only runs if the user doesn’t exit.

Here’s a version that’s easier to understand, using a `break` statement:
```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates
    while (true) // loop until user terminates
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            break;

        ++count;
        std::cout << "We've iterated " << count << " times\n";
    }
```
In this version, by using a single `break` statement, we’ve avoided the use of a Boolean variable (and having to understand both what its intended use is, and where its value is changed), an `else` statement, and a nested block.

The `continue` statement is most effectively used at the top of a for-loop to skip loop iterations when some condition is met. This can allow us to avoid a nested block.
For example, instead of this:
```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is not divisible by 4...
        if ((count % 4) != 0) // nested block
        {
                // Print the number
                std::cout << count << '\n';
        }
    }
```

We can write this:
```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is divisible by 4, skip this iteration
        if ((count % 4) == 0)
            continue;

        // no nested block needed

        std::cout << count << '\n';
    }
```

Minimizing the number of variables used and keeping the number of nested blocks down both improve code comprehensibility more than a `break` or `continue` harms it. For that reason, we believe judicious use of `break` or `continue` is acceptable.
#### Best practice
Use break and continue when they simplify your loop logic.

### The debate over use of early returns

There’s a similar argument to be made for return statements. A return statement that is not the last statement in a function is called an **early return**. Many programmers believe early returns should be avoided. A function that only has one return statement at the bottom of the function has a simplicity to it -- you can assume the function will take its arguments, do whatever logic it has implemented, and return a result without deviation. Having extra returns complicates the logic.

The counter-argument is that using early returns allows your function to exit as soon as it is done, which reduces having to read through unnecessary logic and minimizes the need for conditional nested blocks, which makes your code more readable.

Some developers take a middle ground, and only use early returns at the top of a function to do parameter validation (catch bad arguments passed in), and then a single return thereafter.

Our stance is that early returns are more helpful than harmful, but we recognize that there is a bit of art to the practice.

#### Best practice
Use early returns when they simplify your function’s logic.

## 8.12 [Halts (exiting your program early)](https://www.learncpp.com/cpp-tutorial/halts-exiting-your-program-early/)
The last category of flow control statement we’ll cover in this chapter is the halt. A **halt** is a flow control statement that terminates the program. In C++, halts are implemented as functions (rather than keywords), so our halt statements will be function calls.

Let’s take a brief detour, and recap what happens when a program exits normally. When the `main()` function returns (either by reaching the end of the function, or via a `return statement`), a number of different things happen.

First, because we’re leaving the function, all local variables and function parameters are destroyed (as per usual).

Next, a special function called `std::exit()` is called, with the return value from `main()` (the `status code`) passed in as an argument. So what is `std::exit()`?

### The std::exit() function

`std::exit()` is a function that causes the program to terminate normally. **Normal termination** means the program has exited in an expected way. Note that the term `normal termination` does not imply anything about whether the program was successful (that’s what the `status code` is for). For example, let’s say you were writing a program where you expected the user to type in a filename to process. If the user typed in an invalid filename, your program would probably return a non-zero `status code` to indicate the failure state, but it would still have a `normal termination`.

`std::exit()` performs a number of cleanup functions. First, objects with static storage duration are destroyed. Then some other miscellaneous file cleanup is done if any files were used. Finally, control is returned back to the OS, with the argument passed to `std::exit()` used as the `status code`.

### Calling std::exit() explicitly

Although `std::exit()` is called implicitly after function `main()` returns, `std::exit()` can also be called explicitly to halt the program before it would normally terminate. When `std::exit()` is called this way, you will need to include the `cstdlib` header.
#### Key insight
`std::exit` is called implicitly when `main()` returns.

Here is an example of using `std::exit()` explicitly:
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::cout << 1 << '\n';
    cleanup();

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
```
Note that the statements after the call to `std::exit()` never execute because the program has already terminated.

Although in the program above we call `std::exit()` from function `main()`, `std::exit()` can be called from any function to terminate the program at that point.

### `std::exit()` does not clean up local variables
One important note about calling `std::exit()` explicitly: `std::exit()` does not clean up any local variables (either in the current function, or in functions up the call stack). This means calling `std::exit()` can be dangerous if your program relies on any local variables cleaning themselves up.

#### Warning
The `std::exit()` function does not clean up local variables in the current function or up the call stack.

### std::atexit

Because `std::exit()` terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

#### As an aside…

When an application exits, modern OSes will generally clean up any memory that the application does not properly clean up itself. This leads to the question, “so why bother doing cleanup on exit?”. There are (at least) two reasons:

1. Cleaning up allocated memory is a “good habit” that you will need to use to avoid memory leaks while the application is running. Cleaning up in some cases and not others is inconsistent and can lead to errors. Not cleaning up memory properly can also impact the way certain tools like memory profilers behave (they may be unable to distinguish memory that you inadvertently aren’t intentionally cleaning up from memory that you intentionally aren’t cleaning up because you don’t have to).
2. There are other kinds of cleanup that may be necessary for your program to behave predictably. For example, if you write data to a file and then unexpectedly exit, that data may not have been flushed to the file yet, and may be lost when the program exits. Closing the file before shutting down helps ensure that all cached data will be written first. Or you may want to send data about the user’s session, or why the program is shutting down to server before the shutdown actually happens.

In the above example, we called function `cleanup()` to handle our cleanup tasks. However, remembering to manually call a cleanup function before calling every call to exit() adds burden to the programmer and is a recipe for errors.

To assist with this, C++ offers the `std::atexit()` function, which allows you to specify a function that will automatically be called on program termination via `std::exit()`.

Related content
We discuss passing functions as arguments in lesson [20.1 -- Function Pointers](https://www.learncpp.com/cpp-tutorial/function-pointers/).

Here’s an example:
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
```

Note that when we pass `cleanup()` function as an argument, we use `cleanup` (the function’s name), not `cleanup()` (which would actually call the function).

The benefit of `std::atexit()` is that we only have to call it once (probably from within function `main()`). Since `std::atexit()` will be automatically called on exit, we don’t have to remember to call anything before calling `std::exit()`.

A few notes here about `std::atexit()` and the cleanup function: First, because `std::exit()` is called implicitly when `main()` terminates, this will invoke any functions registered by `std::atexit()` if the program exits that way. Second, the function being registered must take no parameters and have no return value. Finally, you can register multiple cleanup functions using `std::atexit()` if you want, and they will be called in reverse order of registration (the last one registered will be called first).

#### For advanced readers
In multi-threaded programs, calling `std::exit()` can cause your program to crash (because the thread calling `std::exit()` will cleanup static objects that may still be accessed by other threads). For this reason, C++ has introduced another pair of functions that work similarly to `std::exit()` and `std::atexit()` called `std::quick_exit()` and `std::at_quick_exit()`. `std::quick_exit()` terminates the program normally, but does not clean up static objects, and may or may not do other types of cleanup. `std::at_quick_exit()` performs the same role as `std::atexit()` for programs terminated with `std::quick_exit()`.
### std::abort and std::terminate

C++ contains two other halt-related functions.

The `std::abort()` function causes your program to terminate abnormally. **Abnormal termination** means the program had some kind of unusual runtime error and the program couldn’t continue to run. For example, trying to divide by 0 will result in an abnormal termination. `std::abort()` does not do any cleanup.

```cpp
#include <cstdlib> // for std::abort()
#include <iostream>

int main()
{
    std::cout << 1 << '\n';
    std::abort();

    // The following statements never execute
```

We will see cases in future lesson [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/) where `std::abort` is called implicitly.

The `std::terminate()` function is typically used in conjunction with `exceptions` (we’ll cover exceptions in a later chapter). Although `std::terminate` can be called explicitly, it is more often called implicitly when an exception isn’t handled (and in a few other exception-related cases). By default, `std::terminate()` calls `std::abort()`.
### When should you use a halt?

The short answer is “almost never”. Destroying local objects is an important part of C++ (particularly when we get into classes), and none of the above-mentioned functions clean up local variables. Exceptions are a better and safer mechanism for handling error cases.
#### Best practice
Only use a halt if there is no safe or reasonable way to return normally from the main function. If you haven’t disabled exceptions, prefer using exceptions for handling errors safely.

#### Tip
Although explicit use of halts should be minimized, there are many other ways that a program can shut down unexpectedly. For example:
- The application could crash due to a bug (in which case the OS will shut it down).
- The user might kill the application in various ways.
- The user might turn off (or lose) power to their computer.
- The sun could go supernova and consume the earth in a giant ball of fire.

A well-designed program should be able to handle being shut down at any point with minimal repercussions.

As a common example of this, modern games often autosave game state and user settings periodically, so that if the game is unexpectedly shut down without saving, the user can continue later (using the prior autosave) without much lost progress.

## 8.13 [Introduction to random number generation](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/)
The ability to generate random numbers can be useful in certain kinds of programs, particularly in games, statistical modelling programs, and cryptographic applications that need to encrypt and decrypt things. Take games for example -- without random events, monsters would always attack you the same way, you’d always find the same treasure, the dungeon layout would never change, etc… and that would not make for a very good game.

In real life, we often produce randomization by doing things like flipping a coin, rolling a dice, or shuffling a deck of cards. These events aren’t actually random, but involve so many physical variables (e.g. gravity, friction, air resistance, momentum, etc…) that they become almost impossible to predict or control, and (unless you’re a magician) produce results that are for all intents and purposes random.

However, computers aren’t designed to take advantage of physical variables -- your computer can’t toss a coin, throw a dice, or shuffle real cards. Modern computers live in a controlled electrical world where everything is binary (0 or 1) and there is no in-between. By their very nature, computers are designed to produce results that are as predictable as possible. When you tell the computer to calculate 2 + 2, you _always_ want the answer to be 4. Not 3 or 5 on occasion.

Consequently, computers are generally incapable of generating truly random numbers (at least through software). Instead, modern programs typically _simulate_ randomness using an algorithm.

In this lesson, we’ll cover a lot of the theory behind how random numbers are generated in programs, and introduce some terminology we’ll use in future lessons.
### Algorithms and state

First, let’s take a detour through the concepts of algorithms and states.

An **algorithm** is a finite sequence of instructions that can be followed to solve some problem or produce some useful result.

For example, let’s say your boss gives you a small text file containing a bunch of unsorted names (one per line), and asks you to sort the list. Since the list is small, and you don’t expect to do this often, you decide to sort it by hand. There are multiple ways to sort a list, but you might do something like this:
- Create a new empty list to hold the sorted results
- Scan the list of unsorted names to find the name that comes first alphabetically
- Cut that name out of the unsorted list and paste it at the bottom of the sorted list
- Repeat the previous two steps until there are no more names on the unsorted list

The above set of steps describes a sorting algorithm (using natural language). By nature, algorithms are reusable -- if your boss asks you to sort another list tomorrow, you can just apply the same algorithm to the new list.

Because computers can execute instructions and manipulate data much more quickly than we can, algorithms are often written using programming languages, allowing us to automate tasks. In C++, algorithms are typically implemented as reusable functions.

Here’s a simple algorithm for generating a sequence of numbers where each successive number is incremented by 1:

```cpp
#include <iostream>

int plusOne()
{
    static int s_state { 3 }; // only initialized the first time this function is called

    // Generate the next number

    ++s_state;      // first we modify the state
    return s_state; // then we use the new state to generate the next number in the sequence
}

int main()
{
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';
```

This algorithm is pretty simple. The first time we call `plusOne()`, `s_state` is initialized to value `3`. Then the next number in the output sequence is generated and returned.

An algorithm is considered to be **stateful** if it retains some information across calls. Conversely, a **stateless** algorithm does not store any information (and must be given all the information it needs to work with whenever it is called). Our `plusOne()` function is stateful, in that it uses the static variable `s_state` to store the last number that was generated. When applied to algorithms, the term **state** refers to the current values held in stateful variables (those retained across calls).

To generate the next number in the sequence, our algorithm uses a two step process:
- First, the current state (initialized from the start value, or preserved from the prior call) is modified to produce a new state.
- Then, the next number in the sequence is generated from the new state.

Our algorithm is considered **deterministic**, meaning that for a given input (the value provided for `start`), it will always produce the same output sequence.

###  Pseudo-random number generators (PRNGs)

To simulate randomness, programs typically use a pseudo-random number generator. A **pseudo-random number generator (PRNG)** is an algorithm that generates a sequence of numbers whose properties simulate a sequence of random numbers.

It’s easy to write a basic PRNG algorithm. Here’s a short PRNG example that generates 100 16-bit pseudo-random numbers:
```cpp
// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    // Generate the next number

    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    s_state = 8253729 * s_state + 2396403; // first we modify the state
    return s_state % 32768; // then we use the new state to generate the next number in the sequence
}

int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << LCG16() << '\t';

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }
```
The result of this program is:
```
4339	838  	25337	15372	6783	2642	6021	19992	14859	26462	
25105	13860	28567	6762	17053	29744	15139	9078	14633	2108	
7343	642 	17845	29256	5179	14222	26689	12884	8647	17050	
8397	18528	17747	9126	28505	13420	32479	23218	21477	30328	
20075	26558	20081	3716	13303	19146	24317	31888	12163	982	
1417	16540	16655	4834	16917	23208	26779	30702	5281	19124	
9767	13050	32045	4288	31155	17414	31673	11468	25407	11026	
4165	7896	25291	26654	15057	26340	30807	31530	31581	1264	
9187	25654	20969	30972	25967	9026	15989	17160	15611	14414	
16641	25364	10887	9050	22925	22816	11795	25702	2073	9516
```

Each number appears to be pretty random with respect to the previous one.

Notice how similar `LCG16()` is to our `plusOne()` example above! The state is initially set to value `0`. Then to produce the next number in the output sequence, the current state is modified (by applying some mathematical operations) to produce a new state, and the next number in the sequence is generated from that new state.

As it turns out, this particular algorithm isn’t very good as a random number generator (note how each result alternates between even and odd -- that’s not very random!). But most PRNGs work similarly to `LCG16()` -- they just typically use more state variables and more complex mathematical operations in order to generate better quality results.

### Seeding a PRNG

The sequence of “random numbers” generated by a PRNG is not random at all. Just like our `plusOne()` function, `LCG16()` is also deterministic. Given some initial state value (such as `0`), a PRNG will generate the same sequence of numbers each time. If you run the above program 3 times, you’ll see it generates the same sequence of values each time.

In order to generate different output sequences, the initial state of a PRNG needs to be varied. The value (or set of values) used to set the initial state of a PRNG is called a **random seed** (or **seed** for short). When the initial state of a PRNG has been set using a seed, we say it has been **seeded**.

#### Key insight
Because the initial state of the PRNG is set from the seed value(s), all of the values that a PRNG will produce are deterministically calculated from the seed value(s).

The seed value is typically provided by the program using the PRNG. Here’s a sample program that requests a seed value from the user and then generates 10 random numbers using that seed value (using our `LCG16()` function).
```cpp

unsigned int g_state{ 0 };

void seedPRNG(unsigned int seed)
{
    g_state = seed;
}

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    g_state = 8253729 * g_state + 2396403; // first we modify the state
    return g_state % 32768; // then we use the new state to generate the next number in the sequence
}

void print10()
{
    // Print 10 random numbers
    for (int count{ 1 }; count <= 10; ++count)
    {
        std::cout << LCG16() << '\t';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x {};
    std::cout << "Enter a seed value: ";
    std::cin >> x;

    seedPRNG(x); // seed our PRNG
    print10();   // generate 10 random values
```
Notice that when we provide the same seed value, we get the same output sequence. If we provide a different seed value, we get a different output sequence.
### Seed quality and underseeding

If we want the program to produce different randomized numbers each time it is run, then we need some way to vary the seed each time the program is run. Asking the user to provide a seed value isn’t great, since they can just enter the same value each time. The program really needs some way to generate a randomized seed value each time it is run. Unfortunately, we can’t use a PRNG to generate a random seed, because we need a randomized seed to generate random numbers. Instead, we’ll typically use a seed generation algorithm that is designed to produce seed values. We’ll discuss (and implement) such algorithms in the next lesson.

The theoretical maximum number of unique sequences that a PRNG can generate is determined by the number of bits in the PRNG’s state. For example, a PRNG with 128 bits of state can theoretically generate up to 2^128 (340,282,366,920,938,463,463,374,607,431,768,211,456) unique output sequences. That’s a lot!

However, which output sequence is _actually_ generated depends on the initial state of the PRNG, which is determined by the seed. Therefore, practically speaking, the number of unique output sequences a PRNG can _actually_ generate is limited by the number of unique seed values the program using the PRNG can provide. For example, if a particular seed generation algorithm can only generate 4 different seed values, then the PRNG will only be able to generate at most 4 different output sequences.

If a PRNG is not provided with enough bits of quality seed data, we say that it is **underseeded**. An underseeded PRNG may begin to produce randomized results whose quality is compromised in some way -- and the more severe the underseeding, the more the quality of the results will suffer.

For example, an underseeded PRNG may exhibit any of the following issues:
- The random sequences generated by consecutive runs may have a high correlation to each other.
- On the generation of the Nth random number, some values will never be able to be generated. For example, a Mersenne Twister that is underseeded in a particular way will never generate the values 7 or 13 as its first output.
- Someone may be able to guess the seed based on the initial random value produced (or the first few random values). That would allow them to then generate all future random numbers that are going to be produced by the generator. This may allow them to cheat or game the system.
#### For advanced readers
An ideal seed should have the following characteristics:
- The seed should contain at least as many bits as the state of the PRNG, so that every bit in the state of the PRNG can be initialized by an independent bit in the seed.
- Each bit in the seed should be independently randomized.
- The seed should contain a good mix of 0 and 1s distributed across all of the bits.
- There should be no bits in the seed that are always 0 or always 1. These “stuck bits” do not provide any value.
- The seed should have a low correlation with previously generated seeds.

In practice, we may compromise on some of these characteristics. Some PRNGs have huge states (e.g. the state of a Mersenne Twister has 19937 bits), and generating quality seeds that large can be difficult. As a result, PRNGs with large states are often designed to be resilient to being seeded with fewer bits. Stuck bits are also common. For example, if we use the system clock as part of our seed, we’ll end up with some number of stuck bits, as the bits that represent larger time units (e.g. years) are effectively stuck.


Developers who aren’t familiar with proper seeding practices will often try to initialize a PRNG using a single 32-bit or 64-bit value (unfortunately, the design of C++’s standard Random library inadvertently encourages this). This will generally result in a significantly underseeded PRNG.

Seeding a PRNG with 64 bytes of quality seed data (less if the PRNGs state is smaller) is typically good enough to facilitate the generation of 8-byte random values for non-sensitive uses (e.g. not statistical simulations or cryptography).

### What makes a good PRNG? (optional reading)
In order to be a good PRNG, the PRNG needs to exhibit a number of properties:
- The PRNG should generate each number with approximately the same probability.

This is called distribution uniformity. If some numbers are generated more often than others, the result of the program that uses the PRNG will be biased! To check distribution uniformity, we can use a histogram. A histogram is a graph that tracks how many times each number has been generated. Since our histograms are text-based, we’ll use a * symbol to represent each time a given number was generated.

Consider a PRNG that generates numbers between 1 and 6. If we generate 36 numbers, a PRNG with distribution uniformity should generate a histogram that looks something like this:
```
1|******
2|******
3|******
4|******
5|******
6|******
```

A PRNG that is biased in some way will generate a histogram that is uneven, like this:
```
1|***
2|******
3|******
4|******
5|******
6|*********
```

Finding PRNG algorithms that produce uniform results is difficult.
- The method by which the next number in the sequence is generated shouldn’t be predictable.
-  The PRNG should have a good dimensional distribution of numbers.
-This means the PRNG should return numbers across the entire range of possible results at random. For example, the PRNG should generate low numbers, middle numbers, high numbers, even numbers, and odd numbers seemingly at random.
-  The PRNG should have a high period for all seeds
All PRNGs are periodic, which means that at some point the sequence of numbers generated will begin to repeat itself. The length of the sequence before a PRNG begins to repeat itself is known as the **period**.

PRNG are stuck generating t a sequence repeatedly. This happens because PRNGs are deterministic. Once the state of a PRNG is identical to a prior state, the PRNG will start producing the same sequence of outputs it has produced before -- resulting in a loop.

A good PRNG should have a long period for _all_ seed numbers. Designing an algorithm that meets this property can be extremely difficult -- many PRNGs have long periods only for some seeds and not others. If the user happens to pick a seed that results in a state with a short period, then the PRNG won’t do a good job if many random numbers are needed.

- The PRNG should be efficient
Most PRNGs have a state size of less than 4096 bytes, so total memory usage typically isn’t a concern. However, the larger the internal state, the more likely the PRNG is to be underseeded, and the slower the initial seeding will be (since there’s more state to initialize).

Second, to generate the next number in sequence, a PRNG has to mix up its internal state by applying various mathematical operations. How much time this takes can vary significantly by PRNG and also by architecture (some PRNGs perform better on certain architectures than others). This doesn’t matter if you only generate random numbers periodically, but can have a huge impact if you need lots of randomness.

### There are many different kinds of PRNG algorithms

Over the years, many different kinds of PRNG algorithms have been developed (Wikipedia has a good list [here](https://en.wikipedia.org/wiki/List_of_random_number_generators)). Every PRNG algorithm has strengths and weaknesses that might make it more or less suitable for a particular application, so selecting the right algorithm for your application is important.

Many PRNGs are now considered relatively poor by modern standards -- and there’s no reason to use a PRNG that doesn’t perform well when it’s just as easy to use one that does.

### Randomization in C++[](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/#random)

The randomization capabilities in C++ are accessible via the `<random>` header of the standard library. Within the random library, there are 6 PRNG families available for use (as of C++20):

|Type name|Family|Period|State size*|Performance|Quality|Should I use this?|
|---|---|---|---|---|---|---|
|minstd_rand  <br>minstd_rand0|Linear congruential generator|2^31|4 bytes|Bad|Awful|No|
|mt19937  <br>mt19937_64|Mersenne twister|2^19937|2500 bytes|Decent|Decent|Probably (see next section)|
|ranlux24  <br>ranlux48|Subtract and carry|10^171|96 bytes|Awful|Good|No|
|knuth_b|Shuffled linear congruential generator|2^31|1028 bytes|Awful|Bad|No|
|default_random_engine|Any of above (implementation defined)|Varies|Varies|?|?|No2|
|rand()|Linear congruential generator|2^31|4 bytes|Bad|Awful|Nono|

There is zero reason to use `knuth_b`, `default_random_engine`, or `rand()` (which is a random number generator provided for compatibility with C).

As of C++20, the Mersenne Twister algorithm is the only PRNG that ships with C++ that has both decent performance and quality.
#### For advanced readers
A test called [PracRand](http://pracrand.sourceforge.net/) is often used to assess the performance and quality of PRNGs (to determine whether they have different kinds of biases). You may also see references to SmallCrush, Crush or BigCrush -- these are other tests that are sometimes used for the same purpose.

If you want to see what the output of Pracrand looks like, [this website](https://arvid.io/2018/06/30/on-cxx-random-number-generator-quality/) has output for all of the PRNGs that C++ supports as of C++20.

### So we should use Mersenne Twister, right?
Probably. For most applications, Mersenne Twister is fine, both in terms of performance and quality.

However, it’s worth noting that by modern PRNG standards, Mersenne Twister is [a bit outdated](https://en.wikipedia.org/wiki/Mersenne_Twister#Characteristics). The biggest issue with Mersenne Twister is that its results can be predicted after seeing 624 generated numbers, making it non-suitable for any application that requires non-predictability.

If you are developing an application that requires the highest quality random results (e.g. a statistical simulation), the fastest results, or one where non-predictability is important (e.g. cryptography), you’ll need to use a 3rd party library.

Popular choices as of the time of writing:

- The [Xoshiro family](https://prng.di.unimi.it/) and [Wyrand](https://github.com/wangyi-fudan/wyhash) for non-cryptographic PRNGs.
- The [Chacha family](https://cr.yp.to/chacha.html) for cryptographic (non-predictable) PRNGs.

Okay, now that your eyes are probably bleeding, that’s enough theory. Let’s discuss how to actually generate random numbers with Mersenne Twister in C++.
## 8.14 [Generating random numbers using Mersenne Twister](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/)
In the previous lesson [8.13 -- Introduction to random number generation](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/), we introduced the concept of random number generation, and discussed how PRNG algorithms are typically used to simulate randomness in programs.

In this lesson, we’ll take a look at how to generate random numbers in your programs. To access any of the randomization capabilities in C++, we include the `<random>` header of the standard library.

### Generating random numbers in C++ using Mersenne Twister

The Mersenne Twister PRNG, besides having a great name, is probably the most popular PRNG across all programming languages. Although it is a bit old by today’s standards, it generally produces quality results and has decent performance. The random library has support for two Mersenne Twister types:

- `mt19937` is a Mersenne Twister that generates 32-bit unsigned integers
- `mt19937_64` is a Mersenne Twister that generates 64-bit unsigned integers

Using Mersenne Twister is straightforward:
```cpp
#include <random> // for std::mt19937

int main()
{
	std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t'; // generate a random number
```
First, we include the `<random> `header, since that’s where all the random number capabilities live. Next, we instantiate a 32-bit Mersenne Twister engine via the statement `std::mt19937 mt`. Then, each time we want to generate a random 32-bit unsigned integer, we call `mt()`.
#### As an aside…
Since `mt` is a variable, you may be wondering what `mt()` means.
In lesson [5.7 -- Introduction to std::string](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/), we showed an example where we called the function `name.length()`, which invoked the `length()` function on `std::string` variable `name`.
`mt()` is a concise syntax for calling the function `mt.operator()`, which for these PRNG types has been defined to return the next random result in the sequence. The advantage of using `operator()` instead of a named function is that we don’t need to remember the function’s name, and the concise syntax is less typing.

### Rolling a dice using Mersenne Twister

A 32-bit PRNG will generate random numbers between 0 and 4,294,967,295, but we do not always want numbers in that range. If our program was simulating a board game or a dice game, we’d probably want to simulate the roll of a 6-sided dice by generating random numbers between 1 and 6. If our program was a dungeon adventure, and the player had a sword that did between 7 and 11 damage to monsters, then we’d want to generate random numbers between 7 and 11 whenever the player hit a monster.

Unfortunately, PRNGs can’t do this. They can only generate numbers that use the full range. What we need is some way to convert a number that is output from our PRNG into a value in the smaller range we want (with an even probability of each value occurring). While we could write a function to do this ourselves, doing so in a way that produces non-biased results is non-trivial.

Fortunately, the random library can help us here, in the form of random number distributions. A **random number distribution** converts the output of a PRNG into some other distribution of numbers.

#### As an aside…
For the stats geeks: a random number distribution is just a probability distribution designed to take PRNG values as input.

The random library has many random numbers distributions, most of which you will never use unless you’re doing some kind of statistical analysis. But there’s one random number distribution that’s extremely useful: a **uniform distribution** is a random number distribution that produces outputs between two numbers X and Y (inclusive) with equal probability.

Here’s a similar program to the one above, using a uniform distribution to simulate the roll of a 6-sided dice:
```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution

int main()
{
	std::mt19937 mt{};

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here
```
There are only two noteworthy differences in this example compared to the previous one. First, we’ve created a uniform distribution variable (named `die6`) to generate numbers between 1 and 6. Second, instead of calling `mt()` to generate 32-bit unsigned integer random numbers, we’re now calling `die6(mt)` to generate a value between 1 and 6.
### The above program isn’t as random as it seems
Although the results of our dice rolling example above are pretty random, there’s a major flaw with the program. Run the program 3 times and see if you can figure out what it is. Go ahead, we’ll wait.

_Jeopardy music_

If you run the program multiple times, you will note that it prints the same numbers every time! While each number in the sequence is random with regards to the previous one, the entire sequence is not random at all! Each run of our program produces the exact same result.

Imagine that you’re writing a game of hi-lo, where the user has 10 tries to guess a number that has been picked randomly, and the computer tells the user whether their guess is too high or too low. If the computer picks the same random number every time, the game won’t be interesting past the first time it is played. So let’s take a deeper look at why this is happening, and how we can fix it.

In the prior lesson ([8.13 -- Introduction to random number generation](https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/)), we covered that each number in a PRNG sequence is in a deterministic way. And that the state of the PRNG is initialized from the seed value. Thus, given any starting seed number, PRNGs will always generate the same sequence of numbers from that seed as a result.

Because we are value initializing our Mersenne Twister, it is being initialized with the same seed every time the program is run. And because the seed is the same, the random numbers being generated are also the same.

In order to make our entire sequence randomized differently each time the program is run, we need to pick a seed that’s not a fixed number. The first answer that probably comes to mind is that we need a random number for our seed! That’s a good thought, but if we need a random number to generate random numbers, then we’re in a catch-22. It turns out, we really don’t need our seed to be a random number -- we just need to pick something that changes each time the program is run. Then we can use our PRNG to generate a unique sequence of pseudo-random numbers from that seed.

There are two methods that are commonly used to do this:
- Use the system clock
- Use the system’s random device
### Seeding with the system clock
What’s one thing that’s different every time you run your program? Unless you manage to run your program twice at exactly the same moment in time, the answer is that the current time is different. Therefore, if we use the current time as our seed value, then our program will produce a different set of random numbers each time it is run. C and C++ have a long history of PRNGs being seeded using the current time (using the `std::time()` function), so you will probably see this in a lot of existing code.

Fortunately, C++ has a chrono library containing various clocks that we can use to generate a seed value. To minimize the chance of two time values being identical if the program is run quickly in succession, we want to use some time measure that changes as quickly as possible. For this, we’ll ask the clock how much time has passed since the earliest time it can measure. This time is measured in “ticks”, which is a very small unit of time (usually nanoseconds, but could be milliseconds).

```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here
```

The above program has only two changes from the prior. First, we’re including `<chrono>`, which gives us access to the clock. Second, we’re using the current time from the clock as a seed value for our Mersenne Twister.

The results generated by this program should now be different each time it is run, which you can verify experimentally by running it several times.

The downside of this approach is that if the program is run several times in quick succession, the seeds generated for each run won’t be that different, which can impact the quality of the random results from a statistical standpoint. For normal programs, this doesn’t matter, but for programs that require high quality, independent results, this method of seeding may be insufficient.

#### Tip
`std::chrono::high_resolution_clock` is a popular choice instead of `std::chrono::steady_clock`. `std::chrono::high_resolution_clock` is the clock that uses the most granular unit of time, but it may use the system clock for the current time, which can be changed or rolled back by users. `std::chrono::steady_clock` may have a less granular tick time, but is the only clock with a guarantee that users cannot adjust it.
### Seeding with the random device
The random library contains a type called `std::random_device` that is an implementation-defined PRNG. Normally we avoid implementation-defined capabilities because they have no guarantees about quality or portability, but this is one of the exception cases. Typically `std::random_device` will ask the OS for a pseudo-random number (how it does this depends on the OS).

```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here
```
In the above program, we’re seeding our Mersenne Twister with one random number generated from a temporary instance of `std::random_device`. If you run this program multiple times, it should also produce different results each time.

One potential problem with `std::random_device`: it isn’t required to be non-deterministic, meaning it _could_, on some systems, produce the same sequence every time the program is run, which is exactly what we’re trying to avoid. There was a [bug in MinGW](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=85494) (fixed in GCC 9.2) that would do exactly this, making `std::random_device` useless.

However, the latest versions of the most popular compilers (GCC/MinGW, Clang, Visual Studio) support proper implementations of `std::random_device`.

### Only seed a PRNG once

#### Best practice
Use `std::random_device` to seed your PRNGs (unless it’s not implemented properly for your target compiler/architecture).

#### Q: What does `std::random_device{}()` mean?

`std::random_device{}` creates a value-initialized temporary object of type `std::random_device`. The `()` then calls `operator()` on that temporary object, which returns a randomized value (which we use as an initializer for our Mersenne Twister)

It’s the equivalent of the calling the following function, which uses a syntax you should be more familiar with:

```cpp
unsigned int getRandomDeviceValue()
{
   std::random_device rd{}; // create a value initialized std::random_device object
   return rd(); // return the result of operator() to the caller
}
```
Using `std::random_device{}()` allows us to get the same result without creating a named function or named variable, so it’s much more concise.

#### Q: If std::random_device is random itself, why don’t we just use that instead of Mersenne Twister?

Because std::random_device is implementation defined, we can’t assume much about it. It may be expensive to access or it may cause our program to pause while waiting for more random numbers to become available. The pool of numbers that it draws from may also be depleted quickly, which would impact the random results for other applications requesting random numbers via the same method. For this reason, std::random_device is better used to seed other PRNGs rather than as a PRNG itself.

### Only seed a PRNG once

Many PRNGs can be reseeded after the initial seeding. This essentially re-initializes the state of the random number generator, causing it to generate results starting from the new seed state. Reseeding should generally be avoided unless you have a specific reason to do so, as it can cause the results to be less random, or not random at all.

#### Best practice
Only seed a given pseudo-random number generator once, and do not reseed it.

```cpp
int getCard()
{
    std::mt19937 mt{ std::random_device{}() }; // this gets created and seeded every time the function is called
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}

int main()
{
    std::cout << getCard() << '\n';
```

In the `getCard()` function, the random number generator is being created and seeded every time the function is called. This is inefficient at best, and will likely cause poor random results.

### Mersenne Twister and underseeding issues

The internal state of a Mersenne Twister requires 19937 bits (2493 bytes), which is 624 32-bit values or 312 64-bit values. As a result, `std::mt19937` allocates 624 integers, whereas `std::mt19937_64` allocates 312 integers.
#### As an aside…
The integers allocated by `std::mt19937` are defined to be of type `std::uint_fast32_t`, which could be 32-bit or 64-bit integers depending on the architecture. If `std::uint_fast32_t` resolves to a 64-bit integer, `std::mt19937` will use 624 64-bit integers, making it double the size it needs to be.

In the examples above, where we seed our `std::mt19937` from the clock or std::random_device, our seed is only a single integer. This means we’re essentially initializing 624 integers using a single integer, which is significantly underseeding the Mersenne Twister PRNG. The Random library does the best it can to fill in the remaining 623 values with “random” data… but it can’t work magic. Underseeded PRNG can generate results that are suboptimal for applications that need the highest quality results. For example, seeding `std::mt19937` with a single 32-bit value will never generate the number `42` as its first output.

So how do we fix this? As of C++20, there’s no easy way. But we do have some suggestions.

First, let’s talk about `std::seed_seq` (which stands for “seed sequence”). In the prior lesson, we mentioned that ideally we want our seed data to be as many bits as the state of our PRNG, or our PRNG will be underseeded. But in many cases (especially when our PRNG has a large state), we won’t have that many bits of randomized seed data.

`std::seed_seq` is a type that was designed to help with this. We can pass it as many randomized values as we have, and then it will generate as many additional unbiased seed values as needed to initialize a PRNG’s state. If you initialize `std::seed_seq` with a single value (e.g. from `std::random_device`) and then initialize a Mersenne Twister with the `std::seed_seq` object, `std::seed_seq` will generate 623 values of additional seed data. This won’t add randomness, but it will give us a better mix of 0 and 1 bits. However, the more random data we can provide `std::seed_seq`, the better job it will do for us. So the easiest idea is to simply use `std::random_device` to give `std::seed_seq` more data to work with. If we initialize `std::seed_seq` with 8 values from `std::random_device` instead of 1, then the remaining values generated by `std::seed_seq` should be much better:

```cpp
#include <iostream>
#include <random>

int main()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

This is pretty straightforward so there isn’t much reason not to do this at a minimum.
#### Q: Why not give std::seed_seq 624 values from `std::random_device`?
You can, but this is likely to be slow, and risks depleting the pool of random numbers that `std::random_device` uses.

You can also use other “random” inputs to `std::seed_seq`. We’ve already shown you how to get a value from the clock, so you can throw that in easily. Other things that are sometimes used include the current thread id, the address of particular functions, the user’s id, the process id, etc… Doing that is beyond the scope of this article, but [this article](https://www.pcg-random.org/posts/ease-of-use-without-loss-of-power.html) has some context and a link to [randutils.hpp](https://gist.github.com/imneme/540829265469e673d045) that implements this.

An alternate path is to use a different PRNG with a smaller state. Many good PRNGs use 64 or 128 bits of state, which can easily be initialized using `std::seed_seq` filled with 8 calls to `std::random_device`.

### Warming up a PRNG
When a PRNG is given a poor quality seed (or underseeded), the initial results of the PRNG may not be high quality. For this reason, some PRNGs benefit from being “warmed up”, which is a technique where the first N results generated from the PRNG are discarded. This allows the internal state of the PRNG to be mixed up such that the subsequent results should be of higher quality. Typically a few hundred to a few thousand initial results are discarded. The longer the period of the PRNG, the more initial results should be discarded.

#### As an aside…
Visual Studio’s implementation of `rand()` had (or still has?) a bug where the first generated result would not be sufficiently randomized. You may see older programs that use `rand()` discard a single result as a way to avoid this issue.

The `seed_seq` initialization used by `std::mt19937` performs a warm up, so we don’t need to explicitly warm up `std::mt19937` objects.
### Random numbers across multiple functions or files (Random.h)[](https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/#RandomH)
This content was moved to [8.15 -- Global random numbers (Random.h)](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/).

### Debugging programs that use random numbers
Programs that use random numbers can be difficult to debug because the program may exhibit different behaviors each time it is run. When this is the case, the erroneous behavior you may happen, or it may not. This can waste a lot of time. When debugging, it’s helpful to ensure your program executes the same (incorrect) way each time. That way, you can run the program as many times as needed to isolate where the error is.

For this reason, when debugging, it’s a useful technique to seed your PRNG with a specific fixed value (e.g. `5`) that causes the erroneous behavior to occur. If a given seed doesn’t cause your program to exhibit the error, keep incrementing the seed value until you find one that does. This will ensure your program generates the same results each time, making debugging easier. Once you’ve found the error, you can use your normal seeding method to start generating randomized results again.

Q: Help! My random number generator is generating the same sequence of random numbers.
If your random number generator is generating the same sequence of random numbers every time your program is run, you probably didn’t seed it properly (or at all). Make sure you’re seeding it with a value that changes each time the program is run.

Q: Help! My random number generator keeps generating the same number over and over.
If your random number generator is generating the same number every time you ask it for a random number, then you are probably either reseeding the random number generator before generating a random number, or you’re creating a new random generator for each random number.
## 8.15 [Global random numbers (Random.h)](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
What happens if we want to use a random number generator in multiple functions or files? One way is to create (and seed) our PRNG in our `main()` function, and then pass it everywhere we need it. But that’s a lot of passing for something we may only use sporadically, and in many different places. It would add a lot of clutter to our code to pass such an object around.

Alternately, you could create a static local `std::mt19937` variable in each function that needs it (static so that it only gets seeded once). However, it’s overkill to have every function that uses a random number generator define and seed its own local generator, and the low volume of calls to each generator may lead to lower quality results.

What we really want is a single PRNG object that we can share and access anywhere, across all of our functions and files. The best option here is to create a global random number generator object (inside a namespace!). Remember how we told you to avoid non-const global variables? This is an exception.

Here’s a simple, header-only solution that you can #include in any code file that needs access to a randomized, self-seeded `std::mt19937`:

Random.h:
```cpp
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```
### Using Random.h

Generating random numbers using the above is as simple as following these three steps:
1. Copy/paste the above code into a file named `Random.h` in your project directory and save it. Optionally add Random.h to your project.
2. `#include "Random.h"` from any .cpp file in your project that needs to generate random numbers.
3. Call `Random::get(min, max)` to generate a random number between `min` and `max` (inclusive). No initialization or setup is required.

Here is a sample program demonstrating different uses of Random.h:

main.cpp:
```cpp
#include "Random.h" // defines Random::mt, Random::get(), and Random::generate()
#include <cstddef> // for std::size_t
#include <iostream>

int main()
{
	// We can call Random::get() to generate random integral values
	// If the two arguments have the same type, the returned value will have that same type.
	std::cout << Random::get(1, 6) << '\n';   // returns int between 1 and 6
	std::cout << Random::get(1u, 6u) << '\n'; // returns unsigned int between 1 and 6

        // In cases where we have two arguments with different types
        // and/or if we want the return type to be different than the argument types
        // We must specify the return type using a template type argument (between the angled brackets)
	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	std::cout << Random::get<std::size_t>(1, 6u) << '\n'; // returns std::size_t between 1 and 6

	// If we have our own distribution, we can access Random::mt directly

	// Let's create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die6(Random::mt) << '\t'; // generate a roll of the die here
	}

	std::cout << '\n';

	return 0;
}
```

### A few notes about the implementation of Random.h Optional

Normally, defining variables and functions in a header file would cause violations of the one-definition rule (ODR) when that header file was included into more than one source file. However, we’ve made our `mt` variable and supporting functions `inline`, which allows us to have duplicate definitions without violating the ODR so long as those definitions are all identical. Because we’re `#including` those definitions from a header file (rather than typing them manually, or copy/pasting them), we can ensure they are identical. Inline functions and variables were added to the language largely to make doing this kind of header-only functionality possible.

#### Related content
We cover inline functions and variables in lesson [7.9 -- Inline functions and variables](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/).

The other challenge that we have to overcome is in how we initialize our global `Random::mt` object, as we want it to be self-seeding so that we don’t have to remember to explicitly call an initialization function for it to work correctly. Our initializer must be an expression. But in order to initialize a `std::mt19937`, we need several helper objects (a `std::random_device` and a `std::seed_seq`) which must be defined as statements. This is where a helper function comes in handy. A function call is an expression, so we can use the return value of a function as an initializer. And inside the function itself, we can have any combination of statements that we need. Thus, our `generate()` function creates and returns a fully-seeded `std::mt19937` object (seeded using both the system clock and `std::random_device`) that we use as the initializer to our global `Random::mt` object.
## 8.x [Chapter 8 summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-8-summary-and-quiz/)

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

#### Related content
`assert` is a preprocessor macro that terminates the program if the associated argument evaluates to false. So when we write `assert(!isPrime(0))`, we’re meaning “if isPrime(0) is true, then terminate the program”. We cover assert in more detail in lesson [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/).
