#pragma once
#ifndef ORDER_PROCESSOR_SK_LIB_TESTABLE_ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_SK_LIB_TESTABLE_ORDER_PROCESSOR_H

#include "order.h"

namespace testable_order_processor_sk
{

class OrderProcessor
{
public:
    void process_orders_from_file(const std::string& file_path);

private:
    order_processor_sk::Order parse_order_line(const std::string& line);
    double calculate_discount(const std::string& customer_type, int quantity);
    bool check_inventory(const std::string& product, int quantity);
    void save_order_to_database(const order_processor_sk::Order& order);
    void update_inventory(const std::string& product, int quantity);
};


} // namespace testable_order_processor_sk
#endif // ORDER_PROCESSOR_SK_LIB_TESTABLE_ORDER_PROCESSOR_H
