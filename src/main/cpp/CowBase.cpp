#include "CowBase.h"

#include <iostream>

CowBase::CowBase()
    :
    m_ControlBoard(new CowControlBoard()),
    m_OpController(new OperatorController(m_ControlBoard)),
    m_AutoController(new AutoModeController()),
    m_Constants(CowConstants::GetInstance())
{    
    CowConstants::GetInstance()->RestoreData();
    m_Bot = new CowRobot();

    m_Display = new CowDisplay(m_Bot);

    //SetPeriod(HZ(ROBOT_HZ));
    //GetWatchdog().SetEnabled(false);
    printf("Done constructing CowBase!\n");
}

CowBase::~CowBase()
{
    delete m_ControlBoard;
    delete m_OpController;
    delete m_AutoController;
    delete m_Display;
}

void CowBase::RobotInit()
{
    m_Bot->Reset();
}

void CowBase::DisabledInit()
{
    CowConstants::GetInstance()->RestoreData();
    m_Bot->GetGyro()->ResetAngle();
    m_Bot->GetGyro()->BeginCalibration();
    m_Bot->Reset();
}

void CowBase::AutonomousInit()
{
    m_Bot->GetGyro()->FinalizeCalibration();
    m_Bot->GetGyro()->ResetAngle();

    m_AutoController->SetCommandList(AutoModes::GetInstance()->GetCommandList());
    m_Bot->SetController(m_AutoController);
    m_Bot->Reset();
}

void CowBase::TeleopInit()
{
    m_Bot->StartTime();
    m_Bot->GetGyro()->FinalizeCalibration();
    m_Bot->SetController(m_OpController);
    m_Bot->GetArm()->SetBrakeMode();
}

void CowBase::DisabledContinuous()
{
    //taskDelay(WAIT_FOREVER);
}

void CowBase::AutonomousContinuous()
{
    //taskDelay(WAIT_FOREVER);
}

void CowBase::TeleopContinuous()
{
    //taskDelay(WAIT_FOREVER);
}

void CowBase::DisabledPeriodic()
{
    //m_Bot->GyroHandleCalibration();

    if(m_Display)
    {
        m_Display->DisplayPeriodic();
    }

    if(m_ControlBoard->GetAutoSelectButton())
    {
        m_Constants->RestoreData();

        if(m_ControlBoard->GetDriveButton(1))
        {
            m_Bot->Reset();

            /*
             * POSITION FIRST_OWNERSHIP SECOND_OWNERSHIP DRIVE
             */
            AutoModes::GetInstance()->NextMode();
        }
    }
   if(m_Bot)
   {
	m_Bot->GetArm()->DisabledCalibration();
   }
//    m_Bot->PrintToDS();
}

void CowBase::AutonomousPeriodic()
{
    m_Bot->handle();
}

void CowBase::TeleopPeriodic()
{
    m_Bot->handle();

//    if(m_Display)
//    {
//        m_Display->DisplayPeriodic();
//    }
}

int main() { return frc::StartRobot<CowBase>(); }
