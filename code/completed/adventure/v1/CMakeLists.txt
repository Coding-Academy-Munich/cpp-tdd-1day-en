cmake_minimum_required(VERSION 3.20)
project(adventure_v1)

add_executable(${PROJECT_NAME}
    main.cpp
    Location.cpp
    Location.h
    World.cpp
    World.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)
