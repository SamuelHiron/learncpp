# Error Detection and Handling

## 9.1 [Introduction to testing your code](https://www.learncpp.com/cpp-tutorial/introduction-to-testing-your-code/)
So, you’ve written a program, it compiles, and it even appears to work! What now?

Well, it depends. If you’ve written your program to be run once and discarded, then you’re done. In this case, it may not matter that your program doesn’t work for every case -- if it works for the one case you needed it for, and you’re only going to run it once, then you’re done.

If your program is entirely linear (has no conditionals, such as _if statements_ or _switch statements_), takes no inputs, and produces the correct answer, then you’re probably done. In this case, you’ve already tested the entire program by running it and validating the output. You may want to compile and run the program on several different systems to ensure it behaves consistently (if it doesn’t, you’ve probably done something that produces undefined behavior that just happens to work anyway on your initial system).

But most likely you’ve written a program you intend to run many times, that uses loops and conditional logic, and accepts user input of some kind. You’ve possibly written functions that may be reusable in other future programs. You may have experienced a bit of **scope creep**, where you added some new capabilities that were originally not planned for. Maybe you’re even intending to distribute this program to other people (who are likely to try things you haven’t thought of). In this case, you really should be validating that your program works like you think it does under a wide variety of conditions -- and that requires some proactive testing.

Just because your program worked for one set of inputs doesn’t mean it’s going to work correctly in all cases.

**Software testing** (also called **software validation**) is the process of determining whether or not the software actually works as expected.
### The testing challenge

Before we talk about some practical ways to test your code, let’s talk about why testing your program comprehensively is difficult.

Consider this simple program:
```cpp
#include <iostream>

void compare(int x, int y)
{
    if (x > y)
        std::cout << x << " is greater than " << y << '\n'; // case 1
    else if (x < y)
        std::cout << x << " is less than " << y << '\n'; // case 2
    else
        std::cout << x << " is equal to " << y << '\n'; // case 3
}

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another number: ";
    int y{};
    std::cin >> y;

    compare(x, y);

    return 0;
}
```
Assuming a 4-byte integer, explicitly testing this program with every possible combination of inputs would require that you run the program 18,446,744,073,709,551,616 (~18 quintillion) times. Clearly that’s not a feasible task!

Every time we ask for user input, or have a conditional in our code, we increase the number of possible ways our program can execute by some multiplicative factor. For all but the simplest programs, explicitly testing every combination of inputs becomes impossible almost immediately.

Now, your intuition should be telling you that you really shouldn’t need to run the above program 18 quintillion times to ensure it works. You may reasonably conclude that if case 1 works for one pair of `x` and `y` values where `x > y`, it should work for any pair of `x` and `y` where `x > y`. Given that, it becomes apparent that we really only need to run this program about three times (once to exercise each of the three cases in function `compare()`) to have a high degree of confidence it works as desired. There are other similar tricks we can use to dramatically reduce the number of times we have to test something, in order to make testing manageable.

There’s a lot that can be written about testing methodologies -- in fact, we could write a whole chapter on it. But since it’s not a C++ specific topic, we’ll stick to a brief and informal introduction, covered from the point of view of you (as the developer) testing your own code. In the next few subsections, we’ll talk about some _practical_ things you should be thinking about as you test your code.
### Test your programs in small pieces

Consider an auto manufacturer that is building a custom concept car. Which of the following do you think they do?  
a) Build (or buy) and test each car component individually before installing it. Once the component has been proven to work, integrate it into the car and retest it to make sure the integration worked. At the end, test the whole car, as a final validation that everything seems good.  
b) Build a car out of all of the components all in one go, then test the whole thing for the first time right at the end.

It probably seems obvious that option a) is a better choice. And yet, many new programmers write code like option b)!

In case b), if any of the car parts were to not work as expected, the mechanic would have to diagnose the entire car to determine what was wrong -- the issue could be anywhere. A symptom might have many causes -- for example, is the car not starting due to a faulty spark plug, battery, fuel pump, or something else? This leads to lots of wasted time trying to identify exactly where the problems are, and what to do about them. And if a problem is found, the consequences can be disastrous -- a change in one area might cause “ripple effects” (changes) in multiple other places. For example, a fuel pump that is too small might lead to an engine redesign, which leads to a redesign of the car frame. In the worst case, you might end up redesigning a huge part of the car, just to accommodate what was initially a small issue!

In case a), the company tests as they go. If any component is bad right out of the box, they’ll know immediately and can fix/replace it. Nothing is integrated into the car until it’s proven working by itself, and then that part is retested again as soon as it’s been integrated into the car. This way any unexpected issues are discovered as early as possible, while they are still small problems that can be easily fixed.

By the time they get around to having the whole car assembled, they should have reasonable confidence that the car will work -- after all, all the parts have been tested in isolation and when initially integrated. It’s still possible that unexpected issues will be found at this point, but that risk is minimized by all the prior testing.

The above analogy holds true for programs as well, though for some reason, new programmers often don’t realize it. You’re much better off writing small functions (or classes), and then compiling and testing them immediately. That way, if you make a mistake, you’ll know it has to be in the small amount of code that you changed since the last time you compiled/tested. That means fewer places to look, and far less time spent debugging.

Testing a small part of your code in isolation to ensure that “unit” of code is correct is called **unit testing**. Each **unit test** is designed to ensure that a particular behavior of the unit is correct.
#### Best practice
Write your program in small, well defined units (functions or classes), compile often, and test your code as you go.

If the program is short and accepts user input, trying a variety of user inputs might be sufficient. But as programs get longer and longer, this becomes less sufficient, and there is more value in testing individual functions or classes before integrating them into the rest of the program.

So how can we test our code in units?
### Informal testing
One way you can test code is to do informal testing as you write the program. After writing a unit of code (a function, a class, or some other discrete “package” of code), you can write some code to test the unit that was just added, and then erase the test once the test passes. As an example, for the following isLowerVowel() function, you might write the following code:
```cpp
#include <iostream>

// We want to test the following function
// For simplicity, we'll ignore that 'y' is sometimes counted as a vowel
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int main()
{
    // So here's our temporary tests to validate it works
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0

    return 0;
}
```

If the results come back as `1` and `0`, then you’re good to go. You know your function works for some basic cases, and you can reasonably infer by looking at the code that it will work for the cases you didn’t test (‘e’, ‘i’, ‘o’, and ‘u’). So you can erase that temporary test code, and continue programming.

### Preserving your tests

Although writing temporary tests is a quick and easy way to test some code, it doesn’t account for the fact that at some point, you may want to test that same code again later. Perhaps you modified a function to add a new capability, and want to make sure you didn’t break anything that was already working. For that reason, it can make more sense to preserve your tests so they can be run again in the future. For example, instead of erasing your temporary test code, you could move the tests into a testVowel() function:

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Not called from anywhere right now
// But here if you want to retest things later
void testVowel()
{
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0
}

int main()
{
    return 0;
}
```
As you create more tests, you can simply add them to the `testVowel()` function.

### Automating your test functions

One problem with the above test function is that it relies on you to manually verify the results when you run it. This requires you to remember what the expected answer was at worst (assuming you didn’t document it), and manually compare the actual results to the expected results.

We can do better by writing a test function that contains both the tests AND the expected answers and compares them so we don’t have to.

```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// returns the number of the test that failed, or 0 if all tests passed
int testVowel()
{
    if (!isLowerVowel('a')) return 1;
    if (isLowerVowel('q')) return 2;

    return 0;
}

