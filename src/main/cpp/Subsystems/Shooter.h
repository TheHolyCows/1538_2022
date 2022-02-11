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
    Shooter(int motorControllerF, int motorControllerV, bool changeDirectionF);
    bool AtTarget();
    void SetSpeed(float speedF);
    float GetSetpointF()
    {
        return m_SpeedF;
    }

    void ResetConstants();
    void SetClosedLoopError(int error)
    {
        if (m_MotorF)
        {
            m_MotorF->SetClosedLoopError(error);
        }
    }
    void handle();

    float GetSpeedF();
    virtual ~Shooter();

private:
    CowLib::CowMotorController *m_MotorF;
    CowLib::CowMotorController *m_MotorV;
    CowLib::CowLPF *m_RampLPF_F;

    float m_SpeedF;

    CowLib::CowLogger *m_LogServer;
};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
