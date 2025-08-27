// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "Student.h"
#include "Lecture.h"
#include "University.h"

#include <stdexcept>
#include <utility>

Student::Student(std::string name, University& university)
    : name_{std::move(name)}, university_{&university}
{}

const std::string& Student::get_name() const { return name_; }

const University& Student::get_university() const
{
    return const_cast<Student*>(this)->get_university();
}

University& Student::get_university()
{
    if (university_)
    {
        return *university_;
    }
    throw std::runtime_error("Student is not associated with a university");
}

void Student::set_university(University& university) { university_ = &university; }

void Student::submit_assignment(
    const std::string& lecture_name, const std::string& assignment_name,
    const std::string& data
)
{
    Lecture& lecture{university_->get_lecture(lecture_name)};
    lecture.submit_assignment(*this, assignment_name, data);
}

std::vector<Submission>& Student::get_submissions() { return submissions_; }

const Submission& Student::get_submission(const std::string& assignment_name) const
{
    for (const auto& submission : submissions_)
    {
        if (submission.get_assignment().get_name() == assignment_name)
        {
            return submission;
        }
    }
    throw std::runtime_error("Submission not found");
}

void Student::add_submission(const Submission& submission)
{
    submissions_.push_back(submission);
}
