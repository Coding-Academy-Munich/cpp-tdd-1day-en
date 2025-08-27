// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_TELEMETRY_SYSTEM_H
#define LIB_TELEMETRY_SYSTEM_H

enum class SubSystem
{
    core,
    thrusters,
    science_bay,
};

class TelemetrySystem
{
public:
    virtual ~TelemetrySystem() = default;
    virtual int get_power_level_percent(SubSystem system) = 0;
};

#endif // LIB_TELEMETRY_SYSTEM_H
