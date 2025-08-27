cmake_minimum_required(VERSION 3.20)

add_executable(library_v2b_test TestBook.cpp
        TestMember.cpp
        TestUtils.cpp
        TestLibrary.cpp
        TestCatalog.cpp)
target_link_libraries(library_v2b_test PRIVATE library_v2b_lib)
target_link_libraries(library_v2b_test PRIVATE library_data)
target_link_libraries(library_v2b_test PRIVATE Catch2::Catch2WithMain)
