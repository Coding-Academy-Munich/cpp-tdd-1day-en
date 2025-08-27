// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "Lecture.h"
#include "Professor.h"
#include "Student.h"

#include <sstream>
#include <stdexcept>
#include <utility>

Lecture::Lecture(std::string name, Professor& professor)
    : name_{std::move(name)}, professor_{&professor}
{}

const std::string& Lecture::get_name() const { return name_; }

const Professor& Lecture::get_professor() const
{
    if (professor_ == nullptr)
    {
        throw std::runtime_error("No professor assigned to lecture");
    }
    return *professor_;
}

void Lecture::add_assignment(const std::string& name, const std::string& due_date)
{
    assignments_.emplace_back(name, due_date);
}

const std::vector<Assignment>& Lecture::get_assignments() const { return assignments_; }

std::vector<Assignment>& Lecture::get_assignments() { return assignments_; }

void Lecture::add_submission(const Submission& submission)
{
    submissions_[&submission.get_assignment()].push_back(submission);
}

std::vector<Submission>& Lecture::get_submissions_for(const Assignment& assignment)
{
    return submissions_[&assignment];
}

Assignment& Lecture::get_assignment(const std::string& name)
{
    for (auto& assignment : assignments_)
    {
        if (assignment.get_name() == name)
        {
            return assignment;
        }
    }
    throw std::runtime_error("Assignment not found");
}

void Lecture::submit_assignment(
    Student& student, const std::string& assignment_name, const std::string& basic_string
)
{
    Assignment& assignment = get_assignment(assignment_name);
    Submission submission{student, assignment, basic_string};
    add_submission(submission);
    student.add_submission(submission);
}

std::string Lecture::get_info() const
{
    std::stringstream ss;
    ss << "Lecture: " << name_ << "\n";
    ss << "Professor: " << professor_->get_name() << "\n";
    ss << "Assignments:\n";
    for (const auto& assignment : assignments_)
    {
        ss << "  " << assignment.get_name() << " (due " << assignment.get_due_date()
           << ")\n";
    }
    ss << "Submissions:\n";
    for (const auto& [assignment, submissions] : submissions_)
    {
        ss << "  " << assignment->get_name() << ":\n";
        for (const auto& submission : submissions)
        {
            ss << "    " << submission.get_student().get_name() << ": "
               << submission.get_data();
            if (submission.get_grade() != Grade::None)
            {
                ss << " (graded by " << submission.get_grading_professor()->get_name()
                   << " with " << to_string(submission.get_grade()) << ")";
            }
            ss << "\n";
        }
    }
    return ss.str();
}
