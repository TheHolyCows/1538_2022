//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Intake.h
// author: ssemtner
// created on: 2022-2-12
//==================================================

#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include "../CowLib/CowLPF.h"
#include "../CowLib/CowPID.h"
#include <frc/Solenoid.h>

class Intake
{
private:
    CowLib::CowMotorController *m_MotorIntake;
    CowLib::CowMotorController *m_MotorIndex;
    frc::Solenoid *m_SolenoidA;
    frc::Solenoid *m_SolenoidB;
    float m_IntakeSpeed;
    float m_IndexSpeed;
    bool m_IntakeExtended;

public:
    Intake(int intakeMotor, int indexMotor, int solenoidChannelA, int solenoidChannelB);
    void SetSpeed(float intakeSpeed, float indexSpeed);
    void SetExtended(bool extended);
    bool GetExtended()
    {
        return m_IntakeExtended;
    }
    void handle();
    virtual ~Intake();
};

#endif /* SRC_SUBSYSTEMS_ARM_H */
