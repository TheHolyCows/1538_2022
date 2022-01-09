#include "AutoModeController.h"
#include <iostream>
#include <frc/Timer.h>

AutoModeController::AutoModeController()
:
m_Timer(new frc::Timer()),
m_CurrentCommand(RobotCommand())
{
	m_Timer->Start();
	reset();

	m_OriginalEncoder = 0;
}

void AutoModeController::SetCommandList(std::deque<RobotCommand> list)
{
	m_CommandList = list;
}

void AutoModeController::reset()
{
	CowConstants::GetInstance();

	m_CommandList.clear();
	m_CurrentCommand = RobotCommand();
}

void AutoModeController::handle(CowRobot *bot)
{
	bool result = false;
        bot->GetLimelight()->PutNumber("pipeline", 0);
        bot->GetLimelight()->PutNumber("ledMode", 1);

    bot->GetArm()->SetPosition(m_CurrentCommand.m_ArmPosition);
	if(m_CurrentCommand.m_IntakeMode == INTAKE_IN)
    {
        bot->IntakeBalls(CONSTANT("INTAKE_PERCENT_AUTO"));
    }
    else if(m_CurrentCommand.m_IntakeMode == INTAKE_OUT)
    {
        bot->ExhaustBalls(CONSTANT("INTAKE_PERCENT_AUTO"));
    }
    else if(m_CurrentCommand.m_IntakeMode == INTAKE_SHOOT)
    {
        bot->ShootBalls();
    }
    else
    {
        bot->StopRollers();
    }
    if(m_CurrentCommand.m_Shooter)
    {
         if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_GOAL"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_GOAL"), CONSTANT("SHOOTER_B_GOAL"));
        }
        else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_MID"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_MID"), CONSTANT("SHOOTER_B_MID"));
        }
        else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_MID_AUTO"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_MID"), CONSTANT("SHOOTER_B_MID"));
        }
        else if (bot->GetArm()->GetSetpoint() == CONSTANT("ARM_FAR"))
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_FAR"), CONSTANT("SHOOTER_B_FAR"));
        }
        else
        {
            bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_F_ON"), CONSTANT("SHOOTER_B_ON"));
        }
    }
    else
    {
        bot->GetShooter()->SetSpeed(0,0);
    }
    // Run the command
	switch(m_CurrentCommand.m_Command)
	{
	case CMD_NULL:
	{
		doNothing(bot);
		result = true;
		break;
	}
	case CMD_WAIT:
	{
		bot->DriveWithHeading(m_CurrentCommand.m_Heading, 0);
		doNothing(bot);
		break;
	}
	case CMD_TURN:
	{
		result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
		break;
	}
	case CMD_TURN_INTAKE:
	{
		result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
		//bot->GetArm()->SetModulatedSpeed(CONSTANT("INTAKE_SPEED"));

		break;
	}
	case CMD_VISION_ALIGN:
	{
		bot->DoVisionTracking(m_CurrentCommand.m_Speed,4.5);

		result = bot->DoVisionTracking(m_CurrentCommand.m_Speed);
		break;
	}
case CMD_HOLD_DISTANCE:
	{
		bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		result = false;
		break;
	}
	case CMD_HOLD_DISTANCE_INTAKE:
	{
		bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
		result = false;
		break;
	}
	case CMD_DRIVE_DISTANCE:
	{
		float direction = 1;
		if(m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			//We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);
		//bot->GetArm()->SetIntakeSpeed(-0.2);

		if(direction == 1) //Going forward
		{
			if(bot->GetDriveDistance()  > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else //Going backward
		{
			if(bot->GetDriveDistance()  < m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}

		break;
	}
	case CMD_DRIVE_DISTANCE_INTAKE:
	{
		float direction = 1;
		if(m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			//We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);
//		bot->GetArm()->SetPosition(CONSTANT("ARM_DOWN"));
		//bot->GetArm()->SetModulatedSpeed(CONSTANT("INTAKE_SPEED"));

		if(direction == 1) //Going forward
		{
			if(bot->GetDriveDistance()  > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else //Going backward
		{
			if(bot->GetDriveDistance()  < m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		break;
	}
	case CMD_INTAKE_EXHAUST:
	{
		doNothing(bot);
		bot->ResetEncoders();
		break;
	}
	default:
	{
		doNothing(bot);
		result = true;
		break;
	}
	}

	//Check if this command is done / .value() because of seconds_t
	if(result == true || m_CurrentCommand.m_Command == CMD_NULL || m_Timer->Get().value() > m_CurrentCommand.m_Timeout)
	{
		// This command is done, go get the next one
		if(m_CommandList.size() > 0 )
		{
			if(m_CurrentCommand.m_Command == CMD_TURN) 
			{
				bot->ResetEncoders();
			}
			m_CurrentCommand = m_CommandList.front();
			m_OriginalEncoder = bot->GetDriveDistance();
			m_CommandList.pop_front();
			//bot->GetEncoder()->Reset();

			if(!m_CurrentCommand.m_Command == CMD_NULL)
			{
				printf("Time elapsed: %f\n", m_Timer->Get().value());
			}
		}
		else
		{
			// We're done clean up
			m_CurrentCommand = RobotCommand();
		}
		m_Timer->Reset();
	}
}

// Drive Functions
void AutoModeController::doNothing(CowRobot *bot)
{
	bot->DriveLeftRight(0, 0);
	bot->StopRollers();
}
