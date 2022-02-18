#include "Intake.h"
#include <iostream>
#include <frc/Timer.h>
#include <frc/Solenoid.h>

Intake::Intake(int motorControllerA, int motorControllerB, int solenoidChannelA, int solenoidChannelB)
{
    m_MotorA = new CowLib::CowMotorController(motorControllerA);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_SolenoidA = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidChannelA);
    m_SolenoidB = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidChannelB);
    m_Speed = 0;
}

void Intake::SetSpeed(float intakeSpeed, float indexerSpeed)
{
    m_Speed = intakeSpeed;
    m_IndexerSpeed = indexerSpeed;
}

void Intake::SetExtended(bool extended)
{
    m_IntakeExtended = extended;
}

void Intake::handle()
{
    // Extended
    m_SolenoidA->Set(m_IntakeExtended);
    m_SolenoidB->Set(m_IntakeExtended);

    // Intake
    if (m_SolenoidA->Get() && m_SolenoidB->Get())
    {
        m_MotorA->Set(m_Speed);
    }
    else
    {
        m_MotorA->Set(0);
    }

    // Indexer
    m_MotorB->Set(m_IndexerSpeed);
}

Intake::~Intake()
{
    delete m_MotorA;
    delete m_MotorB;
    delete m_SolenoidA;
    delete m_SolenoidB;
}
