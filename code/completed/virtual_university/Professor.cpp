// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "Professor.h"
#include "Lecture.h"

#include <stdexcept>
#include <utility>

Professor::Professor(std::string name, University& university)
    : name_{std::move(name)}, university_{&university}
{}

std::string Professor::get_name() const { return name_; }

const University& Professor::get_university() const { return *university_; }

void Professor::set_university(University& university) { university_ = &university; }

std::vector<Lecture*> Professor::get_lectures() const
{
    std::vector<Lecture*> result;
    for (auto& lecture : get_university().get_lectures())
    {
        if (lecture->get_professor() == *this)
        {
            result.push_back(lecture.get());
        }
    }
    return result;
}

const Lecture& Professor::get_lecture(const std::string& course_name) const
{
    return const_cast<Professor*>(this)->get_lecture(course_name);
}

Lecture& Professor::get_lecture(const std::string& course_name)
{
    for (auto& lecture : get_university().get_lectures())
    {
        if (lecture->get_professor() == *this && lecture->get_name() == course_name)
        {
            return *lecture;
        }
    }
    throw std::runtime_error("Lecture not found");
}

void Professor::create_assignment(
    const std::string& lecture_name, const std::string& assignment_name,
    const std::string& due_date
)
{
    Lecture& lecture{get_lecture(lecture_name)};
    lecture.add_assignment(assignment_name, due_date);
}

void Professor::grade_submission(Submission& submission, Grade grade) const
{
    submission.assign_grade(this, grade);
}

bool operator==(const Professor& lhs, const Professor& rhs)
{
    return lhs.get_name() == rhs.get_name() && lhs.get_university() == rhs.get_university();
}

bool operator!=(const Professor& lhs, const Professor& rhs) { return !(lhs == rhs); }
