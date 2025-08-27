cmake_minimum_required(VERSION 3.20)

set(CXX_STANDARD 20)

add_library(library_v2c_lib Book.cpp Book.h
        Member.cpp
        Member.h
        Utils.h
        Utils.cpp
        Library.cpp
        Library.h
        Catalog.h
        BookCatalog.cpp
        BookCatalog.h
        MemberCatalog.cpp
        MemberCatalog.h
)
target_include_directories(library_v2c_lib PUBLIC .)
target_link_libraries(library_v2c_lib PRIVATE library_data)
