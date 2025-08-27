add_executable(invoice_test_v3 invoice_test.cpp)
target_link_libraries(invoice_test_v3 PRIVATE invoice_lib_v3)
target_link_libraries(invoice_test_v3 PRIVATE Catch2::Catch2WithMain)
