# Fundamental Data Types

## 4.1 [Introduction to fundamental data types](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/)
The smallest unit of memory is a **binary digit** (also called a **bit**), which can hold a value of 0 or 1.
Memory is organized into sequential units called **memory addresses** (or **addresses** for short).

**byte** is a group of bits that are operated on as a unit. The modern standard is that a byte is comprised of 8 sequential bits.
Key insight : In C++, we typically work with “byte-sized” chunks of data.

Because all data on a computer is just a sequence of bits, we use a **data type** (often called a **type** for short) to tell the compiler how to interpret the contents of memory in some meaningful way.

### Fundamental data types

The C++ language comes with many predefined data types available for your use. The most basic of these types are called the **fundamental data types** (informally sometimes called **basic types** or **primitive types**).

Here is a list of the fundamental data types, some of which you have already seen:

|Types|Category|Meaning|Example|
|---|---|---|---|
|float  <br>double  <br>long double|Floating Point|a number with a fractional part|3.14159|
|bool|Integral (Boolean)|true or false|true|
|char  <br>wchar_t  <br>char8_t (C++20)  <br>char16_t (C++11)  <br>char32_t (C++11)|Integral (Character)|a single character of text|‘c’|
|short int  <br>int  <br>long int  <br>long long int (C++11)|Integral (Integer)|positive and negative whole numbers, including 0|64|
|std::nullptr_t (C++11)|Null Pointer|a null pointer|nullptr|
|void|Void|no type|n/a|

This chapter is dedicated to exploring these fundamental data types in detail (except `std::nullptr_t`, which we’ll discuss when we talk about pointers).

### Integer vs integral types

In mathematics, an “integer” is a number with no decimal or fractional part, including negative and positive numbers and zero. The term “integral” has several different meanings, but in the context of C++ is used to mean “like an integer”.
The C++ standard defines the following terms:
- The **standard integer types** are `short`, `int`, `long`, `long long` (including their signed and unsigned variants).
- The **integral types** are `bool`, the various char types, and the standard integer types.

All integral types are stored in memory as integer values, but only the standard integer types will display as an integer value when output. We’ll discuss what `bool` and the char types do when output in their respective lessons.

The C++ standard also explicitly notes that “integer types” is a synonym for “integral types”. However, conventionally, “integer types” is more often used as shorthand for the “standard integer types” instead.

Also note that the term “integral types” only includes fundamental types. This means non-fundamental types (such as `enum` and `enum class`) are not integral types, even when they are stored as an integer (and in the case of `enum`, displayed as one too).

### Other sets of types

C++ contains three sets of types.
The first two are built-in to the language itself (and do not require the inclusion of a header to use):
- The “fundamental data types” provide the most the basic and essential data types.
- The “compound data types” provide more complex data types and allow for the creation of custom (user-defined) types.

The third (and largest) set of types is provided by the C++ standard library. Because the standard library is included in all C++ distributions, these types are broadly available and have been standardized for compatibility. Use of the types in the standard library requires the inclusion of the appropriate header and linking in the standard library.

Nomenclature : The term “built-in type” is most often used as a synonym for the fundamental data types. However, many use the term to mean both the fundamental and compound data types (both of which are built-in to the core language). Since this term isn’t well-defined, we recommend avoiding it accordingly. 

A notable omission from the table of fundamental types above is a data type to handle **strings** (a sequence of characters that is typically used to represent text). This is because in modern C++, strings are part of the standard library.

#### The _t suffix

Many of the types defined in newer versions of C++ (e.g. `std::nullptr_t`) use a _t suffix. This suffix means “type”, and it’s a common nomenclature applied to modern types.

If you see something with a _t suffix, it’s probably a type. But many types don’t have a _t suffix, so this isn’t consistently applied.


## 4.2 [Void](https://www.learncpp.com/cpp-tutorial/void/)
Void is the easiest of the data types to explain. Basically, **void** means “no type”!
Void is our first example of an incomplete type. An **incomplete type** is a type that has been declared but not yet defined.
The compiler knows about the existence of such types, but does not have enough information to determine how much memory to allocate for objects of that type. `void` is intentionally incomplete since it represents the lack of a type, and thus cannot be defined.

Incomplete types can not be instantiated:

```cpp
void value; // won't work, variables can't be defined with incomplete type void
```

Void is typically used in several different contexts.

### Functions that do not return a value
If you use a return statement to try to return a value in such a function, a compile error will result.
### Deprecated: Functions that do not take parameters

In C, void is used as a way to indicate that a function does not take any parameters:

```cpp
int getValue(void){ // void here means no parameters
```
Although this will compile in C++ (for backwards compatibility reasons), this use of keyword _void_ is considered deprecated in C++. The following code is equivalent, and preferred in C++:

```cpp
int getValue() // empty function parameters is an implicit void
	{
```

Best practice  Use an empty parameter list instead of _void_ to indicate that a function has no parameters.

