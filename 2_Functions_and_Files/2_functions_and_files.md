# C++ Basics: Functions and Files

## 2.1 Introduction to functions
**function** is a reusable sequence of statements designed to do a particular job.
Functions that you write yourself are called **user-defined functions**.
A **function call** tells the CPU to interrupt the current function and execute another function and then **returns** to the current function.
The function initiating the function call is the **caller**, and the function being **called** (executed) is the **callee**. A function call is also sometimes called an **invocation**, with the caller **invoking** the callee.
```CPP
returnType functionName() // This is the function header (tells the compiler about the existence of the function)
{
    // This is the function body (tells the compiler what the function does)
}
```

“foo” is a meaningless word that is often used as a placeholder name for a function or variable when the name is unimportant to the demonstration of some concept. Such words are called metasyntactic variables

## 2.2 Function return values (value-returning functions)
To return a value back to the caller:
First, your function has to indicate what type of value will be returned. This is done by setting the function’s **return type**, which is the type that is defined before the function’s name.
Second, inside the function that will return a value, we use a **return statement** to indicate the specific value being returned to the caller. The return statement consists of the return keyword, followed by an expression (sometimes called the **return expression**), ending with a semicolon.

When the return statement is executed:
    The return expression is evaluated to produce a value.
    The value produced by the return expression is copied back to the caller. This copy is called the return value of the function.
    The function exits, and control returns to the caller.
The process of returning a copied value back to the caller is named **return by value**.

`int num { getValueFromUser() };`
If you need to use the return value of a function call more than once, initialize a variable with the return value, and then use that variable as many times as needed.

In C++, there are two special requirements for main():
    main() is required to return an int.
    Explicit function calls to main() are disallowed.

main() function at the bottom of your code file, below other functions

It is a common misconception that main is always the first function that executes.

Global variables are initialized prior to the execution of main. If the initializer for such a variable invokes a function, then that function will execute prior to main.

The return value from main() is sometimes called a **status code** (or less commonly, an *exit code*, or rarely a *return code*). The status code is used to signal whether your program was successful or not. 0 means the program ran normally.

The C++ standard only defines the meaning of 3 status codes: `0`, `EXIT_SUCCESS`, and `EXIT_FAILURE`. 0 and `EXIT_SUCCESS` both mean the program executed successfully. `EXIT_FAILURE` means the program did not execute successfully.
EXIT_SUCCESS and EXIT_FAILURE are preprocessor macros defined in the `<cstdlib>` header

The status code is passed back to the operating system. The OS will typically make the status code available to whichever program launched the program returning the status code. This provides a crude mechanism for any program launching another program to determine whether the launched program ran successfully or not.

A function that returns a value is called a **value-returning function**.

A value-returning function must return a value of that type (using a return statement), otherwise undefined behavior will result.

A value-returning function can only return a single value back to the caller each time it is called.

Note that the value provided in a return statement doesn’t need to be literal -- it can be the result of any valid expression, including a variable or even a call to another function that returns a value.

Some functions use return values as status codes, to indicate whether they succeeded or failed. Other functions return a calculated or selected value. Other return nothing.

Program Mindset: *Don’t Repeat Yourself* (often abbreviated *DRY*).

The essence of modular programming: the ability to write a function, test it, ensure that it works, and then know that we can reuse it as many times as we want and it will continue to work (so long as we don’t modify the function -- at which point we’ll have to retest it).


Follow DRY: “Don’t repeat yourself”. If you need to do something more than once, consider how to modify your code to *remove as much redundancy as possible*. *Variables* can be used to *store the results of calculations that need to be used more than once* (so we don’t have to repeat the calculation). *Functions* can be used to define a *sequence of statements we want to execute more than once*. And *loops* (which we’ll cover in a later chapter) can be used to *execute a statement more than once*.

Like all best practices, DRY is meant to be a guideline, not an absolute. Reader Yariv has noted that DRY can harm overall comprehension when code is broken into pieces that are too small.

The (snarky) opposite of DRY is WET (“Write everything twice”).

Nested function not allowed 
```Cpp
int return7()
{
    return 7;

    int return9() // NOT ALLOWED
    {
        return 9;
    }
}
```


## 2.3 Void functions (non-value returning functions)

Functions are not required to return a value back to the caller. To tell the compiler that a function does not return a value, a return type of **void** is used.
A function that does not return a value is called a **non-value returning function** (or a **void function**).
A void function will automatically return to the caller at the end of the function. No return statement is required.
```Cpp

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';

    return; // tell compiler to return to the caller -- this is redundant since the return will happen at the end of the function anyway!
} // function will return to caller here
```
Do not put a return statement at the end of a non-value returning function.
Some statements require values to be provided in them you can't use a void function, and others don’t.
Trying to return a value from a non-value returning function will result in a compilation error.


## 2.4 Introduction to function parameters and arguments
A **function parameter** is a variable used in the header of a function. Function parameters work almost identically to variables defined inside the function, but with one difference: they are initialized with a value provided by the caller of the function.

An **argument** is a value that is passed from the caller to the function when a function call is made.

When a function is called, all of the parameters of the function are created as variables, and the value of each of the arguments is calculated if it's an expression and then copied into the matching parameter (using copy initialization). This process is called **pass by value**. Function parameters that utilize pass by value are called **value parameters**.

**unreferenced parameters**: parameters that are not used in the body of the function.

In a function definition, the name of a function parameter is optional. Therefore, in cases where a function parameter needs to exist but is not used in the body of the function, you can simply omit the name. A parameter without a name is called an **unnamed parameter**:
```Cpp
void doSomething(int) // ok: unnamed parameter will not generate warning
{
}
```
The Google C++ style guide recommends using a comment to document what the unnamed parameter was: `void doSomething(int /*count*/)`

You’re probably wondering why we’d write a function that has a parameter whose value isn’t used. This happens most often in cases similar to the following:
    Let’s say we have a function with a single parameter. Later, the function is updated in some way, and the value of the parameter is no longer needed. If the now-unused function parameter were simply removed, then every existing call to the function would break (because the function call would be supplying more arguments than the function could accept). This would require us to find every call to the function and remove the unneeded argument. This might be a lot of work (and require a lot of retesting). It also might not even be possible (in cases where we did not control all of the code calling the function). So instead, we might leave the parameter as it is, and just have it do nothing.

Other cases where this occurs:
    Operators ++ and -- have prefix and postfix variants (e.g. ++foo vs foo++). An unreferenced function parameter is used to differentiate whether an overload of such an operator is for the prefix or postfix case. 
    
    When we need to determine something from the type (rather than the value) of a type template parameter.

When a function parameter exists but is not used in the body of the function, do not give it a name. You can optionally put a name inside a comment.



## 2.5 Introduction to local scope
Variables defined inside the body of a function are called **local variables**. Function parameters are also generally considered to be local variables.
Local variables are destroyed in the opposite order of creation at the end of the set of curly braces in which it is defined (or for a function parameter, at the end of the function).

