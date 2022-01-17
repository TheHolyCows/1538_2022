//==================================================
// Copyright (C) 2022 Team 1538 / The Holy Cows
// CowLogger.h
// author: kchau
// created on: 2016-1-21
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
private:
    std::thread *m_Thread;
    static std::mutex m_Mutex;
    static std::queue<std::pair<std::string, double>> m_BufferQueue;
    static std::ofstream m_OutputFile;
    static CowLogger* m_Instance;
    struct sockaddr_in m_LogServer;
    int m_LogSocket;
public:
    CowLogger();
    virtual ~CowLogger();
    static void Log(std::string key, double value);
    static CowLogger* GetInstance();
    static void RemoteLog(int32_t);
private:
    static void Handle();
};

} /* namespace CowLib */

#endif /* __COW_LOGGER_H__ */
