//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_ROBOT_H__
#define __COW_ROBOT_H__

#include "CowLib/CowLogger.h"
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
#include "networktables/NetworkTable.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Conveyor.h"
#include "Subsystems/Shooter.h"

class CowRobot
{
private:
    int m_DSUpdateCount;
    
    GenericController *m_Controller;
    
    // Drive Motors
    CowLib::CowMotorController *m_LeftDriveA;
    CowLib::CowMotorController *m_LeftDriveB;

    CowLib::CowMotorController *m_RightDriveA;
    CowLib::CowMotorController *m_RightDriveB;
    
    CowLib::CowMotorController *m_ShooterWheelF;
    CowLib::CowMotorController *m_ShooterWheelB;

    CowLib::CowCanifier *m_Canifier;

    CowLib::CowGyro *m_Gyro;

    frc::PowerDistribution *m_PowerDistributionPanel;

    CowLib::CowAlphaNum *m_LEDDisplay;
    CowLib::CowLogger *m_WebServer;

    Arm *m_Arm;
    Intake *m_Intake;
    Intake *m_FeederF;
    Intake *m_FeederB;
    Conveyor *m_Conveyor;
    Shooter *m_Shooter;

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
    std::shared_ptr<nt::NetworkTable> m_LimelightForward;
    std::shared_ptr<nt::NetworkTable> m_LimelightBackward;
    frc::CameraServer *m_CameraServer;
    cs::UsbCamera *m_UsbCamera;

    float m_Limelight_PID_P;
    float m_Limelight_PID_D;


public:
    CowRobot();
    void Reset();
    void GyroHandleCalibration();
    void GyroFinalizeCalibration();
    void SetController(GenericController *controller);
    void PrintToDS();
    double GetDriveDistance();
    bool DriveDistance(double distance);
    bool DriveDistanceWithHeading(double heading, double distance, double speed);
    bool DriveWithHeading(double heading, double speed);
    bool DriveWithHeading(double heading, double speed, double maxSpeed);
    void DriveSpeedTurn(float speed, float turn, bool quickTurn);
    void DriveLeftRight(float leftDriveValue, float rightDriveValue);
    bool TurnToHeading(double heading);

    std::shared_ptr<nt::NetworkTable> GetLimelight()
    {
    	return m_LimelightForward;
    }
    bool DoVisionTracking(float speed, float threshold = 5.00);
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

    Arm* GetArm()
    {
        return m_Arm;
    }
    Intake* GetIntake()
    {
        return m_Intake;
    }
    Intake* GetFeederF()
    {
        return m_FeederF;
    }
    Intake* GetFeederB()
    {
        return m_FeederB;
    }
    Conveyor* GetConveyor()
    {
        return m_Conveyor;
    }
    Shooter* GetShooter()
    {
        return m_Shooter;
    }
    CowLib::CowCanifier* GetCanifier()
    {
        return m_Canifier;
    }
    CowLib::CowMotorController* GetShooterF()
    {
        return m_ShooterWheelF;
    }
    CowLib::CowMotorController* GetShooterB()
    {
        return m_ShooterWheelB;
    }

    void IntakeBalls(double percentage)
    {
        GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_IN_LOW") * percentage, CONSTANT("CONVEYOR_IN_UP") * percentage);
        GetFeederF()->SetSpeed(CONSTANT("FEEDER_F_ON") * percentage);
        GetFeederB()->SetSpeed(CONSTANT("FEEDER_B_ON") * percentage);
        GetIntake()->SetSpeed(CONSTANT("INTAKE_ON") * percentage);
    }

    void ExhaustBalls(double percentage)
    {
        GetConveyor()->SetSpeed(-CONSTANT("CONVEYOR_OUT_LOW") * percentage, -CONSTANT("CONVEYOR_OUT_UP") * percentage);
        GetIntake()->SetSpeed(-CONSTANT("INTAKE_ON") * percentage);
        GetFeederF()->SetSpeed(-CONSTANT("FEEDER_F_ON") * percentage);
        GetFeederB()->SetSpeed(-CONSTANT("FEEDER_B_ON") * percentage);
    }

    void ShootBalls()
    {
         GetFeederF()->SetSpeed(CONSTANT("FEEDER_F_SHOOT"));
         GetFeederB()->SetSpeed(CONSTANT("FEEDER_B_SHOOT"));
         GetConveyor()->SetSpeed(CONSTANT("CONVEYOR_SHOOT_LOW"), CONSTANT("CONVEYOR_SHOOT_UP"));
         GetIntake()->SetSpeed(CONSTANT("INTAKE_ON"));
    }

    void StopRollers()
    {
         GetConveyor()->SetSpeed(0, 0);
         GetFeederF()->SetSpeed(0);
         GetFeederB()->SetSpeed(0);
         GetIntake()->SetSpeed(0);
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