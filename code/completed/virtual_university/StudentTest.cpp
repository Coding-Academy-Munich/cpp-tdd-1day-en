// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <catch2/catch_test_macros.hpp>

#include "Professor.h"
#include "Student.h"
#include "University.h"

TEST_CASE ("Student")
{
    University university{"Test University"};
    university.add_student("Test Student");
    university.add_professor("Test Professor");
    university.add_lecture("Test Lecture", "Test Professor");
    Lecture& lecture{university.get_lecture("Test Lecture")};
    lecture.add_assignment("Test Assignment", "2024-06-02");

    Student& unit{university.get_student("Test Student")};

    SECTION ("Student initially has no submissions")
    {
        CHECK(unit.get_submissions().empty());
    }

    SECTION ("Can submit an assignment")
    {
        unit.submit_assignment("Test Lecture", "Test Assignment", "Test Submission");

        CHECK(unit.get_submissions().size() == 1);
        const Submission& submission{unit.get_submission("Test Assignment")};
        CHECK(submission.get_data() == "Test Submission");
    }
}