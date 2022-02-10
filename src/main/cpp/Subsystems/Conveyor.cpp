#include "Conveyor.h"
#include <iostream>
#include <frc/Timer.h>

Conveyor::Conveyor(int motorControllerA, int motorControllerB, bool changeDirectionA, bool changeDirectionB)
{
    m_MotorA = new CowLib::CowMotorController(motorControllerA);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_SpeedU = 0;
    m_SpeedL = 0;
    m_MotorA->GetInternalMotor()->SetInverted(changeDirectionA);
    m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
}

void Conveyor::SetSpeed(float speedL, float speedU)
{
    m_SpeedL = speedL;
    m_SpeedU = speedU;
}

void Conveyor::handle()
{
    // Upper
    m_MotorA->Set(m_SpeedU);

    // Lower
    m_MotorB->Set(m_SpeedL);
}

Conveyor::~Conveyor()
{
    delete m_MotorA;
    delete m_MotorB;
}
