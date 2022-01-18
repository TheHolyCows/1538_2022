/*
 * Shooter.cpp
 *
 *  Created on: March 7, 2020
 *      Author: fcoughlin
 */

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int motorControllerF, bool changeDirectionF)
{
    m_MotorF = new CowLib::CowMotorController(motorControllerF);
    m_MotorF->SetControlMode(CowLib::CowMotorController::SPEED);

}

void Shooter::SetSpeed(float speedF)
{
    speedF = (speedF * (1.0/60.0) * (1.0/10.0) * 2048);
    m_SpeedF = speedF;
}

void Shooter::ResetConstants()
{
    printf("P: %lf\n I: %lf\n D: %lf\n F: %lf\n", CONSTANT("SHOOTER_F_P"), CONSTANT("SHOOTER_F_I"), CONSTANT("SHOOTER_F_D"), CONSTANT("SHOOTER_F_F"));
    m_MotorF->SetPIDGains(CONSTANT("SHOOTER_F_P"), CONSTANT("SHOOTER_F_I"), CONSTANT("SHOOTER_F_D"), CONSTANT("SHOOTER_F_F"), 1);
}

float Shooter::GetSpeedF()
{
    return (m_MotorF->GetInternalMotor()->GetSelectedSensorVelocity())*(10.0/2048.0)*60;
}

void Shooter::handle()
{
    // std::cout << "Shooter::handle()" << m_SpeedF << std::endl;    
    if(m_MotorF)
    {
        if(m_SpeedF != 0)
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
}

Shooter::~Shooter()
{
    delete m_MotorF;
}




