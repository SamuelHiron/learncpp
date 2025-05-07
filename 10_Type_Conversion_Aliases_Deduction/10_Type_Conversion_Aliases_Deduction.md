# 10_Type_Conversion_Aliases_Deduction

## 10.1 [Implicit type conversion](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/)
We introduced type conversion in lesson [4.12 -- Introduction to type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/). To recap the most important points from that lesson:

- The process of converting data from one type to another type is called “type conversion”.
- Implicit type conversion is performed automatically by the compiler when one data type is required, but a different data type is supplied.
- Explicit type conversion is requested by using a cast operator, such as `static_cast`.
- Conversions do not change the data being converted. Instead, the conversion process uses that data as input, and produces the converted result.
- When converting a value to another type of value, the conversion process produces a temporary object of the target type that holds the result of the conversion.

In the first half of this chapter, we’re going to dig a bit deeper into how type conversion works. We’ll start with implicit conversions in this lesson, and explicit type conversions (casting) in upcoming lesson [10.6 -- Explicit type conversion (casting) and static_cast](https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/). Since type conversion is used all over the place, having some understanding of what’s happening under the hood when a conversion is needed is important. This knowledge is also relevant when for understanding how overloaded functions (functions that can have the same name as other functions) work.

#### Author’s note
In this chapter, we’ll focus on the conversion of values to other types of values. We’ll cover other types of conversions once we introduce the prerequisite topics (such as pointers, references, inheritance, etc…).

### Why conversions are needed

The value of an object is stored as a sequence of bits, and the data type of the object tells the compiler how to interpret those bits into meaningful values. Different data types may represent the “same” value differently. For example, the integer value `3` might be stored as binary `0000 0000 0000 0000 0000 0000 0000 0011`, whereas floating point value `3.0` might be stored as binary `0100 0000 0100 0000 0000 0000 0000 0000`.

So what happens when we do something like this?

```cpp
float f{ 3 }; // initialize floating point variable with int 3
```

In such a case, the compiler can’t just copy the bits used to represent `int` value `3` into the memory allocated for `float` variable `f`. If it were to do so, then when `f` (which has type `float`) was evaluated, those bits would be interpreted as a `float` rather than an `int`, and who knows what `float` value we’d end up with!
#### As an aside…
The following program actually prints `int` value `3` as if it were a `float`:
```cpp
#include <iostream>
#include <cstring>

int main()
{
    int n { 3 };                        // here's int value 3
    float f {};                         // here's our float variable
    std::memcpy(&f, &n, sizeof(float)); // copy the bits from n into f
    std::cout << f << '\n';             // print f (containing the bits from n)

    return 0;
}
```
This produces the following result:
`4.2039e-45`

Instead, the integer value `3` needs to be converted into the equivalent floating point value `3.0`, which can then be stored in the memory allocated for `f` (using the bit representation for `float` value `3.0`) .

### When implicit type conversion happens

**Implicit type conversion** (also called **automatic type conversion** or **coercion**) is performed automatically by the compiler when an expression of some type is supplied in a context where some other type is expected. The vast majority of type conversions in C++ are implicit type conversions. For example, implicit type conversion happens in all of the following cases:

When initializing (or assigning a value to) a variable with a value of a different data type:
```cpp
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double
```

When the type of a return value is different from the function’s declared return type:
```cpp
float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}
```

When using certain binary operators with operands of different types:
```cpp
double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
```

When using a non-Boolean value in an if-statement:
```cpp
if (5) // int value 5 implicitly converted to type bool
{
}
```

When an argument passed to a function is a different type than the function parameter:
```cpp
void doSomething(long l)
{
}

doSomething(3); // int value 3 implicitly converted to type long
```

So how does the compiler know how to convert a value to a different type anyway?

### The standard conversions
As part of the core language, the C++ standard defines a collection of conversion rules known as the “standard conversions”. The **standard conversions** specify how various fundamental types (and certain compound types, including arrays, references, pointers, and enumerations) convert to other types within that same group.

As of C++23, there are 14 different standard conversions. These can be roughly grouped into 5 general categories:

|Category|Meaning|Link|
|---|---|---|
|Numeric promotions|Conversions of small integral types to `int` or `unsigned int`, and of `float` to `double`.|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric conversions|Other integral and floating point conversions that aren’t promotions.|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Qualification conversions|Conversions that add or remove `const` or `volatile`.||
|Value transformations|Conversions that change the value category of an expression|[12.2 -- Value categories (lvalues and rvalues)](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)|
|Pointer conversions|Conversions from `std::nullptr` to pointer types, or pointer types to other pointer types||
For example, converting an `int` value to a `float` value falls under the numeric conversions category, so the compiler to perform such a conversion, the compiler simply need apply the `int` to `float` numeric conversion rules.

The numeric conversions and numeric promotions are the most important of these categories, and we’ll cover them in more detail in upcoming lessons.

#### For advanced readers
Here is the full list of standard conversions:

|Category|Standard Conversion|Description|Also See|
|---|---|---|---|
|Value transformation|Lvalue-to-rvalue|Converts lvalue expression to rvalue expression|[12.2 -- Value categories (lvalues and rvalues)](https://www.learncpp.com/cpp-tutorial/value-categories-lvalues-and-rvalues/)|
|Value transformation|Array-to-pointer|Converts C-style array to pointer to first array element (a.k.a. array decay)|[17.8 -- C-style array decay](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)|
|Value transformation|Function-to-pointer|Converts function to function pointer|[20.1 -- Function Pointers](https://www.learncpp.com/cpp-tutorial/function-pointers/)|
|Value transformation|Temporary materialization|Converts value to temporary object||
|Qualification conversion|Qualification conversion|Adds or removes `const` or `volatile` from types||
|Numeric promotions|Integral promotions|Converts smaller integral types to `int` or `unsigned int`|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric promotions|Floating point promotions|Converts `float` to `double`|[10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)|
|Numeric conversions|Integral conversions|Integral conversions that aren’t integral promotions|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Floating point conversions|Floating point conversions that aren’t floating point promotions|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Integral-floating conversions|Converts integral and floating point types|[10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)|
|Numeric conversions|Boolean conversions|Converts integral, unscoped enumeration, pointer, or pointer-to-memver to bool|[4.10 -- Introduction to if statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/)|
|Pointer conversions|Pointer conversions|Converts `std::nullptr` to pointer, or pointer to void pointer or base class||
|Pointer conversions|Pointer-to-member conversions|Converts `std::nullptr` to pointer-to-member  <br>or pointer-to-member of base class to pointer-to-member of derived class||
|Pointer conversions|Function pointer conversions|Converts pointer-to-noexcept-function to pointer-to-function||

### Type conversion can fail

When a type conversion is invoked (whether implicitly or explicitly), the compiler will determine whether it can convert the value from the current type to the desired type. If a valid conversion can be found, then the compiler will produce a new value of the desired type.

If the compiler can’t find an acceptable conversion, then the compilation will fail with a compile error. Type conversions can fail for any number of reasons. For example, the compiler might not know how to convert a value between the original type and the desired type.

For example:
```cpp
int main()
{
    int x { "14" };

    return 0;
}
```

The because there isn’t a standard conversion from the string literal “14” to `int`, the compiler will produce an error. For example, GCC produces the error: `prog.cc:3:13: error: invalid conversion from 'const char*' to 'int' [-fpermissive]`.

In other cases, specific features may disallow some categories of conversions. For example:
```cpp
int x { 3.5 }; // brace-initialization disallows conversions that result in data loss
```
Even though the compiler knows how to convert a `double` value to an `int` value, narrowing conversions are disallowed when using brace-initialization.

There are also cases where the compiler may not be able to figure out which of several possible type conversions is the best one to use. We’ll see examples of this in lesson [11.3 -- Function overload resolution and ambiguous matches](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/).

The full set of rules describing how type conversions work is both lengthy and complicated, and for the most part, type conversion “just works”. In the next set of lessons, we’ll cover the most important things you need to know about the standard conversions. If finer detail is required for some uncommon case, the full rules are detailed in [technical reference documentation for implicit conversions](https://en.cppreference.com/w/cpp/language/implicit_conversion).

Let’s get to it!

## 10.2 [Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)
In lesson [4.3 -- Object sizes and the sizeof operator](https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/), we noted that C++ has minimum size guarantees for each of the fundamental types. However, the actual size of these types can vary based on the compiler and architecture.

This variability was allowed so that the `int` and `double` data types could be set to the size that maximizes performance on a given architecture. For example, a 32-bit computer will typically be able to process 32-bits of data at a time. In such cases, an `int` would likely be set to a width of 32-bits, since this is the “natural” size of the data that the CPU operates on (and likely to be the most performant).

#### A reminder
The number of bits a data type uses is called its width. A wider data type is one that uses more bits, and a narrower data type is one that uses less bits.

But what happens when we want our 32-bit CPU to modify an 8-bit value (such as a `char`) or a 16-bit value? Some 32-bit processors (such as 32-bit x86 CPUs) can manipulate 8-bit or 16-bit values directly. However, doing so is often slower than manipulating 32-bit values! Other 32-bit CPUs (like 32-bit PowerPC CPUs), can only operate on 32-bit values, and additional tricks must be employed to manipulate narrower values.
### Numeric promotion
Because C++ is designed to be portable and performant across a wide range of architectures, the language designers did not want to assume a given CPU would be able to efficiently manipulate values that were narrower than the natural data size for that CPU.

To help address this challenge, C++ defines a category of type conversions informally called the `numeric promotions`. A **numeric promotion** is the type conversion of certain narrower numeric types (such as a `char`) to certain wider numeric types (typically `int` or `double`) that can be processed efficiently.

All numeric promotions are value-preserving. A **value-preserving conversion** (also called a **safe conversion**) is one where every possible source value can be converted into an equal value of the destination type.

Because promotions are safe, the compiler will freely use numeric promotion as needed, and will not issue a warning when doing so.

### Numeric promotion reduces redundancy
Numeric promotion solves another problem as well. Consider the case where you wanted to write a function to print a value of type `int`:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

While this is straightforward, what happens if we want to also be able to print a value of type `short`, or type `char`? If type conversions did not exist, we’d have to write a different print function for `short` and another one for `char`. And don’t forget another version for `unsigned char`, `signed char`, `unsigned short`, `wchar_t`, `char8_t`, `char16_t`, and `char32_t`! You can see how this quickly becomes unmanageable.

Numeric promotion comes to the rescue here: we can write functions that have `int` and/or `double` parameters (such as the `printInt()` function above). That same code can then be called with arguments of types that can be numerically promoted to match the types of the function parameters.

### Numeric promotion categories
The numeric promotion rules are divided into two subcategories: `integral promotions` and `floating point promotions`. Only the conversions listed in these categories are considered to be numeric promotions.
### Floating point promotions
We’ll start with the easier one.
Using the **floating point promotion** rules, a value of type `float` can be converted to a value of type `double`.

This means we can write a function that takes a `double` and then call it with either a `double` or a `float` value:
```cpp
#include <iostream>

void printDouble(double d)
{
    std::cout << d << '\n';
}

int main()
{
    printDouble(5.0); // no conversion necessary
    printDouble(4.0f); // numeric promotion of float to double

    return 0;
}
```
In the second call to `printDouble()`, the `float` literal `4.0f` is promoted into a `double`, so that the type of argument matches the type of the function parameter.


### Integral promotions

The integral promotion rules are more complicated.

Using the **integral promotion** rules, the following conversions can be made:
- signed char or signed short can be converted to int.
- unsigned char, char8_t, and unsigned short can be converted to int if int can hold the entire range of the type, or unsigned int otherwise.
- If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.
- bool can be converted to int, with false becoming 0 and true becoming 1.

Assuming an 8 bit byte and an `int` size of 4 bytes or larger (which is typical these days), the above basically means that `bool`, `char`, `signed char`, `unsigned char`, `signed short`, and `unsigned short` all get promoted to `int`.

There are a few other integral promotion rules that are used less often. These can be found at [https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion](https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion).

In most cases, this lets us write a function taking an `int` parameter, and then use it with a wide variety of other integral types. For example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}
```

There are two things worth noting here. First, on some architectures (e.g. with 2 byte ints) it is possible for some of the unsigned integral types to be promoted to `unsigned int` rather than `int`.

Second, some narrower unsigned types (such as `unsigned char`) may be promoted to larger signed types (such as `int`). So while integral promotion is value-preserving, it does not necessarily preserve the signedness (signed/unsigned) of the type.
### Not all widening conversions are numeric promotions
Some widening type conversions (such as `char` to `short`, or `int` to `long`) are not considered to be numeric promotions in C++ (they are `numeric conversions`, which we’ll cover shortly in lesson [10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)). This is because such conversions do not assist in the goal of converting smaller types to larger types that can be processed more efficiently.

The distinction is mostly academic. However, in certain cases, the compiler will favor numeric promotions over numeric conversions. We’ll see examples where this makes a difference when we cover function overload resolution (in upcoming lesson [11.3 -- Function overload resolution and ambiguous matches](https://www.learncpp.com/cpp-tutorial/function-overload-resolution-and-ambiguous-matches/)).


## 10.3 [Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)
In the previous lesson ([10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)), we covered numeric promotions, which are conversions of specific narrower numeric types to wider numeric types (typically `int` or `double`) that can be processed efficiently.

C++ supports another category of numeric type conversions, called **numeric conversions**. These numeric conversions cover additional type conversions between fundamental types.
#### Key insight

Any type conversion covered by the numeric promotion rules ([10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)) is called a numeric promotion, not a numeric conversion.

There are five basic types of numeric conversions.

1. Converting an integral type to any other integral type (excluding integral promotions):
```cpp
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int
```

2. Converting a floating point type to any other floating point type (excluding floating point promotions):
```cpp
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting a floating point type to any integral type:
```cpp
int i = 3.5; // convert double to int
```

4. Converting an integral type to any floating point type:
```cpp
double d = 3; // convert int to double
```

5. Converting an integral type or a floating point type to a bool:
```cpp
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```
#### As an aside…
Because brace initialization strictly disallows some types of numeric conversions (more on this next lesson), we use copy initialization in this lesson (which does not have any such limitations) in order to keep the examples simple.

### Safe and unsafe conversions

Unlike numeric promotions (which are always value-preserving and thus “safe”), many numeric conversions are unsafe. An **unsafe conversion** is one where at least one value of the source type cannot be converted into an equal value of the destination type.

Numeric conversions fall into three general safety categories:
1. _Value-preserving conversions_ are safe numeric conversions where the destination type can exactly represent all possible values in the source type.

For example, `int` to `long` and `short` to `double` are safe conversions, as the source value can always be converted to an equal value of the destination type.
```cpp
int main()
{
    int n { 5 };
    long l = n; // okay, produces long value 5

    short s { 5 };
    double d = s; // okay, produces double value 5.0

    return 0;
}
```
Compilers will typically not issue warnings for implicit value-preserving conversions.

A value converted using a value-preserving conversion can always be converted back to the source type, resulting in a value that is equivalent to the original value:
```cpp
#include <iostream>

int main()
{
    int n = static_cast<int>(static_cast<long>(3)); // convert int 3 to long and back
    std::cout << n << '\n';                         // prints 3

    char c = static_cast<char>(static_cast<double>('c')); // convert 'c' to double and back
    std::cout << c << '\n';                               // prints 'c'

    return 0;
}
```

2. _Reinterpretive conversions_ are unsafe numeric conversions where the converted value may be different than the source value, but no data is lost. Signed/unsigned conversions fall into this category.

For example, when converting a `signed int` to an `unsigned int`:
```cpp
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```

In the case of `u1`, the signed int value `5` is converted to unsigned int value `5`. Thus, the value is preserved in this case.

In the case of `u2`, the signed int value `-5` is converted to an unsigned int. Since an unsigned int can’t represent negative numbers, the result will be modulo wrapped to a large integral value that is outside the range of a signed int. The value is not preserved in this case.

Such value changes are typically undesirable, and will often cause the program to exhibit unexpected or implementation-defined behavior.
#### Related content
We discuss how out-of-range values are converted between signed and unsigned types in lesson [4.12 -- Introduction to type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/).

#### Warning

Even though reinterpretive conversions are unsafe, most compilers leave implicit signed/unsigned conversion warnings disabled by default.

This is because in some areas of modern C++ (such as when working with standard library arrays), signed/unsigned conversions can be hard to avoid. And practically speaking, the majority of such conversions do not actually result in a value change. Therefore, enabling such warnings can lead to many spurious warnings for signed/unsigned conversions that are actually okay (drowning out legitimate warnings).

If you choose to leave such warnings disabled, be extra careful of inadvertent conversions between these types (particularly when passing an argument to a function taking a parameter of the opposite sign).

Values converted using a reinterpretive conversion can be converted back to the source type, resulting in a value equivalent to the original value (even if the initial conversion produced a value out of range of the source type). As such, reinterpretive conversions do not lose data during the conversion process.

```cpp
#include <iostream>

int main()
{
    int u = static_cast<int>(static_cast<unsigned int>(-5)); // convert '-5' to unsigned and back
    std::cout << u << '\n'; // prints -5

    return 0;
}
```
#### For advanced readers
Prior to C++20, converting an unsigned value that is out-of-range of the signed value is technically implementation-defined behavior (due to the allowance that signed integers could use a different binary representation than unsigned integers). In practice, this was a non-issue on modern system.

C++20 now requires that signed integers use 2s complement. As a result, the conversion rules were changed so that the above is now well-defined as a reinterpretive conversion (an out-of-range conversion will produce modulo wrapping).

Note that while such conversions are well defined, signed arithmetic overflow (which occurs when an arithmetic operation produces a value outside the range that can be stored) is still undefined behavior.

3. _Lossy conversions_ are unsafe numeric conversions where data may be lost during the conversion.

For example, `double` to `int` is a conversion that may result in data loss:

```cpp
int i = 3.0; // okay: will be converted to int value 3 (value preserved)
int j = 3.5; // data lost: will be converted to int value 3 (fractional value 0.5 lost)
```

Conversion from `double` to `float` can also result in data loss:

```cpp
float f = 1.2;        // okay: will be converted to float value 1.2 (value preserved)
float g = 1.23456789; // data lost: will be converted to float 1.23457 (precision lost)
```

Converting a value that has lost data back to the source type will result in a value that is different than the original value:

```cpp
#include <iostream>

int main()
{
    double d { static_cast<double>(static_cast<int>(3.5)) }; // convert double 3.5 to int and back
    std::cout << d << '\n'; // prints 3

    double d2 { static_cast<double>(static_cast<float>(1.23456789)) }; // convert double 1.23456789 to float and back
    std::cout << d2 << '\n'; // prints 1.23457

    return 0;
}
```

For example, if `double` value `3.5` is converted to `int` value `3`, the fractional component `0.5` is lost. When `3` is converted back to a `double,` the result is `3.0`, not `3.5`.

Compilers will generally issue a warning (or in some cases, an error) when an implicit lossy conversion would be performed at runtime.

#### Warning
Some conversions may fall into different categories depending on the platform.

For example, `int` to `double` is typically a safe conversion, because `int` is usually 4 bytes and `double` is usually 8 bytes, and on such systems, all possible `int` values can be represented as a `double`. However, there are architectures where both `int` and `double` are 8 bytes. On such architectures, `int` to `double` is a lossy conversion!

We can demonstrate this by casting a long long value (which must be at least 64 bits) to double and back:

```cpp
#include <iostream>

int main()
{
    std::cout << static_cast<long long>(static_cast<double>(10000000000000001LL));

    return 0;
}
```

This prints:

`10000000000000000`

Note that our last digit has been lost!

Unsafe conversions should be avoided as much as possible. However, this is not always possible. When unsafe conversions are used, it is most often when:
- We can constrain the values to be converted to just those that can be converted to equal values. For example, an `int` can be safely converted to an `unsigned int` when we can guarantee that the `int` is non-negative.
- We don’t mind that some data is lost because it is not relevant. For example, converting an `int` to a `bool` results in the loss of data, but we’re typically okay with this because we’re just checking if the `int` has value `0` or not.

### More on numeric conversions

The specific rules for numeric conversions are complicated and numerous, so here are the most important things to remember.

- In _all_ cases, converting a value into a type whose range doesn’t support that value will lead to results that are probably unexpected. For example:
```cpp
int main()
{
    int i{ 30000 };
    char c = i; // chars have range -128 to 127

    std::cout << static_cast<int>(c) << '\n';

    return 0;
}
```
In this example, we’ve assigned a large integer to a variable with type `char` (that has range -128 to 127). This causes the char to overflow, and produces an unexpected result:
`48`

- Remember that overflow is well-defined for unsigned values and produces undefined behavior for signed values.
- Converting from a larger integral or floating point type to a smaller type from the same family will generally work so long as the value fits in the range of the smaller type. For example:
```cpp
int i{ 2 };
short s = i; // convert from int to short
std::cout << s << '\n';

double d{ 0.1234 };
float f = d;
std::cout << f << '\n';
```

This produces the expected result:
```
2
0.1234
```

- In the case of floating point values, some rounding may occur due to a loss of precision in the smaller type. For example:

```cpp
float f = 0.123456789; // double value 0.123456789 has 9 significant digits, but float can only support about 7
std::cout << std::setprecision(9) << f << '\n'; // std::setprecision defined in iomanip header
```

In this case, we see a loss of precision because the `float` can’t hold as much precision as a `double`:
`0.123456791`

- Converting from an integer to a floating point number generally works as long as the value fits within the range of the floating point type. For example:
```cpp
int i{ 10 };
float f = i;
std::cout << f << '\n';
```

This produces the expected result:
`10`

- Converting from a floating point to an integer works as long as the value fits within the range of the integer, but any fractional values are lost. For example:
```cpp
int i = 3.5;
std::cout << i << '\n';
```
In this example, the fractional value (.5) is lost, leaving the following result:
`3`

While the numeric conversion rules might seem scary, in reality the compiler will generally warn you if you try to do something dangerous (excluding some signed/unsigned conversions).

## 10.4 [Narrowing conversions, list initialization, and constexpr initializers](https://www.learncpp.com/cpp-tutorial/narrowing-conversions-list-initialization-and-constexpr-initializers/)
In the previous lesson ([10.3 -- Numeric conversions](https://www.learncpp.com/cpp-tutorial/numeric-conversions/)), we covered numeric conversions, which cover a wide range of different type conversions between fundamental types.

###  Narrowing conversions
In C++, a **narrowing conversion** is a potentially unsafe numeric conversion where the destination type may not be able to hold all the values of the source type.

The following conversions are defined to be narrowing:
- From a floating point type to an integral type.
- From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range of the destination type (even if the destination type doesn’t have the precision to store all the significant digits of the number).
- From an integral to a floating point type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.
- From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type. This covers both wider to narrower integral conversions, as well as integral sign conversions (signed to unsigned, or vice-versa).

In most cases, implicit narrowing conversions will result in compiler warnings, with the exception of signed/unsigned conversions (which may or may not produce warnings, depending on how your compiler is configured).

Narrowing conversions should be avoided as much as possible, because they are potentially unsafe, and thus a source of potential errors.

#### Best practice
Because they can be unsafe and are a source of errors, avoid narrowing conversions whenever possible.
### Make intentional narrowing conversions explicit
Narrowing conversions are not always avoidable -- this is particularly true for function calls, where the function parameter and argument may have mismatched types and require a narrowing conversion.

In such cases, it is a good idea to convert an implicit narrowing conversion into an explicit narrowing conversion using `static_cast`. Doing so helps document that the narrowing conversion is intentional, and will suppress any compiler warnings or errors that would otherwise result.

For example:
```cpp
void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated

    return 0;
}
```

#### Best practice
If you need to perform a narrowing conversion, use `static_cast` to convert it into an explicit conversion.

### Brace initialization disallows narrowing conversions
Narrowing conversions are disallowed when using brace initialization (which is one of the primary reasons this initialization form is preferred), and attempting to do so will produce a compile error.

For example:
```cpp
int main()
{
    int i { 3.5 }; // won't compile

    return 0;
}
```

If you actually want to do a narrowing conversion inside a brace initialization, use `static_cast` to convert the narrowing conversion into an explicit conversion:
```cpp
int main()
{
    double d { 3.5 };

    // static_cast<int> converts double to int, initializes i with int result
    int i { static_cast<int>(d) };

    return 0;
}
```



### Some constexpr conversions aren’t considered narrowing

When the source value of a narrowing conversion isn’t known until runtime, the result of the conversion also can’t be determined until runtime. In such cases, whether the narrowing conversion preserves the value or not also can’t be determined until runtime. For example:
```cpp
#include <iostream>

void print(unsigned int u) // note: unsigned
{
    std::cout << u << '\n';
}

int main()
{
    std::cout << "Enter an integral value: ";
    int n{};
    std::cin >> n; // enter 5 or -5
    print(n);      // conversion to unsigned may or may not preserve value

    return 0;
}
```

In the above program, the compiler has no idea what value will be entered for `n`. When `print(n)` is called, the conversion from `int` to `unsigned int` will be performed at that time, and the results may be value-preserving or not depending on what value for `n` was entered. Thus, a compiler that has signed/unsigned warnings enabled will issue a warning for this case.

However, you may have noticed that most of the narrowing conversions definitions have an exception clause that begins with “unless the value being converted is constexpr and …”. For example, a conversion is narrowing when it is “From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.”

When the source value of a narrowing conversion is constexpr, the specific value to be converted must be known to the compiler. In such cases, the compiler can perform the conversion itself, and then check whether the value was preserved. If the value was not preserved, the compiler can halt compilation with an error. If the value is preserved, the conversion is not considered to be narrowing (and the compiler can replace the entire conversion with the converted result, knowing that doing so is safe).

For example:
```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```

Let’s apply the rule “From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type” to both of the conversions above.

In the case of `n1` and `u1`, `n1` is an `int` and `u1` is an `unsigned int`, so this is a conversion from an integral type to another integral type that cannot represent all values of the original type. However, `n1` is constexpr, and its value `5` can be represented exactly in the destination type (as unsigned value `5`). Therefore, this is not considered to be a narrowing conversion, and we are allowed to list initialize `u1` using `n1`.

In the case of `n2` and `u2`, things are similar. Although `n2` is constexpr, its value `-5` cannot be represented exactly in the destination type, so this is considered to be a narrowing conversion, and because we are doing list initialization, the compiler will error and halt the compilation.

Strangely, conversions from a floating point type to an integral type do not have a constexpr exclusion clause, so these are always considered narrowing conversions even when the value to be converted is constexpr and fits in the range of the destination type:
```cpp
int n { 5.0 }; // compile error: narrowing conversion
```

Even more strangely, conversions from a constexpr floating point type to a narrower floating point type are not considered narrowing even when there is a loss of precision!
```cpp
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results
```

#### Warning
Conversion from a constexpr floating point type to a narrower floating point type is not considered narrowing even when a loss of precision results.
### List initialization with constexpr initializers
These constexpr exception clauses are incredibly useful when list initializing non-int/non-double objects, as we can use an int or double literal (or a constexpr object) initialization value.

This allows us to avoid:
- Having to use literal suffixes in most cases
- Having to clutter our initializations with a static_cast

For example:
```cpp
int main()
{
    // We can avoid literals with suffixes
    unsigned int u { 5 }; // okay (we don't need to use `5u`)
    float f { 1.5 };      // okay (we don't need to use `1.5f`)

    // We can avoid static_casts
    constexpr int n{ 5 };
    double d { n };       // okay (we don't need a static_cast here)
    short s { 5 };        // okay (there is no suffix for short, we don't need a static_cast here)

    return 0;
}
```

This also works with copy and direct initialization.

One caveat worth mentioning: initializing a narrower or lesser ranked floating point type with a constexpr value is allowed as long as the value is in range of the destination type, even if the destination type doesn’t have enough precision to precisely store the value!
#### Key insight
Floating point types are ranked in this order (greater to lesser):
- Long double
- Double
- Float

Therefore, something like this is legal and will not emit an error:
```cpp
int main()
{
    float f { 1.23456789 }; // not a narrowing conversion, even though precision lost!

    return 0;
}
```
However, your compiler may still issue a warning in this case (GCC and Clang do if you use the -Wconversion compile flag).
## 10.5 [Arithmetic conversions](https://www.learncpp.com/cpp-tutorial/arithmetic-conversions/)

In lesson [6.1 -- Operator precedence and associativity](https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/), we discussed how expressions are evaluated according to the precedence and associativity of their operators.

Consider the following expression:
```cpp
int x { 2 + 3 };
```

Binary `operator+` is given two operands, both of type `int`. Because both operands are of the same type, that type will be used to perform the calculation, and the value returned will also be of this same type. Thus, `2 + 3` will evaluate to `int` value `5`.

But what happens when the operands of a binary operator are of different types?
```cpp
??? y { 2 + 3.5 };
```

In this case, `operator+` is being given one operand of type `int` and another of type `double`. Should the result of the operator be returned as an `int`, a `double`, or possibly something else altogether?

In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with operands of different types, one or both of the operands will be implicitly converted to matching types using a set of rules called the **usual arithmetic conversions**. The matching type produced as a result of the usual arithmetic conversion rules is called the **common type** of the operands.

### The operators that require operands of the same type

The following operators require their operands to be of the same type:

- The binary arithmetic operators: +, -, *, /, %
- The binary relational operators: `<, >, <=, >=, ==, !=`
- The binary bitwise arithmetic operators: &, ^, |
- The conditional operator ?: (excluding the condition, which is expected to be of type `bool`)

#### For advanced readers
Overloaded operators are not subject to the usual arithmetic conversion rules.

### The usual arithmetic conversion rules

The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list of types that looks something like this:
- long double (highest rank)
- double
- float
- long long
- long
- int (lowest rank)

The following rules are applied to find a matching type:

Step 1:
- If one operand is an integral type and the other a floating point type, the integral operand is converted to the type of the floating point operand (no integral promotion takes place).
- Otherwise, any integral operands are numerically promoted (see [10.2 -- Floating-point and integral promotion](https://www.learncpp.com/cpp-tutorial/floating-point-and-integral-promotion/)).

Step 2:
- After promotion, if one operand is signed and the other unsigned, special rules apply (see below)
- Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.

#### For advanced readers
The special matching rules for integral operands with different signs:
- If the rank of the unsigned operand is greater than or equal to the rank of the signed operand, the signed operand is converted to the type of the unsigned operand.
- If the type of the signed operand can represent all the values of the type of the unsigned operand, the type of the unsigned operand is converted to the type of the signed operand.
- Otherwise both operands are converted to the corresponding unsigned type of the signed operand.
#### Related content
You can find the full rules for the usual arithmetic conversions [here](https://en.cppreference.com/w/cpp/language/usual_arithmetic_conversions).

### Some examples

In the following examples, we’ll use the `typeid` operator (included in the `<typeinfo>` header), to show the resulting type of an expression.

First, let’s add an `int` and a `double`:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    int i{ 2 };
    std::cout << typeid(i).name() << '\n'; // show us the name of the type for i

    double d{ 3.5 };
    std::cout << typeid(d).name() << '\n'; // show us the name of the type for d

    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}
```
In this case, the `double` operand has the highest priority, so the lower priority operand (of type `int`) is type converted to `double` value `2.0`. Then `double` values `2.0` and `3.5` are added to produce `double` result `5.5`.

On the author’s machine, this prints:
```
int
double
double 5.5
```
Note that your compiler may display something slightly different, as the names output by `typeid.name()` are implementation-specific.

Now let’s add two values of type `short`:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```
Because neither operand appears on the priority list, both operands undergo integral promotion to type `int`. The result of adding two `ints` is an `int`, as you would expect:
`int 9`

### Signed and unsigned issues
This prioritization hierarchy and conversion rules can cause some problematic issues when mixing signed and unsigned values. For example, take a look at the following code:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer

    return 0;
}
```
You might expect the expression `5u - 10` to evaluate to `-5` since `5 - 10` = `-5`. But here’s what actually results:
`unsigned int 4294967291`

Due to the conversion rules, the `int` operand is converted to an `unsigned int`. And since the value `-5` is out of range of an `unsigned int`, we get a result we don’t expect.

Here’s another example showing a counterintuitive result:
```cpp
#include <iostream>

int main()
{
    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
```
While it’s clear to us that `5` is greater than `-3`, when this expression evaluates, `-3` is converted to a large `unsigned int` that is larger than `5`. Thus, the above prints `false` rather than the expected result of `true`.

This is one of the primary reasons to avoid unsigned integers -- when you mix them with signed integers in arithmetic expressions, you’re at risk for unexpected results. And the compiler probably won’t even issue a warning.

### `std::common_type` and `std::common_type_t`
In future lessons, we’ll encounter cases where it is useful to know what the common type of two type is. `std::common_type` and the useful type alias `std::common_type_t` (both defined in the <type_traits> header) can be used for just this purpose.

For example, `std::common_type_t<int, double>` returns the common type of `int` and `double`, and `std::common_type_t<unsigned int, long>` returns the common type of `unsigned int` and `long`.

We’ll show an example where this is useful in lesson [11.8 -- Function templates with multiple template types](https://www.learncpp.com/cpp-tutorial/function-templates-with-multiple-template-types/).

## 10.6 [Explicit type conversion (casting) and static_cast](https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/)
In lesson [10.1 -- Implicit type conversion](https://www.learncpp.com/cpp-tutorial/implicit-type-conversion/), we discussed that the compiler can use implicit type conversion to convert a value from one data type to another. When you want to numerically promote a value from one data type to a wider data type, using implicit type conversion is fine.

Many new C++ programmers try something like this:
```cpp
double d = 10 / 4; // does integer division, initializes d with value 2.0
```

Because `10` and `4` are both of type `int`, integer division is performed, and the expression evaluates to `int` value `2`. This value then undergoes numeric conversion to `double` value `2.0` before being used to initialize variable `d`. Most likely, this isn’t what was intended.

In the case where you are using literal operands, replacing one or both of the integer literals with double literals will cause floating point division to happen instead:

```cpp
double d = 10.0 / 4.0; // does floating point division, initializes d with value 2.5
```

But what if you are using variables instead of literals? Consider this case:
```cpp
int x { 10 };
int y { 4 };
double d = x / y; // does integer division, initializes d with value 2.0
```

Because integer division is used here, variable `d` will end up with the value of `2.0`. How do we tell the compiler that we want to use floating point division instead of integer division in this case? Literal suffixes can’t be used with variables. We need some way to convert one (or both) of the variable operands to a floating point type, so that floating point division will be used instead.

Fortunately, C++ comes with a number of different **type casting operators** (more commonly called **casts**) that can be used by the programmer to have the compiler perform type conversion. Because casts are explicit requests by the programmer, this form of type conversion is often called an **explicit type conversion** (as opposed to implicit type conversion, where the compiler performs a type conversion automatically).
### Type casting
C++ supports 5 different types of casts: `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`, and C-style casts. The first four are sometimes referred to as **named casts**.

#### For advanced readers

|Cast|Description|Safe?|
|---|---|---|
|static_cast|Performs compile-time type conversions between related types.|Yes|
|dynamic_cast|Performs runtime type conversions on pointers or references in an polymorphic (inheritance) hierarchy|Yes|
|const_cast|Adds or removes const.|Only for adding const|
|reinterpret_cast|Reinterprets the bit-level representation of one type as if it were another type|No|
|C-style casts|Performs some combination of `static_cast`, `const_cast`, or `reinterpret_cast`.|No|
Each cast works the same way. As input, the cast takes an expression (that evaluates to a value or an object), and a target type. As output, the cast returns the result of the conversion.

Because they are the most commonly used casts, we’ll cover C-style casts and `static_cast` in this lesson.
#### Related content
We discuss `dynamic_cast` in lesson [25.10 -- Dynamic casting](https://www.learncpp.com/cpp-tutorial/dynamic-casting/), after we’ve covered other prerequisite topics.

`const_cast` and `reinterpret_cast` should generally be avoided because they are only useful in rare cases and can be harmful if used incorrectly.

#### Warning
Avoid `const_cast` and `reinterpret_cast` unless you have a very good reason to use them.

### C-style cast

In standard C programming, casting is done via `operator()`, with the name of the type to convert to placed inside the parentheses, and the value to convert to placed immediately to the right of the closing parenthesis. In C++, this type of cast is called a **C-style cast**. You may still see these used in code that has been converted from C.

For example:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    std::cout << (double)x / y << '\n'; // C-style cast of x to double

    return 0;
}
```

In the above program, we use a C-style cast to tell the compiler to convert `x` to a `double`. Because the left operand of `operator/` now evaluates to a floating point value, the right operand will be converted to a floating point value as well, and the division will be done using floating point division instead of integer division.

C++ also provides an alternative form of C-style cast known as a **function-style cast**, which resembles a function call:
```cpp
std::cout << double(x) / y << '\n'; //  // function-style cast of x to double
```
The function-style cast makes it a bit easier to tell what is being converted (as it looks like a standard function argument).

There are a couple of significant reasons that C-style casts are generally avoided in modern C++.

First, although a C-style cast appears to be a single cast, it can actually perform a variety of different conversions depending on how it is used. This can include a static cast, a const cast, or a reinterpret cast (the latter two of which we mentioned above you should avoid). A C-style cast does not make it clear which cast(s) will actual be performed, which not only makes your code that much harder to understand, but also opens the door for inadvertent misuse (where you think you’re implementing a simple cast and you end up doing something dangerous instead). Often this will end up producing an error that isn’t discovered until runtime.

Also, because C-style casts are just a type name, parenthesis, and variable or value, they are both difficult to identify (making your code harder to read) and even more difficult to search for.

In contrast, the named casts are easy to spot and search for, make it clear what they are doing, are limited in their abilities, and will produce a compilation error if you try to misuse them.

#### Best practice
Avoid using C-style casts.
#### For advanced readers
A C-style cast tries to perform the following C++ casts, in order:
- `const_cast`
- `static_cast`
- `static_cast`, followed by `const_cast`
- `reinterpret_cast`
- `reinterpret_cast`, followed by `const_cast`

There is one thing you can do with a C-style cast that you can’t do with C++ casts: C-style casts can convert a derived object to a base class that is inaccessible (e.g. because it was privately inherited).

### `static_cast` should be used to cast most values

By far the most used cast in C++ is the **static cast** operator, which is accessed via the `static_cast` keyword. `static_cast` is used when we want to explicitly convert a value of one type into a value of another type.

You’ve previously seen `static_cast` used to convert a `char` into an `int` so that `std::cout` prints it as an integer instead of a character:
```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a

    return 0;
}
```

To perform a static cast, we start with the `static_cast` keyword, and then place the type to convert to inside angled brackets. Then inside parenthesis, we place the expression whose value will be converted. Note how much the syntax looks like a function call to a function named `static_cast<type>()` with the expression whose value will be converted provided as an argument! Static casting a value to another type of value returns a temporary object that has been direct-initialized with the converted value.

Here’s how we’d use `static_cast` to solve the problem we introduced in the introduction of this lesson:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // static cast x to a double so we get floating point division
    std::cout << static_cast<double>(x) / y << '\n'; // prints 2.5

    return 0;
}
```

`static_cast<double>(x)` returns a temporary `double` object containing the converted value `10.0`. This temporary is then used as the left-operand of the floating point division.

There are two important properties of `static_cast`.

First, `static_cast` provides compile-time type checking. If we try to convert a value to a type and the compiler doesn’t know how to perform that conversion, we will get a compilation error.
```cpp
// a C-style string literal can't be converted to an int, so the following is an invalid conversion
int x { static_cast<int>("Hello") }; // invalid: will produce compilation error
```

Second, `static_cast` is (intentionally) less powerful than a C-style cast, as it will prevent certain kinds of dangerous conversions (such as those that require reinterpretation or discarding const).

#### Best practice
Favor `static_cast` when you need to convert a value from one type to another type.
#### For advanced readers
Since static_cast uses direct initialization, any explicit constructors of the target class type will be considered when initializing the temporary object to be returned. We discuss explicit constructors in lesson [14.16 -- Converting constructors and the explicit keyword](https://www.learncpp.com/cpp-tutorial/converting-constructors-and-the-explicit-keyword/).

### Using `static_cast` to make narrowing conversions explicit
Compilers will often issue warnings when a potentially unsafe (narrowing) implicit type conversion is performed. For example, consider the following snippet:

```cpp
int i { 48 };
char ch = i; // implicit narrowing conversion
```

Casting an `int` (2 or 4 bytes) to a `char` (1 byte) is potentially unsafe (as the compiler can’t tell whether the integer value will overflow the range of the `char` or not), and so the compiler will typically print a warning. If we used list initialization, the compiler would yield an error.

To get around this, we can use a static cast to explicitly convert our integer to a `char`:

```cpp
int i { 48 };

// explicit conversion from int to char, so that a char is assigned to variable ch
char ch { static_cast<char>(i) };
```

When we do this, we’re explicitly telling the compiler that this conversion is intended, and we accept responsibility for the consequences (e.g. overflowing the range of a `char` if that happens). Since the output of this static cast is of type `char`, the initialization of variable `ch` doesn’t generate any type mismatches, and hence no warnings or errors.

Here’s another example where the compiler will typically complain that converting a `double` to an `int` may result in loss of data:

```cpp
int i { 100 };
i = i / 2.5;
```

To tell the compiler that we explicitly mean to do this:

```cpp
int i { 100 };
i = static_cast<int>(i / 2.5);
```
#### Related content
We discuss more uses of static_cast in relation to class types in lesson [14.13 -- Temporary class objects](https://www.learncpp.com/cpp-tutorial/temporary-class-objects/).

### Casting vs initializing a temporary object
Let’s say we have some variable `x` that we need to convert to an `int`. There are two conventional ways we can do this:
1. `static_cast<int>(x)`, which returns a temporary `int` object _direct-initialized_ with `x`.
2. `int { x }`, which creates a temporary `int` object _direct-list-initialized_ with `x`.

We should avoid `int ( x )`, which is a C-style cast. This will return a temporary `int` direct-initialized with the value of `x` (like we’d expect from the syntax), but it also has the other downsides mentioned in the C-style cast section (like allowing the possibility of performing a dangerous conversion).

There are (at least) three notable differences between the `static_cast` and the direct-list-initialized temporary:
1. `int { x }` uses list initialization, which disallows narrowing conversions. This is great when initializing a variable, because we rarely intend to lose data in such cases. But when using a cast, it is presumed we know what we’re doing, and if we want to do a cast that might lose some data, we should be able to do that. The narrowing conversion restriction can be an impediment in this case.

Let’s show an example of this, including how it can lead to platform-specific issues:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // We want to do floating point division, so one of the operands needs to be a floating point type
    std::cout << double{x} / y << '\n'; // okay if int is 32-bit, narrowing if x is 64-bit => won’t compile if x is 64-bit
}
```

In this example, we have decided to convert `x` to a `double` so we can do floating-point division rather than integer division. On a 32-bit architecture, this will work fine (because a `double` can represent all the values that can be stored in a 32-bit `int`, so it isn’t a narrowing conversion). But on a 64-bit architecture, this is not the case, so converting a 64-bit `int` to a `double` is a narrowing conversion. And since list initialization disallows narrowing conversions, this won’t compile on architectures where `int` is 64-bits.

2. `static_cast` makes it clearer that we are intending to perform a conversion. Although the `static_cast` is more verbose than the direct-list-initialized alternative, in this case, that’s a good thing, as it makes the conversion easier to spot and search for. That ultimately makes your code safer and easier to understand.
3. Direct-list-initializion of a temporary only allows single-word type names. Due to a weird syntax quirk, there are several places within C++ where only single-word type names are allowed (the C++ standard calls these names “simple type specifiers”). So while `int { x }` is a valid conversion syntax, `unsigned int { x }` is not.

You can see this for yourself in the following example, which produces a compile error:
```cpp
#include <iostream>

int main()
{
    unsigned char c { 'a' };
    std::cout << unsigned int { c } << '\n';

    return 0;
}
```

There are simple ways to work around this, the easiest of which is to use a single-word type alias:
```cpp
#include <iostream>

int main()
{
    unsigned char c { 'a' };
    using uint = unsigned int;
    std::cout << uint { c } << '\n';

    return 0;
}
```

But why go to the trouble when you can just `static_cast`?

For all these reasons, we generally prefer `static_cast` over direct-list-initialization of a temporary.

#### Best practice
Prefer `static_cast` over initializing a temporary object when a conversion is desired.

## 10.7 [Typedefs and type aliases](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)

### 
### 


#### 

### 

#### 
#### 

### 

```cpp
int printData();

<=>

using PrintError = int;
PrintError printData();
```

## 10.8 [Type deduction for objects using the auto keyword](https://www.learncpp.com/cpp-tutorial/type-deduction-for-objects-using-the-auto-keyword/)

### 
### 

In most cases, type deduction will drop the `const` from deduced types. For example:
```cpp
int main()
{
    const int a { 5 }; // a has type const int
    auto b { a };      // b has type int (const dropped)

    return 0;
}
```
#### 

### 

#### 
#### 

### Type deduction for string literals

For historical reasons, string literals in C++ have a strange type. Therefore, the following probably won’t work as expected:

```cpp
auto s { "Hello, world" }; // s will be type const char*, not std::string
```

If you want the type deduced from a string literal to be `std::string` or `std::string_view`, you’ll need to use the `s` or `sv` literal suffixes (introduced in lessons [5.7 -- Introduction to std::string](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/) and [5.8 -- Introduction to std::string_view](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/)):

```cpp
#include <string>
#include <string_view>

int main()
{
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    return 0;
}
```

### Type deduction and constexpr

Because `constexpr` is not part of the type system, it cannot be deduced as part of type deduction. However, a `constexpr` variable is implicitly const, and this const will be dropped during type deduction (and can be readded if desired):

```cpp
int main()
{
    constexpr double a { 3.4 };  // a has type const double (constexpr not part of type, const is implicit)

    auto b { a };                // b has type double (const dropped)
    const auto c { a };          // c has type const double (const dropped but reapplied)
    constexpr auto d { a };      // d has type const double (const dropped but implicitly reapplied by constexpr)

    return 0;
}
```




## 10.9 [Type deduction for functions](https://www.learncpp.com/cpp-tutorial/type-deduction-for-functions/)

### 
### 


#### For advanced readers

3. If we have a function whose return type must be deduced based on the type of the function parameters, a normal return type will not suffice, because the compiler has not yet seen the parameters at that point.

```cpp
#include <type_traits>
// note: decltype(x) evaluates to the type of x

std::common_type_t<decltype(x), decltype(y)> add(int x, double y);         // Compile error: compiler hasn't seen definitions of x and y yet
auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; // ok
```

4. The trailing return syntax is also required for some advanced features of C++, such as lambdas (which we cover in lesson [20.6 -- Introduction to lambdas (anonymous functions)](https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/)).

### 

#### 
#### 

### 

## 10.x [Chapter 10 summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-10-summary-and-quiz/)
### Chapter Review

The process of converting a value from one data type to another data type is called a **type conversion**.

**Implicit type conversion** (also called **automatic type conversion** or **coercion**) is performed whenever one data type is expected, but a different data type is supplied. If the compiler can figure out how to do the conversion between the two types, it will. If it doesn’t know how, then it will fail with a compile error.

The C++ language defines a number of built-in conversions between its fundamental types (as well as a few conversions for more advanced types) called **standard conversions**. These include numeric promotions, numeric conversions, and arithmetic conversions.

A **numeric promotion** is the conversion of certain smaller numeric types to certain larger numeric types (typically `int` or `double`), so that the CPU can operate on data that matches the natural data size for the processor. Numeric promotions include both integral promotions and floating-point promotions. Numeric promotions are **value-preserving**, meaning there is no loss of value or precision. Not all widening conversions are promotions.

A **numeric conversion** is a type conversion between fundamental types that isn’t a numeric promotion. A **narrowing conversion** is a numeric conversion that may result in the loss of value or precision.

In C++, certain binary operators require that their operands be of the same type. If operands of different types are provided, one or both of the operands will be implicitly converted to matching types using a set of rules called the **usual arithmetic conversions**.

**Explicit type conversion** is performed when the programmer explicitly requests conversion via a cast. A **cast** represents a request by the programmer to do an explicit type conversion. C++ supports 5 types of casts: `C-style casts`, `static casts`, `const casts`, `dynamic casts`, and `reinterpret casts`. Generally you should avoid `C-style casts`, `const casts`, and `reinterpret casts`. `static_cast` is used to convert a value from one type to a value of another type, and is by far the most used cast in C++.

**Typedefs** and **type aliases** allow the programmer to create an alias for a data type. These aliases are not new types, and act identically to the aliased type. Typedefs and type aliases do not provide any kind of type safety, and care needs to be taken to not assume the alias is different than the type it is aliasing.

The **auto** keyword has a number of uses. First, auto can be used to do **type deduction** (also called **type inference**), which will deduce a variable’s type from its initializer. Type deduction drops const and references, so be sure to add those back if you want them.

Auto can also be used as a function return type to have the compiler infer the function’s return type from the function’s return statements, though this should be avoided for normal functions. Auto is used as part of the **trailing return syntax**.

What type of conversion happens in each of the following cases? Valid answers are: No conversion needed, numeric promotion, numeric conversion, won’t compile due to narrowing conversion. Assume int and long are both 4 bytes.

int main()
{
    int a { 5 }; // 1a
    int b { 'a' }; // 1b
    int c { 5.4 }; // 1c
    int d { true }; // 1d
    int e { static_cast<int>(5.4) }; // 1e

    double f { 5.0f }; // 1f
    double g { 5 }; // 1g

    // Extra credit section
    long h { 5 }; // 1h

    float i { f }; // 1i (uses previously defined variable f)
    float j { 5.0 }; // 1j

}

1a) Hide Solution
No conversion needed

1b) Hide Solution
Numeric promotion of char ‘a’ to int

1c) Hide Solution
Won’t compile due to narrowing conversion

1d) Hide Solution
Numeric promotion of bool true to int

1e) Hide Solution
Numeric conversion of double 5.4 to int

1f) Hide Solution
Numeric promotion of float to double

1g) Hide Solution
Numeric conversion of int to double

1h) Hide Solution
Numeric conversion of int to long (this conversion is trivial, but it’s still a conversion)

1i) Hide Solution
Won’t compile due to narrowing conversion from double to float

1j) Hide Solution
Numeric conversion of double to float (this is allowed since 5.0 is constexpr and fits in the range of the float)