int main()
{
    int result { testVowel() };
    if (result != 0)
        std::cout << "testVowel() test " << result << " failed.\n";
    else
        std::cout << "testVowel() tests passed.\n";

    return 0;
}
```

Now, you can call `testVowel()` at any time to re-prove that you haven’t broken anything, and the test routine will do all the work for you, returning either an “all good” signal (return value `0`), or the test number that didn’t pass, so you can investigate why it broke. This is particularly useful when going back and modifying old code, to ensure you haven’t accidentally broken anything!

#### For advanced readers
A better method is to use `assert`, which will cause the program to abort with an error message if any test fails. We don’t have to create and handle test case numbers this way.
```cpp
#include <cassert> // for assert
#include <cstdlib> // for std::abort
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Program will halt on any failed test case
int testVowel()
{
#ifdef NDEBUG
    // If NDEBUG is defined, asserts are compiled out.
    // Since this function requires asserts to not be compiled out, we'll terminate the program if this function is called when NDEBUG is defined.
    std::cerr << "Tests run with NDEBUG defined (asserts compiled out)";
    std::abort();
#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('b'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('y'));
    assert(!isLowerVowel('z'));

    return 0;
}

int main()
{
    testVowel();

    // If we reached here, all tests must have passed
    std::cout << "All tests succeeded\n";

    return 0;
}
```

We cover `assert` in lesson [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/).

### Unit testing frameworks
Because writing functions to exercise other functions is so common and useful, there are entire frameworks (called **unit testing frameworks**) that are designed to help simplify the process of writing, maintaining, and executing unit tests. Since these involve third party software, we won’t cover them here, but you should be aware they exist.

### Integration testing
Once each of your units has been tested in isolation, they can be integrated into your program and retested to make sure they were integrated properly. This is called an **integration test**. Integration testing tends to be more complicated -- for now, running your program a few times and spot checking the behavior of the integrated unit will suffice.

## 9.2 [Code coverage](https://www.learncpp.com/cpp-tutorial/code-coverage/)
In the previous lesson [9.1 -- Introduction to testing your code](https://www.learncpp.com/cpp-tutorial/introduction-to-testing-your-code/), we discussed how to write and preserve simple tests. In this lesson, we’ll talk about what kind of tests are useful to write to ensure your code is correct.
### Code coverage
The term **code coverage** is used to describe how much of the source code of a program is executed while testing. There are many different metrics used for code coverage. We’ll cover a few of the more useful and popular ones in the following sections.

### Statement coverage
The term **statement coverage** refers to the percentage of statements in your code that have been exercised by your testing routines.
Consider the following function:
```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```
Calling this function as `foo(1, 0)` will give you complete statement coverage for this function, as every statement in the function will execute.

For our `isLowerVowel()` function:
```cpp
bool isLowerVowel(char c)
{
    switch (c) // statement 1
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true; // statement 2
    default:
        return false; // statement 3
    }
}
```
This function will require two calls to test all of the statements, as there is no way to reach statement 2 and 3 in the same function call.

While aiming for 100% statement coverage is good, it’s often not enough to ensure correctness.
### Branch coverage

**Branch coverage** refers to the percentage of branches that have been executed, each possible branch counted separately. An `if statement` has two branches -- a branch that executes when the condition is `true`, and a branch that executes when the condition is `false` (even if there is no corresponding `else statement` to execute). A switch statement can have many branches.
```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```

The previous call to foo(1, 0) gave us 100% statement coverage and exercised the use case where `x > y`, but that only gives us 50% branch coverage. We need one more call, to `foo(0, 1)`, to test the use case where the `if statement` does not execute.
```cpp
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}
```

In the isLowerVowel() function, two calls will be needed to give you 100% branch coverage: one (such as `isLowerVowel('a')`) to test the first cases, and another (such as `isLowerVowel('q')`) to test the default case. Multiple cases that feed into the same body don’t need to be tested separately -- if one works, they all should.

Now consider the following function:
```cpp
void compare(int x, int y)
{
	if (x > y)
		std::cout << x << " is greater than " << y << '\n'; // case 1
	else if (x < y)
		std::cout << x << " is less than " << y << '\n'; // case 2
	else
		std::cout << x << " is equal to " << y << '\n'; // case 3
}
```

3 calls are needed to get 100% branch coverage here: `compare(1, 0)` tests the positive use case for the first `if statement`. `compare(0, 1)` tests the negative use case for the first `if statement` and the positive use case for the second `if statement`. `compare(0, 0)` tests the negative use case for the first and second `if statement` and executes the `else statement`. Thus, we can say this function is reliably tested with 3 calls (which is slightly better than 18 quintillion).
#### Best practice
Aim for 100% branch coverage of your code.

### Loop coverage

**Loop coverage** (informally called **the 0, 1, 2 test**) says that if you have a loop in your code, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times. If it works correctly for the 2-iteration case, it should work correctly for all iterations greater than 2. These three tests therefore cover all possibilities (since a loop can’t execute a negative number of times).

Consider:
```cpp
#include <iostream>

void spam(int timesToPrint)
{
    for (int count{ 0 }; count < timesToPrint; ++count)
         std::cout << "Spam! ";
}
```
To test the loop within this function properly, you should call it three times: `spam(0)` to test the zero-iteration case, `spam(1)` to test the one-iteration case, and `spam(2)` to test the two-iteration case. If `spam(2)` works, then `spam(n)` should work, where `n > 2`.

#### Best practice
Use the `0, 1, 2 test` to ensure your loops work correctly with different number of iterations.

### Testing different categories of input

When writing functions that accept parameters, or when accepting user input, consider what happens with different categories of input. In this context, we’re using the term “category” to mean a set of inputs that have similar characteristics.

For example, if I wrote a function to produce the square root of an integer, what values would it make sense to test it with? You’d probably start with some normal value, like `4`. But it would also be a good idea to test with `0`, and a negative number.

Here are some basic guidelines for category testing:

For integers, make sure you’ve considered how your function handles negative values, zero, and positive values. You should also check for overflow if that’s relevant.

For floating point numbers, make sure you’ve considered how your function handles values that have precision issues (values that are slightly larger or smaller than expected). Good `double` type values to test with are `0.1` and `-0.1` (to test numbers that are slightly larger than expected) and `0.7` and `-0.7` (to test numbers that are slightly smaller than expected).

For strings, make sure you’ve considered how your function handles an empty string, an alphanumeric string, strings that have whitespace (leading, trailing, and inner), and strings that are all whitespace.

If your function takes a pointer, don’t forget to test `nullptr` as well (don’t worry if this doesn’t make sense, we haven’t covered it yet).
#### Best practice
Test different categories of input values to make sure your unit handles them properly.

## 9.3 [Common semantic errors in C++](https://www.learncpp.com/cpp-tutorial/common-semantic-errors-in-c/)
In lesson [3.1 -- Syntax and semantic errors](https://www.learncpp.com/cpp-tutorial/syntax-and-semantic-errors/), we covered `syntax errors`, which occur when you write code that is not valid according to the grammar of the C++ language. The compiler will notify you of such errors, so they are trivial to catch, and usually straightforward to fix.

We also covered `semantic errors`, which occur when you write code that does not do what you intended. The compiler generally will not catch semantic errors (though in some cases, smart compilers may be able to generate a warning).

Semantic errors can cause most of the same symptoms of `undefined behavior`, such as causing the program to produce the wrong results, causing erratic behavior, corrupting program data, causing the program to crash -- or they may not have any impact at all.

When writing programs, it is almost inevitable that you will make semantic errors. You will probably notice some of these just by using the program: for example, if you were writing a maze game, and your character was able to walk through walls. Testing your program ([9.1 -- Introduction to testing your code](https://www.learncpp.com/cpp-tutorial/introduction-to-testing-your-code/)) can also help surface semantic errors.

But there’s one other thing that can help -- and that’s knowing which type of semantic errors are most common, so you can spend a little more time ensuring things are right in those cases.

In this lesson, we’ll cover a bunch of the most common types of semantic errors that occur in C++ (most of which have to do with flow control in some way).

### Conditional logic errors

One of the most common types of semantic errors is a conditional logic error. A **conditional logic error** occurs when the programmer incorrectly codes the logic of a conditional statement or loop condition. Here is a simple example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (x >= 5) // oops, we used operator>= instead of operator>
        std::cout << x << " is greater than 5\n";

    return 0;
}
```

