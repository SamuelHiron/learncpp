#include <iostream>

double getDouble()
{
    std::cout << "Enter a double value: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter +, -, *, or /: ";
    char operation{};
    std::cin >> operation;
    return operation;
}

void printResult(double x, char operation, double y)
{
    double result{};

    if (operation == '+')
        result = x + y;
    else if (operation == '-')
        result = x - y;
    else if (operation == '*')
        result = x * y;
    else if (operation == '/')
        result = x / y;
    else        // if the user did not pass in a supported operation
        return; // early return

    std::cout << x << ' ' << operation << ' ' << y << " is " << result << '\n';
}

int main()
{
    double x { getDouble() };
    double y { getDouble() };

    char operation { getOperator() };

    printResult(x, operation, y);

    return 0;
}