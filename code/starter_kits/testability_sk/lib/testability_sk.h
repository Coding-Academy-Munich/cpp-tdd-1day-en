// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_TESTABILITY_SK_H
#define LIB_TESTABILITY_SK_H

namespace testability_sk
{
    int count();

    enum class State
    {
        OFF,
        ON
    };

    class Switch
    {
    public:
        void toggle();

    private:
        State state_{State::OFF};
    };

    void print_fib(int n);

} // namespace testability_sk
#endif // LIB_TESTABILITY_SK_H
