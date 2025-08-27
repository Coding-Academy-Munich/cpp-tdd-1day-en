add_library(prime_factors_lib prime_factors.cpp prime_factors.h)

add_executable(prime_factors prime_factors_main.cpp)
target_link_libraries(prime_factors PRIVATE prime_factors_lib)

add_executable(prime_factors_test prime_factors_test.cpp)
target_link_libraries(prime_factors_test PRIVATE prime_factors_lib Catch2WithMain)
