SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(vending_machine_sk main.cpp)
target_link_libraries(vending_machine_sk PRIVATE vending_machine_sk_lib)
