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
    CowLib::CowMotorController *m_MotorA;
    CowLib::CowMotorController *m_MotorB;
    frc::Solenoid *m_SolenoidA;
    frc::Solenoid *m_SolenoidB;
    float m_Speed;
    float m_IndexerSpeed;
    bool m_IntakeExtended;

public:
    Intake(int motorControllerA, int motorControllerB, int solenoidChannelA, int solenoidChannelB);
    void SetSpeed(float intakeSpeed, float indexerSpeed);
    void SetExtended(bool extended);
    bool GetExtended()
    {
        return m_IntakeExtended;
    }
    void handle();
    virtual ~Intake();
};

#endif /* SRC_SUBSYSTEMS_ARM_H */
