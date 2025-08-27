// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#pragma once
#ifndef LIB_SPACECRAFT_COMMAND_CONTROLLER_SK_H
#define LIB_SPACECRAFT_COMMAND_CONTROLLER_SK_H
#include "ground_control_link.h"
#include "telemetry_system.h"
#include "thruster_control.h"

namespace sc_sk
{
    class SpacecraftCommandController
    {
        TelemetrySystem& telemetry;
        ThrusterControl& thrusters;
        GroundControlLink& ground_control;

    public:
        SpacecraftCommandController(TelemetrySystem& tel, ThrusterControl& thr,
                                    GroundControlLink& gc);

        void execute_burn_maneuver(int duration_ms) const;
    };

} // namespace sc_sk
#endif // LIB_SPACECRAFT_COMMAND_CONTROLLER_SK_H
