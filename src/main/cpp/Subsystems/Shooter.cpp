/*
 * Shooter.cpp
 *
 *  Created on: March 7, 2020
 *      Author: fcoughlin
 */

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int motorControllerF, int motorControllerH, bool changeDirectionF)
{
    m_MotorS = new CowLib::CowMotorController(motorControllerF);
    m_MotorS->SetControlMode(CowLib::CowMotorController::SPEED);

    // Variable Hood
    m_MotorH = new CowLib::CowMotorController(motorControllerH);
    m_MotorH->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
    m_HoodPosition = 0;
    m_MotorH->SetNeutralMode(CowLib::CowMotorController::COAST);

    ResetConstants();

    // Logging
    m_LogServer = CowLib::CowLogger::GetInstance();
}

void Shooter::SetSpeed(float speedF)
{
    speedF = (speedF * (1.0 / 60.0) * (1.0 / 10.0) * 2048);
    m_SpeedS = speedF;
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
    m_MotorS->SetPIDGains(CONSTANT("SHOOTER_P"), CONSTANT("SHOOTER_I"), CONSTANT("SHOOTER_D"), CONSTANT("SHOOTER_F"), 1);

    // Variable Hood
    m_MotorH->SetPIDGains(CONSTANT("HOOD_P"), CONSTANT("HOOD_I"), CONSTANT("HOOD_D"), 0, 1);
    m_MotorH->SetMotionMagic(CONSTANT("HOOD_ACCEL"), CONSTANT("HOOD_VELOCITY"));
    m_HoodUpLimit = CONSTANT("HOOD_UP_LIMIT");
    m_HoodDownLimit = CONSTANT("HOOD_DOWN_LIMIT");
}

float Shooter::GetSpeedF()
{
    return (m_MotorS->GetInternalMotor()->GetSelectedSensorVelocity()) * (10.0 / 2048.0) * 60;
}

float Shooter::GetHoodPosition()
{
    return m_MotorH->GetPosition();
}

void Shooter::handle()
{
    m_LogServer->PIDRemoteLog((double)m_SpeedS,
                              (double)GetSpeedF(),
                              m_MotorS->GetInternalMotor()->GetClosedLoopError(),
                              m_MotorS->GetInternalMotor()->GetIntegralAccumulator(),
                              m_MotorS->GetInternalMotor()->GetErrorDerivative());

    if (m_MotorS)
    {
        if (m_SpeedS != 0)
        {
            //float res = (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity())*(10.0/2048.0)*60;
            //std::cout << "Speed: " << res << std::endl;
            m_MotorS->SetControlMode(CowLib::CowMotorController::SPEED);

            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorS->Set(m_SpeedS);
        }
        else
        {
            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorS->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);

            m_MotorS->Set(m_SpeedS);
        }
    }

    if (m_MotorH)
    {
        m_MotorH->Set(m_HoodPosition);
    }
}

Shooter::~Shooter()
{
    delete m_MotorS;
    delete m_MotorH;
}
