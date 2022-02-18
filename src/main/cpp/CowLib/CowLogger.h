//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// CowLogger.h
// author: jon-bassi
// created on: 2022-1-16
//==================================================

#ifndef __COW_LOGGER_H__
#define __COW_LOGGER_H__

#include <mutex>
#include <thread>
#include <queue>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace CowLib {

class CowLogger {
public:
    CowLogger();
    virtual ~CowLogger();
    static void Log(std::string key, double value);
    static CowLogger* GetInstance();
    static void VarRemoteLog(uint32_t,void**);
    static void StrRemoteLog(std::string);
    static void PIDRemoteLog(double,double,double,double,double);

    enum CowLogProtocol
    {
        VAR_LOG=0,
        STR_LOG,
        PID_LOG,
    };

private:
    std::thread *m_Thread;
    static std::mutex m_Mutex;
    static std::queue<std::pair<std::string, double>> m_BufferQueue;
    static std::ofstream m_OutputFile;
    static CowLogger* m_Instance;
    struct sockaddr_in m_LogServer;
    int m_LogSocket;

    void Handle();

    struct CowLogHdr
    {
        CowLogProtocol  proto;
        uint32_t        dataLen;
    };

    struct CowPIDLog
    {
        uint32_t setPoint;
        uint32_t procVar;
        uint32_t pVar;
        uint32_t iVar;
        uint32_t dVar;
    };
};

} /* namespace CowLib */

#endif /* __COW_LOGGER_H__ */
