#include "Random.h"
#include <fmt/base.h>
#include <fmt/core.h>
#include <ios>
#include <iostream>

// BEGIN to make sure we have proper input
#include <cstdlib> // for std::exit
#include <limits> // for std:::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//return true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    //Check for failed extraction
    if(!std::cin) // if the previous extraction failed
    {
        if(std::cin.eof()) // if the stream was closed
        {
            std::exit(0); // shut the program now
        }
 
        //Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

   return false;
}

int getInt(int lower_bound, int upper_bound)
{
    while(true)//Loop until user enters a valid input
    {
        int x;
        std::cin >> x;
        if(clearFailedExtraction() || x < lower_bound || x > upper_bound)
        {
            fmt::println("Oops, that input is invalid.  Please try again. It should be a number between {} and {}",lower_bound, upper_bound);
            continue;
        }

        ignoreLine(); //Remove any extraneous input
        return x;
    }
}

// END to make sure we have proper input



void hilo(int tries_left, int nb_to_find, int lower_bound, int upper_bound)
{
    int guess;
    for(int i = 1; i<=tries_left; ++i)
    {
        fmt::println("Guess #{}: ", i);
        guess = getInt(lower_bound, upper_bound);
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
            hilo(nb_of_guess, nb_to_find, lower_bound, upper_bound);
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