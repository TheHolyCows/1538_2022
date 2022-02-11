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
    frc::Solenoid *m_Solenoid;
    float m_Speed;
    float m_IndexerSpeed;
    bool m_IntakeExtended;

public:
    Intake(int motorControllerA, int motorControllerB, int solenoidChannel);
    void SetSpeed(float intakeSpeed, float indexerSpeed);
    void SetExtended(bool extended);
    void handle();
    virtual ~Intake();
};

#endif /* SRC_SUBSYSTEMS_ARM_H */
