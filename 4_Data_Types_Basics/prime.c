#include <fmt/base.h>
#include <iostream>

int main()
{
    int x{};
    fmt::println("Enter a number between 0 and 9");
    std::cin >> x;
    if (x <0 || x >9)
        fmt::println("Between 0 and 9");
    else if (x==2 || x==3 || x==5 || x==5)
        fmt::println("{} is prime !", x);
    else
        fmt::println("{} NOT prime", x);
    return 0;
}