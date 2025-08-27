// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "window.h"
#include "window_builder.h"
#include <iostream>

using namespace window;

int main()
{
    constexpr Window window = WindowBuilder()
                                  .width(800)
                                  .height(600)
                                  .x(100)
                                  .y(100)
                                  .visible(true)
                                  .active(true)
                                  .resizable(true)
                                  .fullscreen(false)
                                  .build();
    std::cout << window << std::endl;
    return 0;
}