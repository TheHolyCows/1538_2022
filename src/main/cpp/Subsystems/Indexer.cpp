#include "Indexer.h"
#include <iostream>
#include <frc/Timer.h>

Indexer::Indexer(int motorControllerA, int motorControllerB, bool changeDirectionA, bool changeDirectionB)
{
    m_MotorA = new CowLib::CowMotorController(motorControllerA);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_SpeedF = 0;
    m_SpeedR = 0;
    m_MotorA->GetInternalMotor()->SetInverted(changeDirectionA);
    m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
}

void Indexer::SetSpeed(float speedF, float speedR)
{
    m_SpeedF = speedF;
    m_SpeedR = speedR;
}

void Indexer::handle()
{
    // Front
    m_MotorA->Set(m_SpeedF);

    // Rear
    m_MotorB->Set(m_SpeedR);
}

Indexer::~Indexer()
{
    delete m_MotorA;
    delete m_MotorB;
}
