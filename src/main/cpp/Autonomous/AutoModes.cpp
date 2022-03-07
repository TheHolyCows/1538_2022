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
	// Set up our selection order
	// (Messed up by testing)

	m_Modes["5 Ball"];
	// // m_Modes["5 Ball"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_SHOOT, CONSTANT("HOOD_AUTO_1"), true, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 0, 90, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 50, 90, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 20, 90, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 20, 70, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 0, 70, 0.2, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 3));

	// ball 1
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -23, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -33, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -43, 0, 0.1, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1));
	
	// shoot 2
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -10, 15, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), true, 2));

	// route to ball 3
	// drive forward for reverse turn
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 25, 45, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 0.25));

	// reverse into ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 5, 60, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -7, 75, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -15, 95, 0.6, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -80, 110, 0.8, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 120, 0.55, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -150, 130, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -170, 130, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 0.5));

	// route to shoot ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 140, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 115, 0.5, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -90, 95, 0.6, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -70, 70, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -50, 50, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 1));

	// route to balls 4 and 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -90, 50, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -110, 70, 0.65, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -200, 90, 0.55, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -240, 90, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -272, 90, 0.15, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 1));



	// shoot 4 and 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -100, 90, 0.6, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -75, 80, 0.4, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -60, 58, 0.35, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -35, 32, 0.2, false, true, INTAKE_STOP, CONSTANT("HOOD_UP"), false, 2));

	

	// 10 and 20 clockwise
	// -10 and 25 clockwise
	//

	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 0, -60, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_2"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 40, 0, 0.4, true, false, INTAKE_F_IN, CONSTANT("HOOD_AUTO_2"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 0, 100, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_2"), true, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0.4, false, false, INTAKE_SHOOT, CONSTANT("HOOD_AUTO_2"), true, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 0, 20, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_3"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -50, 0, 0.6, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_3"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -10, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_AUTO_3"), false, 3));
	// // Reposition somehow?
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 0, 0.4, false, true, INTAKE_R_IN, CONSTANT("HOOD_AUTO_3"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 60, 0, 0.6, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_3"), false, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_TURN, 0, -20, 0.4, false, false, INTAKE_STOP, CONSTANT("HOOD_AUTO_3"), true, 3));
	// m_Modes["5 Ball"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0.4, false, false, INTAKE_SHOOT, CONSTANT("HOOD_AUTO_3"), true, 3));

	m_Modes["2 Ball"];
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -40, 0, 0.2, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 5));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, true, INTAKE_R_IN, CONSTANT("HOOD_UP"), false, 1));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 0, 0.2, false, false, INTAKE_R_IN, CONSTANT("HOOD_UP"), true, 3));
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, CONSTANT("HOOD_UP"), true, 4));

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