An object’s **lifetime** is defined to be the time between its creation and destruction. Note that variable creation and destruction happen when the program is running (called runtime), not at compile time. Therefore, lifetime is a runtime property.

The rules around creation, initialization, and destruction are guarantees. That is, objects must be created and initialized no later than the point of definition, and destroyed no earlier than the end of the set of the curly braces in which they are defined (or, for function parameters, at the end of the function).
In actuality, the C++ specification gives compilers a lot of flexibility to determine when local variables are created and destroyed. Objects may be created earlier, or destroyed later for optimization purposes. Most often, local variables are created when the function is entered, and destroyed in the opposite order of creation when the function is exited. 

```Cpp
// x is not in scope anywhere in this function
void doSomething()
{
    std::cout << "Hello!\n";
}

int main()
{
        // x can not be used here because it's not in scope yet
    int x{ 0 };    // x's lifetime begins here // x enters scope here and can now be used within this function

    doSomething(); // x is still alive during this function call

    return 0;
} // x's lifetime ends here // x goes out of scope here and can no longer be used
```

What happens when an object is destroyed?

In most cases, nothing. The destroyed object simply becomes invalid.

If the object is a class type object, prior to destruction, a special function called a destructor is invoked. In many cases, the destructor does nothing, in which case no cost is incurred. 

Any use of an object after it has been destroyed will result in undefined behavior.

At some point after destruction, the memory used by the object will be **deallocated** (freed up for reuse).

An identifier’s **scope** determines where the identifier can be seen and used within the source code. When an identifier can be seen and used, we say it is **in scope**. When an identifier can not be seen, we can not use it, and we say it is **out of scope**. Scope is a compile-time property, and trying to use an identifier when it is not in scope will result in a compile error.

The identifier of a local variable has **local scope**. An identifier with local scope (technically called **block scope**) is usable from the point of definition to the end of the innermost pair of curly braces containing the identifier (or for function parameters, at the end of the function). This ensures local variables cannot be used before the point of definition (even if the compiler opts to create them before then) or after they are destroyed.  Local variables defined in one function are also not in scope in other functions that are called.

An identifier is *out of scope* anywhere it cannot be accessed within the code. 

The term *“going out of scope”* is typically applied to objects rather than identifiers. We say an object goes out of scope at the end of the scope (the end curly brace) in which the object was instantiated. 

A local variable’s lifetime ends at the point where it goes out of scope, so local variables are destroyed at this point.

Note that not all types of variables are destroyed when they go out of scope. 

lifetime is a runtime property, and scope is a compile-time property, so although we are talking about both in the same program, they are enforced at different points.

Names used for function parameters or variables declared in a function body are only visible within the function that declares them. This means local variables within a function can be named without regard for the names of variables in other functions. This helps keep functions independent.

In modern C++, the best practice is that local variables inside the function body should be defined as close to their first use as reasonable.
The C language used to require all local variables be defined at the top of the function. 

A function parameter should be used when the caller will pass in the initialization value as an argument. A local variable should be used otherwise.

A **temporary object** (also sometimes called an **anonymous object**) is an unnamed object that is used to hold a value that is only needed for a short period of time. Temporary objects are generated by the compiler when they are needed.
`	std::cout << getValueFromUser() << '\n'; // where does the returned value get stored?`
The answer is that the return value is stored in a temporary object.  
Return by value returns a temporary object (that holds a copy of the return value) to the caller.
Temporary objects have no scope at all (this makes sense, since scope is a property of an identifier, and temporary objects have no identifier).
Temporary objects are destroyed at the end of the full expression in which they are created. This means temporary objects are always destroyed before the next statement executes.
In modern C++ (especially since C++17), the compiler has many tricks to avoid generating temporaries where previously it would have needed to. Ex: in modern C++, the compiler will often skip creating the temporary and just initialize the variable directly with the return value.

## 2.6 Why functions are useful, and how to use them effectively
Function for : Organization, Reusability, Reusability, Extensibility, Abstraction
Use function for : Groups of statements that appear more than once in a program / Code that has a well-defined set of inputs and outputs
A function should generally perform one (and only one) task.
When a function becomes too long, too complicated, or hard to understand, it can be split into multiple sub-functions. This is called **refactoring**.

## 2.7 Forward declarations and definitions
The compiler compiles the contents of code files sequentially.
If the function is used in a line lower than the line of its declaration in the file, that produces an error.

When addressing compilation errors or warnings in your programs, resolve the first issue listed and then compile again.

A **forward declaration** allows us to tell the compiler about the existence of an identifier before actually defining the identifier.

In the case of functions, this allows us to tell the compiler about the existence of a function before we define the function’s body. This way, when the compiler encounters a call to the function, it’ll understand that we’re making a function call, and can check to ensure we’re calling the function correctly, even if it doesn’t yet know how or where the function is defined.

To write a forward declaration for a function, we use a **function declaration** statement (also called a **function prototype**). The function declaration consists of the function’s return type, name, and parameter types, terminated with a semicolon. The names of the parameters can be optionally included. The function body is not included in the declaration.

`int add(int x, int y); // function declaration includes return type, name, parameters, and semicolon.  No function body!`

It is worth noting that function declarations do not need to specify the names of the parameters (as they are not considered to be part of the function declaration).
However, we prefer to name our parameters (using the same names as the actual function). This allows you to understand what the function parameters are just by looking at the declaration for more clarity.
Also many automated documentation generation tools will generate documentation from the content of header files, which is where declarations are often placed. 
You can easily create function declarations by copy/pasting your function’s header and adding a semicolon.


Most often, forward declarations are used to tell the compiler about the existence of some function that has been defined in a different code file. Reordering isn’t possible in this scenario because the caller and the callee are in completely different files! 

Forward declarations can also be used to define our functions in an order-agnostic manner. This allows us to define functions in whatever order maximizes organization (e.g. by clustering related functions together) or reader understanding.

Less often, there are times when we have two functions that call each other. Reordering isn’t possible in this case either, as there is no way to reorder the functions such that each is before the other. Forward declarations give us a way to resolve such circular dependencies.

If a forward declaration is made and the function is called, but the program never defines the function, the program will compile okay, but the linker will complain that it can’t resolve the function call.

Forward declarations can also be used with other identifiers in C++, such as variables and types. Variables and types have a different syntax for forward declaration.

A **declaration** tells the compiler about the existence of an identifier and its associated type information. 

A **definition** is a declaration that actually implements (for functions and types) or instantiates (for variables) the identifier.

Declarations that aren’t definitions are called **pure declarations** (includes forward declaration).

In common language, the term “declaration” is typically used to mean “a pure declaration”, and “definition” is used to mean “a definition that also serves as a declaration”.

There are a few cases where the compiler must be able to see a full definition in order to use an identifier (such as for template definitions and type definitions)

