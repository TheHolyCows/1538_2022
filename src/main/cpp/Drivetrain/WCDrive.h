//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
//==================================================

#ifndef __WC_DRIVE_H__
#define __WC_DRIVE_H__

#include "GenericDrive.h"
#include "../CowConstants.h"
#include "../CowLib/Utility.h"
#include "../CowLib/CowMotorController.h"


class WCDrive : public GenericDrive
{
private:
    WCDrive();
    static WCDrive* m_Instance;
    
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

    // encoder math members
    float m_drivingGearTC = 0;
    float m_drivenGearTC = 0;
    float m_WheelDia = 0;
    float m_falconUnitsPer = 0;
    float m_EncoderToDistRatio = 0;

public:
    static WCDrive* GetInstance();

    /* inherited from GenericDrive */
    void InitMotorIds(int, int, int, int);
    void InitMotorInversion(bool, bool, bool, bool);
    void InitMotorPhase(bool, bool, bool, bool);
    void InitMotorNeutralMode(CowLib::CowMotorController::CowNeutralMode);

    void ResetDriveEncoders(void);

    void handle(void);

    /* custom */
    void SetDriveConversionParams(float drivingGearTC, float drivenGearTC, float wheelDiameter, float falconUnitsPerRev=2048);
};

#endif /* __WC_DRIVE_H__ */