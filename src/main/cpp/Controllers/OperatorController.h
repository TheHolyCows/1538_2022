//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __OPERATOR_CONTROLLER_H__
#define __OPERATOR_CONTROLLER_H__

#include <math.h>
#include <wpi/deprecated.h>
#include "../CowRobot.h"
#include "../CowControlBoard.h"
#include "../CowLib/CowLib.h"
#include "../Declarations.h"
#include "../CowConstants.h"
#include "../CowLib/CowLatch.h"

class OperatorController : public GenericController
{    
private:
    OperatorController();
    CowControlBoard *m_CB;
//    float time;
//    float previousTime;
//    float speed;

public:
    OperatorController(CowControlBoard *controlboard);
    void handle(CowRobot *bot);
};

#endif /* __OPERATOR_CONTROLLER_H__ */
