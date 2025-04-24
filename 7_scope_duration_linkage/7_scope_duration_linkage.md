# Scope, Duration, and Linkage

## 7.1 [Compound statements (blocks)](https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/)
A **compound statement** (also called a **block**, or **block statement**) is a group of _zero or more statements_ that is treated by the compiler as if it were a single statement.

Blocks begin with a `{` symbol, end with a `}` symbol, with the statements to be executed being placed in between. Blocks can be used anywhere a single statement is allowed. No semicolon is needed at the end of a block.

You have already seen an example of blocks when writing functions, as the function body is a block:
```cpp
int add(int x, int y)
{ // start block
    return x + y;
} // end block (no semicolon)

int main()
{ // start block

    // multiple statements
    int value {}; // this is initialization, not a block
```
### Blocks inside other blocks

Although functions can’t be nested inside other functions, blocks _can be_ nested inside other blocks:
```cpp
int main()
{ // outer block

    // multiple statements
    int value {};

    { // inner/nested block
        add(3, 4);
    } // end inner/nested block
```
When blocks are nested, the enclosing block is typically called the **outer block** and the enclosed block is called the **inner block** or **nested block**.
### Using blocks to execute multiple statements conditionally

One of the most common use cases for blocks is in conjunction with `if statements`. By default, an `if statement` executes a single statement if the condition evaluates to `true`. However, we can replace this single statement with a block of statements if we want multiple statements to execute when the condition evaluates to `true`.

For example:
```cpp
 if (value >= 0)
    { // start of nested block
        std::cout << value << " is a positive integer (or zero)\n";
        std::cout << "Double this number is " << value * 2 << '\n';
    } // end of nested block
    else
    { // start of another nested block
        std::cout << value << " is a negative integer\n";
        std::cout << "The positive of this number is " << -value << '\n';
    } // end of another nested block
```
### Block nesting levels

It is even possible to put blocks inside of blocks inside of blocks:
```cpp

    if (value >  0)
    { // block 2, nesting level 2
        if ((value % 2) == 0)
        { // block 3, nesting level 3
            std::cout << value << " is positive and even\n";
        }
        else
        { // block 4, also nesting level 3
            std::cout << value << " is positive and odd\n";
        }
    }
```
The **nesting level** (also called the **nesting depth**) of a function is the maximum number of nested blocks you can be inside at any point in the function (including the outer block). In the above function, there are 4 blocks, but the nesting level is 3 since in this program you can never be inside more than 3 blocks at any point.

The C++ standard says that C++ compilers should support 256 levels of nesting -- however not all do (e.g. as of the time of writing, Visual Studio supports fewer).

It’s a good idea to keep your nesting level to 3 or less. Just as overly-long functions are good candidates for refactoring (breaking into smaller functions), overly-nested blocks are hard to read and are good candidates for refactoring (with the most-nested blocks becoming separate functions).
#### Best practice
Keep the nesting level of your functions to 3 or less. If your function has a need for more nested levels, consider refactoring your function into sub-functions.

## 7.2 [User-defined namespaces and the scope resolution operator](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/)
In lesson [2.9 -- Naming collisions and an introduction to namespaces](https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/), we introduced the concept of `naming collisions` and `namespaces`. As a reminder, a naming collision occurs when two identical identifiers are introduced into the same scope, and the compiler can’t disambiguate which one to use. When this happens, compiler or linker will produce an error because they do not have enough information to resolve the ambiguity.
####  Key insight
As programs become larger, the number of identifiers increases, which in turn causes the probability of a naming collision occurring to increase significantly. Because every name in a given scope can potentially collide with every other name in the same scope, a linear increase in identifiers will result in an exponential increase in potential collisions! This is one of the key reasons for defining identifiers in the smallest scope possible.

Let’s revisit an example of a naming collision, and then show how we can improve things using namespaces. In the following example, `foo.cpp` and `goo.cpp` are the source files that contain functions that do different things but have the same name and parameters.
foo.cpp:
```cpp
// This doSomething() adds the value of its parameters
int doSomething(int x, int y)
{
    return x + y;
}
```

goo.cpp:
```cpp
// This doSomething() subtracts the value of its parameters
int doSomething(int x, int y)
{
    return x - y;
}
```

main.cpp:
```cpp
#include <iostream>

int doSomething(int x, int y); // forward declaration for doSomething

int main()
{
    std::cout << doSomething(4, 3) << '\n'; // which doSomething will we get?
    return 0;
}
```
If this project contains only `foo.cpp` _or_ `goo.cpp` (but not both), it will compile and run without incident. However, by compiling both into the same program, we have now introduced two different functions with the same name and parameters into the same scope (the global scope), which causes a naming collision. As a result, the linker will issue an error:

```
goo.cpp:3: multiple definition of `doSomething(int, int)'; foo.cpp:3: first defined here
```

Note that this error happens at the point of redefinition, so it doesn’t matter whether function `doSomething` is ever called.

One way to resolve this would be to rename one of the functions, so the names no longer collide. But this would also require changing the names of all the function calls, which can be a pain, and is subject to error. A better way to avoid collisions is to put your functions into your own namespaces. For this reason the standard library was moved into the `std` namespace.

### Defining your own namespaces
C++ allows us to define our own namespaces via the `namespace` keyword. Namespaces that you create in your own programs are casually called **user-defined namespaces** (though it would be more accurate to call them **program-defined namespaces**).
The syntax for a namespace is as follows:

```cpp
namespace NamespaceIdentifier
{
    // content of namespace here
}
```
We start with the `namespace` keyword, followed by an identifier for the namespace, and then curly braces with the content of the namespace inside.

Historically, namespace names have not been capitalized, and many style guides still recommend this convention.
#### For advanced readers
Some reasons to prefer namespace names starting with a capital letter:
- It is convention to name program-defined types starting with a capital letter. Using the same convention for program-defined namespaces is consistent (especially when using a qualified name such as `Foo::x`, where `Foo` could be a namespace or a class type).
- It helps prevent naming collisions with other system-provided or library-provided lower-cased names.
- The C++20 standards document uses this style.
- The C++ Core guidelines document uses this style.

We recommend starting namespace names with a capital letter. However, either style should be seen as acceptable.

A namespace must be defined either in the global scope, or inside another namespace. Much like the content of a function, the content of a namespace is conventionally indented one level. You may occasionally see an optional semicolon placed after the closing brace of a namespace.

Here is an example of the files in the prior example rewritten using namespaces:

foo.cpp:
```cpp
namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}
```

goo.cpp:
```cpp
namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}
```

Now `doSomething()` inside of `foo.cpp` is inside the `Foo` namespace, and the `doSomething()` inside of `goo.cpp` is inside the `Goo` namespace. Let’s see what happens when we recompile our program.

main.cpp:
```cpp
int doSomething(int x, int y); // forward declaration for doSomething

int main()
{
    std::cout << doSomething(4, 3) << '\n'; // which doSomething will we get?
    return 0;
}
```
The answer is that we now get another error!

```
ConsoleApplication1.obj : error LNK2019: unresolved external symbol "int __cdecl doSomething(int,int)" (?doSomething@@YAHHH@Z) referenced in function _main
```

In this case, the compiler was satisfied (by our forward declaration), but the linker could not find a definition for `doSomething` in the global namespace. This is because both of our versions of `doSomething` are no longer in the global namespace! They are now in the scope of their respective namespaces!

There are two different ways to tell the compiler which version of `doSomething()` to use, via the `scope resolution operator ::`, or via `using statements` (which we’ll discuss in a later lesson in this chapter).

For the subsequent examples, we’ll collapse our examples down to a one-file solution for ease of reading.
### Accessing a namespace with the scope resolution operator (::)
The best way to tell the compiler to look in a particular namespace for an identifier is to use the **scope resolution operator** (::). The scope resolution operator tells the compiler that the identifier specified by the right-hand operand should be looked for in the scope of the left-hand operand.

Here is an example of using the scope resolution operator to tell the compiler that we explicitly want to use the version of `doSomething()` that lives in the `Foo` namespace:

```cpp
#include <iostream>

namespace Foo // define a namespace named Foo
{
    // This doSomething() belongs to namespace Foo
    int doSomething(int x, int y)
    {
        return x + y;
    }
}

namespace Goo // define a namespace named Goo
{
    // This doSomething() belongs to namespace Goo
    int doSomething(int x, int y)
    {
        return x - y;
    }
}

int main()
{
    std::cout << Foo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Foo => 7
    std::cout << Goo::doSomething(4, 3) << '\n'; // use the doSomething() that exists in namespace Goo => 1
```

The scope resolution operator is great because it allows us to _explicitly_ pick which namespace we want to look in, so there’s no potential ambiguity. 

### Using the scope resolution operator with no name prefix

The scope resolution operator can also be used in front of an identifier without providing a namespace name (e.g. `::doSomething`). In such a case, the identifier (e.g. `doSomething`) is looked for in the global namespace.
```cpp
oid print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}
}

int main()
{
	Foo::print(); // call print() in Foo namespace => Hello
	::print();    // call print() in global namespace (same as just calling print() in this case) => there\n
```
In the above example, the `::print()` performs the same as if we’d called `print()` with no scope resolution, so use of the scope resolution operator is superfluous in this case. But the next example will show a case where the scope resolution operator with no namespace can be useful.

### Identifier resolution from within a namespace
If an identifier inside a namespace is used and no scope resolution is provided, the compiler will first try to find a matching declaration in that same namespace. If no matching identifier is found, the compiler will then check each containing namespace in sequence to see if a match is found, with the global namespace being checked last.
```cpp

void print() // this print() lives in the global namespace
{
	std::cout << " there\n";
}

namespace Foo
{
	void print() // this print() lives in the Foo namespace
	{
		std::cout << "Hello";
	}

	void printHelloThere()
	{
		print();   // calls print() in Foo namespace
		::print(); // calls print() in global namespace
	}
}

int main()
{
	Foo::printHelloThere();

	return 0;
}
// Hello there
```
In the above example, `print()` is called with no scope resolution provided. Because this use of `print()` is inside the `Foo` namespace, the compiler will first see if a declaration for `Foo::print()` can be found. Since one exists, `Foo::print()` is called.

If `Foo::print()` had not been found, the compiler would have checked the containing namespace (in this case, the global namespace) to see if it could match a `print()` there.

Note that we also make use of the scope resolution operator with no namespace (`::print()`) to explicitly call the global version of `print()`.
### Forward declaration of content in namespaces
In lesson [2.11 -- Header files](https://www.learncpp.com/cpp-tutorial/header-files/), we discussed how we can use header files to propagate forward declarations. For identifiers inside a namespace, those forward declarations also need to be inside the same namespace:
add.h
```cpp
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}

#endif
```

add.cpp
```cpp
#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
}
```

main.cpp
```cpp
#include "add.h" // for BasicMath::add()

#include <iostream>

