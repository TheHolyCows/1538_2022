//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Intake.cpp
// author: ssemtner
// created on: 2022-2-12
//==================================================

#include "Intake.h"
#include <iostream>
#include <frc/Timer.h>
#include <frc/Solenoid.h>

Intake::Intake(int intakeMotor, int indexMotor, int solenoidChannelA, int solenoidChannelB)
{
    m_MotorIntake = new CowLib::CowMotorController(intakeMotor);
    m_MotorIndex = new CowLib::CowMotorController(indexMotor);
    m_SolenoidA = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidChannelA);
    //m_SolenoidB = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidChannelB);
    m_IntakeSpeed = 0;
    m_IndexSpeed = 0;
}

void Intake::SetSpeed(float intakeSpeed, float indexerSpeed)
{
    m_IntakeSpeed = intakeSpeed;
    m_IndexSpeed = indexerSpeed;
}

void Intake::SetExtended(bool extended)
{
    m_IntakeExtended = extended;
}

void Intake::handle()
{
    // Extended
    m_SolenoidA->Set(m_IntakeExtended);
    //m_SolenoidB->Set(m_IntakeExtended);

    // Intake
    if (m_SolenoidA->Get() && m_SolenoidB->Get())
    {
        m_MotorIntake->Set(m_IntakeSpeed);
    }
    else
    {
        m_MotorIntake->Set(0);
    }

    // Indexer - because we may want to run this independently...
    m_MotorIndex->Set(m_IndexSpeed);
}

Intake::~Intake()
{
    delete m_MotorIntake;
    delete m_MotorIndex;
    delete m_SolenoidA;
    //delete m_SolenoidB;
}
