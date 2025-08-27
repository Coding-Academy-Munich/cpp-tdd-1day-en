// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_VIRTUAL_UNIVERSITY_TEACHER_H
#define COMPLETED_VIRTUAL_UNIVERSITY_TEACHER_H

#include "University.h"
#include <string>
#include <vector>

class Lecture;
class University;

class Professor
{
public:
    Professor(std::string name, University& university);

    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] const University& get_university() const;
    void set_university(University& university);

    [[nodiscard]] std::vector<Lecture*> get_lectures() const;
    [[nodiscard]] const Lecture& get_lecture(const std::string& course_name) const;
    [[nodiscard]] Lecture& get_lecture(const std::string& course_name);

    void create_assignment(
        const std::string& lecture_name, const std::string& assignment_name,
        const std::string& due_date
    );
    void grade_submission(Submission& submission, Grade grade) const;

private:
    std::string name_;
    University* university_{};
};

bool operator==(const Professor& lhs, const Professor& rhs);
bool operator!=(const Professor& lhs, const Professor& rhs);

#endif // COMPLETED_VIRTUAL_UNIVERSITY_TEACHER_H
