#include "AutoModes.h"
#include <frc/Errors.h>

AutoModes *AutoModes::m_SingletonInstance = NULL;

AutoModes *AutoModes::GetInstance()
{
	if (m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new AutoModes();
	}
	return m_SingletonInstance;
}

AutoModes::AutoModes()
{
	/** 5 Ball **/
	m_Modes["5 Ball"];
	// reverse to ball 2
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, true, 0.6));

	// shoot 1+2
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_STOP, true, 0.80));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_SHOOT, true, 0.80));

	// prepare to reverse for ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 25, 0.4, false, false, INTAKE_STOP, false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 25, 50, 0.4, false, false, INTAKE_STOP, false, 0.5));

	// reverse to ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 75, 0.6, false, true, INTAKE_R_IN , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -45, 90, 0.6, false, true, INTAKE_R_IN , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -145, 120, 0.6, false, true, INTAKE_R_IN , false, 6));

	// shoot 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -175, 120, 0.45, false, true, INTAKE_R_IN , false, 0.75));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -200, 35, 0.45, false, false, INTAKE_R_IN , false, 0.75));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -200, 40, 0, false, false, INTAKE_R_IN, true, 1));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -200, 40, 0, false, false, INTAKE_SHOOT, true, 0.5));

	// route to 4 + 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -253, 65, 0.6, false, true, INTAKE_STOP , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -348, 45, 0.3, false, true, INTAKE_R_IN , false, 1.6));

	// shoot 4 + 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -280, 90, 0.8, false, false, INTAKE_R_IN , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -280, 40, 0.3, false, false, INTAKE_STOP , false, 0.5));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -280, 0, 0, false, false, INTAKE_STOP, true, 0.80));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -280, 0, 0, false, false, INTAKE_SHOOT, true, 1.0));


	/** 4 Ball **/
	m_Modes["4 Ball"];
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -28, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -38, 0, 0.3, false, true, INTAKE_R_IN, true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -57, 0, 0.2, false, true, INTAKE_R_IN, true, 0.8));

	// shoot 2
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -40, 0, 0.2, false, true, INTAKE_R_IN, true, 0.75));

	// shoot 1+2
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -35, 0, 0, false, false, INTAKE_STOP, true, 1.0));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -35, 0, 0, false, false, INTAKE_SHOOT, true, 1.0));

	// route to ball 3 and 4
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -10, -23, 0.3, false, true, INTAKE_STOP, false, 1.15));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -50, 10, 0.5, false, true, INTAKE_STOP, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -105, 45, 0.5, false, true, INTAKE_STOP, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -145, 10, 0.45, false, true, INTAKE_R_IN, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, -15, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -303, -22, 0.2, false, true, INTAKE_R_IN, false, 1.75));

	// shoot 3 and 4
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, -5, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 10, 0.5, false, false, INTAKE_STOP, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 40, 0.45, false, false, INTAKE_STOP, false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -50, 15, 0.5, false, false, INTAKE_STOP, true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -30, -10, 0.35, false, false, INTAKE_STOP, true, 0.75));

	m_Modes["4 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -30, -10, 0, false, false, INTAKE_STOP, true, 1.0));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -30, -10, 0, false, false, INTAKE_SHOOT, true, 1.5));


	m_Modes["3 Ball"];
	// reverse to ball 2
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, true, 0.6));

	// shoot 1+2
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_R_IN, true, 0.80));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_SHOOT, true, 1.0));

	// prepare to reverse for ball 3
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 25, 0.35, false, false, INTAKE_STOP, false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 25, 45, 0.35, false, false, INTAKE_STOP, false, 1.0));

	// reverse to ball 3
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 70, 0.5, false, true, INTAKE_R_IN , false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 90, 0.5, false, true, INTAKE_R_IN , false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 100, 0.5, false, true, INTAKE_R_IN , false, 6));

	// shoot 3
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -160, 100, 0.45, false, true, INTAKE_R_IN , false, 0.75));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -180, 40, 0.45, false, false, INTAKE_STOP , false, 1));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -180, 40, 0, false, false, INTAKE_STOP, true, 0.66));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -180, 40, 0, false, false, INTAKE_SHOOT, true, 1.0));


	/** 2 Ball **/
	m_Modes["2 Ball"];
	// reverse to ball 2
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, true, 0.6));

	// shoot 1+2
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_STOP, true, 1.5));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_SHOOT, true, 1.0));


	

	

	// m_Modes["5 Ball - slow"];
	// // ball 1
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, true, 0.3));

	// // shoot 2
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 6, 0.4, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_STOP, true, .75));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_SHOOT, true, 1));

	// // route to ball 3
	// // drive forward for reverse turn
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 37, 45, 0.3, false, true, INTAKE_STOP, false, 1));

	// // reverse into ball 3
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 15, 60, 0.3, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -7, 75, 0.5, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 100, 0.5, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 110, 0.8, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 130, 0.5, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 130, 0.3, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -170, 130, 0.2, false, true, INTAKE_R_IN, false, 0.5));

	// // route to shoot ball 3
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 140, 0.35, false, true, INTAKE_STOP, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 115, 0.5, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 95, 0.7, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -55, 70, 0.3, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.2, false, true, INTAKE_STOP, true, .75));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.1, false, true, INTAKE_SHOOT, true, 1));

	// // route to balls 4 and 5
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 55, 0.3, false, true, INTAKE_STOP, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -75, 80, 0.5, false, true, INTAKE_STOP, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 100, 0.8, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -160, 130, 0.6, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 90, 0.4, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, false, 1.5));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, false, 2));

	// // shoot 4 and 5
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, 100, 0.3, false, true, INTAKE_R_IN, false, 1.5));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 90, 0.3, false, true, INTAKE_R_IN, false, 1.5));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 90, 0.3, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 80, 0.3, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 53, 0.45, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 27, 0.35, false, true, INTAKE_STOP, true, 6));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.2, false, true, INTAKE_STOP, true,0.8));
	// m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.1, false, true, INTAKE_SHOOT, true, 1));

	/** Do Nothing **/
	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, false, 1));

	/** Move Around **/
	m_Modes["Leave Start Zone"];
	m_Modes["Leave Start Zone"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -30, 0, 0.4, false, false, INTAKE_STOP, false, 4));

	m_Modes["Leave And Ret"];
	m_Modes["Leave And Ret"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -30, 0, 0.4, false, false, INTAKE_STOP, false, 4));
	m_Modes["Leave And Ret"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.4, false, false, INTAKE_STOP, false, 4));
	

	// m_Modes["Test_Turn"];
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, false, 1));
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_TURN, 0, 45, 0.2, false, false, INTAKE_STOP, false, 1));
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, false, 1));

	// m_Modes["Test_Intake"];
	// m_Modes["Test_Intake"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, false, 2));
	// m_Modes["Test_Intake"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 20, 0, 0.4, true, false, INTAKE_F_IN, false, 4));

	m_Iterator = m_Modes.begin();
}

std::deque<RobotCommand> AutoModes::GetCommandList()
{
	return m_Iterator->second;
}

const char *AutoModes::GetName()
{
	return m_Iterator->first;
}

void AutoModes::NextMode()
{
	++m_Iterator;
	if (m_Iterator == m_Modes.end())
	{
		m_Iterator = m_Modes.begin();
	}
	std::string str(GetName());
	std::string temp = "Auto mode: " + str;
	FRC_ReportError(frc::err::Error, "{}", temp);
}