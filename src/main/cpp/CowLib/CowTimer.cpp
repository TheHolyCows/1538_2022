/*
 * CowTimer.cpp
 *
 *  Created on: Jan 9, 2022
 *      Author: jon-bassi
 */

#include "CowTimer.h"

/**
 * reimplementation of WPILib Wait command - usese native datatypes
 **/
void CowLib::CowWait(double seconds)
{
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}