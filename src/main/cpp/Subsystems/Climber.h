//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Climber.h
// author: ssemtner
// created on: 2022-3-17
//==================================================

#ifndef SRC_SUBSYSTEMS_CLIMBER_H_
#define SRC_SUBSYSTEMS_CLIMBER_H_

#include <iostream>
#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"

class Climber
{
private:
    CowLib::CowMotorController *m_LeftMotor;
    CowLib::CowMotorController *m_RightMotor;

    float m_LeftPosition;
    float m_RightPosition;

public:
    Climber(int leftMotor, int rightMotor);

    void SetLeftPosition(float position);
    void SetRightPosition(float position);

    float GetLeftPosition();
    float GetRightPosition();

    bool LeftAtTarget();
    bool RightAtTarget();
    bool AtTarget()
    {
        return LeftAtTarget() && RightAtTarget();
    }

    void ResetConstants();

    void handle();

    virtual ~Climber();
};

#endif /* SRC_SUBSYSTEMS_CLIMBER_H_ */