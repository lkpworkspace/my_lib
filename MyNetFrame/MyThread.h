#ifndef __MyThread_H__
#define __MyThread_H__
#include <thread>
#include <mutex>
namespace my_master {

class MyThread
{
public:
	MyThread();
	~MyThread();
	virtual void Run() = 0;
    virtual void OnInit(){}
    virtual void OnExit(){}
	void Start();
	void Stop();
public:
    std::mutex m_mutex;
    std::thread::id m_id;
protected:
	static void ListenThread(void*);
private:
    std::thread* m_thread;
    bool m_isRuning;
};

} // end namespace
#endif
