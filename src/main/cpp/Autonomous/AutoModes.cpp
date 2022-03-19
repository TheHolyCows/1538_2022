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
	/** 4 Ball **/
	m_Modes["4 Ball"];
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -28, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -38, 0, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -57, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 0.8));

	// shoot 2
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 10, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -10, -20, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 4));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 6, -21, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 1.15));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 6, -21, 0.2, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1.15));

	// route to ball 3 and 4
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -10, -23, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -50, 10, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 45, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -185, 10, 0.45, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, -15, 0.45, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -307, -20, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 1.75));

	// shoot 3 and 4
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, -5, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 10, 0.5, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 40, 0.45, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -57, 0, 0.5, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, -13, 0.35, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 2, -23, 0.3, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 1.75));
	m_Modes["4 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 2, -23, 0.3, false, false, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1.5));

	/** 2 Ball **/
	m_Modes["2 Ball"];
	// ball 1
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -53, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 0.3));

	// shoot 2
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 0, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, .75));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.2, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));


	/** 3 Ball **/
	m_Modes["5 Ball - slow"];
	// ball 1
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 0.3));

	// shoot 2
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 6, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, .75));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));

	// route to ball 3
	// drive forward for reverse turn
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 37, 45, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	// reverse into ball 3
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 15, 60, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -7, 75, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 100, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 110, 0.8, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 130, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 130, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -170, 130, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 0.5));

	// route to shoot ball 3
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 140, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 115, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 95, 0.7, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -55, 70, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, .75));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.1, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));

	/** 5 Ball **/
	m_Modes["5 Ball - slow"];
	// ball 1
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), true, 0.3));

	// shoot 2
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 6, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, .75));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));

	// route to ball 3
	// drive forward for reverse turn
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 37, 45, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	// reverse into ball 3
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 15, 60, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -7, 75, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 100, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 110, 0.8, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 130, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 130, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -170, 130, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 0.5));

	// route to shoot ball 3
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 140, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 115, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 95, 0.7, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -55, 70, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, .75));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.1, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));

	// route to balls 4 and 5
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 55, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -75, 80, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 100, 0.8, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -160, 130, 0.6, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 90, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 1.5));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 2));

	// shoot 4 and 5
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, 100, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 1.5));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 90, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_DOWN"), false, 1.5));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 90, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 80, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 53, 0.45, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 27, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true, 6));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_DOWN"), true,0.8));
	m_Modes["5 Ball - slow"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.1, false, true, INTAKE_SHOOT, CONSTANT("HOOD_DOWN"), true, 1));

	/** Do Nothing **/
	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	/** Move Around **/
	m_Modes["Leave Start Zone"];
	m_Modes["Leave Start Zone"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -30, 0, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 4));

	m_Modes["Leave And Ret"];
	m_Modes["Leave And Ret"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -30, 0, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 4));
	m_Modes["Leave And Ret"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 4));
	

	// m_Modes["Test_Turn"];
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_TURN, 0, 45, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));
	// m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	// m_Modes["Test_Intake"];
	// m_Modes["Test_Intake"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 2));
	// m_Modes["Test_Intake"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 20, 0, 0.4, true, false, INTAKE_F_IN, CONSTANT("HOOD_DOWN"), false, 4));

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