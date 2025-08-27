// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef ACTION_H
#define ACTION_H
#include <string>

namespace adv
{

class Action
{
public:
    virtual ~Action() = default;

private:
    virtual bool equals(const Action& rhs) const;
    friend bool operator==(const Action& lhs, const Action& rhs);
};

bool operator==(const Action& lhs, const Action& rhs);

class MoveAction : public Action
{
public:
    explicit MoveAction(const std::string& direction);

private:
    std::string direction_;
    bool equals(const Action& rhs) const override;
};

} // namespace adv

#endif // ACTION_H
