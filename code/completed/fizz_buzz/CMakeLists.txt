add_library(fizz_buzz_lib fizz_buzz.cpp fizz_buzz.h)

add_executable(fizz_buzz fizz_buzz_main.cpp)
target_link_libraries(fizz_buzz PRIVATE fizz_buzz_lib)

add_executable(fizz_buzz_test fizz_buzz_test.cpp)
target_link_libraries(fizz_buzz_test PRIVATE fizz_buzz_lib Catch2WithMain)