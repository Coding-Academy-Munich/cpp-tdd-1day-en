// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#ifndef LIB_GROUND_CONTROL_LINK_H
#define LIB_GROUND_CONTROL_LINK_H

#include <string>

class GroundControlLink
{
public:
    virtual ~GroundControlLink() = default;
    virtual void send_status_report(const std::string& report) = 0;
};

#endif // LIB_GROUND_CONTROL_LINK_H
