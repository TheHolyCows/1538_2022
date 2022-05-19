#include "OperatorController.h"

OperatorController::OperatorController(CowControlBoard *controlboard)
    : m_CB(controlboard)
{}

void OperatorController::handle(CowRobot *bot)
{
    if (m_CB->GetSteeringButton(PID_BUTTON))
    {
        /* limelight tracking here */
    }
    else
    {
        /* standard drive control */
        bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                            m_CB->GetSteeringX(),
                            m_CB->GetSteeringButton(FAST_TURN));
    }
}
