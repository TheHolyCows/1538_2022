//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Climber.h
// author: ssemtner
// created on: 2022-3-17
//==================================================

#include "Climber.h"

Climber::Climber(int motor, int solenoidLock, int solenoidPTO)
{
    m_MotorController = new CowLib::CowMotorController(motor);
    m_MotorController->SetNeutralMode(CowLib::CowMotorController::BRAKE);

    m_SolenoidLock = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidLock);
    m_SolenoidPTO = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidPTO);

    m_Speed = 0;
    m_Locked = true;
    m_PTOEngaged = false;
}

void Climber::SetSpeed(float speed)
{
    // position = CONSTANT("CLIMBER_MAX") < CONSTANT("CLIMBER_MIN") ? std::max((float)CONSTANT("CLIMBER_MAX"), position) : std::min((float)CONSTANT("CLIMBER_MAX"), position);
    // position = CONSTANT("CLIMBER_MAX") > CONSTANT("CLIMBER_MIN") ? std::max((float)CONSTANT("CLIMBER_MIN"), position) : std::min((float)CONSTANT("CLIMBER_MIN"), position);

    // m_Position = position;

    // m_MotorController->Set(m_Position / m_EncoderInchPerTick);

    m_Speed = speed;
}

void Climber::SetLockState(bool locked)
{
    m_SolenoidLock->Set(locked);
}

void Climber::SetPTOEngaged(bool engaged)
{
    m_SolenoidPTO->Set(engaged);

}

float Climber::GetDistance()
{
    return m_MotorController->GetPosition() * m_EncoderInchPerTick;
}

void Climber::ResetConstants()
{
    // m_MotorController->SetPIDGains(CONSTANT("CLIMBER_P"), CONSTANT("CLIMBER_I"), CONSTANT("CLIMBER_D"), 0, 1);
    // m_MotorController->SetMotionMagic(CONSTANT("CLIMBER_ACCEL"), CONSTANT("CLIMBER_VELOCITY"));

    // m_EncoderInchPerTick = CONSTANT("CLIMBER_INCH_PER_TICK");
}

// bool Climber::AtTarget()
// {
//     return (fabs(m_Position - this->GetDistance()) < CONSTANT("CLIMBER_TOLERANCE"));
// }

void Climber::handle()
{
    m_MotorController->Set(m_Speed);
}

Climber::~Climber()
{
    delete m_MotorController;
    delete m_SolenoidLock;
    delete m_SolenoidPTO;
}
