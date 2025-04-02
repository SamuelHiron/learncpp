#include <fmt/base.h>
#include <iostream>

int readNumber(){
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x){
    fmt::println("{}", x);
}