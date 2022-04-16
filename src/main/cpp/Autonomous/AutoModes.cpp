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
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_STOP, true, 0.3));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_SHOOT, true, 0.5));

	// prepare to reverse for ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 25, 0.4, false, false, INTAKE_STOP, false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 25, 50, 0.2, false, false, INTAKE_STOP, false, 1));

	// reverse to ball 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 85, 0.35, false, true, INTAKE_R_IN , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -120, 97, 0.4, false, true, INTAKE_R_IN , false, 6));

	// shoot 3
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -140, 97, 0.2, false, false, INTAKE_R_IN , false, 0.9));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -140, 60, 0.2, false, false, INTAKE_R_IN, true, 0.8));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -140, 60, 0, false, false, INTAKE_STOP, true, 0.3));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -140, 60, 0, false, false, INTAKE_SHOOT, true, 0.5));

	// route to 4 + 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -235, 90, 0.4, false, true, INTAKE_STOP , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -325, 45, 0.3, false, true, INTAKE_R_IN , false, 2));

	// // shoot 4 + 5
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -220, 70, 0.8, false, true, INTAKE_R_IN , false, 6));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -180, 70, 0.3, false, false, INTAKE_R_IN , true, 0.8));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -180, 0, 0, false, false, INTAKE_STOP, true, 0.4));
	m_Modes["5 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -190, 0, 0, false, false, INTAKE_SHOOT, true, 1.5));


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


	/** 3 Ball **/
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
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 0, 70, 0.5, false, true, INTAKE_R_IN, false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -30, 90, 0.5, false, true, INTAKE_R_IN, false, 6));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -130, 100, 0.5, false, true, INTAKE_R_IN, false, 6));

	// shoot 3
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -160, 100, 0.45, false, true, INTAKE_R_IN, false, 0.75));
	m_Modes["3 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -180, 40, 0.45, false, false, INTAKE_STOP, false, 1));
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
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_VISION_ALIGN, -47, 0, 0, false, false, INTAKE_SHOOT, true, 2.5));

	// taxi
	m_Modes["2 Ball"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -70, 0, 0, false, false, INTAKE_STOP, false, 6));


	// /** Hide Ball Hub **/
	// m_Modes["Hide Hub LEFT"];
	// // reverse to ball 
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 0, 0.4, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 0, 0.3, false, true, INTAKE_R_IN, false, 6));
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 0, 0.2, false, true, INTAKE_R_IN, false, 1));

	// // move close
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 10, 0, 0.2, false, false, INTAKE_STOP, false, 1));
	// // exhaust
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_VISION_ALIGN, 10, 0, 0, false, false, INTAKE_STOP, false, 1.5));
	// m_Modes["Hide Hub LEFT"].push_back(RobotCommand(CMD_VISION_ALIGN, 10, 0, 0, false, false, INTAKE_F_OUT, false, 2.5));

	/** Hide Ball Hangar **/
	m_Modes["Hide Hangar LEFT"];
	// shoot one
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -10, 0, 0.2, false, false, INTAKE_STOP, true, 1));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_VISION_ALIGN, -10, 0, 0.2, false, false, INTAKE_STOP, true, 1));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_VISION_ALIGN, -10, 0, 0.2, false, false, INTAKE_SHOOT, true, 1));
	// reverse to ball 
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 20, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 20, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 20, 0.2, false, true, INTAKE_R_IN, false, 1.5));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 20, 0.2, false, false, INTAKE_R_IN, false, 0.5));

	// exhaust
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -70, -40, 0.1, false, false, INTAKE_STOP, false, 1.5));
	m_Modes["Hide Hangar LEFT"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -70, -40, 0, false, false, INTAKE_R_OUT, false, 2));

	/** 2Fast2Furiousosing **/
	m_Modes["2Fast2Furious"];
	// shoot one
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -10, 0, 0.2, false, false, INTAKE_STOP, true, 0.4));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_VISION_ALIGN, -10, 0, 0.2, false, false, INTAKE_STOP, true, 0.3));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_VISION_ALIGN, -10, 0, 0.2, false, false, INTAKE_SHOOT, true, 0.5));
	// reverse to ball 
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -18, 20, 0.4, false, true, INTAKE_R_IN, false, 6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -32, 20, 0.3, false, true, INTAKE_R_IN, false, 6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 20, 0.2, false, true, INTAKE_R_IN, false, 0.6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -47, 20, 0.2, false, false, INTAKE_R_IN, false, 0.5));

	// shoot 1
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, -20, 150, 0.1, false, false, INTAKE_STOP, false, 6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 10, 150, 0.3, false, false, INTAKE_STOP, false, 6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 75, 130, 0.3, false, false, INTAKE_TOP_OUT, false, 6));

	// drive to 2
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_DRIVE_DISTANCE, 140, 45, 0.5, true, false, INTAKE_STOP, false, 3));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 225, 25, 0.5, true, false, INTAKE_F_IN, false, 2.5));

	//exfil 2
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 225, -5, 0.1, false, false, INTAKE_STOP, false, .5));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 225, -5, 0.1, false, false, INTAKE_R_OUT, false, 0.7));

	// get other blue
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 225, 50, 0.1, false, false, INTAKE_STOP, false, 0.5));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 150, 50, 0.3, false, true, INTAKE_R_IN, false, 2));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_HOLD_DISTANCE, 150, -34, 0.1, false, true, INTAKE_R_IN, false, 0.6));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_VISION_ALIGN, 150, -34, 0.2, false, false, INTAKE_STOP, true, 0.3));
	m_Modes["2Fast2Furious"].push_back(RobotCommand(CMD_VISION_ALIGN, 150, -34, 0.2, false, false, INTAKE_SHOOT, true, 0.5));


	/** Do Nothing **/
	m_Modes["Nothing"];
	m_Modes["Nothing"].push_back(RobotCommand(CMD_WAIT, 0, 0, 0, false, false, INTAKE_STOP, false, 1));

	/** Move Around **/
	m_Modes["Leave Start Zone"];
	m_Modes["Leave Start Zone"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -55, 0, 0.4, false, false, INTAKE_STOP, false, 4));

	m_Modes["Leave And Ret"];
	m_Modes["Leave And Ret"].push_back(RobotCommand(CMD_HOLD_DISTANCE, -55, 0, 0.4, false, false, INTAKE_STOP, false, 4));
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