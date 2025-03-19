# Chapter 1:  C++ Basics
## 1.1 Statements and the structure of a program
    introduce topics
    **statement** = an instruction in a computer program that tells the computer to perform an action.
        They ends with a semicolon
        statement = declaration | jump | expression | compound | iteration | try blocks
    **function** = collection of statements that get executed sequentially
    every C++ program must have a function named `main`
    identifier = name of a function,(or object, type, template...)
    text = **plain text** = text with only standard keyboard characters, no special formatting r styling
    control character = space, tab, backspace
    
    `#include` processor directive => we want to use the contents of a file or a library
    
    When an executable program finishes running, program sends a value back to the Operating System in order to indicate wether it ran successfully or not (0 everything is ok).

    **syntax** = set of rule to form valid sentences in the language
    A syntax error occurs when your program violates the grammar rules of the C++ language.

    Key insight
    Compilers will sometimes report that an error has occurred on the line after the one where we’d conventionally fix the issue. If you can’t find the error on the line indicated, check the prior line

## 1.2 Comments
    // single-line comment is used to make a quick comment about a single line of code. above the line it is commenting if too long line
     /*  */  denotes multi-line comment. Everything in between the symbols is ignored.
    Used for :
    + At the library, program, or function level, use comments to describe what.
    + Inside the library, program, or function, use comments to describe how.
    + At the statement level, use comments to describe why.
    should makes sense to someone who has no idea what the code does. Don’t assume you’ll remember why you made specific choices.

    Documentation generation programs such as Doxygen:
            Help standardize the way your code is documented can:
        Generate diagrams, visualizations, and cross-links to make understanding the code structure easier.
        Export your documentation to other formats (e.g. HTML) so it can be easily shared with others (e.g. other team members, or developers who are integrating whatever you are writing).

    commenting out your code : a convenient way to (temporarily) exclude parts of your code from being included in your compiled program.
    Used for :  Find your source of error, remplace code, can't finish now something that doesn't work, need to run a code that doesn't compile

    For VS Code users : You can comment or uncomment a selection by pressing ctrl-/.

    If you do need to comment out a code block that contains multi-line comments, you can also consider using the #if 0 preprocessor directive

## 1.3 Introduction to objects and variables
    **data** is any information that can be moved, processed, or stored by a computer.
    **Programs** are collections of instructions that manipulate data to produce a desired result.
    a **value** is a single piece of data (sometimes called a data value).
        Values placed in single-quotes are interpreted by the compiler as character values.
        Values placed in double-quotes are interpreted by the compiler as text values.
    **literals**  are values that are placed directly into the source code. Read-only
    
    Random Access Memory (RAM) is the main memory in a computer.
    When we run a program, the operating system loads the program into RAM. Any data that is hardcoded into the program itself (e.g. text such as “Hello, world!”) is loaded at this point. The operating system also reserves some additional RAM for the program to use while it is running.
    In C++, direct memory access is discouraged. Instead, we access memory indirectly through an object. 

    An **object** represents a region of storage (typically RAM or a CPU register) that can hold a value. Memory abstraction : we can focus on using objects to store and retrieve values, and not have to worry about where in memory those objects are actually being placed.
    **variable** is an object with a name. Each variable has an identifier, a type, and a value 
    In C++, the term object has a narrower definition that excludes functions.

    A **definition**  statement can be used to tell the compiler that we want to use a variable in our program.

    At **runtime** (when the program is loaded into memory and run), each object is given an actual storage location (such as RAM, or a CPU register) that it can use to store values. The process of reserving storage for an object’s use is called **allocation**. 
    An object is “created” once actual storage has been reserved for the object’s use.
    A **data type** (more commonly just called a **type**) determines what kind of value the object will store.
    An **integer** is a number that can be written without a fractional component
    In C++, the type of an object must be known at compile-time  (so the compiler knows how much memory that object requires), and that type can not be changed without recompiling the program.

    It is possible to define multiple variables of the same type in a single statement by separating the names with a comma. `int a, b;`
    Variables of different types must be defined in separate statements.
    Define each variable in a separate statement on its own line.

## 1.4 Variable assignment and initialization

    After a variable has been defined, you can give it a value (in a separate statement) using the = operator. This process is called **assignment**, and the = operator is called the **assignment operator**. 
    **copy-assignment** copies the value on the right-hand side of the = operator to the variable on the left-hand side of the operator

    When an object is defined, you can optionally provide an initial value for the object. The process of specifying an initial value for an object is called **initialization**, and the syntax used to initialize an object is called an **initializer**. Informally, the initial value is often called an “initializer” as well.

There are 5 common forms of initialization in C++:
    ```
        int a;         // default-initialization (no initializer) a -> 0 

        // Traditional initialization forms:
        int b = 5;     // copy-initialization (initial value after equals sign)
        int c ( 6 );   // direct-initialization (initial value in parenthesis)

        // Modern initialization forms (preferred):
        int d { 7 };   // direct-list-initialization (initial value in braces)
        int e {};      // value-initialization (empty braces)
    ```

    Other forms of initialization include:
        + Aggregate initialization (see 13.8 -- Struct aggregate initialization).
        + Copy-list-initialization (discussed below).
        + Reference initialization (see 12.3 -- Lvalue references).
        + Static-initialization, constant-initialization, and dynamic-initialization (see 7.8 -- Why (non-const) global variables are evil).
        + Zero-initialization (discussed below).

    ### default initialization `int a;`
    no initializer provided => default-initialization, in many cases default-initialization performs no initialization, and leaves the variable with an indeterminate value

    ### copy-initialization `int a = 4;`
    initial value provided after an equals sign
    used whenever there is an implicit copy (passing arguments to a function by value, returning a function by value or catching exception by value)

    ### direct-initialization `int a (4)` 
    value provided inside parenthesis mostly used when values are explicitly cast to another type (`static_cast`) otherwise superseded by direct-list-initialization

    ### List-initialisation `int a {4}` (jack's & advance way initializating object)
    The modern way to initialize objects in C++ is to use a form of initialization that makes use of curly braces. This is called list-initialization (or uniform initialization or brace initialization). <======================== the one to do

    In list-initialization, “narrowing conversions” are disallowed. This means that if you try to list-initialize a variable using a value that the variable can not safely hold, the compiler is required to produce a diagnostic (compilation error or warning) to notify you.
```Cpp
    int main(){
        // An integer can only hold non-fractional values.
        // Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold.
        // Such a conversion is a narrowing conversion, since the fractional part of the value will be lost.
        int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion


        int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
        int w3 (4.5);   // compiles: w3 direct-initialized to value 4

        //Note that this restriction on narrowing conversions only applies to the list-initialization, not to any subsequent assignments to the variable:
        w1 = 4.5;       // okay: copy-assignment allows narrowing conversion of 4.5 to 4

        return 0;
}
```
    When we see curly braces, we know we’re list-initializing an object.

    ### Value-initialization and zero-initialization

## 1.5 Introduction to iostream: cout, cin, and endl

## 1.6 Uninitialized variables and undefined behavior

## 1.7 Keywords and naming identifiers

## 1.8 Whitespace and basic formatting

## 1.9 Introduction to literals and operators

## 1.10 Introduction to expressions

## 1.11 Developing your first program

## 1.x Chapter 1 summary and quiz
