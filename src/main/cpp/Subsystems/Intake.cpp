#include "Intake.h"
#include <iostream>
#include <frc/Timer.h>

Intake::Intake(int motorController)
{
    m_Motor = new CowLib::CowMotorController(motorController);
    m_Speed = 0;
}

void Intake::SetSpeed(float speed)
{
    m_Speed = speed;
}


void Intake::handle()
{
    m_Motor->Set(m_Speed);
}


Intake::~Intake()
{
    delete m_Motor;
}
