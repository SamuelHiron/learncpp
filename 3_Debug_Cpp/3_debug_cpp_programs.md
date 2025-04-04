

# Debugging C++ Programs

## 3.1 Syntax and semantic errors
Errors generally fall into one of two categories: syntax errors, and semantic errors (logic errors).
A **syntax error** occurs when you write a statement that is not valid according to the grammar of the C++ language. This includes errors such as missing semicolons, mismatched parentheses or braces, etc…
Fortunately, the compiler will detect syntax errors and issue a compilation warning or error, so you easily identify and fix the problem. Then it’s just a matter of compiling again until you get rid of all the errors.

A **semantic error** is an error in meaning. These occur when a statement is syntactically valid, but either violates other rules of the language, or does not do what the programmer intended.

Some kind of semantic errors can be caught by the compiler. Common examples include using an undeclared variable, type mismatches (when we use an object with the wrong type somewhere), etc…

Other semantic errors only manifest at runtime. Sometimes these will cause your program to crash, such as in the case of division by zero.

More often these will just produce the wrong value or behavior => undefined behavior

runtime semantic errors are not easy to find by eyeballing the code. This is where debugging techniques can come in handy.

## 3.2 The debugging process
Let’s say you’ve written a program, and it’s not working correctly -- the code compiles fine, but when you run it, you’re getting an incorrect result. You must have a semantic error somewhere. How can you find it? If you’ve been following best practices by writing a little bit of code and then testing it, you may have a good idea where your error is. Or you may have no clue at all.

All bugs stem from a simple premise: Something that you thought was correct, isn’t. Actually figuring out where that error is can be challenging. In this lesson, we’ll outline the general process of debugging a program.

Once a problem has been identified, debugging the problem generally consists of six steps:
1. Find the root cause of the problem (usually the line of code that’s not working). We’ll discuss some strategies in the next lesson.
2. Ensure you understand why the issue is occurring.
3. Determine how you’ll fix the issue.
4. Repair the issue causing the problem.
5. Retest to ensure the problem has been fixed.
6. Retest to ensure no new problems have emerged.
## 3.3 A strategy for debugging
When debugging a program, in most cases the vast majority of your time will be spent trying to find where the error actually is. Once the issue is found, the remaining steps (fixing the issue and validating that the issue was fixed) are often trivial in comparison.

In this lesson, we’ll start exploring how to find errors.

### Finding problems via code inspection

Let’s say you’ve noticed a problem, and you want to track the cause of that specific problem down. In many cases (especially in smaller programs), we can approximate where the issue is likely to be based on the nature of the error and the way the program is structured.

In cases where you can narrow the problem down to a specific function, you may be able to spot the issue just by looking at the code.

However, as programs get more complex, finding issues by code inspection becomes more complex as well.

First, there’s a lot more code to look at. Looking at every line of code in a program that is thousands of lines long can take a really long time (not to mention it’s incredibly boring). Second, the code itself tends to be more complex, with more possible places for things to go wrong. Third, the code’s behavior may not give you many clues as to where things are going wrong. If you wrote a program to output stock recommendations and it actually output nothing at all, you probably wouldn’t have much of a lead on where to start looking for the problem.

Finally, bugs can be caused by making bad assumptions. It’s almost impossible to visually spot a bug caused by a bad assumption, because you’re likely to make the same bad assumption when inspecting the code, and not notice the error. So if we have an issue that we can’t find via code inspection, how do we find it?

### Finding problems by running the program
we can watch the behavior of the program as it runs, and try to diagnose the issue from that. This approach can be generalized as:
1. Figure out how to reproduce the problem
2. Run the program and gather information to narrow down where the problem is
3. Repeat the prior step until you find the problem

For the rest of this chapter, we’ll discuss techniques to facilitate this approach.
### Reproducing the problem
The first and most important step in finding a problem is to be able to _reproduce the problem_. Reproducing the problem means making the problem appear in a consistent manner. The reason is simple: it’s extremely hard to find an issue unless you can observe it occurring.
If a software issue is blatant (e.g. the program crashes in the same place every time you run it) then reproducing the problem can be trivial. However, sometimes reproducing an issue can be a lot more difficult. The problem may only occur on certain computers, or in particular circumstances (e.g. when the user enters certain input). In such cases, generating a set of reproduction steps can be helpful.
**Reproduction steps** are a list of clear and precise steps that can be followed to cause an issue to recur with a high level of predictability. The goal is to be able to cause the issue to reoccur as much as possible, so we can run our program over and over and look for clues to determine what’s causing the problem. If the issue can be reproduced 100% of the time, that’s ideal, but less than 100% reproducibility can be okay. 

