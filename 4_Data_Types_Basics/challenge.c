#include <fmt/base.h>
#include <iostream>

void outputHeightBall(int tower_height, int seconds)
{
    double ball_height = tower_height - 9.8*seconds*seconds/2.0;
    if (ball_height>0)
        fmt::println("At {} seconds, the ball is at height: {} meters", seconds, ball_height) ;
    else
        fmt::println("At {} seconds, the ball is on the ground", seconds);
}

int main()
{
    fmt::println("Enter the height of the tower in meters : ");
    int tower_height{};
    std::cin>>tower_height;
    outputHeightBall(tower_height, 0);
    outputHeightBall(tower_height, 1);
    outputHeightBall(tower_height, 2);
    outputHeightBall(tower_height, 3);
    outputHeightBall(tower_height, 4);
    outputHeightBall(tower_height, 5);
    return 0;
}