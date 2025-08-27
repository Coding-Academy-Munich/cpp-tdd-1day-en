#include <iostream>
#include <stdexcept>
#include "non_testable_order_processor.h"
#include "testable_order_processor.h"

void run_non_testable_order_processor()
{
    non_testable_order_processor_sk::OrderProcessor processor;
    try
    {
        processor.process_orders_from_file("orders.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error processing orders: " << e.what() << std::endl;
    }
}

void run_testable_order_processor()
{
    testable_order_processor_sk::OrderProcessor processor;
    try
    {
        processor.process_orders_from_file("orders.txt");
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error processing orders: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Running non-testable order processor\n"
              << "====================================\n\n";
    run_non_testable_order_processor();
    std::cout << "\nRunning testable order processor\n"
              << "================================\n\n";
    run_testable_order_processor();
    return 0;
}
