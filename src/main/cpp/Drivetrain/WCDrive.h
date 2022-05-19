//==================================================
// Copyright (C) 2018 Team 1538 / The Holy Cows
//==================================================

#ifndef __COW_DRIVE_H__
#define __COW_DRIVE_H__

class __COW_DRIVE_H__

#include "../CowLib/Utility.h"


{
public:

    void InitLeftDrive(int,bool,int,bool);
    void InitRightDrive(int,bool,int,bool);
    void SetGearRatio(float,float,float falconUnitsPerRev = 2048,)
    
    bool DriveDistance(double distance);
    bool DriveDistanceWithHeading(double heading, double distance, double speed);
    bool DriveWithHeading(double heading, double speed);
    bool DriveWithHeading(double heading, double speed, double maxSpeed);
    void DriveSpeedTurn(float speed, float turn, bool quickTurn);
    void DriveLeftRight(float leftDriveValue, float rightDriveValue);
    bool TurnToHeading(double heading);

    void QuickTurn(float turn);

    void ResetEncoders(void);

private:
    CowLib::CowMotorController m_leftDrive[2];
    CowLib::CowMotorController m_rightDrive[2];

    float m_LeftDriveValue;
    float m_RightDriveValue;
}









#endif /* __COW_DRIVE_H__ */