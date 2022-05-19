#include "WCDrive.h"



/* private */

WCDrive::WCDrive()
{
    // TODO
}

/* public */

void WCDrive::InitLeftDrive(int motorA, bool invertA, int motorB, bool invertB)
{
    // Set up drive motors
    m_Drive.m_DriveLeft.m_DriveA = new CowLib::CowMotorController(motorA);
    m_Drive.m_DriveLeft.m_DriveB = new CowLib::CowMotorController(motorB);

    m_Drive.m_DriveLeft.m_DriveA->SetInverted(invertA);
    m_Drive.m_DriveLeft.m_DriveB->SetInverted(invertB);

    m_Drive.m_DriveLeft.m_DriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_Drive.m_DriveLeft.m_DriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_Drive.m_DriveLeft.m_DriveA->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_Drive.m_DriveLeft.m_DriveB->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_LeftDriveValue = 0;
}

void WCDrive::InitRightDrive(int motorA, bool invertA, int motorB, bool invertB)
{
    // Set up drive motors
    m_Drive.m_DriveRight.m_DriveA = new CowLib::CowMotorController(motorA);
    m_Drive.m_DriveRight.m_DriveB = new CowLib::CowMotorController(motorB);

    m_Drive.m_DriveRight.m_DriveA->SetInverted(invertA);
    m_Drive.m_DriveRight.m_DriveB->SetInverted(invertB);

    m_Drive.m_DriveRight.m_DriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_Drive.m_DriveRight.m_DriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));

    m_Drive.m_DriveRight.m_DriveA->SetNeutralMode(CowLib::CowMotorController::COAST);
    m_Drive.m_DriveRight.m_DriveB->SetNeutralMode(CowLib::CowMotorController::COAST);

    m_RightDriveValue = 0;
}

// void WCDrive::SetDriveConversionParams(float drivingGearTC, float drivenGearTC, float wheelDiameter, float falconUnitsPerRev)
// {
//     m_drivingGearTC = drivingGearTC;
//     m_drivenGearTC = drivenGearTC;

//     m_WheelDia = wheelDiameter;

//     m_falconUnitsPer = falconUnitsPerRev;

//     m_EncoderToDistRatio = m_WheelDia (m_falconUnitsPer * (m_drivenGearTC / m_drivingGearTC));
// }

// void WCDrive::DriveLeftRight(float leftDriveValue, float rightDriveValue)
// {
//     m_LeftDriveValue = leftDriveValue;
//     m_RightDriveValue = rightDriveValue;
// }

// // double CowRobot::GetDriveVelocity()
// // {
// //     // use moving average filter from frc
// //     int buffSize = 20;

// //     double sum = 0.0;
// //     for (int i = 0; i < buffSize; i++)
// //     {
// //         sum += m_DistDeltaBuff[i];
// //     }

// //     return sum / buffSize;
// // }

// void WCDrive::Reset()
// {
//     m_LeftDriveValue = 0;
//     m_RightDriveValue = 0;

//     ResetEncoders();
// }

// void WCDrive::ResetEncoders()
// {
//     m_LeftDrive[0]->SetSensorPosition(0);
//     m_LeftDrive[1]->SetSensorPosition(0);
//     m_RightDrive[0]->SetSensorPosition(0);
//     m_RightDrive[1]->SetSensorPosition(0);
// }

void WCDrive::handle()
{
    float leftDrive = CowLib::LimitMix(m_LeftDriveValue);
    float rightDrive = CowLib::LimitMix(m_RightDriveValue);

    m_Drive.m_DriveLeft.m_DriveA->Set(m_LeftDriveValue);
    m_Drive.m_DriveLeft.m_DriveB->Set(m_RightDriveValue);

    m_Drive.m_DriveRight.m_DriveA->Set(m_RightDriveValue);
    m_Drive.m_DriveRight.m_DriveA->Set(m_RightDriveValue);
}