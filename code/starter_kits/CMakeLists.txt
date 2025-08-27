set(STARTER_KITS
        adventure_sk
        adventure_sk2
        bmi_sk
        catch2_intro_sk
        fizz_buzz_sk
        hello_world_sk
        invoice_sk
        library_sk
        order_processor_sk
        prime_factors_sk
        project_adventure_sk
        recipes_sk
        refactoring_lms_sk
        salaries_sk
        simple_calculator_sk
        simple_refactoring_sk
        spacecraft_controller_sk
        testability_sk
        two_loop_cycle_sk
        user_registration_sk
        vending_machine_sk
        virtual_university_sk
)

foreach (PROJECT ${STARTER_KITS})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${PROJECT})
        add_subdirectory(${PROJECT})
    endif ()
endforeach ()

set(OPTIONAL_STARTER_KITS
        blocks_sk
)

foreach (PROJECT ${OPTIONAL_STARTER_KITS})
    if (IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${PROJECT})
        add_subdirectory(${PROJECT} EXCLUDE_FROM_ALL)
    endif ()
endforeach ()
