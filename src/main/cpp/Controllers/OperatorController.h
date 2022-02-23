//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __OPERATOR_CONTROLLER_H__
#define __OPERATOR_CONTROLLER_H__

#include <math.h>
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

    enum OperatorButtonMap
    {
        SWITCH_FRONT_INTAKE = 8,
        SWITCH_REAR_INTAKE = 10,
        BUTTON_FRONT_EXHAUST = 4,
        BUTTON_REAR_EXHAUST = 6,
        BUTTON_FRONT_INTAKE = 7,
        BUTTON_REAR_INTAKE = 9,
        BUTTON_SHOOT = 5,
        SWITCH_SHOOTER = 3,
        BUTTON_HOOD_UP = 1,
        BUTTON_HOOD_DOWN = 2,
    };
    //    float time;
    //    float previousTime;
    //    float speed;

public:
    OperatorController(CowControlBoard *controlboard);
    void handle(CowRobot *bot);
};

#endif /* __OPERATOR_CONTROLLER_H__ */
