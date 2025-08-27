// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "window.h"

namespace window
{

std::ostream& operator<<(std::ostream& os, const Window& window)
{
    os << "Window(" << window.width << ", " << window.height << ", " << window.x << ", "
       << window.y << ", " << window.visible << ", " << window.active << ", "
       << window.resizable << ", " << window.fullscreen << ")";
    return os;
}
} // namespace window