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
#include "../Declarations.h"
#include <frc/DutyCycle.h>
#include <frc/DigitalSource.h>
#include <frc/DigitalInput.h>
#include <string>

class Conveyor
{
private:
    CowLib::CowMotorController *m_MotorUpper;
    CowLib::CowMotorController *m_MotorFront;
    CowLib::CowMotorController *m_MotorRear;
    float m_SpeedUpper;
    float m_SpeedFront;
    float m_SpeedRear;

    frc::DigitalInput m_ColorSensor;
    frc::DutyCycle *m_DutyCycle;

public:
    Conveyor(int upperMotor, int frontMotor, int rearMotor, int colorSensorPinNum);
    void SetSpeed(float speedUpper, float speedFront, float speedRear);
    frc::DutyCycle* GetColorSensor(void);
    void handle();
    virtual ~Conveyor();
};

#endif /* SRC_SUSBSYTEMS_CONVEYOR_H_ */
