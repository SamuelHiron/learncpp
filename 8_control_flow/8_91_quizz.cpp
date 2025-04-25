
#include <fmt/base.h>
#include <fmt/core.h>

int sumTo(int value)
{
    int sum = 0;
    for(int i = 1; i<=value; i+=1)
    {
        sum += i;
    }
    return sum;
}

void fizzbuzz(int value)
{
    for(int i = 1; i<= value; ++i)
    {
        bool print_nb = true;
        if(0 == i%3)
        {
            fmt::print("fizz");
            print_nb = false;
        }
        if(0==i%5)        
        { 
            fmt::print("buzz");
            print_nb = false;
        }
        if(0 == i%7)        
        {
            fmt::print("pop");
            print_nb = false;
        }
        if(print_nb)
            fmt::print("{}", i);
        fmt::println("");
    }
}

int main()
{
    //q1
    for(int i=0; i<=20; i+=2)
    {
        fmt::print("{} ", i);
    }
    fmt::println("");

    //q2
    fmt::println("sumTo(5) = {}", sumTo(5));

    //q4 q5
    fizzbuzz(15);
    return 0;

}
