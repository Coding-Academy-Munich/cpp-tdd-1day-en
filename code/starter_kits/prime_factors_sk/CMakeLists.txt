add_library(prime_factors_sk_lib prime_factors.cpp prime_factors.h)

add_executable(prime_factors_sk prime_factors_main.cpp)
target_link_libraries(prime_factors_sk PRIVATE prime_factors_sk_lib)

add_executable(prime_factors_sk_test prime_factors_test.cpp)
target_link_libraries(prime_factors_sk_test PRIVATE prime_factors_sk_lib Catch2WithMain)
