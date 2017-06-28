#ifndef __MyCtrlClient_H__
#define __MyCtrlClient_H__
#include <Windows.h>
#include <iostream>
#include "MyThread.h"

// 编译服务版客户端
#define SERVICE

#define DEBUG 1

#if DEBUG
#include "MyDelayTest.h"
extern MyDelayTest g_delayTest;
#endif


#define SECTION_ONE_SIZE   200
#define SECTION_TWO_SIZE   200
// 服务端使用命名事件对象的名称
#define SERVER_EVENT_NAME L"Global\\GCWT_STEPVR_SERVER_EVENT"
// 客户端使用命名事件对象的名称
#define CLIENT_EVENT_NAME L"Global\\GCWT_STEPVR_CLIENT_EVENT"
// 信号量名称前缀
#define SEMPHORE_NAME     L"Global\\GCWT_STEPVR_SEMPHORE"
// 共享内存名称
#ifdef SERVICE
#define MEM_MAP_NAME      L"Global\\GCWT_STEPVR_MMAP"
#else
#define MEM_MAP_NAME      L"GCWT_STEPVR_MMAP"
#endif

extern float* g_buf;
extern int g_len;

// 客户端连接使用的信号量信息
typedef struct conn_info
{
	HANDLE semphore;
	std::wstring name;
}conn_info;

class MyCtrlClient : public MyThread
{
public:
	MyCtrlClient();
	~MyCtrlClient();

	int Go();
	void GetServerNum()
	{// 测试代码,随后会删除
		int temp = 0;
		uint8_t* MMapPointer = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE + SECTION_TWO_SIZE);

		WaitForSingleObject(m_connInfo.semphore, INFINITE);

		// TODO...以下为测试代码
		// 获得服务器塞入得内容
		memcpy(&temp,
			MMapPointer,
			sizeof(int));
#if 1
		if (GetLastError() != 0)
		{
			std::cout << GetLastError() << std::endl;
		}
		std::cout << "get server num = " << temp << std::endl;
		// END
#endif
	}
	
	// 从共享内存中取得数据
	void GetServerData(float* data,int len)
	{
		uint8_t* MMapPointer = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE + SECTION_TWO_SIZE);

		WaitForSingleObject(m_connInfo.semphore, INFINITE);

		// TODO...以下为测试代码
		// 获得服务器塞入得内容
		memcpy((void*)data,
			(void*)MMapPointer,
			len*sizeof(float));
#if DEBUG
		// biu biu biu
		g_delayTest.Send();
#endif
#if 0
		for (int i = 0; i < 200; ++i)
		{
			printf("%f\t", *((float*)m_MMapPointer + i));
		}
#endif
	}

	// 重写基类方法(取数据)
	virtual void Run()
	{
		GetServerData(g_buf, g_len);
	}
private:
	int ConnServer();
	int OpenMMap();
	void* GetMMAPPointer();
	int GetEvent();
	int ErrorProcess();

	/////////////////////SendEvent
	void BuildEvent1();
	/////////////////////ProcessEvent
	void ProcessEvent();
	int ProcessEvent1();
private:
	HANDLE m_serverEvent;
	HANDLE m_clientEvent;
	HANDLE m_MMap;
	void* m_MMapPointer;
	conn_info m_connInfo;
};



#endif