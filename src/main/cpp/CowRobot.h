//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include "CowLib/CowLogger.h"
#include <frc/DriverStation.h>
#include <frc/PowerDistribution.h>
#include <frc/BuiltInAccelerometer.h>
#include <cameraserver/CameraServer.h>
#include "Controllers/GenericController.h"
#include "CowLib/CowLib.h"
#include "CowControlBoard.h"
#include "frc/CounterBase.h"
#include "CowConstants.h"
#include "CowLib/CowAlphaNum.h"
#include "CowGyro.h"
#include "CowLib/CowMotorController.h"
#include "CowLib/CowCanifier.h"
#include "CowLib/CowLPF.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "Subsystems/Arm.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Conveyor.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Limelight.h"

class CowRobot
{
public:
    enum ConveyorMode
    {
        CONVEYOR_OFF = 0,
        CONVEYOR_EXHAUST = 1,
        CONVEYOR_INTAKE = 2,
        CONVEYOR_SHOOT = 3
    };

    enum IntakeMode
    {
        INTAKE_OFF = 0,
        INTAKE_EXHAUST = 1,
        INTAKE_SHOOT = 2,
        INTAKE_INTAKE = 3
    };

private:
    int m_DSUpdateCount;

    GenericController *m_Controller;

    // Drive Motors
    CowLib::CowMotorController *m_LeftDriveA;
    CowLib::CowMotorController *m_LeftDriveB;

    CowLib::CowMotorController *m_RightDriveA;
    CowLib::CowMotorController *m_RightDriveB;

    CowLib::CowGyro *m_Gyro;

    frc::PowerDistribution *m_PowerDistributionPanel;

    CowLib::CowAlphaNum *m_LEDDisplay;
    CowLib::CowLogger *m_WebServer;

    Intake *m_IntakeF;
    Intake *m_IntakeR;
    Conveyor *m_Conveyor;
    Shooter *m_Shooter;
    Climber *m_Climber;
    Limelight *m_Limelight;
    CowLib::CowCanifier *m_Canifier;

    ConveyorMode m_ConveyorMode;
    IntakeMode m_IntakeModeF;
    IntakeMode m_IntakeModeR;

    float m_LeftDriveValue;
    float m_RightDriveValue;

    double m_PreviousGyroError;
    double m_PreviousDriveError;

    double m_MatchTime;
    double m_StartTime;

    void SetLeftMotors(float val);
    void SetRightMotors(float val);

    frc::Accelerometer *m_Accelerometer;

    CowLib::CowLPF *m_AccelY_LPF;
    CowLib::CowLPF *m_LoadDetect_LPF;

    float m_TipTime;
    bool m_Tipping;
    frc::CameraServer *m_CameraServer;
    cs::UsbCamera *m_UsbCamera;

    // logging
    CowLib::CowLogger *m_LogServer;

public:
    CowRobot();
    void Reset();
    void GyroHandleCalibration();
    void GyroFinalizeCalibration();
    void SetController(GenericController *controller);
    void PrintToDS();
    bool DoVisionTracking(float speed, float threshold = 5.0);
    double GetDriveDistance();
    bool DriveDistance(double distance);
    bool DriveDistanceWithHeading(double heading, double distance, double speed);
    bool DriveWithHeading(double heading, double speed);
    bool DriveWithHeading(double heading, double speed, double maxSpeed);
    void DriveSpeedTurn(float speed, float turn, bool quickTurn);
    void DriveLeftRight(float leftDriveValue, float rightDriveValue);
    bool TurnToHeading(double heading);

    void QuickTurn(float turn);

    void StartTime();

    CowLib::CowAlphaNum *GetDisplay()
    {
        return m_LEDDisplay;
    }

    frc::PowerDistribution *GetPowerDistributionPanel()
    {
        return m_PowerDistributionPanel;
    }

    CowLib::CowGyro *GetGyro()
    {
        return CowLib::CowGyro::GetInstance();
    }

    Intake *GetIntakeF()
    {
        return m_IntakeF;
    }
    Intake *GetIntakeR()
    {
        return m_IntakeR;
    }
    Conveyor *GetConveyor()
    {
        return m_Conveyor;
    }
    Shooter *GetShooter()
    {
        return m_Shooter;
    }
    Climber *GetClimber()
    {
        return m_Climber;
    }
    Limelight *GetLimelight()
    {
        return m_Limelight;
    }
    CowLib::CowCanifier *GetCanifier()
    {
        return m_Canifier;
    }

    // Sets the conveyor mode the new mode if the new mode is higher priority
    void SetConveyorMode(ConveyorMode newMode, double percentage = 1.0)
    {
        // Only changes the conveyor mode if the new mode is higher priority
        if (m_ConveyorMode < newMode)
        {
            m_ConveyorMode = newMode;
        }

        switch (m_ConveyorMode)
        {
        case CONVEYOR_OFF:
            GetConveyor()->SetSpeed(0, 0, 0);
            break;
        case CONVEYOR_EXHAUST:
            GetConveyor()->SetSpeed(-CONSTANT("CONVEYOR_OUT_UP") * percentage, -CONSTANT("CONVEYOR_OUT_LOW") * percentage, -CONSTANT("CONVEYOR_OUT_LOW") * percentage);
            break;
        case CONVEYOR_INTAKE:
            // add auto exhaust
            GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_IN_UP") * percentage, CONSTANT("CONVEYOR_IN_LOW") * percentage, CONSTANT("CONVEYOR_IN_LOW") * percentage);
            break;
        case CONVEYOR_SHOOT:
            GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_SHOOT_UP") * percentage, CONSTANT("CONVEYOR_SHOOT_LOW") * percentage, CONSTANT("CONVEYOR_SHOOT_LOW") * percentage);
            break;
        }
    }

