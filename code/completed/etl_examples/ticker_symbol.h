// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_ETL_EXAMPLES_TICKER_SYMBOL_H
#define COMPLETED_ETL_EXAMPLES_TICKER_SYMBOL_H

#include "etl/hash.h"

#define TICKER_SYMBOL(symbol) symbol,

enum class TickerSymbol {
#include "ticker_symbols.inc"
};

#undef TICKER_SYMBOL

template <>
struct etl::hash<TickerSymbol> {
    constexpr size_t operator()(TickerSymbol symbol) const
    {
        return static_cast<size_t>(symbol);
    }
};

#define TICKER_SYMBOL(symbol) #symbol,

constexpr const char* ticker_symbol_names[]{
#include "ticker_symbols.inc"
};

#undef TICKER_SYMBOL

constexpr int num_ticker_symbols{
    sizeof ticker_symbol_names / sizeof ticker_symbol_names[0]
};

constexpr const char* get_ticker_symbol_name(TickerSymbol symbol)
{
    const int index{static_cast<int>(symbol)};
    assert(index >= 0 && index < num_ticker_symbols);
    return ticker_symbol_names[index];
}

#endif // COMPLETED_ETL_EXAMPLES_TICKER_SYMBOL_H
