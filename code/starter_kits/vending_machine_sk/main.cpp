// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>


#include "chicago/vending_machine.h"
#include "london/vending_machine.h"

int main()
{
    std::cout << "Isolation styles: " << chicago_vending::isolation() << ", "
              << london_vending::isolation() << '\n';
}
