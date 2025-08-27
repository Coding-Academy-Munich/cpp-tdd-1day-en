SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(user_registration main.cpp)
target_link_libraries(user_registration PRIVATE user_registration_lib)
