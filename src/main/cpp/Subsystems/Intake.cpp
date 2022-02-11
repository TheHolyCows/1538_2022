#include "Intake.h"
#include <iostream>
#include <frc/Timer.h>
#include <frc/Solenoid.h>

Intake::Intake(int motorControllerA, int motorControllerB, int solenoidChannel)
{
    m_MotorA = new CowLib::CowMotorController(motorControllerA);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_Solenoid = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, solenoidChannel);
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
    // Intake
    if (m_IntakeExtended)
    {
        m_MotorA->Set(m_Speed);
    }
    else
    {
        m_MotorA->Set(0);
    }

    // Indexer
    m_MotorB->Set(m_IndexerSpeed);

    // Position
    m_Solenoid->Set(m_IntakeExtended);
}

Intake::~Intake()
{
    delete m_MotorA;
    delete m_MotorB;
    // delete m_Solenoid
}
