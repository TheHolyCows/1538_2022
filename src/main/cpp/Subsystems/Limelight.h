//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Limelight.h
// author: jon-bassi
// created on: 2022-2-28
//==================================================

#ifndef __LIMELIGHT_H__
#define __LIMELIGHT_H__

#include <algorithm>
#include "../CowConstants.h"
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

class Limelight
{
public:
    Limelight(std::string hostname);

    enum LimelightMode
    {
        LIMELIGHT_TRACKING = 0,
        LIMELIGHT_VISUAL
    };

    void SetMode(LimelightMode);
    bool GetValidTargets(void);
    float GetTargetXPos(void);
    float GetTargetYPos(void);

    bool TargetCentered(void);

    int CalcHoodPos(void);
    float CalcNewPid(void);

    void ResetPID(void);

private:
    std::shared_ptr<nt::NetworkTable> m_Limelight;
    float m_Limelight_PID_P;
    float m_Limelight_PID_D;
};

#endif /* __LIMELIGHT_H__ */
