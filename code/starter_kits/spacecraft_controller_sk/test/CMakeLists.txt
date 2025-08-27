enable_testing()

add_executable(spacecraft_controller_sk_test spacecraft_controller_sk_test.cpp)

target_link_libraries(spacecraft_controller_sk_test
    PRIVATE
	spacecraft_controller_sk_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME spacecraft_controller_sk_test
         COMMAND spacecraft_controller_sk_test
)
