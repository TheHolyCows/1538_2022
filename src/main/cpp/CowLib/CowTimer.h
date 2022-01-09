/*
 * CowTimer.h
 *
 *  Created on: Jan 9, 2022
 *      Author: jon-bassi
 */

#ifndef __COW_TIMER_H__
#define __COW_TIMER_H__

#include <chrono>
#include <thread>

namespace CowLib
{
    // replacement for old frc::Wait() to get around using units
    void CowWait(double);
}


#endif