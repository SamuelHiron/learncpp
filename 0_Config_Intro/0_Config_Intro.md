# Chapter 0 : Introduction/Getting Started
## 0.1 Intro to these tutorials
### Advices
    Type in the examples by hand, questionning what each things does
    fix mistakas and bugs before asking
    experiment with exmaples

## 0.2 intro to programs and language
**software** broadly refers to the programs on a system that are designed to be executed on hardware.
**platform** refers to a compatible set of hardware and software (OS, browser, etc…) that provides an environment for software to run.
.txt"
**portability** to be able to go to multiple platform
**C++** high lvl language 

## 0.3 intro to C/C++
Five major updates (C++11, C++14, C++17, C++20, and C++23) 
C/C++ philosophy => trust the programmer

## 0.4 intro to C++ dev
 1) Define the problem
 2) Determine how to solve it, solutions must be:
    + straightforward (not overly complicated or confusing).
    + well documented (especially around any assumptions being made or limitations).
    + built modularly, so parts can be reused or changed later without impacting other parts of the program.
    + recover gracefully or give useful error messages when something unexpected happens.
 3) write the program with code editor (line number, syntax highlighting and coloring, fixed-width font), primary source code file main.cpp


 A bug is any kind of programming error that prevents the program from operating correctly.

## 0.5 Introduction to the compiler, linker, and libraries
 4) Compiling source code: First check the code, Second translation to machine language instruction in an object file (.o or .obj)
 5) Linking object files and libraries and creating the desired output file
 combine all object file and produce the output file:
    First linker reads all object files and ensure validity
    Second linker ensures all cross-file dependencies are resolved properly (connect reference to definition)
    Third link library files (collection of precompiled code)
        C++ Standard Library and 3rd  party libraries
    Finaly linker produces the output (library or executable file)
 Building = full process from source code to executable (sometimes named build)
 build automations tools (make) with automated tests

 6) and 7) Testing and Debugging 
 test: see if everything is working as planned
 debugging: finding and fixing programming errors

## 0.6 Installing an Integrated Development Environment (IDE)
 software package called an integrated development environment (IDE) bundles and integrates all of editor, compiler, linker and debugger together.
 https://code.visualstudio.com/docs/cpp/config-linux

## 0.7 Compiling your first program
    project = container all source code, data files
    workspace = container hold one or more projects
    `g++ hello_world.cpp -o hello_world -lfmt`

## 0.8 A few common C++ problems
all programs must include one and only one main function
When there is an hard problem:
    + 1rst search engine: If you are searching an error message, paste in the exact error message using quotes (exclude any filenames or line numbers).
    + 2nd AI explanation concept, difference between two things, demonstration of a concept


