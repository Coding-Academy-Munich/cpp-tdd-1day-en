add_library(lms_sk_lib
        library.cpp
        library.h
        book.cpp
        book.h
        member.cpp
        member.h
        loan.cpp
        loan.h
        catalog.cpp
        catalog.h)
target_include_directories(lms_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
