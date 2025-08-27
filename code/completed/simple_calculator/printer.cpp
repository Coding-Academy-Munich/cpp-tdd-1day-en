#include <iostream>

#include "printer.hpp"

int print_result(double num1, double num2, char operation)
{
    double result{};
    switch (operation) {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/': result = num1 / num2; break;
    default: std::cerr << "Invalid operation"; return 1;
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}
