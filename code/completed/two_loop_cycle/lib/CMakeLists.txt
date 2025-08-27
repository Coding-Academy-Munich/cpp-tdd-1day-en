add_library(two_loop_cycle_lib
        todo_list.cpp
        todo_list.h
        task.cpp
        task.h
)
target_include_directories(two_loop_cycle_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
