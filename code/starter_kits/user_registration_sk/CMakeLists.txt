SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(user_registration_sk main.cpp)
target_link_libraries(user_registration_sk PRIVATE user_registration_sk_lib)
