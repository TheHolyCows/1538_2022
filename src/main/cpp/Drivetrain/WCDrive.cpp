#include "WCDrive.h"

/* singleton implementation */
WCDrive* WCDrive::GetInstance()
{
    if (m_Instance == NULL)
    {
        m_Instance = new WCDrive();
    }

    return m_Instance;
}

/* private */

WCDrive::WCDrive()
{
    m_LeftDriveValue = 0;
    m_RightDriveValue = 0;
}

/* public */

void WCDrive::InitMotorIds(int motorLeftA, int motorLeftB, int motorRightA, int motorRightB)
{
    m_Drive.m_DriveLeft.m_DriveA = new CowLib::CowMotorController(motorLeftA);
    m_Drive.m_DriveLeft.m_DriveB = new CowLib::CowMotorController(motorLeftB);
    m_Drive.m_DriveRight.m_DriveA = new CowLib::CowMotorController(motorRightA);
    m_Drive.m_DriveRight.m_DriveB = new CowLib::CowMotorController(motorRightB);

    m_Drive.m_DriveLeft.m_DriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_Drive.m_DriveLeft.m_DriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_Drive.m_DriveRight.m_DriveA->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
    m_Drive.m_DriveRight.m_DriveB->SetStatorLimit(CONSTANT("STATOR_LIMIT"), CONSTANT("STATOR_THRESHOLD"), CONSTANT("STATOR_DURATION"));
}

void WCDrive::InitMotorInversion(bool invertLeftA, bool invertLeftB, bool invertRightA, bool invertRightB)
{
    m_Drive.m_DriveLeft.m_DriveA->SetInverted(invertLeftA);
    m_Drive.m_DriveLeft.m_DriveB->SetInverted(invertLeftB);
    m_Drive.m_DriveRight.m_DriveA->SetInverted(invertRightA);
    m_Drive.m_DriveRight.m_DriveB->SetInverted(invertRightB);
}

void WCDrive::InitMotorPhase(bool phaseLeftA, bool phaseLeftB, bool phaseRightA, bool phaseRightB)
{
    // TODO
}

void WCDrive::InitMotorNeutralMode(CowLib::CowMotorController::CowNeutralMode mode)
{
    m_Drive.m_DriveLeft.m_DriveA->SetNeutralMode(mode);
    m_Drive.m_DriveLeft.m_DriveB->SetNeutralMode(mode);
    m_Drive.m_DriveRight.m_DriveA->SetNeutralMode(mode);
    m_Drive.m_DriveRight.m_DriveB->SetNeutralMode(mode);

}

void WCDrive::SetDriveConversionParams(float drivingGearTC, float drivenGearTC, float wheelDiameter, float falconUnitsPerRev)
{
    m_drivingGearTC = drivingGearTC;
    m_drivenGearTC = drivenGearTC;

    m_WheelDia = wheelDiameter;

    m_falconUnitsPer = falconUnitsPerRev;

    m_EncoderToDistRatio = m_WheelDia * (m_falconUnitsPer * (m_drivenGearTC / m_drivingGearTC));
}

// void WCDrive::DriveLeftRight(float leftDriveValue, float rightDriveValue)
// {
//     m_LeftDriveValue = leftDriveValue;
//     m_RightDriveValue = rightDriveValue;
// }

// void WCDrive::Reset()
// {
//     m_LeftDriveValue = 0;
//     m_RightDriveValue = 0;

//     ResetEncoders();
// }

void WCDrive::ResetDriveEncoders()
{
    m_Drive.m_DriveLeft.m_DriveA->SetSensorPosition(0);
    m_Drive.m_DriveLeft.m_DriveB->SetSensorPosition(0);
    m_Drive.m_DriveRight.m_DriveA->SetSensorPosition(0);
    m_Drive.m_DriveRight.m_DriveB->SetSensorPosition(0);
}

void WCDrive::handle()
{
    float leftDrive = CowLib::LimitMix(m_LeftDriveValue);
    float rightDrive = CowLib::LimitMix(m_RightDriveValue);

    m_Drive.m_DriveLeft.m_DriveA->Set(leftDrive);
    m_Drive.m_DriveLeft.m_DriveB->Set(leftDrive);

    m_Drive.m_DriveRight.m_DriveA->Set(rightDrive);
    m_Drive.m_DriveRight.m_DriveA->Set(rightDrive);
}