The one definition rule (ODR), three parts:
1. Within a file, each function, variable, type, or template in a given scope can only have one definition. Definitions occurring in different scopes (e.g. local variables defined inside different functions, or functions defined inside different namespaces) do not violate this rule.
2.  Within a program, each function or variable in a given scope can only have one definition. This rule exists because programs can have more than one file (we’ll cover this in the next lesson). Functions and variables not visible to the linker are excluded from this rule
3. Types, templates, inline functions, and inline variables are allowed to have duplicate definitions in different files, so long as each definition is identical. 

Violating part 1 of the ODR will cause the compiler to issue a redefinition error. Violating ODR part 2 will cause the linker to issue a redefinition error. Violating ODR part 3 will cause undefined behavior.

Functions that share an identifier but have different sets of parameters are also considered to be distinct functions, so such definitions do not violate the ODR. 


## 2.8 Programs with multiple code files
gcc
From the command line, you can create the additional file yourself, using your favorite editor, and give it a name. When you compile your program, you’ll need to include all of the relevant code files on the compile line. For example: g++ main.cpp add.cpp -o main, where main.cpp and add.cpp are the names of your code files, and main is the name of the output file.

VSCode
To create a new file, choose View > Explorer from the top nav to open the Explorer pane, and then click the New File icon to the right of the project name. Alternately, choose File > New File from the top nav. Then give your new file a name (don’t forget the .cpp extension). If the file appears inside the .vscode folder, drag it up one level to the project folder.

Next open the tasks.json file, and find the line "${file}",.

You have two options here:

    If you wish to be explicit about what files get compiled, replace "${file}", with the name of each file you wish to compile, one per line, like this:

"main.cpp",
"add.cpp",

    Reader “geo” reports that you can have VS Code automatically compile all .cpp files in the directory by replacing "${file}", with "${fileDirname}\\**.cpp" (on Windows).
    Reader “Orb” reports that "${fileDirname}/**.cpp" works on Unix.

Your compiler may compile either add.cpp or main.cpp first. Either way, main.cpp will fail to compile, giving the same compiler error as the previous example.
Remember, the compiler compiles each file individually. It does not know about the contents of other code files, or remember anything it has seen from previously compiled code files. So even though the compiler may have seen the definition of function add previously (if it compiled add.cpp first), it doesn’t remember.

This limited visibility and short memory is intentional, for a few reasons:
    It allows the source files of a project to be compiled in any order.
    When we change a source file, only that source file needs to be recompiled.
    It reduces the possibility of naming conflicts between identifiers in different files.

main.cpp (with forward declaration):

```Cpp
#include <iostream>

int add(int x, int y); // needed so main.cpp knows that add() is a function defined elsewhere

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}
```
add.cpp (stays the same):
```Cpp
int add(int x, int y)
{
    return x + y;
}
```
Now, when the compiler is compiling main.cpp, it will know what identifier add is and be satisfied. The linker will connect the function call to add in main.cpp to the definition of function add in add.cpp.

Using this method, we can give files access to functions that live in another file.

Because the compiler compiles each code file individually (and then forgets what it has seen), each code file that uses `std::cout` or `std::cin` needs to `#include <iostream>`.

When an identifier is used in an expression, the identifier must be connected to its definition.
    If the compiler has seen neither a forward declaration nor a definition for the identifier in the file being compiled, it will error at the point where the identifier is used.
    Otherwise, if a definition exists in the same file, the compiler will connect the use of the identifier to its definition.
    Otherwise, if a definition exists in a different file (and is visible to the linker), the linker will connect the use of the identifier to its definition.
    Otherwise, the linker will issue an error indicating that it couldn’t find a definition for the identifier.

Do not #include “add.cpp” from main.cpp. While doing so compiles in this case, #including .cpp files increases the risk of naming conflicts and other unanticipated consequences (especially as programs get larger and more complex). 


C++ is designed so that each source file can be compiled independently, with no knowledge of what is in other files. Therefore, the order in which files are actually compiled should not be relevant.

We will begin working with multiple files a lot once we get into object-oriented programming, so now’s as good a time as any to make sure you understand how to add and compile multiple file projects.

Reminder: Whenever you create a new code (.cpp) file, you will need to add it to your project so that it gets compiled.


## 2.9 Naming collisions and an introduction to namespaces
Similarly, C++ requires that all identifiers be non-ambiguous. If two identical identifiers are introduced into the same program in a way that the compiler or linker can’t tell them apart, the compiler or linker will produce an error. This error is generally referred to as a **naming collision** (or **naming conflict**).

If the colliding identifiers are introduced into the same file, the result will be a compiler error. If the colliding identifiers are introduced into separate files belonging to the same program, the result will be a linker error.

If two files contains the same named function with same type,  each file will compile with no problems but there will be a linker error.

Most naming collisions occur in two cases:
    1 Two (or more) identically named functions (or global variables) are introduced into separate files belonging to the same program. This will result in a linker error, as shown above.
    2 Two (or more) identically named functions (or global variables) are introduced into the same file. This will result in a compiler error.

C++ provides plenty of mechanisms for avoiding naming collisions. Local scope, which keeps local variables defined inside functions from conflicting with each other, is one such mechanism. But local scope doesn’t work for function names.

A **scope region** is an area of source code where all declared identifiers are considered distinct from names declared in other scopes.
Two identifiers with the same name can be declared in separate scope regions without causing a naming conflict. However, within a given scope region, all identifiers must be unique, otherwise a naming collision will result.

The body of a function is one example of a scope region. Two identically-named identifiers can be defined in separate functions without issue -- because each function provides a separate scope region, there is no collision. However, if you try to define two identically-named identifiers within the same function, a naming collision will result, and the compiler will complain.

A **namespace** provides another type of scope region (called **namespace scope**) that allows you to declare or define names inside of it for the purpose of disambiguation. The names declared in a namespace are isolated from names declared in other scopes, allowing such names to exist without conflict.

A name declared within a scope region (such as a namespace) is distinct from any identical name declared in another scope.

For example, two functions with identical declarations can be defined inside different namespaces, and no naming collision or ambiguity will occur.

Namespaces may only contain declarations and definitions (e.g. variables and functions). Executable statements are not allowed unless they are part of a definition (e.g. within a function).

In C++, any name that is not defined inside a class, function, or a namespace is considered to be part of an implicitly-defined namespace called the **global namespace** (sometimes also called the **global scope**).

Identifiers declared inside the global scope are in scope from the point of declaration to the end of the file.
Although variables can be defined in the global namespace, this should generally be avoided.

```Cpp
#include <iostream> // imports the declaration of std::cout into the global scope

// All of the following statements are part of the global namespace

void foo();    // okay: function forward declaration
int x;         // compiles but strongly discouraged: non-const global variable definition (without initializer)
int y { 5 };   // compiles but strongly discouraged: non-const global variable definition (with initializer)
x = 5;         // compile error: executable statements are not allowed in namespaces

int main()     // okay: function definition
{
    return 0;
}

void goo();    // okay: A function forward declaration
```

