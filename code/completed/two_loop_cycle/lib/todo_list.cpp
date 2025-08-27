// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include "todo_list.h"

namespace tlc_sk
{

    const std::vector<Task>& TodoList::get_tasks() const
    {
        return tasks_;
    }

    void TodoList::add_task(std::string_view task_title)
    {
        tasks_.push_back(Task{std::string{task_title}});
    }

    void TodoList::mark_as_complete(const std::string& description)
    {
        auto task_it =
            std::ranges::find_if(tasks_, [&](const Task& task)
                                 { return task.description == description; });
        if (task_it != tasks_.end())
        {
            task_it->completed = true;
        }
    }
} // namespace tlc_sk
