#include <iostream>
#include <fmt/base.h>
#include <string>



int main()
{
    fmt::println("Enter your full name: ");
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    fmt::println("Enter your age:");
    int age{};
    std::cin >> age;
    fmt::println("Your age + length of name is: {}", age+static_cast<int>(name.length()));
    return 0;
}