When you use an identifier that is defined inside a non-global namespace (e.g. the std namespace), you need to tell the compiler that the identifier lives inside the namespace. `std::cin`

The most straightforward way to tell the compiler that we want to use cout from the std namespace is by explicitly using the std:: prefix. 

The `::` symbol is an operator called the **scope resolution operator**.

The identifier to the left of the :: symbol identifies the namespace that the name to the right of the :: symbol is contained within. If no identifier to the left of the `::` symbol is provided, the global namespace is assumed.

So when we say std::cout we’re saying “the cout that is declared in namespace std“.

Use explicit namespace prefixes to access identifiers defined in a namespace.

When an identifier includes a namespace prefix, the identifier is called a **qualified name**.

Another way to access identifiers inside a namespace is to use a using-directive statement. `using namespace std; cout ` TO AVOID

A **using directive** allows us to access the names in a namespace without using a namespace prefix.
However, used in this way, this is a bad practice, and highly discouraged.

When using a using-directive in this manner, any identifier we define may conflict with any identically named identifier in the std namespace. Even worse, while an identifier name may not conflict today, it may conflict with new identifiers added to the std namespace in future language revisions. This was the whole point of moving all of the identifiers in the standard library into the std namespace in the first place!

Avoid using-directives (such as using namespace std;) at the top of your program or in header files. They violate the reason why namespaces were added in the first place.

In C++, curly braces are often used to delineate a scope region that is nested within another scope region (braces are also used for some non-scope-related purposes, such as list initialization). For example, a function defined inside the global scope region uses curly braces to separate the scope region of the function from the global scope.

In certain cases, identifiers defined outside the curly braces may still be part of the scope defined by the curly braces rather than the surrounding scope -- function parameters are a good example of this.

```Cpp
#include <iostream> // imports the declaration of std::cout into the global scope

void foo(int x) // foo is defined in the global scope, x is defined within scope of foo()
{ // braces used to delineate nested scope region for function foo()
    std::cout << x << '\n';
} // x goes out of scope here

int main()
{ // braces used to delineate nested scope region for function main()
    foo(5);

    int x { 6 }; // x is defined within the scope of main()
    std::cout << x << '\n';

    return 0;
} // x goes out of scope here
// foo and main (and std::cout) go out of scope here (the end of the file)
```
The code that exists inside a nested scope region is conventionally indented one level, both for readability and to help indicate that it exists inside a separate scope region.

The #include and function definitions for foo() and main() exist in the global scope region, so they are not indented. The statements inside each function exist inside the nested scope region of the function, so they are indented one level.

## 2.10 Introduction to the preprocessor
When you compile your project, you might expect that the compiler compiles each code file exactly as you’ve written it. This actually isn’t the case.

Instead, prior to compilation, each code (.cpp) file goes through a **preprocessing** phase. In this phase, a program called the **preprocessor** makes various changes to the text of the code file. The preprocessor does not actually modify the original code files in any way -- rather, all changes made by the preprocessor happen either temporarily in-memory or using temporary files.

Historically, the preprocessor was a separate program from the compiler, but in modern compilers, the preprocessor may be built right into the compiler itself.

Most of what the preprocessor does is fairly uninteresting. For example, it strips out comments, and ensures each code file ends in a newline. However, the preprocessor does have one very important role: it is what processes `#include` directives.

When the preprocessor has finished processing a code file, the result is called a **translation unit**. This translation unit is what is then compiled by the compiler.

The entire process of preprocessing, compiling, and linking is called **translation**. 

here is a list of translation phases https://en.cppreference.com/w/cpp/language/translation_phases.
As of the time of writing, preprocessing encompasses phases 1 through 4, and compilation is phases 5 through 7.

When the preprocessor runs, it scans through the code file (from top to bottom), looking for **preprocessor directives**. Preprocessor directives (often just called directives) are instructions that *start with a # symbol* and end with a newline (NOT a semicolon). These directives tell the preprocessor to perform certain text manipulation tasks. Note that the preprocessor does not understand C++ syntax -- instead, the directives have their own syntax (which in some cases resembles C++ syntax, and in other cases, not so much).

The final output of the preprocessor contains no directives -- only the output of the processed directive is passed to the compiler.


Using directives (introduced in lesson 2.9 -- Naming collisions and an introduction to namespaces) are not preprocessor directives (and thus are not processed by the preprocessor). So while the term directive usually means a preprocessor directive, this is not always the ca

When you `#include` a file, the preprocessor replaces the *#include* directive with the contents of the included file. The included contents are then preprocessed (which may result in additional #includes being preprocessed recursively), then the rest of the file is preprocessed.

#include is almost exclusively used to include header files

Each translation unit typically consists of a single code (.cpp) file and all header files it #includes (applied recursively, since header files can #include other header files).

The `#define` directive can be used to create a macro. In C++, a **macro** is a rule that defines how input text is converted into replacement output text.

There are two basic types of macros: *object-like macros*, and *function-like macros*.

*Function-like macros* act like functions, and serve a similar purpose. Their use is generally considered **unsafe**, and almost anything they can do can be done by a normal function.

Object-like macros can be defined in one of two ways:
```
#define IDENTIFIER
#define IDENTIFIER substitution_text
```

The top definition has no substitution text, whereas the bottom one does. Because these are preprocessor directives (not statements), note that neither form ends with a semicolon.

The identifier for a macro uses the same naming rules as normal identifiers: they can use letters, numbers, and underscores, cannot start with a number, and should not start with an underscore. By convention, macro names are typically all uppercase, separated by underscores.

Macro names should be written in all uppercase letters, with words separated by underscores.

When the preprocessor encounters this directive, an association is made between the macro identifier and *substitution_text*. All further occurrences of the macro identifier (outside of use in other preprocessor commands) are replaced by the *substitution_text*.

```Cpp
#define MY_NAME "Alex"
...
    std::cout << "My name is: " << MY_NAME << '\n';
```

Object-like macros with substitution text were used (in C) as a way to assign names to literals. This is no longer necessary, as better methods are available in C++ (see 7.10 -- Sharing global constants across multiple files (using inline variables)). Object-like macros with substitution text are now mostly seen in legacy code, and we recommend **avoiding them whenever possible**.

Avoid macros with substitution text unless no viable alternatives exist.

Object-like macros can also be defined without substitution text.
Macros of this form work like you might expect: most further occurrences of the identifier is removed and replaced by nothing!
This might seem pretty useless, and it is useless for doing text substitution. However, that’s not what this form of the directive is generally used for. We’ll discuss the uses of this form in just a moment.

Unlike object-like macros with substitution text, macros of this form are generally considered acceptable to use.

### Conditional compilation

