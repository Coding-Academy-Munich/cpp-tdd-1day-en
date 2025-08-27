// Copyright (c) 2024 Dr. Matthias Hölzl. All rights reserved.

#ifndef COMPLETED_TEST_EXAMPLES_STATE_MACHINE_H
#define COMPLETED_TEST_EXAMPLES_STATE_MACHINE_H

#include <iostream>

// State transitions:
//
// Initial        -insert_coin->  CoinInserted  -select_drink-> DrinkDelivered
// Initial        -select_drink-> DrinkSelected -insert_coin->  DrinkDelivered
// DrinkDelivered -take_drink->   Initial

enum class State
{
    Initial,
    CoinInserted,
    DrinkSelected,
    DrinkDelivered,
};

class StateMachine
{
public:
    StateMachine() : state_{State::Initial} {}

    void insert_coin()
    {
        if (state_ == State::Initial)
        {
            state_ = State::CoinInserted;
        }
        else if (state_ == State::DrinkSelected)
        {
            state_ = State::DrinkDelivered;
        }
    }

    void select_drink()
    {
        if (state_ == State::Initial)
        {
            state_ = State::DrinkSelected;
        }
        else if (state_ == State::CoinInserted)
        {
            state_ = State::DrinkDelivered;
        }
    }

    void take_drink()
    {
        if (state_ == State::DrinkDelivered)
        {
            std::cout << "Enjoy your drink!" << std::endl;
            state_ = State::Initial;
        }
    }

private:
    State state_{State::Initial};
};

class StateNotifier
{
public:
    virtual void notify(State state) = 0;
};

class ObservableStateMachine
{
public:
    ObservableStateMachine(StateNotifier& notifier) : notifier_{notifier} {}

    void insert_coin()
    {
        if (state_ == State::Initial)
        {
            state_ = State::CoinInserted;
            notifier_.notify(state_);
        }
        else if (state_ == State::DrinkSelected)
        {
            state_ = State::DrinkDelivered;
            notifier_.notify(state_);
        }
    }

    void select_drink()
    {
        if (state_ == State::Initial)
        {
            state_ = State::DrinkSelected;
            notifier_.notify(state_);
        }
        else if (state_ == State::CoinInserted)
        {
            state_ = State::DrinkDelivered;
            notifier_.notify(state_);
        }
    }

    void take_drink()
    {
        if (state_ == State::DrinkDelivered)
        {
            std::cout << "Enjoy your drink!" << std::endl;
            state_ = State::Initial;
            notifier_.notify(state_);
        }
    }

private:
    StateNotifier& notifier_;
    State state_{State::Initial};
};

#endif // COMPLETED_TEST_EXAMPLES_STATE_MACHINE_H
