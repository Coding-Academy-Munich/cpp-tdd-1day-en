// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <catch2/catch_test_macros.hpp>

#include "Professor.h"
#include "catch2/generators/catch_generators.hpp"

TEST_CASE ("Professor")
{
    University university{"Test University"};
    university.add_professor("Test Professor");
    Professor& unit{university.get_professor("Test Professor")};

    SECTION ("Professor initially has no lectures")
    {
        CHECK(unit.get_lectures().empty());
    }

    SECTION ("Lectures are updated when a new lecture is added")
    {
        university.add_lecture("Test Lecture", "Test Professor");
        CHECK(unit.get_lectures().size() == 1);
        CHECK(unit.get_lecture("Test Lecture").get_name() == "Test Lecture");
    }

    SECTION ("Can create assignments")
    {
        university.add_lecture("Test Lecture", "Test Professor");
        Lecture& lecture{university.get_lecture("Test Lecture")};

        unit.create_assignment("Test Lecture", "Test Assignment", "2024-06-02");

        CHECK(lecture.get_assignments().size() == 1);
        CHECK(lecture.get_assignment("Test Assignment").get_name() == "Test Assignment");
    }

    SECTION ("Can grade submissions")
    {
        university.add_student("Test Student");
        university.add_lecture("Test Lecture", "Test Professor");
        Lecture& lecture{university.get_lecture("Test Lecture")};
        Student& student{university.get_student("Test Student")};
        lecture.add_assignment("Test Assignment", "2024-06-02");
        lecture.submit_assignment(student, "Test Assignment", "Test Submission");
        Submission& submission{
            lecture.get_submissions_for(lecture.get_assignment("Test Assignment"))[0]
        };

        unit.grade_submission(submission, Grade::C);

        CHECK(submission.get_grade() == Grade::C);
        REQUIRE(submission.get_grading_professor() != nullptr);
        CHECK(submission.get_grading_professor() == &unit);
    }

    SECTION ("Equality compares name and university name")
    {
        auto [uni2_name, prof2_name, eq]{GENERATE(table<const char*, const char*, bool>(
            {{"Test University", "Test Professor", true},
             {"Test University", "Test Professor 2", false},
             {"Test University 2", "Test Professor", false},
             {"Test University 2", "Test Professor 2", false}}
        ))};
        University university2{uni2_name};
        Professor professor2{prof2_name, university2};
        CHECK((unit == professor2) == eq);
    }
}
