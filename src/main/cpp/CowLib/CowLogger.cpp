//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// CowLogger.h
// author: kchau
// created on: 2016-1-21
//==================================================

#include "CowLogger.h"
#include <iostream>
#include <time.h>
#include "CowTimer.h"
#include <errno.h>

namespace CowLib
{

CowLogger* CowLogger::m_Instance = 0;

std::mutex CowLogger::m_Mutex;
std::ofstream CowLogger::m_OutputFile;
std::queue<std::pair<std::string, double>> CowLogger::m_BufferQueue;

CowLogger::CowLogger()
{
    // m_Thread = new std::thread(CowLogger::Handle);
    // time_t rawTime;
    // struct tm *timeInfo;
    // time(&rawTime);
    // timeInfo = localtime(&rawTime);
    // char buffer[80];
    // strftime(buffer, 80, "/home/lvuser/logs/DebugLog_%h_%d_%j_%H%M.txt", timeInfo);
    // m_OutputFile.open(buffer);
    // std::cout << "Opened file for debugging" << std::endl;


    // create sock stuff - using TCP is that too much overhead?
    m_LogSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

    if (m_LogSocket < 0)
    {
        std::cout << "error creating socket" << std::endl;
    }

    m_LogServer.sin_family = AF_INET;
    m_LogServer.sin_addr.s_addr = inet_addr("10.15.38.21");
    m_LogServer.sin_port = htons(2341);

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

void CowLogger::RemoteLog(int32_t logVal)
{
    int ret = sendto(GetInstance()->m_LogSocket,&logVal,sizeof(int32_t),
        0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer),sizeof(m_LogServer));
    if (ret == -1)
    {
        std::cout << "errno: " << strerror(errno) << std::endl;
    }
}

/**
 * CowLogger::PIDRemoteLog(double *pidArray)
 * logs PID values to remote logging server for graphing and testing
 * @arg pidArray:
 *  size 5
 *  [setPoint, processVar, P, I, D]
 **/
void CowLogger::PIDRemoteLog(double setPoint, double procVar, double P, double I, double D)
{
    double pidArray[5] = {setPoint, procVar, P, I, D};
    // int ret = 0;
    // std::cout << "PIDRemoteLog():" << std::endl;
    // std::cout << setPoint << std::endl;
    // std::cout << procVar << std::endl;
    // std::cout << P << std::endl;
    // std::cout << I << std::endl;
    // std::cout << D << std::endl;
    int ret = sendto(GetInstance()->m_LogSocket, &pidArray, sizeof(pidArray),
        0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer), sizeof(m_LogServer));
    if (ret == -1)
    {
        std::cout << "errno: " << strerror(errno) << std::endl;
    }
}

} /* namespace CowLib */
