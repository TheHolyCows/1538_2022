#include "CowCanifier.h"

namespace CowLib
{
    CowCanifier::CowCanifier(int deviceNum)
        :
        m_DeviceNum(deviceNum),
        m_R(0),
        m_G(0),
        m_B(0)
    {
        m_Canifier = new CANifier(m_DeviceNum);
    }

    void CowCanifier::SetLEDColor(int R, int G, int B)
    {
        m_R = R;
        m_G = G;
        m_B = B;
    }
    void CowCanifier::Handle()
    {
        double dutyCycle_R = double(m_R) / 255.0;
        double dutyCycle_G = double(m_G) / 255.0;
        double dutyCycle_B = double(m_B) / 255.0;

        m_Canifier->SetLEDOutput(dutyCycle_R, ctre::phoenix::CANifier::LEDChannelB);
        m_Canifier->SetLEDOutput(dutyCycle_G, ctre::phoenix::CANifier::LEDChannelA);
        m_Canifier->SetLEDOutput(dutyCycle_B, ctre::phoenix::CANifier::LEDChannelC);
    }
    CowCanifier::~CowCanifier()
    {
        delete m_Canifier;
    }
}
