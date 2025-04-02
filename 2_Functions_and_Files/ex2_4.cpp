#include <fmt/base.h>
#include <iostream>
int doubleNumber(int x)
{
    return x*2;
}

int main(){
    int y {};
    std::cin >> y;
    fmt::println("{}", doubleNumber(y));
    return 0;
}