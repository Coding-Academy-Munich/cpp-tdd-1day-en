add_library(invoice_data invoice_data.h invoice_data.cpp)
target_include_directories(invoice_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(invoice_data PRIVATE invoice_lib_v0)
