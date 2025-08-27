add_executable(invoice_test_v7 invoice_test.cpp)
target_link_libraries(invoice_test_v7 PRIVATE invoice_lib_v7)
target_link_libraries(invoice_test_v7 PRIVATE Catch2::Catch2WithMain)
