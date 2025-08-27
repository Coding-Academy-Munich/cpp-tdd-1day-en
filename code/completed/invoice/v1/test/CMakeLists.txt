add_executable(invoice_test_v1 invoice_test.cpp)
target_link_libraries(invoice_test_v1 PRIVATE invoice_lib_v1)
target_link_libraries(invoice_test_v1 PRIVATE Catch2::Catch2WithMain)