Here’s a run of the program that exhibits the conditional logic error:
```
Enter an integer: 5
5 is greater than 5
```
When the user enters `5`, the conditional expression `x >= 5` evaluates to `true`, so the associated statement is executed.

Here’s another example, using a for loop:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    // oops, we used operator> instead of operator<
    for (int count{ 1 }; count > x; ++count)
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

This program is supposed to print all of the numbers between 1 and the number the user entered. But here’s what it actually does:

`Enter an integer: 5`

It didn’t print anything. This happens because on entrance to the for loop, `count > x` is `false`, so the loop never iterates at all.
### Infinite loops

In lesson [8.8 -- Introduction to loops and while statements](https://www.learncpp.com/cpp-tutorial/introduction-to-loops-and-while-statements/), we covered infinite loops, and showed this example:

```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10) // this condition will never be false
    {
        std::cout << count << ' '; // so this line will repeatedly execute
    }

    std::cout << '\n'; // this line will never execute

    return 0; // this line will never execute
}
```

Here’s another example that teachers love asking as a quiz question. What’s wrong with the following code?
```cpp
#include <iostream>

int main()
{
    for (unsigned int count{ 5 }; count >= 0; --count) //uint wrap 
    {
        if (count == 0)
            std::cout << "blastoff! ";
        else
          std::cout << count << ' ';
    }
```
This program is supposed to print `5 4 3 2 1 blastoff!`, which it does, but it doesn’t stop there. In actuality, it prints:
`5 4 3 2 1 blastoff! 4294967295 4294967294 4294967293 4294967292 4294967291 ...`
and then just keeps decrementing. The program will never terminate, because `count >= 0` can never be `false` when `count` is an unsigned integer.
### Off-by-one errors

An **off-by-one** error is an error that occurs when a loop executes one too many or one too few times. Here’s an example that we covered in lesson [8.10 -- For statements](https://www.learncpp.com/cpp-tutorial/for-statements/):

```cpp
#include <iostream>

int main()
{
    for (int count{ 1 }; count < 5; ++count) //programer want until 5 included toprint => not happening
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

The programmer intended for this code to print `1 2 3 4 5`. However, the wrong relational operator was used (`<` instead of `<=`), so the loop executes one fewer times than intended, printing `1 2 3 4`. 

### Incorrect operator precedence

From lesson [6.8 -- Logical operators](https://www.learncpp.com/cpp-tutorial/logical-operators/), the following program makes an operator precedence mistake:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y) // oops: operator precedence issue <=> ((!x)>y)
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```
Because `logical NOT` has higher precedence than `operator>`, the conditional evaluates as if it was written `(!x) > y`, which isn’t what the programmer intended.

As a result, this program prints:
`5 is greater than 7

This can also happen when mixing Logical OR and Logical AND in the same expression (Logical AND takes precedence over Logical OR). Use explicit parenthesization to avoid these kinds of errors.
### Precision issues with floating point types

The following floating point variable doesn’t have enough precision to store the entire number:
```cpp
#include <iostream>

int main()
{
    float f{ 0.123456789f };
    std::cout << f << '\n';

    return 0;
}
```

Because of this lack of precision, the number is rounded slightly:
`0.123457`

In lesson [6.7 -- Relational operators and floating point comparisons](https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/), we talked about how using `operator==` and `operator!=` can be problematic with floating point numbers due to small rounding errors (as well as what to do about it). Here’s an example:
```cpp
#include <iostream>

int main()
{
    double d{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should sum to 1.0

    if (d == 1.0)
        std::cout << "equal\n";
    else
        std::cout << "not equal\n";

    return 0;
}
```
This program prints: `not equal`

The more arithmetic you do with a floating point number, the more it will accumulate small rounding errors.
### Integer division

In the following example, we mean to do a floating point division, but because both operands are integers, we end up doing an integer division instead:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 3 };

    std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // integer division

    return 0;
}
```

This prints:
`5 divided by 3 is: 1`

In lesson [6.2 -- Arithmetic operators](https://www.learncpp.com/cpp-tutorial/arithmetic-operators/), we showed that we can use static_cast to convert one of the integral operands to a floating point value in order to do floating point division.

### Accidental null statements
In lesson [8.3 -- Common if statement problems](https://www.learncpp.com/cpp-tutorial/common-if-statement-problems/), we covered `null statements`, which are statements that do nothing.
In the below program, we only want to blow up the world if we have the user’s permission:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y');     // accidental null statement here
        blowUpWorld(); // so this will always execute since it's not part of the if-statement

    return 0;
}
```
However, because of an accidental `null statement`, the function call to `blowUpWorld()` is always executed, so we blow it up regardless:
```
Should we blow up the world again? (y/n): n
Kaboom!
```
### Not using a compound statement when one is required
Another variant of the above program that always blows up the world:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y')
        std::cout << "Okay, here we go...\n";
        blowUpWorld(); // Will always execute.  Should be inside compound statement.

    return 0;
}
```
This program prints:
```
Should we blow up the world again? (y/n): n
Kaboom!
```

A `dangling else` (covered in lesson [8.3 -- Common if statement problems](https://www.learncpp.com/cpp-tutorial/common-if-statement-problems/)) also falls into this category.
### Using assignment instead of equality inside a conditional
Because the assignment operator (`=`) and equality operator (`==`) are similar, we may intend to use equality but accidentally use assignment instead:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c = 'y') // uses assignment operator instead of equality operator
        blowUpWorld();

    return 0;
}
```
This program prints:
```
Should we blow up the world again? (y/n): n
Kaboom!
```
The assignment operator returns its left operand. `c = 'y'` executes first, which assigns `y` to `c` and returns `c`. Then `if (c)` is evaluated. Since `c` is now non-zero, it is implicitly converted to `bool` value `true`, and the statement associated with the if-statement executes.

Because assignment inside a conditional is almost never intended, modern compilers will often warn when they encounter this. However, if you aren’t in the habit of resolving all your warnings, such warnings can easily get lost.
### Forgetting to use the function call operator when calling a function
```cpp
#include <iostream>

int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
```
While you might expect this program to print `5`, it will most likely print `1` (on some compilers, it will print a memory address in hex).

Instead of using `getValue()` (which would call the function and produce an `int` return value), we’ve used `getValue` without the function call operator. In many cases, this will result in a value that gets converted to `bool` value `true`).

In our example above, it is this `bool` value `true` that is output, which prints `1`.
#### For advanced readers
Using a function’s name without calling it generally yields a function pointer holding the address of the function. Such a function pointer will implicitly convert to a `bool` value. And since this pointer should never have address `0`, that `bool` value will always be `true`.

We cover function pointers in lesson [20.1 -- Function Pointers](https://www.learncpp.com/cpp-tutorial/function-pointers/).


### What else?
The above represents a good sample of the most common type of semantic errors new C++ programmers tend to make, but there are plenty more. Readers, if you have any additional ones that you think are common pitfalls, leave a note in the comments.

## 9.4 [Detecting and handling errors](https://www.learncpp.com/cpp-tutorial/detecting-and-handling-errors/)
In lesson [9.3 -- Common semantic errors in C++](https://www.learncpp.com/cpp-tutorial/common-semantic-errors-in-c/), we covered many types of common C++ semantic errors that new C++ programmers run into with the language. If an error is the result of a misused language feature or logic error, the error can simply be corrected.

But most errors in a program don’t occur as the result of inadvertently misusing language features -- rather, most errors occur due to faulty assumptions made by the programmer and/or a lack of proper error detection/handling.

For example, in a function designed to look up a grade for a student, you might have assumed:
- The student being looked up will exist.
- All student names will be unique.
- The class uses letter grading (instead of pass/fail).

What if any of these assumptions aren’t true? If the programmer didn’t anticipate these cases, the program will likely malfunction or crash when such cases arise (usually at some point in the future, well after the function has been written).

There are three key places where assumption errors typically occur:
- When a function returns, the programmer may have assumed the called function was successful when it was not.
- When a program receives input (either from the user, or a file), the programmer may have assumed the input was in the correct format and semantically valid when it was not.
- When a function has been called, the programmer may have assumed the arguments would be semantically valid when they were not.

Many new programmers write code and then only test the **happy path**: only the cases where there are no errors. But you should also be planning for and testing your **sad paths**, where things can and will go wrong. In lesson [3.10 -- Finding issues before they become problems](https://www.learncpp.com/cpp-tutorial/finding-issues-before-they-become-problems/), we defined **defensive programming** as the practice of trying to anticipate all of the ways software can be misused, either by end-users, or by developers (either the programmer themselves, or others). Once you’ve anticipated (or discovered) some misuse, the next thing to do is handle it.

In this lesson, we’ll talk about error handling strategies (what to do when things go wrong) inside a function. In the subsequent lessons, we’ll talk about validating user input, and then introduce a useful tool to help document and validate assumptions.

### Handling errors in functions
Functions may fail for any number of reasons -- the caller may have passed in an argument with an invalid value, or something may fail within the body of the function. For example, a function that opens a file for reading might fail if the file cannot be found.

When this happens, you have quite a few options at your disposal. There is no best way to handle an error -- it really depends on the nature of the problem and whether the problem can be fixed or not.

There are 4 general strategies that can be used:
- Handle the error within the function
- Pass the error back to the caller to deal with
- Halt the program
- Throw an exception

### Handling the error within the function

If possible, the best strategy is to recover from the error in the same function in which the error occurred, so that the error can be contained and corrected without impacting any code outside the function. There are two options here: retry until successful, or cancel the operation being executed.

If the error has occurred due to something outside of the program’s control, the program can retry until success is achieved. For example, if the program requires an internet connection, and the user has lost their connection, the program may be able to display a warning and then use a loop to periodically recheck for internet connectivity. Alternatively, if the user has entered invalid input, the program can ask the user to try again, and loop until the user is successful at entering valid input. We’ll show examples of handling invalid input and using loops to retry in the next lesson ([9.5 -- std::cin and handling invalid input](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/)).

An alternate strategy is just to ignore the error and/or cancel the operation. For example:
```cpp
// Silent failure if y=0
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
}
```
In the above example, if the user passed in an invalid value for `y`, we just ignore the request to print the result of the division operation. The primary challenge with doing this is that the caller or user have no way to identify that something went wrong. In such case, printing an error message can be helpful:
```cpp
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
    else
        std::cout << "Error: Could not divide by zero\n";
}
```
However, if the calling function is expecting the called function to produce a return value or some useful side-effect, then just ignoring the error may not be an option.
### Passing errors back to the caller

In many cases, the error can’t reasonably be handled in the function that detects the error. For example, consider the following function:
```cpp
int doIntDivision(int x, int y)
{
    return x / y;
}
```

If `y` is `0`, what should we do? We can’t just skip the program logic, because the function needs to return some value. We shouldn’t ask the user to enter a new value for `y` because this is a calculation function, and introducing input routines into it may or may not be appropriate for the program calling this function.

In such cases, the best option can be to pass the error back to the caller in hopes that the caller will be able to deal with it.

How might we do that?
If the function has a `void` return type, it can be changed to return a `bool` that indicates success or failure. For example, instead of:
```cpp
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
    else
        std::cout << "Error: Could not divide by zero\n";
}
```

We can do this:
```cpp
bool printIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: could not divide by zero\n";
        return false;
    }

    std::cout << x / y;

    return true;
}
```
That way, the caller can check the return value to see if the function failed for some reason.

If the function returns a normal value, things are a little more complicated. In some cases, the full range of return values isn’t used. In such cases, we can use a return value that wouldn’t otherwise be possible to occur normally to indicate an error. For example, consider the following function:
```cpp
// The reciprocal of x is 1/x
double reciprocal(double x)
{
    return 1.0 / x;
}
```
The reciprocal of some number `x` is defined as `1/x`, and a number multiplied by its reciprocal equals 1.

However, what happens if the user calls this function as `reciprocal(0.0)`? We get a `divide by zero` error and a program crash, so clearly we should protect against this case. But this function must return a double value, so what value should we return? It turns out that this function will never produce `0.0` as a legitimate result, so we can return `0.0` to indicate an error case.
```cpp
// The reciprocal of x is 1/x, returns 0.0 if x=0
constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace

