// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_VIRTUAL_UNIVERSITY_UNIVERSITY_H
#define COMPLETED_VIRTUAL_UNIVERSITY_UNIVERSITY_H

#include "Lecture.h"
#include "Professor.h"
#include "Student.h"
#include <memory>
#include <vector>

class University
{
public:
    explicit University(std::string name);

    [[nodiscard]] const std::string& get_name() const;

    void add_student(const std::string& name);
    void add_professor(const std::string& name);
    void add_lecture(const std::string& name, const std::string& professor_name);

    [[nodiscard]] const std::vector<std::unique_ptr<Student>>& get_students() const;
    [[nodiscard]] const Student& get_student(const std::string& name) const;
    [[nodiscard]] Student& get_student(const std::string& name);

    [[nodiscard]] const std::vector<std::unique_ptr<Professor>>& get_professors() const;
    [[nodiscard]] const Professor& get_professor(const std::string& name) const;
    [[nodiscard]] Professor& get_professor(const std::string& name);

    [[nodiscard]] const std::vector<std::unique_ptr<Lecture>>& get_lectures() const;
    [[nodiscard]] const Lecture& get_lecture(const std::string& name) const;
    [[nodiscard]] Lecture& get_lecture(const std::string& name);

private:
    std::string name_;
    std::vector<std::unique_ptr<Student>> students_;
    std::vector<std::unique_ptr<Professor>> professors_;
    std::vector<std::unique_ptr<Lecture>> lectures_;
};

bool operator==(const University& lhs, const University& rhs);
bool operator!=(const University& lhs, const University& rhs);

#endif // COMPLETED_VIRTUAL_UNIVERSITY_UNIVERSITY_H
