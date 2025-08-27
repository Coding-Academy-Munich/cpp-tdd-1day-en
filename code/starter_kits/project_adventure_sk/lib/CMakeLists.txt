add_library(project_adventure_sk_lib
        project_adventure_sk.cpp
        project_adventure_sk.h
)
target_include_directories(project_adventure_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
