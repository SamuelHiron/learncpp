#include <fmt/base.h>
#include <fmt/core.h>

int main()
{
    //q3
    int outer=5;
    while(outer != 0)
    {
        int inner = outer;
        while(0!=inner)
        {
            fmt::print("{} ", inner);
            --inner;
        }
        fmt::println("");
        --outer;
    }

    fmt::println("");

    //q4
    int count = 1;
    while(count != 6)
    {
        int blanc = 5 - count;
        int nb = count;
        while(blanc!=0)
        {
            fmt::print("  ");
            --blanc;
        }
        while(nb!=0)
        {
            fmt::print("{} ", nb);
            --nb;
        }
        fmt::println("");
        ++count;
    }

    fmt::println("");
    
    
    
    return 0;
}