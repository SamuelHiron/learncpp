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
    When a variable is initialized using an empty set of braces, a special form of list-initialization called **value-initialization** takes place. In most cases, value-initialization will implicitly initialize the variable to **zero** (or whatever value is closest to zero for a given type). In cases where zeroing occurs, this is called **zero-initialization**.
    `int width {}; // value-initialization / zero-initialization to value 0`

    For class types, value-initialization (and default-initialization) may instead initialize the object to predefined default values, which may be non-zero.

    Use direct-list-initialization when you’re actually using the initial value: `int x {0}; f(x)`

    Use value-initialization when the object’s value is temporary and will be replaced: `int x {}; x =f(y)`

    Initialize your variables upon creation. You may eventually find cases where you want to ignore this advice for a specific reason (e.g. a performance critical section of code that uses a lot of variables), and that’s okay, as long as the choice is made deliberately.

    recommendation https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#es20-always-initialize-an-object creator C++


    **instanciation** = variable created (allocated) and initialized (include default initialization)
    An instantiated object is sometimes called an **instance**. 
```Cpp
    int a, b = 5;     // wrong: a is not initialized to 5!
    int a = 5, b = 5; // correct: a and b are initialized to 5
```
The best way to remember that this is wrong is to note that each variable can only be initialized by its own initializer



    C++17 introduced the `[[maybe_unused]]` attribute, which allows us to tell the compiler that we’re okay with a variable being unused. The compiler will not generate unused variable warnings for such variables.
    `[[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused`


## 1.5 Introduction to iostream: cout, cin, and endl
```Cpp
#include <iostream>
std::cout // send data to the console to be printed as text. cout stands for “character output”.
<< "Hi" //insertion operator (<<), to send the text Hi to the consol
std::endl; // std::endl will cause the cursor to move to the next line &&  empty the buffer (slow)
std::cin // (which stands for “character input”) reads input from keyboard.
```

std::cout is processed in C++. Statements in our program request that output be sent to the console. However, that output is typically not sent to the console immediately. Instead, the requested output “gets in line”, and is stored in a region of memory set aside to collect such requests (called a buffer). Periodically, the buffer is flushed, meaning all of the data collected in the buffer is transferred to its destination (in this case, the console).
This also means that if your program crashes, aborts, or is paused (e.g. for debugging purposes) before the buffer is flushed, any output still waiting in the buffer will not be displayed.
Writing data to a buffer is typically fast, whereas transferring a batch of data to an output device is comparatively slow. Buffering can significantly increase performance by batching multiple output requests together to minimize the number of times output has to be sent to the output device.

Note that you don’t need to output '\n' when accepting a line of input, as the user will need to press the enter key to have their input accepted, and this will move the cursor to the next line of the console.

inputting data is also a two stage process:
    The individual characters you enter as input are added to the end of an input buffer (inside std::cin). The enter key (pressed to submit the data) is also stored as a '\n' character.
    The extraction operator ‘>>’ removes characters from the front of the input buffer and converts them into a value that is assigned (via copy-assignment) to the associated variable. This variable can then be used in subsequent statements.

```cpp
#include <iostream> //for std::cout and stp::cin

int main()
{
    std::cout << "Enter two numbers: ";

    int x{};
    std::cin >> x;

    int y{};
    std::cin >> y;

    std::cout << "You entered " << x << " and " << y << '\n';

    return 0;
}
```

if you input `4 5<enter>` it will be the same as `4<enter>` then `5<enter>`

std::cin is buffered because it allows us to separate the entering of input from the extract of input. We can enter input once and then perform multiple extraction requests on it.
If the input buffer is empty, operator >> will wait for the user to enter more data. Any leading whitespace is discarded from the entered data.

`int x {}; std::cin <<x // you put 5a\n` 5 will be extracted, converted to an integer, and assigned to variable x. a\n will be left in the input buffer for the next extraction.
if the user put `b` => extraction failure. Variable x would be set to 0, and future extractions will fail until the input stream is cleared.

if you enter a really big number
x can only hold numbers up to a certain size. If you enter a value larger than the largest number x can hold, it will be set to the largest number that x can hold (which is probably 2147483647, but might be different on your system). 

## 1.6 Uninitialized variables and undefined behavior
Unlike some programming languages, C/C++ does not automatically initialize most variables to a given value (such as zero).
When a variable that is not initialized is given a memory address to use to store data, the default value of that variable is whatever (garbage) value happens to already be in that memory address!
A variable that has not been given a known value (through initialization or assignment) is called an **uninitialized variable**.
    Initialized = The object is given a known value at the point of definition.
    Assignment = The object is given a known value beyond the point of definition.
    Uninitialized = The object has not been given a known value yet.

