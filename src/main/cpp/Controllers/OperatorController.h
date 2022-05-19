//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __OPERATOR_CONTROLLER_H__
#define __OPERATOR_CONTROLLER_H__

#include "../CowRobot.h"
#include "../CowControlBoard.h"
#include "../CowLib/CowLib.h"
#include "../CowConstants.h"
#include "../CowLib/CowLatch.h"

class OperatorController : public GenericController
{
private:
    OperatorController();
    CowControlBoard *m_CB;

    enum OperatorButtonMap
    {
        OP_BUTTON_1 = 1,
        OP_BUTTON_2 = 2,
        OP_BUTTON_3 = 3,
        OP_BUTTON_4 = 4,
        OP_BUTTON_5 = 5,
        OP_BUTTON_6 = 6,
        OP_BUTTON_7 = 7,
        OP_BUTTON_8 = 8,
        OP_BUTTON_9 = 9,
        OP_BUTTON_10 = 10,
        OP_BUTTON_11 = 11,
        OP_BUTTON_12 = 12,
        OP_BUTTON_13 = 13,
        OP_BUTTON_14 = 14,
        OP_BUTTON_15 = 15,
        OP_BUTTON_16 = 16,
        OP_BUTTON_17 = 17,
        OP_BUTTON_18 = 18
    };

public:
    OperatorController(CowControlBoard *controlboard);
    void handle(CowRobot *bot);
};

#endif /* __OPERATOR_CONTROLLER_H__ */
