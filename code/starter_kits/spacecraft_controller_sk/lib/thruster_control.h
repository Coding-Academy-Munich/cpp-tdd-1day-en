// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_THRUSTER_CONTROL_H
#define LIB_THRUSTER_CONTROL_H

class ThrusterControl
{
public:
    virtual ~ThrusterControl() = default;
    virtual void fire_thrusters(int duration_ms) = 0;
};

#endif // LIB_THRUSTER_CONTROL_H
