//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Shooter.cpp
// author: ssemtner
// created on: 2022-2-12
//==================================================

#include "Shooter.h"
#include <iostream>
#include <frc/Timer.h>

Shooter::Shooter(int shooterMotor1, int shooterMotor2, int hoodMotor)
{
    m_MotorShooter1 = new CowLib::CowMotorController(shooterMotor1);
    m_MotorShooter1->SetControlMode(CowLib::CowMotorController::SPEED);

    // m_MotorShooter2 = new CowLib::CowMotorController(shooterMotor2);
    // m_MotorShooter2->SetControlMode(CowLib::CowMotorController::FOLLOWER);
    m_Motor1ID = shooterMotor1;

    // Variable Hood
    m_MotorHood = new CowLib::CowMotorController(hoodMotor);
    m_MotorHood->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
    m_HoodPosition = 0;
    m_MotorHood->SetNeutralMode(CowLib::CowMotorController::BRAKE);
    m_HoodZeroed = false;

    ResetConstants();

    // Logging
    m_LogServer = CowLib::CowLogger::GetInstance();
}

void Shooter::SetSpeed(float speedShooter)
{
    if (speedShooter != 0)
    {
        m_MotorShooter1->SetControlMode(CowLib::CowMotorController::SPEED);
    }
    else
    {
        m_MotorShooter1->SetControlMode(CowLib::CowMotorController::PERCENTVBUS);
    }

    m_Setpoint = speedShooter;
    speedShooter = (speedShooter * (1.0 / 60.0) * (1.0 / 10.0) * 2048);
    m_SpeedShooter = speedShooter;
}

void Shooter::SetSpeedHoodRelative()
{
    // ranges from 0 -> 1.0
    float percentOfHood = (m_HoodPosition - m_HoodDownLimit) / CONSTANT("HOOD_DELTA");

    int speedDelta = CONSTANT("SHOOTER_SPEED_UP") - CONSTANT("SHOOTER_SPEED_DOWN");
    SetSpeed((speedDelta * percentOfHood) + CONSTANT("SHOOTER_SPEED_DOWN"));
}

/**
 * Sets position of variable hood
 * Value is added to the hood down limit, therefore it is a relative position
 **/
void Shooter::SetHoodPosition(float position)
{
    m_HoodPosition = m_HoodDownLimit + position;

    if (m_MotorHood)
    {
        // m_MotorHood->Set(m_HoodPosition);
    }
}

void Shooter::SetHoodPositionUp()
{
    m_HoodPosition = m_HoodUpLimit;

    if (m_MotorHood)
    {
        // m_MotorHood->Set(CONSTANT("HOOD_UP"));
    }
}

void Shooter::SetHoodPositionDown()
{
    m_HoodPosition = m_HoodDownLimit;

    if (m_MotorHood)
    {
        // m_MotorHood->Set(CONSTANT("HOOD_DOWN"));
    }
}

void Shooter::ZeroHoodPosition()
{
    if (m_HoodZeroed)
    {
        m_ZeroingHood = false;
        return;
    }
    else
    {
        m_ZeroingHood = true;
    }

    float current = m_MotorHood->GetOutputCurrent();
    std::cout << "hood current: " << current << std::endl;
    if (current >= 0.25)
    {
        m_ZeroingHood = false;
        m_HoodZeroed = true;

        float hoodDelta = CONSTANT("HOOD_DELTA");

        m_HoodPosition = hoodDelta < 0 ? m_HoodPosition - 200 : m_HoodPosition + 200;
        m_HoodDownLimit = m_HoodPosition;
        m_HoodUpLimit = m_HoodPosition + hoodDelta;

        return;
    }

    // this may need to be reversed depending on motor orientation
    m_HoodPosition += 25;
    m_MotorHood->Set(m_HoodPosition);
}

void Shooter::ResetConstants()
{
    // Shooter
    printf("P: %lf\n I: %lf\n D: %lf\n F: %lf\n", CONSTANT("SHOOTER_P"), CONSTANT("SHOOTER_I"), CONSTANT("SHOOTER_D"), CONSTANT("SHOOTER_F"));
    m_MotorShooter1->SetPIDGains(CONSTANT("SHOOTER_P"), CONSTANT("SHOOTER_I"), CONSTANT("SHOOTER_D"), CONSTANT("SHOOTER_F"), 1);

    // Variable Hood
    m_MotorHood->SetPIDGains(CONSTANT("HOOD_P"), CONSTANT("HOOD_I"), CONSTANT("HOOD_D"), 0, 1);
    m_MotorHood->SetMotionMagic(CONSTANT("HOOD_ACCEL"), CONSTANT("HOOD_VELOCITY"));
    m_HoodUpLimit = CONSTANT("HOOD_DELTA");
    m_HoodDownLimit = 0;
    m_HoodZeroed = false;
    m_ZeroingHood = false;
}

float Shooter::CalcShooterTolerance()
{
    // min incase i forget to update constants on the robot
    return m_Setpoint * CONSTANT("SHOOTER_SPEED_TOLERANCE");
}

float Shooter::GetSpeedF()
{
    // *2 at the end of this statement for gear ratio on shooter
    return (m_MotorShooter1->GetInternalMotor()->GetSelectedSensorVelocity()) * (10.0 / 2048.0) * 60 * 2;
}

float Shooter::GetHoodPosition()
{
    return m_MotorHood->GetPosition();
}

void Shooter::handle()
{
    if (CONSTANT("DEBUG_PID") == 1)
    {
        m_LogServer->PIDRemoteLog((double)m_Setpoint,
                                  (double)GetSpeedF(),
                                  m_MotorShooter1->GetInternalMotor()->GetClosedLoopError(),
                                  m_MotorShooter1->GetInternalMotor()->GetIntegralAccumulator(),
                                  m_MotorShooter1->GetInternalMotor()->GetOutputCurrent());
    }

    // if (m_MotorShooter1 && m_MotorShooter2)
    if (m_MotorShooter1)
    {
        // TODO: TEMPORARY FOR A BOT WHEN WE HAVE ONE MOTOR

        m_MotorShooter1->Set(-m_SpeedShooter);
        // m_MotorShooter1->Set(m_SpeedShooter);
        // m_MotorShooter2->Set(m_Motor1ID);
    }
}

Shooter::~Shooter()
{
    delete m_MotorShooter1;
    // delete m_MotorShooter2;
    delete m_MotorHood;
}
