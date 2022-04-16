#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{
    m_TrackingCooldownTimer = 0.0;
    m_FlashCounter = 0;
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
    bool validTargets = bot->GetLimelight()->GetValidTargets();
    bool targetAcquired = false;

    // No target = purple
    // Hood down no target = blue
    // if (bot->GetShooter()->GetHoodPosition() == CONSTANT("HOOD_DOWN") && bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    // {
    //     if (m_FlashCounter++ > CONSTANT("BLINK_SPEED"))
    //     {
    //         m_FlashCounter = -CONSTANT("BLINK_SPEED");
    //         // bot->GetCanifier()->SetLEDColor(0, 0, 0);
    //     }
    //     else if (m_FlashCounter > 0)
    //     {
    //         // bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_HOOD_DOWN_R"), CONSTANT("COLOR_HOOD_DOWN_G"), CONSTANT("COLOR_HOOD_DOWN_B"));
    //     }
    // }
    // else if (bot->GetLimelight()->TargetCentered() && bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    // {
    //     if (m_FlashCounter++ > CONSTANT("BLINK_SPEED"))
    //     {
    //         m_FlashCounter = -CONSTANT("BLINK_SPEED");
    //         // bot->GetCanifier()->SetLEDColor(0, 0, 0);
    //     }
    //     else if (m_FlashCounter > 0)
    //     {
    //         // bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_ALIGNED_R"), CONSTANT("COLOR_ALIGNED_G"), CONSTANT("COLOR_ALIGNED_B"));
    //     }
    // }
    // else if (bot->GetShooter()->GetSpeedF() > bot->GetShooter()->CalcShooterTolerance() && bot->GetShooter()->GetSetpointF() != 0)
    // {
    //     // bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_SPEED_R"), CONSTANT("COLOR_SPEED_G"), CONSTANT("COLOR_SPEED_B"));
    // }
    // else
    // {
    //     // bot->GetCanifier()->SetLEDColor(0, 0, 0);
    // }

    // if (m_CB->GetDriveButton(1))
    // {
    //     // bot->DriveDistanceWithHeading(0, 12, 0.2);
    //     // bot->TurnToHeading(90);

    //     // doingTracking = true;
    //     // bool acquired = bot->DoVisionTracking(1,CONSTANT("TRACKING_THRESHOLD"));
    //     // if(acquired)
    //     // {
    //     // }
    //     // bot->GetShooter()->ZeroHoodPosition();
    // }
    if (m_CB->GetSteeringButton(3))
    {
        doingTracking = true;

        bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_TRACKING);

        // set cooldown timer before calling the vision tracking function
        // let 0.5 seconds pass before attempting to move the robot
        // this allows the camera to adjust to the new contrast
        if (m_TrackingCooldownTimer / 25.0 > 0.5 && validTargets == true)
        {
            targetAcquired = bot->DoVisionTracking(-m_CB->GetDriveStickY(), CONSTANT("TRACKING_THRESHOLD"));
        }
        else
        {
        }

        m_TrackingCooldownTimer += 1.0;
    }
    else
    {
        if (doingTracking)
        {
            m_TrackingCooldownTimer = 0.0;
            doingTracking = false;
            bot->GetLimelight()->ClearXFilter();
            // bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_VISUAL);
        }
        if (!m_CB->GetOperatorButton(SWITCH_CLIMBER))
        {
            bot->DriveSpeedTurn(-m_CB->GetDriveStickY(),
                                -m_CB->GetSteeringX(),
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
        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE, m_ExhaustMode);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, false);
    }
    else if (m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST) && !m_CB->GetOperatorButton(SWITCH_CLIMBER))
    {
        m_ExhaustMode = false;
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST, m_ExhaustMode);
        bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false);
    }
    else if (m_CB->GetSteeringButton(4))
    {
        // special driver exhaust
        // TODO: this
        if (bot->GetIntakeF()->GetExtended())
        {
            bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false);
        }
    }

    // Rear Intake / Exhaust
    if (m_CB->GetOperatorButton(BUTTON_REAR_INTAKE))
    {
        // bot->IntakeWithAutoExhaust(true);

        bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE,m_ExhaustMode);
        bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, true);
    }
    else if (m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST) && !m_CB->GetOperatorButton(SWITCH_CLIMBER))
    {
        m_ExhaustMode = true;
        bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST, m_ExhaustMode);
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
    if (m_CB->GetOperatorButton(BUTTON_SHOOT) && !m_CB->GetOperatorButton(SWITCH_CLIMBER))
    {
        bot->ShootBalls();
    }

    // Sets speed according to hood position
    if (m_CB->GetOperatorButton(SWITCH_SHOOTER))
    {
        if (!m_HoodOverride)
        {
            // hood adjustment
            float yPercent = bot->GetLimelight()->CalcYPercent();
            float hoodDelta = CONSTANT("TARGET_Y_FAR") - CONSTANT("TARGET_Y_CLOSE");
            float autoHoodPos = CONSTANT("TARGET_Y_FAR") - (hoodDelta * yPercent);

            bot->GetShooter()->SetHoodPosition(autoHoodPos);
        }
        bot->RunShooter();
    }
    else if (m_CB->GetOperatorButton(BUTTON_HOOD_BOTTOM))
    {
        // because of the weird speeds here this is special
        bot->GetShooter()->SetHoodPositionBottom();
        bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_BOTTOM"));
        bot->GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_BOTTOM"));
        bot->ShootBalls();
    }
    else
    {
        m_HoodOverride = false;
        bot->GetShooter()->SetSpeed(0);
        bot->GetShooter()->SetHoodRollerSpeed(0);
        bot->GetLimelight()->ClearYFilter();
    }

    if (m_CB->GetOperatorButton(BUTTON_HOOD_UP))
    {
        m_HoodOverride = true;
        bot->GetShooter()->SetHoodPositionUp();
    }
    else if (m_CB->GetOperatorButton(BUTTON_HOOD_DOWN))
    {
        m_HoodOverride = true;
        bot->GetShooter()->SetHoodPositionDown();
    }

    // Climber

    // switch -> rear -> front -> shoot

    if (m_CB->GetOperatorButton(SWITCH_CLIMBER))
    {
        bot->GetClimber()->SetLeftPosition(m_CB->GetDriveStickY());
        bot->GetClimber()->SetRightPosition(m_CB->GetOperatorGamepadAxis(1));
        
        // if (!m_PrevClimberSwitch)
        // {
            
        //     bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_MID_RUNG"));
        //     // bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_MID_RUNG")-2000);
        //     bot->GetShooter()->SetHoodPositionDown();
        // }

        // if (m_CB->GetOperatorButton(BUTTON_REAR_EXHAUST))
        // {
        //     bot->GetClimber()->SetLeftPosition(CONSTANT("CLIMBER_IN"));
        //     if (bot->GetClimber()->GetLeftPosition() < CONSTANT("CLIMBER_OUT") * CONSTANT("CLIMB_DELAY_1"))
        //     {
        //         bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_OUT"));
        //     }
        // }
        // else if (m_CB->GetOperatorButton(BUTTON_FRONT_EXHAUST))
        // {
        //     bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_IN"));
        //     if (bot->GetClimber()->GetRightPosition() < CONSTANT("CLIMBER_OUT") * CONSTANT("CLIMB_DELAY_2"))
        //     {
        //         bot->GetClimber()->SetLeftPosition(CONSTANT("CLIMBER_OUT"));
        //     }
        // }
        // else if (m_CB->GetOperatorButton(BUTTON_SHOOT))
        // {
        //     bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_MID"));
        //     // bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_MID")-2000);
        // }
    }
    else if (m_PrevClimberSwitch)
    {
        bot->GetClimber()->SetLeftPosition(CONSTANT("CLIMBER_IN"));
        bot->GetClimber()->SetRightPosition(CONSTANT("CLIMBER_IN"));
    }

    m_PrevClimberSwitch = m_CB->GetOperatorButton(SWITCH_CLIMBER);

    // If nothing ever changed the conveyor or intake modes, sets them to off
    bot->SetConveyorMode(CowRobot::CONVEYOR_OFF, m_ExhaustMode);
    bot->SetIntakeMode(CowRobot::INTAKE_OFF, false);
    bot->SetIntakeMode(CowRobot::INTAKE_OFF, true);
}
