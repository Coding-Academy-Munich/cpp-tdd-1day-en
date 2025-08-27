// Copyright (c) 2025 Dr. Matthias Hölzl. All rights reserved.

#include <iostream>

#include "spacecraft_command_controller.h"


namespace sc_sk
{

    SpacecraftCommandController::SpacecraftCommandController(
        TelemetrySystem& tel, ThrusterControl& thr, GroundControlLink& gc) :
        telemetry{tel}, thrusters{thr}, ground_control{gc}
    {
    }

    void SpacecraftCommandController::execute_burn_maneuver(int duration_ms) const
    {
        int power_level{telemetry.get_power_level_percent(SubSystem::thrusters)};
        if (power_level < 50)
        {
            ground_control.send_status_report(
                "ERROR: Thruster power too low for maneuver.");
            return;
        }

        thrusters.fire_thrusters(duration_ms);
        ground_control.send_status_report("SUCCESS: Maneuver executed.");
    }
} // namespace sc_sk
