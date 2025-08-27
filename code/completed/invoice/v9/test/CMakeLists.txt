add_executable(invoice_test_v9 invoice_test.cpp)
target_link_libraries(invoice_test_v9 PRIVATE invoice_lib_v9)
target_link_libraries(invoice_test_v9 PRIVATE Catch2::Catch2WithMain)
