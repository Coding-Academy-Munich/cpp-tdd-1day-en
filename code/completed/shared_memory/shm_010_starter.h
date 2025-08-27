// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_010_STARTER_H
#define COMPLETED_SHARED_MEMORY_SHM_010_STARTER_H

#include <string_view>

namespace shm010 {
int run_parent(std::string_view program);
int run_child(std::string_view arg);
} // namespace shm010

#endif // COMPLETED_SHARED_MEMORY_SHM_010_STARTER_H
