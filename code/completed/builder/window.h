// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_BUILDER_WINDOW_H
#define COMPLETED_BUILDER_WINDOW_H

#include <ostream>

namespace window
{

struct Window
{
    constexpr Window(
        int width, int height, int x, int y, bool visible, bool active, bool resizable,
        bool fullscreen
    )
        : width{width},
          height{height},
          x{x},
          y{y},
          visible{visible},
          active{active},
          resizable{resizable},
          fullscreen{fullscreen}
    {}

    int width;
    int height;
    int x;
    int y;
    bool visible;
    bool active;
    bool resizable;
    bool fullscreen;
};

std::ostream& operator<<(std::ostream& os, const Window& window);

} // namespace window

#endif // COMPLETED_BUILDER_WINDOW_H
