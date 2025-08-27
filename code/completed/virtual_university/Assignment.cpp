// Copyright 2024, Dr. Matthias Hölzl.

#include "Assignment.h"

#include <utility>

Assignment::Assignment(std::string name, std::string due_date)
    : name_{std::move(name)}, due_date_{std::move(due_date)}
{}

const std::string& Assignment::get_name() const { return name_; }

const std::string& Assignment::get_due_date() const { return due_date_; }
