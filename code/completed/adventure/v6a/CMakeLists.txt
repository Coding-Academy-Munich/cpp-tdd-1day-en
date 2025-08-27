cmake_minimum_required(VERSION 3.20)
project(adventure_v6a)

add_subdirectory(cli)
add_subdirectory(lib)
add_subdirectory(test)

add_executable(${PROJECT_NAME} main.cpp
        cli/CliPlayerObserver.cpp
        cli/CliGameObserver.h)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_v6a_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)
