add_library(fizz_buzz_sk_lib fizz_buzz.cpp fizz_buzz.h)

add_executable(fizz_buzz_sk fizz_buzz_main.cpp)
target_link_libraries(fizz_buzz_sk PRIVATE fizz_buzz_sk_lib)

add_executable(fizz_buzz_sk_test fizz_buzz_test.cpp)
target_link_libraries(fizz_buzz_sk_test PRIVATE fizz_buzz_sk_lib Catch2WithMain)