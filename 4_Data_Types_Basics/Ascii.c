#include <iostream>
#include <fmt/base.h>

int main()
{
    char x{};
    std::cin >> x;
    fmt::println("You entered '{}', which has ASCII code {}.", x, static_cast<int>(x) );
    return 0;
}