double reciprocal(double x)
{
    if (x == 0.0)
       return error_no_reciprocal;

    return 1.0 / x;
}
```

A **sentinel value** is a value that has some special meaning in the context of a function or algorithm. In our `reciprocal()` function above, `0.0` is a sentinel value indicating that the function failed. The caller can test the return value to see if it matches the sentinel value -- if so, then the caller knows the function failed. While functions often return the sentinel value directly, returning a constant that describes the sentinel value can add additional readability.

However, if the full range of return values can be produced by the function, then using a sentinel value to indicate an error is problematic (because the caller would not be able to tell whether the return value is a valid value or an error value).
#### Related content
In such a case, returning a `std::optional` (or `std::expected`) would be a better choice. We cover `std::optional` in lesson [12.15 -- std::optional](https://www.learncpp.com/cpp-tutorial/stdoptional/).
### Fatal errors
If the error is so bad that the program can not continue to operate properly, this is called a **non-recoverable** error (also called a **fatal error**). In such cases, the best thing to do is terminate the program. If your code is in `main()` or a function called directly from `main()`, the best thing to do is let `main()` return a non-zero status code. However, if you’re deep in some nested subfunction, it may not be convenient or possible to propagate the error all the way back to `main()`. In such a case, a `halt statement` (such as `std::exit()`) can be used.

For example:
```cpp
double doIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);
    }
    return x / y;
}
```
### Exceptions
Because returning an error from a function back to the caller is complicated (and the many different ways to do so leads to inconsistency, and inconsistency leads to mistakes), C++ offers an entirely separate way to pass errors back to the caller: `exceptions`.

The basic idea is that when an error occurs, an exception is “thrown”. If the current function does not “catch” the error, the caller of the function has a chance to catch the error. If the caller does not catch the error, the caller’s caller has a chance to catch the error. The error progressively moves up the call stack until it is either caught and handled (at which point execution continues normally), or until main() fails to handle the error (at which point the program is terminated with an exception error).

We cover exception handling in [chapter 27](https://www.learncpp.com#Chapter27) of this tutorial series.

### When to use `std::cout` vs `std::cerr` vs logging
In lesson [3.4 -- Basic debugging tactics](https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/), we introduced `std::cerr`. You may be wondering when (or whether) you should be using `std::cerr` vs `std::cout` vs logging to a text file.

By default, both `std::cout` and `std::cerr` print text to the console. However, modern OSes provide a way to redirect output streams to files, so that the output can be captured for review or automated processing later.

For this discussion, it is useful to differentiate two types of applications:
- **Interactive applications** are those that the user will interact with after running. Most standalone applications, like games and music apps, fall into this category.
- **Non-interactive applications** are applications that do not require user interaction to operate. The output of these programs may be used as input for another application

Within non-interactive applications, there are two types:
- **Tools** are non-interactive applications that are typically launched in order to produce some immediate result, and then terminate after producing such a result. An example of this is Unix’s grep command, which is a utility that searches text for lines that match some pattern.
- **Services** are non-interactive applications that typically run silently in the background to perform some ongoing function. An example of this would be a virus scanner.

Here’s some rules of thumb:
- Use `std::cout` for all conventional, user-facing text.
- For an interactive program, use `std::cout` for normal user-facing error messages (e.g. “Your input was invalid”). Use `std::cerr` or a logfile for status and diagnostic information that may be helpful for diagnosing issues but probably isn’t interesting for normal users. This can include technical warnings and errors (e.g. bad input to function x), status updates (e.g. successfully opened file x, failed to connect to internet service x), percentage completion of long tasks (e.g. encoding 50% complete), etc…
- For a non-interactive program (tool or service), use `std::cerr` for error output only (e.g. could not open file x). This allows errors to be displayed or parsed separately from normal output.
- For any application type that is transactional in nature (e.g. one that processes specific events, such as an interactive web browser or non-interactive web server), use a logfile to produce a transactional log of events that can be reviewed later. This can include outputting to the logfile which file is being processed, updates on the percentage complete, timestamps of when it started certain stages of computing, warning and error messages, etc…

## 9.5 [std::cin and handling invalid input](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/)
Most programs that have a user interface of some kind need to handle user input. In the programs that you have been writing, you have been using std::cin to ask the user to enter text input. Because text input is so free-form (the user can enter anything), it’s very easy for the user to enter input that is not expected.

As you write programs, you should always consider how users will (unintentionally or otherwise) misuse your programs. A well-written program will anticipate how users will misuse it, and either handle those cases gracefully or prevent them from happening in the first place (if possible). A program that handles error cases well is said to be **robust**.

In this lesson, we’ll take a look specifically at ways the user can enter invalid text input via std::cin, and show you some different ways to handle those cases.

Before we discuss how `std::cin` and `operator>>` can fail, let’s recap how they work. We discussed this material in lesson [1.5 -- Introduction to iostream: cout, cin, and endl](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/#extraction).

Here’s a simplified view of how `operator>>` works for input:
1. First, leading whitespace (spaces, tabs, and newlines at the front of the buffer) is discarded from the input buffer. This will discard any unextracted newline character remaining from a prior line of input.
2. If the input buffer is now empty, `operator>>` will wait for the user to enter more data. Leading whitespace is again discarded.
3. `operator>>` then extracts as many consecutive characters as it can, until it encounters either a newline character (representing the end of the line of input) or a character that is not valid for the variable being extracted to.

The result of the extraction is as follows:
- If any characters were extracted in step 3 above, extraction is a success. The extracted characters are converted into a value that is then assigned to the variable.
- If no characters could be extracted in step 3 above, extraction has failed. The object being extracted to is assigned the value `0` (as of C++11), and any future extractions will immediately fail (until `std::cin` is cleared).
### Validating input
The process of checking whether user input conforms to what the program is expecting is called **input validation**.
There are three basic ways to do input validation:
Inline (as the user types):
1. Prevent the user from typing invalid input in the first place.

Post-entry (after the user types):
2. Let the user enter whatever they want into a string, then validate whether the string is correct, and if so, convert the string to the final variable format.
3. Let the user enter whatever they want, let `std::cin` and operator>> try to extract it, and handle the error cases.

Some graphical user interfaces and advanced text interfaces will let you validate input as the user enters it (character by character). Generally speaking, the programmer provides a validation function that accepts the input the user has entered so far, and returns true if the input is valid, and false otherwise. This function is called every time the user presses a key. If the validation function returns true, the key the user just pressed is accepted. If the validation function returns false, the character the user just input is discarded (and not shown on the screen). Using this method, you can ensure that any input the user enters is guaranteed to be valid, because any invalid keystrokes are discovered and discarded immediately. Unfortunately, `std::cin` does not support this style of validation.

Since strings do not have any restrictions on what characters can be entered, extraction is guaranteed to succeed (though remember that `std::cin` stops extracting at the first non-leading whitespace character). Once a string is entered, the program can then parse the string to see if it is valid or not. However, parsing strings and converting string input to other types (e.g. numbers) can be challenging, so this is only done in rare cases.

Most often, we let `std::cin` and the extraction operator do the hard work. Under this method, we let the user enter whatever they want, have `std::cin` and operator>> try to extract it, and deal with the fallout if it fails. This is the easiest method, and the one we’ll talk more about below.

### A sample program

Consider the following calculator program that has no error handling:
```cpp
#include <iostream>