`int x;` In most cases (such as this one), default-initialization performs no actual initialization. Thus we’d say x is uninitialized. We’re focused on the outcome (the object has not been given a known value), not the process.

For now, you should always initialize your variables because the cost of doing so is minuscule compared to the benefit. Once you are more comfortable with the language, there may be certain cases where you omit the initialization for optimization purposes. But this should always be done selectively and intentionally.

always initialize your variables best practice


**Undefined behavior** (often abbreviated UB) is the result of executing code whose behavior is not well-defined by the C++ language. In this case, the C++ language doesn’t have any rules determining what happens if you use the value of a variable that has not been given a known value. Consequently, if you actually do this, undefined behavior will result.

implementation-defined behavior depends on the compiler ex sizeof int
Unspecified behavior  implementation not require to document the behavior
avoid both when possible

## 1.7 Keywords and naming identifiers
C++ reserves a set of 92 words, called keywords, (as of C++23) for its own use. 
| Colonne 1       | Colonne 2       | Colonne 3       | Colonne 4       | Colonne 5       | Colonne 6       |
|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|
| alignas         | alignof         | and             | and_eq          | asm             | auto            |
| bitand          | bitor           | bool            | break           | case            | catch           |
| char            | char8_t         | char16_t        | char32_t        | class           | compl           |
| concept         | const           | consteval       | constexpr       | constinit       | const_cast      |
| continue        | co_await        | co_return       | co_yield        | decltype        | default         |
| delete          | do              | double          | dynamic_cast    | else            | enum            |
| explicit        | export          | extern          | false           | float           | for             |
| friend          | goto            | if              | inline          | int             | long            |
| mutable         | namespace       | new             | noexcept        | not             | not_eq          |
| nullptr         | operator        | or              | or_eq           | private         | protected       |
| public          | register        | reinterpret_cast| requires        | return          | short           |
| signed          | sizeof          | static          | static_assert   | static_cast     | struct          |
| switch          | template        | this            | thread_local    | throw           | true            |
| try             | typedef         | typeid          | typename        | union           | unsigned        |
| using           | virtual         | void            | volatile        | wchar_t         | while           |
| xor             | xor_eq          |                 |                 |                 |                 |

C++ also defines special identifiers: `override`, `final`, `import`, and `module`. These have a specific meaning when used in certain contexts but are not reserved otherwise.

It is conventional in C++ that variable names should begin with a lowercase letter. If the variable name is a single word or acronym, the whole thing should be written in lowercase letters.
Most often, function names are also started with a lowercase letter.
identifier names that start with a capital letter are typically used for user-defined types (such as structs, classes, and enumerations).
If the variable or function name is multi-word, there are two common conventions: words separated by underscores (sometimes called snake_case), or intercapped (sometimes called camelCase).

It’s worth noting that if you’re working in someone else’s code, it’s generally considered better to match the style of the code you are working in than to rigidly follow the naming conventions laid out above.

Avoid naming your identifiers starting with an underscore. Although syntactically legal, these names are typically reserved for OS, library, and/or compiler use.

A good rule of thumb is to make the length of an identifier proportional to how specific and accessible the identifier is. This means:
    An identifier that exists for only a few statements (e.g. in the body of a short function) can have a shorter name.
    An identifier that is accessible from anywhere might benefit from a longer name.
    An identifier that represents a non-specific number (e.g. anything the user provides) can have a shorter name.
    An identifier that represents a specific value (e.g. the length of an inseam in millimeters) should have a longer name.

Avoid abbreviations, except when they are common and unambiguous (e.g. num, cm, idx).
For variable declarations, it can be useful to use a comment to describe what a variable is going to be used for, or to explain anything else that might not be obvious

## 1.8 Whitespace and basic formatting
**Whitespace** is a term that refers to characters that are used for formatting purposes. In C++, this refers primarily to spaces, tabs, and newlines, used in C++ for separating certain language elements, inside text, and for formatting code.
`int x; // int and x must be whitespace separated`
Preprocessor directives (e.g. `#include <iostream>`) must be placed on separate lines.
```cpp
std::cout << "Hello
     world!"; // Not allowed!

// Quoted text separated by nothing but whitespace (spaces, tabs, or newlines) will be concatenated:
std::cout << "Hello "
     "world!"; // prints "Hello world!"
```

Whitespace is otherwise generally ignored.
Unlike some other languages, C++ does not enforce any kind of formatting restrictions on the programmer. For this reason, we say that C++ is a whitespace-independent language.
recommand tabs to 3 or 4 spaces worth of indentation

