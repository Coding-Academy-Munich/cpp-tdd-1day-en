add_executable(invoice_test_v8 invoice_test.cpp)
target_link_libraries(invoice_test_v8 PRIVATE invoice_lib_v8)
target_link_libraries(invoice_test_v8 PRIVATE Catch2::Catch2WithMain)
