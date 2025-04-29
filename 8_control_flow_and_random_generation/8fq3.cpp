#include "Random.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <iostream>


void hilo(int tries_left, int nb_to_find)
{
    int guess;
    for(int i = 1; i<=tries_left; ++i)
    {
        fmt::println("Guess #{}: ", i);
        std::cin >> guess;
        if(guess<nb_to_find)
            fmt::println("Your guess is too low.");
        else if(guess>nb_to_find)
            fmt::println("Tour guess is too high.");
        else{
            fmt::println("Correct ! You win !");
            return;
        }
    }
    fmt::println("Sorry, you lose. The correct number was {}", nb_to_find);
}

int main()
{
    char y_or_n = 'y';
    int nb_of_guess = 7;
    int lower_bound = 0;
    int upper_bound = 10;
    
    while(y_or_n != 'n')
    {
        if(y_or_n == 'y')
        {
            int nb_to_find = Random::get(lower_bound,upper_bound);
            fmt::println("Let's play a game. I'm thinking of a number between {} and {}. You have {} tries to guess what it is.",lower_bound, upper_bound, nb_of_guess);
            hilo(nb_of_guess, nb_to_find);
        }
        if(y_or_n == 'c')
        {
            fmt::println("nb_of_guess = ");
            std::cin >> nb_of_guess;
            fmt::println("lower_bound = ");
            std::cin >> lower_bound; 
            fmt::println("upper_bound = ");
            std::cin >> upper_bound; 
        }    
        fmt::println("Would you like to play again (y/n) or change parameters(c)?");

        std::cin >> y_or_n;
       
    }    
    fmt::println("Thank you for playing");
    return 0;
}