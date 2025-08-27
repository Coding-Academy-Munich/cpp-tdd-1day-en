add_library(project_adventure_lib
        room.cpp
        room.h
        game.cpp
        game.h
        action.cpp
        action.h
)
target_include_directories(project_adventure_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
