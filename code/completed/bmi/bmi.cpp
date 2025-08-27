#include <iostream>

int main()
{
    double weight{}, height{};
    std::cout << "Enter your weight in kg: ";
    std::cin >> weight;
    std::cout << "Enter your height in m: ";
    std::cin >> height;
    double bmi = weight / (height * height);
    std::cout << "Your BMI is: " << bmi << std::endl;
    return 0;
}