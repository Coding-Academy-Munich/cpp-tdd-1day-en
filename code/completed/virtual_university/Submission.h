// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_VIRTUAL_UNIVERSITY_SUBMISSION_H
#define COMPLETED_VIRTUAL_UNIVERSITY_SUBMISSION_H

#include <string>

using namespace std::string_literals;

class Assignment;
class Professor;
class Student;

enum class Grade
{
    A,
    B,
    C,
    D,
    F,
    None
};

std::string to_string(Grade grade);

class Submission
{
private:
    const Student* student_;
    const Assignment* assignment_;
    std::string data_;
    const Professor* graded_by_;
    Grade grade_;

public:
    Submission(
        const Student& student, const Assignment& assignment, std::string data = ""s,
        Professor* graded_by = nullptr, Grade grade = Grade::None
    );

    [[nodiscard]] const Student& get_student() const;
    [[nodiscard]] const Assignment& get_assignment() const;
    [[nodiscard]] const std::string& get_data() const;
    [[nodiscard]] const Professor* get_grading_professor() const;
    [[nodiscard]] Grade get_grade() const;

    void assign_grade(const Professor* professor, Grade grade);
};

#endif // COMPLETED_VIRTUAL_UNIVERSITY_SUBMISSION_H
