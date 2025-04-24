#include <iostream>
#include <fmt/core.h>


int main()
{
    int smaller{};
    fmt::println("Enter an integer: ");
    std::cin >> smaller;
    int larger{};
    fmt::println("Enter a larger integer: ");
    std::cin >> larger;
    if(smaller>larger){
        fmt::println("Swapping the values");
        int swap = larger;
        larger = smaller;
        smaller = swap;
    }
    fmt::println("The smaller value is {}", smaller);
    fmt::println("The larger value is {}", larger);

    return 0;
}