add_library(recipes_sk_lib
    recipes_sk.h
    recipes_sk.cpp
)

add_executable (recipes_sk
    recipes_sk_main.cpp
)
target_link_libraries(recipes_sk
	recipes_sk_lib
)

add_executable(recipes_sk_test
    recipes_sk_test.cpp
)
target_link_libraries(recipes_sk_test
    Catch2WithMain
	recipes_sk_lib
)