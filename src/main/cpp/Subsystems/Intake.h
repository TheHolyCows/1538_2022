#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_

#include "../CowLib/CowMotorController.h"
#include "../CowConstants.h"
#include "../CowLib/CowLPF.h"
#include "../CowLib/CowPID.h"

class Intake
{
private:
    CowLib::CowMotorController *m_Motor;
    float m_Speed;

public:
    Intake(int motorController);
    void SetSpeed(float speed);
    void handle();
    virtual ~Intake();
};


#endif /* SRC_SUBSYSTEMS_ARM_H */
