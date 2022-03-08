//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COWLIB_COWMOTORCONTROLLER_H__
#define __COWLIB_COWMOTORCONTROLLER_H__

#include "ctre/Phoenix.h"

namespace CowLib
{
    class CowMotorController
    {
    public:
        enum CowNeutralMode
        {
            JUMPER,
            BRAKE,
            COAST,
        };

        enum CowControlMode
        {
            PERCENTVBUS,
            CURRENT,
            SPEED,
            POSITION,
            VOLTAGE,
            FOLLOWER,
            MOTIONPROFILE,
            MOTIONMAGIC
        };

        CowMotorController(int deviceNum);
        virtual ~CowMotorController();

        void SetClosedLoopError(int error);
        void SetNeutralMode(CowNeutralMode);
        enum CowNeutralMode GetNeutralMode();
        void SetControlMode(CowControlMode);
        enum CowControlMode GetControlMode();
        float GetPosition();
        void SetSensorPosition(float position);
        void SetPIDGains(float pGain, float iGain, float dGain, float fGain, double peakOutput);
        void SetMotionMagic(float accel, float velocity);
        void Set(float);
        void SetInverted(bool Value);
        void SetPeakCurrent(int amps, int ms);
        void SetStatorLimit(float limit, float threshold, float duration);
        double GetOutputCurrent();
        TalonFX *GetInternalMotor();

    private:
        TalonFX *m_MotorController;
        int m_DeviceNum;
        enum CowNeutralMode m_CowNeutralMode;
        enum CowControlMode m_CowControlMode;

        ControlMode TranslateControlMode(enum CowControlMode);
    };
}

#endif /* __COWLIB_COWMOTORCONTROLLER_H__ */
