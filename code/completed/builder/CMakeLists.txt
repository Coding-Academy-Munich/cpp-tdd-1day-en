SET(CMAKE_CXX_STANDARD 23)

add_library(builder_lib
        window.cpp
        window.h
        window_builder.cpp
        window_builder.h
)

add_executable(builder_test window_test.cpp)
target_link_libraries(builder_test builder_lib Catch2WithMain)

add_executable(builder_main window_main.cpp)
target_link_libraries(builder_main builder_lib)
