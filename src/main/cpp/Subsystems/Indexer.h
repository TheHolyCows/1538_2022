#ifndef SRC_SUBSYSTEMS_CONVEYOR_H_
#define SRC_SUBSYSTEMS_CONVEYOR_H_

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowPID.h"
#include <string>

class Indexer
{
private:
    CowLib::CowMotorController *m_MotorA;
    CowLib::CowMotorController *m_MotorB;
    float m_SpeedF;
    float m_SpeedR;

public:
    Indexer(int motorControllerA, int motorControllerB, bool changeDirectionA, bool changeDirectionB);
    void SetSpeed(float speedF, float speedR);
    void handle();
    virtual ~Indexer();
};

#endif /* SRC_SUBSYSTEMS_CONVEYOR_H_ */