double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        std::cout << x / y << '\n';
        return;
    }
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    printResult(x, operation, y);

    return 0;
}
```

This simple program asks the user to enter two numbers and a mathematical operator.
```
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: *
Enter a decimal number: 7
5 * 7 is 35
```

Now, consider where invalid user input might break this program. 

First, we ask the user to enter some numbers. What if they enter something other than a number (e.g. ‘q’)? In this case, extraction will fail.

Second, we ask the user to enter one of four possible symbols. What if they enter a character other than one of the symbols we’re expecting? We’ll be able to extract the input, but we don’t currently handle what happens afterward.

Third, what if we ask the user to enter a symbol and they enter a string like `"*q hello"`. Although we can extract the `'*'` character we need, there’s additional input left in the buffer that could cause problems down the road.

### Types of invalid text input

We can generally separate input text errors into four types:
1. Input extraction succeeds but the input is meaningless to the program (e.g. entering ‘k’ as your mathematical operator).
2. Input extraction succeeds but the user enters additional input (e.g. entering ‘*q hello’ as your mathematical operator).
3. Input extraction fails (e.g. trying to enter ‘q’ into a numeric input).
4. Input extraction succeeds but the user overflows a numeric value.

Thus, to make our programs robust, whenever we ask the user for input, we ideally should determine whether each of the above can possibly occur, and if so, write code to handle those cases.

Let’s dig into each of these cases, and how to handle them using `std::cin`. 

### Error case 1: Extraction succeeds but input is meaningless
This is the simplest case. Consider the following execution of the above program:
```
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: k
Enter a decimal number: 7
```
In this case, we asked the user to enter one of four symbols, but they entered ‘k’ instead. ‘k’ is a valid character, so `std::cin` happily extracts it to variable `op`, and this gets returned to `main`. But our program wasn’t expecting this to happen, so it doesn’t properly deal with this case. As a result, it outputs:

`5 k 7 is`

The solution here is simple: do input validation. This usually consists of 3 steps:
1. Check whether the user’s input was what you were expecting.
2. If so, return the value to the caller.
3. If not, tell the user something went wrong and have them try again.

Here’s an updated getOperator() function that does input validation.
```cpp
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } // and try again
}
```
As you can see, we’re using a while loop to continuously loop until the user provides valid input. If they don’t, we ask them to try again until they either give us valid input, shutdown the program, or destroy their computer.

### Error case 2: Extraction succeeds but with extraneous input
Consider the following execution of the above program:
`Enter a decimal number: 5*7`

What do you think happens next?
```
Enter a decimal number: 5*7
Enter one of the following: +, -, *, or /: Enter a decimal number: 5 * 7 is 35
```

The program prints the right answer, but the formatting is all messed up. Let’s take a closer look at why.

When the user enters `5*7` as input, that input goes into the buffer. Then `operator>>` extracts the 5 to variable x, leaving `*7\n` in the buffer. Next, the program prints `“Enter one of the following: +, -, *, or /:”`. However, when the extraction operator was called, it sees `*7\n` waiting in the buffer to be extracted, so it uses that instead of asking the user for more input. Consequently, it extracts the ‘*’ character, leaving `7\n` in the buffer.

After asking the user to enter another decimal number, the `7` in the buffer gets extracted without asking the user. Since the user never had an opportunity to enter additional data and hit enter (causing a newline), the output prompts all run together on the same line.

Although the above program works, the execution is messy. It would be better if any extraneous characters entered were simply ignored. Fortunately, it’s easy to ignore characters:
```cpp
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
```
This call would remove up to 100 characters, but if the user entered more than 100 characters we’ll get messy output again. To ignore all characters up to the next ‘\n’, we can pass `std::numeric_limits<std::streamsize>::max()` to `>std::cin.ignore()`. `std::numeric_limits<std::streamsize>::max()` returns the largest value that can be stored in a variable of type `std::streamsize`. Passing this value to `std::cin.ignore()` causes it to disable the count check.

To ignore everything up to and including the next ‘\n’ character, we call
```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