The conditional compilation preprocessor directives allow you to specify under what conditions something will or won’t compile. There are quite a few different conditional compilation directives, but we’ll only cover a few that are used the most often: *#ifdef*, *#ifndef*, and *#endif*.

The *#ifdef* preprocessor directive allows the preprocessor to check whether an identifier has been previously defined via *#define*. If so, the code between the *#ifdef* and matching #endif is compiled. If not, the code is ignored.

```Cpp
#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif

    return 0;
}
```


*#ifndef* is the opposite of *#ifdef*, in that it allows you to check whether an identifier has NOT been *#defined* yet.

In place of *#ifdef PRINT_BOB* and *#ifndef PRINT_BOB*, you’ll also see *#if defined(PRINT_BOB)* and *#if !defined(PRINT_BOB)*. These do the same, but use a slightly more C++-style syntax.

_#if 0_ to exclude a block of code from being compiled (as if it were inside a comment block)
This provides a convenient way to “comment out” code that contains multi-line comments (which can’t be commented out using another multi-line comment due to multi-line comments being non-nestable):  
```Cpp
```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    /* Some
     * multi-line
     * comment here
     */
    std::cout << "Steve\n";
#endif // until this point

    return 0;
}
```

To temporarily re-enable code that has been wrapped in an `#if 0`, you can change the `#if 0` to `#if 1`
```Cpp
```cpp
#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

    return 0;
}
```
Since we defined _PRINT_JOE_ to be nothing, how come the preprocessor didn’t replace _PRINT_JOE_ in _#ifdef PRINT_JOE_ with nothing and exclude the output statement from compilation?

In most cases, macro substitution does not occur when a macro identifier is used within another preprocessor command.
There is at least one exception to this rule: most forms of `#if` and `#elif` do macro substitution within the preprocessor command.

```cpp
#define FOO 9 // Here's a macro substitution

#ifdef FOO // This FOO does not get replaced with 9 because it’s part of another preprocessor directive
    std::cout << FOO << '\n'; // This FOO gets replaced with 9 because it's part of the normal code
#endif
```


Directives are resolved before compilation, from top to bottom on a file-by-file basis.
```cpp
#include <iostream>

void foo()
{
#define MY_NAME "Alex"
}

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n';

	return 0;
}
```
Even though it looks like _#define MY_NAME “Alex”_ is defined inside function _foo_, the preprocessor doesn’t understand C++ concepts like functions. Therefore, this program behaves identically to one where _#define MY_NAME “Alex”_ was defined either before or immediately after function _foo_. To avoid confusion, you’ll generally want to #define identifiers outside of functions.
Because an #include directive replaces the #include directive with the content of the included file, an #include can copy directives from the included file into the current file. These directives will then be processed in order.

Alex.h:

```cpp
#define MY_NAME "Alex"
```

main.cpp:

```cpp
#include "Alex.h" // copies #define MY_NAME from Alex.h here
#include <iostream>

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n'; // preprocessor replaces MY_NAME with "Alex"

	return 0;
}
```