Many editors have a built-in feature (or plugin/extension) that will show a line (called a “column guide”) at a given column (e.g. at 80 characters), so you can easily see when your lines are getting too long. 
If a long line is split with an operator (eg. << or +), the operator should be placed at the beginning of the next line, not the end of the current line
```
std::cout << 3 + 4
    + 5 + 6
    * 7 * 8;
```
Use whitespace to make your code easier to read by aligning values or comments or adding spacing between blocks of code.

When working in an existing project, be consistent with whatever style has already been adopted.

Most modern IDEs will help you format your code as you type it in (e.g. when you create a function, the IDE will automatically indent the statements inside the function body).

For easier access, we recommend adding a keyboard shortcut to auto-format the active file.
There are also external tools that can be used to automatically format code. clang-format "https://clang.llvm.org/docs/ClangFormat.html" is a popular one.

A **style guide** is a concise, opinionated document containing (sometimes arbitrary) programming conventions, formatting guidelines, and best practices. The goal of a style guide is to ensure that all developers on a project are programming in a consistent manner.
Some commonly referenced C++ style guides include:
    C++ Core Guidelines http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines, maintained by Bjarne Stroustrup and Herb Sutter. <== we follow that
    Google.
    LLVM
    GCC/GNU

## 1.9 Introduction to literals and operators
```cpp
std::cout << "Hello world!";
int x { 5 };
```
What are ‘”Hello world!”‘ and ‘5’?  literals
A **literal** (also known as a **literal constant**) is a fixed value that has been inserted directly into the source code.
The value of a literal is fixed and cannot be changed. This is why literals are called constants.
A literal’s value is placed directly in the executable, and the executable itself can’t be changed after it is created. A variable’s value is placed in memory, and the value of memory can be changed while the executable is running.
Literals are values that are inserted directly into the source code. These values usually appear directly in the executable code (unless they are optimized out).
Objects and variables represent memory locations that hold values. These values can be fetched on demand.

In mathematics, an **operation** is a process involving zero or more input values (called **operands**) that produces a new value (called an *output value*). The specific operation to be performed is denoted by a symbol called an **operator**.
In C++, the output value of an operation is often called a **return value**.

While most operators have symbols for names (e.g. `+`, or `==`), there are also a number of operators that are keywords (e.g. `new`, `delete`, and `throw`).
For operators that are symbols, it is common to append the operator’s symbol to the word operator.
For example, the plus operator would be written `operator+`, and the extraction operator would be written `operator>>`.

The number of operands that an operator takes as input is called the operator’s **arity**.
4 differents arity in C++:
    Unary operators act on one operand.
    Binary operators act on two operand.
    Ternary operators act on three operands. There is also only one of these in C++, the conditional operator.
    Nullary operators act on zero operands. There is also only one of these in C++, the throw operator.

Operators can be chained together such that the output of one operator can be used as the input for another operator. For example, given the following: `2 * 3 + 4`

For now, it’s enough to know that the arithmetic operators execute in the same order as they do in standard mathematics: Parenthesis first, then Exponents, then Multiplication & Division, then Addition & Subtraction. This ordering is sometimes abbreviated PEMDAS, or expanded to the mnemonic “Please Excuse My Dear Aunt Sally”.

Most operators in C++ just use their operands to calculate a return value.
There are a few operators that do not produce return values (such as `delete` and `throw`). 

Some operators have additional behaviors. An operator (or function) that has some observable effect beyond producing a return value is said to have a **side effect**. 
For example, `x = 5` has the side effect of assigning value `5` to variable `x`. 

In common language, the term “side effect” is typically used to mean a secondary (often negative or unexpected) result of some other thing happening (such as taking medicine).
In C++, the term “side effect” has a different meaning: it is an observable effect of an operator or function beyond producing a return value.
Since assignment has the observable effect of changing the value of an object, this is considered a side effect. We use certain operators (e.g. the assignment operator) primarily for their side effects (rather than the return value those operators produce). In such cases, the side effect is both beneficial and predictable (and it is the return value that is often incidental).

For the operators we call primarily for their side effects (e.g. `operator=` or `operator<<`), it’s not always obvious what return values they produce (if any). For example, what return value would you expect x = 5 to have?

Both `operator=` and `operator<<` (when used to output values to the console) return their left operand. Thus, `x = 5` returns `x`, and `std::cout << 5` returns `std::cout`. This is done so that these operators can be chained.

For example, `x = y = 5` evaluates as `x = (y = 5)`. First `y = 5` assigns `5` to `y`. This operation then returns `y`, which can then be assigned to `x`.

