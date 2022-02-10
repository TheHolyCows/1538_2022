#ifndef SRC_SUBSYSTEMS_CONVEYOR_H_
#define SRC_SUBSYSTEMS_CONVEYOR_H_

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowPID.h"
#include <string>

class Conveyor
{
private:
    CowLib::CowMotorController *m_MotorA;
    CowLib::CowMotorController *m_MotorB;
    float m_SpeedL;
    float m_SpeedU;

public:
    Conveyor(int motorControllerA, int motorControllerB, bool changeDirectionA, bool changeDirectionB);
    void SetSpeed(float speedL, float speedU);
    void handle();
    virtual ~Conveyor();
};

#endif /* SRC_SUSBSYTEMS_CONVEYOR_H_ */
