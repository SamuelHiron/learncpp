#include <fmt/base.h>
#include <iostream>

int main(){
    int k;
    fmt::println("k is unitialiazed, the value is {}", k); //value is unknown and changing from one execution ex 32522
    int x{}, y{}, z{};
    fmt::print("Enter three numbers:");
    std::cin >> x >> y >> z;
    fmt::println("\nYou entered {}, {}, and {}.", x, y, z);
    return 0;
}