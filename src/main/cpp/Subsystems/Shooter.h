//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Shooter.h
// author: ssemtner
// created on: 2022-2-12
//==================================================

#ifndef __SRC_SUBSYSTEMS_SHOOTER_H__
#define __SRC_SUBSYSTEMS_SHOOTER_H__

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowLogger.h"
#include <wpi/deprecated.h>
#include <frc/Timer.h>
#include <string>

class Shooter
{
public:
    Shooter(int motorControllerS1, int motorControllerS2, int motorControllerH);
    bool AtTarget();
    void SetSpeed(float speedF);
    void SetHoodPosition(float position);
    float GetSetpointF()
    {
        return m_Setpoint;
    }
    float GetSetpointH()
    {
        return m_HoodPosition;
    }

    void ResetConstants();
    void SetClosedLoopError(int error)
    {
        if (m_MotorShooter1)
        {
            m_MotorShooter1->SetClosedLoopError(error);
        }
    }
    void handle();

    float GetSpeedF();
    float GetHoodPosition();

    virtual ~Shooter();

private:
    CowLib::CowMotorController *m_MotorShooter1;
    CowLib::CowMotorController *m_MotorShooter2;
    CowLib::CowMotorController *m_MotorHood;
    CowLib::CowLPF *m_RampLPF_F;

    int m_Motor1ID;

    float m_SpeedShooter;
    float m_Setpoint;

    float m_HoodPosition;
    float m_HoodUpLimit;
    float m_HoodDownLimit;

    CowLib::CowLogger *m_LogServer;
};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
