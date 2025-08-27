cmake_minimum_required(VERSION 3.20)
project(adventure_v5b_test)

add_executable(${PROJECT_NAME}
        TestActions.cpp
        TestLocation.cpp
        TestPawn.cpp
        TestPlayer.cpp
        TestWorld.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_v5b_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE adventure_data)
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
