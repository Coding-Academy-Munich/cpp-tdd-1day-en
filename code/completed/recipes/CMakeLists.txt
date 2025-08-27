add_library(recipes_lib
    recipes.h
    recipes.cpp
)

add_executable (recipes
    recipes_main.cpp
)
target_link_libraries(recipes
	recipes_lib
)

add_executable(recipes_test
    recipes_test.cpp
)
target_link_libraries(recipes_test
    Catch2WithMain
	recipes_lib
)