Because this line is quite long for what it does, it’s handy to wrap it in a function which can be called in place of `std::cin.ignore()`.
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```
Since the last character the user entered is typically a ‘\n’, we can tell `std::cin` to ignore buffered characters until it finds a newline character (which is removed as well).

Let’s update our getDouble() function to ignore any extraneous input:
```cpp
double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;

    ignoreLine();
    return x;
}
```

Now our program will work as expected, even if we enter `5*7` for the first input -- the 5 will be extracted, and the rest of the characters will be removed from the input buffer. Since the input buffer is now empty, the user will be properly asked for input the next time an extraction operation is performed!
#### Tip

In certain cases, it may be better to treat extraneous input as a failure case (rather than just ignoring it). We can then ask the user to re-enter their input.

Here’s a variation of `getDouble()` that asks the user to re-enter their input if there is any extraneous input entered:
```cpp
// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        // NOTE: YOU SHOULD CHECK FOR A FAILED EXTRACTION HERE (see section below)

        // If there is extraneous input, treat as failure case
        if (hasUnextractedInput())
        {
            ignoreLine(); // remove extraneous input
            continue;
        }

        return x;
    }
}
```
The above snippet makes use of two functions we haven’t seen before:
- The `std::cin.eof()` function returns `true` if the last input operation (in this case the extraction to `x`) reached the end of the input stream.
- The `std::cin.peek()` function allows us to peek at the next character in the input stream without extracting it.

Here’s how this function works. After the user’s input has been extracted to `x`, there may or may not be additional (unextracted) characters left in `std::cin`.

First, we call `std::cin.eof()` to see if the extraction to `x` reached the end of the input stream. If so, then we know all characters were extracted, which is a success case.

Otherwise, there must be additional characters still inside `std::cin` waiting to be extracted. In that case, we call `std::cin.peek()` to peek at the next character waiting to be extracted without actually extracting it. If that next character is a `'\n'`, that means we’ve already extracted all of the characters on this line of input to `x`. This is also a success case.

However, if the next character is something other than `'\n'`, then the user must have entered extraneous input that wasn’t extracted to `x`. That’s our failure case. We clear out all of that extraneous input, and `continue` back to the top of the loop to try again.

If you’re having trouble deciphering how the boolean expression in `hasUnextractedInput()` evaluates, that’s not surprising -- boolean expressions with negations can be difficult to understand. In such cases, using de Morgan’s law can help. An equivalent statement is `return !(std::cin.eof() || std::cin.peek() == '\n');`. This makes it clearer that we are testing for EOF or a newline. If either are true, then we’ve extracted all the input. We then apply `operator!` to tell us whether we haven’t extracted all the input, meaning there is still unextracted input.

### Error case 3: Extraction fails
Extraction fails when no input can be extracted to the specified variable.

Now consider the following execution of our updated calculator program:

`Enter a decimal number: a`

You shouldn’t be surprised that the program doesn’t perform as expected, but how it fails is interesting:
```
Enter a decimal number: a
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
```
and that last line keeps printing until the program is closed.

This looks pretty similar to the extraneous input case, but it’s a little different. Let’s take a closer look.

When the user enters ‘a’, that character is placed in the buffer. Then operator>> tries to extract ‘a’ to variable x, which is of type double. Since ‘a’ can’t be converted to a double, `operator>>` can’t do the extraction. Two things happen at this point: ‘a’ is left in the buffer, and std::cin goes into “failure mode”.

Once in “failure mode”, future requests for input extraction will silently fail. Thus in our calculator program, the output prompts still print, but any requests for further extraction are ignored. This means that instead waiting for us to enter an operation, the input prompt is skipped, and we get stuck in an infinite loop because there is no way to reach one of the valid cases.

In order to get `std::cin` working properly again, we typically need to do three things:
- Detect that a prior extraction has failed.
- Put `std::cin` back in normal operation mode.
- Remove the input that caused the failure (so the next extraction request doesn’t fail in an identical manner).

Here’s what that looks like:
```cpp
if (std::cin.fail()) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

Because `std::cin` has a Boolean conversion indicating whether the last input succeeded, it’s more idiomatic to write the above as following:
```cpp
if (!std::cin) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```
#### Key insight
Once an extraction has failed, future requests for input extraction (including calls to `ignore()`) will silently fail until the `clear()` function is called. Thus, after detecting a failed extraction, calling `clear()` is usually the first thing you should do.

Let’s integrate that into our getDouble() function:
```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        // Our extraction succeeded
        ignoreLine(); // Ignore any additional input on this line
        return x;     // Return the value we extracted
    }
}
```

For fundamental types, a failed extraction due to invalid input will cause the variable to be assigned the value `0` (or whatever value `0` converts to in the variable’s type).

It is fine to call `clear()` even when extraction hasn’t failed -- it won’t do anything. In cases where we are going to call `ignoreLine()` regardless of whether we succeeded or failed, we can essentially combine the two cases:
```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        bool success { std::cin }; // Remember whether we had a successful extraction
        std::cin.clear();          // Put us back in 'normal' operation mode (in case we failed)
        ignoreLine();              // Ignore any additional input on this line (regardless)

        if (success)               // If we actually extracted a value
            return x;              // Return it (otherwise, we go back to top of loop)
    }
}
```

### Checking for EOF
There’s another case that we need to address.

An end-of-file (EOF) is a special error state that means “No more data available”. This is normally generated **after** an input operation fails due to no data being available. For example, if you were reading the contents of a file on disk, and then try to read in more data after you’ve already reached the end of the file, an EOF will be generated to tell you that no more data is available. In the case of file input, this is no problem -- we can just close the file and move on.

Now consider `std::cin`. If we try to extract input from `std::cin` and there is none, by design it won’t generate an EOF -- it will just wait for the user to enter more input. However, `std::cin` can generate an EOF in certain cases -- most commonly when the user enters a special key combination for their OS. Both Unix (via ctrl-D) and Windows (via ctrl-Z + ENTER) support entering an “EOF character” from the keyboard.

#### Key insight
In C++, EOF is an error state, not a character. Different OSes have special character combinations that are treated as a “user-entered EOF request”. These are sometimes called “EOF characters”.

When extracting data to `std::cin` and the user enters an EOF character, the behavior is OS-specific. Here’s what typically happens
- If the EOF is not the first character of input: All input prior to the EOF will be flushed, and the EOF character is ignored. On Windows, any characters entered after the EOF are ignored, except for the newline.
- If the EOF is the first character entered: The EOF error will be set. The input stream may (or may not) be disconnected.

Although `std::cin.clear()` will clear an EOF error, if the input stream is disconnected, the next input request will generate another EOF error. This is problematic when our input is inside a `while(true)` loop, as we will get stuck in an infinite loop of EOF errors.

Since the intent of an keyboard-entered `EOF` character is to terminate the input stream, the best thing to do is detect the EOF (via `std::cin.eof()`) and then terminate the program.

