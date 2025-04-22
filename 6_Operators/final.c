#include <iostream>
#include <string_view>

// Write the function getQuantityPhrase() here
constexpr std::string_view getQuantityPhrase(int num)
{
    if(num < 0)
        return "negative";
    if(0 == num)
        return "no";
    if(1 == num)
        return "a single";
    if(2 == num)
        return "a couple of";
    if(3 == num)
        return "a few";
    //>3
    return "many";

}
// Write the function getApplesPluralized() here
constexpr std::string_view getApplesPluralized(int num)
{
    return (num == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}