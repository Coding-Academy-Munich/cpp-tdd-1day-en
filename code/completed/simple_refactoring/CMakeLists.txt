SET(CMAKE_CXX_STANDARD 20)

add_subdirectory("lib")
add_subdirectory("test")

add_executable(simple_refactoring main.cpp)
target_link_libraries(simple_refactoring PRIVATE simple_refactoring_lib)