#include "WCDrive.h"

void WCDrive::InitLeftDrive(int motorA, bool invertA, int motorB, bool invertB)
{
    // Set up drive motors
    m_LeftDrive[0] = new CowLib::CowMotorController(motorA);
    m_LeftDrive[1] = new CowLib::CowMotorController(motorB);

    m_LeftDrive[0]->SetInverted(invertA);
    m_LeftDrive[1]->SetInverted(invertB);

    m_LeftDrive[0]->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_LeftDrive[1]->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_LeftDrive[0]->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_LeftDrive[1]->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_LeftDriveValue = 0;
}

void WCDrive::InitRightDrive(int motorA, bool invertA, int motorB, bool invertB)
{
    // Set up drive motors
    m_RightDrive[0] = new CowLib::CowMotorController(motorA);
    m_RightDrive[1] = new CowLib::CowMotorController(motorB);

    m_RightDrive[0]->SetInverted(invertA);
    m_RightDrive[1]->SetInverted(invertB);

    m_RightDrive[0]->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_RightDrive[1]->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_RightDrive[0]->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_RightDrive[1]->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_RightDriveValue = 0;
}

void WCDrive::SetDriveConversionParams(float drivingGearTC, float drivenGearTC, float wheelDiameter, float falconUnitsPerRev)
{
    m_drivingGearTC = drivingGearTC;
    m_drivenGearTC = drivenGearTC;

    m_WheelDia = wheelDiameter;

    m_falconUnitsPer = falconUnitsPerRev;

    m_EncoderToDistRatio = m_WheelDia (m_falconUnitsPer * (m_drivenGearTC / m_drivingGearTC));
}

void WCDrive::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
    m_LeftDriveValue = leftDriveValue;
    m_RightDriveValue = rightDriveValue;
}

// double CowRobot::GetDriveVelocity()
// {
//     // use moving average filter from frc
//     int buffSize = 20;

//     double sum = 0.0;
//     for (int i = 0; i < buffSize; i++)
//     {
//         sum += m_DistDeltaBuff[i];
//     }

//     return sum / buffSize;
// }

void WCDrive::Reset()
{
    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;

    ResetEncoders();
}

void WCDrive::ResetEncoders()
{
    m_LeftDrive[0]->SetSensorPosition(0);
    m_LeftDrive[1]->SetSensorPosition(0);
    m_RightDrive[0]->SetSensorPosition(0);
    m_RightDrive[1]->SetSensorPosition(0);
}

void WCDrive::handle()
{
    float leftDrive = CowLib::LimitMix(m_LeftDriveValue);
    float rightDrive = CowLib::LimitMix(m_RightDriveValue);

    m_LeftDrive[0]->Set(m_RightDriveValue);
    m_LeftDrive[1]->Set(m_RightDriveValue);

    m_RightDrive[0]->Set(m_RightDriveValue);
    m_RightDrive[1]->Set(m_RightDriveValue);
}