// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_VIRTUAL_UNIVERSITY_ASSIGNMENT_H
#define COMPLETED_VIRTUAL_UNIVERSITY_ASSIGNMENT_H

#include <string>

class Lecture;

class Assignment
{
public:
    Assignment(std::string name, std::string due_date);

    [[nodiscard]] const std::string& get_name() const;
    [[nodiscard]] const std::string& get_due_date() const;

private:
    std::string name_;
    std::string due_date_;
};

#endif // COMPLETED_VIRTUAL_UNIVERSITY_ASSIGNMENT_H
