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

    // Intakes, Indexers, and Conveyor
    // If either exhaust button is pressed, call ExhaustBalls with the coresponding bools
    // TODO: come back to this logic - shooting while intaking is impossible
    // front exhaust and rear exhaust
    if (m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST) || m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST))
    {
        bot->ExhaustBalls(1, m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST), m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST));
    }
    else if (m_CB->GetOperatorButton(BUTTON_SHOOT)) // Shoot
    {
        bot->ShootBalls(); // Stops intakes, runs indexers and conveyor

        // Intake while shooting
        if (m_CB->GetOperatorButton(BUTTON_FRONT_INTAKE) || m_CB->GetOperatorButton(BUTTON_REAR_INTAKE))
        {
            bot->GetIntakeF()->SetIntakeSpeed(CONSTANT("INTAKE_ON"));
            bot->GetIntakeR()->SetIntakeSpeed(CONSTANT("INTAKE_ON"));
        }
    }
    // front intake or rear intake
    else if (m_CB->GetOperatorButton(BUTTON_FRONT_INTAKE) || m_CB->GetOperatorButton(BUTTON_REAR_INTAKE)) // Same as exhaust
    {
        bot->IntakeBalls(1, m_CB->GetOperatorButton(BUTTON_FRONT_INTAKE), m_CB->GetOperatorButton(BUTTON_REAR_INTAKE));
    }
    else
    {
        bot->StopRollers();
    }

    if (m_CB->GetOperatorButton(SWITCH_SHOOTER))
    {
        if (bot->GetShooter()->GetSetpointH() == CONSTANT("HOOD_DOWN"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_DOWN"));
        }
        else if (bot->GetShooter()->GetSetpointH() == CONSTANT("HOOD_UP"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_UP"));
        }
        else
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_DOWN"));
        }
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
