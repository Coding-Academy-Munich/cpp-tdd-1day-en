cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 20)

add_library(library_v1_lib Book.cpp Book.h
        Member.cpp
        Member.h
        Utils.h
        Utils.cpp)
target_include_directories(library_v1_lib PUBLIC .)
target_link_libraries(library_v1_lib PRIVATE library_data)
