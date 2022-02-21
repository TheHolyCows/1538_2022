//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Shooter.cpp
// author: ssemtner
// created on: 2022-2-12
//==================================================

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int shooterMotor, int hoodMotor)
{
    m_MotorShooter = new CowLib::CowMotorController(shooterMotor);
    m_MotorShooter->SetControlMode(CowLib::CowMotorController::SPEED);

    // Variable Hood
    m_MotorHood = new CowLib::CowMotorController(hoodMotor);
    m_MotorHood->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
    m_HoodPosition = 0;
    m_MotorHood->SetNeutralMode(CowLib::CowMotorController::COAST);

    ResetConstants();

    // Logging
    m_LogServer = CowLib::CowLogger::GetInstance();
}

void Shooter::SetSpeed(float speedShooter)
{
    speedShooter = (speedShooter * (1.0 / 60.0) * (1.0 / 10.0) * 2048);
    m_SpeedShooter = speedShooter;
}

void Shooter::SetHoodPosition(float position)
{
    if (position < m_HoodDownLimit)
    {
        m_HoodPosition = m_HoodDownLimit;
    }
    else if (position > m_HoodUpLimit)
    {
        m_HoodPosition = m_HoodUpLimit;
    }
    else
    {
        m_HoodPosition = position;
    }
}

void Shooter::ResetConstants()
{
    // Shooter
    printf("P: %lf\n I: %lf\n D: %lf\n F: %lf\n", CONSTANT("SHOOTER_P"), CONSTANT("SHOOTER_I"), CONSTANT("SHOOTER_D"), CONSTANT("SHOOTER_F"));
    m_MotorShooter->SetPIDGains(CONSTANT("SHOOTER_P"), CONSTANT("SHOOTER_I"), CONSTANT("SHOOTER_D"), CONSTANT("SHOOTER_F"), 1);

    // Variable Hood
    m_MotorHood->SetPIDGains(CONSTANT("HOOD_P"), CONSTANT("HOOD_I"), CONSTANT("HOOD_D"), 0, 1);
    m_MotorHood->SetMotionMagic(CONSTANT("HOOD_ACCEL"), CONSTANT("HOOD_VELOCITY"));
    m_HoodUpLimit = CONSTANT("HOOD_UP_LIMIT");
    m_HoodDownLimit = CONSTANT("HOOD_DOWN_LIMIT");
}

float Shooter::GetSpeedF()
{
    return (m_MotorShooter->GetInternalMotor()->GetSelectedSensorVelocity()) * (10.0 / 2048.0) * 60;
}

float Shooter::GetHoodPosition()
{
    return m_MotorHood->GetPosition();
}

void Shooter::handle()
{
    // m_LogServer->PIDRemoteLog((double)m_SpeedShooter,
    //                           (double)GetSpeedF(),
    //                           m_MotorShooter->GetInternalMotor()->GetClosedLoopError(),
    //                           m_MotorShooter->GetInternalMotor()->GetIntegralAccumulator(),
    //                           m_MotorShooter->GetInternalMotor()->GetErrorDerivative());

    if (m_MotorShooter)
    {
        if (m_SpeedShooter != 0)
        {
            //float res = (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity())*(10.0/2048.0)*60;
            //std::cout << "Speed: " << res << std::endl;
            m_MotorShooter->SetControlMode(CowLib::CowMotorController::SPEED);

            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorShooter->Set(m_SpeedShooter);
        }
        else
        {
            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorShooter->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);

            m_MotorShooter->Set(m_SpeedShooter);
        }
    }

    if (m_MotorHood)
    {
        m_MotorHood->Set(m_HoodPosition);
    }
}

Shooter::~Shooter()
{
    delete m_MotorShooter;
    delete m_MotorHood;
}
