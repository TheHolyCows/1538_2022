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
    m_LogServer.sin_port = htons(6969);

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

/**
 * CowLogger::VarRemoteLog(uint32_t nArgs, void **args)
 * WIP
 **/ 
void CowLogger::VarRemoteLog(uint32_t nArgs, void **args)
{
    // WIP
    return;
}

/**
 * CowLogger::StrLog(std::string logStr)
 * logs string to remote logging server for debugging
 * @arg logStr: string to log
 **/
void CowLogger::StrRemoteLog(std::string logStr)
{
    CowLogger::CowLogHdr logHdr;
    logHdr.proto = CowLib::CowLogger::STR_LOG;
    logHdr.dataLen = logStr.length() + 1;

    char data[sizeof(CowLogHdr) + logHdr.dataLen + 1];

    // copy header
    memcpy(data, &logHdr, sizeof(logHdr));

    // copy string and null terminate
    strncpy(data + sizeof(CowLogHdr), logStr.c_str(), logStr.length());
    data[sizeof(CowLogHdr) + logHdr.dataLen] = '\0';

    int ret = sendto(GetInstance()->m_LogSocket, &data, sizeof(data),
        0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer), sizeof(m_LogServer));
    if (ret == -1)
    {
        std::cout << "StrLog() errno: " << strerror(errno) << std::endl;
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
    CowLogger::CowLogHdr logHdr;
    logHdr.proto = CowLib::CowLogger::PID_LOG;
    logHdr.dataLen = sizeof(CowPIDLog);

    CowLogger::CowPIDLog pidPacket;
    pidPacket.setPoint = setPoint;
    pidPacket.procVar = procVar;
    pidPacket.pVar = P;
    pidPacket.iVar = I;
    pidPacket.dVar = D;

    char data[sizeof(CowLogHdr) + sizeof(CowPIDLog)];
    memcpy(data,&logHdr,sizeof(CowLogHdr));
    memcpy(data+sizeof(CowLogHdr),&pidPacket,sizeof(CowPIDLog));
    
    int ret = sendto(GetInstance()->m_LogSocket, &data, sizeof(data),
        0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer), sizeof(m_LogServer));
    if (ret == -1)
    {
        std::cout << "PIDRemoteLog() errno: " << strerror(errno) << std::endl;
    }
}

} /* namespace CowLib */
