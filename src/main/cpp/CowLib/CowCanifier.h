//==================================================
// Copyright (C) 2019 Team 1538 / The Holy Cows
//==================================================

#ifndef __COWLIB_COWCANIFIER_H__
#define __COWLIB_COWCANIFIER_H__

#include <stdint.h>
#include <wpi/deprecated.h>
#include "ctre/Phoenix.h"

namespace CowLib
{
    class CowCanifier
    {
    public:
        CowCanifier(int deviceNum);
        virtual ~CowCanifier();

        void SetLEDColor(int R, int G, int B);
        void Handle();
    private:
        CANifier* m_Canifier;
        int m_DeviceNum;
        int m_R;
        int m_G;
        int m_B;
    };
}

#endif /* __COWLIB_COWMOTORCONTROLLER_H__ */
