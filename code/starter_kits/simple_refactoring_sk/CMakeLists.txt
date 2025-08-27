SET(CMAKE_CXX_STANDARD 20)

add_subdirectory("lib")
add_subdirectory("test")

add_executable(simple_refactoring_sk main.cpp)
target_link_libraries(simple_refactoring_sk PRIVATE simple_refactoring_sk_lib)