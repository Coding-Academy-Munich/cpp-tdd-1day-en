// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>
#include <vector>

#include "salaries_sk.h"

using namespace salaries_sk;

void pay_some_salaries()
{
    std::vector<double> all_salaries{};
    const double tax_1{handle_money_stuff(3, 240.0, "Joe", all_salaries)};
    const double tax_2{handle_money_stuff(5, 240.0, "Jack", all_salaries)};
    const double tax_3{handle_money_stuff(6, 260.0, "Jill", all_salaries)};
    const double tax_4{handle_money_stuff(6, 800.0, "Jane", all_salaries)};
    std::cout << "Taxes:" << tax_1 << ", " << tax_2 << ", " << tax_3 << ", " << tax_4
              << "\n";
}

int main()
{
    std::cout << "Salaries original\n\n";
    pay_some_salaries();
}
