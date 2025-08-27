cmake_minimum_required(VERSION 3.20)

add_executable(library_v2a_test TestBook.cpp
        TestMember.cpp
        TestUtils.cpp
        TestLibrary.cpp)
target_link_libraries(library_v2a_test PRIVATE library_v2a_lib)
target_link_libraries(library_v2a_test PRIVATE library_data)
target_link_libraries(library_v2a_test PRIVATE Catch2::Catch2WithMain)
