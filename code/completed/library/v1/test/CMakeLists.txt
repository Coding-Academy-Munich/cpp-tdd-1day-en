cmake_minimum_required(VERSION 3.20)

add_executable(library_v1_test TestBook.cpp
        TestMember.cpp
        TestUtils.cpp)
target_link_libraries(library_v1_test PRIVATE library_v1_lib)
target_link_libraries(library_v1_test PRIVATE library_data)
target_link_libraries(library_v1_test PRIVATE Catch2::Catch2WithMain)
