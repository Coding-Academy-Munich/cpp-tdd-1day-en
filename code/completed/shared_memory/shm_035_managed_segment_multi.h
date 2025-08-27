// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_SHARED_MEMORY_SHM_035_MANAGED_SEGMENT_MULTI_H
#define COMPLETED_SHARED_MEMORY_SHM_035_MANAGED_SEGMENT_MULTI_H

#include <string_view>

namespace shm035 {
int run_parent(std::string_view program);
int run_child(std::string_view char_handle_str, std::string_view double_handle_str);
} // namespace shm035

#endif // COMPLETED_SHARED_MEMORY_SHM_035_MANAGED_SEGMENT_MULTI_H
