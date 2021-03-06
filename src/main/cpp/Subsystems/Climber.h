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
#include "../CowLib/CowTimer.h"

class Climber
{
private:
    CowLib::CowMotorController *m_LeftMotor;
    CowLib::CowMotorController *m_RightMotor;

    float m_LeftPosition;
    float m_RightPosition;

    int m_State = 0;
    void ClimberSM(void);

    enum CLIMB_STATE
    {
        NONE = 0,
        EXT_BOTH,
        CLIMB_MID,
        EXT_LEFT_MID,
        CLIMB_HIGH,
        EXT_RIGHT_HIGH,
        EXT_RIGHT_TRAV,
        CLIMB_TRAV,
    };

public:
    Climber(int leftMotor, int rightMotor);

    void SetLeftPosition(float position);
    void SetRightPosition(float position);

    float GetLeftPosition();
    float GetRightPosition();

    float GetLeftSetpoint()
    {
        return m_LeftPosition;
    }
    float GetRightSetpoint()
    {
        return m_RightPosition;
    }

    void NextState(void);
    void PrevState(void);

    // bool LeftAtTarget();
    // bool RightAtTarget();
    // bool AtTarget()
    // {
    //     return LeftAtTarget() && RightAtTarget();
    // }

    void ResetConstants();

    void handle();

    virtual ~Climber();
};

#endif /* SRC_SUBSYSTEMS_CLIMBER_H_ */