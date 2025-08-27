// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_TODO_LIST_H
#define LIB_TODO_LIST_H

#include <vector>
#include "task.h"

namespace tlc_sk
{
    class TodoList
    {
    public:
        const std::vector<Task>& get_tasks() const;
        void add_task(std::string_view task_title);
        void mark_as_complete(const std::string& description);

    private:
        std::vector<Task> tasks_;
    };
} // namespace tlc_sk
#endif // LIB_TODO_LIST_H
