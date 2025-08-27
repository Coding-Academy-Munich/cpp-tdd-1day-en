add_library(invoice_lib_v3 invoice.cpp invoice.h)
target_include_directories(invoice_lib_v3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
