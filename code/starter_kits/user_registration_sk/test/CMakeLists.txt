enable_testing()

add_executable(user_registration_sk_test user_registration_service_test.cpp)

target_link_libraries(user_registration_sk_test
        PRIVATE
        user_registration_sk_lib
        Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME user_registration_sk_test
        COMMAND user_registration_sk_test
)
