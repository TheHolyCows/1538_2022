#include "CowRobot.h"
#include "CowBase.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/RobotController.h>
#include <frc/filter/LinearFilter.h>

CowRobot::CowRobot()
{
    m_DSUpdateCount = 0;

    m_Controller = NULL;

    // Set up drive - make a singleton
    m_Drivetrain = new WCDrive::WCDrive();
    WCDrive::InitLeftDrive(DRIVE_LEFT_A, false, DRIVE_LEFT_B, false);
    WCDrive::InitRightDrive(DRIVE_RIGHT_A, true, DRIVE_RIGHT_B, true);
    WCDrive::SetDriveConversionParams(12, 46, 4, 2048);

    m_MatchTime = 0;
    m_StartTime = 0;

    m_LEDDisplay = new CowLib::CowAlphaNum(0x70);

    m_Gyro = CowLib::CowGyro::GetInstance();

    m_PowerDistributionPanel = new frc::PowerDistribution();

    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_Accelerometer = new frc::BuiltInAccelerometer(frc::Accelerometer::kRange_4G);
}

void CowRobot::Reset()
{
    ResetEncoders();

    m_PreviousGyroError = 0;
    m_PreviousDriveError = 0;

    m_Drivetrain->Reset();
    m_MatchTime = 0;
}

void CowRobot::SetController(GenericController *controller)
{
    m_Controller = controller;
}

void CowRobot::PrintToDS()
{
    if (m_DSUpdateCount % 10 == 0)
    {
        m_DSUpdateCount = 0;
        // std::cout << std::endl;
        // or printf
    }

    m_DSUpdateCount++;
}

// Used to handle the recurring logic funtions inside the robot.
// Please call this once per update cycle.
void CowRobot::handle()
{
    m_MatchTime = CowLib::CowTimer::GetFPGATimestamp() - m_StartTime;

    if (m_Controller == NULL)
    {
        printf("No controller for CowRobot!!\n");
        return;
    }

    m_Controller->handle(this);

    // Drivetrain
    m_Drivetrain->handle();

    PrintToDS();
}

void CowRobot::StartTime()
{
    m_StartTime = CowLib::CowTimer::GetFPGATimestamp();
}
