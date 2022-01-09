#include "Conveyor.h"
#include <iostream>
#include <frc/Timer.h>

Conveyor::Conveyor(int motorControllerA, int motorControllerB, int motorControllerC, bool changeDirectionA, bool changeDirectionB, bool changeDirectionC)
{
    m_MotorA = new CowLib::CowMotorController(motorControllerA);
    m_MotorB = new CowLib::CowMotorController(motorControllerB);
    m_MotorC = new CowLib::CowMotorController(motorControllerC);
    m_SpeedU = 0;
    m_SpeedL = 0;
    m_MotorA->GetInternalMotor()->SetInverted(changeDirectionA);
    m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
    m_MotorC->GetInternalMotor()->SetInverted(changeDirectionC);
}

void Conveyor::SetSpeed(float speedL, float speedU)
{
    m_SpeedL = speedL;
    m_SpeedU = speedU;
}

void Conveyor::handle()
{
    //Upper
    m_MotorA->Set(m_SpeedU);
   //Upper 
    m_MotorB->Set(m_SpeedL);
    m_MotorC->Set(m_SpeedL);
}

Conveyor::~Conveyor()
{
    delete m_MotorA;
    delete m_MotorB;
    delete m_MotorC;
}
