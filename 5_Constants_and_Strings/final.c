#include <fmt/base.h>
#include <iostream>
#include <string>
#include <string_view>

std::string getName(int nb)
{
    fmt::println("Enter the name of person #{}: ", nb);
    std::string name{};
    std::getline(std::cin >> std::ws, name);
    return name;
}

int getAge(std::string_view person)
{
    fmt::println("Enter the age of {}: ", person);
    int age{};
    std::cin >> age;
    return age;
}

int main()
{
    int nb=1;
    const std::string person1{getName(nb)};
    const int age1{getAge(person1)};
    nb++;
    const std::string person2{getName(nb)};
    const int age2{getAge(person2)};
    if(age1>age2)
        fmt::println("{} (age {}) is older than {} (age{}).", person1, age1, person2, age2);
    else if(age2>age1)
        fmt::println("{} (age {}) is older than {} (age{}).", person2, age2, person1, age1);
    else
        fmt::println("{} (age {}) has the same age as {} (age{}).", person1, age1, person2, age2);
    return 0;
}