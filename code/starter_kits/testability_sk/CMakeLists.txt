SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(testability_sk main.cpp)
target_link_libraries(testability_sk PRIVATE testability_sk_lib)
