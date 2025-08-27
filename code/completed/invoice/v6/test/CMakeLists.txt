add_executable(invoice_test_v6 invoice_test.cpp)
target_link_libraries(invoice_test_v6 PRIVATE invoice_lib_v6)
target_link_libraries(invoice_test_v6 PRIVATE Catch2::Catch2WithMain)
