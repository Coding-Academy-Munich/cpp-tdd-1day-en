SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(spacecraft_controller_sk main.cpp)
target_link_libraries(spacecraft_controller_sk PRIVATE spacecraft_controller_sk_lib)
