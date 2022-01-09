/*
 * Shooter.cpp
 *
 *  Created on: March 7, 2020
 *      Author: fcoughlin
 */

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int motorControllerF, int motorControllerB, bool changeDirectionF, bool changeDirectionB)
{
    m_MotorF = new CowLib::CowMotorController(motorControllerF);
    m_MotorF->SetControlMode(CowLib::CowMotorController::SPEED);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_MotorB->SetControlMode(CowLib::CowMotorController::SPEED);
    m_RampLPF_F = new CowLib::CowLPF(CONSTANT("SHOOT_RAMP_LPF"));
    m_RampLPF_B = new CowLib::CowLPF(CONSTANT("SHOOT_RAMP_LPF"));
}

void Shooter::SetSpeed(float speedF, float speedB)
{
    speedF = (speedF * -1.44 * (1.0/60.0) * (1.0/10.0) * 4096);
    speedB = (speedB * 1.44 * (1.0/60.0) * (1.0/10.0) * 4096);
    m_SpeedF = speedF;
    m_SpeedB = speedB;
}

void Shooter::ResetConstants()
{
    m_MotorF->SetPIDGains(CONSTANT("SHOOTER_F_P"), CONSTANT("SHOOTER_F_I"), CONSTANT("SHOOTER_F_D"), CONSTANT("SHOOTER_F_F"), 1);
    m_MotorB->SetPIDGains(CONSTANT("SHOOTER_B_P"), CONSTANT("SHOOTER_B_I"), CONSTANT("SHOOTER_B_D"), CONSTANT("SHOOTER_B_F"), 1);
    m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
    m_RampLPF_B->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
}

float Shooter::GetSpeedF()
{
    return (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity())/16384.0*6000.0*1.44;
}

float Shooter::GetSpeedB()
{
    return (m_MotorB->GetInternalMotor()->GetSelectedSensorVelocity())/16384.0*6000.0*1.44;
}

void Shooter::handle()
{
    if(m_MotorF && m_MotorB)
    {
        if(m_SpeedF != 0 && m_SpeedB != 0)
        {
            if((fabs(GetSpeedF()) < CONSTANT("SHOOT_RAMP_SHIFT_F")) && !m_HasShifted_F)
            {
                m_MotorF->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
                m_MotorF->Set(m_RampLPF_F->Calculate(CONSTANT("SHOOT_RAMP")));
            }
            else
            {
                m_MotorF->SetControlMode(CowLib::CowMotorController::SPEED);
                m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
                m_MotorF->Set(m_SpeedF);
                m_HasShifted_F = true;
            }
            if((fabs(GetSpeedB()) < CONSTANT("SHOOT_RAMP_SHIFT_B")) && !m_HasShifted_B)
            {
                m_MotorB->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
                m_MotorB->Set(m_RampLPF_B->Calculate(CONSTANT("SHOOT_RAMP")));
            }
            else
            {
                m_MotorB->SetControlMode(CowLib::CowMotorController::SPEED);
                m_RampLPF_B->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
                m_MotorB->Set(m_SpeedB);
                m_HasShifted_B = true;
            }
        }
        else
        {
                m_RampLPF_F->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
                m_RampLPF_B->UpdateBeta(CONSTANT("SHOOT_RAMP_LPF"));
                m_MotorF->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
                m_MotorB->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
                m_MotorF->Set(m_SpeedF);
                m_MotorB->Set(m_SpeedB);
                m_HasShifted_F = false;
                m_HasShifted_B = false;
        }
    }
}

Shooter::~Shooter()
{
    delete m_MotorF;
    delete m_MotorB;
}