int main()
{
    std::cout << BasicMath::add(4, 3) << '\n';
```
If the forward declaration for `add()` wasn’t placed inside namespace `BasicMath`, then `add()` would be declared in the global namespace instead, and the compiler would complain that it hadn’t seen a declaration for the call to `BasicMath::add(4, 3)`. If the definition of function `add()` wasn’t inside namespace `BasicMath`, the linker would complain that it couldn’t find a matching definition for the call to `BasicMath::add(4, 3)`.
### Multiple namespace blocks are allowed
It’s legal to declare namespace blocks in multiple locations (either across multiple files, or multiple places within the same file). All declarations within the namespace are considered part of the namespace.
circle.h:
```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

namespace BasicMath
{
    constexpr double pi{ 3.14 };
}

#endif
```

growth.h:
```cpp
#ifndef GROWTH_H
#define GROWTH_H

namespace BasicMath
{
    // the constant e is also part of namespace BasicMath
    constexpr double e{ 2.7 };
}

#endif
```

main.cpp:
```cpp
#include "circle.h" // for BasicMath::pi
#include "growth.h" // for BasicMath::e

#include <iostream>

int main()
{
    std::cout << BasicMath::pi << '\n';
    std::cout << BasicMath::e << '\n';
```

The standard library makes extensive use of this feature, as each standard library header file contains its declarations inside a `namespace std` block contained within that header file. Otherwise the entire standard library would have to be defined in a single header file!

Note that this capability also means you could add your own functionality to the `std` namespace. Doing so causes undefined behavior most of the time, because the `std` namespace has a special rule prohibiting extension from user code.
#### Warning
Do not add custom functionality to the std namespace.
### Nested namespaces
Namespaces can be nested inside other namespaces. For example:
```cpp
namespace Foo
{
    namespace Goo // Goo is a namespace inside the Foo namespace
    {
        int add(int x, int y)
        {
            return x + y;
        }
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
```
Note that because namespace `Goo` is inside of namespace `Foo`, we access `add` as `Foo::Goo::add`.

Since C++17, nested namespaces can also be declared this way:
```cpp
#include <iostream>

namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
```
This is equivalent to the prior example.

If you later need to add declarations to the `Foo` namespace (only), you can define a separate `Foo` namespace to do so:
```cpp
namespace Foo::Goo // Goo is a namespace inside the Foo namespace (C++17 style)
{
    int add(int x, int y)
    {
        return x + y;
    }
}

namespace Foo
{
     void someFcn() {} // This function is in Foo only
}

int main()
{
    std::cout << Foo::Goo::add(1, 2) << '\n';
```
Whether you keep the separate `Foo::Goo` definition or nest `Goo` inside `Foo` is a stylistic choice.
### Namespace aliases
Because typing the qualified name of a variable or function inside a nested namespace can be painful, C++ allows you to create **namespace aliases**, which allow us to temporarily shorten a long sequence of namespaces into something shorter:
```cpp
namespace Foo::Goo
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = Foo::Goo; // active now refers to Foo::Goo

    std::cout << Active::add(1, 2) << '\n'; // This is really Foo::Goo::add()

    return 0;
} // The Active alias ends here
```

One nice advantage of namespace aliases: If you ever want to move the functionality within `Foo::Goo` to a different place, you can just update the `Active` alias to reflect the new destination, rather than having to find/replace every instance of `Foo::Goo`.
```cpp
#include <iostream>

namespace Foo::Goo
{
}

namespace V2
{
    int add(int x, int y)
    {
        return x + y;
    }
}

int main()
{
    namespace Active = V2; // active now refers to V2

    std::cout << Active::add(1, 2) << '\n'; // We don't have to change this
```

### How to use namespaces
It’s worth noting that namespaces in C++ were not originally designed as a way to implement an information hierarchy -- they were designed primarily as a mechanism for preventing naming collisions. As evidence of this, note that the entirety of the standard library lives under the single top-level namespace `std`. Newer standard library features that introduce lots of names have started using nested namespaces (e.g. `std::ranges`) to avoid naming collisions within the `std` namespace.
+ Small applications developed for your own use typically do not need to be placed in namespaces. However, for larger personal projects that include lots of third party libraries, namespacing your code can help prevent naming collisions with libraries that aren’t properly namespaced.
#### Author’s note
The examples in these tutorials will typically not be namespaced unless we are illustrating something specific about namespaces, to help keep the examples concise.

- Any code that will be distributed to others should definitely be namespaced to prevent conflicts with the code it is integrated into. Often a single top-level namespace will suffice (e.g. `Foologger`). As an additional advantage, placing library code inside a namespace also allows the user to see the contents of your library by using their editor’s auto-complete and suggestion feature (e.g. if you type `Foologger`, autocomplete will show you all of the names inside `Foologger`).
- In multi-team organizations, two-level or even three-level namespaces are often used to prevent naming conflicts between code generated by different teams. These often take the form of one of the following:

1. Project or library :: module (e.g. `Foologger::Lang`)
2. Company or org :: project or library (e.g. `Foosoft::Foologger`)
3. Company or org :: project or library :: module (e.g. `Foosoft::Foologger::Lang`)

Use of module-level namespaces can help separate code that might be reusable later from application-specific code that will not be reusable. For example, physics and math functions could go into one namespace (e.g. `Math::`). Language and localization functions in another (e.g. `Lang::`). However, directory structures can also be used for this (with app-specific code in the project directory tree, and reusable code in a separate shared directory tree).

In general, you should avoid deeply nested namespaces (more than 3 levels).
#### Related content
C++ provides other useful namespace functionality. We cover unnamed namespaces and inline namespaces later in this chapter, in lesson [7.14 -- Unnamed and inline namespaces](https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/).
 
##  7.3 [Local variables](https://www.learncpp.com/cpp-tutorial/local-variables/)
In lesson [2.5 -- Introduction to local scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/), we introduced `local variables`, which are variables that are defined inside a function (including function parameters).

It turns out that C++ actually doesn’t have a single attribute that defines a variable as being a local variable. Instead, local variables have several different properties that differentiate how these variables behave from other kinds of (non-local) variables. We’ll explore these properties in this and upcoming lessons.

In lesson [2.5 -- Introduction to local scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/), we also introduced the concept of scope. An identifier’s `scope` determines where an identifier can be accessed within the source code. When an identifier can be accessed, we say it is `in scope`. When an identifier can not be accessed, we say it is `out of scope`. Scope is a compile-time property, and trying to use an identifier when it is out of scope will result in a compile error.
### Local variables have block scope
Local variables have **block scope**, which means they are _in scope_ from their point of definition to the end of the block they are defined within.
```cpp
int main()
{
    int i { 5 }; // i enters scope here
    double d { 4.0 }; // d enters scope here

    return 0;
} // d and i go out of scope here
```
Although function parameters are not defined inside the function body, for typical functions they can be considered to be part of the scope of the function body block.
```cpp
int max(int x, int y) // x and y enter scope here
{
    // assign the greater of x or y to max
    int max{ (x > y) ? x : y }; // max enters scope here

    return max;
} // max, y, and x leave scope here
```
### All variable names within a scope must be unique
Variable names must be unique within a given scope, otherwise any reference to the name will be ambiguous. Consider the following program:
```cpp
void someFunction(int x)
{
    int x{}; // compilation failure due to name collision with function parameter
}

int main()
{
    return 0;
}
```
The above program doesn’t compile because the variable `x` defined inside the function body and the function parameter `x` have the same name and both are in the same block scope.

### Local variables have automatic storage duration
A variable’s **storage duration** (usually just called **duration**) determines what rules govern when and how a variable will be created (instantiated) and destroyed. In most cases, a variable’s storage duration directly determines its `lifetime`.

#### Related content
We discuss what a lifetime is in lesson [2.5 -- Introduction to local scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/).

For example, local variables have **automatic storage duration**, which means they are created at the point of definition and destroyed at the end of the block they are defined in. For example:
```cpp
int main()
{
    int i { 5 }; // i created and initialized here
    double d { 4.0 }; // d created and initialized here

    return 0;
} // d and i are destroyed here
```

For this reason, local variables are sometimes called **automatic variables**.

### Local variables in nested blocks
Local variables can be defined inside nested blocks. This works identically to local variables in function body blocks:
```cpp
int main() // outer block
{
    int x { 5 }; // x enters scope and is created here

    { // nested block
        int y { 7 }; // y enters scope and is created here
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    return 0;
} // x goes out of scope and is destroyed here
```
In the above example, variable `y` is defined inside a nested block. Its scope is limited from its point of definition to the end of the nested block, and its lifetime is the same. Because the scope of variable `y` is limited to the inner block in which it is defined, it’s not accessible anywhere in the outer block.

Note that nested blocks are considered part of the scope of the outer block in which they are defined. Consequently, variables defined in the outer block _can_ be seen inside a nested block:
```cpp
#include <iostream>

int main()
{ // outer block

    int x { 5 }; // x enters scope and is created here

    { // nested block
        int y { 7 }; // y enters scope and is created here

        // x and y are both in scope here
        std::cout << x << " + " << y << " = " << x + y << '\n';
    } // y goes out of scope and is destroyed here

    // y can not be used here because it is out of scope in this block

    return 0;
} // x goes out of scope and is destroyed here
```

### Local variables have no linkage

Identifiers have another property named _linkage_. An identifier’s **linkage** determines whether a declaration of that same identifier in a different scope refers to the same object (or function).

Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.

For example:
```cpp
int main()
{
    int x { 2 }; // local variable, no linkage

    {
        int x { 3 }; // this declaration of x refers to a different object than the previous x
    }

    return 0;
}
```

Scope and linkage may seem somewhat similar. However, scope determines where declaration of a single identifier can be seen and used in the code. Linkage determines whether multiple declarations of the same identifier refer to the same object or not.

#### Related content
We discuss what happens when variables with the same name appear in nested blocks in lesson [7.5 -- Variable shadowing (name hiding)](https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/).

Linkage isn’t very interesting in the context of local variables, but we’ll talk about it more in the next few lessons.
### Variables should be defined in the most limited scope
If a variable is only used within a nested block, it should be defined inside that nested block:
```cpp
int main()
{
    // do not define y here
    {
        // y is only used inside this block, so define it here
        int y { 5 };
        std::cout << y << '\n';
    }
    // otherwise y could still be used here, where it's not needed
    return 0;
}
```

By limiting the scope of a variable, you reduce the complexity of the program because the number of active variables is reduced. Further, it makes it easier to see where variables are used (or aren’t used). A variable defined inside a block can only be used within that block (or nested blocks). This can make the program easier to understand.

If a variable is needed in an outer block, it needs to be declared in the outer block:
```cpp
int main()
{
    int y { 5 }; // we're declaring y here because we need it in this outer block later
    {
        int x{};
        std::cin >> x;
        // if we declared y here, immediately before its actual first use...
        if (x == 4)
            y = 4;
    } // ... it would be destroyed here
    std::cout << y; // and we need y to exist here
```
 The above example shows one of the rare cases where you may need to declare a variable well before its first use.

New developers sometimes wonder whether it’s worth creating a nested block just to intentionally limit a variable’s scope (and force it to go out of scope / be destroyed early). Doing so makes that variable simpler, but the overall function becomes longer and more complex as a result. The tradeoff generally isn’t worth it. If creating a nested block seems useful to intentionally limit the scope of a chunk of code, that code might be better to put in a separate function instead.
#### Best practice
Define variables in the most limited existing scope. Avoid creating new blocks whose only purpose is to limit the scope of variables.

## 7.4 [Introduction to global variables](https://www.learncpp.com/cpp-tutorial/introduction-to-global-variables/)
In lesson [7.3 -- Local variables](https://www.learncpp.com/cpp-tutorial/local-variables/), we covered that local variables are variables defined inside a function body. Local variables have block scope (are only visible within the block they are declared in), and have automatic duration (they are created at the point of definition and destroyed when the block is exited).

In C++, variables can also be declared _outside_ of a function. Such variables are called **global variables**.
### Declaring global variables

By convention, global variables are declared at the top of a file, below the includes, in the global namespace. Here’s an example of a global variable being defined:
```cpp
#include <iostream>

// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    g_x = 3;
    std::cout << g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << g_x << '\n';

    // global variables can be seen and used everywhere in the file
    g_x = 5;
    std::cout << g_x << '\n';

    return 0;
}
// g_x goes out of scope here
```

The above example prints:
```
3
3
5
```
### The scope of global variables
Identifiers declared in the global namespace have **global namespace scope** (commonly called **global scope**, and sometimes informally called **file scope**), which means they are visible from the point of declaration until the end of the _file_ in which they are declared.

Once declared, a global variable can be used anywhere in the file from that point onward! In the above example, global variable `g_x` is used in both functions `doSomething()` and `main()`.

Global variables can also be defined inside a user-defined namespace. Here is the same example as above, but `g_x` has been moved from the global scope into user-defined namespace `Foo`:
```cpp
#include <iostream>

namespace Foo // Foo is defined in the global scope
{
    int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    Foo::g_x = 3;
    std::cout << Foo::g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << Foo::g_x << '\n';

    // global variables can be seen and used everywhere in the file
    Foo::g_x = 5;
    std::cout << Foo::g_x << '\n';

    return 0;
}
```

Although the identifier `g_x` is now limited to the scope of `namespace Foo`, that name is still globally accessible (via `Foo::g_x`), and `g_x` is still a global variable.
#### Key insight
Variables declared inside a namespace are also global variables.
#### Best practice
Prefer defining global variables inside a namespace rather than in the global namespace.
### Global variables have static duration
Global variables are created when the program starts (before `main()` begins execution), and destroyed when it ends. This is called **static duration**. Variables with _static duration_ are sometimes called **static variables**.
### Naming global variables
By convention, some developers prefix global variable identifiers with “g” or “g_” to indicate that they are global. This prefix serves several purposes:
- It helps avoid naming collisions with other identifiers in the global namespace.
- It helps prevent inadvertent name shadowing (we discuss this point further in lesson [7.5 -- Variable shadowing (name hiding)](https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/)).
- It helps indicate that the prefixed variables persist beyond the scope of the function, and thus any changes we make to them will also persist.

Global variables defined inside a user-defined namespace often omit the prefix (since the first two points in the list above are not an issue in this case, and we can infer that a variable is a global when we see a prepended namespace name). However, it doesn’t hurt if you want to keep the prefix as a more visible reminder of the third point.
#### Best practice
Consider using a “g” or “g_” prefix when naming global variables (especially those defined in the global namespace), to help differentiate them from local variables and function parameters.
#### Author’s note
We sometimes get feedback from readers asking whether prefixes such as `g_` are okay because they’ve been told that prefixes are a form of [Hungarian notation](https://en.wikipedia.org/wiki/Hungarian_notation) and “Hungarian notation is bad”.

The objection to Hungarian notation comes mainly from the use of Hungarian notation to encode the _type_ of the variable in the variable’s name. e.g. `nAge`, where `n` means `int`. That’s not that useful in modern C++.

However, using prefixes (typically `g`/`g_`, `s`/`s_`, and `m`/`m_`) to represent the _scope_ or _duration_ of a variable does add value, for the reasons noted in this section.

### Global variable initialization

Unlike local variables, which are uninitialized by default, variables with static duration are zero-initialized by default.

Non-constant global variables can be optionally initialized:
```cpp
int g_x;       // no explicit initializer (zero-initialized by default)
int g_y {};    // value initialized (resulting in zero-initialization)
int g_z { 1 }; // list initialized with specific value
```




### Constant global variables

Just like local variables, global variables can be constant. As with all constants, constant global variables must be initialized.
```cpp
#include <iostream>

const int g_x;     // error: constant variables must be initialized
constexpr int g_w; // error: constexpr variables must be initialized

const int g_y { 1 };     // const global variable g_y, initialized with a value
constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';
}

int main()
{
    doSomething();

    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';

    return 0;
}
// g_y and g_z goes out of scope here
```
#### Related content
We discuss global constants in more detail in lesson [7.10 -- Sharing global constants across multiple files (using inline variables)](https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/).

### A word of caution about (non-constant) global variables
New programmers are often tempted to use lots of global variables, because they can be used without having to explicitly pass them to every function that needs them. However, use of non-constant global variables should generally be avoided altogether! We’ll discuss why in upcoming lesson [7.8 -- Why (non-const) global variables are evil](https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/).
### Quick Summary

```cpp
// Non-constant global variables
int g_x;                 // defines non-initialized global variable (zero initialized by default)
int g_x {};              // defines explicitly value-initialized global variable
int g_x { 1 };           // defines explicitly initialized global variable

// Const global variables
const int g_y;           // error: const variables must be initialized
const int g_y { 2 };     // defines initialized global const

// Constexpr global variables
constexpr int g_y;       // error: constexpr variables must be initialized
constexpr int g_y { 3 }; // defines initialized global constexpr
```

## 7.5 [Variable shadowing (name hiding)](https://www.learncpp.com/cpp-tutorial/variable-shadowing-name-hiding/)
Each block defines its own scope region. So what happens when we have a variable inside a nested block that has the same name as a variable in an outer block? When this happens, the nested variable “hides” the outer variable in areas where they are both in scope. This is called **name hiding** or **shadowing**.
### Shadowing of local variables
```cpp
#include <iostream>

int main()
{ // outer block
    int apples { 5 }; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        int apples{ 0 }; // define apples in the scope of the nested block

        // apples now refers to the nested block apples
        // the outer block apples is temporarily hidden

        apples = 10; // this assigns value 10 to nested block apples, not outer block apples

        std::cout << apples << '\n'; // print value of nested block apples
    } // nested block apples destroyed


    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
} // outer block apples destroyed
```

If you run this program, it prints:
```
5
10
5
```
In the above program, we first declare a variable named `apples` in the outer block. This variable is visible within the inner block, which we can see by printing its value (`5`). Then we declare a different variable (also named `apples`) in the nested block. From this point to the end of the block, the name `apples` refers to the nested block `apples`, not the outer block `apples`.

Thus, when we assign value `10` to `apples`, we’re assigning it to the nested block `apples`. After printing this value (`10`), the nested block ends and nested block `apples` is destroyed. The existence and value of outer block `apples` is not affected, and we prove this by printing the value of outer block `apples` (`5`).

Note that if the nested block `apples` had not been defined, the name `apples` in the nested block would still refer to the outer block `apples`, so the assignment of value `10` to `apples` would have applied to the outer block `apples`:
```cpp
#include <iostream>

int main()
{ // outer block
    int apples{5}; // here's the outer block apples

    { // nested block
        // apples refers to outer block apples here
        std::cout << apples << '\n'; // print value of outer block apples

        // no inner block apples defined in this example

        apples = 10; // this applies to outer block apples

        std::cout << apples << '\n'; // print value of outer block apples
    } // outer block apples retains its value even after we leave the nested block

    std::cout << apples << '\n'; // prints value of outer block apples

    return 0;
} // outer block apples destroyed
```
The above program prints:
```
5
10
10
```
When inside the nested block, there’s no way to directly access the shadowed variable from the outer block.

### Shadowing of global variables
Similar to how variables in a nested block can shadow variables in an outer block, local variables with the same name as a global variable will shadow the global variable wherever the local variable is in scope:

```cpp
#include <iostream>
int value { 5 }; // global variable

void foo()
{
    std::cout << "global variable value: " << value << '\n'; // value is not shadowed here, so this refers to the global value
}

int main()
{
    int value { 7 }; // hides the global variable value (wherever local variable value is in scope)

    ++value; // increments local value, not global value

    std::cout << "local variable value: " << value << '\n';

    foo();

    return 0;
} // local value is destroyed
```

This code prints:
```
local variable value: 8
global variable value: 5
```
However, because global variables are part of the global namespace, we can use the scope operator (::) with no prefix to tell the compiler we mean the global variable instead of the local variable.

```cpp
#include <iostream>
int value { 5 }; // global variable

int main()
{
    int value { 7 }; // hides the global variable value
    ++value; // increments local value, not global value

    --(::value); // decrements global value, not local value (parenthesis added for readability)

    std::cout << "local variable value: " << value << '\n';
    std::cout << "global variable value: " << ::value << '\n';

    return 0;
} // local value is destroyed
```

This code prints:
```
local variable value: 8
global variable value: 4
```


### Avoid variable shadowing

Shadowing of local variables should generally be avoided, as it can lead to inadvertent errors where the wrong variable is used or modified. Some compilers will issue a warning when a variable is shadowed.

For the same reason that we recommend avoiding shadowing local variables, we recommend avoiding shadowing global variables as well. This is trivially avoidable if all of your global names use a “g_” prefix.

#### Best practice
Avoid variable shadowing.
#### For gcc users
GCC and Clang support the flag `-Wshadow` that will generate warnings if a variable is shadowed. There are several subvariants of this flag (`-Wshadow=global`, `-Wshadow=local`, and `-Wshadow=compatible-local`. Consult the [GCC documentation](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html) for an explanation of the differences.
Visual Studio has such warnings enabled by default.

## 7.6 [Internal linkage](https://www.learncpp.com/cpp-tutorial/internal-linkage/)
In lesson [7.3 -- Local variables](https://www.learncpp.com/cpp-tutorial/local-variables/), we said, “An identifier’s linkage determines whether other declarations of that name refer to the same object or not”, and we discussed how local variables have `no linkage`.

Global variables and function identifiers can have either `internal linkage` or `external linkage`. We’ll cover the internal linkage case in this lesson, and the external linkage case in lesson [7.7 -- External linkage and variable forward declarations](https://www.learncpp.com/cpp-tutorial/external-linkage-and-variable-forward-declarations/).

An identifier with **internal linkage** can be seen and used within a single translation unit, but it is not accessible from other translation units. This means that if two source files have identically named identifiers with internal linkage, those identifiers will be treated as independent (and do not result in an ODR violation for having duplicate definitions).
#### Key insight
Identifiers with internal linkage may not be visible to the linker at all. Alternatively, they may be visible to the linker, but marked for use in a specific translation unit only.
#### Related content
We cover translation units in lesson [2.10 -- Introduction to the preprocessor](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/).
### Global variables with internal linkage

Global variables with internal linkage are sometimes called **internal variables**.

To make a non-constant global variable internal, we use the `static` keyword.

```cpp
#include <iostream>

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}
```

Const and constexpr global variables have internal linkage by default (and thus don’t need the `static` keyword -- if it is used, it will be ignored).

Here’s an example of multiple files using internal variables:

a.cpp:
```cpp
[[maybe_unused]] constexpr int g_x { 2 }; // this internal g_x is only accessible within a.cpp
```

main.cpp:
```cpp
#include <iostream>

static int g_x { 3 }; // this separate internal g_x is only accessible within main.cpp

int main()
{
    std::cout << g_x << '\n'; // uses main.cpp's g_x, prints 3

    return 0;
}
```

This program prints: `3`

Because `g_x` is internal to each file, `main.cpp` has no idea that `a.cpp` also has a variable named `g_x` (and vice versa).
#### For advanced readers
The use of the `static` keyword above is an example of a **storage class specifier**, which sets both the name’s linkage and its storage duration. The most commonly used `storage class specifiers` are `static`, `extern`, and `mutable`. The term `storage class specifier` is mostly used in technical documentations.
#### For advanced readers

The C++11 standard (appendix C) provides the rationale for why const variables have internal linkage by default: “Because const objects can be used as compile-time values in C++, this feature urges programmers to provide explicit initializer values for each const. This feature allows the user to put const objects in header files that are included in many compilation units.”

The designers of C++ intended two things:
- Const objects should be usable in constant expressions. In order to be usable in a constant expression, the compiler must have seen a definition (not a declaration) so it be evaluated at compile-time.
- Const objects should be able to be propagated via header files.

Objects with external linkage can only be defined in a single translation unit without violating the ODR -- other translation units must access those objects via a forward declaration. If const objects had external linkage by default, they would only be usable in constant expressions in the single translation unit containing the definition, and they could not be effectively propagated via header files, as #including the header into more than one source file would result in an ODR violation.

Objects with internal linkage can have a definition in each translation unit where they are needed without violating the ODR. This allows const objects to be placed in a header file and #included into as many translation units as desired without violating the ODR. And since each translation unit has a definition rather than a declaration, this ensures that those constants can be used in constant expressions within the translation unit.

Inline variables (which can have external linkage without causing ODR violations) weren’t introduced until C++17.

### Functions with internal linkage
As noted above, function identifiers also have linkage. Functions default to external linkage (which we’ll cover in the next lesson), but can be set to internal linkage via the `static` keyword:

add.cpp:
```cpp
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
[[maybe_unused]] static int add(int x, int y)
{
    return x + y;
}
```

main.cpp:
```cpp
#include <iostream>

int add(int x, int y); // forward declaration for function add

int main()
{
    std::cout << add(3, 4) << '\n';

    return 0;
}
```

This program won’t link, because function `add` is not accessible outside of `add.cpp`.

### The one-definition rule and internal linkage

In lesson [2.7 -- Forward declarations and definitions](https://www.learncpp.com/cpp-tutorial/forward-declarations/), we noted that the one-definition rule says that an object or function can’t have more than one definition, either within a file or a program.

However, it’s worth noting that internal objects (and functions) that are defined in different files are considered to be independent entities (even if their names and types are identical), so there is no violation of the one-definition rule. Each internal object only has one definition.

### `static` vs unnamed namespaces

In modern C++, use of the `static` keyword for giving identifiers internal linkage is falling out of favor. Unnamed namespaces can give internal linkage to a wider range of identifiers (e.g. type identifiers), and they are better suited for giving many identifiers internal linkage.

We cover unnamed namespaces in lesson [7.14 -- Unnamed and inline namespaces](https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/).

### Why bother giving identifiers internal linkage?

There are typically two reasons to give identifiers internal linkage:
- There is an identifier we want to make sure isn’t accessible to other files. This could be a global variable we don’t want messed with, or a helper function we don’t want to be called.
- To be pedantic about avoiding naming collisions. Because identifiers with internal linkage aren’t exposed to the linker, they can only collide with names in the same translation unit, not across the entire program.

Many modern development guides recommend giving every variable and function that isn’t meant to be used from another file internal linkage. If you have the discipline, this is a good recommendation.

For now, we’ll recommend a lighter-touch approach as a minimum: give internal linkage to any identifier that you have an explicit reason to disallow access from other files.
#### Best practice
Give identifiers internal linkage when you have an explicit reason to disallow access from other files.
Consider giving all identifiers you don’t want accessible to other files internal linkage (use an unnamed namespace for this).
### Quick Summary
```cpp
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```

We provide a comprehensive summary in lesson [7.12 -- Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/).


## 7.7 [External linkage and variable forward declarations](https://www.learncpp.com/cpp-tutorial/external-linkage-and-variable-forward-declarations/)
In the prior lesson ([7.6 -- Internal linkage](https://www.learncpp.com/cpp-tutorial/internal-linkage/)), we discussed how `internal linkage` limits the use of an identifier to a single file. In this lesson, we’ll explore the concept of `external linkage`.

An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). In this sense, identifiers with external linkage are truly “global” in that they can be used anywhere in your program!
#### Key insight
Identifiers with external linkage are visible to the linker. This allows the linker to do two things:
- Connect an identifier used in one translation unit with the appropriate definition in another translation unit.
- Deduplicate inline identifiers so one canonical definition remains. We discuss inline variables and functions in lesson [7.9 -- Inline functions and variables](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/).
### Functions have external linkage by default
In lesson [2.8 -- Programs with multiple code files](https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/), you learned that you can call a function defined in one file from another file. This is because functions have external linkage by default.

In order to call a function defined in another file, you must place a `forward declaration` for the function in any other files wishing to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.

Here’s an example:

a.cpp:
```cpp
#include <iostream>

void sayHi() // this function has external linkage, and can be seen by other files
{
    std::cout << "Hi!\n";
}
```

main.cpp:
```cpp
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
    sayHi(); // call to function defined in another file, linker will connect this call to the function definition

    return 0;
}
```
In the above example, the forward declaration of function `sayHi()` in `main.cpp` allows `main.cpp` to access the `sayHi()` function defined in `a.cpp`. The forward declaration satisfies the compiler, and the linker is able to link the function call to the function definition.

If function `sayHi()` had internal linkage instead, the linker would not be able to connect the function call to the function definition, and a linker error would result.

### Global variables with external linkage
Global variables with external linkage are sometimes called **external variables**. To make a global variable external (and thus accessible by other files), we can use the `extern` keyword to do so:
```cpp
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

Non-const global variables are external by default, so we don’t need to mark them as `extern`.

### Variable forward declarations via the extern keyword

To actually use an external global variable that has been defined in another file, you also must place a `forward declaration` for the global variable in any other files wishing to use the variable. For variables, creating a forward declaration is also done via the `extern` keyword (with no initialization value).

Here is an example of using variable forward declarations:

main.cpp:
```cpp
#include <iostream>

extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```

Here’s the definitions for those variables:

a.cpp:
```cpp
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```
In the above example, `a.cpp` and `main.cpp` both reference the same global variable named `g_x`. So even though `g_x` is defined and initialized in `a.cpp`, we are able to use its value in `main.cpp` via the forward declaration of `g_x`.

Note that the `extern` keyword has different meanings in different contexts. In some contexts, `extern` means “give this variable external linkage”. In other contexts, `extern` means “this is a forward declaration for an external variable that is defined somewhere else”. Yes, this is confusing, so we summarize all of these usages in lesson [7.12 -- Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/).
#### Warning
If you want to define an uninitialized non-const global variable, do not use the extern keyword, otherwise C++ will think you’re trying to make a forward declaration for the variable.

#### Warning
Although constexpr variables can be given external linkage via the `extern` keyword, they can not be forward declared as constexpr. This is because the compiler needs to know the value of the constexpr variable (at compile time). If that value is defined in some other file, the compiler has no visibility on what value was defined in that other file.
However, you can forward declare a constexpr variable as const, which the compiler will treat as a runtime const. This isn’t particularly useful.

Note that function forward declarations don’t need the `extern` keyword -- the compiler is able to tell whether you’re defining a new function or making a forward declaration based on whether you supply a function body or not. Variables forward declarations _do_ need the `extern` keyword to help differentiate uninitialized variables definitions from variable forward declarations (they look otherwise identical):
```cpp
// non-constant
int g_x;        // variable definition (no initializer)
int g_x { 1 };  // variable definition (w/ initializer)
extern int g_x; // forward declaration (no initializer)

// constant
extern const int g_y { 1 }; // variable definition (const requires initializers)
extern const int g_y;       // forward declaration (no initializer)
```

### Avoid using `extern` on a non-const global variable with an initializer
The following two lines are semantically equivalent:
```cpp
int g_x { 1 };        // extern by default
extern int g_x { 1 }; // explicitly extern (may cause compiler warning)
```

However, your compiler may issue a warning about the latter statement, even though it is technically valid.

Remember when we said compilers have the leeway to issue a diagnostic for things they find suspicious? This is one of those cases. Conventionally, `extern` is applied to a non-const variable when we want a forward declaration. However, adding an initializer makes the statement a definition instead. The compiler is telling you that something seems amiss. To correct it, either remove the initializer (if you intended a forward declaration) or remove the `extern` (if you intended a definition).

#### Best practice
Only use `extern` for global variable forward declarations or const global variable definitions.  
Do not use `extern` for non-const global variable definitions (they are implicitly `extern`).
### Quick summary
```cpp
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```
We provide a comprehensive summary in lesson [7.12 -- Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/).

### Quiz time
What’s the difference between a variable’s scope, duration, and linkage? 
Scope determines where a variable is accessible. Duration determines when a variable is created and destroyed. Linkage determines whether the variable can be exported to another file or not.

What kind of scope, duration, and linkage do global variables have?
Global variables have global scope (a.k.a. file scope), which means they can be accessed from the point of declaration to the end of the file in which they are declared.
Global variables have static duration, which means they are created when the program is started, and destroyed when it ends.
Global variables can have either internal or external linkage, via the static and extern keywords respectively.

## 7.8 [Why (non-const) global variables are evil](https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/)
If you were to ask a veteran programmer for _one_ piece of advice on good programming practices, after some thought, the most likely answer would be, “Avoid global variables!”. And with good reason: global variables are one of the most historically abused concepts in the language. Although they may seem harmless in small academic programs, they are often problematic in larger ones.

New programmers are often tempted to use lots of global variables, because they are easy to work with, especially when many calls to different functions are involved (passing data through function parameters is a pain). However, this is generally a bad idea. Many developers believe non-const global variables should be avoided completely!

But before we go into why, we should make a clarification. When developers tell you that global variables are evil, they’re usually not talking about _all_ global variables. They’re mostly talking about non-const global variables.

### Why (non-const) global variables are evil
By far the biggest reason non-const global variables are dangerous is because their values can be changed by _any_ function that is called, and there is no easy way for the programmer to know that this will happen. Consider the following program:
```cpp
#include <iostream>

int g_mode; // declare global variable (will be zero-initialized by default)

void doSomething()
{
    g_mode = 2; // set the global g_mode variable to 2
}

int main()
{
    g_mode = 1; // note: this sets the global g_mode variable to 1.  It does not declare a local g_mode variable!

    doSomething();

    // Programmer still expects g_mode to be 1
    // But doSomething changed it to 2!

    if (g_mode == 1)
    {
        std::cout << "No threat detected.\n";
    }
    else
    {
        std::cout << "Launching nuclear missiles...\n";
    }

    return 0;
}
```

Note that the programmer set variable `g_mode` to _1_, and then called `doSomething()`. Unless the programmer had explicit knowledge that `doSomething()` was going to change the value of `g_mode`, he or she was probably not expecting `doSomething()` to change the value! Consequently, the rest of `main()` doesn’t work like the programmer expects (and the world is obliterated).

In short, global variables make the program’s state unpredictable. Every function call becomes potentially dangerous, and the programmer has no easy way of knowing which ones are dangerous and which ones aren’t! Local variables are much safer because other functions can not affect them directly.

There are plenty of other good reasons not to use non-const globals.

With global variables, it’s not uncommon to find a piece of code that looks like this:

```cpp
void someFunction()
{
    // useful code

    if (g_mode == 4)
    {
        // do something good
    }
}
```

After debugging, you determine that your program isn’t working correctly because `g_mode` has value `3`, not _4_. How do you fix it? Now you need to find all of the places `g_mode` could possibly be set to `3`, and trace through how it got set in the first place. It’s possible this may be in a totally unrelated piece of code!

One of the key reasons to declare local variables as close to where they are used as possible is because doing so minimizes the amount of code you need to look through to understand what the variable does. Global variables are at the opposite end of the spectrum -- because they can be accessed anywhere, you might have to look through the entire program to understand their usage. In small programs, this might not be an issue. In large ones, it will be.

For example, you might find `g_mode` is referenced 442 times in your program. Unless `g_mode` is well documented, you’ll potentially have to look through every use of `g_mode` to understand how it’s being used in different cases, what its valid values are, and what its overall function is.

Global variables also make your program less modular and less flexible. A function that utilizes nothing but its parameters and has no side effects is perfectly modular. Modularity helps both in understanding what a program does, as well as with reusability. Global variables reduce modularity significantly.

In particular, avoid using global variables for important “decision-point” variables (e.g. variables you’d use in a conditional statement, like variable `g_mode` in the example above). Your program isn’t likely to break if a global variable holding an informational value changes (e.g. like the user’s name). It is much more likely to break if you change a global variable that impacts _how_ your program actually functions.
#### Best practice
Use local variables instead of global variables whenever possible.

### The initialization order problem of global variables
Initialization of static variables (which includes global variables) happens as part of program startup, before execution of the `main` function. This proceeds in two phases.

The first phase is called **static initialization**. Static initialization proceeds in two phases:

- Global variables with constexpr initializers (including literals) are initialized to those values. This is called **constant initialization**.
- Global variables without initializers are zero-initialized. Zero-initialization is considered to be a form of static-initialization since `0` is a constexpr value.

The second phase is called **dynamic initialization**. This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.

Here’s an example of a non-constexpr initializer:
```cpp
int init()
{
    return 5;
}

int g_something{ init() }; // non-constexpr initialization
```

Within a single file, for each phase, global variables are generally initialized in order of definition (there are a few exceptions to this rule for the dynamic initialization phase). Given this, you need to be careful not to have variables dependent on the initialization value of other variables that won’t be initialized until later. For example:
```cpp
#include <iostream>

int initX();  // forward declaration
int initY();  // forward declaration

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
    return g_y; // g_y isn't initialized when this is called
}

int initY()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}
```
This prints:
0 5

Much more of a problem, the order in which static objects are initialized across different translation units is ambiguous.

Given two files, _a.cpp_ and _b.cpp_, either could have its global variables initialized first. If some variable with static duration in _a.cpp_ is initialized with a static duration variable defined in _b.cpp_, there’s a 50% chance that the variable in _b.cpp_ won’t be initialized yet.

#### Nomenclature
The ambiguity in the order that objects with static storage duration in different translation units are initialized is often called the [static initialization order fiasco](https://en.cppreference.com/w/cpp/language/siof).
#### Warning
Avoid initializing objects with static duration using other objects with static duration from a different translation unit.
Dynamic initialization of global variables is also susceptible to initialization order issues and should be avoided whenever possible.

### So what are very good reasons to use non-const global variables?

There aren’t many. In most cases, using local variables and passing them as arguments to other functions is preferable. But in some cases, judicious use of non-const global variables _can_ actually reduce program complexity, and in these rare cases, their use may be better than the alternatives.

A good example is a log file, where you can dump error or debug information. It probably makes sense to define this as a global, because you’re likely to only have one such log in a program and it will likely be used everywhere in your program. Another good example would be a random number generator (we show an example of this in lesson [8.15 -- Global random numbers (Random.h)](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)).

For what it’s worth, the std::cout and std::cin objects are implemented as global variables (inside the _std_ namespace).

As a rule of thumb, any use of a global variable should meet at least the following two criteria: There should only ever be one of the thing the variable represents in your program, and its use should be ubiquitous throughout your program.

Many new programmers make the mistake of thinking that something can be implemented as a global because only one is needed _right now_. For example, you might think that because you’re implementing a single player game, you only need one player. But what happens later when you want to add a multiplayer mode (versus or hotseat)?
### Protecting yourself from global destruction

If you do find a good use for a non-const global variable, a few useful bits of advice will minimize the amount of trouble you can get into. This advice isn’t only for non-const global variables, but can help with all global variables.

First, prefix all non-namespaced global variables with “g” or “g_”, or better yet, put them in a namespace (discussed in lesson [7.2 -- User-defined namespaces and the scope resolution operator](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/)), to reduce the chance of naming collisions.

For example, instead of:
```cpp
#include <iostream>

constexpr double gravity { 9.8 }; // risk of collision with some other global variable named gravity

int main()
{
    std::cout << gravity << '\n'; // unclear if this is a local or global variable from the name

    return 0;
}
```

Do this:
```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 }; // will not collide with other global variables named gravity
}

int main()
{
    std::cout << constants::gravity << '\n'; // clear this is a global variable (since namespaces are global)

    return 0;
}
```

Second, instead of allowing direct access to the global variable, it’s a better practice to “encapsulate” the variable. Make sure the variable can only be accessed from within the file it’s declared in, e.g. by making the variable static or const, then provide external global “access functions” to work with the variable. These functions can ensure proper usage is maintained (e.g. do input validation, range checking, etc…). Also, if you ever decide to change the underlying implementation (e.g. move from one database to another), you only have to update the access functions instead of every piece of code that uses the global variable directly.

For example, instead of this:

constants.cpp:
```cpp
namespace constants
{
    extern const double gravity { 9.8 }; // has external linkage, can be accessed by other files
}
```

main.cpp:
```cpp
#include <iostream>

namespace constants
{
    extern const double gravity; // forward declaration
}

int main()
{
    std::cout << constants::gravity << '\n'; // direct access to global variable

    return 0;
}
```

Do this:

contants.cpp:
```cpp
namespace constants
{
    constexpr double gravity { 9.8 }; // has internal linkage, is accessible only within this file
}

double getGravity() // has external linkage, can be accessed by other files
{
    // We could add logic here if needed later
    // or change the implementation transparently to the callers
    return constants::gravity;
}
```

main.cpp:
```cpp
#include <iostream>

double getGravity(); // forward declaration

int main()
{
    std::cout << getGravity() << '\n';

    return 0;
}
```

#### A reminder
Global `const` variables have internal linkage by default, `gravity` doesn’t need to be `static`.

Third, when writing an otherwise standalone function that uses the global variable, don’t use the variable directly in your function body. Pass it in as an argument instead. That way, if your function ever needs to use a different value for some circumstance, you can simply vary the argument. This helps maintain modularity.

Instead of:

```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 };
}

// This function is only useful for calculating your instant velocity based on the global gravity
double instantVelocity(int time)
{
    return constants::gravity * time;
}

int main()
{
    std::cout << instantVelocity(5) << '\n';

    return 0;

}
```

Do this:

```cpp
#include <iostream>

namespace constants
{
    constexpr double gravity { 9.8 };
}

// This function can calculate the instant velocity for any gravity value (more useful)
double instantVelocity(int time, double gravity)
{
    return gravity * time;
}

int main()
{
    std::cout << instantVelocity(5, constants::gravity) << '\n'; // pass our constant to the function as a parameter

    return 0;
}
```

## 7.9 [Inline functions and variables](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/) Moved
Consider the case where you need to write some code to perform some discrete task, like reading input from the user, or outputting something to a file, or calculating a particular value. When implementing this code, you essentially have two options:

1. Write the code as part of an existing function (called writing code “in-place” or “inline”).
2. Create a new function (and possibly sub-functions) to handle the task.

Putting the code in a new function provides many potential benefits, as small functions:

- Are easier to read and understand in the context of the overall program.
- Are easier to reuse, as functions are naturally modular.
- Are easier to update, as the code only needs to be modified in one place.

However, one downside of using a new function is that every time a function is called, there is a certain amount of performance overhead that occurs. Consider the following example:

```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```

When a call to `min()` is encountered, the CPU must store the address of the current instruction it is executing (so it knows where to return to later) along with the values of various CPU registers (so they can be restored upon returning). Then parameters `x` and `y` must be instantiated and then initialized. Then the execution path has to jump to the code in the `min()` function. When the function ends, the program has to jump back to the location of the function call, and the return value has to be copied so it can be output. This has to be done for each function call.  
All of the extra work that must happen to setup, facilitate, and/or cleanup after some task (in this case, making a function call) is called **overhead**.

For functions that are large and/or perform complex tasks, the overhead of the function call is typically insignificant compared to the amount of time the function takes to run. However, for small functions (such as `min()` above), the overhead costs can be larger than the time needed to actually execute the function’s code! In cases where a small function is called often, using a function can result in a significant performance penalty over writing the same code in-place.

### Inline expansion
Fortunately, the C++ compiler has a trick that it can use to avoid such overhead cost: **Inline expansion** is a process where a function call is replaced by the code from the called function’s definition.

For example, if the compiler expanded the `min()` calls in the above example, the resulting code would look like this:
```cpp
#include <iostream>

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n';
    std::cout << ((3 < 2) ? 3 : 2) << '\n';
    return 0;
}
```
Note that the two calls to function `min()` have been replaced by the code in the body of the `min()` function (with the value of the arguments substituted for the parameters). This allows us to avoid the overhead of those calls, while preserving the results of the code.

### The performance of inline code

Beyond removing the cost of function call, inline expansion can also allow the compiler to optimize the resulting code more efficiently -- for example, because the expression `((5 < 6) ? 5 : 6)` is now a constant expression, the compiler could further optimize the first statement in `main()` to `std::cout << 5 << '\n';`.

However, inline expansion has its own potential cost: if the body of the function being expanded takes more instructions than the function call being replaced, then each inline expansion will cause the executable to grow larger. Larger executables tend to be slower (due to not fitting as well in memory caches).

The decision about whether a function would benefit from being made inline (because removal of the function call overhead outweighs the cost of a larger executable) is not straightforward. Inline expansion could result in performance improvements, performance reductions, or no change to performance at all, depending on the relative cost of a function call, the size of the function, and what other optimizations can be performed.

Inline expansion is best suited to simple, short functions (e.g. no more than a few statements), especially cases where a single function call can be executed more than once (e.g. function calls inside a loop).

### When inline expansion occurs

Every function falls into one of two categories, where calls to the function:
- May be expanded (most functions are in this category).
- Can’t be expanded.

Most functions fall into the “may” category: their function calls can be expanded if and when it is beneficial to do so. For functions in this category, a modern compiler will assess each function and each function call to make a determination about whether that particular function call would benefit from inline expansion. A compiler might decide to expand none, some, or all of the function calls to a given function.
#### Tip
Modern optimizing compilers make the decision about when functions should be expanded inline.

The most common kind of function that can’t be expanded inline is a function whose definition is in another translation unit. Since the compiler can’t see the definition for such a function, it doesn’t know what to replace the function call with!
### The inline keyword, historically

Historically, compilers either didn’t have the capability to determine whether inline expansion would be beneficial, or were not very good at it. For this reason, C++ provided the keyword `inline`, which was originally intended to be used as a hint to the compiler that a function would (probably) benefit from being expanded inline.

A function that is declared using the `inline` keyword is called an **inline function**.

Here’s an example of using the `inline` keyword:

```cpp
#include <iostream>

inline int min(int x, int y) // inline keyword means this function is an inline function
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```

However, in modern C++, the `inline` keyword is no longer used to request that a function be expanded inline. There are quite a few reasons for this:

- Using `inline` to request inline expansion is a form of premature optimization, and misuse could actually harm performance.
- The `inline` keyword is just a hint to help the compiler determine where to perform inline expansion. The compiler is completely free to ignore the request, and it may very well do so. The compiler is also free to perform inline expansion of functions that do not use the `inline` keyword as part of its normal set of optimizations.
- The `inline` keyword is defined at the wrong level of granularity. We use the `inline` keyword on a function definition, but inline expansion is actually determined per function call. It may be beneficial to expand some function calls and detrimental to expand others, and there is no syntax to influence this.

Modern optimizing compilers are typically good at determining which function calls should be made inline -- better than humans in most cases. As a result, the compiler will likely ignore or devalue any use of `inline` to request inline expansion for your functions.
#### Best practice
Do not use the `inline` keyword to request inline expansion for your functions.

### The inline keyword, modernly
In previous chapters, we mentioned that you should not implement functions (with external linkage) in header files, because when those headers are included into multiple .cpp files, the function definition will be copied into multiple .cpp files. These files will then be compiled, and the linker will throw an error because it will note that you’ve defined the same function more than once, which is a violation of the one-definition rule.

In modern C++, the term `inline` has evolved to mean “multiple definitions are allowed”. Thus, an inline function is one that is allowed to be defined in multiple translation units (without violating the ODR).

Inline functions have two primary requirements:

- The compiler needs to be able to see the full definition of an inline function in each translation unit where the function is used (a forward declaration will not suffice on its own). Only one such definition can occur per translation unit, otherwise a compilation error will occur.
- The definition can occur after the point of use if a forward declaration is also provided. However, the compiler will likely not be able to perform inline expansion until it has seen the definition (so any uses between the declaration and definition will probably not be candidates for inline expansion).
- Every definition for an inline function (with external linkage, which functions have by default) must be identical, otherwise undefined behavior will result.

#### Rule
The compiler needs to be able to see the full definition of an inline function wherever it is used, and all definitions for an inline function (with external linkage) must be identical (or undefined behavior will result).

#### Related content
We cover internal linkage in lesson [7.6 -- Internal linkage](https://www.learncpp.com/cpp-tutorial/internal-linkage/) and external linkage in lesson [7.7 -- External linkage and variable forward declarations](https://www.learncpp.com/cpp-tutorial/external-linkage-and-variable-forward-declarations/).

The linker will consolidate all inline function definitions for an identifier into a single definition (thus still meeting the requirements of the one definition rule).

Here’s an example:

main.cpp:
```cpp
#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; }

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

math.cpp
```cpp
inline double pi() { return 3.14159; }

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

Notice that both files have a definition for function `pi()` -- however, because this function has been marked as `inline`, this is acceptable, and the linker will de-duplicate them. If you remove the `inline` keyword from both definitions of `pi()`, you’ll get an ODR violation (as duplicate definitions for non-inline functions are disallowed).
#### Optional reading

While the historic use of inline (to perform inline expansion) and the modern use of inline (to allow multiple definitions) may seem a bit unrelated, they are highly interconnected.

Historically, let’s say we had some trivial function that is a great candidate for inline expansion, so we mark it as `inline`. In order to actually perform inline expansion of a function call, the compiler must be able to see the full definition of this function in each translation unit where the function is used -- otherwise it wouldn’t know what to replace each function call with. A function defined in another translation unit can’t be inline expanded in the current translation unit being compiled.

It’s common for trivial inline functions to be needed in multiple translation units. But as soon as we copy the function definition into each translation unit (per the prior requirement), this ends up violating the ODR’s requirement that a function only have a single definition per program. The best solution to this issue was simply to make inline functions exempt from the ODR requirement that there only be a single definition per program.

So historically, we used `inline` to request inline expansion, and the ODR-exemption was a detail that was required to make such functions inline expandable across multiple translation units. Modernly, we use `inline` for the ODR-exemption, and let the compiler handle the inline expansion stuff. The mechanics of how inline functions work hasn’t changed, our focus has.

You might be wondering why inline functions were allowed to be ODR-exempt but non-inline functions still must adhere to this part of the ODR. With non-inline functions, we expect a function to be defined exactly once (in a single translation unit). If the linker runs across multiple definitions of a non-inline function, it assumes this is due to a naming conflict between two independently defined functions. And any call to a non-inline function with more than one definition would lead to potential ambiguity about which definition is the correct one to call. But with inline functions, all definitions are assumed to be for the same inline function, so the function calls within that translation unit can be expanded inline. And if a function call isn’t expanded inline, there is no ambiguity about which of multiple definitions is the correct one for the call to match with -- any of them are fine!


Inline functions are typically defined in header files, where they can be #included into the top of any code file that needs to see the full definition of the identifier. This ensures that all inline definitions for an identifier are identical.

pi.h:
```cpp
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif
```

main.cpp:
```cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

math.cpp:
```cpp
#include "pi.h" // will include a copy of pi() here

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```

This is particularly useful for **header-only libraries**, which are one or more header files that implement some capability (no .cpp files are included). Header-only libraries are popular because there are no source files that need to be added to a project to use them and nothing that needs to be linked. You simply #include the header-only library and then can use it.
#### Related content
We show a practical example where inline is used for a random number generation header-only library in lesson [8.15 -- Global random numbers (Random.h)](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/).

#### For advanced readers
The following functions are implicitly inline:
- Functions defined inside a class, struct, or union type definition ([14.3 -- Member functions](https://www.learncpp.com/cpp-tutorial/member-functions/)).
- Constexpr / consteval functions ([F.1 -- Constexpr functions](https://www.learncpp.com/cpp-tutorial/constexpr-functions/)).
- Functions implicitly instantiated from function templates ([11.7 -- Function template instantiation](https://www.learncpp.com/cpp-tutorial/function-template-instantiation/)).

For the most part, you should not mark your functions or variables as inline unless you are defining them in a header file (and they are not already implicitly inline).
#### Best practice
Avoid the use of the `inline` keyword unless you have a specific, compelling reason to do so (e.g. you’re defining those functions or variables in a header file).

### Why not make all functions inline and defined in a header file?

Mainly because doing so can increase your compile times significantly.

When a header containing an inline function is #included into a source file, that function definition will be compiled as part of that translation unit. An inline function #included into 6 translation units will have its definition compiled 6 times (before the linker deduplicates the definitions). Conversely, a function defined in a source file will have its definition compiled only once, no matter how many translation units its forward declaration is included into.

Second, if a function defined in a source file changes, only that single source file needs to be recompiled. When an inline function in a header file changes, every code file that includes that header (either directly or via another header) needs to recompiled. On large projects, this can cause a cascade of recompilation and have a drastic impact.

### Inline variables C++17

In the above example, `pi()` was written as a function that returns a constant value. It would be more staightforward if `pi` were implemented as a (const) variable instead. However, prior to C++17, there were some obstacles and inefficiencies in doing so.

C++17 introduces **inline variables**, which are variables that are allowed to be defined in multiple files. Inline variables work similarly to inline functions, and have the same requirements (the compiler must be able to see an identical full definition everywhere the variable is used).

#### For advanced readers
The following variables are implicitly inline:
- Static constexpr data members [15.6 -- Static member variables](https://www.learncpp.com/cpp-tutorial/static-member-variables/).
Unlike constexpr functions, constexpr variables are not inline by default (excepting those noted above)!

We’ll illustrate a common use for inline variables in lesson [7.10 -- Sharing global constants across multiple files (using inline variables)](https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/).


## 7.10 [Sharing global constants across multiple files (using inline variables)](https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/)

In some applications, certain symbolic constants may need to be used throughout your code (not just in one location). These can include physics or mathematical constants that don’t change (e.g. pi or Avogadro’s number), or application-specific “tuning” values (e.g. friction or gravity coefficients). Instead of redefining these constants in every file that needs them (a violation of the “Don’t Repeat Yourself” rule), it’s better to declare them once in a central location and use them wherever needed. That way, if you ever need to change them, you only need to change them in one place, and those changes can be propagated out.

This lesson discusses the most common ways to do this.

### Global constants as internal variables

Prior to C++17, the following is the easiest and most common solution:

1. Create a header file to hold these constants
2. Inside this header file, define a namespace (discussed in lesson [7.2 -- User-defined namespaces and the scope resolution operator](https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/))
3. Add all your constants inside the namespace (make sure they’re _constexpr_)
4. #include the header file wherever you need it

For example:
constants.h:
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define your own namespace to hold constants
namespace constants
{
    // Global constants have internal linkage by default
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

Then use the scope resolution operator (::) with the namespace name to the left, and your variable name to the right in order to access your constants in .cpp files:

main.cpp:
```cpp
#include "constants.h" // include a copy of each constant in this file

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```
When this header gets `#included `into a .cpp file, each of these variables defined in the header will be copied into that code file at the point of inclusion. Because these variables live outside of a function, they’re treated as global variables within the file they are included into, which is why you can use them anywhere in that file.

Because const globals have internal linkage, each .cpp file gets an independent version of the global variable that the linker can’t see. In most cases, because these are constexpr, the compiler will simply optimize the variables away.

While this is simple (and fine for smaller programs), every time _constants.h_ gets #included into a different code file, each of these variables is copied into the including code file. Therefore, if constants.h gets included into 20 different code files, each of these variables is duplicated 20 times. Header guards won’t stop this from happening, as they only prevent a header from being included more than once into a single including file, not from being included one time into multiple different code files. This introduces two challenges:
1. Changing a single constant value would require recompiling every file that includes the constants header, which can lead to lengthy rebuild times for larger projects.
2. If the constants are large in size and can’t be optimized away, this can use a lot of memory.

Advantages:
- Works prior to C++17.
- Can be used in constant expressions in any translation unit that includes them.

Downsides:
- Changing anything in the header file requires recompiling files including the header.
- Each translation unit including the header gets its own copy of the variable.

### Global constants as external variables

If you’re actively changing values or adding new constants, the prior solution might be problematic, at least until things settle.

One way to avoid these problems is by turning these constants into external variables, since we can then have a single variable (initialized once) that is shared across all files. In this method, we’ll define the constants in a .cpp file (to ensure the definitions only exist in one place), and put forward declarations in the header (which will be included by other files).

constants.cpp:
```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

constants.h:
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    // Since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    // We can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
    extern const double pi;
    extern const double avogadro;
    extern const double myGravity;
}

#endif
```

Use in the code file stays the same:

main.cpp:

```cpp
#include "constants.h" // include all the forward declarations

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

Now the symbolic constants will get instantiated only once (in _constants.cpp_) instead of in each code file where _constants.h_ is #included, and all uses of these constants will be linked to the version instantiated in _constants.cpp_. Any changes made to _constants.cpp_ will require recompiling only _constants.cpp_.

However, there are a couple of downsides to this method. First, because only the variable definitions are constexpr (the forward declarations aren’t, and can’t be), these constants are constant expressions only within the file they are actually defined in (_constants.cpp_). In other files, the compiler will only see the forward declaration, which doesn’t define a constexpr value (and must be resolved by the linker). This means outside of the file where they are defined, these variables can’t be used in a constant expression. Second, because constant expressions can typically be optimized more than runtime expressions, the compiler may not be able to optimize these as much.
#### Key insight
In order for variables to be usable in compile-time contexts, such as array sizes, the compiler has to see the variable’s definition (not just a forward declaration).

Because the compiler compiles each source file individually, it can only see variable definitions that appear in the source file being compiled (which includes any included headers). For example, variable definitions in _constants.cpp_ are not visible when the compiler compiles _main.cpp_. For this reason, constexpr variables cannot be separated into header and source file, they have to be defined in the header file.

Given the above downsides, prefer defining your constants in a header file (either per the prior section, or per the next section). If you find that the values for your constants are changing a lot (e.g. because you are tuning the program) and this is leading to long compilation times, you can temporarily move just the offending constants into a .cpp file (using this method) as needed.

Advantages:

- Works prior to C++17.
- Only one copy of each variable is required.
- Only requires recompilation of one file if the value of a constant changes.

Disadvantages:

- Forward declarations and variable definitions are in separate files, and must be kept in sync.
- Variables not usable in constant expressions outside of the file in which they are defined.
- 
### Global constants as inline variables C++17
In lesson [7.9 -- Inline functions and variables](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/), we covered inline variables, which are variables that can have more than one definition, so long as those definitions are identical. By making our constexpr variables inline, we can define them in a header file and then #include them into any .cpp file that requires them. This avoids both ODR violations and the downside of duplicated variables.

#### A reminder
Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline. If you want an inline constexpr variable, you must explicitly mark it as `inline`.
#### Key insight
Inline variables have external linkage by default, so that they are visible to the linker. This is necessary so the linker can de-duplicate the definitions.
Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.

constants.h:
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

main.cpp:
```cpp
#include "constants.h"

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```
We can include `constants.h` into as many code files as we want, but these variables will only be instantiated once and shared across all code files.

This method does retain the downside of requiring every file that includes the constants header be recompiled if any constant value is changed.

Advantages:
- Can be used in constant expressions in any translation unit that includes them.
- Only one copy of each variable is required.

Downsides:
- Only works in C++17 onward.
- Changing anything in the header file requires recompiling files including the header.
#### Best practice
If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.

#### A reminder
Use `std::string_view` for `constexpr` strings. We cover this in lesson [5.8 -- Introduction to std::string_view](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/).

#### Related content
We summarize the scope, duration, and linkage of various kinds of variables in lesson [7.12 -- Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/).

## 7.11 [Static local variables](https://www.learncpp.com/cpp-tutorial/static-local-variables/)
The term `static` is one of the most confusing terms in the C++ language, in large part because `static` has different meanings in different contexts.

In prior lessons, we covered that global variables have static duration, which means they are created when the program starts and destroyed when the program ends.

We also discussed how the `static` keyword gives a global identifier internal-linkage, which means the identifier can only be used in the file in which it is defined.

In this lesson, we’ll explore the use of the `static` keyword when applied to a local variable.

### Static local variables
In lesson [2.5 -- Introduction to local scope](https://www.learncpp.com/cpp-tutorial/introduction-to-local-scope/), you learned that local variables have automatic duration by default, which means they are created at the point of definition, and destroyed when the block is exited.

Using the `static` keyword on a local variable changes its duration from automatic duration to static duration. This means the variable is now created at the start of the program, and destroyed at the end of the program (just like a global variable). As a result, the static variable will retain its value even after it goes out of scope!

The easiest way to show the difference between automatic duration and static duration local variables is by example.

Automatic duration (default):
```cpp
#include <iostream>

void incrementAndPrint()
{
    int value{ 1 }; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```

Each time `incrementAndPrint()` is called, a variable named value is created and assigned the value of `1`. `incrementAndPrint()` increments value to `2`, and then prints the value of `2`. When `incrementAndPrint()` is finished running, the variable goes out of scope and is destroyed. Consequently, this program outputs:
```
2
2
2
```
Now consider a version of this program that uses a static local variable. The only difference between this and the above program is that we’ve changed the local variable from automatic duration to static duration by using the `static` keyword.

Static duration (using static keyword):
```cpp
#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```

In this program, because `s_value` has been declared as `static`, it is created at the program start.

Static local variables that are zero-initialized or have a constexpr initializer can be initialized at program start.

Static local variables that have no initializer or a non-constexpr initializer are zero-initialized at program start. Static local variables with a non-constexpr initializer are reinitialized the first time the variable definition is encountered. The definition is skipped on subsequent calls, so no futher reinitialization happens. Because they have static duration, static local variables that are not explicitly initialized will be zero-initialized by default.

Because `s_value` has constexpr initializer `1`, `s_value` will be initialized at program start.

When `s_value` goes out of scope at the end of the function, it is not destroyed. Each time the function `incrementAndPrint()` is called, the value of `s_value` remains at whatever we left it at previously. Consequently, this program outputs:
```
2
3
4
```

#### Key insight
Static local variables are used when you need a local variable to remember its value across function calls.

#### Best practice
Initialize your static local variables. Static local variables are only initialized the first time the code is executed, not on subsequent calls.

#### Tip
Just like we use “g_” to prefix global variables, it’s common to use “s_” to prefix static (static duration) local variables.

### ID generation

One of the most common uses for static duration local variables is for unique ID generators. Imagine a program where you have many similar objects (e.g. a game where you’re being attacked by many zombies, or a simulation where you’re displaying many triangles). If you notice a defect, it can be near impossible to distinguish which object is having problems. However, if each object is given a unique identifier upon creation, then it can be easier to differentiate the objects for further debugging.

Generating a unique ID number is very easy to do with a static duration local variable:

```cpp
int generateID()
{
    static int s_itemID{ 0 };
    return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
}
```

The first time this function is called, it returns `0`. The second time, it returns `1`. Each time it is called, it returns a number one higher than the previous time it was called. You can assign these numbers as unique IDs for your objects. Because `s_itemID` is a local variable, it can not be “tampered with” by other functions.

Static variables offer some of the benefit of global variables (they don’t get destroyed until the end of the program) while limiting their visibility to block scope. This makes them easier to understand and safer to use.

#### Key insight
A static local variable has block scope like a local variable, but its lifetime is until the end of the program like a global variable.

### Static local constants
Static local variables can be made const (or constexpr). One good use for a const static local variable is when you have a function that needs to use a const value, but creating or initializing the object is expensive (e.g. you need to read the value from a database). If you used a normal local variable, the variable would be created and initialized every time the function was executed. With a const/constexpr static local variable, you can create and initialize the expensive object once, and then reuse it whenever the function is called.

#### Key insight
Static local variables are best used to avoid expensive local object initialization each time a function is called.

### Don’t use static local variables to alter flow
Consider the following code:
```cpp
#include <iostream>

int getInteger()
{
	static bool s_isFirstCall{ true };

	if (s_isFirstCall)
	{
		std::cout << "Enter an integer: ";
		s_isFirstCall = false;
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger() };
	int b{ getInteger() };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}
```

Sample output

Enter an integer: 5
Enter another integer: 9
5 + 9 = 14

This code does what it’s supposed to do, but because we used a static local variable, we made the code harder to understand. If someone reads the code in `main()` without reading the implementation of `getInteger()`, they’d have no reason to assume that the two calls to `getInteger()` do something different. But the two calls do something different, which can be very confusing if the difference is more than a changed prompt.

Say you press the +1 button on your microwave and the microwave adds 1 minute to the remaining time. Your meal is warm and you’re happy. Before you take your meal out of the microwave, you see a cat outside your window and watch it for a moment, because cats are cool. The moment turned out to be longer than you expected and when you take the first bite of your meal, it’s cold again. No problem, just put it back into the microwave and press +1 to run it for a minute. But this time the microwave adds only 1 second and not 1 minute. That’s when you go “I changed nothing and now it’s broken” or “It worked last time”. If you do the same thing again, you’d expect the same behavior as last time. The same goes for functions.

Suppose we want to add subtraction to the calculator such that the output looks like the following:

Addition
Enter an integer: 5
Enter another integer: 9
5 + 9 = 14
Subtraction
Enter an integer: 12
Enter another integer: 3
12 - 3 = 9

We might try to use `getInteger()` to read in the next two integers like we did for addition.

```cpp
int main()
{
  std::cout << "Addition\n";

  int a{ getInteger() };
  int b{ getInteger() };

  std::cout << a << " + " << b << " = " << (a + b) << '\n';

  std::cout << "Subtraction\n";

  int c{ getInteger() };
  int d{ getInteger() };

  std::cout << c << " - " << d << " = " << (c - d) << '\n';

  return 0;
}
```

But this won’t do as we want, as the output is:

Addition
Enter an integer: 5
Enter another integer: 9
5 + 9 = 14
Subtraction
Enter another integer: 12
Enter another integer: 3
12 - 3 = 9

(The third-to-last line is “Enter another integer” instead of “Enter an integer”)

`getInteger()` is not reusable, because it has an internal state (The static local variable `s_isFirstCall`) which cannot be reset from the outside. `s_isFirstCall` is not a variable that should be unique in the entire program. Although our program worked great when we first wrote it, the static local variable prevents us from reusing the function later on.

One better way of implementing `getInteger` is to pass `s_isFirstCall` as a parameter. This allows the caller to choose which prompt will be printed:

```cpp
#include <iostream>

// We'll define a symbolic constant with a nice name
constexpr bool g_firstCall { true };

int getInteger(bool bFirstCall)
{
	if (bFirstCall)
	{
		std::cout << "Enter an integer: ";
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger(g_firstCall) };  // so that it's clearer what the argument represents here
	int b{ getInteger(!g_firstCall) };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}
```

Non-const static local variables should only be used if in your entire program and in the foreseeable future of your program, the variable is unique and it wouldn’t make sense to reset the variable.

#### Best practice
Const static local variables are generally okay to use.
Non-const static local variables should generally be avoided. If you do use them, ensure the variable never needs to be reset, and isn’t used to alter program flow.

#### Tip
An even more reusable solution would be to change the `bool` parameter to `std::string_view` and let the caller pass in the text prompt that will be used!

#### For advanced readers
In cases where you need multiple instances of a non-const variable that remembers its value (e.g. to have multiple ID generators), a functor is a good solution (see lesson [21.10 -- Overloading the parenthesis operator](https://www.learncpp.com/cpp-tutorial/overloading-the-parenthesis-operator/)).

### Quizz
What effect does using keyword `static` have on a global variable? What effect does it have on a local variable?
When applied to a global variable, the static keyword defines the global variable as having internal linkage, meaning the variable cannot be exported to other files.

When applied to a local variable, the static keyword defines the local variable as having static duration, meaning the variable will only be created once, and will not be destroyed until the end of the program.


## 7.12 [Scope, duration, and linkage summary](https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/)

The concepts of scope, duration, and linkage cause a lot of confusion, so we’re going to take an extra lesson to summarize everything. Some of these things we haven’t covered yet, and they’re here just for completeness / reference later.

### Scope summary

An identifier’s _scope_ determines where the identifier can be accessed within the source code.
- Variables with **block (local) scope** can only be accessed from the point of declaration until the end of the block in which they are declared (including nested blocks). This includes:
    - Local variables
    - Function parameters
    - Program-defined type definitions (such as enums and classes) declared inside a block
- Variables and functions with **global scope** can be accessed from the point of declaration until the end of the file. This includes:
    - Global variables
    - Functions
    - Program-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope

### Duration summary
A variable’s _duration_ determines when it is created and destroyed.
- Variables with **automatic duration** are created at the point of definition, and destroyed when the block they are part of is exited. This includes:
    - Local variables
    - Function parameters
- Variables with **static duration** are created when the program begins and destroyed when the program ends. This includes:
    - Global variables
    - Static local variables
- Variables with **dynamic duration** are created and destroyed by programmer request. This includes:
    - Dynamically allocated variables

### Linkage summary
An identifier’s **linkage** determines whether a declaration of that same identifier in a different scope refers to the same entity (object, function, reference, etc…) or not.

Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.

- An identifier with **no linkage** means another declaration of the same identifier refers to a unique entity. Entities whose identifiers have no linkage include:
    - Local variables
    - Program-defined type identifiers (such as enums and classes) declared inside a block
- An identifier with **internal linkage** means a declaration of the same identifier within the same translation unit refers to the same object or function. Entities whose identifiers have internal linkage include:
    - Static global variables (initialized or uninitialized)
    - Static functions
    - Const global variables
    - Unnamed namespaces and anything defined within them
- An identifier with **external linkage** means a declaration of the same identifier within the entire program refers to the same object or function. Entities whose identifiers have external linkage include:
    - Non-static functions
    - Non-const global variables (initialized or uninitialized)
    - Extern const global variables
    - Inline const global variables
    - Namespaces

Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to violating the one-definition rule). There are some exceptions to this rule (for types, templates, and inline functions and variables) -- we’ll cover these further in future lessons when we talk about those topics.

Also note that functions have external linkage by default. They can be made internal by using the static keyword.

### Variable scope, duration, and linkage summary

Because variables have scope, duration, and linkage, let’s summarize in a chart:

|Type|Example|Scope|Duration|Linkage|Notes|
|---|---|---|---|---|---|
|Local variable|int x;|Block|Automatic|None||
|Static local variable|static int s_x;|Block|Static|None||
|Dynamic local variable|int* x { new int{} };|Block|Dynamic|None||
|Function parameter|void foo(int x)|Block|Automatic|None||
|Internal non-const global variable|static int g_x;|Global|Static|Internal|Initialized or uninitialized|
|External non-const global variable|int g_x;|Global|Static|External|Initialized or uninitialized|
|Inline non-const global variable (C++17)|inline int g_x;|Global|Static|External|Initialized or uninitialized|
|Internal constant global variable|constexpr int g_x { 1 };|Global|Static|Internal|Must be initialized|
|External constant global variable|extern const int g_x { 1 };|Global|Static|External|Must be initialized|
|Inline constant global variable (C++17)|inline constexpr int g_x { 1 };|

### Forward declaration summary
You can use a forward declaration to access a function or variable in another file. The scope of the declared variable is as per usual (global scope for globals, block scope for locals).

|Type|Example|Notes|
|---|---|---|
|Function forward declaration|void foo(int x);|Prototype only, no function body|
|Non-constant variable forward declaration|extern int g_x;|Must be uninitialized|
|Const variable forward declaration|extern const int g_x;|Must be uninitialized|
|Constexpr variable forward declaration|extern constexpr int g_x;|Not allowed, constexpr cannot be forward declared|

A constexpr variable (which is implicitly const) can be forward declared using a const variable forward declaration. When accessed through the forward declaration, the variable will be considered const (not constexpr).


###  What the heck is a storage class specifier?
When used as part of an identifier declaration, the `static` and `extern` keywords are called **storage class specifiers**. In this context, they set the storage duration and linkage of the identifier.

C++ supports 4 active storage class specifiers:

|Specifier|Meaning|Note|
|---|---|---|
|extern|static (or thread_local) storage duration and external linkage||
|static|static (or thread_local) storage duration and internal linkage||
|thread_local|thread storage duration||
|mutable|object allowed to be modified even if containing class is const||
|auto|automatic storage duration|Deprecated in C++11|
|register|automatic storage duration and hint to the compiler to place in a register|Deprecated in C++17|

The term _storage class specifier_ is typically only used in formal documentation.


## 7.13 [Using declarations and using directives](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/)
You’ve probably seen this program in a lot of textbooks and tutorials:

```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!\n";

    return 0;
}
```
If you see this, run. Your textbook or tutorial are probably out of date. In this lesson, we’ll explore why.

Tip
Some IDEs will also auto-populate new C++ projects with a similar program (so you can compile something immediately, rather than starting from a blank file).

### A short history lesson

Back before C++ had support for namespaces, all of the names that are now in the `std` namespace were in the global namespace. This caused naming collisions between program identifiers and standard library identifiers. Programs that worked under one version of C++ might have a naming conflict with a newer version of C++.

In 1995, namespaces were standardized, and all of the functionality from the standard library was moved out of the global namespace and into namespace `std`. This change broke older code that was still using names without `std::`.

As anyone who has worked on a large codebase knows, any change to a codebase (no matter how trivial) risks breaking the program. Updating every name that was now moved into the `std` namespace to use the `std::` prefix was a massive risk. A solution was requested.

Fast forward to today -- if you’re using the standard library a lot, typing `std::` before everything you use from the standard library can become repetitive, and in some cases, can make your code harder to read.

C++ provides some solutions to both of these problems, in the form of using-statements.

But first, let’s define two terms.

### Qualified and unqualified names
A name can be either qualified or unqualified.
A **qualified name** is a name that includes an associated scope. Most often, names are qualified with a namespace using the scope resolution operator (::). For example:
```cpp
std::cout // identifier cout is qualified by namespace std
::foo // identifier foo is qualified by the global namespace
```
#### For advanced readers
A name can also be qualified by a class name using the scope resolution operator (::), or by a class object using the member selection operators (. or ->). For example:
```cpp
class C; // some class

C::s_member; // s_member is qualified by class C
obj.x; // x is qualified by class object obj
ptr->y; // y is qualified by pointer to class object ptr
```

An **unqualified name** is a name that does not include a scoping qualifier. For example, `cout` and `x` are unqualified names, as they do not include an associated scope.

### Using-declarations
One way to reduce the repetition of typing `std::` over and over is to utilize a using-declaration statement. A **using declaration** allows us to use an unqualified name (with no scope) as an alias for a qualified name.

Here’s our basic Hello world program, using a using-declaration on line 5:

```cpp
#include <iostream>

int main()
{
   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
   cout << "Hello world!\n"; // so no std:: prefix is needed here!

   return 0;
} // the using declaration expires at the end of the current scope
```

The using-declaration `using std::cout;` tells the compiler that we’re going to be using the object `cout` from the `std` namespace. So whenever it sees `cout`, it will assume that we mean `std::cout`. If there’s a naming conflict between `std::cout` and some other use of `cout` that is visible from within `main()`, `std::cout` will be preferred. Therefore on line 6, we can type `cout` instead of `std::cout`.

This doesn’t save much effort in this trivial example, but if you are using `cout` many times inside of a function, a using-declaration can make your code more readable. Note that you will need a separate using-declaration for each name (e.g. one for `std::cout`, one for `std::cin`, etc…).

The using-declaration is active from the point of declaration to the end of the scope in which it is declared.

Although using-declarations are less explicit than using the `std::` prefix, they are generally considered safe and acceptable to use in source (.cpp) files, with one exception that we’ll discuss below.

### Using-directives
Another way to simplify things is to use a using-directive. A **using directive** allows _all_ identifiers in a given namespace to be referenced without qualification from the scope of the using-directive.
#### For advanced readers
For technical reasons, using-directives do not actually introduce new meanings for names into the current scope -- instead they introduce new meanings for names into an outer scope (more details about which outer scope is picked can be found [here](https://quuxplusone.github.io/blog/2020/12/21/using-directive/)).

Here’s our Hello world program again, with a using-directive on line 5:
```cpp
#include <iostream>

int main()
{
   using namespace std; // all names from std namespace now accessible without qualification
   cout << "Hello world!\n"; // so no std:: prefix is needed here

   return 0;
} // the using-directive ends at the end of the current scope
```

The using-directive `using namespace std;` tells the compiler that all of the names in the `std` namespace should be accessible without qualification in the current scope (in this case, of function `main()`). When we then use unqualified identifier `cout`, it will resolve to `std::cout`.

Using-directives are the solution that was provided for old pre-namespace codebases that used unqualified names for standard library functionality. Rather than having to manually update every unqualified name to a qualified name (which was risky), a single using-directive (`using namespace std;`) could be placed at the top of each file, and all of the names that had been moved to the `std` namespace could still be used unqualified.

### Problems with using-directives (a.k.a. why you should avoid “using namespace std;”)[](https://www.learncpp.com/cpp-tutorial/using-declarations-and-using-directives/#avoidUsingNamespace)
In modern C++, using-directives generally offer little benefit (saving some typing) compared to the risk. This is due to two factors:
1. Using-directives allow unqualified access to _all_ of the names from a namespace (potentially including lots of names you’ll never use).
2. Using-directives do not prefer names from the namespace identified by the using-directive over other names.

The end result is that the possibility for naming collisions to occur increases significantly (especially if you import the `std` namespace).

First, let’s take a look at an illustrative example where using-directives cause a naming collision:
```cpp
#include <iostream>

namespace A
{
	int x { 10 };
}

namespace B
{
	int x{ 20 };
}

int main()
{
	using namespace A;
	using namespace B;

	std::cout << x << '\n';

	return 0;
}
```
In the above example, the compiler is unable to determine whether the `x` in `main` refers to `A::x` or `B::x`. In this case, it will fail to compile with an “ambiguous symbol” error. We could resolve this by removing one of the using-directives, employing a using-declaration instead, or qualifying `x` (as `A::x` or `B::x`).

Here’s another more subtle example:
```cpp
#include <iostream> // imports the declaration of std::cout

int cout() // declares our own "cout" function
{
    return 5;
}

int main()
{
    using namespace std; // makes std::cout accessible as "cout"
    cout << "Hello, world!\n"; // uh oh!  Which cout do we want here?  The one in the std namespace or the one we defined above?

    return 0;
}
```
In this example, the compiler is unable to determine whether our unqualified use of `cout` means `std::cout` or the `cout` function we’ve defined, and again will fail to compile with an “ambiguous symbol” error. Although this example is trivial, if we had explicitly prefixed `std::cout` like this:

```cpp
std::cout << "Hello, world!\n"; // tell the compiler we mean std::cout
```

or used a using-declaration instead of a using-directive:
```cpp
using std::cout; // tell the compiler that cout means std::cout
cout << "Hello, world!\n"; // so this means std::cout
```

then our program wouldn’t have any issues in the first place. And while you’re probably not likely to write a function named “cout”, there are hundreds of other names in the `std` namespace just waiting to collide with your names.

Even if a using-directive does not cause naming collisions today, it makes your code more vulnerable to future collisions. For example, if your code includes a using-directive for some library that is then updated, all of the new names introduced in the updated library are now candidates for naming collisions with your existing code.

For example, the following program compiles and runs fine:

FooLib.h (part of some third-party library):
```cpp
#ifndef FOOLIB
#define FOOLIB

namespace Foo
{
    int a { 20 };
}

#endif
```

main.cpp:
```cpp
#include <iostream>
#include <FooLib.h> // a third-party library we installed outside our project directory, thus angled brackets used

void print()
{
    std::cout << "Hello\n";
}

int main()
{
    using namespace Foo; // Because we're lazy and want to access Foo:: qualified names without typing the Foo:: prefix

    std::cout << a << '\n'; // uses Foo::a
    print(); // calls ::print()

    return 0;
}
```

Now let’s say you update FooLib to a new version, and FooLib.h changes to this:

FooLib.h (updated):
```cpp
#ifndef FOOLIB
#define FOOLIB

namespace Foo
{
    int a { 20 };
    void print() { std::cout << "Timmah!"; } // This function added
}
#endif
```
Your main.cpp hasn’t changed, but it will no longer compile! This is because our using-directive causes `Foo::print()` to be accessible as just `print()`, and it is now ambiguous whether the call to `print()` means `::print()` or `Foo::print()`.

There is a more insidious version of this problem that can occur as well. The updated library may introduce a function that not only has the same name, but is actually a better match for some function call. In such a case, the compiler may decide to prefer the new function instead, and the behavior of your program will change unexpectedly and silently.

Consider the following program:

Foolib.h (part of some third-party library):
```cpp
#ifndef FOOLIB_H
#define FOOLIB_H

namespace Foo
{
    int a { 20 };
}
#endif
```

main.cpp:
```cpp
#include <iostream>
#include <Foolib.h> // a third-party library we installed outside our project directory, thus angled brackets used

int get(long)
{
    return 1;
}

int main()
{
    using namespace Foo; // Because we're lazy and want to access Foo:: qualified names without typing the Foo:: prefix
    std::cout << a << '\n'; // uses Foo::a

    std::cout << get(0) << '\n'; // calls ::get(long)

    return 0;
}
```

This program runs and prints `1`.

Now, let’s say we update the Foolib library, which includes an updated Foolib.h that looks like this:

Foolib.h (updated):
```cpp
#ifndef FOOLIB_H
#define FOOLIB_H

namespace Foo
{
    int a { 20 };

    int get(int) { return 2; } // new function added
}
#endif
```

Once again, our `main.cpp` file hasn’t changed at all, but this program now compiles, runs, and prints `2`!

When the compiler encounters a function call, it has to determine what function definition it should match the function call with. In selecting a function from a set of potentially matching functions, it will prefer a function that requires no argument conversions over a function that requires argument conversions. Because the literal `0` is an integer, C++ will prefer to match `print(0)` with the newly introduced `print(int)` (no conversions) over `print(long)` (which requires a conversion from `int` to `long`). That causes an unexpected change to our program behavior.

In this case, the change in behavior is fairly obvious. But in a more complex program, where the returned value isn’t just printed, this issue could be very difficult to discover.

This would not have happened if we’d used a using-declaration or explicit scope qualifier.

Finally, the lack of explicit scope prefixes make it harder for a reader to tell what functions are part of a library and what’s part of your program. For example, if we use a using-directive:

```cpp
using namespace NS;

int main()
{
    foo(); // is this foo a user-defined function, or part of the NS library?
}
```

It’s unclear whether the call to `foo()` is actually a call to `NS::foo()` or to a `foo()` that is a user-defined function. Modern IDEs should be able to disambiguate this for you when you hover over a name, but having to hover over each name just to see where it comes from is tedious.

Without the using-directive, it’s much clearer:

```cpp
int main()
{
    NS::foo(); // clearly part of the NS library
    foo(); // likely a user-defined function
}
```

In this version, the call to `NS::foo()` is clearly a library call. The call to plain `foo()` is probably a call to a user-defined function (some libraries, including certain standard library headers, do put names into the global namespace, so it’s not a guarantee).

The scope of using-statements

If a using-declaration or using-directive is used within a block, the names are applicable to just that block (it follows normal block scoping rules). This is a good thing, as it reduces the chances for naming collisions to occur to just within that block.

If a using-declaration or using-directive is used in a namespace (including the global namespace), the names are applicable to the entire rest of the file (they have file scope).

### The scope of using-statements
If a using-declaration or using-directive is used within a block, the names are applicable to just that block (it follows normal block scoping rules). This is a good thing, as it reduces the chances for naming collisions to occur to just within that block.

If a using-declaration or using-directive is used in a namespace (including the global namespace), the names are applicable to the entire rest of the file (they have file scope).


### Do not use using-statements in header files, or before an #include directive
A good rule of thumb is that using-statements should not be placed anywhere where they might have an impact on code in a different file. Nor should they be placed anywhere where another file’s code might be able to impact them.

More specifically, this means using-statements should not be used in header files, nor before an #include directive.

For example, if you placed a using-statement in the global namespace of a header file, then every other file that #included that header would also get that using-statement. That’s clearly bad. This also applies to namespaces inside header files, for the same reason.

But what about using-statements within functions defined inside header files? Surely that can’t be bad since the scope of the using-statement is contained to the function, right? Even that’s a no. And it’s a no for the same reason that we shouldn’t use using-statements before an #include directive.

It turns out that the behavior of using-statements is dependent on what identifiers have already been introduced. This makes them order-dependent, as their function may change if the identifiers that have been introduced before them change.

We will illustrate this with an example:

FooInt.h:
```cpp
namespace Foo
{
    void print(int)
    {
        std::cout << "print(int)\n" << std::endl;
    }
}
```

FooDouble.h:
```cpp
namespace Foo
{
    void print(double)
    {
        std::cout << "print(double)\n" << std::endl;
    }
}
```

main.cpp (okay):
```cpp
#include <iostream>

#include "FooDouble.h"
#include "FooInt.h"

using Foo::print; // print means Foo::print

int main()
{
    print(5);  // Calls Foo::print(int)
}
```

When run, this program calls `Foo::print(int)`, which prints `print(int)`.

Now let’s change main.cpp slightly.

main.cpp (bad):
```cpp
#include <iostream>

#include "FooDouble.h"

using Foo::print; // we moved the using-statement here, before the #include directive
#include "FooInt.h"

int main()
{
    print(5);  // Calls Foo::print(double)
}
```

All we’ve done is move `using Foo::print;` before `#include "FooInt.h"`. And our program now prints `print(double)`! Regardless of why this happens, you’ll likely agree that this is the kind of behavior we want to avoid!

So then to loop back around, the reason we shouldn’t use using-statements in functions that are defined in header files is the same reason -- we can’t control which other headers might be `#included` before our header, and it’s possible those headers might do something that alters the way our using-statement behaves!

The only place it is truly safe to use using-statements is in our source (.cpp) files, after all the `#includes`.

#### For advanced readers
This example uses a concept we haven’t covered yet called “function overloading” (we cover this in lesson [11.1 -- Introduction to function overloading](https://www.learncpp.com/cpp-tutorial/introduction-to-function-overloading/)). All you need to know for this example is that two functions in the same scope can have the same name so long as the parameters of each are distinct. Since `int` and `double` are distinct types, there is no issue having both `Foo::print(int)` and `Foo::print(double)` living side-by-side.

In the working version, when the compiler encounters `using Foo::print`, it has already seen both `Foo::print(int)` and `Foo::print(double)`, so it makes both available to be called as just `print()`. Since `Foo::print(int)` is a better match than `Foo::print(double)`, it calls `Foo::print(int)`.

In the bad version, when the compiler encounters `using Foo::print`, it has only seen a declaration for `Foo::print(double)`, so it only makes `Foo::print(double)` available to be called unqualified. So when we call `print(5)` only `Foo::print(double)` is even eligible to be matched. Thus `Foo::print(double)` is the one that gets called!

### Cancelling or replacing a using-statement

Once a using-statement has been declared, there’s no way to cancel or replace it with a different using-statement within the scope in which it was declared.
```cpp
int main()
{
    using namespace Foo;

    // there's no way to cancel the "using namespace Foo" here!
    // there's also no way to replace "using namespace Foo" with a different using statement

    return 0;
} // using namespace Foo ends here
```

The best you can do is intentionally limit the scope of the using-statement from the outset using the block scoping rules.

```cpp
int main()
{
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // using namespace Foo expires

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // using namespace Goo expires

    return 0;
}
```

Of course, all of this headache can be avoided by explicitly using the scope resolution operator (::) in the first place.

### Best practices for using-statements

#### Best practice
Prefer explicit namespace qualifiers over using-statements.
Avoid using-directives altogether (except `using namespace std::literals` to access the `s` and `sv` literal suffixes). Using-declarations are okay in .cpp files, after the #include directives. Do not use using-statements in header files (especially in the global namespace of header files).
#### Related content
The `using` keyword is also used to define type aliases, which are unrelated to using-statements. We cover type aliases in lesson [10.7 -- Typedefs and type aliases](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/).

## 7.14 [Unnamed and inline namespaces](https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/)

C++ supports two variants of namespaces that are worth at least knowing about. We won’t build on these, so consider this lesson optional for now.
### Unnamed (anonymous) namespaces

An **unnamed namespace** (also called an **anonymous namespace**) is a namespace that is defined without a name, like so:
```cpp
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```
This prints:
`v1`

All content declared in an unnamed namespace is treated as if it is part of the parent namespace. So even though function `doSomething()` is defined in the unnamed namespace, the function itself is accessible from the parent namespace (which in this case is the global namespace), which is why we can call `doSomething()` from `main()` without any qualifiers.

This might make unnamed namespaces seem useless. But the other effect of unnamed namespaces is that all identifiers inside an unnamed namespace are treated as if they have internal linkage, which means that the content of an unnamed namespace can’t be seen outside of the file in which the unnamed namespace is defined.

For functions, this is effectively the same as defining all functions in the unnamed namespace as static functions. The following program is effectively identical to the one above:
```cpp
#include <iostream>

static void doSomething() // can only be accessed in this file
{
    std::cout << "v1\n";
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

Unnamed namespaces are typically used when you have a lot of content that you want to ensure stays local to a given translation unit, as it’s easier to cluster such content in a single unnamed namespace than individually mark all declarations as `static`. Unnamed namespaces will also keep program-defined types (something we’ll discuss in a later lesson) local to the translation unit, something for which there is no alternative equivalent mechanism to do.
#### Tip
If you’re hardcore, you can take the opposite approach -- put all content that isn’t explicitly meant to be exported/external in an unnamed namespace.

Unnamed namespaces should generally not be used in header files. [SEI CERT (rule DCL59-CPP)](https://wiki.sei.cmu.edu/confluence/display/cplusplus/DCL59-CPP.+Do+not+define+an+unnamed+namespace+in+a+header+file) has some good examples as to why.
#### Best practice
Prefer unnamed namespaces when you have content you want to keep local to a translation unit.
Avoid unnamed namespaces in header files.

### Inline namespaces

Now consider the following program:
```cpp
#include <iostream>

void doSomething()
{
    std::cout << "v1\n";
}

int main()
{
    doSomething();

    return 0;
}
```

This prints:`v1`

Pretty straightforward, right?

But let’s say you’re not happy with `doSomething()`, and you want to improve it in some way that changes how it behaves. But if you do this, you risk breaking existing programs using the older version. How do you handle this?

One way would be to create a new version of the function with a different name. But over the course of many changes, you could end up with a whole set of almost-identically named functions (`doSomething`, `doSomething_v2`, `doSomething_v3`, etc…).

An alternative is to use an inline namespace. An **inline namespace** is a namespace that is typically used to version content. Much like an unnamed namespace, anything declared inside an inline namespace is considered part of the parent namespace. However, unlike unnamed namespaces, inline namespaces don’t affect linkage.

To define an inline namespace, we use the `inline` keyword:
```cpp
#include <iostream>

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}
```

This prints:
```
V1
V2
V1
```
In the above example, callers to `doSomething()` will get the V1 (the inline version) of `doSomething()`. Callers who want to use the newer version can explicitly call `V2::doSomething()`. This preserves the function of existing programs while allowing newer programs to take advantage of newer/better variations.

Alternatively, if you want to push the newer version:

```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace V2 // declare an inline namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V2)

    return 0;
}
```

This prints:

V1
V2
V2

In this example, all callers to `doSomething()` will get the v2 version by default (the newer and better version). Users who still want the older version of `doSomething()` can explicitly call `V1::doSomething()` to access the old behavior. This means existing programs who want the V1 version will need to globally replace `doSomething` with `V1::doSomething`, but this typically won’t be problematic if the functions are well named.
Alternatively, if you want to push the newer version you put the inline in the V2 version.

### Mixing inline and unnamed namespaces Optional

A namespace can be both inline and unnamed:
```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace // declare an inline unnamed namespace
{
    void doSomething() // has internal linkage
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    // there is no V2 in this example, so we can't use V2:: as a namespace prefix

    doSomething(); // calls the inline version of doSomething() (which is the anonymous one)

    return 0;
}
```

However, in such cases, it’s probably better to nest an anonymous namespace inside an inline namespace. This has the same effect (all functions inside the anonymous namespace have internal linkage by default) but still gives you an explicit namespace name you can use:

```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace V2 // declare an inline namespace named V2
{
    namespace // unnamed namespace
    {
        void doSomething() // has internal linkage
        {
            std::cout << "V2\n";
        }

    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V2)

    return 0;
}
```

## 7.x [Chapter 7 summary and quiz](https://www.learncpp.com/cpp-tutorial/chapter-7-summary-and-quiz/)
### Chapter Review

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

### 3b) Quizz
```cpp
int accumulate(int x)
{
    static int sum{ 0 }; // initialize sum to 0 at start of program
    sum += x;
    return sum;
}
```
Extra credit: What are two shortcomings of the `accumulate()` function above?


1. There is no conventional way to reset the accumulation without restarting the program.
2. There is no conventional way to have multiple accumulators running.

#### For advanced readers
Both of these shortcomings can be addressed using functors ([21.10 -- Overloading the parenthesis operator](https://www.learncpp.com/cpp-tutorial/overloading-the-parenthesis-operator/)) instead of a static local variable.