// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_050_BAD_POINTER_H
#define COMPLETED_SHARED_MEMORY_SHM_050_BAD_POINTER_H

#include <string_view>

namespace shm050 {
int run_parent(std::string_view program);
int run_child(std::string_view arg);
} // namespace shm050

#endif // COMPLETED_SHARED_MEMORY_SHM_050_BAD_POINTER_H
