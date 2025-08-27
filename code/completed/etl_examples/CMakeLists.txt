add_executable(etl_basic etl_basic.cpp)
target_link_libraries(etl_basic PRIVATE etl)

add_executable(etl_observer
        etl_observer.cpp
        etl_observer.h
        ticker_symbol.h
        etl_observer_main.cpp)
target_link_libraries(etl_observer PRIVATE etl)

add_executable(etl_singleton etl_singleton.cpp etl_singleton.h
        etl_singleton_main.cpp)
target_link_libraries(etl_singleton PRIVATE etl)

add_executable(etl_expected etl_expected.cpp
        etl_expected.h
        etl_expected_main.cpp)
target_link_libraries(etl_expected PRIVATE etl)