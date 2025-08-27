// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_TASK_H
#define LIB_TASK_H
#include <string>

namespace tlc_sk
{

    struct Task
    {
        std::string description{};
        bool completed{};
    };

} // namespace tlc_sk

#endif // LIB_TASK_H
