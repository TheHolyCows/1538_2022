//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Conveyor.h
// author: ssemtner
// created on: 2022-2-12
//==================================================

#ifndef SRC_SUBSYSTEMS_CONVEYOR_H_
#define SRC_SUBSYSTEMS_CONVEYOR_H_

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowPID.h"
#include <string>

class Conveyor
{
private:
    CowLib::CowMotorController *m_MotorUpper;
    CowLib::CowMotorController *m_MotorLower;
    float m_SpeedLower;
    float m_SpeedUpper;

public:
    Conveyor(int upperMotor, int lowerMotor);
    void SetSpeed(float speedLower, float speedUpper);
    void handle();
    virtual ~Conveyor();

    float GetLowerSpeed()
    {
        return -m_SpeedLower;
    }
};

#endif /* SRC_SUSBSYTEMS_CONVEYOR_H_ */
