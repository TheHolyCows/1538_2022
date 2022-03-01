//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// Limelight.cpp
// author: jon-bassi
// created on: 2022-2-28
//==================================================

#include "Limelight.h"

Limelight::Limelight(std::string hostname)
{
    m_Limelight = nt::NetworkTableInstance::GetDefault().GetTable(hostname);

    ResetPID();

    SetMode(LIMELIGHT_TRACKING);
}

void Limelight::SetMode(LimelightMode mode)
{
    switch (mode)
    {
    case LIMELIGHT_TRACKING:
        m_Limelight->PutNumber("pipeline", 0);
        m_Limelight->PutNumber("ledMode", 3);
        break;
    case LIMELIGHT_VISUAL:
    default:
        m_Limelight->PutNumber("pipeline", 3);
        m_Limelight->PutNumber("ledMode", 1);
        break;
    }
}

bool Limelight::GetValidTargets()
{
    return m_Limelight->GetNumber("tv",0);
}

float Limelight::GetTargetXPos()
{
    return m_Limelight->GetNumber("tx",0.0);
}

float Limelight::GetTargetYPos()
{
    return m_Limelight->GetNumber("ty",0.0);
}

int Limelight::CalcHoodPos()
{
    float tarArea = m_Limelight->GetNumber("ta", 0.0);
    return std::min(CONSTANT("HOOD_UP") - (CONSTANT("HOOD_UP") * tarArea), CONSTANT("HOOD_DOWN"));
}

float Limelight::CalcNewPid()
{
    float tmp_limelight_P = m_Limelight->GetNumber("tx", 0.0);
    m_Limelight_PID_D = m_Limelight_PID_P - m_Limelight_PID_D;
    m_Limelight_PID_P = tmp_limelight_P;

    float pid = (m_Limelight_PID_P * CONSTANT("LIMELIGHT_X_KP"));
    pid += (m_Limelight_PID_D * CONSTANT("LIMELIGHT_X_KD"));

    return pid;
}

void Limelight::ResetPID()
{
    m_Limelight_PID_P = 0;
    m_Limelight_PID_D = 0;
}