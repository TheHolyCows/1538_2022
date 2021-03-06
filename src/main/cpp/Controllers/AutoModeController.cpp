#include "AutoModeController.h"
#include <iostream>

AutoModeController::AutoModeController()
	: m_Timer(new CowLib::CowTimer()),
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

	bot->GetLimelight()->SetMode(Limelight::LIMELIGHT_TRACKING);

	// Set intake and hood positions
	bot->GetIntakeF()->SetExtended(m_CurrentCommand.m_FrontIntakeExtended);
	bot->GetIntakeR()->SetExtended(m_CurrentCommand.m_RearIntakeExtended);

	// auto hood adjustments
	float yPercent = bot->GetLimelight()->CalcYPercent();

	float hoodDelta = CONSTANT("TARGET_Y_FAR") - CONSTANT("TARGET_Y_CLOSE");
	float autoHoodPos = CONSTANT("TARGET_Y_FAR") - (hoodDelta * yPercent);

	bot->GetShooter()->SetHoodPosition(autoHoodPos);

	bot->ResetConveyorMode();
	bot->ResetIntakeMode(false);
	bot->ResetIntakeMode(true);

	if (m_CurrentCommand.m_IntakeMode == INTAKE_F_IN)
	{
		bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, false, CONSTANT("INTAKE_PERCENT_AUTO"));
		bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE, false);
	}
	else if (m_CurrentCommand.m_IntakeMode == INTAKE_R_IN)
	{
		bot->SetIntakeMode(CowRobot::INTAKE_INTAKE, true, CONSTANT("INTAKE_PERCENT_AUTO"));
		bot->SetConveyorMode(CowRobot::CONVEYOR_INTAKE, false);
	}
	else if (m_CurrentCommand.m_IntakeMode == INTAKE_F_OUT)
	{
		
		m_ExhaustMode = false;
		bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, false, CONSTANT("INTAKE_PERCENT_AUTO"));
		bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST, m_ExhaustMode);
	}
	else if (m_CurrentCommand.m_IntakeMode == INTAKE_R_OUT)
	{
		m_ExhaustMode = true;
		bot->SetIntakeMode(CowRobot::INTAKE_EXHAUST, true, CONSTANT("INTAKE_PERCENT_AUTO"));
		bot->SetConveyorMode(CowRobot::CONVEYOR_EXHAUST, m_ExhaustMode);
	}
	else if (m_CurrentCommand.m_IntakeMode == INTAKE_SHOOT)
	{
		bot->ShootBalls();
	}
	else if (m_CurrentCommand.m_IntakeMode == INTAKE_TOP_OUT)
	{
		// because of the weird speeds here this is special
        bot->GetShooter()->SetHoodPositionBottom();
        bot->GetShooter()->SetSpeed(CONSTANT("SHOOTER_SPEED_BOTTOM"));
        bot->GetShooter()->SetHoodRollerSpeed(CONSTANT("HOOD_ROLLER_SPEED_BOTTOM"));
        bot->ShootBalls();
	}
	else
	{
		bot->StopRollers();
	}

	bot->SetConveyorMode(CowRobot::CONVEYOR_OFF, m_ExhaustMode);
	bot->SetIntakeMode(CowRobot::INTAKE_OFF, false);
	bot->SetIntakeMode(CowRobot::INTAKE_OFF, true);

	if (m_CurrentCommand.m_Shooter)
	{
		bot->RunShooter();
	}
	else if (m_CurrentCommand.m_IntakeMode != INTAKE_TOP_OUT)
	{
		bot->GetShooter()->SetSpeed(0);
		bot->GetShooter()->SetHoodRollerSpeed(0);
	}

	// LED feedback for autos
	// if (m_CurrentCommand.m_IntakeMode == INTAKE_SHOOT)
	// {
	// 	bot->GetCanifier()->FlashColor(CONSTANT("COLOR_ALIGNED_R"), CONSTANT("COLOR_ALIGNED_G"), CONSTANT("COLOR_ALIGNED_B"));
	// }
	// else if (m_CurrentCommand.m_Shooter)
	// {
	// 	bot->GetCanifier()->SetLEDColor(CONSTANT("COLOR_SPEED_R"), CONSTANT("COLOR_SPEED_G"), CONSTANT("COLOR_SPEED_B"));
	// }
	// else
	// {
	// 	bot->GetCanifier()->SetLEDColor(0, 0, 0);
	// }

	// Run the command
	switch (m_CurrentCommand.m_Command)
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
	case CMD_TURN_INTAKE: // Why does this exist?
	{
		result = bot->TurnToHeading(m_CurrentCommand.m_Heading);
		break;
	}
	case CMD_VISION_ALIGN:
	{
		bot->DoVisionTracking(0, CONSTANT("TRACKING_THRESHOLD"));
		break;
	}
	case CMD_HOLD_DISTANCE:
	{
		bot->DriveDistanceWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_EncoderCount, m_CurrentCommand.m_Speed);
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
		// std::cout << "OriginalEncoder: " << m_OriginalEncoder << "  EncoderCount: " << m_CurrentCommand.m_EncoderCount << std::endl;
		if (m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			// We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);

		if (direction == 1) // Going forward
		{
			if (bot->GetDriveDistance() > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else // Going backward
		{
			if (bot->GetDriveDistance() < m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}

		break;
	}
	case CMD_DRIVE_DISTANCE_INTAKE:
	{
		float direction = 1;
		if (m_OriginalEncoder > m_CurrentCommand.m_EncoderCount)
		{
			// We want to go backward
			direction = -1;
		}

		bot->DriveWithHeading(m_CurrentCommand.m_Heading, m_CurrentCommand.m_Speed * direction);

		if (direction == 1) // Going forward
		{
			if (bot->GetDriveDistance() > m_CurrentCommand.m_EncoderCount)
			{
				result = true;
			}
		}
		else // Going backward
		{
			if (bot->GetDriveDistance() < m_CurrentCommand.m_EncoderCount)
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

	// Check if this command is done / .value() because of seconds_t
	if (result == true || m_CurrentCommand.m_Command == CMD_NULL || m_Timer->Get() > m_CurrentCommand.m_Timeout)
	{
		// This command is done, go get the next one
		if (m_CommandList.size() > 0)
		{
			if (m_CurrentCommand.m_Command == CMD_TURN)
			{
				bot->ResetEncoders();
			}
			m_CurrentCommand = m_CommandList.front();
			m_OriginalEncoder = bot->GetDriveDistance();
			m_CommandList.pop_front();
			// bot->GetEncoder()->Reset();

			if (!m_CurrentCommand.m_Command == CMD_NULL)
			{
				printf("Time elapsed: %f\n", m_Timer->Get());
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
