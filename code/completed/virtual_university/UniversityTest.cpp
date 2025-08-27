// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "University.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE ("University")
{
    University unit{"Test University"};

    SECTION ("Can add student")
    {
        unit.add_student("Alice");

        CHECK(unit.get_students().size() == 1);
        Student& student{*unit.get_students().front()};
        CHECK(student.get_name() == "Alice");
        CHECK(student.get_university() == unit);
    }

    SECTION ("Can get student by name")
    {
        unit.add_student("Alice");
        unit.add_student("Bob");

        CHECK(unit.get_student("Alice").get_name() == "Alice");
        CHECK(unit.get_student("Bob").get_name() == "Bob");
    }

    SECTION ("Can get student by name (const)")
    {
        unit.add_student("Alice");
        unit.add_student("Bob");

        const University& const_unit = unit;
        CHECK(const_unit.get_student("Alice").get_name() == "Alice");
        CHECK(const_unit.get_student("Bob").get_name() == "Bob");
    }

    SECTION ("Can add professor")
    {
        unit.add_professor("Bob");

        CHECK(unit.get_professors().size() == 1);
        Professor& professor{*unit.get_professors().front()};
        CHECK(professor.get_name() == "Bob");
        CHECK(professor.get_university() == unit);
    }

    SECTION ("Can get professor by name")
    {
        unit.add_professor("Alice");
        unit.add_professor("Bob");

        CHECK(unit.get_professor("Alice").get_name() == "Alice");
        CHECK(unit.get_professor("Bob").get_name() == "Bob");
    }

    SECTION ("Can get professor by name (const)")
    {
        unit.add_professor("Alice");
        unit.add_professor("Bob");

        const University& const_unit = unit;
        CHECK(const_unit.get_professor("Alice").get_name() == "Alice");
        CHECK(const_unit.get_professor("Bob").get_name() == "Bob");
    }

    SECTION ("Can add lecture")
    {
        unit.add_professor("Alice");

        unit.add_lecture("Math", "Alice");

        CHECK(unit.get_lectures().size() == 1);
        Lecture& lecture{*unit.get_lectures().front()};
        CHECK(lecture.get_name() == "Math");
        CHECK(lecture.get_professor().get_name() == "Alice");
        CHECK(lecture.get_assignments().empty());
    }

    SECTION ("Can get lecture by name")
    {
        unit.add_professor("Alice");
        unit.add_lecture("Math", "Alice");
        unit.add_lecture("Physics", "Alice");

        CHECK(unit.get_lecture("Math").get_name() == "Math");
        CHECK(unit.get_lecture("Physics").get_name() == "Physics");
    }

    SECTION ("Can get lecture by name (const)")
    {
        unit.add_professor("Alice");
        unit.add_lecture("Math", "Alice");
        unit.add_lecture("Physics", "Alice");

        const University& const_unit = unit;
        CHECK(const_unit.get_lecture("Math").get_name() == "Math");
        CHECK(const_unit.get_lecture("Physics").get_name() == "Physics");
    }
}