`std::cout << "Hello " << "world!"` evaluates as (`std::cout << "Hello "`) `<< "world!"`. This first prints `"Hello "` to the console. This operation returns `std::cout`, which can then be used to print `"world!"` to the console as well.

## 1.10 Introduction to expressions
```cpp
// five() is a function that returns the value 5
int five()
{
    return 5;
}

int main()
{
    int a{ 2 };       // initialize variable a with literal value 2
    int b{ 2 + 3 };   // initialize variable b with computed value 5
    int d{ b };       // initialize variable d with variable value 5
    int e{ five() };  // initialize variable e with function return value 5

    return 0;
}
```

All of these initializers make use of an expression.

In general programming, an **expression** is a non-empty sequence of literals, variables, operators, and function calls that calculates a value. The process of executing an expression is called **evaluation**, and the resulting value produced is called the *result* of the expression (also sometimes called the **return value**).

In C++, the result of an expression is one of the following:
    A value (most commonly)
    An object or a function.
    Nothing. These are the result of non-value returning function calls that are called only for their side effects

For now, to keep things simple, we’ll assume expressions are evaluated to produce values.
When an expression is evaluated, each of the terms inside the expression are evaluated, until a single value remains. 
```cpp
2               // 2 is a literal that evaluates to value 2
"Hello world!"  // "Hello world!" is a literal that evaluates to text "Hello world!"
x               // x is a variable that evaluates to the value held by variable x
2 + 3           // operator+ uses operands 2 and 3 to evaluate to value 5
five()          // evaluates to the return value of function five()

x = 5           // x = 5 has side effect of assigning 5 to x, evaluates to x
x = 2 + 3       // has side effect of assigning 5 to x, evaluates to x
std::cout << x  // has side effect of printing value of x to console, evaluates to std::cout
```
literals evaluate to their own values. Variables evaluate to the value of the variable. Operators (such as operator+) use their operands to evaluate to some other value.
function calls evaluate to whatever value the function returns.

Wherever a single value is expected in C++, you can use an value-producing expression instead, and the expression will be evaluated to produce a single value.
Expressions do not end in a semicolon, and cannot be compiled by themselves. Rather, expressions are always evaluated as part of statements.

An **expression statement** is a statement that consists of an expression followed by a semicolon.
When an expression is used in an expression statement, any result generated by the expression is discarded (because it is not used).
For example, when the expression `x = 5` evaluates, the return value of `operator=` is discarded. And that’s fine, because we just wanted to assign `5` to `x` anyway.
expression statements that compile but have no effect. For example, the expression statement (2 * 3;) is an expression statement that is discarded.

a **subexpression** is an expression used as an operand. For example, the subexpressions of `x = 4 + 5` are `x` and `4 + 5`.
A **full expression** is an expression that is not a subexpression.
In casual language, a **compound expression** is an expression that contains two or more uses of operators.

## 1.11 Developing your first program
New programmers often try to write an entire program all at once, and then get overwhelmed when it produces a lot of errors. A better strategy is to add one piece at a time, make sure it compiles, and test it. 

The first and primary goal of programming is to make your program work. A program that doesn’t work isn’t useful regardless of how well it’s written.
However, there’s a saying I’m fond of: “You have to write a program once to know how you should have written it the first time.” This speaks to the fact that the best solution often isn’t obvious, and that our first solutions to problems are usually not as good as they could be.

When we’re focused on figuring out how to make our programs work, it doesn’t make a lot of sense to invest a lot of time into code we don’t even know if we’ll keep. So we take shortcuts. We skip things like error handling and comments. We sprinkle debugging code throughout our solution to help us diagnose issues and find errors. We learn as we go -- things we thought might work don’t work after all, and we have to backtrack and try another approach.

The end result is that our initial solutions often aren’t well structured, robust (error-proof), readable, or concise. So once your program is working, your job really isn’t done (unless the program is a one-off/throwaway). The next step is to cleanup your code. This involves things like: removing (or commenting out) temporary/debugging code, adding comments, handling error cases, formatting your code, and ensuring best practices are followed. And even then, your program may not be as simple as it could be -- perhaps there is redundant logic that can be consolidated, or multiple statements that can be combined, or variables that aren’t needed, or a thousand other little things that could be simplified. Too often new programmers focus on optimizing for performance when they should be optimizing for maintainability.

All of this is really to say: don’t be frustrated if/when your solutions don’t come out wonderfully optimized right out of your brain. That’s normal. Perfection in programming is an iterative process.

As you read through this site for the first time, focus less on memorizing specifics, and more on understanding what’s possible. Then, when you have a need to implement something in a program you’re writing, you can come back here (or to a reference site) and refresh yourself on how to do so.

## 1.x Chapter 1 summary and quiz

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