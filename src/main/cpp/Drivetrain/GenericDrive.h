//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
//==================================================

#ifndef __GENERIC_DRIVE_H__
#define __GENERIC_DRIVE_H__

#include "../CowLib/CowMotorController.h"

class GenericDrive
{
public:
    // initializations
    virtual void InitMotorIds(int, int, int, int) = 0;
    virtual void InitMotorInversion(bool, bool, bool, bool) = 0;
    virtual void InitMotorPhase(bool, bool, bool, bool) = 0;
    virtual void InitMotorNeutralMode(CowLib::CowMotorController::CowNeutralMode) = 0;

    // movement
    virtual double GetDriveDistance(void) = 0;

    virtual bool TurnToHeading(double heading) = 0;
    virtual bool DriveWithHeading(double heading, double speed=1.0) = 0;
    virtual bool DriveDistanceWithHeading(double distance,double heading,double speed=1.0) = 0;
    virtual bool DriveTeleop(...) = 0;

    virtual void ResetDriveEncoders(void) = 0;

    // standard
    virtual void handle(void) = 0;
};

#endif /* __GENERIC_DRIVE_H__ */