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
#include <frc/Solenoid.h>

class Climber
{
private:
    CowLib::CowMotorController *m_MotorController;
    frc::Solenoid *m_SolenoidLock;
    frc::Solenoid *m_SolenoidPTO;

    float m_EncoderInchPerTick;

    float m_Speed;

    bool m_Locked;
    bool m_PTOEngaged;

public:
    Climber(int motor, int solenoidLock, int solenoidPTO);

    void SetSpeed(float speed);
    void SetLockState(bool locked);
    void SetPTOEngaged(bool engaged);

    void SetEnabled(bool enabled);

    // float GetSetpoint()
    // {
    //     return m_Position;
    // };

    float GetSpeed()
    {
        return m_Speed;
    }

    bool GetLockState()
    {
        return m_Locked;
    };
    bool GetPTOEngage()
    {
        return m_PTOEngaged;
    };

    float GetDistance();

    void ResetConstants();

    bool AtTarget();

    void handle();
    virtual ~Climber();
};

#endif /* SRC_SUBSYSTEMS_CLIMBER_H_ */