### Homing in on issues
Once we can reasonably reproduce the problem, the next step is to figure out where in the code the problem is. Based on the nature of the problem, this may be easy or difficult. For the sake of example, let’s say we don’t have much of an idea where the problem actually is. How do we find it? Dichotomie approach

We can use this process to debug programs. In the worst case, we may have no idea where the bug is. However, we do know that the problem must be somewhere in the code that executes between the beginning of the program and the point where the program exhibits the first incorrect symptom that we can observe. That at least rules out the parts of the program that execute after *the first observable symptom*. But that still potentially leaves a lot of code to cover. To diagnose the issue, we’ll make some educated guesses about where the problem is, with the goal of homing in on the problem quickly.

Often, whatever it was that caused us to notice the problem will give us an initial guess that’s close to where the actual problem is. For example, if the program isn’t writing data to a file when it should be, then the issue is probably somewhere in the code that handles writing to a file (duh!). Then we can use a dichotomie like strategy to try and isolate where the problem actually is.

Eventually, with enough guesses and some good technique, we can home in on the exact line causing the problem! If we’ve made any bad assumptions, this will help us discover where. When you’ve excluded everything else, the only thing left must be causing the problem. Then it’s just a matter of understanding why.

What guessing strategy you want to use is up to you -- the best one depends on what type of bug it is, so you’ll likely want to try many different approaches to narrow down the issue. As you gain experience in debugging issues, your intuition will help guide you.

So how do we “make guesses”? There are many ways to do so. We’re going to start with some simple approaches in the next chapter, and then we’ll build on these and explore others in future chapters.

## 3.4 Basic debugging tactics
In the previous lesson, we explored a strategy for finding issues by running our programs and using guesswork to home in on where the problem is. In this lesson, we’ll explore some basic tactics for actually making those guesses and collecting information to help find issues.
### Debugging tactic #1: Commenting out your code
Let’s start with an easy one. If your program is exhibiting erroneous behavior, one way to reduce the amount of code you have to search through is to comment some code out and see if the issue persists. If the issue remains unchanged, the commented out code probably wasn’t responsible.
If commenting out causes the problem to morph into some other related problem (e.g. the program stops printing names), then it’s likely that _doMaintenance_ is doing something useful that some other code is dependent on. In this case, we probably can’t tell whether the issue is in _doMaintenance_ or elsewhere, so we can uncomment _doMaintenance_ and try some other approach.
If the problem goes away, then the commented code must be causing the problem, and we should focus our attention there.

Warning:
Don’t forget which functions you’ve commented out so you can uncomment them later!
After making many debugging-related changes, it’s very easy to miss undoing one or two. If that happens, you’ll end up fixing one bug but introducing others!
Having a good version control system is extremely useful here, as you can diff your code against the main branch to see all the debugging-related changes you’ve made (and ensure that they are reverted before you commit your change).

