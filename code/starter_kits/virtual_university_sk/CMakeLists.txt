set(CMAKE_CXX_STANDARD 20)

add_library(virtual_university_lib_sk
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

add_executable(virtual_university_sk main.cpp)
target_link_libraries(virtual_university_sk virtual_university_lib_sk)

add_executable(virtual_university_test_sk
        AssignmentTest.cpp
        LectureTest.cpp
        ProfessorTest.cpp
        StudentTest.cpp
        SubmissionTest.cpp
        UniversityTest.cpp
)
target_link_libraries(virtual_university_test_sk virtual_university_lib_sk Catch2WithMain)