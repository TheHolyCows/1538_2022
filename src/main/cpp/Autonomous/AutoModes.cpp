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
	// m_Modes["testing_intakes"];
	// m_Modes["testing_intakes"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 2));
	// m_Modes["testing_intakes"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0, false, false, INTAKE_SHOOT, CONSTANT("HOOD_UP"), true, 10));

	m_Modes["5 Ball"];
	// ball 1
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), true, 0.3));

	// shoot 2
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 6, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, .75));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 12, 0.2, false, true, INTAKE_SHOOT, CONSTANT("HOOD_UP"), true, 1));

	// route to ball 3
	// drive forward for reverse turn
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 37, 45, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 1));

	// reverse into ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 15, 60, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -7, 75, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 100, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 110, 0.8, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 130, 0.5, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 130, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -170, 130, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 0.5));

	// route to shoot ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 140, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 115, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 95, 0.7, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -55, 70, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, .75));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -20, 40, 0.1, false, true, INTAKE_SHOOT, CONSTANT("HOOD_UP"), true, 1));

	// route to balls 4 and 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 55, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -75, 80, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 100, 0.8, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -160, 130, 0.6, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 90, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1.5));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -310, 45, 0.15, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 2));

	// shoot 4 and 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, 100, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1.5));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 90, 0.3, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1.5));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 90, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 80, 0.3, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 53, 0.45, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 27, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), true,0.8));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 27, 0.1, false, true, INTAKE_SHOOT, CONSTANT("HOOD_UP"), true, 1));

	

	m_Modes["2 Ball"]; // Not tested yet
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -40, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), true, 2));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.4, false, false, INTAKE_SHOOT, CONSTANT("HOOD_UP"), true, 4));

	m_Modes["Bad Idea (Testing)"];
	// m_Modes["Bad Idea (Testing)"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 10, 0, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 4));
	// m_Modes["Bad Idea (Testing)"].push_back(RobotCommand(CMD, 0, 90, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 2));
	m_Modes["Bad Idea (Testing)"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 10, 45, 0.1, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 2));

	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	m_Modes["Test_Turn"];
	m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));
	m_Modes["Test_Turn"].push_back(RobotCommand(CMD_TURN, 0, 45, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));
	m_Modes["Test_Turn"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 1));

	m_Modes["Test_Intake"];
	m_Modes["Test_Intake"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 2));
	m_Modes["Test_Intake"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 20, 0, 0.4, true, false, INTAKE_F_IN, CONSTANT("HOOD_UP"), false, 4));

	m_Modes["Taxi"];
	m_Modes["Taxi"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 0, 0.5, false, false, INTAKE_STOP, CONSTANT("HOOD_DOWN"), false, 4));

	// m_Modes["2 Ball - Opponent Trench Run"];
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_TURN, 0, -29, 0.4, CONSTANT("ARM_MID_AUTO"), INTAKE_STOP, true, .6));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, -29, 0.4, CONSTANT("ARM_MID_AUTO"), INTAKE_STOP, true, 3));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, -29, 0.4, CONSTANT("ARM_MID_AUTO"), INTAKE_SHOOT, true, 2));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, -29, 0.4, CONSTANT("ARM_DOWN"), INTAKE_STOP, true, .4));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_TURN, 0, 0, 0.4, CONSTANT("ARM_DOWN"), INTAKE_STOP, true, .6));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 208, 0, 0.4, CONSTANT("ARM_DOWN"), INTAKE_IN, true, 8));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, -19, 1, CONSTANT("ARM_DOWN"), INTAKE_IN, true, 5));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_TURN, 0, 0, 0.4, CONSTANT("ARM_MID_AUTO"), INTAKE_STOP, true, .4));
	// m_Modes["2 Ball - Opponent Trench Run"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 0, 0.4, CONSTANT("ARM_MID_AUTO"), INTAKE_SHOOT, true, 10));
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