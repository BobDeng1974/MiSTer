#ifndef COMMON_THREAD_RUNNABLE_H_
#define COMMON_THREAD_RUNNABLE_H_

#include <atomic>
#include <thread>
#include <string>
#include <sys/types.h>

using namespace std;

class Runnable
{
protected:
    thread m_thread;
    string m_name;
    pid_t m_thread_id = -1;
    atomic<bool> m_stop;
    atomic<bool> m_stopped;

public:
    Runnable() : m_thread(), m_name(), m_stop(false), m_stopped(true) {};
    Runnable(const string& name) : m_thread(), m_name(name), m_stop(false), m_stopped(true) {};
    virtual ~Runnable();

    Runnable(Runnable const&) = delete; 				// Disable copy constructor
    Runnable& operator =(Runnable const&) = delete;	// Disable assignments

    void start();
    void stop();

protected:
    void threadStart();
    virtual void run() = 0;
};

#endif /* COMMON_THREAD_RUNNABLE_H_ */
