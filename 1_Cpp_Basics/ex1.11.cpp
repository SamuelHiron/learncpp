#include <fmt/base.h>
#include <iostream>

int main() 
{
    fmt::print("Enter an integer: ");
    int x {};
    std::cin >> x;
    fmt::println("Double {} is: {}", x, x*2);
    fmt::println("Triple {} is: {}", x, 3*x);
}