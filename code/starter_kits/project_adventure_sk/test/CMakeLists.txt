enable_testing()

add_executable(project_adventure_sk_test project_adventure_sk_test.cpp)

target_link_libraries(project_adventure_sk_test
    PRIVATE
	project_adventure_sk_lib
    Catch2::Catch2WithMain
)

include(CTest)
add_test(NAME project_adventure_sk_test
         COMMAND project_adventure_sk_test
)
