// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

#include "salaries.h"

using namespace salaries;

void pay_some_salaries()
{
    std::vector<double> all_salaries{};
    const double tax_1{process_salary(3, 240.0, "Joe", all_salaries)};
    const double tax_2{process_salary(5, 240.0, "Jack", all_salaries)};
    const double tax_3{process_salary(6, 260.0, "Jill", all_salaries)};
    const double tax_4{process_salary(6, 800.0, "Jane", all_salaries)};
    std::cout << tax_1 << ", " << tax_2 << ", " << tax_3 << ", " << tax_4 << "\n";
}

void show_compute_day_of_week_name()
{
    std::array<int, 7> valid_day_numbers{};
    std::iota(begin(valid_day_numbers), end(valid_day_numbers), 1);
    std::for_each(begin(valid_day_numbers), end(valid_day_numbers), [](int day) {
        std::cout << "Day " << day << ": " << compute_day_of_week_name(day) << "\n";
    });
    try
    {
        compute_day_of_week_name(0);
    }
    catch (const std::domain_error& err)
    {
        std::cout << "Caught expected error for day 0: " << err.what() << std::endl;
    }
    try
    {
        compute_day_of_week_name(8);
    }
    catch (const std::domain_error& err)
    {
        std::cout << "Caught expected error for day 8: " << err.what() << std::endl;
    }
}

void show_compute_tax_rate()
{
    for (const double salary : {400.0, 500.0, 600.0, 1000.0, 1500.0, 2000.0, 3000.0})
    {
        std::cout << "Salary: " << salary << ", tax rate: " << compute_tax_rate(salary)
                  << "\n";
    }
}

int main()
{
    try
    {
        std::cout << "Salaries completed\n\n";
        pay_some_salaries();

        std::cout << "\nDay of week computation\n";
        show_compute_day_of_week_name();

        std::cout << "\nTax rate computation\n";
        show_compute_tax_rate();
    }
    catch (...)
    {
        std::printf("An error occurred!");
    }
}