## 0.9 Configuring your compiler: Build configurations
    A **build configuration** (also called a **build target**) is a collection of project settings that determines how your IDE will build your project:
    + debug configuration (turn off optimization includes debugging info) active by default, for development
    + release configuration (turn on optimization exclude debugging info) for test perfs

    For gcc and Clang users
    Add `-ggdb` to the command line for debug builds and `-O2 -DNDEBUG` for release builds. Use the debug build options for now.
    For GCC and Clang, the `-O#` option is used to control optimization settings. The most common options are as follows:
    - `-O0` is the recommended optimization level for debug builds, as it disables optimization. This is the default setting.
    - `-O2` is the recommended optimization level for release builds, as it applies optimizations that should be beneficial for all programs.
    - `-O3` adds additional optimizations that may or may not perform better than `-O2` depending on the specific program. Once your program is written, you can try compiling your release build with `-O3` instead of `-O2` and measure to see which is faster.

    See [https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html) for information on optimization options.

    For VS Code users
    When you first ran your program, a new file called _tasks.json_ was created under the _.vscode_ folder in the explorer pane. Open the _tasks.json_ file, find _“args”_, and then locate the line _“${file}”_ within that section.
    Above the _“${file}”_ line, add a new line containing the following command (one per line) when debugging:  
    `"-ggdb",`
    Above the _“${file}”_ line, add new lines containing the following commands (one per line) for release builds:  
    `"-O2",`  
    `"-DNDEBUG",`

    Tip : Whenever you update your project settings, make the change for all build configurations (unless it’s not appropriate for some reason

## 0.10 Configuring your compiler: Compiler extensions
    **compiler extensions** =>  compilers implement their own changes to the language
    You can disable compiler extension
    For gcc and Clang users : You can disable compiler extensions by adding the _-pedantic-errors_ flag to the compile command line.
    For VS Code users:
    - Open the tasks.json file, find `"args"`, and then locate the line `"${file}"` within that section.
    - Above the `"${file}"` line, add a new line containing the following commands:

    `"-pedantic-errors",`

    As of the time of writing, VS Code does not automatically add a newline to the end of code files that are missing it (something that is pedantically required by the C++ standard). Fortunately, we can tell VS Code to do so:

    - Open VS Code and go to _File (Code if using a Mac) > Preferences > Settings_. This will open a settings dialog.
    - Enter `insert final newline` into the search bar.
    - In both the _Workspace Settings_ and _User Settings_ tabs, ensure the checkbox labeled _Files: Insert Final Newline_ is checked.
    
    A reminder
    These settings are applied on a per-project basis. You need to set them every time you create a new project, or create a template project with those settings once and use that to create new projects.
## 0.11 Configuring your compiler: Warning and error levels
    violates the rules of the language, then your program is **ill-formed**.
    compiler encounters some kind of issue, it will emit **diagnostic message** (often called a **diagnostic** for short): 
    - A **diagnostic error** (**error** for short) means the compiler has decided to halt compilation, because it either cannot proceed or deems the error serious enough to stop. Diagnostic errors generated by the compiler are often called **compilation errors**, **compiler errors**, or **compile errors**.
    - A **diagnostic warning** (**warning** for short) means the compiler has decided not to halt compilation. In such cases, the issue is simply ignored, and compilation proceeds.

    Best practice : Don’t let warnings pile up. Resolve them as you encounter them (as if they were errors). Otherwise a warning about a serious issue may be lost amongst warnings about non-serious issues.

    Best practice Turn your warning levels up, especially while you are learning. The additional diagnostic information may help in identifying programming mistakes that can cause your program to malfunction.


    For gcc users 
    Add the following flags to your command line: `-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion`

    For VS Code users 
    Open the tasks.json file, find “args”, and then locate the line _“${file}”_ within that section.

    Above the _“${file}”_ line, add new lines containing the following commands (one per line):
    "-Wall",
    "-Weffc++",
    "-Wextra",
    "-Wconversion",
    "-Wsign-conversion",


    Best practice
    Enable “Treat warnings as errors”. This will force you to resolve all issues causing warnings.
    For gcc users
    Add the following flag to your command line: _-Werror_

    For VS Code users
    In the `tasks.json` file, add the following flags before “${file}”, one per line:
    "-Werror",

## 0.12 Configuring your compiler: Choosing a language standard
    In professional environments, it’s common to choose a language standard that is one or two versions back from the latest finalized standard.
    For personal projects and while learning, we recommend choosing the latest finalized standard, as there is little downside to doing so.
    This website currently targets the C++17 standard, meaning our lessons and examples assume your compiler is C++17 capable. Some C++20 and C++23 content is available for those with compatible compilers.

    Setting a language standard in GCC/G++/Clang
    For GCC/G++/Clang, you can use compiler options `-std=c++11`, `-std=c++14`, `-std=c++17`, `-std=c++20`, or `-std=c++23` (to enable C++11/14/17/20/23 support respectively). You can also try the latest code name (e.g. `-std=c++2c`) for experimental support for features from the upcoming language standard.

    Setting a language standard for VS Code
    For VS Code, you can follow the rules above for setting a language standard in GCC/G++/Clang.
    Place the appropriate language standard flag (including the double quotes and comma) in the `tasks.json` configuration file, in the `"args"` section, on its own line before `"${file}"`.
    We also want to configure Intellisense to use the same language standard. For C++20, in `settings.json`, change or add the following setting on its own line: `"C_Cpp.default.cppStandard": "c++20"`.
    Each C++ language standard is described by a **standards document**, which is a formal technical document that is the authoritative source for the rules and requirements of a given language standard. Not designed for learning -- rather, it’s designed for compiler writers to be able to implement new language standards accurately, Not free
    draft standards free [here](https://www.open-std.org/jtc1/sc22/wg21/docs/standards).
    Even after a language standard is finalized, compilers supporting that language standard often still have missing, partial, or buggy support for certain features.
    For example, you can see which C++23 features are supported [here](https://en.cppreference.com/w/cpp/compiler_support/23).

## 0.13 What language standard is my compiler using?
    If my compiler is using a preview/pre-release version, should I go back one version?
    If you are just learning the language, it’s not necessary. Just be aware that some features from the upcoming version of the language may be missing, incomplete, buggy, or may change slightly.
    


# Chapter 0 Configs
GCC options
```
-lfmt -ggdb -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++23
-ggdb for debug
-O0 by default (no optimization)
-pedantic-errors disable compiler extension (for portable)
-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion see errors
-Werror treat warning as errors
-std=c++23 use c++23 standards
-O2 -DNDEBUG
```


VSCode in .vscode dans tasks.json  find _“args”_, and then locate the line _“${file}”_ within that section.
Above the _“${file}”_ line, add a new line containing the following command (one per line) 
```
"-ggdb",         // debugging
"-Wall",    //start turn all warnings
"-Weffc++",
"-Wextra",
"-Wconversion",
"-Wsign-conversion",  // end turn all warning 
"-Werror", //treat warning as errors
"-std=c++23",    //use c++23 standatd

"-pedantic-errors",             // disable compiler extension
```
    As of the time of writing, VS Code does not automatically add a newline to the end of code files that are missing it (something that is pedantically required by the C++ standard). Fortunately, we can tell VS Code to do so:
        - Open VS Code and go to _File (Code if using a Mac) > Preferences > Settings_. This will open a settings dialog.
        - Enter `insert final newline` into the search bar.
        - In both the _Workspace Settings_ and _User Settings_ tabs, ensure the checkbox labeled _Files: Insert Final Newline_ is checked.

    We also want to configure Intellisense to use the same language standard. For C++20, in `settings.json`, change or add the following setting on its own line: `"C_Cpp.default.cppStandard": "c++23"`.
