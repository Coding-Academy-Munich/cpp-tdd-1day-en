add_library(spacecraft_controller_sk_lib
        spacecraft_command_controller.cpp
        spacecraft_command_controller.h
        telemetry_system.h
        thruster_control.h
        ground_control_link.h
)
target_include_directories(spacecraft_controller_sk_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
