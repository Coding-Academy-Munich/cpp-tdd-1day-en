// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include <catch2/catch_test_macros.hpp>

#include "Submission.h"
#include "University.h"

TEST_CASE ("Submission")
{
    University university{"Test University"};
    university.add_student("Test Student");
    Student& student{university.get_student("Test Student")};
    university.add_professor("Test Professor");
    Professor& professor{university.get_professor("Test Professor")};
    university.add_lecture("Test Lecture", "Test Professor");
    Lecture& lecture{university.get_lecture("Test Lecture")};
    lecture.add_assignment("Test Assignment", "2024-06-02");
    lecture.submit_assignment(student, "Test Assignment", "Test Submission");
    Submission& submission{
        lecture.get_submissions_for(lecture.get_assignment("Test Assignment")).front()
    };

    SECTION ("Assigning a grade also sets the grading professor")
    {
        submission.assign_grade(&professor, Grade::B);
        CHECK(submission.get_grade() == Grade::B);
        CHECK(submission.get_grading_professor() == &professor);
    }
}