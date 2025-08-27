// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_060_OFFSET_POINTER_H
#define COMPLETED_SHARED_MEMORY_SHM_060_OFFSET_POINTER_H

#include <string_view>

namespace shm060 {
int run_parent(std::string_view program);
int run_child(std::string_view arg);
} // namespace shm060

#endif // COMPLETED_SHARED_MEMORY_SHM_060_OFFSET_POINTER_H
