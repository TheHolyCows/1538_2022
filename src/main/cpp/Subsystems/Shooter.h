/*
 * Shooter.h
 *
 *  Created on: Mar 8, 2020
 *      Author: fcoughlin
 */

#ifndef __SRC_SUBSYSTEMS_SHOOTER_H__
#define __SRC_SUBSYSTEMS_SHOOTER_H__

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowLogger.h"
#include <wpi/deprecated.h>
#include <frc/Timer.h>
#include <string>

class Shooter
{
public:
    Shooter(int motorControllerF, int motorControllerH, bool changeDirectionF);
    bool AtTarget();
    void SetSpeed(float speedF);
    void SetHoodPosition(float position);
    float GetSetpointF()
    {
        return m_SpeedS;
    }
    float GetSetpointH()
    {
        return m_HoodPosition;
    }

    void ResetConstants();
    void SetClosedLoopError(int error)
    {
        if (m_MotorS)
        {
            m_MotorS->SetClosedLoopError(error);
        }
    }
    void handle();

    float GetSpeedF();
    float GetHoodPosition();

    virtual ~Shooter();

private:
    CowLib::CowMotorController *m_MotorS;
    CowLib::CowMotorController *m_MotorH;
    CowLib::CowLPF *m_RampLPF_F;

    float m_SpeedS;

    float m_HoodPosition;
    float m_HoodUpLimit;
    float m_HoodDownLimit;

    CowLib::CowLogger *m_LogServer;
};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
