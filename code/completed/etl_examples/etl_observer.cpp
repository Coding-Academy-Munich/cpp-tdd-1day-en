// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "etl_observer.h"

void PrintingObserver::notification(StockPrice price)
{
    std::cout << name << " received price update for "
              << get_ticker_symbol_name(price.symbol) << " at " << price.price << "\n";
}

void RisingPricesObserver::notification(StockPrice price)
{
    auto old_price_iter = prices.find(price.symbol);
    if (old_price_iter == prices.end())
    {
        std::cout << name << " received price update for "
                  << get_ticker_symbol_name(price.symbol) << " at " << price.price
                  << " (no previous price)\n";
    }
    else if (price.price > old_price_iter->second)
    {
        std::cout << name << " received price update for "
                  << get_ticker_symbol_name(price.symbol) << " at " << price.price
                  << " (was " << old_price_iter->second << ")\n";
    }
    prices[price.symbol] = price.price;
}

void FallingPricesObserver::notification(StockPrice price)
{
    auto old_price_iter = prices.find(price.symbol);
    if (old_price_iter == prices.end())
    {
        std::cout << name << " received price update for "
                  << get_ticker_symbol_name(price.symbol) << " at " << price.price
                  << " (no previous price)\n";
    }
    else if (price.price < old_price_iter->second)
    {
        std::cout << name << " received price update for "
                  << get_ticker_symbol_name(price.symbol) << " at " << price.price
                  << " (was " << old_price_iter->second << ")\n";
    }
    prices[price.symbol] = price.price;
}
