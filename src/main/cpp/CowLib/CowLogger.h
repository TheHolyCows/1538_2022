/*
 * CowWebDebugger.h
 *
 *  Created on: Jan 21, 2016
 *      Author: kchau
 */

#ifndef SRC_COWWEBDEBUGGER_H_
#define SRC_COWWEBDEBUGGER_H_

#include <mutex>
#include <thread>
#include <queue>
#include <fstream>

namespace CowLib {

class CowLogger {
private:
    std::thread *m_Thread;
    static std::mutex m_Mutex;
    static std::queue<std::pair<std::string, double>> m_BufferQueue;
    static std::ofstream m_OutputFile;
    static CowLogger* m_Instance;
public:
    CowLogger();
    virtual ~CowLogger();
    static void Log(std::string key, double value);
    static CowLogger* GetInstance();
private:
    static void Handle();
};

} /* namespace CowLib */

#endif /* SRC_COWWEBDEBUGGER_H_ */
