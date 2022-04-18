//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include <math.h>
#include "CowLib/CowLogger.h"
#include "CowLib/CowCircularBuffer.h"
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
#include "frc/filter/LinearFilter.h"

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

    frc::LinearFilter<double> m_ZFilter = frc::LinearFilter<double>::MovingAverage(12);
    double m_PrevZ = 0;

    CowLib::CowLPF *m_AccelY_LPF;
    CowLib::CowLPF *m_LoadDetect_LPF;

    float m_TipTime;
    bool m_Tipping;
    frc::CameraServer *m_CameraServer;
    cs::UsbCamera *m_UsbCamera;

    // logging
    CowLib::CowLogger *m_LogServer;

    // velocity
    int m_DistIdx = 0;
    double m_DistDeltaBuff[20];
    double m_PrevDist;

public:
    CowRobot();
    void Reset();
    void GyroHandleCalibration();
    void GyroFinalizeCalibration();
    void SetController(GenericController *controller);
    void PrintToDS();
    bool DoVisionTracking(float speed, float threshold = 5.0);
    void DriveSpeedPushDistance();
    double GetDriveDistance();
    double GetDriveSpeed();
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
    void SetConveyorMode(ConveyorMode newMode, bool rear, double percentage = 1.0);

    // Sets the intake mode the new mode if the new mode is higher priority
    void SetIntakeMode(IntakeMode newMode, bool rear, double percentage = 1.0);

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

    // void IntakeWithAutoExhaust(bool rear)
    // {
    //     bool red = frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kRed;

    //     // not sure why the function returns an int
    //     // int freq = m_Conveyor->GetColorSensor()->GetFrequency();

    //     SetIntakeMode(IntakeMode::INTAKE_INTAKE, rear);

    //     // If correct color
    //     // if (freq in red range)
    //     if (true)
    //     {
    //         SetIntakeMode(IntakeMode::INTAKE_OFF, !rear);
    //         SetConveyorMode(ConveyorMode::CONVEYOR_INTAKE, false);
    //     }
    //     else
    //     {
    //         SetIntakeMode(IntakeMode::INTAKE_EXHAUST, !rear);

    //         if (rear)
    //         {
    //             GetConveyor()->SetSpeed(0, CONSTANT("CONVEYOR_OUT_LOW"), CONSTANT("CONVEYOR_IN_LOW"));
    //         }
    //         else
    //         {
    //             GetConveyor()->SetSpeed(0, CONSTANT("CONVEYOR_IN_LOW"), CONSTANT("CONVEYOR_OUT_LOW"));
    //         }
    //     }
    // }

    // Stops conveyor and intakes
    void StopRollers()
    {
        GetConveyor()->SetSpeed(0, 0, 0);
        GetIntakeF()->SetSpeed(0, 0);
        GetIntakeR()->SetSpeed(0, 0);
    }

    void ShootBalls(void);
    void RunShooter(void);

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
