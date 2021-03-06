/*
 * Arm.cpp
 *
 *  Created on: Feb 18, 2018
 *      Author: kchau
 */

#include "Arm.h"
#include "string.h"
#include <iostream>
#include <frc/Timer.h>

Arm::Arm(int motorControllerA, int motorControllerB, double maxSpeed, double upLimit, double downLimit, std::string name, bool changeDirectionA, bool changeDirectionB, double degreesPerTick, double peakOutput)
{
	m_MotorA = new CowLib::CowMotorController(motorControllerA);
	m_MotorA->SetControlMode(CowLib::CowMotorController::MOTIONMAGIC);
	m_MotorB = new CowLib::CowMotorController(motorControllerB);
	m_MotorB->SetControlMode(CowLib::CowMotorController::FOLLOWER);
    m_MotorAID = motorControllerA;
    m_Position = 0;
	m_DegreesPerTick = degreesPerTick;
    //m_MaxSpeed = maxSpeed;
	
	
	//SetCurrentLimit();

	m_UpLimit = upLimit;
	m_DownLimit = downLimit;

	m_Name = name;
    m_PeakOutput = peakOutput;

	ResetConstants(upLimit, downLimit, peakOutput);
	m_MotorA->SetInverted(changeDirectionA);
	m_MotorB->GetInternalMotor()->SetInverted(changeDirectionB);
    SetCoastMode();
}

bool Arm::AtTarget()
{
	std::string toleranceName = m_Name + "_TOLERANCE";
	return (fabs(m_Position - m_MotorA->GetPosition() * m_DegreesPerTick) < CONSTANT(toleranceName.c_str()));
}

void Arm::SetPosition(float position)
{
	//if(position < m_DownLimit)
	//{
	//	position = m_DownLimit;
	//}
	//else if(position > m_UpLimit)
	//{
//		position = m_UpLimit;
//	}
	//position = position / m_DegreesPerTick;
    //m_CalculateGain = true;
	m_Position = position;
}

float Arm::GetSetpoint()
{
	return m_Position;
}

float Arm::GetPosition()
{
	return m_MotorA->GetPosition();
}

void Arm::ResetConstants(double upLimit, double downLimit, double peakOutput)
{
	//m_MotorA->SetPIDGains(CONSTANT("ARM_P")*CONSTANT("DEBUG_PID"), CONSTANT("ARM_I")*CONSTANT("DEBUG_PID"), CONSTANT("ARM_D")*CONSTANT("DEBUG_PID"), 0, 1);
	//m_MotorA->SetMotionMagic(CONSTANT("ARM_ACCEL"), CONSTANT("ARM_VELOCITY"));
	std::cout << "In the arm reset constants" << std::endl;
    m_UpLimit = upLimit;
    m_DownLimit = downLimit;
}

void Arm::DisabledCalibration()
{
        float currentPosition = m_MotorA->GetPosition();

        if(currentPosition < 0)
        {
                m_MotorA->SetSensorPosition(0);
        }
}

void Arm::handle()
{
    if(m_MotorA && m_MotorB)
    {
        m_MotorA->Set(m_Position);
        m_MotorB->Set(m_MotorAID);
    }
    //SmartDashboard::PutNumber("Arm", (m_Motor->GetPosition()-m_PlanetaryHardstop));
	//std::cout << m_Name << " position: " << m_Position << std::endl;
}
void Arm::SetCurrentLimit(float peakAmps, float continuousAmps, int peakDuration, int ms)
{
	//m_Motor->GetInternalMotor()->ConfigPeakCurrentLimit(peakAmps, ms);
	//m_Motor->GetInternalMotor()->ConfigPeakCurrentDuration(peakDuration, ms);
	//m_Motor->GetInternalMotor()->ConfigContinuousCurrentLimit(continuousAmps, ms);
	//m_Motor->GetInternalMotor()->EnableCurrentLimit(true);
}

Arm::~Arm()
{
	delete m_MotorA;
	delete m_MotorB;
}

