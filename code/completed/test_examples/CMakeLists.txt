add_library(fun_state_interact_lib
        fun_state_interact.cpp
        fun_state_interact.h
)

add_executable(fun_state_interact_test fun_state_interact_test.cpp cout_redirect.h)
target_link_libraries(fun_state_interact_test fun_state_interact_lib Catch2WithMain)

add_library(state_machine_test_lib
        state_machine.h
        state_machine.cpp
)

add_executable(state_machine_test state_machine_test.cpp cout_redirect.h)
target_link_libraries(state_machine_test state_machine_test_lib Catch2WithMain)