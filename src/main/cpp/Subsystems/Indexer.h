#ifndef SRC_SUBSYSTEMS_INDEXER_H_
#define SRC_SUBSYSTEMS_INDEXER_H_

#include "../CowLib/CowMotorController.h"
#include "../CowLib/CowLPF.h"
#include "../CowConstants.h"
#include "../CowLib/CowPID.h"
#include <string>

class Indexer
{
private:
    CowLib::CowMotorController *m_Motor;
    float m_Speed;

public:
    Indexer(int motorController, bool changeDirection);
    void SetSpeed(float speed);
    void handle();
    virtual ~Indexer();
};

#endif /* SRC_SUBSYSTEMS_INDEXER_H_ */
