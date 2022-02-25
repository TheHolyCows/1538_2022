#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
    // float r_color = m_CB->GetOperatorGamepadAxis(2);
    // r_color = fabs(r_color * 254);
    // float g_color = m_CB->GetDriveAxis(2);
    // g_color = fabs(g_color * 254);
    // float b_color = m_CB->GetDriveAxis(0);
    // b_color = fabs(b_color * 254);
    // bot->GetCanifier()->SetLEDColor(r_color, g_color, b_color);

    bool doingTracking = false;
    if (m_CB->GetDriveButton(1))
    {
        bot->DriveDistanceWithHeading(0, 12, 0.2);
        // doingTracking = true;
        // bool acquired = bot->DoVisionTracking(-CONSTANT("AUTO_TRACK_SPEED"));
        // if(acquired)
        // {
        // }
    }
    else
    {
        if (m_CB->GetSteeringButton(3))
        {
            // bot->DoVisionTracking(m_CB->GetDriveStickY());
        }
        else
        {
            // bot->GetLimelight()->PutNumber("pipeline", 3);
            // bot->GetLimelight()->PutNumber("ledMode", 1);
            bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                                m_CB->GetSteeringX(),
                                m_CB->GetSteeringButton(FAST_TURN));
        }
    }

    // Intake Position Switches
    bot->GetIntakeF()->SetExtended(m_CB->GetOperatorButton(SWITCH_FRONT_INTAKE));
    bot->GetIntakeR()->SetExtended(m_CB->GetOperatorButton(SWITCH_REAR_INTAKE));

    // Front Intake / Exhaust
    if (m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST);
        bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false);
    }
    else if (m_CB->GetOperatorButton(BUTTON_FRONT_INTAKE))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, false);
    }

    // Rear Intake / Exhaust
    if (m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST);
        bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, true);
    }
    else if (m_CB->GetOperatorButton(BUTTON_REAR_INTAKE))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, true);
    }

    // Shooting
    if (m_CB->GetOperatorButton(BUTTON_SHOOT))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_SHOOT);
        bot->SetIntakeMode(CowRobot::INTAKE_SHOOT, false);
        bot->SetIntakeMode(CowRobot::INTAKE_SHOOT, true);
    }

    // Sets speed according to hood position
    if (m_CB->GetOperatorButton(SWITCH_SHOOTER))
    {
        bot->RunShooter();
    }
    else
    {
        bot->GetShooter()->SetSpeed(0);
    }

    if (m_CB->GetOperatorButton(BUTTON_HOOD_UP))
    {
        bot->GetShooter()->SetHoodPosition(CONSTANT("HOOD_UP"));
    }
    else if (m_CB->GetOperatorButton(BUTTON_HOOD_DOWN))
    {
        bot->GetShooter()->SetHoodPosition(CONSTANT("HOOD_DOWN"));
    }
}
