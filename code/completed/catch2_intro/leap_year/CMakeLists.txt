add_library(leap_year_lib leap_year.h leap_year.cpp)

add_executable(leap_year_test leap_year_test.cpp)
target_link_libraries(leap_year_test leap_year_lib Catch2WithMain)

add_executable(leap_year_scenario_test leap_year_scenario_test.cpp)
target_link_libraries(leap_year_scenario_test leap_year_lib Catch2WithMain)