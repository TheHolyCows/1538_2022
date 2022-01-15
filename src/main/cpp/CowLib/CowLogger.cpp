/*
 * CowWebDebugger.cpp
 *
 *  Created on: Jan 21, 2016
 *      Author: kchau
 */
#include "CowLogger.h"
#include <iostream>
#include <time.h>
#include "CowTimer.h"

namespace CowLib
{

CowLogger* CowLogger::m_Instance = 0;

std::mutex CowLogger::m_Mutex;
std::ofstream CowLogger::m_OutputFile;
std::queue<std::pair<std::string, double>> CowLogger::m_BufferQueue;

CowLogger::CowLogger()
{
    m_Thread = new std::thread(CowLogger::Handle);
    time_t rawTime;
    struct tm *timeInfo;
    time(&rawTime);
    timeInfo = localtime(&rawTime);
    char buffer[80];
    strftime(buffer, 80, "/home/lvuser/logs/DebugLog_%h_%d_%j_%H%M.txt", timeInfo);
    m_OutputFile.open(buffer);
    std::cout << "Opened file for debugging" << std::endl;
}

CowLogger::~CowLogger()
{
    m_OutputFile.close();
    m_Thread->detach();
    delete m_Thread;

}

CowLogger* CowLogger::GetInstance()
{
    if(m_Instance == 0)
    {
        m_Instance = new CowLogger();
    }

    return m_Instance;
}

void CowLogger::Handle()
{
    while(true)
    {
        //std::cout << "Test from CowWebDebugger" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if(!m_BufferQueue.empty())
        {
            m_Mutex.lock();
            while(!m_BufferQueue.empty())
            {
                std::pair<std::string, double> toPrint = m_BufferQueue.front();

                std::string key = toPrint.first;
                double value = toPrint.second;
                m_OutputFile << (CowLib::CowTimer::GetFPGATimestamp()) << " " << key << ": " << value << std::endl;
                m_BufferQueue.pop();
            }
            m_Mutex.unlock();
        }
    }
}

void CowLogger::Log(std::string key, double value)
{
    m_Mutex.lock();
    m_BufferQueue.push(std::pair<std::string, double>(key, value));
    m_Mutex.unlock();
}

} /* namespace CowLib */
