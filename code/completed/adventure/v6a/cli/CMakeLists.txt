cmake_minimum_required(VERSION 3.20)
project(adventure_v6a_cli)

add_library(${PROJECT_NAME}
        CliPlayerObserver.cpp
        CliGameObserver.h
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC adventure_v6a_lib)
