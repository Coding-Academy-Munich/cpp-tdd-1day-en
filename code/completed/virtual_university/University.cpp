// Copyright 2024, Dr. Matthias Hölzl.
//

#include "University.h"
#include <memory>
#include <stdexcept>
#include <utility>

University::University(std::string name) : name_{std::move(name)} {}

const std::string& University::get_name() const { return name_; }

void University::add_student(const std::string& name)
{
    students_.push_back(std::make_unique<Student>(name, *this));
}

void University::add_professor(const std::string& name)
{
    professors_.push_back(std::make_unique<Professor>(name, *this));
}

void University::add_lecture(const std::string& name, const std::string& professor_name)
{
    auto& professor{get_professor(professor_name)};
    lectures_.push_back(std::make_unique<Lecture>(name, professor));
}

const std::vector<std::unique_ptr<Student>>& University::get_students() const
{
    return students_;
}

const Student& University::get_student(const std::string& name) const
{
    return const_cast<University*>(this)->get_student(name);
}

Student& University::get_student(const std::string& name)
{
    for (auto& student : students_)
    {
        if (student->get_name() == name)
        {
            return *student;
        }
    }
    throw std::runtime_error("Student not found");
}

const std::vector<std::unique_ptr<Professor>>& University::get_professors() const
{
    return professors_;
}

const Professor& University::get_professor(const std::string& name) const
{
    return const_cast<University*>(this)->get_professor(name);
}

Professor& University::get_professor(const std::string& name)
{
    for (const auto& professor : professors_)
    {
        if (professor->get_name() == name)
        {
            return *professor;
        }
    }
    throw std::runtime_error("Professor not found");
}

const std::vector<std::unique_ptr<Lecture>>& University::get_lectures() const
{
    return lectures_;
}

const Lecture& University::get_lecture(const std::string& name) const
{
    return const_cast<University*>(this)->get_lecture(name);
}

Lecture& University::get_lecture(const std::string& name)
{
    for (const auto& lecture : lectures_)
    {
        if (lecture->get_name() == name)
        {
            return *lecture;
        }
    }
    throw std::runtime_error("Lecture not found");
}

bool operator==(const University& lhs, const University& rhs)
{
    return lhs.get_name() == rhs.get_name();
}

bool operator!=(const University& lhs, const University& rhs) { return !(lhs == rhs); }
