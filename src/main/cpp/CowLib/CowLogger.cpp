//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// CowLogger.h
// author: jon-bassi
// created on: 2022-1-16
//==================================================

#include "CowLogger.h"
#include <iostream>
#include <time.h>
#include <errno.h>
#include <string.h>

namespace CowLib
{

    CowLogger *CowLogger::m_Instance = NULL;

    CowLogger::CowLogger()
    {
        // create sock stuff - using TCP is that too much overhead?
        m_LogSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (m_LogSocket < 0)
        {
            std::cout << "error creating socket" << std::endl;
        }

        m_LogServer.sin_family = AF_INET;
        m_LogServer.sin_addr.s_addr = inet_addr("10.15.38.233");
        m_LogServer.sin_port = htons(6969);
    }

    CowLogger::~CowLogger()
    {
        return;
    }

    CowLogger *CowLogger::GetInstance()
    {
        if (m_Instance == NULL)
        {
            m_Instance = new CowLogger();
        }

        return m_Instance;
    }

    void CowLogger::Handle()
    {
        // while(true)
        // {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));

        //     if(!m_BufferQueue.empty())
        //     {
        //         m_Mutex.lock();
        //         while(!m_BufferQueue.empty())
        //         {
        //             std::pair<std::string, double> toPrint = m_BufferQueue.front();

        //             std::string key = toPrint.first;
        //             double value = toPrint.second;
        //             m_OutputFile << (CowLib::CowTimer::GetFPGATimestamp()) << " " << key << ": " << value << std::endl;
        //             m_BufferQueue.pop();
        //         }
        //         m_Mutex.unlock();
        //     }
        // }
    }

    void CowLogger::Log(std::string key, double value)
    {
        // m_Mutex.lock();
        // m_BufferQueue.push(std::pair<std::string, double>(key, value));
        // m_Mutex.unlock();
    }

    /**
 * CowLogger::VarRemoteLog(uint32_t nArgs, void **args)
 * logs a variable amount of 32 bit data to our remote server
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

        void *data = malloc(sizeof(CowLogHdr) + logHdr.dataLen + 1);

        // copy header
        memcpy(data, &logHdr, sizeof(logHdr));

        // copy string and null terminate
        memcpy(((char *)data) + sizeof(CowLogHdr), logStr.c_str(), logStr.length());
        ((char *)data)[sizeof(CowLogHdr) + logStr.length()] = '\0';

        int ret = sendto(GetInstance()->m_LogSocket, &data, sizeof(data),
                         0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer), sizeof(m_LogServer));
        if (ret == -1)
        {
            std::cout << "StrLog() errno: " << strerror(errno) << std::endl;
        }

        free(data);
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
        // CowLogger::CowLogHdr logHdr;
        // logHdr.proto = CowLib::CowLogger::PID_LOG;
        // logHdr.dataLen = sizeof(CowPIDLog);

        CowLogger::CowPIDLog pidPacket;
        pidPacket.setPoint = setPoint;
        pidPacket.procVar = procVar;
        pidPacket.pVar = P;
        pidPacket.iVar = I;
        pidPacket.dVar = D;

        // void* data = malloc(sizeof(CowLogHdr) + sizeof(CowPIDLog));
        // memcpy(data,&logHdr,sizeof(CowLogHdr));
        // memcpy(((char*) data)+sizeof(CowLogHdr),&pidPacket,sizeof(CowPIDLog));

        int ret = sendto(GetInstance()->m_LogSocket, &pidPacket, sizeof(pidPacket),
                         0, reinterpret_cast<sockaddr *>(&GetInstance()->m_LogServer), sizeof(m_LogServer));
        if (ret == -1)
        {
            std::cout << "PIDRemoteLog() errno: " << strerror(errno) << std::endl;
        }

        // free(data);
    }

} /* namespace CowLib */
