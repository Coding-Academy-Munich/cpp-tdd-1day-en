SET(CMAKE_CXX_STANDARD 20)

add_subdirectory("lib")
add_subdirectory("test")

add_executable(refactoring_lms_sk main.cpp)
target_link_libraries(refactoring_lms_sk PRIVATE lms_sk_lib)