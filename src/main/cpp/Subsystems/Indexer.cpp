#include "Indexer.h"
#include <iostream>
#include <frc/Timer.h>

Indexer::Indexer(int motorController, bool changeDirection)
{
    m_Motor = new CowLib::CowMotorController(motorController);
    m_Speed = 0;
    m_Motor->GetInternalMotor()->SetInverted(changeDirection);
}

void Indexer::SetSpeed(float speed)
{
    m_Speed = speed;
}

void Indexer::handle()
{
    // Front
    m_Motor->Set(m_Speed);
}

Indexer::~Indexer()
{
    delete m_Motor;
}
