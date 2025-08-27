enable_testing()

add_executable(mars_rover_test mars_rover_test.cpp)

target_link_libraries(mars_rover_test
    PRIVATE
	mars_rover_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME mars_rover_test
         COMMAND mars_rover_test
)
