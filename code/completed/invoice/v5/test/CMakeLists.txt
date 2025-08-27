add_executable(invoice_test_v5 invoice_test.cpp)
target_link_libraries(invoice_test_v5 PRIVATE invoice_lib_v5)
target_link_libraries(invoice_test_v5 PRIVATE Catch2::Catch2WithMain)