Tip :
An alternate approach to repeatedly adding/removing or uncommenting/commenting debug statements is to use a 3rd party library that will let you leave debug statements in your code but compile them out in release mode via a preprocessor macro. [dbg](https://github.com/sharkdp/dbg-macro/blob/master/dbg.h) is one such header-only library that exists to help facilitate this (via the `DBG_MACRO_DISABLE` preprocessor macro).
We discuss header-only libraries in lesson [7.9 -- Inline functions and variables](https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/).

### Debugging tactic #2: Validating your code flow
Another problem common in more complex programs is that the program is calling a function too many or too few times (including not at all).
In such cases, it can be helpful to place statements at the top of your functions to print the function’s name. That way, when the program runs, you can see which functions are getting called.

Tip :
When printing information for debugging purposes, use `std::cerr` instead of `std::cout`. One reason for this is that `std::cout` may be buffered, which means a bit of time may pass between when you ask `std::cout` to output text and when it actually does. If you output using `std::cout` and then your program crashes immediately afterward, `std::cout` may or may not have actually output yet. This can mislead you about where the issue is. On the other hand, `std::cerr` is unbuffered, which means anything you send to it will output immediately. This helps ensure all debug output appears as soon as possible (at the cost of some performance, which we usually don’t care about when debugging).
Using `std::cerr` also helps make clear that the information being output is for an error case rather than a normal case.
We discuss when to use `std::cout` vs `std::cerr` further in lesson [9.4 -- Detecting and handling errors](https://www.learncpp.com/cpp-tutorial/detecting-and-handling-errors/).

```cpp
int getValue()
{
std::cerr << "getValue() called\n";
```

Tip:
When adding temporary debug statements, it can be helpful to not indent them. This makes them easier to find for removal later.
If you are using clang-format to format your code, it will try to auto-indent these lines. You can suppress the automatic formatting like this:
```cpp
// clang-format off
std::cerr << "main() called\n";
// clang-format on
```

### Debugging tactic #3: Printing values
With some types of bugs, the program may be calculating or passing the wrong value.
We can also output the value of variables (including parameters) or expressions to ensure that they are correct.
```cpp
	int x{ getUserInput() };
std::cerr << "main::x = " << x << '\n';
```

### Why using printing statements to debug isn’t great

While adding debug statements to programs for diagnostic purposes is a common rudimentary technique, and a functional one (especially when a debugger is not available for some reason), it’s not that great for a number of reasons:
1. Debug statements clutter your code.
2. Debug statements clutter the output of your program.
3. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.
4. Debug statements must be removed after you’re done with them, which makes them non-reusable.

We can do better. We’ll explore how in future lessons.

## 3.5 More debugging tactics
In the previous lesson ([3.4 -- Basic debugging tactics](https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/)), we started exploring how to manually debug problems. In that lesson, we offered some criticisms of using statements to print debug text:
1. Debug statements clutter your code.
2. Debug statements clutter the output of your program.
3. Debug statements require modification of your code to both add and to remove, which can introduce new bugs.
4. Debug statements must be removed after you’re done with them, which makes them non-reusable.

We can mitigate some of these issues. In this lesson, we’ll explore some basic techniques for doing so.
### Conditionalizing your debugging code
When you’re done with the debugging statement, you’ll either need to remove them, or comment them out. Then if you want them again later, you’ll have to add them back, or uncomment them.

One way to make it easier to disable and enable debugging throughout your program is to make your debugging statements conditional using preprocessor directives:
```cpp
#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
```
Now we can enable debugging simply by commenting / uncommenting _#define ENABLE_DEBUG_. This allows us to reuse previously added debug statements and then just disable them when we’re done with them, rather than having to actually remove them from the code. If this were a multi-file program, the #define ENABLE_DEBUG would go in a header file that’s included into all code files so we can comment / uncomment the #define in a single location and have it propagate to all code files.

This addresses the issue with having to remove debug statements and the risk in doing so, but at the cost of even more code clutter. Another downside of this approach is that if you make a typo (e.g. misspell “DEBUG”) or forget to include the header into a code file, some or all of the debugging for that file may not be enabled. So although this is better than the unconditionalized version, there’s still room to improve.
### Using a logger
An alternative approach to conditionalized debugging via the preprocessor is to send your debugging information to a log. A **log** is a sequential record of events that have happened, usually time-stamped. The process of generating a log is called **logging**. Typically, logs are written to a file on disk (called a **log file**) so they can be reviewed later. Most applications and operating systems write log files that can be used to help diagnose issues that occur.

Log files have a few advantages. Because the information written to a log file is separated from your program’s output, you can avoid the clutter caused by mingling your normal output and debug output. Log files can also be easily sent to other people for diagnosis -- so if someone using your software has an issue, you can ask them to send you the log file, and it might help give you a clue where the issue is.

C++ contains an output stream named `std::clog` that is intended to be used for writing logging information. However, by default, `std::clog` writes to the standard error stream (the same as `std::cerr`). And while you can redirect it to file instead, this is one area where you’re generally better off using one of the many existing third-party logging tools available. Which one you use is up to you.

For illustrative purposes, we’ll show what outputting to a logger looks like using the [plog](https://github.com/SergiusTheBest/plog) logger. Plog is implemented as a set of header files, so it’s easy to include anywhere you need it, and it’s lightweight and easy to use.
```cpp
#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
	PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger

	PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console
```
Here’s output from the above logger (in the `Logfile.txt` file):
```
2018-12-26 20:03:33.295 DEBUG [4752] [main@19] main() called
2018-12-26 20:03:33.296 DEBUG [4752] [getUserInput@7] getUserInput() called
```
How you include, initialize, and use a logger will vary depending on the specific logger you select.

Note that conditional compilation directives are also not required using this method, as most loggers have a method to reduce/eliminate writing output to the log. This makes the code a lot easier to read, as the conditional compilation lines add a lot of clutter. With plog, logging can be temporarily disabled by changing the init statement to the following:

```cpp
plog::init(plog::none , "Logfile.txt"); // plog::none eliminates writing of most messages, essentially turning logging off
```

We won’t use plog in any future lessons, so you don’t need to worry about learning it.
As an aside…

If you want to compile the above example yourself, or use plog in your own projects, you can follow these instructions to install it:

First, get the latest plog release:

- Visit the [plog](https://github.com/SergiusTheBest/plog) repo.
- Click the green Code button in the top right corner, and choose “Download zip”

Next, unzip the entire archive to `somewhere` on your hard drive.

Finally, for each project, set the `somewhere\plog-master\include\` directory as an `include directory` inside your IDE. Since plog doesn’t have a precompiled library file, you can skip the parts related to precompiled library files.

The log file will generally be created in the same directory as your executable.

Tip: In larger or performance-sensitive projects, faster and more feature-rich loggers may be preferred, such as [spdlog](https://github.com/gabime/spdlog).

## 3.6 Using an integrated debugger: Stepping
When you run your program, execution begins at the top of the _main_ function, and then proceeds sequentially statement by statement, until the program ends. At any point in time while your program is running, the program is keeping track of a lot of things: the value of the variables you’re using, which functions have been called (so that when those functions return, the program will know where to go back to), and the current point of execution within the program (so it knows which statement to execute next). All of this tracked information is called your **program state** (or just _state_, for short).

In previous lessons, we explored various ways to alter your code to help with debugging, including printing diagnostic information or using a logger. These are simple methods for examining the state of a program while it is running. Although these can be effective if used properly, they still have downsides: they require altering your code, which takes time and can introduce new bugs, and they clutter your code, making the existing code harder to understand.

### The debugger

A **debugger** is a computer program that allows the programmer to control how another program executes and examine the program state while that program is running. For example, the programmer can use a debugger to execute a program line by line, examining the value of variables along the way. By comparing the actual value of variables to what is expected, or watching the path of execution through the code, the debugger can help immensely in tracking down semantic (logic) errors.

The power behind the debugger is twofold: the ability to precisely control execution of the program, and the ability to view (and modify, if desired) the program’s state.

Initially, debuggers (such as [gdb](https://en.wikipedia.org/wiki/Gdb)) were separate programs that had command-line interfaces, where the programmer had to type arcane commands to make them work. Later debuggers (such as early versions of Borland’s [turbo debugger](https://en.wikipedia.org/wiki/Turbo_Debugger)) were still separate programs, but supplied a “graphical” front end to make working with them easier. These days, many modern IDEs have an **integrated debugger** -- that is, a debugger that uses the same interface as the code editor, so you can debug using the same environment that you use to write your code (rather than having to switch programs).

While integrated debuggers are highly convenient and recommended for beginners, command line debuggers are well supported and still commonly used in environments that do not support graphical interfaces (e.g. embedded systems).

Nearly all modern debuggers contain the same standard set of basic features -- however, there is little consistency in terms of how the menus to access these features are arranged, and even less consistency in the keyboard shortcuts.

Tip : Don’t neglect learning to use a debugger. As your programs get more complicated, the amount of time you spend learning to use the integrated debugger effectively will pale in comparison to amount of time you save finding and fixing issues.

Warning : Before proceeding with this lesson (and subsequent lessons related to using a debugger), make sure your project is compiled using a debug build configuration `-ggdb`
If you’re compiling your project using a release configuration instead, the functionality of the debugger may not work correctly (e.g. when you try to step into your program, it will just run the program instead).

For VS Code users
To set up debugging, press _Ctrl+Shift+P_ and select “C/C++: Add Debug Configuration”, followed by “C/C++: g++ build and debug active file”. This should create and open the `launch.json` configuration file. Change the “stopAtEntry” to true:  
`"stopAtEntry": true,`
Then open _main.cpp_ and start debugging by pressing _F5_ or by pressing _Ctrl+Shift+P_ and selecting “Debug: Start Debugging and Stop on Entry”.

### Stepping

We’re going to start our exploration of the debugger by first examining some of the debugging tools that allow us to control the way a program executes.
**Stepping** is the name for a set of related debugger features that let us execute (step through) our code statement by statement.
There are a number of related stepping commands that we’ll cover in turn.

### Step into

The **step into** command executes the next statement in the normal execution path of the program, and then pauses execution of the program so we can examine the program’s state using the debugger. If the statement being executed contains a function call, _step into_ causes the program to jump to the top of the function being called, where it will pause.
For VS Code users
In VS Code, the _step into_ command can be accessed via _Run > Step Into_.


Warning : The version of operator<< used for output is implemented as a function. As a result, your IDE may step into the implementation of the operator<< function instead.
If this happens, you’ll see your IDE open a new code file, and the arrow marker will move to the top of a function named operator<< (this is part of the standard library). Close the code file that just opened, then find and execute _step out_ debug command (instructions are below under the “step out” section, if you need help).
```cpp
#ifdef DEBUG
std::cout << std::unitbuf; // enable automatic flushing for std::cout (for debugging)
#endif
```
You’ll need to make sure the *DEBUG* preprocessor macro is defined, either somewhere above this statement, or as part of your compiler settings.

### Step over

Like _step into_, The **step over** command executes the next statement in the normal execution path of the program. However, whereas _step into_ will enter function calls and execute them line by line, _step over_ will execute an entire function without stopping and return control to you after the function has been executed.
For VS Code users : In VS Code, the _step over_ command can be accessed via _Run > Step Over_, or by pressing the _F10_ shortcut key.
The _step over_ command provides a convenient way to skip functions when you are sure they already work or are not interested in debugging them right now.

### Step out
Unlike the other two stepping commands, **Step out** does not just execute the next line of code. Instead, it executes all remaining code in the function currently being executed, and then returns control to you when the function has returned.
For VS Code users : In VS Code, the _step out_ command can be accessed via _Run > Step Out_, or by pressing the _shift+F11_ shortcut combo.

### A step too far
When stepping through a program, you can normally only step forward. It’s very easy to accidentally step past (overstep) the place you wanted to examine.
If you step past your intended destination, the usual thing to do is stop debugging and restart debugging again, being a little more careful not to pass your target this time.

### Step back
Some debuggers (such as Visual Studio Enterprise Edition and [rr](https://github.com/rr-debugger/rr)) have introduced a stepping capability generally referred to as _step back_ or _reverse debugging_. The goal of a _step back_ is to rewind the last step, so you can return the program to a prior state. This can be useful if you overstep, or if you want to re-examine a statement that just executed.

Implementing _step back_ requires a great deal of sophistication on the part of the debugger (because it has to keep track of a separate program state for each step). Because of the complexity, this capability isn’t standardized yet, and varies by debugger. 

## 3.7 Using an integrated debugger: Running and breakpoints
While stepping is useful for examining each individual line of your code in isolation, in a large program, it can take a long time to step through your code to even get to the point where you want to examine in more detail.

Fortunately, modern debuggers provide more tools to help us efficiently debug our programs. In this lesson, we’ll look at some of the debugger features that let us more quickly navigate our code.

### Run to cursor
The first useful command is commonly called _Run to cursor_. This **Run to cursor** command executes the program until execution reaches the statement selected by your cursor. Then it returns control to you so you can debug starting at that point. This makes for an efficient way to start debugging at a particular point in your code, or if already debugging, to move straight to some place you want to examine further.
For VS Code users : In VS Code, the _run to cursor_ command can be accessed while already debugging a program by right clicking a statement in your code and choosing _Run to Cursor_ from the context menu.
### Continue
Once you’re in the middle of a debugging session, you may want to just run the program from that point forward. The easiest way to do this is to use the _continue_ command. The **continue** debug command simply continues running the program as per normal, either until the program terminates, or until something triggers control to return back to you again (such as a breakpoint).
For VS Code users : In VS Code, the _continue_ command can be accessed while already debugging a program via _Run menu > Continue_, or by pressing the _F5_ shortcut key.

### Start
The _continue_ command has a twin brother named _start_. The _start_ command performs the same action as _continue_, just starting from the beginning of the program. It can only be invoked when not already in a debug session.
For VS Code users : In VS Code, the _start_ command can be accessed while not debugging a program via _Run menu > Start Debugging_, or by pressing the _F5_ shortcut key.

### Breakpoints
A **breakpoint** is a special marker that tells the debugger to stop execution of the program at the breakpoint when running in debug mode.
For VS Code users : In VS Code, you can set or remove a breakpoint via _Run menu > Toggle Breakpoint_, or by pressing the _F9_ shortcut key, or by clicking to the left of the line number.
Breakpoints have a couple of advantages over _run to cursor_. First, a breakpoint will cause the debugger to return control to you every time they are encountered (unlike _run to cursor_, which only runs to the cursor once each time it is invoked). Second, you can set a breakpoint and it will persist until you remove it, whereas with _run to cursor_ you have to locate the spot you want to run to each time you invoke the command.

Note that breakpoints placed on lines that are not in the path of execution will not cause the debugger to halt execution of the code.

### Set next statement
There’s one more debugging command that’s used fairly uncommonly, but is still at least worth knowing about, even if you won’t use it very often. The **set next statement** command allows us to change the point of execution to some other statement (sometimes informally called _jumping_). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.
For VS Code users : In VS Code, you can jump the point of execution by right clicking on a statement and choosing _Jump to cursor_ from the context menu. This option is contextual and only occurs while already debugging a program.

This functionality can be useful in several contexts.

In our exploration of basic debugging techniques, we discussed commenting out a function as a way to determine whether that function had a role in causing an issue. This requires modifying our code, and remembering to uncomment the function later. In the debugger, there’s no direct way to skip a function, so if you decide you want to do this, using _set next statement_ to jump over a function call is the easiest way to do so.

Jumping backwards can also be useful if we want to watch a function that just executed run again, so we can see what it is doing.

Warning : The _set next statement_ command will change the point of execution, but will not otherwise change the program state. Your variables will retain whatever values they had before the jump. As a result, jumping may cause your program to produce different values, results, or behaviors than it would otherwise. Use this capability judiciously (especially jumping backwards).

Warning : You should not use _set next statement_ to change the point of execution to a different function. This may result in undefined behavior, and likely a crash.

### “Step back” vs jumping backwards via “Set next statement”

“Step back” rewinds the state of everything, as if you’d never gone past that point in the first place. Any changes to variable values or other program state is undone. This is essentially an “undo” command for stepping.

“Set next statement” when used to jump backwards only changes the point of execution. Any changes to variable values or other program state are not undone.

### Conclusion

You now learned the major ways that you can use an integrated debugger to watch and control how your program executes. While these commands can be useful for diagnosing code flow issues (e.g. to determine if certain functions are or aren’t being called), they are only a portion of the benefit that the integrated debugger brings to the table. In the next lesson, we’ll start exploring additional ways to examine your program’s state, for which you’ll need these commands as a prerequisite. Let’s go!

## 3.8 Using an integrated debugger: Watching variables
The debugger also lets you examine the value of variables as you step through your code, all without having to modify your code.

### Watching variables
**Watching a variable** is the process of inspecting the value of a variable while the program is executing in debug mode.
The easiest way to examine the value of a simple variable is to hover your mouse over the variable x. Some modern debuggers support this method of inspecting simple variables, and it is the most straightforward way to do so. 

### The watch window

Using the mouse hover or QuickWatch methods to inspect variables is fine if you want to know the value of a variable at a particular point in time, but it’s not particularly well suited to watching the value of a variable change as you run the code because you continually have to rehover/reselect the variable.

In order to address this issue, all modern integrated debuggers provide another feature, called a watch window. The **watch window** is a window where you can add variables you would like to continually inspect, and these variables will be updated as you step through your program. The watch window may already be on your screen when you enter debug mode, but if it is not, you can bring it up through your IDE’s window commands (these are typically found in a View or Debug menu).

For VS Code users : In VS Code, the watch window appears in debug mode, docked on the left above the call stack.

Variables that go out of scope (e.g. a local variable inside a function that has already returned to the caller) will stay in your watch window, but will generally either be marked as “not available”, or may show the last known value but grayed out. If the variable returns to scope (e.g. the function is called again), its value will begin showing again. Therefore, it’s fine to leave variables in the watch window, even if they’re out of scope.

Using watches is the best way to watch the value of a variable change over time as you step through your program.

### Setting a breakpoint on watched variables
Some debuggers will allow you to set a breakpoint on a watched variable rather than a line. This will cause the program to stop execution whenever the value of that variable changes.

### The watch window can evaluate expressions too
The watch window will also allow you to evaluate simple expressions e.g. enter _x + 2_.
You can also highlight an expression in your code and then inspect the value of that expression via hover or by adding it to the watch window via the right-click context menu.

Warning : Identifiers in watched expressions will evaluate to their current values. If you want to know what value an expression in your code is actually evaluating to, _run to cursor_ to it first, so that all identifiers have the correct values.

### Local watches
Because inspecting the value of local variables inside a function is common while debugging, many debuggers will offer some way to quickly watch the value of _all_ local variables in scope.
For VS Code users : In VS Code, the value of local variables can be found in the _VARIABLES_ section that appears docked to the left in debug mode. You may need to uncollapse the _Locals_ node.
If you’re just looking to watch the value of a local variable, check the _locals_ window first. It should already be there.

## 3.9 Using an integrated debugger: The call stack
When your program calls a function, you already know that it bookmarks the current location, makes the function call, and then returns. How does it know where to return to? The answer is that it keeps track in the call stack.

The **call stack** is a list of all the active functions that have been called to get to the current point of execution. The call stack includes an entry for each function called, as well as which line of code will be returned to when the function returns. Whenever a new function is called, that function is added to the top of the call stack. When the current function returns to the caller, it is removed from the top of the call stack, and control returns to the function just below it.

The **call stack window** is a debugger window that shows the current call stack. If you don’t see the call stack window, you will need to tell the IDE to show it.

For VS Code users : In VS Code, the call stack window appears in debug mode, docked on the left.

Tip : The line numbers after the function names show the next line to be executed in each function.
Since the top entry on the call stack represents the currently executing function, the line number here shows the next line that will execute when execution resumes. The remaining entries in the call stack represent functions that will be returned to at some point, so the line number for these represent the next statement that will execute after the function is returned to.

The call stack is useful in conjunction with breakpoints, when your breakpoint is hit and you want to know what functions were called to get to that specific point in the code.

### Conclusion

Congratulations, you now know the basics of using an integrated debugger! Using stepping, breakpoints, watches, and the call stack window, you now have the fundamentals to be able to debug almost any problem. Like many things, becoming good at using a debugger takes some practice and some trial and error. But again, we’ll reiterate the point that the time devoted to learning how to use an integrated debugger effectively will be repaid many times over in time saved debugging your programs!

## 3.10 Finding issues before they become problems
When you make a semantic error, that error may or may not be immediately noticeable when you run your program. An issue may lurk undetected in your code for a long time before newly introduced code or changed circumstances cause it to manifest as a program malfunction. The longer an error sits in the code base before it is found, the more likely it is to be hard to find, and something that may have been easy to fix originally turns into a debugging adventure that eats up time and energy.

So what can we do about that?

Don’t make errors

Well, the best thing is to not make errors in the first place. Here’s a list of things that can help avoid making errors:
- Follow best practices.
- Don’t program when tired or frustrated. Take a break and come back later.
- Understand where the common pitfalls are in a language (all those things we warn you not to do).
- Don’t let your functions get too long.
- Prefer using the standard library to writing your own code, when possible.
- Comment your code liberally.
- Start with simple solutions, then layer in complexity incrementally.
- Avoid clever/non-obvious solutions.
- Optimize for readability and maintainability, not performance.

> Everyone knows that debugging is twice as hard as writing a program in the first place. So if you’re as clever as you can be when you write it, how will you ever debug it?
> 
> —Brian Kernighan, “The Elements of Programming Style”

### Refactoring your code

As you add new capabilities to your programs (“behavioral changes”), you will find that some of your functions grow in length. As functions get longer, they get both more complex and harder to understand.

One way to address this is to break a single long function into multiple shorter functions. This process of making structural changes to your code without changing its behavior is called **refactoring**. The goal of refactoring is to make your program less complex by increasing its organization and modularity.

So how long is too long for a function? A function that takes up one vertical screen worth of code is generally regarded as too long -- if you have to scroll to read the whole function, the function’s comprehensibility drops significantly. Ideally, a function should be less than ten lines. Functions that are less than five lines are even better.

Remember that the goal here is to maximize comprehension and maintainability, not to minimize function length -- abandoning best practices or using obscure coding techniques to save a line or two doesn’t do your code any favors.

Key insight : When making changes to your code, make behavioral changes OR structural changes, and then retest for correctness. Making behavioral and structural changes at the same time tends to lead to more errors as well as errors that are harder to find.

### An introduction to defensive programming

Errors can be not only of your own making (e.g. incorrect logic), but also occur when your users use the application in a way that you did not anticipate. For example, if you ask the user to enter an integer, and they enter a letter instead, how does your program behave in such a case? Unless you anticipated this, and added some error handling for this case, probably not very well.

**Defensive programming** is a practice whereby the programmer tries to anticipate all of the ways the software could be misused, either by end-users, or by other developers (including the programmer themselves) using the code. These misuses can often be detected and then mitigated (e.g. by asking a user who entered bad input to try again).

We’ll explore topics related to error handling in future lessons.

### Finding errors fast

Since not making errors is difficult in large programs, the next best thing is to catch errors you do make quickly.
The best way to do this is to program a little bit at a time, and then test your code and make sure it works.
However, there are a few other techniques we can also use.

### An introduction to testing functions

One common way to help uncover issues with your program is to write testing functions to “exercise” the code you’ve written. Here’s a primitive attempt, more for illustrative purposes than anything:
```cpp
void testadd()
{
	std::cout << "This function should print: 2 0 0 -2\n";
	std::cout << add(1, 1) << ' ';
	std::cout << add(-1, 1) << ' ';
	std::cout << add(1, -1) << ' ';
	std::cout << add(-1, -1) << ' ';
}
```
The testadd() function tests the add() function by calling it with different values. If all the values match our expectations, then we can be reasonably confident the function works. Even better, we can keep this function around, and run it any time we change function _add_ to ensure we haven’t accidentally broken it.

This is a primitive form of **unit testing**, which is a software testing method by which small units of source code are tested to determine whether they are correct.

As with logging frameworks, there are many 3rd party unit testing frameworks that can be used. It’s also possible to write your own, though we’ll need more language features at our disposal to do the topic justice. We’ll come back to some of this in a future lesson.

### An introduction to constraints

Constraints-based techniques involve the addition of some extra code (that can be compiled out in a non-debug build, if desired) to check that some set of assumptions or expectations are not violated.

For example, if we were writing a function to calculate the factorial of a number, which expects a non-negative argument, the function could check to make sure the caller passed in a non-negative number before proceeding. If the caller passes in a negative number, then the function could immediately error out rather than producing some indeterminate result, helping ensure the problem is caught immediately.

One common method of doing this is via _assert_ and _static_assert_, which we cover in lesson [9.6 -- Assert and static_assert](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/).

### Shotgunning for general issues

Programmers tend to make certain kinds of common mistakes, and some of those mistakes can be discovered by programs trained to look for them. These programs, generally known as **static analysis tools** (sometimes informally called _linters_) are programs that analyze your source code to identify specific semantic issues (in this context, _static_ means that these tools analyze the source code without executing it). The issues found by static analysis tools may or may not be the cause of any particular problem you are having, but may help point out fragile areas of code or issues that can be problematic in certain circumstances.

You already have one static analysis tool at your disposal -- your compiler! In addition to ensuring your program is syntactically correct, most modern C++ compilers will do some light static analysis to identify some common problems. For example, many compilers will warn you if you try to use a variable that has not been initialized. If you haven’t already, turning up your compiler warning and error levels (see lesson [0.11 -- Configuring your compiler: Warning and error levels](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-warning-and-error-levels/)) can help surface these.

[Many static analysis tools exist](https://en.wikipedia.org/wiki/List_of_tools_for_static_code_analysis#C,_C++), some of which can identify over 300 types of programming errors. On our small academic programs, use of a static analysis tool is optional, but using one may help you find areas where your code is non-compliant with best practices. On large programs, use of a static analysis tool is highly recommended, as it can surface tens or hundreds of potential issues.

Best practice :  Use a static analysis tool on your programs to help find areas where your code is non-compliant with best practices.
Tip :
Some commonly recommended static analysis tools include:
Free:
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [cpplint](https://github.com/cpplint/cpplint)
- [cppcheck](https://cppcheck.sourceforge.io/) (already integrated into Code::Blocks)
- [SonarLint](https://www.sonarsource.com/open-source-editions/)
Most of these have extensions that allow them to integrate into your IDE. For example, [Clang Power Tools extension](https://marketplace.visualstudio.com/items?itemName=caphyon.ClangPowerTools).

## 3.x Chapter 3 summary and quiz
A **syntax error** is an error that occurs when you write a statement that is not valid according to the grammar of the C++ language. The compiler will catch these.

A **semantic error** occurs when a statement is syntactically valid, but does not do what the programmer intended.

The process of finding and removing errors from a program is called **debugging**.

We can use a five step process to approach debugging:

1. Find the root cause.
2. Understand the problem.
3. Determine a fix.
4. Repair the issue.
5. Retest.

Finding an error is usually the hardest part of debugging.

**Static analysis tools** are tools that analyze your code and look for semantic issues that may indicate problems with your code.

Being able to reliably reproduce an issue is the first and most important step in debugging.

There are a number of tactics we can use to help find issues:

- Commenting out code.
- Using output statements to validate your code flow.
- Printing values.

When using print statements to debug, use _std::cerr_ instead of _std::cout_. But even better, avoid debugging via print statements.

A **log file** is a file that records events that occur in a program. The process of writing information to a log file is called **logging**.

The process of restructuring your code without changing how it behaves is called **refactoring**. This is typically done to make your program more organized, modular, or performant.

**Unit testing** is a software testing method by which small units of source code are tested to determine whether they are correct.

**Defensive programming** is a technique whereby the programmer tries to anticipate all of the ways the software could be misused. These misuses can often be detected and mitigated.

All of the information tracked in a program (variable values, which functions have been called, the current point of execution) is part of the **program state**.

A **debugger** is a tool that allows the programmer to control how a program executes and examine the program state while the program is running. An **integrated debugger** is a debugger that integrates into the code editor.

**Stepping** is the name for a set of related debugging features that allow you to step through your code statement by statement.

**Step into** executes the next statement in the normal execution path of the program, and then pauses execution. If the statement contains a function call, _step into_ causes the program to jump to the top of the function being called.

**Step over** executes the next statement in the normal execution path of the program, and then pauses execution. If the statement contains a function call, _step over_ executes the function and returns control to you after the function has been executed.

**Step out** executes all remaining code in the function currently being executed and then returns control to you when the function has returned.

**Run to cursor** executes the program until execution reaches the statement selected by your mouse cursor.

**Continue** runs the program, until the program terminates or a breakpoint is hit. **Start** is the same as continue, just from the beginning of the program.

A **breakpoint** is a special marker that tells the debugger to stop execution of the program when the breakpoint is reached.

The **set next statement** command allows us to change the point of execution to some other statement (sometimes informally called jumping). This can be used to jump the point of execution forwards and skip some code that would otherwise execute, or backwards and have something that already executed run again.

**Watching a variable** allows you to inspect the value of a variable while the program is executing in debug mode. The **watch window** allows you to examine the value of variables or expressions.

The **call stack** is a list of all the active functions that have been executed to get to the current point of execution. The **call stack window** is a debugger window that shows the call stack.