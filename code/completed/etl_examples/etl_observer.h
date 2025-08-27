// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ETL_EXAMPLES_ETL_OBSERVER_H
#define COMPLETED_ETL_EXAMPLES_ETL_OBSERVER_H

#include "etl/array.h"
#include "etl/observer.h"
#include "etl/unordered_map.h"
#include "ticker_symbol.h"
#include <iostream>

constexpr int num_observers{3};

struct StockPrice {
    TickerSymbol symbol;
    double price;
};

using StockObserver = etl::observer<StockPrice>;

class StockMarket : public etl::observable<StockObserver, num_observers>
{
public:
    void update_price(TickerSymbol symbol, double price)
    {
        prices[symbol] = price;
        notify_observers<StockPrice>({symbol, price});
    }

private:
    etl::unordered_map<TickerSymbol, double, num_ticker_symbols> prices;
};

class PrintingObserver : public StockObserver
{
public:
    PrintingObserver(const std::string& name) : name{name} {}
    void notification(StockPrice price) override;

private:
    std::string name;
};

class RisingPricesObserver : public StockObserver
{
public:
    RisingPricesObserver(const std::string& name) : name{name} {}
    void notification(StockPrice price) override;

private:
    std::string name;
    etl::unordered_map<TickerSymbol, double, num_ticker_symbols> prices;
};

class FallingPricesObserver : public StockObserver
{
public:
    FallingPricesObserver(const std::string& name) : name{name} {}
    void notification(StockPrice price) override;

private:
    std::string name;
    etl::unordered_map<TickerSymbol, double, num_ticker_symbols> prices;
};

#endif // COMPLETED_ETL_EXAMPLES_ETL_OBSERVER_H
