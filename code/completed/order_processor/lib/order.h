#pragma once
#ifndef ORDER_PROCESSOR_LIB_ORDER_H
#define ORDER_PROCESSOR_LIB_ORDER_H

#include <string>

namespace order_processor
{
    struct Order
    {
        std::string customer_type; // "premium", "regular"
        std::string product;
        int quantity;
        double unit_price;
        double total_price;
        bool is_valid;
    };

} // namespace order_processor
#endif // ORDER_PROCESSOR_LIB_ORDER_H