Because clearing a failed input stream is something we’re likely to be checking for a lot, this is a good candidate for a reusable function:
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```

### Error case 4: Extraction succeeds but the user overflows a numeric value
Consider the following simple example:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;

    std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
    std::cout << "Enter another number between -32768 and 32767: ";
    std::cin >> y;

    std::cout << "The sum is: " << x + y << '\n';
    return 0;
}
```
What happens if the user enters a number that is too large (e.g. 40000)?

```
Enter a number between -32768 and 32767: 40000
Enter another number between -32768 and 32767: The sum is: 32767
```

In the above case, `std::cin` goes immediately into “failure mode”, but also assigns the closest in-range value to the variable. When the entered value is larger than the largest possible value for the type, the closest in-range value is the largest possible value for the type. Consequently, `x` is left with the assigned value of `32767`. Additional inputs are skipped, leaving `y` with the initialized value of `0`. We can handle this kind of error in the same way as a failed extraction.

### Putting it all together
Putting it all together

Here’s our example calculator, updated with a few additional bits of error checking:

```cpp
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
```

### Conclusion

As you write your programs, consider how users will misuse your program, especially around text input. For each point of text input, consider:
- Could extraction fail?
- Could the user enter more input than expected?
- Could the user enter meaningless input?
- Could the user overflow an input?

You can use if statements and boolean logic to test whether input is expected and meaningful.

The following code will clear any extraneous input:
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

The following code will test for and fix failed extractions or overflow (and remove extraneous input):
```cpp
// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```

We can test to see if there is an unextracted input (other than a newline) as follows:
```cpp
// returns true if std::cin has unextracted input on the current line, false otherwise
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}
```

Finally, use loops to ask the user to re-enter input if the original input was invalid.

#### Author’s note
Input validation is important and useful, but it also tends to make examples more complicated and harder to follow. Accordingly, in future lessons, we will generally not do any kind of input validation unless it’s relevant to something we’re trying to teach.

