#include "OperatorController.h"
#include <iostream>

OperatorController::OperatorController(CowControlBoard *controlboard)
    :
    m_CB(controlboard)
{
}

void OperatorController::handle(CowRobot *bot)
{
    float r_color = m_CB->GetOperatorGamepadAxis(2);
    r_color = fabs(r_color*254);
    float g_color = m_CB->GetDriveAxis(2);
    g_color = fabs(g_color*254);
    float b_color = m_CB->GetDriveAxis(0);
    b_color = fabs(b_color*254);
    bot->GetCanifier()->SetLEDColor(r_color, g_color, b_color);
    bool doingTracking = false;
    if(m_CB->GetDriveButton(1))
    {
        bot->DriveDistanceWithHeading(0, 12, 0.2);
	    //doingTracking = true;
    	//bool acquired = bot->DoVisionTracking(-CONSTANT("AUTO_TRACK_SPEED"));
		//if(acquired)
		//{
		//}
    }
    else
    {
       if(m_CB->GetSteeringButton(3))
       {
	        bot->DoVisionTracking(m_CB->GetDriveStickY());
       }
       else
       { 
        bot->GetLimelight()->PutNumber("pipeline", 3);
        bot->GetLimelight()->PutNumber("ledMode", 1);
        bot->DriveSpeedTurn(m_CB->GetDriveStickY(),
                             m_CB->GetSteeringX(),
                             m_CB->GetSteeringButton(FAST_TURN));
      }
    }
    //Arm Switch
    if(m_CB->GetOperatorButton(1))
    {
        //bot->GetArm()->SetPosition(CONSTANT("ARM_GOAL"));
    }
    else if(m_CB->GetOperatorButton(2))
    {
        //bot->GetArm()->SetPosition(CONSTANT("ARM_MID"));
    }
    else if(m_CB->GetOperatorButton(5))
    {
        //bot->GetArm()->SetPosition(CONSTANT("ARM_FAR"));
    }
    else if(m_CB->GetSteeringButton(2))
    {
        //bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
    }
    //Shooter Switch
    if(m_CB->GetOperatorButton(10))
    {
        // if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_GOAL"))
        // {
        // std::cout << CONSTANT("SHOOTER_F_GOAL") << std::endl;
        //bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_GOAL")); //, CONSTANT("SHOOTER_B_GOAL"));
        // }
        // else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_MID"))
        // {
        //     bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_MID"), CONSTANT("SHOOTER_B_MID"));
        // }
        // else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_FAR"))
        // {
        //     bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_FAR"), CONSTANT("SHOOTER_B_FAR"));
        // }
        // else
        // {
        //     bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_ON"), CONSTANT("SHOOTER_B_ON"));
        // }
    }
    else
    {
        //bot->GetShooter()->SetSpeed(0);
    }
    //Conveyor and Intake and Feeder
    if(m_CB->GetOperatorButton(6))
    {
        bot->ExhaustBalls(1);
    }
    else if(m_CB->GetOperatorButton(9)) //Intake
    {
        bot->IntakeBalls(1);
    }
    else if(m_CB->GetOperatorButton(7))//Shoot
    {
        bot->ShootBalls();
    }
    else
    {
        bot->StopRollers();
    }
}

