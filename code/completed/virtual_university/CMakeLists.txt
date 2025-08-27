set(CMAKE_CXX_STANDARD 20)

add_library(virtual_university_lib
        Assignment.cpp
        Assignment.h
        Lecture.cpp
        Lecture.h
        Professor.cpp
        Professor.h
        Student.cpp
        Student.h
        Submission.cpp
        Submission.h
        University.cpp
        University.h
)

add_executable(virtual_university main.cpp)
target_link_libraries(virtual_university virtual_university_lib)

add_executable(virtual_university_test
        AssignmentTest.cpp
        LectureTest.cpp
        ProfessorTest.cpp
        StudentTest.cpp
        SubmissionTest.cpp
        UniversityTest.cpp
)
target_link_libraries(virtual_university_test virtual_university_lib Catch2WithMain)