//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Conveyor.cpp
// author: ssemtner
// created on: 2022-2-12
//==================================================

#include "Conveyor.h"
#include <iostream>
#include <frc/Timer.h>

Conveyor::Conveyor(int upperMotor, int lowerMotor)
{
    m_MotorUpper = new CowLib::CowMotorController(upperMotor);
    m_MotorLower = new CowLib::CowMotorController(lowerMotor);
    m_SpeedUpper = 0;
    m_SpeedLower = 0;

    // removed - if we need to invert at creation we should hardcode it -jbassi
    // m_MotorA->GetInternalMotor()->SetInverted(changeDirectionA);
    // m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
}

void Conveyor::SetSpeed(float speedUpper, float speedLower)
{
    m_SpeedUpper = speedUpper;
    m_SpeedLower = speedLower;
}

void Conveyor::handle()
{
    // Upper
    m_MotorUpper->Set(m_SpeedUpper);

    // Lower
    m_MotorLower->Set(m_SpeedLower);
}

Conveyor::~Conveyor()
{
    delete m_MotorUpper;
    delete m_MotorLower;
}