Once the preprocessor has finished, all defined identifiers from that file are discarded. This means that directives are only valid from the point of definition to the end of the file in which they are defined. Directives defined in one file do not have any impact on other files (unless they are #included into another file).
function.cpp:

```cpp
#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}
```

main.cpp:

```cpp
void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();

    return 0;
}
```

The above program will print:

Not printing!

Even though PRINT was defined in _main.cpp_, that doesn’t have any impact on any of the code in _function.cpp_ (PRINT is only #defined from the point of definition to the end of main.cpp). This will be of consequence when we discuss header guards in a future lesson.

## 2.11 Header files

When programs contain only a few small files, manually adding a few forward declarations to the top of each file isn’t too bad. However, as programs grow larger (and make use of more files and functions), having to manually add a large number of (possibly different) forward declarations to the top of each file becomes extremely tedious.

The other type of file in C++ programs is called a **header file**. Header files usually have a .h extension, but you will occasionally see them with a .hpp extension or no extension at all.

Conventionally, header files are used to propagate a bunch of related forward declarations into a code file.

Header files allow us to put **declarations** in one place and then import them wherever we need them. This can save a lot of typing in multi-file programs.

_std::cout_ has been forward declared in the “iostream” header file.
When we `#include <iostream>`, we’re requesting that the preprocessor copy all of the content (including forward declarations for std::cout) from the file named “iostream” into the file doing the #include.

When you `#include` a file, the content of the included file is inserted at the point of inclusion. This provides a useful way to pull in declarations from another file.

Writing a header file is easy, as header files only consist of two parts:
1. A _header guard_
2. The actual content of the header file, which should be the forward declarations for all of the identifiers we want other files to be able to see.
   
Unlike source files, header files should _not_ be added to your compile command (they are implicitly included by #include statements and compiled as part of your source files).

Prefer a .h suffix when naming your header files (unless your project already follows some other convention).
This is a longstanding convention for C++ header files, and most IDEs still default to .h over other options.

Header files are often paired with code files, with the header file providing forward declarations for the corresponding code file. 
If a header file is paired with a code file (e.g. add.h with add.cpp), they should both have the same base name (add).

add.h:
```cpp
// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
```

In order to use this header file in main.cpp, we have to #include it (using quotes, not angle brackets).

main.cpp:

```cpp
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

add.cpp:

```cpp
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.

int add(int x, int y)
{
    return x + y;
}
```

When the preprocessor processes the `#include "add.h"` line, it copies the contents of add.h into the current file at that point. Because our _add.h_ contains a forward declaration for function _add()_, that forward declaration will be copied into _main.cpp_. The end result is a program that is functionally the same as the one where we manually added the forward declaration at the top of _main.cpp_.
![[Pasted image 20250402094518.png]]
Note: In the graphic above, “Standard Runtime Library” should be labelled as the “C++ Standard Library”.

For now, you should avoid putting function or variable definitions in header files. Doing so will generally result in a violation of the one-definition rule (ODR) in cases where the header file is included into more than one source file.

If `add.h` contains a definition of a function `add()` . When `main.cpp` and `add.cpp` is compiled, the `#include "add.h"` will be replaced with the contents of `add.h` and then compiled.
This will also compile just fine.
Finally, the linker will run. And the linker will see that there are now two definitions for function `add()`: one in main.cpp, and one in add.cpp.
This is a violation of ODR part 2, which states, “Within a given program, a variable or normal function can only have one definition.

Do not put function and variable definitions in your header files (for now).

Defining either of these in a header file will likely result in a violation of the one-definition rule (ODR) if that header is then #included into more than one source (.cpp) file.

In future lessons, we will encounter additional kinds of definitions that can be safely defined in header files (because they are exempt from the ODR). This includes definitions for inline functions, inline variables, types, and templates. We’ll discuss this further when we introduce each of these.

In C++, it is a best practice for code files to #include their paired header file (if one exists) (e.g. `include "add.h"; in add.cpp `. This allows the compiler to catch certain kinds of errors at compile time instead of link time. 

Source files should #include their paired header file (if one exists).

Although the preprocessor will happily do so, you should generally not `#include` .cpp files. These should be added to your project and compiled.

There are number of reasons for this:

- Doing so can cause naming collisions between source files.
- In a large project it can be hard to avoid one definition rules (ODR) issues.
- Any change to such a .cpp file will cause both the .cpp file and any other .cpp file that includes it to recompile, which can take a long time. Headers tend to change less often than source files.
- It is non-conventional to do so.
  
 Best practice : Avoid #including .cpp files.
Tip : If your project doesn’t compile unless you #include .cpp files, that means those .cpp files are not being compiled as part of your project. Add them to your project or command line so they get compiled.


### Angled brackets vs double quotes. 
It’s possible that a header file with the same filename might exist in multiple directories. Our use of angled brackets vs double quotes helps give the preprocessor a clue as to where it should look for header files.
When we use angled brackets, we’re telling the preprocessor that this is a header file we didn’t write ourselves. The preprocessor will search for the header only in the directories specified by the `include directories`. The `include directories` are configured as part of your project/IDE settings/compiler settings, and typically default to the directories containing the header files that come with your compiler and/or OS. The preprocessor will not search for the header file in your project’s source code directory.
When we use double-quotes, we’re telling the preprocessor that this is a header file that we wrote. The preprocessor will first search for the header file in the current directory. If it can’t find a matching header there, it will then search the `include directories`.

Rule: Use double quotes to include header files that you’ve written or are expected to be found in the current directory. Use angled brackets to include headers that come with your compiler, OS, or third-party libraries you’ve installed elsewhere on your system.

Another commonly asked question is “why doesn’t iostream (or any of the other standard library header files) have a .h extension?”. The answer is that _iostream.h_ is a different header file than _iostream_! To explain requires a short history lesson.

Modern C++ now contains 4 sets of header files:

|Header type|Naming convention|Example|Identifiers placed in namespace|
|---|---|---|---|
|C++ specific (new)|<xxx>|iostream|`std` namespace|
|C compatibility (new)|<cxxx>|cstddef|`std` namespace (required)  <br>global namespace (optional)|
|C++ specific (old)|<xxx.h>|iostream.h|Global namespace|
|C compatibility (old)|<xxx.h>|stddef.h|Global namespace (required)  <br>`std` namespace (optional)|

Warning

The new C compatibility headers <cxxx> may optionally declare names in the global namespace, and the old C compatibility headers <xxx.h> may optionally declare names in the `std` namespace. Names in these locations should be avoided, as those names may not be declared in those locations on other implementations.

Best practice : Use the standard library header files without the .h extension. User-defined headers should still use a .h extension.

Another common question involves how to include header files from other directories.

One (bad) way to do this is to include a relative path to the header file you want to include as part of the #include line. For example:
```cpp
#include "headers/myHeader.h"
#include "../moreHeaders/myOtherHeader.h"
```

While this will compile (assuming the files exist in those relative directories), the downside of this approach is that it requires you to reflect your directory structure in your code. If you ever update your directory structure, your code won’t work anymore.

A better method is to tell your compiler or IDE that you have a bunch of header files in some other location, so that it will look there when it can’t find them in the current directory. This can generally be done by setting an _include path_ or _search directory_ in your IDE project settings.

For gcc users
Using g++, you can use the -I option to specify an alternate include directory:  
`g++ -o main -I./source/includes main.cpp`

There is no space after the `-I`. For a full path (rather than a relative path), remove the `.` after `-I`.

For VS Code users

In your _tasks.json_ configuration file, add a new line in the _“Args”_ section:  
`"-I./source/includes",`

There is no space after the `-I`. For a full path (rather than a relative path), remove the `.` after `-I`.

The nice thing about this approach is that if you ever change your directory structure, you only have to change a single compiler or IDE setting instead of every code file.

It’s common that the content of a header file will make use of something that is declared (or defined) in another header file. When this happens, the header file should #include the other header file containing the declaration (or definition) that it needs.

Foo.h:

```cpp
#include <string_view> // required to use std::string_view

std::string_view getApplicationName(); // std::string_view used here
```

When your source (.cpp) file #includes a header file, you’ll also get any other header files that are #included by that header (and any header files those include, and so on). These additional header files are sometimes called **transitive includes**, as they’re included implicitly rather than explicitly.


The content of these transitive includes are available for use in your code file. However, you generally should not rely on the content of headers that are included transitively (unless reference documentation indicates that those transitive includes are required). The implementation of header files may change over time, or be different across different systems. If that happens, your code may only compile on certain systems, or may compile now but not in the future. This is easily avoided by explicitly including all of the header files the content of your code file requires.

Best practice Each file should explicitly #include all of the header files it needs to compile. Do not rely on headers included transitively from other headers.

Unfortunately, there is no easy way to detect when your code file is accidentally relying on content of a header file that has been included by another header file.

If your header files are written properly and #include everything they need, the order of inclusion shouldn’t matter.

Best practice :
To maximize the chance that missing includes will be flagged by compiler, order your #includes as follows (skipping any that are not relevant):
- The paired header file for this code file (e.g. `add.cpp` should `#include "add.h"`)
- Other headers from the same project (e.g. `#include "mymath.h"`)
- 3rd party library headers (e.g. `#include <boost/tuple/tuple.hpp>`)
- Standard library headers (e.g. `#include <iostream>`)

The headers for each grouping should be sorted alphabetically (unless the documentation for a 3rd party library instructs you to do otherwise).

recommendations for creating and using header files.

- Always include header guards (we’ll cover these next lesson).
- Do not define variables and functions in header files (for now).
- Give a header file the same name as the source file it’s associated with (e.g. `grades.h` is paired with `grades.cpp`).
- Each header file should have a specific job, and be as independent as possible. For example, you might put all your declarations related to functionality A in A.h and all your declarations related to functionality B in B.h. That way if you only care about A later, you can just include A.h and not get any of the stuff related to B.
- Be mindful of which headers you need to explicitly include for the functionality that you are using in your code files, to avoid inadvertent transitive includes.
- A header file should #include any other headers containing functionality it needs. Such a header should compile successfully when #included into a .cpp file by itself.
- Only #include what you need (don’t include everything just because you can).
- Do not #include .cpp files.
- Prefer putting documentation on what something does or how to use it in the header. It’s more likely to be seen there. Documentation describing how something works should remain in the source files.


## 2.12 Header guards

a variable or function identifier can only have one definition (the one definition rule). Thus, a program that defines a variable identifier or a function more than once will cause a compile error.
While two definition in the same program are easy to fix (remove the duplicate definition), with header files, it’s quite easy to end up in a situation where a definition in a header file gets included more than once. This can happen when a header file #includes another header file (which is common).

wave.h:
```Cpp
#include "square.h"
```
main.cpp:
```Cpp
#include "square.h"
#include "wave.h"
```

### Header guards
The good news is that we can avoid the above problem via a mechanism called a header guard (also called an include guard). Header guards are conditional compilation directives that take the following form:
```Cpp
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```
When this header is `#included`, the preprocessor will check whether *SOME_UNIQUE_NAME_HERE* has been previously defined in this translation unit. If this is the first time we’re including the header, *SOME_UNIQUE_NAME_HERE* will not have been defined. Consequently, it #defines *SOME_UNIQUE_NAME_HERE* and includes the contents of the file. If the header is included again into the same file, *SOME_UNIQUE_NAME_HERE* will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored (thanks to the #ifndef).

All of your header files should have header guards on them. *SOME_UNIQUE_NAME_HERE* can be any name you want, but by convention is set to the full filename of the header file, typed in all caps, using underscores for spaces or punctuation. For example, square.h would have the header guard:
square.h:
```Cpp
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

#endif
```

In large programs, it’s possible to have two separate header files (included from different directories) that end up having the same filename (e.g. directoryA\config.h and directoryB\config.h). If only the filename is used for the include guard (e.g. CONFIG_H), these two files may end up using the same guard name. If that happens, any file that includes (directly or indirectly) both config.h files will not receive the contents of the include file to be included second. This will probably cause a compilation error.

Because of this possibility for guard name conflicts, many developers recommend using a more complex/unique name in your header guards. Some good suggestions are a naming convention of PROJECT_PATH_FILE_H, FILE_LARGE-RANDOM-NUMBER_H, or FILE_CREATION-DATE_H.

main.cpp:
```Cpp
// Square.h included from main.cpp
#ifndef SQUARE_H // square.h included from main.cpp
#define SQUARE_H // SQUARE_H gets defined here

// and all this content gets included
int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H

#ifndef WAVE_H // wave.h included from main.cpp
#define WAVE_H
#ifndef SQUARE_H // square.h included from wave.h, SQUARE_H is already defined from above
#define SQUARE_H // so none of this content gets included

int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H
#endif // WAVE_H

int main(){..}
```
Let’s look at how this evaluates.

First, the preprocessor evaluates #ifndef SQUARE_H. SQUARE_H has not been defined yet, so the code from the #ifndef to the subsequent #endif is included for compilation. This code defines SQUARE_H, and has the definition for the getSquareSides function.

Later, the next #ifndef SQUARE_H is evaluated. This time, SQUARE_H is defined (because it got defined above), so the code from the #ifndef to the subsequent #endif is excluded from compilation.

Header guards prevent duplicate inclusions because the first time a guard is encountered, the guard macro isn’t defined, so the guarded content is included. Past that point, the guard macro is defined, so any subsequent copies of the guarded content are excluded.

Note that the goal of header guards is to prevent a code file from receiving more than one copy of a guarded header. By design, header guards do not prevent a given header file from being included (once) into separate code files. This can also cause unexpected problems if you add the definition in header files. 
If you include this header in two .cpp there will be the same definition in two files => linker error.
Therefore simply put the function definition in one of the .cpp files so that the header just contains a forward declaration

### Can’t we just avoid definitions in header files?
We’ve generally told you not to include function definitions in your headers. So you may be wondering why you should include header guards if they protect you from something you shouldn’t do.

There are quite a few cases we’ll show you in the future where it’s necessary to put non-function definitions in a header file. For example, C++ will let you create your own types. These custom types are typically defined in header files, so the type definitions can be propagated out to the code files that need to use them. Without a header guard, a code file could end up with multiple (identical) copies of a given type definition, which the compiler will flag as an error.

So even though it’s not strictly necessary to have header guards at this point in the tutorial series, we’re establishing good habits now, so you don’t have to unlearn bad habits later.
### `#pragma once`

Modern compilers support a simpler, alternate form of header guards using the #pragma preprocessor directive:
IN Tour HPP
```Cpp
#pragma once

// your code here
```
`#pragma once` serves the same purpose as header guards: to avoid a header file from being included multiple times. With traditional header guards, the developer is responsible for guarding the header (by using preprocessor directives #ifndef, #define, and #endif). With `#pragma once`, we’re requesting that the compiler guard the header. How exactly it does this is an implementation-specific detail.

There is one known case where `#pragma once` will typically fail. If a header file is copied so that it exists in multiple places on the file system, if somehow both copies of the header get included, header guards will successfully de-dupe the identical headers, but `#pragma once` won’t (because the compiler won’t realize they are actually identical content).

For most projects, `#pragma once` works fine, and many developers now prefer it because it is easier and less error-prone. Many IDEs will also auto-include `#pragma once` at the top of a new header file generated through the IDE.

Warning: The `#pragma` directive was designed for compiler implementers to use for whatever purposes they desire. As such, which pragmas are supported and what meaning those pragmas have is completely implementation-specific. With the exception of `#pragma once`, do not expect a pragma that works on one compiler to be supported by another.

Because `#pragma once` is not defined by the C++ standard, it is possible that some compilers may not implement it. For this reason, some development houses (such as Google) recommend using traditional header guards. In this tutorial series, we will favor header guards, as they are the most conventional way to guard headers. However, support for `#pragma once` is fairly ubiquitous at this point, and if you wish to use `#pragma once` instead, that is generally accepted in modern C++.


### Summary

Header guards are designed to ensure that the contents of a given header file are not copied more than once into any single file, in order to prevent duplicate definitions.

Duplicate declarations are fine -- but even if your header file is composed of all declarations (no definitions) it’s still a best practice to include header guards.

Note that header guards do not prevent the contents of a header file from being copied (once) into separate project files. This is a good thing, because we often need to reference the contents of a given header from different project files.

```Cpp
#ifndef ADD_H
#define ADD_H
int add(int x, int y);
#endif
```

## 2.13 How to design your first programs

The most important thing to remember (and hardest thing to do) is to design your program before you start coding. 
If you try to program before you have a good game-plan moving forward, you’ll likely find that your code has a lot of problems, and you’ll have to spend a lot of time fixing problems that could have been avoided altogether with a little thinking ahead.
A little up-front planning will save you both time and frustration in the long run.

In this lesson, we’ll lay out a generalized approach for converting ideas into simple functional programs.

### Design step 1: Define your goal
In order to write a successful program, you first need to define what your goal is. Ideally, you should be able to state this in a sentence or two. It is often useful to express this as a user-facing outcome. For example:
    Allow the user to organize a list of names and associated phone numbers.
    Generate randomized dungeons that will produce interesting looking caverns.

Although this step seems obvious, it’s also highly important. The worst thing you can do is write a program that doesn’t actually do what you (or your boss) wanted!

### Design step 2: Define requirements
While defining your problem helps you determine what outcome you want, it’s still vague. The next step is to think about requirements.

Requirements is a fancy word for both the constraints that your solution needs to abide by (e.g. budget, timeline, space, memory, etc…), as well as the capabilities that the program must exhibit in order to meet the users’ needs. Note that your requirements should similarly be focused on the “what”, not the “how”.

For example:
    Phone numbers should be saved, so they can be recalled later.

A single problem may yield many requirements, and the solution isn’t “done” until it satisfies all of them.

### Design step 3: Define your tools, targets, and backup plan
When you are an experienced programmer, there are many other steps that typically would take place at this point, including:
    Defining what target architecture and/or OS your program will run on.
    Determining what set of tools you will be using.
    Determining whether you will write your program alone or as part of a team.
    Defining your testing/feedback/release strategy.
    Determining how you will back up your code.

### Design step 4: Break hard problems down into easy problems
n real life, we often need to perform tasks that are very complex. Trying to figure out how to do these tasks can be very challenging. In such cases, we often make use of the **top down** method of problem solving. That is, instead of solving a single complex task, we break that task into multiple subtasks, each of which is individually easier to solve. If those subtasks are still too difficult to solve, they can be broken down further. By continuously splitting complex tasks into simpler ones, you can eventually get to a point where each individual task is manageable, if not trivial.

The other way to create a hierarchy of tasks is to do so from the **bottom up**. In this method, we’ll start from a list of easy tasks, and construct the hierarchy by grouping them.

As it turns out, these task hierarchies are extremely useful in programming, because once you have a task hierarchy, you have essentially defined the structure of your overall program. The top level task (in this case, “Clean the house” or “Go to work”) becomes main() (because it is the main problem you are trying to solve). The subitems become functions in the program.

If it turns out that one of the items (functions) is too difficult to implement, simply split that item into multiple sub-items/sub-functions. Eventually you should reach a point where each function in your program is trivial to implement.

### Design step 5: Figure out the sequence of events
Now that your program has a structure, it’s time to determine how to link all the tasks together. The first step is to determine the sequence of events that will be performed.
At this point, we’re ready for implementation.

### Implementation step 1: Outlining your main function
Now we’re ready to start implementation. The above sequences can be used to outline your main program. Don’t worry about inputs and outputs for the time being.
```Cpp
int main()
{
//    doBedroomThings();
//    doBathroomThings();
//    doBreakfastThings();
//    doTransportationThings();

    return 0;
}
```
Note that if you’re going to use this “outline” method for constructing your programs, your functions won’t compile because the definitions don’t exist yet. Commenting out the function calls until you’re ready to implement the function definitions is one way to address this (and the way we’ll show here). Alternatively, you can *stub out* your functions (create placeholder functions with empty bodies) so your program will compile.

### Implementation step 2: Implement each function
In this step, for each function, you’ll do three things:
    1. Define the function prototype (inputs and outputs)
    2. Write the function
    3. Test the function

If your functions are granular enough, each function should be fairly simple and straightforward. If a given function still seems overly-complex to implement, perhaps it needs to be broken down into subfunctions that can be more easily implemented (or it’s possible you did something in the wrong order, and need to revisit your sequencing of events).

After coding the function, we’ve implemented some temporary code in function main to test that function getUserInput (including its return value) is working correctly.

We can run this program many times with different input values and make sure that the program is behaving as we expect at this point. If we find something that doesn’t work, we know the problem is in the code we’ve just written.

Once we’re convinced the program is working as intended up to this point, we can remove the temporary testing code, and proceed to implementation of the next function (function getMathematicalOperation). We won’t finish the program in this lesson, as we need to cover some additional topics first.

Remember: Don’t implement your entire program in one go. Work on it in steps, testing each step along the way before proceeding.

### Implementation step 3: Final testing
Once your program is “finished”, the last step is to test the whole program and ensure it works as intended. If it doesn’t work, fix it. 9.1 Introduction to testing your code.

### Words of advice when writing programs
**Keep your programs simple to start** If you try to write something too complex to start, you will become overwhelmed and discouraged at your lack of progress. Instead, make your first goal as simple as possible, something that is definitely within your reach.

**Add features over time** Once you have your simple program working and working well, then you can add features to it. By adding each feature incrementally your program will get progressively more complex without overwhelming you in the process.

**Focus on one area at a time** Don’t try to code everything at once, and don’t divide your attention across multiple tasks. Focus on one task at a time. It is much better to have one working task and five that haven’t been started yet than six partially-working tasks. If you split your attention, you are more likely to make mistakes and forget important details.

**Test each piece of code as you go** New programmers will often write the entire program in one pass. Then when they compile it for the first time, the compiler reports hundreds of errors. This can not only be intimidating, if your code doesn’t work, it may be hard to figure out why. Instead, write a piece of code, and then compile and test it immediately. If it doesn’t work, you’ll know exactly where the problem is, and it will be easy to fix. Once you are sure that the code works, move to the next piece and repeat. It may take longer to finish writing your code, but when you are done the whole thing should work, and you won’t have to spend twice as long trying to figure out why it doesn’t.

**Don’t invest in perfecting early code** The first draft of a feature (or program) is rarely good. Furthermore, programs tend to evolve over time, as you add capabilities and find better ways to structure things. If you invest too early in polishing your code (adding lots of documentation, full compliance with best practices, making optimizations), you risk losing all of that investment when a code change is necessary. Instead, get your features minimally working and then move on. As you gain confidence in your solutions, apply successive layers of polish. Don’t aim for perfect -- non-trivial programs are never perfect, and there’s always something more that could be done to improve them. Get to “good enough” and move on.

**Optimize for maintainability, not performance.** There is a famous quote (by Donald Knuth) that says “premature optimization is the root of all evil”. New programmers often spend far too much time thinking about how to micro-optimize their code (e.g. trying to figure out which of 2 statements is faster). This rarely matters. Most performance benefits come from good program structure, using the right tools and capabilities for the problem at hand, and following best practices. Additional time should be used to improve the maintainability of your code. Find redundancy and remove it. Split up long functions into shorter ones. Replace awkward or hard to use code with something better. The end result will be code that is easier to improve and optimize later (after you’ve determined where optimization is actually needed) and fewer bugs. We offer some additional suggestions in lesson 3.10 -- Finding issues before they become problems.

A complex system that works is invariably found to have evolved from a simple system that worked
—John Gall, Systemantics: How Systems Really Work and How They Fail


### Conclusion
Many new programmers shortcut the design process (because it seems like a lot of work and/or it’s not as much fun as writing the code). However, for any non-trivial project, following these steps will save you a lot of time in the long run. A little planning up front saves a lot of debugging at the end.

Spending a little time up front thinking about how to structure your program will lead to better code and less time spent finding and fixing errors.

As you become more comfortable with these concepts and tips, they will start coming more naturally to you. Eventually you will get to the point where you can write entire functions (and short programs) with minimal pre-planning.

## 2.x Chapter 2 summary and quizz
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