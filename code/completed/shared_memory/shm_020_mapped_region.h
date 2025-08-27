// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_020_MAPPED_REGION_H
#define COMPLETED_SHARED_MEMORY_SHM_020_MAPPED_REGION_H

#include <string_view>

namespace shm020 {
int run_parent(std::string_view program);
int run_child(std::string_view arg);
} // namespace shm020

#endif // COMPLETED_SHARED_MEMORY_SHM_020_MAPPED_REGION_H
