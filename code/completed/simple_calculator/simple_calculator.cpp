#include <iostream>

#include "printer.hpp"

int main() // NOLINT(bugprone-exception-escape)
{
    double num1{}, num2{};
    char operation{};
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the operation: ";
    std::cin >> operation;
    std::cout << "Enter the second number: ";
    std::cin >> num2;
    return print_result(num1, num2, operation);
}
