#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{
    m_TrackingCooldownTimer = 0.0;
    m_FlashCounter = 0;
    m_OffGround = false;
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
    bool targetAcquired = false;

    // No target = purple
    // Hood down no target = blue
    if (bot->GetShooter()->GetHoodPosition() == CONSTANT("HOOD_DOWN") && bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    {
        if (m_FlashCounter++ > CONSTANT("BLINK_SPEED"))
        {
            m_FlashCounter = -CONSTANT("BLINK_SPEED");
            bot->GetCanifier()->SetLEDColor(0, 0, 0);
        }
        else if (m_FlashCounter > 0)
        {
            bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_HOOD_DOWN_R"), CONSTANT("COLOR_HOOD_DOWN_G"), CONSTANT("COLOR_HOOD_DOWN_B"));
        }
    }
    else if (bot->GetLimelight()->TargetCentered() && bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    {
        if (m_FlashCounter++ > CONSTANT("BLINK_SPEED"))
        {
            m_FlashCounter = -CONSTANT("BLINK_SPEED");
            bot->GetCanifier()->SetLEDColor(0, 0, 0);
        }
        else if (m_FlashCounter > 0)
        {
            bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_ALIGNED_R"), CONSTANT("COLOR_ALIGNED_G"), CONSTANT("COLOR_ALIGNED_B"));
        }
    }
    else if (bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    {
        bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_SPEED_R"), CONSTANT("COLOR_SPEED_G"), CONSTANT("COLOR_SPEED_B"));
    }
    else
    {
        bot->GetCanifier()->SetLEDColor(0, 0, 0);
    }

    if (m_CB->GetDriveButton(1))
    {
        // bot->DriveDistanceWithHeading(0, 12, 0.2);
        // bot->TurnToHeading(90);

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
        if (m_TrackingCooldownTimer / 25.0 > 0.5 && isValidTargets == true)
        {
            targetAcquired = bot->DoVisionTracking(-m_CB->GetDriveStickY(), CONSTANT("TRACKING_THRESHOLD"));
            // placeholder for hood adjustment
            int autoHoodPos = bot->GetLimelight()->CalcHoodPosition();
            // bot->GetShooter()->SetHoodPosition(autoHoodPos);
        }
        m_TrackingCooldownTimer += 1.0;
    }
    else
    {
        if (doingTracking)
        {
            m_TrackingCooldownTimer = 0.0;
            doingTracking = false;
            // bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_VISUAL);
        }

        // TODO: Make this not dumb
        bot->DriveSpeedTurn(-m_CB->GetDriveStickY(),
                            -m_CB->GetSteeringX(),
                            m_CB->GetSteeringButton(FAST_TURN));
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
    else if (m_CB->GetSteeringButton(4))
    {
        // special driver exhaust
        if (bot->GetIntakeF()->GetExtended())
        {
            bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false);
        }
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
    else if (m_CB->GetSteeringButton(4))
    {
        // special driver exhaust
        if (bot->GetIntakeR()->GetExtended())
        {
            bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, true);
        }
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
        bot->RunShooter();
    }
    else
    {
        bot->GetShooter()->SetSpeed(0);
        bot->GetShooter()->SetHoodRollerSpeed(0);
    }

    if (m_CB->GetOperatorButton(BUTTON_HOOD_UP))
    {
        bot->GetShooter()->SetHoodPositionUp();
    }
    else if (m_CB->GetOperatorButton(BUTTON_HOOD_DOWN))
    {
        bot->GetShooter()->SetHoodPositionDown();
    }

    // Process would be switch, drive forwards, hold button

    // Raise the climber (switch???)
    if (false)
    {
        bot->GetClimber()->SetLockState(false);
        bot->GetClimber()->SetPosition(CONSTANT("CLIMBER_STAGE_ONE"));
    }
    else
    {
        bot->GetClimber()->SetLockState(true);
        bot->GetClimber()->SetPosition(0); // could change to CONSTANT("CLIMBER_MIN")
    }

    // Button you hold to go down
    if (false)
    {
        // problem: if bot is not limed up and this runs it will just start running pto (bad)

        // If not off ground, get there
        if (bot->GetClimber()->GetDistance() < CONSTANT("CLIMBER_OFF_GROUND"))
        {
            bot->GetClimber()->SetPosition(CONSTANT("CLIMBER_OFF_GROUND"));

            if (bot->GetClimber()->AtTarget())
            {
                m_OffGround = true;
                bot->EngagePTO();
            }
        }
        else
        {
            // If bot is off ground, go to final position fast

            bot->GetClimber()->SetPosition(CONSTANT("CLIMBER_FINAL"));

            if (bot->GetClimber()->AtTarget())
            {
                bot->DisengagePTO();
                bot->GetClimber()->SetLockState(true);

                // How do I stop it from trying to move
            }
        }
    }
}