## 9.6 [Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/)
In a function that takes parameters, the caller may be able to pass in arguments that are syntactically valid but semantically meaningless. For example, in the previous lesson ([9.4 -- Detecting and handling errors](https://www.learncpp.com/cpp-tutorial/detecting-and-handling-errors/)), we showed the following sample function:

```cpp
void printDivision(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cerr << "Error: Could not divide by zero\n";
}
```

This function does an explicit check to see if `y` is `0`, since dividing by zero is a semantic error and will cause the program to crash if executed.

In the prior lesson, we discussed a couple of ways to deal with such problems, including halting the program, or skipping the offending statements.

Both of those options are problematic though. If a program skips statements due to an error, then it is essentially failing silently. Especially while we are writing and debugging programs, silent failures are bad, because they obscure real problems. Even if we print an error message, that error message may be lost among the other program output, and it may be non-obvious where the error message is being generated or how the conditions that triggered the error message occurred. Some functions may be called tens or hundreds of times, and if only one of those cases is generating a problem, it can be hard to know which one.

If the program terminates (via `std::exit`) then we will have lost our call stack and any debugging information that might help us isolate the problem. `std::abort` is a better option for such cases, as typically the developer will be given the option to start debugging at the point where the program aborted.

### Preconditions, invariants, and postconditions

In programming, a **precondition** is any condition that must be true prior to the execution of some section of code (typically the body of a function). In the prior example, our check that `y != 0` is a precondition that ensures `y` has a non-zero value before dividing by `y`.

Preconditions for a function are best placed at the top of a function, using an early return to return back to the caller if the precondition isn’t met. For example:

```cpp
void printDivision(int x, int y)
{
    if (y == 0) // handle
    {
        std::cerr << "Error: Could not divide by zero\n";
        return; // bounce the user back to the caller
    }

    // We now know that y != 0
    std::cout << static_cast<double>(x) / y;
}
```

#### Optional reading
This is sometimes known as the “bouncer pattern”, as you are bounced out of the function immediately when an error is detected.

The bouncer pattern has two major benefits:
1. All your test cases are up-front, and the test case and code handling the error are together.
2. You end up with less nesting.

Here’s what the non-bouncer version of this looks like:
```cpp
void printDivision(int x, int y)
{
    if (y != 0)
    {
        std::cout << static_cast<double>(x) / y;
    }
    else
    {
        std::cerr << "Error: Could not divide by zero\n";
        return; // bounce the user back to the caller
    }
}
```

This version is strictly worse, as the test case and code handling the error are more separated, and there is more nesting.

An **invariant** is a condition that must be true while some section of code is executing. This is often used with loops, where the loop body will only execute so long as the invariant is true.
#### For advanced readers
We talk about a common type of invariant called a “class invariant” in lesson [14.2 -- Introduction to classes](https://www.learncpp.com/cpp-tutorial/introduction-to-classes/).

Similarly, a **postcondition** is something that must be true after the execution of some section of code. Our function doesn’t have any postconditions.

### Assertions
Using a conditional statement to detect an invalid parameter (or to validate some other kind of assumption), along with printing an error message and terminating the program, is such a common method of detecting problems that C++ provides a shortcut method for doing this.

An **assertion** is an expression that will be true unless there is a bug in the program. If the expression evaluates to `true`, the assertion statement does nothing. If the conditional expression evaluates to `false`, an error message is displayed and the program is terminated (via `std::abort`). This error message typically contains the expression that failed as text, along with the name of the code file and the line number of the assertion. This makes it very easy to tell not only what the problem was, but where in the code the problem occurred. This can help with debugging efforts immensely.

#### Key insight
Asserts are used to detect errors while developing and debugging.

When an assertion evaluates to false, your program is immediately stopped. This gives you an opportunity to use debugging tools to examine the state of your program and determine why the assertion failed. Working backwards, you can then find and fix the issue quickly.

Without an assertion to detect an error and fail, such an error would likely cause your program to malfunction later. In such cases, it can be very difficult to determine where things are going wrong, or what the root cause of the issue actually is.

In C++, runtime assertions are implemented via the **assert** preprocessor macro, which lives in the `<cassert>` header.
```cpp
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

  return 0;
}
```
When the program calls `calculateTimeUntilObjectHitsGround(100.0, -9.8)`, `assert(gravity > 0.0)` will evaluate to `false`, which will trigger the assert. That will print a message similar to this:
`dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.`

The actual message varies depending on which compiler you use.

Although asserts are most often used to validate function parameters, they can be used anywhere you would like to validate that something is true.

Although we told you previously to avoid preprocessor macros, asserts are one of the few preprocessor macros that are considered acceptable to use. We encourage you to use assert statements liberally throughout your code.
#### Key insight
Asserts are better than comments because they have both document and enforce a condition. Comments can become stale when the code changes and the comment isn’t updated. An assert that has become out of date is a code correctness issue, so developers are less likely to let them languish.

### Making your assert statements more descriptive

Sometimes assert expressions aren’t very descriptive. Consider the following statement:
```cpp
assert(found);
```

If this assert is triggered, the assert will say:
`Assertion failed: found, file C:\\VCProjects\\Test.cpp, line 34`

What does this even mean? Clearly `found` was `false` (since the assert triggered), but what wasn’t found? You’d have to go look at the code to determine that.

Fortunately, there’s a little trick you can use to make your assert statements more descriptive. Simply add a string literal joined by a logical AND:
```cpp
assert(found && "Car could not be found in database");
```
Here’s why this works: A string literal always evaluates to Boolean `true`. So if `found` is `false`, `false && true` is `false`. If `found` is `true`, `true && true` is `true`. Thus, logical AND-ing a string literal doesn’t impact the evaluation of the assert.

However, when the assert triggers, the string literal will be included in the assert message:

`Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34`

That gives you some additional context as to what went wrong.

### Using assertions for unimplemented features
Assertions are also sometimes used to document cases that were not implemented because they were not needed at the time the programmer wrote the code:
```cpp
assert(moved && "Need to handle case where student was just moved to another classroom");
```
That way, if a developer encounters a situation where this case is needed, the code will fail with a useful error message, and the programmer can then determine how to implement that case.

### NDEBUG

The `assert` macro comes with a small performance cost that is incurred each time the assert condition is checked. Furthermore, asserts should (ideally) never be encountered in production code (because your code should already be thoroughly tested). Consequently, most developers prefer that asserts are only active in debug builds. C++ comes with a built-in way to turn off asserts in production code: if the preprocessor macro `NDEBUG` is defined, the assert macro gets disabled.

Most IDEs set `NDEBUG` by default as part of the project settings for release configurations. For example, in Visual Studio, the following preprocessor definitions are set at the project level: `WIN32;NDEBUG;_CONSOLE`. If you’re using Visual Studio and want your asserts to trigger in release builds, you’ll need to remove `NDEBUG` from this setting.

If you’re using an IDE or build system that doesn’t automatically define `NDEBUG` in release configuration, you will need to add it in the project or compilation settings manually.

#### Tip
For testing purposes, you can enable or disable asserts within a given translation unit. To do so, place one of the following on its own line **before** any `#includes` :  `#define NDEBUG` (to disable asserts) or `#undef NDEBUG` (to enable asserts). Make sure that you do not end the line in a semicolon.
e.g.
```cpp
#define NDEBUG // disable asserts (must be placed before any #includes) #undef NDEBUG (to enable asserts)
#include <cassert>
#include <iostream>

int main()
{
    assert(false); // won't trigger since asserts have been disabled in this translation unit
    std::cout << "Hello, world!\n";

    return 0;
}
```
### static_assert[](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/#static_assert)
C++ also has another type of assert called `static_assert`. A **static_assert** is an assertion that is checked at compile-time rather than at runtime, with a failing `static_assert` causing a compile error. Unlike assert, which is declared in the `<cassert>` header, static_assert is a keyword, so no header needs to be included to use it.

A `static_assert` takes the following form:

static_assert(condition, diagnostic_message)

If the condition is not true, the diagnostic message is printed. Here’s an example of using static_assert to ensure types have a certain size:
```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```

On the author’s machine, when compiled, the compiler errors:
`1>c:\consoleapplication1\main.cpp(19): error C2338: long must be 8 bytes`

A few useful notes about `static_assert`:
- Because `static_assert` is evaluated by the compiler, the condition must be a constant expression.
- `static_assert` can be placed anywhere in the code file (even in the global namespace).
- `static_assert` is not deactivated in release builds (like normal `assert` is).
- Because the compiler does the evaluation, there is no runtime cost to a `static_assert`.

Prior to C++17, the diagnostic message must be supplied as the second parameter. Since C++17, providing a diagnostic message is optional.
#### Best practice
Favor `static_assert` over `assert()` whenever possible.

### Asserts vs error handling
Assertions and error handling are similar enough that their purposes can be confused, so let’s clarify.

Assertions are used to detect _programming errors_ during development by documenting assumptions about things that should never happen. And if they do happen, it’s the fault of the programmer. Assertions do not allow recovery from errors (after all, if something should never happen, there’s no need to recover from it). Because asserts are typically compiled-out in release builds, you can put a lot of them in without worrying about performance, so there’s little reason not to use them liberally.

Error handling is used when we need to gracefully handle cases that could happen (however rarely) in a release build. These may either be recoverable issues (where the program can keep running), or unrecoverable issues (where the program has to shut down, but we can at least show a nice error message and ensure everything is cleaned up properly). Error detection and handling has both a runtime performance cost and a development time cost.

In some cases, it’s less clear what we should do. Consider a function like this:

```cpp
double getInverse(double x)
{
    return 1.0 / x;
}
```

If `x` is `0.0`, this function will misbehave, and we need to guard against that. Should we use an assert or error handling? The best answer may be “both”.

During debugging, if this function is called when `x` is `0.0`, that indicates a bug in our code somewhere, and we want to know that immediately. So an assert is definitely appropriate.

However, this could also reasonably happen in a release build (e.g. along an obscure path we didn’t test). If the assert is compiled out and we don’t have error handling, then this function will return something unexpected and misbehave. In such a case, it’s probably better to detect that and handle the case.

Our resulting function might look like this:

```cpp
double getInverse(double x)
{
    assert(x != 0.0);
    if (x == 0.0)
       // handle error somehow (e.g. throw an exception)

    return 1.0 / x;
}
```

#### Tip
Given this, we suggest the following:
- Use assertions to detect programming errors, incorrect assumptions, or conditions that should never occur in correct code. It is the programmer’s responsibility to fix these, so we want to catch them early.
- Use error handling for issues that we expect will occur during the normal operation of your program.
- Use both in cases where something isn’t supposed to occur, but we want to fail gracefully if it does.
### Some assert limitations and warnings

There are a few pitfalls and limitations to asserts. First, the assert itself can be improperly written. If this happens, the assert will either report an error where none exists, or fail to report a bug where one does exist.

Second, your `assert()` expressions should have no side effects, as the assert expression won’t be evaluated when `NDEBUG` is defined (and thus the side effect won’t be applied). Otherwise, what you are testing in a debug configuration will not be the same as in a release configuration (assuming you ship with NDEBUG).

Also note that the `abort()` function terminates the program immediately, without a chance to do any further cleanup (e.g. close a file or database). Because of this, asserts should be used only in cases where corruption isn’t likely to occur if the program terminates unexpectedly.

## 9.x [Chapter 9 summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-9-summary-and-quiz/)
### Chapter Review

**Scope creep** occurs when a project’s capabilities grow beyond what was originally intended at the start of the project or project phase.

**Software verification** is the process of testing whether or not the software works as expected in all cases. A **unit test** is a test designed to test a small portion of the code (typically a function or call) in isolation to ensure a particular behavior occurs as expected. **Unit test frameworks** can help you organize your unit tests. **Integration testing** tests the integration of a bunch of units together to ensure they work properly.

**Code coverage** refers to how much of the source code is executed while testing. **Statement coverage** refers to the percentage of statements in a program that have been exercised by testing routines. **Branch coverage** refers to the percentage of branches that have been executed by testing routines. **Loop coverage** (also called the **0, 1, 2 test**) means that if you have a loop, you should ensure it works properly when it iterates 0 times, 1 time, and 2 times.

The **happy path** is the path of execution that occurs when there are no errors encountered. A **sad path** is one where an error or failure state occurs. A **non-recoverable error** (also called a **fatal error**) is an error that is severe enough that the program can’t continue running. A program that handles error cases well is **robust**.

A **buffer** is a piece of memory set aside for storing data temporarily while it is moved from one place to another.

The process of checking whether user input conforms to what the program is expecting is called **input validation**.

**std::cerr** is an output stream (like `std::cout`) designed to be used for error messages.

A **precondition** is any condition that must always be true prior to the execution of some segment of code. An **invariant** is a condition that must be true while some component is executing. A **postcondition** is any condition that must always be true after the execution of some code.

An **assertion** is an expression that will be true unless there is a bug in the program. In C++, runtime assertions are typically implemented using the **assert** preprocessor macro. Assertions are usually turned off in non-debug code. A **static_assert** is an assertion that is evaluated at compile-time. `assert(BooleanConditionToTest & "msg erreur si besoin")`

Assertions should be used to document cases that should be logically impossible. Error handling should be used to handle cases that are possible.

See the [std::cin and handling invalid input](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/) for how to handle `std::cin` errors