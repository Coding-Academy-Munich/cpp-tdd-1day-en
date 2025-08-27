// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_VIRTUAL_UNIVERSITY_STUDENT_H
#define COMPLETED_VIRTUAL_UNIVERSITY_STUDENT_H

#include "Lecture.h"
#include "Submission.h"

#include <string>
#include <vector>

class University;

class Student
{
public:
    Student(std::string name, University& university);

    [[nodiscard]] const std::string& get_name() const;

    [[nodiscard]] const University& get_university() const;
    [[nodiscard]] University& get_university();
    void set_university(University& university);

    void submit_assignment(
        const std::string& lecture_name, const std::string& assignment_name,
        const std::string& data
    );

    std::vector<Submission>& get_submissions();
    const Submission& get_submission(const std::string& assignment_name) const;

private:
    friend void Lecture::submit_assignment(
        Student& student, const std::string& assignment_name,
        const std::string& basic_string
    );
    void add_submission(const Submission& submission);

    std::string name_;
    University* university_{};
    std::vector<Submission> submissions_;
};

#endif // COMPLETED_VIRTUAL_UNIVERSITY_STUDENT_H
