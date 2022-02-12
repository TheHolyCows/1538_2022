/*
 * Shooter.cpp
 *
 *  Created on: March 7, 2020
 *      Author: fcoughlin
 */

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int motorControllerF, int motorControllerV, bool changeDirectionF, float hoodUpLimit, float hoodDownLimit)
{
    m_MotorF = new CowLib::CowMotorController(motorControllerF);
    m_MotorF->SetControlMode(CowLib::CowMotorController::SPEED);

    // Variable Hood
    m_MotorV = new CowLib::CowMotorController(motorControllerV);
    m_MotorV->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
    m_HoodPosition = 0;
    m_MotorV->SetNeutralMode(CowLib::CowMotorController::COAST);

    ResetConstants(hoodUpLimit, hoodDownLimit);

    // Logging
    m_LogServer = CowLib::CowLogger::GetInstance();
}

void Shooter::SetSpeed(float speedF)
{
    speedF = (speedF * (1.0 / 60.0) * (1.0 / 10.0) * 2048);
    m_SpeedF = speedF;
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

void Shooter::ResetConstants(float upLimit, float downLimit)
{
    // Shooter
    printf("P: %lf\n I: %lf\n D: %lf\n F: %lf\n", CONSTANT("SHOOTER_F_P"), CONSTANT("SHOOTER_F_I"), CONSTANT("SHOOTER_F_D"), CONSTANT("SHOOTER_F_F"));
    m_MotorF->SetPIDGains(CONSTANT("SHOOTER_F_P"), CONSTANT("SHOOTER_F_I"), CONSTANT("SHOOTER_F_D"), CONSTANT("SHOOTER_F_F"), 1);

    // Variable Hood
    m_MotorV->SetPIDGains(CONSTANT("HOOD_P") * CONSTANT("DEBUG_PID"), CONSTANT("HOOD_I") * CONSTANT("DEBUG_PID"), CONSTANT("ARM_D") * CONSTANT("DEBUG_PID"), 0, 1);
    m_MotorV->SetMotionMagic(CONSTANT("ARM_ACCEL"), CONSTANT("ARM_VELOCITY"));
    m_HoodUpLimit = upLimit;
    m_HoodDownLimit = downLimit;
}

float Shooter::GetSpeedF()
{
    return (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity()) * (10.0 / 2048.0) * 60;
}

float Shooter::GetHoodPosition()
{
    return m_MotorV->GetPosition();
}

void Shooter::handle()
{
    m_LogServer->PIDRemoteLog((double)CONSTANT("SHOOTER_F_GOAL"),
                              (double)GetSpeedF(),
                              m_MotorF->GetInternalMotor()->GetClosedLoopError(),
                              m_MotorF->GetInternalMotor()->GetIntegralAccumulator(),
                              m_MotorF->GetInternalMotor()->GetErrorDerivative());

    if (m_MotorF)
    {
        if (m_SpeedF != 0)
        {
            //float res = (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity())*(10.0/2048.0)*60;
            //std::cout << "Speed: " << res << std::endl;
            m_MotorF->SetControlMode(CowLib::CowMotorController::SPEED);

            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorF->Set(m_SpeedF);
        }
        else
        {
            //m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));

            m_MotorF->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);

            m_MotorF->Set(m_SpeedF);
        }
    }

    if (m_MotorV)
    {
        m_MotorV->Set(m_HoodPosition);
    }
}

Shooter::~Shooter()
{
    delete m_MotorF;
    delete m_MotorV;
}
