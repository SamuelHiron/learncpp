#include <fmt/core.h>
template <typename T>
T add(T x, T y)
{
    return x + y;
}
template <typename T>
T mult(T x, int y)
{
    return x * y;
}
template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

auto subcpp20(auto x, auto y)
{
    return x - y;
}


int main()
{
    fmt::println("add(2, 3) = {}\nadd(1.2, 3.4) = {}", add(2, 3), add(1.2, 3.4));
    fmt::println("mult(2, 3) = {}\nmult(1.2, 3) = {}", mult(2, 3), mult(1.2, 3));
    fmt::println("sub(3, 2) = {}\nsub(3.5, 2) = {}\nsub(1, 4.5) = {}", sub(3, 2), sub(3.5, 2), sub(1, 4.5));
    return 0;
}
