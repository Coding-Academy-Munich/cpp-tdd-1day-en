add_library(invoice_sk_data invoice_sk_data.h invoice_sk_data.cpp)
target_include_directories(invoice_sk_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(invoice_sk_data PRIVATE invoice_sk_lib_v0)
