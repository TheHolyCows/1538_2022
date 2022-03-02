#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{
    m_TrackingCooldownTimer = 0.0;
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

    bool doingTracking = true;
    bool targetAcquired = false;

    if (m_CB->GetDriveButton(1))
    {
        // bot->DriveDistanceWithHeading(0, 12, 0.2);
        //bot->TurnToHeading(90);

        // doingTracking = true;
        // bool acquired = bot->DoVisionTracking(1,CONSTANT("TRACKING_THRESHOLD"));
        // if(acquired)
        // {
        // }
        // bot->GetShooter()->ZeroHoodPosition();
    }
    if (m_CB->GetSteeringButton(3))
    {
        doingTracking = true;

        bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_TRACKING);

        // set cooldown timer before calling the vision tracking function
        // let 0.5 seconds pass before attempting to move the robot
        // this allows the camera to adjust to the new contrast
        bool isValidTargets = bot->GetLimelight()->GetValidTargets();
        if (m_TrackingCooldownTimer/25.0 > 0.5 && isValidTargets == true)
        {
            targetAcquired = bot->DoVisionTracking(m_CB->GetDriveStickY(), CONSTANT("TRACKING_THRESHOLD"));
            //placeholder for hood adjustment
            int autoHoodPos = bot->GetLimelight()->CalcHoodPos();
            bot->GetShooter()->SetHoodPosition(autoHoodPos);
        }
        m_TrackingCooldownTimer += 1.0;
    }
    else
    {
        if (doingTracking)
        {
            m_TrackingCooldownTimer = 0.0;
            doingTracking = false;
            bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_VISUAL);

            // is this necessary?
            bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                                m_CB->GetSteeringX(),
                                m_CB->GetSteeringButton(FAST_TURN));
        }
    }

    // Intake Position Switches
    bot->GetIntakeF()->SetExtended(m_CB->GetOperatorButton(SWITCH_FRONT_INTAKE));
    bot->GetIntakeR()->SetExtended(m_CB->GetOperatorButton(SWITCH_REAR_INTAKE));

    // Resets variables to off but doesn't actually turn them off
    bot->ResetConveyorMode();
    bot->ResetIntakeMode(false);
    bot->ResetIntakeMode(true);

    // Whenever SetConveyorMode or SetIntakeMode are called, only changes the mode if new value is higher priority

    // Front Intake / Exhaust
    if (m_CB->GetOperatorButton(BUTTON_FRONT_INTAKE))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, false);
    }
    else if (m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST);
        bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false);
    }

    // Rear Intake / Exhaust
    if (m_CB->GetOperatorButton(BUTTON_REAR_INTAKE))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, true);
    }
    else if (m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST))
    {
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST);
        bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, true);
    }

    // Shooting
    if (m_CB->GetOperatorButton(BUTTON_SHOOT))
    {
        // secondary check if driver is holding down tracking button
        if (doingTracking)
        {
            if (targetAcquired)
            {
                bot->ShootBalls();
            }
        }
        else
        {
            bot->ShootBalls();
        }
    }

    // If nothing ever changed the conveyor or intake modes, sets them to off
    bot->SetConveyorMode(CowRobot::CONVEYOR_OFF);
    bot->SetIntakeMode(CowRobot::INTAKE_OFF, false);
    bot->SetIntakeMode(CowRobot::INTAKE_OFF, true);

    // Sets speed according to hood position
    if (m_CB->GetOperatorButton(SWITCH_SHOOTER))
    {
        // bot->RunShooter();
        bot->GetShooter()->SetSpeedHoodRelative();
    }
    else
    {
        bot->GetShooter()->SetSpeed(0);
    }

    if (m_CB->GetOperatorButton(BUTTON_HOOD_UP))
    {
        bot->GetShooter()->SetHoodPositionUp();
    }
    else if (m_CB->GetOperatorButton(BUTTON_HOOD_DOWN))
    {
        bot->GetShooter()->SetHoodPositionDown();
    }
}
