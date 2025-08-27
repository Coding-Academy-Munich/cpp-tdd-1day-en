add_executable(invoice_test_v0 invoice_test.cpp)
target_link_libraries(invoice_test_v0 PRIVATE invoice_lib_v0)
target_link_libraries(invoice_test_v0 PRIVATE Catch2::Catch2WithMain)
