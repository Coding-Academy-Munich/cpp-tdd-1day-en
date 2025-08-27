SET(CMAKE_CXX_STANDARD 20)

add_subdirectory("lib")
add_subdirectory("test")

add_executable(invoice_sk_v0 main.cpp)
target_link_libraries(invoice_sk_v0 PRIVATE invoice_sk_data)
target_link_libraries(invoice_sk_v0 PRIVATE invoice_sk_lib_v0)
