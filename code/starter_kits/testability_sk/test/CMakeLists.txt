enable_testing()

add_executable(testability_sk_test testability_sk_test.cpp)

target_link_libraries(testability_sk_test
    PRIVATE
	testability_sk_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME testability_sk_test
         COMMAND testability_sk_test
)
