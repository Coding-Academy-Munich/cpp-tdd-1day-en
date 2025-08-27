cmake_minimum_required(VERSION 3.20)
project(adventure_v4c_lib)

add_library(${PROJECT_NAME}
        Location.cpp
        Location.h
        World.cpp
        World.h
        WorldFactory.cpp
        WorldFactory.h
        Pawn.cpp
        Pawn.h
        actions/MoveAction.cpp
        actions/MoveAction.h
        actions/SkipTurnAction.cpp
        actions/SkipTurnAction.h
        Action.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)
