SET(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(test)

add_executable(project_adventure_sk main.cpp)
target_link_libraries(project_adventure_sk PRIVATE project_adventure_sk_lib)

# This command is attached directly to the executable target
# and runs after it has been built.
add_custom_command(
    TARGET project_adventure_sk
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:project_adventure_sk>/data"
    COMMENT "Copying data to output directory"
    VERBATIM
)