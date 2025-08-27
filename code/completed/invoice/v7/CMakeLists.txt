SET(CMAKE_CXX_STANDARD 20)

add_subdirectory("lib")
add_subdirectory("test")

add_executable(invoice_v7 main.cpp)
target_link_libraries(invoice_v7 PRIVATE invoice_data)
target_link_libraries(invoice_v7 PRIVATE invoice_lib_v7)
