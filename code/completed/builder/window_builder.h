// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_BUILDER_WINDOW_BUILDER_H
#define COMPLETED_BUILDER_WINDOW_BUILDER_H

#include "window.h"

namespace window
{

class WindowBuilder
{
public:
    constexpr WindowBuilder() = default;

    constexpr Window build()
    {
        return Window(
            this->width_, this->height_, this->x_, this->y_, this->visible_, this->active_,
            this->resizable_, this->fullscreen_
        );
    }

    constexpr WindowBuilder& width(int width)
    {
        this->width_ = width;
        return *this;
    }
    constexpr WindowBuilder& height(int height)
    {
        this->height_ = height;
        return *this;
    }
    constexpr WindowBuilder& x(int x)
    {
        this->x_ = x;
        return *this;
    }
    constexpr WindowBuilder& y(int y)
    {
        this->y_ = y;
        return *this;
    }
    constexpr WindowBuilder& visible(bool visible)
    {
        this->visible_ = visible;
        return *this;
    }
    constexpr WindowBuilder& active(bool active)
    {
        this->active_ = active;
        return *this;
    }
    constexpr WindowBuilder& resizable(bool resizable)
    {
        this->resizable_ = resizable;
        return *this;
    }
    constexpr WindowBuilder& fullscreen(bool fullscreen)
    {
        this->fullscreen_ = fullscreen;
        return *this;
    }

private:
    int width_ = 800;
    int height_ = 600;
    int x_ = 0;
    int y_ = 0;
    bool visible_ = true;
    bool active_ = true;
    bool resizable_ = true;
    bool fullscreen_ = false;
};

} // namespace window

#endif // COMPLETED_BUILDER_WINDOW_BUILDER_H
