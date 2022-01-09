//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_BASE_H__
#define __COW_BASE_H__

#include <frc/TimedRobot.h>
#include "CowControlBoard.h"
#include "Controllers/OperatorController.h"
#include "Controllers/AutoModeController.h"
#include "Autonomous/AutoModes.h"
#include "CowLib/CowLib.h"
#include "CowConstants.h"
#include "CowDisplay.h"

class CowBase : public frc::TimedRobot
{
private:
    CowRobot *m_Bot;
    CowControlBoard *m_ControlBoard;
    OperatorController *m_OpController;
    AutoModeController *m_AutoController;
    CowConstants *m_Constants;
    CowDisplay *m_Display;

public:
    CowBase();
    ~CowBase();
    void RobotInit();
    void DisabledInit();
    void AutonomousInit();
    void TeleopInit();
    void DisabledContinuous();
    void AutonomousContinuous();
    void TeleopContinuous();
    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();
};

#endif

