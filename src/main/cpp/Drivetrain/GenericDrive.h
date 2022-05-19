//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
//==================================================

#ifndef __GENERIC_DRIVE_H__
#define __GENERIC_DRIVE_H__


class GenericDrive
{
public:
    virtual double GetDriveDistance(void);

    virtual bool TurnToHeading(double heading);
    virtual bool DriveWithHeading(double heading, double speed=1.0);
    virtual bool DriveDistanceWithHeading(double distance,double heading,double speed=1.0);
    virtual bool DriveTeleop(...);

    virtual void ResetDriveEncoders(void);

    virtual void handle(void);
};

#endif /* __GENERIC_DRIVE_H__ */