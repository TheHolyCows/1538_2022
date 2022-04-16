//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Climber.h
// author: ssemtner
// created on: 2022-3-17
//==================================================

#include "Climber.h"

Climber::Climber(int leftMotor, int rightMotor)
{
    m_LeftMotor = new CowLib::CowMotorController(leftMotor);
    m_RightMotor = new CowLib::CowMotorController(rightMotor);

    m_LeftMotor->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
    m_RightMotor->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);

    m_LeftMotor->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_RightMotor->SetNeutralMode(CowLib::CowMotorController::BRAKE);

    m_RightMotor->GetInternalMotor()->SetSensorPhase(true);
    m_LeftMotor->GetInternalMotor()->SetInverted(true);

    m_LeftPosition = 0;
    m_RightPosition = 0;

    ResetConstants();
}

void Climber::SetLeftPosition(float position)
{
    m_LeftPosition = position;
}

void Climber::SetRightPosition(float position)
{
    m_RightPosition = position;
}

float Climber::GetLeftPosition()
{
    return m_LeftMotor->GetPosition();
}

float Climber::GetRightPosition()
{
    return m_RightMotor->GetPosition();
}

// bool Climber::LeftAtTarget()
// {
//     return (fabs(GetLeftPosition() - m_LeftPosition) < CONSTANT("CLIMBER_TOLERANCE"));
// }

// bool Climber::RightAtTarget()
// {
//     return (fabs(GetRightPosition() - m_RightPosition) < CONSTANT("CLIMBER_TOLERANCE"));
// }

void Climber::ResetConstants()
{
    m_LeftMotor->SetPIDGains(CONSTANT("CLIMBER_P"), CONSTANT("CLIMBER_I"), CONSTANT("CLIMBER_D"), 0, 1);
    m_RightMotor->SetPIDGains(CONSTANT("CLIMBER_P"), CONSTANT("CLIMBER_I"), CONSTANT("CLIMBER_D"), 0, 1);
}

void Climber::handle()
{
    if (m_LeftMotor)
    {
        m_LeftMotor->Set(m_LeftPosition);
    }
    if (m_RightMotor)
    {
        m_RightMotor->Set(m_RightPosition);
    }
}

Climber::~Climber()
{
    delete m_LeftMotor;
    delete m_RightMotor;
}