// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "window.h"
#include "window_builder.h"
#include <catch2/catch_test_macros.hpp>

using namespace window;

TEST_CASE ("Window")
{
    SECTION ("Build using constructor")
    {
        Window unit{800, 600, 100, 100, true, true, true, false};
        CHECK(unit.width == 800);
        CHECK(unit.height == 600);
        CHECK(unit.x == 100);
        CHECK(unit.y == 100);
        CHECK(unit.visible);
        CHECK(unit.active);
        CHECK(unit.resizable);
        CHECK_FALSE(unit.fullscreen);
    }

    SECTION ("Build using builder with default values")
    {
        Window unit = WindowBuilder().build();
        CHECK(unit.width == 800);
        CHECK(unit.height == 600);
        CHECK(unit.x == 0);
        CHECK(unit.y == 0);
        CHECK(unit.visible);
        CHECK(unit.active);
        CHECK(unit.resizable);
        CHECK_FALSE(unit.fullscreen);
    }

    SECTION ("Build using builder")
    {
        Window unit = WindowBuilder()
                          .width(1024)
                          .height(768)
                          .x(200)
                          .y(300)
                          .visible(false)
                          .active(false)
                          .resizable(false)
                          .fullscreen(true)
                          .build();
        CHECK(unit.width == 1024);
        CHECK(unit.height == 768);
        CHECK(unit.x == 200);
        CHECK(unit.y == 300);
        CHECK_FALSE(unit.visible);
        CHECK_FALSE(unit.active);
        CHECK_FALSE(unit.resizable);
        CHECK(unit.fullscreen);
    }

    SECTION ("Build constexpr using builder")
    {
        constexpr Window unit = WindowBuilder()
                                    .width(1024)
                                    .height(768)
                                    .x(200)
                                    .y(300)
                                    .visible(false)
                                    .active(false)
                                    .resizable(false)
                                    .fullscreen(true)
                                    .build();
        CHECK(unit.width == 1024);
        CHECK(unit.height == 768);
        CHECK(unit.x == 200);
        CHECK(unit.y == 300);
        CHECK_FALSE(unit.visible);
        CHECK_FALSE(unit.active);
        CHECK_FALSE(unit.resizable);
        CHECK(unit.fullscreen);
    }
}
