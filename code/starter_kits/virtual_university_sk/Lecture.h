// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_VIRTUAL_UNIVERSITY_COURSE_H
#define COMPLETED_VIRTUAL_UNIVERSITY_COURSE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Assignment.h"
#include "Submission.h"

class Student;

class Lecture
{
public:
    Lecture(std::string name, Professor& professor);
    [[nodiscard]] const std::string& get_name() const;
    [[nodiscard]] const Professor& get_professor() const;

    void add_assignment(const std::string& name, const std::string& due_date);

    std::vector<Assignment>& get_assignments();
    [[nodiscard]] const std::vector<Assignment>& get_assignments() const;

    void add_submission(const Submission& submission);

    [[nodiscard]] std::vector<Submission>& get_submissions_for(const Assignment& assignment
    );

    Assignment& get_assignment(const std::string& name);

    void submit_assignment(
        Student& student, const std::string& assignment_name,
        const std::string& basic_string
    );

    std::string get_info() const;

private:
    std::string name_;
    Professor* professor_{};
    std::vector<Assignment> assignments_;
    std::unordered_map<const Assignment*, std::vector<Submission>> submissions_;
};

#endif // COMPLETED_VIRTUAL_UNIVERSITY_COURSE_H
