#include <fmt/core.h>

int main()
{
    char letter = 'a';
    while(letter != 'z')
    {
        fmt::println("{} = {}", letter, static_cast<int>(letter) );
        ++letter;
    }
    fmt::println("{} = {}", letter, static_cast<int>(letter) );
}
