//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Conveyor.cpp
// author: ssemtner
// created on: 2022-2-12
//==================================================

#include "Conveyor.h"
#include <iostream>
#include <frc/Timer.h>

Conveyor::Conveyor(int upperMotor, int frontMotor, int rearMotor, int colorSensorPinNum)
    : m_ColorSensor(colorSensorPinNum)
{
    m_MotorUpper = new CowLib::CowMotorController(upperMotor);
    m_MotorFront = new CowLib::CowMotorController(frontMotor);
    m_MotorRear = new CowLib::CowMotorController(rearMotor);

    m_MotorUpper->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_MotorFront->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_MotorRear->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_DutyCycle = new frc::DutyCycle(m_ColorSensor);

    m_SpeedUpper = 0;
    m_SpeedFront = 0;
    m_SpeedRear = 0;

    // voltage compensation
    m_MotorUpper->GetInternalMotor()->EnableVoltageCompensation(true);
    m_MotorUpper->GetInternalMotor()->ConfigVoltageCompSaturation(CONSTANT("CONVEYOR_VOLT_COMP"));

    // removed - if we need to invert at creation we should hardcode it -jbassi
    // m_MotorA->GetInternalMotor()->SetInverted(changeDirectionA);
    // m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
}

void Conveyor::SetSpeed(float speedUpper, float speedFront, float speedRear)
{
    // Unsure which need to be inverted, + should be going in
    m_SpeedUpper = -speedUpper;
    m_SpeedFront = -speedFront;
    m_SpeedRear = speedFront;
}

frc::DutyCycle* Conveyor::GetColorSensor()
{
    return m_DutyCycle;
}

void Conveyor::handle()
{
    // Upper
    m_MotorUpper->Set(m_SpeedUpper);

    // Lower
    m_MotorFront->Set(m_SpeedFront);
    m_MotorRear->Set(m_SpeedRear);
}

Conveyor::~Conveyor()
{
    delete m_MotorUpper;
    delete m_MotorFront;
    delete m_MotorRear;
}
