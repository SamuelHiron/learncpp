#include <iostream>
#include <fmt/core.h>

constexpr bool isEven(int x)
{   
    return x%2==0;
}

int main()
{ 
    fmt::println("Enter an integer: ");
    int x{};
    std::cin >> x;
    if(isEven(x))
        fmt::println("{} is even", x);
    else
        fmt::println("{} is odd", x);
    
    for(int i=0; i<4;++i)
    {
        fmt::println("{}",i);
    }
    return 0;
}