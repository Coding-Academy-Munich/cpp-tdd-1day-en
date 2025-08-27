// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef ORDER_PROCESSOR_LIB_TESTABLE_ORDER_PROCESSOR_H
#define ORDER_PROCESSOR_LIB_TESTABLE_ORDER_PROCESSOR_H

#include <memory>
#include "order.h"

namespace testable_order_processor
{

class IInventoryService
{
public:
    virtual ~IInventoryService() = default;
    virtual bool check_inventory(const std::string& product, int quantity) = 0;
    virtual void update_inventory(const std::string& product, int quantity) = 0;
};

class IOrderRepository
{
public:
    virtual ~IOrderRepository() = default;
    virtual void save_order_to_database(const order_processor::Order& order) = 0;
};

class OrderService
{
public:
    OrderService(std::unique_ptr<IInventoryService> inventory_service,
                 std::unique_ptr<IOrderRepository> order_service);
    void process_order(order_processor::Order& order) const;

private:
    std::unique_ptr<IInventoryService> inventory_service_;
    std::unique_ptr<IOrderRepository> order_service_;

    static double calculate_discount(const std::string& customer_type,
                                     int quantity);
};

class OrderProcessor
{
public:
    OrderProcessor();
    explicit OrderProcessor(std::unique_ptr<OrderService> order_service);

    void process_orders_from_file(const std::string& file_path) const;

private:
    std::unique_ptr<OrderService> order_service_;
    static order_processor::Order parse_order_line(const std::string& line);
};

class DefaultInventoryService : public IInventoryService
{
    bool check_inventory(const std::string& product, int quantity) override;
    void update_inventory(const std::string& product, int quantity) override;
};

class DefaultOrderRepository : public IOrderRepository
{
    void save_order_to_database(const order_processor::Order& order) override;
};

} // namespace testable_order_processor
#endif // ORDER_PROCESSOR_LIB_TESTABLE_ORDER_PROCESSOR_H
