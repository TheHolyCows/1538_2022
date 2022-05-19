//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
//==================================================

#ifndef __WC_DRIVE_H__
#define __WC_DRIVE_H__

#include "../CowConstants.h"
#include "../CowLib/Utility.h"
#include "../CowLib/CowMotorController.h"


class WCDrive : public GenericDrive
{
private:
    static WCDrive *m_Instance = NULL;
    
    double m_LeftDriveValue;
    double m_RightDriveValue;

    struct DriveSingle
    {
        CowLib::CowMotorController *m_DriveA;
        CowLib::CowMotorController *m_DriveB;
    };

    struct DriveLR
    {
        DriveSingle m_DriveLeft;
        DriveSingle m_DriveRight;
    };

    DriveLR m_Drive;

public:
    WCDrive();

    void InitLeftDrive(int motorA, bool invertA, int motorB, bool invertB);
    void InitRightDrive(int motorA, bool invertA, int motorB, bool invertB);

    void handle(void);
}





#endif /* __WC_DRIVE_H__ */