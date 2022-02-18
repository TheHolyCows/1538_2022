#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
    float r_color = m_CB->GetOperatorGamepadAxis(2);
    r_color = fabs(r_color * 254);
    float g_color = m_CB->GetDriveAxis(2);
    g_color = fabs(g_color * 254);
    float b_color = m_CB->GetDriveAxis(0);
    b_color = fabs(b_color * 254);
    bot->GetCanifier()->SetLEDColor(r_color, g_color, b_color);
    bool doingTracking = false;
    if (m_CB->GetDriveButton(1))
    {
        bot->DriveDistanceWithHeading(0, 12, 0.2);
        //doingTracking = true;
        //bool acquired = bot->DoVisionTracking(-CONSTANT("AUTO_TRACK_SPEED"));
        //if(acquired)
        //{
        //}
    }
    else
    {
        if (m_CB->GetSteeringButton(3))
        {
            bot->DoVisionTracking(m_CB->GetDriveStickY());
        }
        else
        {
            bot->GetLimelight()->PutNumber("pipeline", 3);
            bot->GetLimelight()->PutNumber("ledMode", 1);
            bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                                m_CB->GetSteeringX(),
                                m_CB->GetSteeringButton(FAST_TURN));
        }
    }

    // Intake Position Switches
    bot->GetIntakeF()->SetExtended(m_CB->GetOperatorButton(2));
    bot->GetIntakeR()->SetExtended(m_CB->GetOperatorButton(3));

    // Intakes, Indexers, and Conveyor
    // If either exhaust button is pressed, call ExhaustBalls with the coresponding bools
    // TODO: come back to this logic - shooting while intaking is broken
    if (m_CB->GetOperatorButton(5) || m_CB->GetOperatorButton(7))
    {
        bot->ExhaustBalls(1, m_CB->GetOperatorButton(5), m_CB->GetOperatorButton(7));
    }
    else if (m_CB->GetOperatorButton(4) || m_CB->GetOperatorButton(6)) // Same as exhaust
    {
        bot->IntakeBalls(1, m_CB->GetOperatorButton(4), m_CB->GetOperatorButton(6));
    }
    else if (m_CB->GetOperatorButton(8)) // Shoot
    {
        bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_TEST")); // Temporary
        bot->ShootBalls();                                     // Stops intakes, runs indexers and conveyor
    }
    else
    {
        bot->GetShooter()->SetSpeed(0);
        bot->StopRollers();
    }

    if (m_CB->GetOperatorButton(11))
    {
        // Somehow get distance to target and calculate hood angle and shooter speed
        bot->GetShooter()->SetHoodPosition(0);
        bot->GetShooter()->SetSpeed(0);
    }

    // Climber
    if (m_CB->GetOperatorButton(12))
    {
        // Climb
    }

    // Shooter Switch
    // if (m_CB->GetOperatorButton(10))
    // {
    //     if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_GOAL"))
    //     {
    //         std::cout << CONSTANT("SHOOTER_F_GOAL") << std::endl;
    //         bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_GOAL")); //, CONSTANT("SHOOTER_B_GOAL"));
    //     }
    //     else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_MID"))
    //     {
    //         bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_MID"), CONSTANT("SHOOTER_B_MID"));
    //     }
    //     else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_FAR"))
    //     {
    //         bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_FAR"), CONSTANT("SHOOTER_B_FAR"));
    //     }
    //     else
    //     {
    //         bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_ON"), CONSTANT("SHOOTER_B_ON"));
    //     }
    // }
    // else
    // {
    //     bot->GetShooter()->SetSpeed(0);
    // }
}
