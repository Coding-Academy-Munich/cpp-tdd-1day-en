enable_testing()

add_executable(user_registration_test user_registration_test.cpp)

target_link_libraries(user_registration_test
    PRIVATE
	user_registration_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME user_registration_test
         COMMAND user_registration_test
)
