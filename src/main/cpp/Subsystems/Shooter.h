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
#include <wpi/deprecated.h>
#include <frc/Timer.h>
#include <string>

class Shooter
{
public:
        Shooter(int motorControllerF, int motorControllerB, bool changeDirectionF, bool changeDirectionB);
        bool AtTarget();
        void SetSpeed(float speedF, float speedB);
        float GetSetpointF()
        {
            return m_SpeedF;
        }
        float GetSetpointB()
        {
            return m_SpeedB;
        }
        void ResetConstants();
        void SetClosedLoopError(int error)
        {
            if(m_MotorF && m_MotorB)
            {
                m_MotorF->SetClosedLoopError(error);
                m_MotorB->SetClosedLoopError(error);
            }
        }
        void handle();

        float GetSpeedF();
        float GetSpeedB();
        virtual ~Shooter();
private:
    CowLib::CowMotorController *m_MotorF;
    CowLib::CowMotorController *m_MotorB;
    CowLib::CowLPF *m_RampLPF_F;
    CowLib::CowLPF *m_RampLPF_B;

    float m_SpeedF;
    float m_SpeedB;
    bool m_HasShifted_F;
    bool m_HasShifted_B;

};

#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
