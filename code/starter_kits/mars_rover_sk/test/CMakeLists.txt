enable_testing()

add_executable(mars_rover_sk_test mars_rover_sk_test.cpp)

target_link_libraries(mars_rover_sk_test
    PRIVATE
	mars_rover_sk_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME mars_rover_sk_test
         COMMAND mars_rover_sk_test
)
