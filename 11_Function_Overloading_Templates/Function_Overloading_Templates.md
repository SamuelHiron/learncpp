# 11.2 — Function overload differentiation 

### How overloaded functions are differentiated

|Function property|Used for differentiation|Notes|
|---|---|---|
|Number of parameters|Yes||
|Type of parameters|Yes|Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses.|
|Return type|No|

#### 
#### For advanced readers

We haven’t covered ellipsis yet, but ellipsis parameters are considered to be a unique type of parameter:

```cpp
void foo(int x, int y);
void foo(int x, ...); // differentiated from foo(int, int)
```

Thus a call to `foo(4, 5)` will match to `foo(int, int)`, not `foo(int, ...)`.

### 

## 

### 


#### Deleting all non-matching overloads Advanced

Deleting a bunch of individual function overloads works fine, but can be verbose. There may be times when we want a certain function to be called only with arguments whose types exactly match the function parameters. We can do this by using a function template (introduced in upcoming lesson [11.6 -- Function templates](https://www.learncpp.com/cpp-tutorial/function-templates/)) as follows:

```cpp
#include <iostream>

// This function will take precedence for arguments of type int
void printInt(int x)
{
    std::cout << x << '\n';
}

// This function template will take precedence for arguments of other types
// Since this function template is deleted, calls to it will halt compilation
template <typename T>
void printInt(T x) = delete

int main()
{
    printInt(97);   // okay
    printInt('a');  // compile error
    printInt(true); // compile error

    return 0;
}
```

### 
```cpp
void print(int x, int y = 10);      // signature print(int, int)

int main()
{
    print(1);   // will resolve to print(1, 10)
```
#### 
#### 

### 

## Introduction to C++ templates

In C++, the template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types.

Instead of manually creating a bunch of mostly-identical functions or classes (one for each set of different types), we instead create a single _template_. Just like a normal definition, a **template** definition describes what a function or class looks like. Unlike a normal definition (where all types must be specified), in a template we can use one or more placeholder types. A placeholder type represents some type that is not known at the time the template is defined, but that will be provided later (when the template is used).

Once a template is defined, the compiler can use the template to generate as many overloaded functions (or classes) as needed, each using different actual types!

```cpp
template <typename T> // this is the template parameter declaration defining T as a type template parameter
T max(T x, T y) // this is the function template definition for max<T>

{
	return (x<y) ? y : x;
}
```
If a type template parameter has a non-obvious usage or specific requirements that must be met, there are two common conventions for such names:

- Starting with a capital letter (e.g. `Allocator`). The standard library uses this naming convention.
- Prefixed with a `T`, then starting with a capital letter (e.g. `TAllocator`). This makes it easier to see that the type is a type template parameter.

Use a single capital letter starting with `T` (e.g. `T`, `U`, `V`, etc…) to name type template parameters that are used in trivial or obvious ways and represent “any reasonable type”.
```cpp
template< class T, class Compare >
const T& max( const T& a, const T& b, Compare comp ); // ignore the & for now, we'll cover these in a future lesson
```

To use our `max<T>` function template, we can make a function call with the following syntax:
`max<actual_type>(arg1, arg2); // actual_type is some actual type, like int or double`


```cpp
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
```

For example, instead of making a function call like this:
```cpp
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
```

We can do one of these instead:
```cpp
std::cout << max<>(1, 2) << '\n';
std::cout << max(1, 2) << '\n';
```

```cpp
template <typename T>
int someFcn(T, double)
```

```cpp
template <typename T>
T addOne(T x)
{
    return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* addOne(const char* x) = delete;
```

### 
```cpp
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';  // compile error
```
type conversion is done only when resolving function overloads, not when performing template argument deduction.
Solution :
```cpp
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)
```

```cpp
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';
```

this won't work:

```cpp
template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
}

    std::cout << max(2, 3.5) << '\n';
```

This works
```cpp
template <typename T, typename U>
auto max(T x, U y) // ask compiler can figure out what the relevant return type is
{
    return (x < y) ? y : x;
}

    std::cout << max(2, 3.5) << '\n';
```

If we need a function that can be forward declared, we have to be explicit about the return type. Since our return type needs to be the common type of `T` and `U`, we can use `std::common_type_t`
```cpp
auto max(T x, U y) -> std::common_type_t<T, U>; // returns the common type of T and U
```
#### **abbreviated function template**.

For example:
```cpp
// no template needed
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}
```

is shorthand in C++20 for the following:
```cpp
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}
```

### Function templates may be overloaded
Just like functions may be overloaded, function templates may also be overloaded. Such overloads can have a different number of template types and/or a different number or type of function parameters:

```cpp
#include <iostream>

// Add two values with matching types
template <typename T>
auto add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
auto add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
auto add(T x, U y, V z)
{
    return x + y + z;
}
```

#### Non-type template parameters

A **non-type template parameter** is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.

A non-type template parameter can be any of the following types:

- An integral type
- An enumeration type
- `std::nullptr_t`
- A floating point type (since C++20)
- A pointer or reference to an object
- A pointer or reference to a function
- A pointer or reference to a member function
- A literal class type (since C++20)

```cpp
template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument
```

When the compiler sees this call, it will instantiate a function that looks something like this:

```cpp
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
```

At runtime, when this function is called from `main()`, it prints `5`.

### What are non-type template parameters useful for?
As of C++20, function parameters cannot be constexpr. This is true for normal functions, constexpr functions (which makes sense, as they must be able to be run at runtime), and perhaps surprisingly, even consteval functions.

So let’s say we have some function like this one:
```cpp
double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}
```

When run, the call to `getSqrt(-5.0)` will runtime assert out. While this is better than nothing, because `-5.0` is a literal (and implicitly constexpr), it would be better if we could static_assert so that errors such as this one would be caught at compile-time. However, static_assert requires a constant expression, and function parameters can’t be constexpr…
However, if we change the function parameter to a non-type template parameter instead, then we can do exactly as we want:

```cpp
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```

This version fails to compile. When the compiler encounters `getSqrt<-5.0>()`, it will instantiate and call a function that looks something like this:

```cpp
template <>
double getSqrt<-5.0>()
{
    static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (-5.0 >= 0) // ignore the constexpr here for this example
        return std::sqrt(-5.0);

    return 0.0;
}
```

The static_assert condition is false, so the compiler asserts out.

### Implicit conversions for non-type template arguments Optional
```cpp
template <int N> // int non-type template parameter
void print()
{
    std::cout << N << '\n';
}

template <char N> // char non-type template parameter
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // ambiguous match with int N = 5 and char N = 5
    print<'c'>(); // ambiguous match with int N = 99 and char N = 'c'
```


#### Type deduction for non-type template parameters using `auto` C++17

```cpp
template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`
```

After instantiating the function template for the above example, the program looks something like this:
```cpp
template <auto N>
void print()
{
    std::cout << N << '\n';
}

template <>
void print<5>() // note that this is print<5> and not print<int>
{
    std::cout << 5 << '\n';
}

template <>
void print<'c'>() // note that this is print<`c`> and not print<char>
{
    std::cout << 'c' << '\n';
}
```
## Using function templates in multiple files
The most conventional way to address this issue is to put all your template code in a header (.h) file instead of a source (.cpp) file:

add.h:

```cpp
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif
```

main.cpp:

```cpp
#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
## Chapter Review

**Function overloading** allows us to create multiple functions with the same name, so long as each identically named function has different set of parameter types (or the functions can be otherwise differentiated). Such a function is called an **overloaded function** (or **overload** for short). Return types are not considered for differentiation.

When resolving overloaded functions, if an exact match isn’t found, the compiler will favor overloaded functions that can be matched via numeric promotions over those that require numeric conversions. When a function call is made to function that has been overloaded, the compiler will try to match the function call to the appropriate overload based on the arguments used in the function call. This is called **overload resolution**.

An **ambiguous match** occurs when the compiler finds two or more functions that can match a function call to an overloaded function and can’t determine which one is best.

A **default argument** is a default value provided for a function parameter. Parameters with default arguments must always be the rightmost parameters, and they are not used to differentiate functions when resolving overloaded functions.

**Function templates** allow us to create a function-like definition that serves as a pattern for creating related functions. In a function template, we use **type template parameters** as placeholders for any types we want to be specified later. The syntax that tells the compiler we’re defining a template and declares the template types is called a **template parameter declaration**.

The process of creating functions (with specific types) from function templates (with template types) is called **function template instantiation** (or **instantiation**) for short. When this process happens due to a function call, it’s called **implicit instantiation**. An instantiated function is called a **function instance** (or **instance** for short, or sometimes a **template function**).

**Template argument deduction** allows the compiler to deduce the actual type that should be used to instantiate a function from the arguments of the function call. Template argument deduction does not do type conversion.

Template types are sometimes called **generic types**, and programming using templates is sometimes called **generic programming**.

In C++20, when the auto keyword is used as a parameter type in a normal function, the compiler will automatically convert the function into a function template with each auto parameter becoming an independent template type parameter. This method for creating a function template is called an **abbreviated function template**.

A **non-type template parameter** is a template parameter with a fixed type that serves as a placeholder for a constexpr value passed in as a template argument.