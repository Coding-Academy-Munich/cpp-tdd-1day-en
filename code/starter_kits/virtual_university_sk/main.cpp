// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "Assignment.h"
#include "Lecture.h"
#include "Professor.h"
#include "Student.h"
#include "University.h"
#include <iostream>

int main()
{
    // Create a University instance
    University uni{"The University of Nowhere"};

    // Add students to the university
    uni.add_student("Alice");
    uni.add_student("Bob");
    uni.add_student("Carol");
    uni.add_student("Dave");

    Student& alice = uni.get_student("Alice");
    Student& bob = uni.get_student("Bob");
    Student& carol = uni.get_student("Carol");
    Student& dave = uni.get_student("Dave");

    // Add professors to the university
    uni.add_professor("Mr. Smith");
    uni.add_professor("Ms. Jones");

    Professor& mr_smith = uni.get_professor("Mr. Smith");
    Professor& ms_jones = uni.get_professor("Ms. Jones");

    // Create some lectures
    uni.add_lecture("Math 101", "Mr. Smith");
    uni.add_lecture("Physics 201", "Mr. Smith");
    uni.add_lecture("English 101", "Ms. Jones");
    uni.add_lecture("History 203", "Ms. Jones");

    Lecture& math_course{uni.get_lecture("Math 101")};
    Lecture& physics_course{mr_smith.get_lecture("Physics 201")};
    Lecture& english_course{ms_jones.get_lecture("English 101")};
    Lecture& history_course{ms_jones.get_lecture("History 203")};

    // Add assignments to the lectures
    for (auto [title, date] : std::vector<std::pair<std::string, std::string>>{
             {"Homework 1", "2024-06-01"},
             {"Homework 2", "2024-06-08"},
             {"Homework 3", "2024-06-15"},
             {"Homework 4", "2024-06-22"}
         })
    {
        math_course.add_assignment(title, date);
        mr_smith.create_assignment("Physics 201", title, date);
        english_course.add_assignment(title, date);
        ms_jones.create_assignment("History 203", title, date);
    }

    // Students submit assignments
    alice.submit_assignment("Math 101", "Homework 1", "1 + 1 = 2");
    bob.submit_assignment("Math 101", "Homework 1", "1 + 1 < 3");
    carol.submit_assignment("Physics 201", "Homework 1", "F = m * a");
    dave.submit_assignment(
        "History 203", "Homework 1", "The American Revolution was in 1776"
    );
    for (auto& student : uni.get_students())
    {
        student->submit_assignment("English 101", "Homework 1", "To be or not to be");
    }

    // Professors grade the assignments
    for (auto& professor : uni.get_professors())
    {
        for (auto& lecture : professor->get_lectures())
        {
            for (auto& assignment : lecture->get_assignments())
            {
                for (auto& submission : lecture->get_submissions_for(assignment))
                {
                    professor->grade_submission(submission, Grade::A);
                }
            }
        }
    }

    // Print Lecture details
    for (const auto& lecture : uni.get_lectures())
    {
        std::cout << lecture->get_info() << "\n";
    }

    return 0;
}
