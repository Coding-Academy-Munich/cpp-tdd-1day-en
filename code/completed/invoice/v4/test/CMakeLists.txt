add_executable(invoice_test_v4 invoice_test.cpp)
target_link_libraries(invoice_test_v4 PRIVATE invoice_lib_v4)
target_link_libraries(invoice_test_v4 PRIVATE Catch2::Catch2WithMain)
