// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "Submission.h"
#include "Assignment.h"
#include "Professor.h"
#include "Student.h"

#include <utility>

std::string to_string(Grade grade)
{
    switch (grade)
    {
    case Grade::A:
        return "A";
    case Grade::B:
        return "B";
    case Grade::C:
        return "C";
    case Grade::D:
        return "D";
    case Grade::F:
        return "F";
    case Grade::None:
        return "None";
    }
    return "Unknown";
}

Submission::Submission(
    const Student& student, const Assignment& assignment, std::string data,
    Professor* graded_by, Grade grade
)
    : student_{&student},
      assignment_{&assignment},
      data_{std::move(data)},
      graded_by_{graded_by},
      grade_{grade}
{}

const Student& Submission::get_student() const { return *student_; }

const Assignment& Submission::get_assignment() const { return *assignment_; }

const std::string& Submission::get_data() const { return data_; }

const Professor* Submission::get_grading_professor() const { return graded_by_; }

Grade Submission::get_grade() const { return grade_; }
void Submission::assign_grade(const Professor* professor, Grade grade)
{
    graded_by_ = professor;
    grade_ = grade;
}
