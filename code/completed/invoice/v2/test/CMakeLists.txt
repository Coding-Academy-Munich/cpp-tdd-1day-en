add_executable(invoice_test_v2 invoice_test.cpp)
target_link_libraries(invoice_test_v2 PRIVATE invoice_lib_v2)
target_link_libraries(invoice_test_v2 PRIVATE Catch2::Catch2WithMain)
