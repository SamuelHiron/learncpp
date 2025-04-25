#include <fmt/core.h>
#include <iostream>

int calculate(int x, int y, char symb)
{
    switch(symb)
    {
    case '*':
        return x*y;
    case '/':
        return x/y;
    case '+':
        return x+y;
    case '-':
        return x-y;
    case '%':
        return x%y;
    default:
        fmt::println(stderr, "Error wrong symbol not : * - + / or %");
        return 0;
    }
}
int main()
{
    while(true)
    {
        char continue_game{};
        fmt::println("\nWanna stop enter: n\nContinue enter: y");
        std::cin >> continue_game;
        fmt::println("");
        if(continue_game=='n') break;

        int x{},y{};
        char symb{};
        fmt::println("Enter an integer");
        std::cin >> x;
        fmt::println("Enter an auther integer");
        std::cin >> y;
        fmt::println("Enter a symb: either * - + / or %");
        std::cin >> symb;
        int result = calculate(x, y, symb);
        fmt::println("{} {} {} = {}", x, symb, y, result);
    }    
    return 0;   
}