    // Sets the intake mode the new mode if the new mode is higher priority
    void SetIntakeMode(IntakeMode newMode, bool rear, double percentage = 1.0)
    {
        // Creates pointers to the intake and intake mode coresponding to the selected side
        Intake *intake = NULL;
        IntakeMode *intakeMode = NULL;

        if (rear)
        {
            intake = GetIntakeR();
            intakeMode = &m_IntakeModeR;
        }
        else
        {
            intake = GetIntakeF();
            intakeMode = &m_IntakeModeF;
        }

        // Only changes the intake mode if the new mode is higher priority
        if (*intakeMode < newMode)
        {
            *intakeMode = newMode;
        }

        switch (*intakeMode)
        {
        case INTAKE_OFF:
            intake->SetSpeed(0, 0);
            break;
        case INTAKE_EXHAUST:
            intake->SetSpeed(-CONSTANT("INTAKE_ON") * percentage, -CONSTANT("INDEXER_ON") * percentage);
            break;
        case INTAKE_SHOOT:
            intake->SetSpeed(0, 0);
            break;
        case INTAKE_INTAKE:
            intake->SetSpeed(CONSTANT("INTAKE_ON") * percentage, CONSTANT("INDEXER_ON") * percentage);
            break;
        }
    }

    // Sets conveyor mode to off without actually stoping conveyor
    void ResetConveyorMode()
    {
        m_ConveyorMode = CONVEYOR_OFF;
    }

    // Sets intake mode to off without actually stoping intake
    void ResetIntakeMode(bool rear)
    {
        if (rear)
        {
            m_IntakeModeR = INTAKE_OFF;
        }
        else
        {
            m_IntakeModeF = INTAKE_OFF;
        }
    }

    void IntakeWithAutoExhaust(bool rear)
    {
        bool red = frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kRed;

        // not sure why the function returns an int
        // int freq = m_Conveyor->GetColorSensor()->GetFrequency();

        SetIntakeMode(IntakeMode::INTAKE_INTAKE, rear);

        // If correct color
        // if (freq in red range)
        if (true)
        {
            SetIntakeMode(IntakeMode::INTAKE_OFF, !rear);
            SetConveyorMode(ConveyorMode::CONVEYOR_INTAKE);
        }
        else
        {
            SetIntakeMode(IntakeMode::INTAKE_EXHAUST, !rear);

            if (rear)
            {
                GetConveyor()->SetSpeed(0, CONSTANT("CONVEYOR_OUT_LOW"), CONSTANT("CONVEYOR_IN_LOW"));
            }
            else
            {
                GetConveyor()->SetSpeed(0, CONSTANT("CONVEYOR_IN_LOW"), CONSTANT("CONVEYOR_OUT_LOW"));
            }
        }
    }

    // Waits for shooter speed tolerance, then sets conveyor and intake to shoot
    void ShootBalls()
    {
        // std::cout << "shooter F: " << GetShooter()->GetSpeedF() << std::endl;
        // std::cout << "comparator: " << fabs(GetShooter()->GetSpeedF() - GetShooter()->GetSetpointF()) << std::endl;

        SetConveyorMode(CONVEYOR_SHOOT);
        SetIntakeMode(INTAKE_SHOOT, false);
        SetIntakeMode(INTAKE_SHOOT, true);

        // if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_DOWN"))
        // {
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_DOWN"));
        // }
        // else if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_UP"))
        // {
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_UP"));
        // }
        // else
        // {
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_UP"));
        // }
    }

    // Stops conveyor and intakes
    void StopRollers()
    {
        GetConveyor()->SetSpeed(0, 0, 0);
        GetIntakeF()->SetSpeed(0, 0);
        GetIntakeR()->SetSpeed(0, 0);
    }

    // Sets shooter speed based on hood position
    void RunShooter()
    {
        // 1 is max speed, 0 is lowest
        float hoodPercent = (GetShooter()->GetSetpointH() - CONSTANT("TARGET_Y_CLOSE")) / (CONSTANT("TARGET_Y_FAR") - CONSTANT("TARGET_Y_CLOSE"));

        float shooterSpeed = (CONSTANT("SHOOTER_SPEED_UP") - CONSTANT("SHOOTER_SPEED_DOWN")) * hoodPercent + CONSTANT("SHOOTER_SPEED_DOWN");
        float rollerSpeed = (CONSTANT("HOOD_ROLLER_SPEED") - CONSTANT("HOOD_ROLLER_SPEED_DOWN")) * hoodPercent + CONSTANT("HOOD_ROLLER_SPEED_DOWN");

        if (hoodPercent >= CONSTANT("SHOOTER_C_MIN") && hoodPercent <= CONSTANT("SHOOTER_C_MAX"))
        {
            shooterSpeed *= CONSTANT("SHOOTER_C");
            rollerSpeed *= CONSTANT("SHOOTER_C");
        }

        GetShooter()->SetSpeed(shooterSpeed);
        GetShooter()->SetHoodRollerSpeed(rollerSpeed);

        // if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_DOWN"))
        // {
        //     GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_DOWN"));
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_DOWN"));
        // }
        // else if (GetShooter()->GetSetpointH() == CONSTANT("HOOD_BOTTOM"))
        // {
        //     GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_BOTTOM"));
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_BOTTOM"));
        // }
        // else
        // {
        //     GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_UP"));
        //     GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED"));
        // }
    }

    void UseLeftEncoder()
    {
    }

    void UseRightEncoder()
    {
    }

    void ResetEncoders()
    {
        m_LeftDriveA->SetSensorPosition(0);
        m_LeftDriveB->SetSensorPosition(0);
        m_RightDriveA->SetSensorPosition(0);
        m_RightDriveB->SetSensorPosition(0);
    }

    void handle();
};

#endif