### Other uses of void 
The void keyword has a third (more advanced) use in C++ that we cover in section [19.5 -- Void pointers](https://www.learncpp.com/cpp-tutorial/void-pointers/).

## 4.3 [Object sizes and the sizeof operator](https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/)
### object size
Memory on modern machines is typically organized into byte-sized units, with each byte of memory having a unique address.

A single object may use 1, 2, 4, 8, or even more consecutive memory addresses. The amount of memory that an object uses is based on its data type.

Because we typically access memory through variable names (and not directly via memory addresses), the compiler is able to hide the details of how many bytes a given object uses from us. When we access some variable `x` in our source code, the compiler knows how many bytes of data need to be retrieved (based on the type of variable `x`), and will output the appropriate machine language code to handle that detail for us.

Even so, there are several reasons it is useful to know how much memory an object uses.

First, the more memory an object uses, the more information it can hold.
A single bit can hold 2 possible values, a 0, or a 1.  2 bits can hold 4 possible values.
To generalize, an object with _n_ bits (where n is an integer) can hold 2n (2 to the power of n, also commonly written 2^n) unique values. Therefore, with an 8-bit byte, a byte-sized object can hold 28 (256) different values. An object that uses 2 bytes can hold 2^16 (65536) different values!

Thus, the size of the object puts a limit on the amount of unique values it can store -- objects that utilize more bytes can store a larger number of unique values. We will explore this further when we talk more about integers.

Second, computers have a finite amount of free memory. Every time we define an object, a small portion of that free memory is used for as long as the object is in existence. Because modern computers have a lot of memory, this impact is usually negligible. However, for programs that need a large amount of objects or data (e.g. a game that is rendering millions of polygons), the difference between using 1 byte and 8 byte objects can be significant.


Key insight : New programmers often focus too much on optimizing their code to use as little memory as possible. In most cases, this makes a negligible difference. Focus on writing maintainable code, and optimize only when and where the benefit will be substantive.

### Fundamental data type sizes
- An object must occupy at least 1 byte (so that each object has a distinct memory address).
- A byte must be at least 8 bits.
- The integral types `char`, `short`, `int`, `long`, and `long long` have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
- `char` and `char8_t` are exactly 1 byte (at least 8 bits).

Nomenclature  : When we talk about the size of a type, we really mean the size of an instantiated object of that type.


In this tutorial series, we will present a simplified view, by making some reasonable assumptions that are generally true for modern architectures:
- A byte is 8 bits.
- Memory is byte addressable (we can access every byte of memory independently).
- Floating point support is IEEE-754 compliant.
- We are on a 32-bit or 64-bit architecture.

Given the above assumptions, we can reasonably state the following:

|Category|Type|Minimum Size|Typical Size|
|---|---|---|---|
|Boolean|bool|1 byte|1 byte|
|Character|char|1 byte (exactly)|1 byte|
||wchar_t|1 byte|2 or 4 bytes|
||char8_t|1 byte|1 byte|
||char16_t|2 bytes|2 bytes|
||char32_t|4 bytes|4 bytes|
|Integral|short|2 bytes|2 bytes|
||int|2 bytes|4 bytes|
||long|4 bytes|4 or 8 bytes|
||long long|8 bytes|8 bytes|
|Floating point|float|4 bytes|4 bytes|
||double|8 bytes|8 bytes|
||long double|8 bytes|8, 12, or 16 bytes|
|Pointer|std::nullptr_t|4 bytes|4 or 8 bytes|

Tip : For maximum portability, you shouldn’t assume that objects are larger than the specified minimum size.

Alternatively, if you want to assume that a type has some non-minimum size (e.g. that an int is at least `4` bytes), you can use `static_assert` to have the compiler fail a build if it is compiled on an architecture where this assumption is not true.

The sizeof operator

In order to determine the size of data types on a particular machine, C++ provides an operator named `sizeof`. The **sizeof operator** is a unary operator that takes either a type or a variable, and returns the size of an object of that type (in bytes). You can compile and run the following program to find out how large some of your data types are:

```cpp
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT

int main()
{
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

    std::cout << std::left; // left justify output

    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";

    return 0;
}
```
Your results may vary based on compiler, computer architecture, OS, compilation settings (32-bit vs 64-bit), etc…

Trying to use `sizeof` on an incomplete type (such as `void`) will result in a compilation error.
For gcc users : If you have not disabled compiler extensions, gcc allows `sizeof(void)` to return 1 instead of producing a diagnostic ([Pointer-Arith](https://gcc.gnu.org/onlinedocs/gcc-4.4.2/gcc/Pointer-Arith.html#Pointer-Arith)). We show how to disable compiler extensions in lesson [0.10 -- Configuring your compiler: Compiler extensions](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-compiler-extensions/).

You can also use the `sizeof` operator on a variable name:

```cpp
    int x{};
    std::cout << "x is " << sizeof(x) << " bytes\n";

```

For advanced readers `sizeof` does not include dynamically allocated memory used by an object.

## 4.4 [Signed integers](https://www.learncpp.com/cpp-tutorial/signed-integers/)

An **integer** is an integral type that can represent positive and negative whole numbers, including 0 (e.g. -2, -1, 0, 1, 2). C++ has _4_ primary fundamental integer types available for use:

|Type|Minimum Size|Note|
|---|---|---|
|short int|16 bits||
|int|16 bits|Typically 32 bits on modern architectures|
|long int|32 bits||
|long long int|64 bits||

The key difference between the various integer types is that they have varying sizes -- the larger integers can hold bigger numbers.

A reminder : C++ only guarantees that integers will have a certain minimum size, not that they will have a specific size.

As an aside… Technically, the `bool` and `char` types are considered to be integral types (because these types store their values as integer values). For the purpose of the next few lessons, we’ll exclude these types from our discussion.

### Signed integers
This attribute of being positive, negative, or zero is called the number’s **sign**.

By default, integers in C++ are **signed**, which means the number’s sign is stored as part of the value. Therefore, a signed integer can hold both positive and negative numbers (and 0).

In this lesson, we’ll focus on signed integers. We’ll discuss unsigned integers (which can only hold non-negative numbers) in the next lesson.

### Defining signed integers

Here is the preferred way to define the four types of signed integers:

```cpp
short s;      // prefer "short" instead of "short int"
int i;
long l;       // prefer "long" instead of "long int"
long long ll; // prefer "long long" instead of "long long int"
```

Although _short int_, _long int_, or _long long int_ will work, we prefer the short names for these types (that do not use the _int_ suffix). In addition to being more typing, adding the _int_ suffix makes the type harder to distinguish from variables of type _int_. This can lead to mistakes if the short or long modifier is inadvertently missed.

The integer types can also take an optional _signed_ keyword, which by convention is typically placed before the type name:

```cpp
signed short ss;
signed int si;
signed long sl;
signed long long sll;
```

However, this keyword should not be used, as it is redundant, since integers are signed by default.

Best practice : Prefer the shorthand types that do not use the `int` suffix or `signed` prefix.

### Signed integer ranges

As you learned in the last section, a variable with _n_ bits can hold 2n possible values. But which specific values? We call the set of specific values that a data type can hold its **range**. The range of an integer variable is determined by two factors: its size (in bits), and whether it is signed or not.

For example, an 8-bit signed integer has a range of -128 to 127. This means an 8-bit signed integer can store any integer value between -128 and 127 (inclusive) safely.

Here’s a table containing the range of signed integers of different sizes:

|Size / Type|Range|
|---|---|
|8-bit signed|-128 to 127|
|16-bit signed|-32,768 to 32,767|
|32-bit signed|-2,147,483,648 to 2,147,483,647|
|64-bit signed|-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807|

For the math inclined, an n-bit signed variable has a range of -(2^n-1) to (2^n-1)-1.

For advanced readers
The above ranges assume “two’s complement” binary representation. This representation is the de-facto standard for modern architectures (as it is easier to implement in hardware), and is now required by the C++20 standard.
In prior standards, sign-magnitude and ones complement representations were permitted for historical reasons. Such representations produce values in the range -(2^n-1-1) to +(2^n-1-1).

### Overflow
What happens if we try to assign the value _140_ to an 8-bit signed integer? This number is outside the range that an 8-bit signed integer can hold. The number 140 requires 9 bits to represent (8 magnitude bits and 1 sign bit), but we only have 8 bits (7 magnitude bits and 1 sign bit) available in an 8-bit signed integer.

The C++20 standard makes this blanket statement: “If during the evaluation of an expression, the result is not mathematically defined or not in the range of representable values for its type, the behavior is undefined”. Colloquially, this is called **overflow**.

Therefore, assigning value 140 to an 8-bit signed integer will result in **undefined behavior**.

If an arithmetic operation (such as addition or multiplication) attempts to create a value outside the range that can be represented, this is called **integer overflow** (or **arithmetic overflow**). For signed integers, integer overflow will result in undefined behavior.

In general, overflow results in information being lost, which is almost never desirable. If there is _any_ suspicion that an object might need to store a value that falls outside its range, use a type with a bigger range!

### Integer division
When dividing two integers, C++ works like you’d expect when the **quotient** is a whole number:

```cpp
#include <iostream>

int main()
{
    std::cout << 8 / 5 << '\n';
    return 0;
}
```
When doing division with two integers (called **integer division**), C++ always produces an integer result. Since integers can’t hold fractional values, any fractional portion is simply dropped (not rounded!).

Taking a closer look at the above example, 8 / 5 produces the value 1.6. The fractional part (0.6) is dropped, and the result of 1 remains. Alternatively, we can say 8 / 5 equals 1 remainder 3. The remainder is dropped, leaving 1.

Warning :  Be careful when using integer division, as you will lose any fractional parts of the quotient. However, if it’s what you want, integer division is safe to use, as the results are predictable.

## 4.5 [Unsigned integers, and why to avoid them](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)
### Unsigned integers
C++ also supports unsigned integers. **Unsigned integers** are integers that can only hold non-negative whole numbers.

### Defining unsigned integers

To define an unsigned integer, we use the _unsigned_ keyword. By convention, this is placed before the type:

```cpp
unsigned short us;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
```

### Unsigned integer range

A 1-byte unsigned integer has a range of 0 to 255. Compare this to the 1-byte signed integer range of -128 to 127. Both can store 256 different values, but signed integers use half of their range for negative numbers, whereas unsigned integers can store positive numbers that are twice as large.

Here’s a table showing the range for unsigned integers:

|Size/Type|Range|
|---|---|
|8 bit unsigned|0 to 255|
|16 bit unsigned|0 to 65,535|
|32 bit unsigned|0 to 4,294,967,295|
|64 bit unsigned|0 to 18,446,744,073,709,551,615|

An n-bit unsigned variable has a range of 0 to (2n)-1.

When no negative numbers are required, unsigned integers are well-suited for networking and systems with little memory, because unsigned integers can store more positive numbers without taking up extra memory.

### Remembering the terms signed and unsigned

New programmers sometimes get signed and unsigned mixed up. The following is a simple way to remember the difference: in order to differentiate negative numbers from positive ones, we use a negative sign. If a sign is not provided, we assume a number is positive. Consequently, an integer with a sign (a signed integer) can tell the difference between positive and negative. An integer without a sign (an unsigned integer) assumes all values are positive.

### Unsigned integer overflow

What happens if we try to store the number `280` (which requires 9 bits to represent) in a 1-byte (8-bit) unsigned integer? The answer is overflow.

Author’s note : Oddly, the C++ standard explicitly says “a computation involving unsigned operands can never overflow”. This is contrary to general programming consensus that integer overflow encompasses both signed and unsigned use cases ([cite](https://en.wikipedia.org/wiki/Integer_overflow#Definition_variations_and_ambiguity)). Given that most programmers would consider this overflow, we’ll call this overflow despite the C++ standard’s statements to the contrary.

If an unsigned value is out of range, it is divided by one greater than the largest number of the type, and only the remainder kept.

The number `280` is too big to fit in our 1-byte range of 0 to 255. 1 greater than the largest number of the type is 256. Therefore, we divide 280 by 256, getting 1 remainder 24. The remainder of 24 is what is stored.


Here’s another way to think about the same thing. Any number bigger than the largest number representable by the type simply “wraps around” (sometimes called “modulo wrapping”). `255` is in range of a 1-byte integer, so `255` is fine. `256`, however, is outside the range, so it wraps around to the value `0`. `257` wraps around to the value `1`. `280` wraps around to the value `24`.

It’s possible to wrap around the other direction as well. 0 is representable in a 2-byte unsigned integer, so that’s fine. -1 is not representable, so it wraps around to the top of the range, producing the value 65535.
```cpp
{
    unsigned short x{ 0 }; // smallest 2-byte unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = -1; // -1 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';
```
The above code triggers a warning in some compilers, because the compiler detects that the integer literal is out-of-range for the given type. If you want to compile the code anyway, temporarily disable “Treat warnings as errors”.

### The controversy over unsigned numbers
Many developers (and some large development houses, such as Google) believe that developers should generally avoid unsigned integers.

This is largely because of two behaviors that can cause problems.

First, with signed values, it takes a little work to accidentally overflow the top or bottom of the range because those values are far from 0. With unsigned numbers, it is much easier to overflow the bottom of the range, because the bottom of the range is 0, which is close to where the majority of our values are. Like the subtraction of two unsigned numbers, such as 2 and 3.
Another common unwanted wrap-around happens when an unsigned integer is repeatedly decremented by 1, until it tries to decrement to a negative number. 

Second, and more insidiously, unexpected behavior can result when you mix signed and unsigned integers. In C++, if a mathematical operation (e.g. arithmetic or comparison) has one signed integer and one unsigned integer, the signed integer will usually be converted to an unsigned integer. And the result will thus be unsigned. For example:
```cpp
#include <iostream>

// assume int is 4 bytes
int main()
{
	unsigned int u{ 2 };
	signed int s{ 3 };

	std::cout << u - s << '\n'; // 2 - 3 = 4294967295

	return 0;
}
```
In this case, if `u` was signed, the correct result would be produced. But because `u` is unsigned (which is easy to miss), `s` gets converted to unsigned, and the result (`-1`) is treated as an unsigned value. Since `-1` can’t be stored in an unsigned value, so we get overflow and an unexpected answer.

```cpp
#include <iostream>

// assume int is 4 bytes
int main()
{
    signed int s { -1 };
    unsigned int u { 1 };

    if (s < u) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes

    return 0;
}
```
This program is well formed, compiles, and is logically consistent to the eye. But it prints the wrong answer. And while your compiler should warn you about a signed/unsigned mismatch in this case, your compiler will also generate identical warnings for other cases that do not suffer from this problem (e.g. when both numbers are positive), making it hard to detect when there is an actual problem.

Related content
We cover the conversion rules that require both operands of certain binary operations to be the same type in lesson [10.5 -- Arithmetic conversions](https://www.learncpp.com/cpp-tutorial/arithmetic-conversions/).  
We cover if-statements in upcoming lesson [4.10 -- Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/).

Additionally, there are other problematic cases that are challenging to detect. Consider the following:

```cpp
#include <iostream>

// assume int is 4 bytes
void doSomething(unsigned int x)
{
    // Run some code x times

    std::cout << "x is " << x << '\n';
}

int main()
{
    doSomething(-1);

    return 0;
}
```

The author of doSomething() was expecting someone to call this function with only positive numbers. But the caller is passing in _-1_ -- clearly a mistake, but one made regardless. What happens in this case?

The signed argument of `-1` gets implicitly converted to an unsigned parameter. `-1` isn’t in the range of an unsigned number, so it wraps around to 4294967295. Then your program goes ballistic.

Even more problematically, it can be hard to prevent this from happening. Unless you’ve configured your compiler to be aggressive about producing signed/unsigned conversion warnings (and you should), your compiler probably won’t even complain about this.

All of these problems are commonly encountered, produce unexpected behavior, and are hard to find, even using automated tools designed to detect problem cases.

Given the above, the somewhat controversial best practice that we’ll advocate for is to avoid unsigned types except in specific circumstances.

Best practice  : Favor signed numbers over unsigned numbers for holding quantities (even quantities that should be non-negative) and mathematical operations. Avoid mixing signed and unsigned numbers.

Related content
Additional material in support of the above recommendations (also covers refutation of some common counter-arguments):
1. [Interactive C++ panel](https://www.youtube.com/watch?v=_nrly6PH6NU) (see 9:48-13:08, 41:06-45:26, and 1:02:50-1:03:15)
2. [Subscripts and sizes should be signed](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1428r0.pdf) (from Bjarne Stroustrup, the creator of C++)
3. [Unsigned integers from the libtorrent blog](https://blog.libtorrent.org/2016/05/unsigned-integers/)

### So when should you use unsigned numbers?

There are still a few cases in C++ where it’s okay / necessary to use unsigned numbers.

First, unsigned numbers are preferred when dealing with bit manipulation (covered in chapter O -- that’s a capital ‘o’, not a ‘0’). They are also useful when well-defined wrap-around behavior is required (useful in some algorithms like encryption and random number generation).

Second, use of unsigned numbers is still unavoidable in some cases, mainly those having to do with array indexing. We’ll talk more about this in the lessons on arrays and array indexing.

Also note that if you’re developing for an embedded system (e.g. an Arduino) or some other processor/memory limited context, use of unsigned numbers is more common and accepted (and in some cases, unavoidable) for performance reasons.

## 4.6 [Fixed-width integers and size_t](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/)
In the previous lessons on integers, we covered that C++ only guarantees that integer variables will have a minimum size -- but they could be larger, depending on the target system.
For example, an `int` has a minimum size of 16-bits, but it’s typically 32-bits on modern architectures.
If you assume an `int` is 32-bits because that’s most likely, then your program will probably misbehave on architectures where `int` is actually 16-bits (since you will probably be storing values that require 32-bits of storage in a variable with only 16-bits of storage, which will cause overflow or undefined behavior).


Key insight : In most cases, we only instantiate a small number of `int` variables at a time, and these are typically destroyed at the end of the function in which they are created. In such cases, wasting 2 bytes of memory per variable isn’t a concern (the limited range is a bigger issue). However, in cases where our program allocates millions of `int` variables, wasting 2 bytes of memory per variable can have a significant impact on the program’s overall memory usage.

### Why isn’t the size of the integer types fixed?
The short answer is that this goes back to the early days of C, when computers were slow and performance was of the utmost concern. C opted to intentionally leave the size of an integer open so that the compiler implementers could pick a size for `int` that performs best on the target computer architecture. That way, programmers could just use `int` without having to worry about whether they could be using something more performant.
By modern standards, the lack of consistent ranges for the various integral types sucks (especially in a language designed to be portable).

### Fixed-width integers

To address the above issues, C++11 provides an alternate set of integer types that are guaranteed to be the same size on any architecture. Because the size of these integers is fixed, they are called **fixed-width integers**.

The fixed-width integers are defined (in the `<cstdint>\` header) as follows:

|Name|Fixed Size|Fixed Range|Notes|
|---|---|---|---|
|std::int8_t|1 byte signed|-128 to 127|Treated like a signed char on many systems. See note below.|
|std::uint8_t|1 byte unsigned|0 to 255|Treated like an unsigned char on many systems. See note below.|
|std::int16_t|2 byte signed|-32,768 to 32,767||
|std::uint16_t|2 byte unsigned|0 to 65,535||
|std::int32_t|4 byte signed|-2,147,483,648 to 2,147,483,647||
|std::uint32_t|4 byte unsigned|0 to 4,294,967,295||
|std::int64_t|8 byte signed|-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807||
|std::uint64_t|8 byte unsigned|0 to 18,446,744,073,709,551,615||

Here’s an example:

```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int32_t x { 32767 }; // x is always a 32-bit integer
```

Best practice :Use a fixed-width integer type when you need an integral type that has a guaranteed range.

### Warning: `std::int8_t` and `std::uint8_t` typically behave like chars

Due to an oversight in the C++ specification, modern compilers typically treat `std::int8_t` and `std::uint8_t` (and the corresponding fast and least fixed-width types, which we’ll introduce in a moment) the same as `signed char` and `unsigned char` respectively. Thus on most modern systems, the 8-bit fixed-width integral types will behave like char types.

As a quick teaser:

```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int8_t x { 65 };   // initialize 8-bit integral type with value 65
    std::cout << x << '\n'; // You're probably expecting this to print 65
```
Although you’re probably expecting the above program to print `65`, it most likely won’t.

We discuss what this example actually prints (and how to ensure it always prints `65`) in lesson [4.12 -- Introduction to type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/), after we cover chars (and how they print) in lesson [4.11 -- Chars](https://www.learncpp.com/cpp-tutorial/chars/).

Warning : The 8-bit fixed-width integer types are often treated like chars instead of integer values (and this may vary per system). The 16-bit and wider integral types are not subject to this issue.

#### For advanced readers
The fixed-width integers actually don’t define new types -- they are just aliases for existing integral types with the desired size. For each fixed-width type, the implementation (the compiler and standard library) gets to determine which existing type is aliased. As an example, on a platform where `int` is 32-bits, `std::int32_t` will be an alias for `int`. On a system where `int` is 16-bits (and `long` is 32-bits), `std::int32_t` will be an alias for `long` instead.

So what about the 8-bit fixed-width types?

In most cases, `std::int8_t` is an alias for `signed char` because it is the only available 8-bit signed integral type (`bool` and `char` are not considered to be signed integral types). And when this is the case, `std::int8_t` will behave just like a char on that platform.

However, in rare cases, if a platform has an implementation-specific 8-bit signed integral type, the implementation may decide to make `std::int8_t` an alias for that type instead. In that case, `std::int8_t` will behave like that type, which may be more like an int than a char.

`std::uint8_t` behaves similarly.

### Other fixed-width downsides

The fixed-width integers have some potential downsides:

First, the fixed-width integers are not guaranteed to be defined on all architectures. They only exist on systems where there are fundamental integral types that match their widths and following a certain binary representation. Your program will fail to compile on any such architecture that does not support a fixed-width integer that your program is using. However, given that modern architectures have standardized around 8/16/32/64-bit variables, this is unlikely to be a problem unless your program needs to be portable to some exotic mainframe or embedded architectures.

Second, if you use a fixed-width integer, it may be slower than a wider type on some architectures. For example, if you need an integer that is guaranteed to be 32-bits, you might decide to use `std::int32_t`, but your CPU might actually be faster at processing 64-bit integers. However, just because your CPU can process a given type faster doesn’t mean your program will be faster overall -- modern programs are often constrained by memory usage rather than CPU, and the larger memory footprint may slow your program more than the faster CPU processing accelerates it. It’s hard to know without actually measuring.

These are just minor quibbles though.

### Fast and least integral types Optional
To help address the above downsides, C++ also defines two alternative sets of integers that are guaranteed to exist.
The fast types (`std::int_fast#_t` and `std::uint_fast#_t`) provide the fastest signed/unsigned integer type with a width of at least # bits (where # = 8, 16, 32, or 64). For example, `std::int_fast32_t` will give you the fastest signed integer type that’s at least 32-bits. By fastest, we mean the integral type that can be processed most quickly by the CPU.

The least types (`std::int_least#_t` and `std::uint_least#_t`) provide the smallest signed/unsigned integer type with a width of at least # bits (where # = 8, 16, 32, or 64). For example, `std::uint_least32_t` will give you the smallest unsigned integer type that’s at least 32-bits.

However, these fast and least integers have their own downsides. First, not many programmers actually use them, and a lack of familiarity can lead to errors. Then the fast types can also lead to memory wastage, as their actual size may be significantly larger than indicated by their name.

Most seriously, because the size of the fast/least integers is implementation-defined, your program may exhibit different behaviors on architectures where they resolve to different sizes.
```cpp

    std::uint_fast16_t sometype { 0 };
    sometype = sometype - 1; // intentionally overflow to invoke wraparound behavior
```
This code will produce different results depending on whether `std::uint_fast16_t` is 16, 32, or 64 bits! This is exactly what we were trying to avoid by using fixed-width integers in the first place!

Best practice : Avoid the fast and least integral types because they may exhibit different behaviors on architectures where they resolve to different sizes.

### Best practices for integral types
Given the various pros and cons of the fundamental integral types, the fixed-width integral types, the fast/least integral types, and signed/unsigned challenges, there is little consensus on integral best practices.

Our stance is that it’s better to be correct than fast, and better to fail at compile time than runtime. Therefore, if you need an integral type with a guaranteed range, we recommend avoiding the fast/least types in favor of the fixed-width types. If you later discover the need to support an esoteric platform for which a specific fixed-width integral type won’t compile, then you can decide how to migrate your program (and thoroughly retest) at that point.

Best practice
- Prefer `int` when the size of the integer doesn’t matter (e.g. the number will always fit within the range of a 2-byte signed integer). For example, if you’re asking the user to enter their age, or counting from 1 to 10, it doesn’t matter whether `int` is 16-bits or 32-bits (the numbers will fit either way). This will cover the vast majority of the cases you’re likely to run across.
- Prefer `std::int#_t` when storing a quantity that needs a guaranteed range.
- Prefer `std::uint#_t` when doing bit manipulation or well-defined wrap-around behavior is required (e.g. for cryptography or random number generation).

Avoid the following when possible:
- `short` and `long` integers (prefer a fixed-width integer type instead).
- The fast and least integral types (prefer a fixed-width integer type instead).
- Unsigned types for holding quantities (prefer a signed integer type instead).
- The 8-bit fixed-width integer types (prefer a 16-bit fixed-width integer type instead).
- Any compiler-specific fixed-width integers (for example, Visual Studio defines __int8, __int16, etc…)

### What is std::size_t?
Pretty simple, right? We can infer that operator `sizeof` returns an integer value (the number of bytes), -- but what integral type is that return value? An int? A short? The answer is that `sizeof` returns a value of type `std::size_t`. **std::size_t** is an alias for an implementation-defined unsigned integral type. In other words, the compiler decides if `std::size_t` is an unsigned int, an unsigned long, an unsigned long long, etc…

Key insight : `std::size_t` is an alias for an implementation-defined unsigned integral type. It is used within the standard library to represent the byte-size or length of objects.

#### For advanced readers
`std::size_t` is actually a typedef. We cover typedefs in lesson [10.7 -- Typedefs and type aliases](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/).
`std::size_t` is defined in a number of different headers. If you need to use `std::size_t`, `<cstddef>` is the best header to include, as it contains the least number of other defined identifiers.


Best practice : If you use `std::size_t` explicitly in your code, #include one of the headers that defines `std::size_t` (we recommend `<cstddef>`).  Using `sizeof` does not require a header (even though it returns a value whose type is `std::size_t`).

Much like an integer can vary in size depending on the system, `std::size_t` also varies in size. `std::size_t` is guaranteed to be unsigned and at least 16 bits, but on most systems will be equivalent to the address-width of the application. That is, for 32-bit applications, `std::size_t` will typically be a 32-bit unsigned integer, and for a 64-bit application, `std::size_t` will typically be a 64-bit unsigned integer.

`std::size_t` imposes an upper limit on the size of an object Optional
The [C++20 standard](https://isocpp.org/files/papers/N4860.pdf#subsection.6.8.2) ([basic.compound] 1.8.2) says: “Constructing a type such that the number of bytes in its object representation exceeds the maximum value representable in the type std::size_t (17.2) is ill-formed.”
If it were possible to create a larger object, `sizeof` would not be able to return its byte-size, as it would be outside the range that a `std::size_t` could hold. Thus, creating an object with a size (in bytes) larger than the largest value an object of type `std::size_t` can hold is invalid (and will cause a compile error).

As an aside…
The size of `std::size_t` imposes a strict mathematical upper limit on an object’s size. In practice, the largest creatable object may be smaller than this amount (perhaps significantly so).
Some compilers limit the largest creatable object to half the maximum value of `std::size_t` (an explanation for this can be found [here](https://stackoverflow.com/a/42428240)).
Other factors may also play a role, such as how much contiguous memory your computer has available for allocation.
When 8-bit and 16-bit applications were the norm, this limit imposed a significant constraint on the size of objects. In the 32-bit and 64-bit era, this is rarely an issue, and therefore not something you generally need to worry about.

## 4.7 [Introduction to scientific notation](https://www.learncpp.com/cpp-tutorial/introduction-to-scientific-notation/)
**Scientific notation** is a useful shorthand for writing lengthy numbers in a concise manner. And although scientific notation may seem foreign at first, understanding scientific notation will help you understand how floating point numbers work, and more importantly, what their limitations are.

Numbers in scientific notation take the following form: _significand_ x 10_exponent_. For example, in the scientific notation `1.2 x 10⁴`, `1.2` is the significand and `4` is the exponent. Since 10⁴ evaluates to 10,000, 1.2 x 10⁴ evaluates to 12,000.

Because it can be hard to type or display exponents in C++, we use the letter ‘e’ (or sometimes ‘E’) to represent the “times 10 to the power of” part of the equation. For example, `1.2 x 10⁴` would be written as `1.2e4`, and `5.9722 x 10²⁴` would be written as `5.9722e24`.
For numbers smaller than 1, the exponent can be negative. The number `5e-2` is equivalent to `5 * 10⁻²`, which is `5 / 10²`, or `0.05`.

The digits in the significand (the part before the ‘e’) are called the **significant digits** (or **significant figures**). The more significant digits, the more precise a number is.

## 4.8 [Floating point numbers](https://www.learncpp.com/cpp-tutorial/floating-point-numbers/)

Integers are great for counting whole numbers, but sometimes we need to store _very_ large (positive or negative) numbers, or numbers with a fractional component. A **floating point** type variable is a variable that can hold a number with a fractional component, such as 4320.0, -3.33, or 0.01226. The _floating_ part of the name _floating point_ refers to the fact that the decimal point can “float” -- that is, it can support a variable number of digits before and after the decimal point. Floating point data types are always signed (can hold positive and negative values).

Tip : When writing floating point numbers in your code, the decimal separator must be a decimal point. If you’re from a country that uses a decimal comma, you’ll need to get used to using a decimal point instead.


### C++ floating point types

C++ has three fundamental floating point data types: a single-precision `float`, a double-precision `double`, and an extended-precision `long double`. As with integers, C++ does not define the actual size of these types.

|Category|C++ Type|Typical Size|
|---|---|---|
|floating point|float|4 bytes|
||double|8 bytes|
||long double|8, 12, or 16 bytes|

On modern architectures, floating-point types are conventionally implemented using one of the floating-point formats defined in the IEEE 754 standard (see [https://en.wikipedia.org/wiki/IEEE_754](https://en.wikipedia.org/wiki/IEEE_754)). As a result, `float` is almost always 4 bytes, and `double` is almost always 8 bytes.

On the other hand, `long double` is a strange type. On different platforms, its size can vary between 8 and 16 bytes, and it may or may not use an IEEE 754 compliant format. We recommend avoiding `long double`.
You can see if your floating point types are IEEE 754 compatible with the following code:
```cpp
    std::cout << "float: " << std::numeric_limits<float>::is_iec559 << '\n';
```

##### For advanced readers
`float` is almost always implemented using the 4-byte IEEE 754 single-precision format.  
`double` is almost always implemented using the 8-byte IEEE 754 double-precision format.

However, the format used to implement `long double` varies by platform. Common choices include:
- 8-byte IEEE 754 double-precision format (same as `double`).
- 80-bit (often padded to 12 or 16 bytes) x87 extended-precision format (compatible with IEEE 754).
- 16-byte IEEE 754 quadruple-precision format.
- 16-byte double-double format (not compatible with IEEE 754).

### Floating point variables and literals

Here are some definitions of floating point variables:
```cpp
float f;
double d;
long double ld;
```

When using floating point literals, always include at least one decimal place (even if the decimal is 0). This helps the compiler understand that the number is a floating point number and not an integer.

```cpp
int a { 5 };      // 5 means integer
double b { 5.0 }; // 5.0 is a floating point literal (no suffix means double type by default)
float c { 5.0f }; // 5.0 is a floating point literal, f suffix means float type
```
Note that by default, floating point literals default to type double. An `f` suffix is used to denote a literal of type float.

Best practice : Always make sure the type of your literals match the type of the variables they’re being assigned to or used to initialize. Otherwise an unnecessary conversion will result, possibly with a loss of precision.

#### Printing floating point numbers
```cpp
#include <iostream>

int main()
{
	std::cout << 5.0 << '\n'; // 5
	std::cout << 6.7f << '\n'; // 6.7
	std::cout << 9876543.21 << '\n'; // 9.87654e+06

	return 0;
}
```

#### Floating point range

|Format|Range|Precision|
|---|---|---|
|IEEE 754 single-precision (4 bytes)|±1.18 x 10-38 to ±3.4 x 1038 and 0.0|6-9 significant digits, typically 7|
|IEEE 754 double-precision (8 bytes)|±2.23 x 10-308 to ±1.80 x 10308 and 0.0|15-18 significant digits, typically 16|
|x87 extended-precision (80 bits)|±3.36 x 10-4932 to ±1.18 x 104932 and 0.0|18-21 significant digits|
|IEEE 754 quadruple-precision (16 bytes)|±3.36 x 10-4932 to ±1.18 x 104932 and 0.0|33-36 significant digits|
#### For advanced readers
The 80-bit x87 extended-precision floating point type is a bit of a historical anomaly. On modern processors, objects of this type are typically padded to 12 or 16 bytes (which is a more natural size for processors to handle). This means those objects have 80-bits of floating point data, and the remaining memory is filler.
It may seem a little odd that the 80-bit floating point type has the same range as the 16-byte floating point type. This is because they have the same number of bits dedicated to the exponent -- however, the 16-byte number can store more significant digits.

### Floating point precision
Consider the fraction 1/3. The decimal representation of this number is 0.33333333333333… with 3’s going out to infinity.

On a computer, an infinite precision number would require infinite memory to store, and we typically only have 4 or 8 bytes per value. This limited memory means floating point numbers can only store a certain number of significant digits -- any additional significant digits are either lost or represented imprecisely. The number that is actually stored may be close to the desired number, but not exact. We’ll show an example of this in the next section.

The **precision** of a floating point type defines how many significant digits it can represent without information loss.

The number of digits of precision a floating point type has depends on both the size (floats have less precision than doubles) and the particular value being stored (some values can be represented more precisely than others).

For example, a float has 6 to 9 digits of precision. This means that a float can exactly represent any number with up to 6 significant digits. A number with 7 to 9 significant digits may or may not be represented exactly depending on the specific value. And a number with more than 9 digits of precision will definitely not be represented exactly.

Double values have between 15 and 18 digits of precision, with most double values having at least 16 significant digits. Long double has a minimum precision of 15, 18, or 33 significant digits depending on how many bytes it occupies.

##### Key insight

A floating point type can only precisely represent a certain number of significant digits. Using a value with more significant digits than the minimum may result in the value being stored inexactly.

### Outputting floating point values
When outputting floating point numbers, `std::cout` has a default precision of 6 -- that is, it assumes all floating point variables are only significant to 6 digits (the minimum precision of a float), and hence it will truncate anything after that.

Also note that std::cout will switch to outputting numbers in scientific notation in some cases. Depending on the compiler, the exponent will typically be padded to a minimum number of digits. Fear not, 9.87654e+006 is the same as 9.87654e6, just with some padding 0’s. The minimum number of exponent digits displayed is compiler-specific (Visual Studio uses 3, some others use 2 as per the C99 standard).

We can override the default precision that std::cout shows by using an `output manipulator` function named `std::setprecision()`. **Output manipulators** alter how data is output, and are defined in the _iomanip_ header.


Tip 
Output manipulators (and input manipulators) are sticky -- meaning if you set them, they will remain set.
The one exception is `std::setw`. Some IO operations reset `std::setw`, so `std::setw` should be used every time it is needed.

Precision issues don’t just impact fractional numbers, they impact any number with too many significant digits. Let’s consider a big number:
```cpp
    float f { 123456789.0f }; // f has 10 significant digits
    std::cout << std::setprecision(9); // to show 9 digits in f // 123456792
```
We lost some precision! When precision is lost because a number can’t be stored precisely, this is called a **rounding error**.
Consequently, one has to be careful when using floating point numbers that require more precision than the variables can hold.

Best practice
Favor double over float unless space is at a premium, as the lack of precision in a float will often lead to inaccuracies.

### Rounding errors make floating point comparisons tricky
Floating point numbers are tricky to work with due to non-obvious differences between binary (how data is stored) and decimal (how we think) numbers. Consider the fraction 1/10. In decimal, this is easily represented as 0.1, and we are used to thinking of 0.1 as an easily representable number with 1 significant digit. However, in binary, decimal value 0.1 is represented by the infinite sequence: 0.00011001100110011… Because of this, when we assign 0.1 to a floating point number, we’ll run into precision problems.

```cpp
double d{0.1};
    std::cout << d << '\n'; // use default cout precision of 6
    std::cout << std::setprecision(17);
    std::cout << d << '\n';

// Output:
// 0.1
// 0.10000000000000001
```
On the top line, `std::cout` prints 0.1, as we expect.

On the bottom line, where we have `std::cout` show us 17 digits of precision, we see that `d` is actually _not quite_ 0.1! This is because the double had to truncate the approximation due to its limited memory. The result is a number that is precise to 16 significant digits (which type double guarantees), but the number is not _exactly_ 0.1. Rounding errors may make a number either slightly smaller or slightly larger, depending on where the truncation happens.
```cpp
    double d1{ 1.0 };
    std::cout << d1 << '\n';

    double d2{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should equal 1.0 // 0.99999999999999989 in reality
    std::cout << d2 << '\n';
```
Although we might expect that `d1` and `d2` should be equal, we see that they are not. If we were to compare `d1` and `d2` in a program, the program would probably not perform as expected. Because floating point numbers tend to be inexact, comparing floating point numbers is generally problematic -- we discuss the subject more (and solutions) in lesson [6.7 -- Relational operators and floating point comparisons](https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/).

One last note on rounding errors: mathematical operations (such as addition and multiplication) tend to make rounding errors grow. So even though 0.1 has a rounding error in the 17th significant digit, when we add 0.1 ten times, the rounding error has crept into the 16th significant digit. Continued operations would cause this error to become increasingly significant.

### Key insight 
Rounding errors occur when a number can’t be stored precisely. This can happen even with simple numbers, like 0.1. Therefore, rounding errors can, and do, happen all the time. Rounding errors aren’t the exception -- they’re the norm. Never assume your floating point numbers are exact.
A corollary of this rule is: be wary of using floating point numbers for financial or currency data.

Related content
For more insight into how floating point numbers are stored in binary, check out the [float.exposed](https://float.exposed/0x3dcccccd) tool.  
To learn more about floating point numbers and rounding errors, [floating-point-gui.de](https://floating-point-gui.de/) and [fabiensanglard.net](https://fabiensanglard.net/floating_point_visually_explained/index.html) have approachable guides on the topic.


###  NaN and Inf

IEEE 754 compatible formats additionally support some special values:

- **Inf**, which represents infinity. Inf is signed, and can be positive (+Inf) or negative (-Inf).
- **NaN**, which stands for “Not a Number”. There are several different kinds of NaN (which we won’t discuss here).
- Signed zero, meaning there are separate representations for “positive zero” (+0.0) and “negative zero” (-0.0).

Formats that are not compatible with IEEE 754 may not support some (or any) of these values. In such cases, code that uses or generates these special values will produce implementation-defined behavior.

Here’s a program showing all three:

```cpp
#include <iostream>

int main()
{
    double zero { 0.0 };

    double posinf { 5.0 / zero }; // positive infinity
    std::cout << posinf << '\n';

    double neginf { -5.0 / zero }; // negative infinity
    std::cout << neginf << '\n';

    double z1 { 0.0 / posinf }; // positive zero
    std::cout << z1 << '\n';

    double z2 { -0.0 / posinf }; // negative zero
    std::cout << z2 << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}
```

And the results using Clang:

```
inf
-inf
0
-0
nan
```
Note that the results of printing `Inf` and `NaN` are platform specific, so your results may vary

Best practice  : Avoid division by `0.0`, even if your compiler supports it.

#### Conclusion

To summarize, the two things you should remember about floating point numbers:
1. Floating point numbers are useful for storing very large or very small numbers, including those with fractional components.
2. Floating point numbers often have small rounding errors, even when the number has fewer significant digits than the precision. Many times these go unnoticed because they are so small, and because the numbers are truncated for output. However, comparisons of floating point numbers may not give the expected results. Performing mathematical operations on these values will cause the rounding errors to grow larger.

## 4.9 [Boolean values](https://www.learncpp.com/cpp-tutorial/boolean-values/)

The kinds of sentences that have only two possible outcomes: yes/true, or no/false are so common, that many programming languages include a special type for dealing with them. That type is called a **Boolean** type (note: Boolean is properly capitalized in the English language because it’s named after its inventor, George Boole).

### Boolean variables

Boolean variables are variables that can have only two possible values: `true`, and `false`.

To declare a Boolean variable, we use the keyword `bool`.

```cpp
bool b;
```

To initialize or assign a `true` or `false` value to a Boolean variable, we use the keywords `true` and `false`.

```cpp
bool b1 { true };
bool b2 { false };
b1 = false;
bool b3 {}; // default initialize to false
```
Just as the unary minus operator (-) can be used to make an integer negative, the logical NOT operator (!) can be used to flip a Boolean value from `true` to `false`, or `false` to `true`:

```cpp
bool b1 { !true }; // b1 will be initialized with the value false
```
Boolean values are not actually stored in Boolean variables as the words “true” or “false”. Instead, they are stored as integral values: `true` is stored as integer `1`, and `false` is stored as integer `0`. Similarly, when Boolean values are evaluated, they don’t actually evaluate to “true” or “false”. They evaluate to the integers `0` (false) or `1` (true). Because Booleans store integral values, they are considered to be an integral type.

### Printing Boolean values
When we print Boolean values, `std::cout` prints `0` for `false`, and `1` for `true`

Use `std::boolalpha` to print `true` or `false`

If you want `std::cout` to print `true` or `false` instead of `0` or `1`, you can output `std::boolalpha`. This doesn’t output anything, but manipulates the way `std::cout` outputs `bool` values.
```cpp
    std::cout << true << '\n';//1
	std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n'; // true
```
You can use `std::noboolalpha` to turn it back off.

### Integer to Boolean conversion
When using uniform initialization, you can initialize a variable using integer literals `0` (for `false`) and `1` (for `true`) (but you really should be using `false` and `true` instead). Other integer literals cause compilation errors:
```cpp
	bool bFalse { 0 }; // okay: initialized to false
	bool bTrue  { 1 }; // okay: initialized to true
	bool bNo    { 2 }; // error: narrowing conversions disallowed
```
However, in any context where an integer can be converted to a Boolean, the integer `0` is converted to `false`, and any other integer is converted to `true`.
```cpp
	bool b1 = 4 ; // copy initialization allows implicit conversion from int to bool
	std::cout << b1 << '\n'; // print 1

	bool b2 = 0 ; // copy initialization allows implicit conversion from int to bool
	std::cout << b2 << '\n';
```
### Inputting Boolean values
Inputting Boolean values using `std::cin` sometimes trips new programmers up.

Consider the following program:

```cpp
#include <iostream>

int main()
{
	bool b{}; // default initialize to false
	std::cout << "Enter a boolean value: ";
	std::cin >> b;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```

```
Enter a Boolean value: true
You entered: 0
```
Wait, what?

By default, `std::cin` only accepts numeric input for Boolean variables: `0` is `false`, and `1` is `true`. Any other numeric value will be interpreted as `true`, and will cause `std::cin` to enter failure mode. Any non-numeric value will be interpreted as `false` and will cause `std::cin` to enter failure mode.

Related content : We discuss failure mode (and how to get out of it) in lesson [9.5 -- std::cin and handling invalid input](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/).

In this case, because we entered `true`, `std::cin` silently failed and set `b` to `false`. Consequently, when `std::cout` prints a value for `b`, it prints `0`.

To allow `std::cin` to accept the words `false` and `true` as inputs, you must first input to `std::boolalpha`:
```cpp
#include <iostream>

int main()
{
	bool b{};
	std::cout << "Enter a boolean value: ";

	// Allow the user to input 'true' or 'false' for boolean values
	// This is case-sensitive, so True or TRUE will not work
	std::cin >> std::boolalpha;
	std::cin >> b;

	// Let's also output bool values as `true` or `false`
	std::cout << std::boolalpha;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```

However, when `std::boolalpha` is enabled for input, numeric values will no longer be accepted (they evaluate to `false` and cause `std::cin` to enter failure mode).

#### Warning 
Enabling `std::boolalpha` for input will only allow lower-cased `false` or `true` to be accepted. Variations with capital letters will not be accepted. `0` and `1` will also no longer be accepted.

Note that we use `std::cin >> std::boolalpha;` to input bool values as `true` or `false`, and `std::cout << std::boolalpha;` to output bool values as `true` or `false`. These are independent controls that can be turned on (using `std::boolalpha`) or off (using `std::noboolalpha`) separately.

#### Boolean return values
Boolean values are often used as the return values for functions that check whether something is true or not. Such functions are typically named starting with the word _is_ (e.g. isEqual) or _has_ (e.g. hasCommonDivisor).

Boolean values take a little bit of getting used to, but once you get your mind wrapped around them, they’re quite refreshing in their simplicity! Boolean values are also a huge part of the language -- you’ll end up using them more than all the other fundamental types put together!

We’ll continue our exploration of Boolean values in the next lesson.

## 4.10 [Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/)
implement conditional behavior into our programs
The simplest kind of conditional statement in C++ is called an _if statement_. An **if statement** allows us to execute one (or more) lines of code only if some condition is true.
The simplest _if statement_ takes the following form:
`if (condition) true_statement;`

For readability, this is more often written as following:
```cpp
if (condition)
    true_statement;
```

A **condition** (also called a **conditional expression**) is an expression that evaluates to a Boolean value.

If the _condition_ of an _if statement_ evaluates to Boolean value _true_, then _true_statement_ is executed. If the _condition_ instead evaluates to Boolean value _false_, then _true_statement_ is skipped.

Warning
_If statements_ only conditionally execute a single statement. We talk about how to conditionally execute multiple statements in lesson [8.2 -- If statements and blocks](https://www.learncpp.com/cpp-tutorial/if-statements-and-blocks/).

```
if (condition)
    true_statement;
else
    false_statement;
```

```cpp
    if (x > 0)
        std::cout << "The value is positive\n";
    else if (x < 0)
        std::cout << "The value is negative\n";
    else
        std::cout << "The value is zero\n";
```

### Non-Boolean conditionals
What happens if your conditional is an expression that does not evaluate to a Boolean value?

In such a case, the result of the conditional expression is converted to a Boolean value: non-zero values get converted to Boolean `true`, and zero-values get converted to Boolean `false`.
Therefore, if we do something like this:
```cpp

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";
```
This will print `hi`, since `x` has value `4`, and `4` is a non-zero value that gets converted to Boolean `true`, causing the statement after the condition to execute.

Key insight : `if (x)` means “if x is non-zero/non-empty”.

#### If-statements and early returns
A return-statement that is not the last statement in a function is called an **early return**. Such a statement will cause the function to return to the caller when the return statement is executed (before the function would otherwise return to the caller, hence, “early”).

Historically, early returns were frowned upon. However, in modern programming they are more accepted, particularly when they can be used to make a function simpler, or are used to abort a function early due to some error condition.

Related content
We discuss the debate over early returns further in lesson [8.11 -- Break and continue](https://www.learncpp.com/cpp-tutorial/break-and-continue/)

We’ll continue our exploration of if-statements in future lesson [8.2 -- If statements and blocks](https://www.learncpp.com/cpp-tutorial/if-statements-and-blocks/).


```cpp
bool isPrime(int x)
{
    switch (x)
    {
        case 2: // if the user entered 2
        case 3: // or if the user entered 3
        case 5: // or if the user entered 5
        case 7: // or if the user entered 7
            return true; // then the digit is prime
    }

    return false; // otherwise the digit must not be prime
}
```



## 4.11 [Chars](https://www.learncpp.com/cpp-tutorial/chars/)
The **char** data type was designed to hold a single `character`. A **character** can be a single letter, number, symbol, or whitespace.

The char data type is an integral type, meaning the underlying value is stored as an integer. Similar to how a Boolean value `0` is interpreted as `false` and non-zero is interpreted as `true`, the integer stored by a `char` variable are interpreted as an `ASCII character`.

**ASCII** stands for American Standard Code for Information Interchange, and it defines a particular way to represent English characters (plus a few other symbols) as numbers between 0 and 127 (called an **ASCII code** or **code point**). For example, ASCII code 97 is interpreted as the character ‘a’.

Character literals are always placed between single quotes (e.g. ‘g’, ‘1’, ‘ ‘).

Here’s a full table of ASCII characters:

|Code|Symbol|Code|Symbol|Code|Symbol|Code|Symbol|
|---|---|---|---|---|---|---|---|
|0|NUL (null)|32|(space)|64|@|96|`|
|1|SOH (start of header)|33|!|65|A|97|a|
|2|STX (start of text)|34|”|66|B|98|b|
|3|ETX (end of text)|35|#|67|C|99|c|
|4|EOT (end of transmission)|36|$|68|D|100|d|
|5|ENQ (enquiry)|37|%|69|E|101|e|
|6|ACK (acknowledge)|38|&|70|F|102|f|
|7|BEL (bell)|39|’|71|G|103|g|
|8|BS (backspace)|40|(|72|H|104|h|
|9|HT (horizontal tab)|41|)|73|I|105|i|
|10|LF (line feed/new line)|42|*|74|J|106|j|
|11|VT (vertical tab)|43|+|75|K|107|k|
|12|FF (form feed / new page)|44|,|76|L|108|l|
|13|CR (carriage return)|45|-|77|M|109|m|
|14|SO (shift out)|46|.|78|N|110|n|
|15|SI (shift in)|47|/|79|O|111|o|
|16|DLE (data link escape)|48|0|80|P|112|p|
|17|DC1 (data control 1)|49|1|81|Q|113|q|
|18|DC2 (data control 2)|50|2|82|R|114|r|
|19|DC3 (data control 3)|51|3|83|S|115|s|
|20|DC4 (data control 4)|52|4|84|T|116|t|
|21|NAK (negative acknowledge)|53|5|85|U|117|u|
|22|SYN (synchronous idle)|54|6|86|V|118|v|
|23|ETB (end of transmission block)|55|7|87|W|119|w|
|24|CAN (cancel)|56|8|88|X|120|x|
|25|EM (end of medium)|57|9|89|Y|121|y|
|26|SUB (substitute)|58|:|90|Z|122|z|
|27|ESC (escape)|59|;|91|[|123|{|
|28|FS (file separator)|60|<|92|\|124|\||
|29|GS (group separator)|61|=|93|]|125|}|
|30|RS (record separator)|62|>|94|^|126|~|
|31|US (unit separator)|63|?|95|_|127|DEL (delete)|

Codes 0-31 and 127 are called the unprintable chars. These codes were designed to control peripheral devices such as printers (e.g. by instructing the printer how to move the print head). Most of these are obsolete now. If you try to print these chars, the results are dependent upon your OS (you may get some emoji-like characters).

Codes 32-126 are called the printable characters, and they represent the letters, number characters, and punctuation that most computers use to display basic English text.

If you try to print a character whose value is outside the range of ASCII, the results are also dependent upon your OS.

### Initializing chars
You can initialize char variables using character literals:
```cpp
char ch2{ 'a' }; // initialize with code point for 'a' (stored as integer 97) (preferred)
```

You can initialize chars with integers as well, but this should be avoided if possible
```cpp
char ch1{ 97 }; // initialize with integer 97 ('a') (not preferred)
```

#### Warning
Be careful not to mix up character numbers with integer numbers. The following two initialization are not the same:
```cpp
char ch{5}; // initialize with integer 5 (stored as integer 5)
char ch{'5'}; // initialize with code point for '5' (stored as integer 53)
```
Character numbers are intended to be used when we want to represent numbers as text, rather than as numbers to apply mathematical operations to.

### Printing chars

When using std::cout to print a char, std::cout outputs the char variable as an ASCII character:
```cpp
    char ch1{ 'a' }; // (preferred)
    std::cout << ch1; // cout prints character 'a'

    char ch2{ 98 }; // code point for 'b' (not preferred)
    std::cout << ch2; // cout prints a character ('b')
    std::cout << 'c';
```

#### Inputting chars
```cpp
    char ch{};
    std::cin >> ch;
```
Note that std::cin will let you enter multiple characters. However, variable _ch_ can only hold 1 character. Consequently, only the first input character is extracted into variable _ch_. The rest of the user input is left in the input buffer that std::cin uses, and can be extracted with subsequent calls to std::cin.

If you want to read in more than one char at a time (e.g. to read in a name, word, or sentence), you’ll want to use a string instead of a char. A string is a collection of sequential characters (and thus, a string can hold multiple symbols). We discuss this in upcoming lesson ([5.7 -- Introduction to std::string](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/)).

### Extracting whitespace characters
Because extracting input ignores leading whitespace, this can lead to unexpected results when trying to extract whitespace characters to a char variable:
```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

```
Input a keyboard character: a b
You entered: a
You entered: b
```
In the above example, we may have expected to extract the space, but because leading whitespace is skipped, we extracted the `b` character instead.

One simple way to address this is to use the `std::cin.get()` function to perform the extraction instead, as this function does not ignore leading whitespace:
```cpp
    std::cin.get(ch); // extracts space, leaves "b\n" in stream
```

###  Char size, range, and default sign
Char is defined by C++ to always be 1 byte in size. By default, a char may be signed or unsigned (though it’s usually signed). If you’re using chars to hold ASCII characters, you don’t need to specify a sign (since both signed and unsigned chars can hold values between 0 and 127).

If you’re using a char to hold small integers (something you should not do unless you’re explicitly optimizing for space), you should always specify whether it is signed or unsigned. A signed char can hold a number between -128 and 127. An unsigned char can hold a number between 0 and 255.

### Escape sequences
There are some sequences of characters in C++ that have special meaning. These characters are called **escape sequences**. An escape sequence starts with a ‘\’ (backslash) character, and then a following letter or number.

You’ve already seen the most common escape sequence: `'\n'`, which can be used to print a newline.
Another commonly used escape sequence is `'\t'`, which embeds a horizontal tab.

Three other notable escape sequences are:  
`\’` prints a single quote  
`\”` prints a double quote  
`\\` prints a backslash

Here’s a table of all of the escape sequences:

| Name            | Symbol      | Meaning                                                                                |
| --------------- | ----------- | -------------------------------------------------------------------------------------- |
| Alert           | \a          | Makes an alert, such as a beep                                                         |
| Backspace       | \b          | Moves the cursor back one space                                                        |
| Formfeed        | \f          | Moves the cursor to next logical page                                                  |
| Newline         | \n          | Moves cursor to next line                                                              |
| Carriage return | \r          | Moves cursor to beginning of line                                                      |
| Horizontal tab  | \t          | Prints a horizontal tab                                                                |
| Vertical tab    | \v          | Prints a vertical tab                                                                  |
| Single quote    | \’          | Prints a single quote                                                                  |
| Double quote    | \”          | Prints a double quote                                                                  |
| Backslash       | `\\`        | Prints a backslash.                                                                    |
| Question mark   | `\?`        | Prints a question mark.  <br>No longer relevant. You can use question marks unescaped. |
| Octal number    | `\(number)` | Translates into char represented by octal                                              |
| Hex number      | \x(number)  | Translates into char represented by hex number                                         |

```cpp
    std::cout << "6F in hex is char '\x6F'\n"; // 'o'
```
### Warning
Escape sequences start with a backslash (\), not a forward slash (/). If you use a forward slash by accident, it may still compile, but will not yield the desired result.
### What’s the difference between putting symbols in single and double quotes?
Text between single quotes is treated as a `char` literal, which represents a single character. For example, `'a'` represents the character `a`, `'+'` represents the character for the plus symbol, `'5'` represents the character `5` (not the number 5), and `'\n'` represents the newline character.

Text between double quotes (e.g. “Hello, world!”) is treated as a C-style string literal, which can contain multiple characters. We discuss strings in lesson [5.2 -- Literals](https://www.learncpp.com/cpp-tutorial/literals/).

### Best practice
Single characters should usually be single-quoted, not double-quoted (e.g. `'t'` or `'\n'`, not `"t"` or `"\n"`). One possible exception occurs when doing output, where it can be preferential to double quote everything for consistency (see lesson [1.5 -- Introduction to iostream: cout, cin, and endl](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/)).

### Avoid multicharacter literals
For backwards compatibility reasons, many C++ compilers support **multicharacter literals**, which are char literals that contain multiple characters (e.g. `'56'`). If supported, these have an implementation-defined value (meaning it varies depending on the compiler). Because they are not part of the C++ standard, and their value is not strictly defined, multicharacter literals should be avoided.
Best practice : Avoid multicharacter literals (e.g. `'56'`).
Multicharacter literal support often causes problems for new programmers when the forget whether escape sequences use forward slashes or backslashes:

Warning
Make sure that your newlines are using escape sequence `'\n'` , not multicharacter literal `'/n'`.

Key insight
Note that if we’d double-quoted the output `"/n"`, the program would have printed `3/n`, which is still wrong, but much less confusing.

Using double quotes when outputting character literals (instead of single quotes) either makes these kind of issues easier to discover or avoids them entirely.

### What about the other char types, `wchar_t`, `char8_t`, `char16_t`, and `char32_t`?
Much like ASCII maps the integers 0-127 to American English characters, other character encoding standards exist to map integers (of varying sizes) to characters in other languages. The most well-known mapping outside of ASCII is the Unicode standard, which maps over 144,000 integers to characters in many different languages. Because Unicode contains so many code points, a single Unicode code point needs 32-bits to represent a character (called UTF-32). However, Unicode characters can also be encoded using multiple 16-bit or 8-bit characters (called UTF-16 and UTF-8 respectively).

`char16_t` and `char32_t` were added to C++11 to provide explicit support for 16-bit and 32-bit Unicode characters. These char types have the same size as `std::uint_least16_t` and `std::uint_least32_t` respectively (but are distinct types). `char8_t` was added in C++20 to provide support for 8-bit Unicode (UTF-8). It is a distinct type that uses the same representation as `unsigned char`.

You won’t need to use `char8_t`, `char16_t`, or `char32_t` unless you’re planning on making your program Unicode compatible. `wchar_t` should be avoided in almost all cases (except when interfacing with the Windows API), as its size is implementation-defined.

Unicode and localization are generally outside the scope of these tutorials, so we won’t cover it further. In the meantime, you should only use ASCII characters when working with characters (and strings). Using characters from other character sets may cause your characters to display incorrectly.


## 4.12  [Introduction to type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/)
#### Implicit type conversion

```cpp
void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5); // what happens when we pass an int value?
```

In the above example, the `print()` function has a parameter of type `double` but the caller is passing in the value `5` which is of type `int`. What happens in this case?

In most cases, C++ will allow us to convert values of one fundamental type to another fundamental type. The process of converting data from one type to another type is called **type conversion**. Thus, the int argument `5` will be converted to double value `5.0` and then copied into parameter `x`. The `print()` function will print this value, resulting in the following output: `5`
A reminder By default, floating point values whose decimal part is 0 print without the decimal places (e.g. `5.0` prints as `5`).

When the compiler does type conversion on our behalf without us explicitly asking, we call this **implicit type conversion**. The above example illustrates this -- nowhere do we explicitly tell the compiler to convert integer value `5` to double value `5.0`. Rather, the function is expecting a double value, and we pass in an integer argument. The compiler will notice the mismatch and implicitly convert the integer to a double.

Here’s a similar example where our argument is an int variable instead of an int literal:
```cpp
void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	int y { 5 };
	print(y); // y is of type int
```
This works identically to the above. The value held by int variable `y` (`5`) will be converted to double value `5.0`, and then copied into parameter `x`.

### Type conversion of a value produces a new value
The type conversion process does not modify the value (or object) supplying the data to be converted. Instead, the conversion process uses that data as input, and produces the converted result.

Key insight
The type conversion of a value to another type of value behaves much like a call to a function whose return type matches the target type of the conversion. The data to be converted is passed in as an argument, and the converted result is returned (in a temporary object) to be used by the caller.

In the above example, the conversion does not change variable `y` from type `int` to `double` or the value of `y` from `5` to `5.0`. Instead, the conversion uses the value of `y` (`5`) as input, and returns a temporary object of type `double` with value `5.0`. This temporary object is then passed to function `print`.

For advanced readers
Some advanced type conversions (e.g. those involving `const_cast` or `reinterpret_cast`) do not return temporary objects, but instead reinterpret the type of an existing value or object.

### Implicit type conversion warnings
Although implicit type conversion is sufficient for most cases where type conversion is needed, there are a few cases where it is not. Consider the following program, which is similar to the example above:
```cpp

void print(int x) // print now takes an int parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5.5); // warning: we're passing in a double value
```

In this program, we’ve changed `print()` to take an `int` parameter, and the function call to `print()` is now passing in `double` value `5.5`. Similar to the above, the compiler will use implicit type conversion in order to convert double value `5.5` into a value of type `int`, so that it can be passed to function `print()`.

Unlike the initial example, when this program is compiled, your compiler will generate some kind of a warning about a possible loss of data. And because you have “treat warnings as errors” turned on (you do, right?), your compiler will abort the compilation process.

Tip
You’ll need to disable “treat warnings as errors” temporarily if you want to compile this example.

When compiled and run, this program prints the following: `5`

Note that although we passed in value `5.5`, the program printed `5`. Because integral values can’t hold fractions, when double value `5.5` is implicitly converted to an `int`, the fractional component is dropped, and only the integral value is retained.

Because converting a floating point value to an integral value results in any fractional component being dropped, the compiler will warn us when it does an implicit type conversion from a floating point to an integral value. This happens even if we were to pass in a floating point value with no fractional component, like `5.0` -- no actual loss of value occurs during the conversion to integral value `5` in this specific case, but the compiler may still warn us that the conversion is unsafe.


Key insight
Some type conversions (such as a `char` to an `int`) always preserve the value being converted, whereas others (such as `double` to `int`) may result in the value being changed during conversion. Unsafe implicit conversions will typically either generate a compiler warning, or (in the case of brace initialization) an error.
This is one of the primary reasons brace initialization is the preferred initialization form. Brace initialization will ensure we don’t try to initialize a variable with an initializer that will lose value when it is implicitly type converted:

```cpp
	double d { 5 }; // okay: int to double is safe
    int x { 5.5 }; // error: double to int not safe
```
Related content
Implicit type conversion is a meaty topic. We dig into this topic in more depth in future lessons, starting with lesson [10.1 -- Implicit type conversion](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/).
### Using static_cast to convert char to int
If we want to print the integral value instead of the char, we can do this by using `static_cast` to cast the value from a `char` to an `int`:
```cpp
    char ch{ 97 }; // 97 is ASCII code for 'a'
    // print value of variable ch as an int
    std::cout << ch << " has value " << static_cast<int>(ch) << '\n'; // a has value 97
```

It’s worth noting that the argument to _static_cast_ evaluates as an expression. When we pass in a variable, that variable is evaluated to produce its value, and that value is then converted to the new type. The variable itself is _not_ affected by casting its value to a new type. In the above case, variable `ch` is still a char, and still holds the same value even after we’ve cast its value to an `int`.


### Sign conversions using static_cast
Signed integral values can be converted to unsigned integral values, and vice-versa, using a static cast.

If the value being converted can be represented in the destination type, the converted value will remain unchanged (only the type will change). For example:
```cpp
	unsigned int u1 { 5 };
    // Convert value of u1 to a signed int
    int s1 { static_cast<int>(u1) };
    std::cout << s1 << '\n'; // prints 5
        
        
    int s2 { 5 };
    // Convert value of s2 to an unsigned int
    unsigned int u2 { static_cast<unsigned int>(s2) };
```
Since the value `5` is in the range of both a signed int and an unsigned int, the value `5` can be converted to either type without issue.

If the value being converted cannot be represented in the destination type:
- If the destination type is unsigned, the value will be modulo wrapped. We cover modulo wrapping in lesson [4.5 -- Unsigned integers, and why to avoid them](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/).
- If the destination type is signed, the value is implementation-defined prior to C++20, and will be modulo wrapped as of C++20.

Here’s an example of converting two values that are not representable in the destination type (assuming 32-bit integers):
```cpp
	int s { -1 };
    std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

    unsigned int u { 4294967295 }; // largest 32-bit unsigned int
    std::cout << static_cast<int>(u) << '\n'; // implementation-defined prior to C++20, -1 as of C++20
```
Signed int value `-1` cannot be represented as an unsigned int. The result modulo wraps to unsigned int value `4294967295`.
Unsigned int value `4294967295` cannot be represented as a signed int. Prior to C++20, the result is implementation defined (but will probably be `-1`). As of C++20, the result will modulo wrap to `-1`.

Warning
Converting an unsigned integral value to a signed integral value will result in implementation-defined behavior prior to C++20 if the value being converted can not be represented in the signed type.

### std::int8_t and std::uint8_t likely behave like chars instead of integers
As noted in lesson [4.6 -- Fixed-width integers and size_t](https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/), most compilers define and treat `std::int8_t` and `std::uint8_t` (and the corresponding fast and least fixed-width types) identically to types `signed char` and `unsigned char` respectively. Now that we’ve covered what chars are, we can demonstrate where this can be problematic:
```cpp
    std::int8_t myInt{65};      // initialize myInt with value 65
    std::cout << myInt << '\n'; // you're probably expecting this to print 65
```
Because `std::int8_t` describes itself as an int, you might be tricked into believing that the above program will print the integral value `65`. However, on most systems, this program will print `A` instead (treating `myInt` as a `signed char`). However, this is not guaranteed (on some systems, it may actually print `65`).

If you want to ensure that a `std::int8_t` or `std::uint8_t` object is treated as an integer, you can convert the value to an integer using `static_cast`:
```cpp
    std::cout << static_cast<int>(myInt) << '\n'; // will always print 65
```

In cases where `std::int8_t` is treated as a char, input from the console can also cause problems:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::cout << "Enter a number between 0 and 127: ";
    std::int8_t myInt{};
    std::cin >> myInt;

    std::cout << "You entered: " << static_cast<int>(myInt) << '\n';

    return 0;
}
```

A sample run of this program:

```
Enter a number between 0 and 127: 35
You entered: 51
```

Here’s what’s happening. When `std::int8_t` is treated as a char, the input routines interpret our input as a sequence of characters, not as an integer. So when we enter `35`, we’re actually entering two chars, `'3'` and `'5'`. Because a char object can only hold one character, the `'3'` is extracted (the `'5'` is left in the input stream for possible extraction later). Because the char `'3'` has ASCII code point 51, the value `51` is stored in `myInt`, which we then print later as an int.

In contrast, the other fixed-width types will always print and input as integral values.

## 4.x [Chapter 4 summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-4-summary-and-quiz/)
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