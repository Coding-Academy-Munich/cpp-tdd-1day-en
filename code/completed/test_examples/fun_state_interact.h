// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef COMPLETED_TEST_EXAMPLES_FUN_STATE_INTERACT_H
#define COMPLETED_TEST_EXAMPLES_FUN_STATE_INTERACT_H

#include <iostream>
// Very easy to test: pure function
int add(int x, int y) { return x + y; }

// OK to test: stateful class with access to required state
class Adder
{
public:
    Adder(int result = 0) : result_{result} {}

    void add(int x, int y) { result_ = x + y; }
    int get_result() const { return result_; }

private:
    int result_;
};

// More difficult to test: class that interacts with another class
// without access to state, but with interface that can be mocked
class AbstractAdder
{
public:
    virtual void add(int x, int y) = 0;
};

class InteractionAdder
{
public:
    InteractionAdder(AbstractAdder& adder) : adder_{adder} {}

    void add(int x, int y) { adder_.add(x, y); }

private:
    AbstractAdder& adder_;
};

// Very difficult to test: functions or classes that only have side effects that are not
// accessible as states.

void add_and_print(int x, int y) { std::cout << x + y << std::endl; }

#endif // COMPLETED_TEST_EXAMPLES_FUN_STATE_INTERACT_H
