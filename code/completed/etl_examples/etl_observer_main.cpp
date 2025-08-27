// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#include "etl_observer.h"

int main()
{
    StockMarket market;
    PrintingObserver observer1{"Printing Observer"};
    RisingPricesObserver observer2{"  Rising Observer"};
    FallingPricesObserver observer3{" Falling Observer"};

    market.add_observer(observer1);
    market.add_observer(observer2);
    market.add_observer(observer3);

    market.update_price(TickerSymbol::AAPL, 200.0);
    market.update_price(TickerSymbol::GOOG, 400.0);
    market.update_price(TickerSymbol::AAPL, 201.0);
    market.update_price(TickerSymbol::AAPL, 199.0);
    market.update_price(TickerSymbol::MSFT, 300.0);
    market.update_price(TickerSymbol::GOOG, 410.0);
    market.update_price(TickerSymbol::MSFT, 290.0);
    market.update_price(TickerSymbol::MSFT, 310.0);
}