// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <catch2/catch_test_macros.hpp>

#include "Lecture.h"
#include "University.h"

TEST_CASE ("Lecture")
{
    University university("Test University");
    university.add_professor("Test Professor");
    university.add_student("Test Student");
    university.add_lecture("Test Lecture", "Test Professor");

    Student& student{university.get_student("Test Student")};
    Lecture& unit{university.get_lecture("Test Lecture")};

    SECTION ("Can add single assignment")
    {
        unit.add_assignment("Test Assignment", "2024-06-02");

        Assignment& assignment = unit.get_assignment("Test Assignment");
        CHECK(assignment.get_name() == "Test Assignment");
        CHECK(assignment.get_due_date() == "2024-06-02");
    }

    SECTION ("Can add multiple assignments")
    {
        unit.add_assignment("Test Assignment 1", "2024-06-02");
        unit.add_assignment("Test Assignment 2", "2024-06-03");
        unit.add_assignment("Test Assignment 3", "2024-06-04");

        CHECK(unit.get_assignments().size() == 3);
        CHECK(unit.get_assignment("Test Assignment 1").get_due_date() == "2024-06-02");
        CHECK(unit.get_assignment("Test Assignment 2").get_due_date() == "2024-06-03");
        CHECK(unit.get_assignment("Test Assignment 3").get_due_date() == "2024-06-04");
    }

    SECTION ("Can submit assignment")
    {
        unit.add_assignment("Test Assignment", "2024-06-02");
        unit.submit_assignment(student, "Test Assignment", "Test Submission");
        Assignment& assignment{unit.get_assignment("Test Assignment")};
        const auto& submissions{unit.get_submissions_for(assignment)};
        CHECK(submissions.size() == 1);
        CHECK(submissions[0].get_student().get_name() == "Test Student");
        CHECK(submissions[0].get_data() == "Test Submission");
    }

    SECTION ("Can submit multiple assignments")
    {
        unit.add_assignment("Test Assignment 1", "2024-06-02");
        unit.add_assignment("Test Assignment 2", "2024-06-03");

        unit.submit_assignment(student, "Test Assignment 1", "Test Submission 1.1");
        unit.submit_assignment(student, "Test Assignment 1", "Test Submission 1.2");
        unit.submit_assignment(student, "Test Assignment 1", "Test Submission 1.3");
        unit.submit_assignment(student, "Test Assignment 2", "Test Submission 2.1");
        unit.submit_assignment(student, "Test Assignment 2", "Test Submission 2.2");

        Assignment& assignment1{unit.get_assignment("Test Assignment 1")};
        Assignment& assignment2{unit.get_assignment("Test Assignment 2")};
        CHECK(unit.get_submissions_for(assignment1).size() == 3);
        CHECK(unit.get_submissions_for(assignment2).size() == 2);
    }
}