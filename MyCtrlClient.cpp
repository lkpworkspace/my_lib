#include "MyCtrlClient.h"
#include <iostream>

MyCtrlClient::MyCtrlClient()
{
	ConnServer();
	OpenMMap();
	m_MMapPointer = GetMMAPPointer();
}
MyCtrlClient::~MyCtrlClient()
{
	ErrorProcess();
}

int MyCtrlClient::Go()
{
	// 发送连接请求事件
	BuildEvent1();
	if (!ReleaseSemaphore(m_serverEvent, 1, NULL))
		exit(-1);
	//SetEvent(m_serverEvent);
	// 等待回应
	WaitForSingleObject(m_clientEvent, INFINITE);
	// 获得回应
	ProcessEvent();

	// 开始线程接收数据
	this->Start();
	//ResetEvent(m_clientEvent);
	return 0;
}
////////////////////////////////////////////SendEvent
void MyCtrlClient::BuildEvent1()
{// 客户端连接服务器请求
	uint8_t* temp = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE);
	temp[0] = 0x01;
}
////////////////////////////////////////////事件处理函数
void MyCtrlClient::ProcessEvent()
{// 目前只有连接服务器事件
	// TODO...
	int event_num = GetEvent();
#if DEBUG
	std::cout << "event num = " << event_num << std::endl;
#endif
	switch (event_num)
	{
	case 1:
		// 获得共享内存的同步信号量的名字
		ProcessEvent1();
		break;
	case 2:
		break;
	default:
		break;
	}
}
int MyCtrlClient::ProcessEvent1()
{
	// 获得信号量名称
	int length = *((uint8_t*)m_MMapPointer + 1);
	uint8_t* buf = (uint8_t*)malloc(sizeof(wchar_t)*length + 1);
	memset(buf, 0, sizeof(wchar_t)*length + 1);
	memcpy(buf,
		((uint8_t*)m_MMapPointer) + 2,
		sizeof(WCHAR) * length + sizeof(WCHAR));
	// 打开信号量
	m_connInfo.semphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, (WCHAR*)buf);
	if (GetLastError() != 0)
	{
		std::cout << "OpenSemaphore error num = " << GetLastError() << std::endl;
		std::getchar();
	}
#if DEBUG
	//std::wstring sem(L"GCWT.STEPVR.SEMPHORE0");
	//m_connInfo.semphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, sem.c_str());
#endif
	m_connInfo.name = (wchar_t*)buf;
	//free(buf);
	return 0;
}
////////////////////////////////////////////辅助函数
int MyCtrlClient::ErrorProcess()
{
	if (m_MMap != NULL) CloseHandle(m_MMap);
	if (m_serverEvent != NULL) CloseHandle(m_serverEvent);
	if (m_clientEvent != NULL) CloseHandle(m_clientEvent);
	if (m_connInfo.semphore != NULL) CloseHandle(m_connInfo.semphore);
	return 0;
}

void* MyCtrlClient::GetMMAPPointer()
{
	void* temp = nullptr;
	temp = MapViewOfFile(m_MMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,      // memory start address 
		0);     // all memory space 
	if (NULL == temp)
	{
		std::cout << "MapViewOfFile fail = " << GetLastError() << std::endl;
		ErrorProcess();
	}
	return temp;
}

int MyCtrlClient::GetEvent()
{// 获取服务器端存放的事件类型
	uint8_t event_num;
	uint8_t* temp = ((uint8_t*)m_MMapPointer);
	memcpy(&event_num, m_MMapPointer, sizeof(uint8_t));
	return event_num;
}

int MyCtrlClient::ConnServer()
{
	// 打开服务器事件内核对象
#if 0
	m_serverEvent = OpenEvent(EVENT_ALL_ACCESS, false, SERVER_EVENT_NAME);
	if (m_serverEvent == NULL)
	{
		std::cout << "open server event kernel object fail..." << std::endl;
	}
	m_clientEvent = OpenEvent(EVENT_ALL_ACCESS, false, CLIENT_EVENT_NAME);
	if (m_clientEvent == NULL)
	{
		std::cout << "open client event kernel object fail..." << std::endl;
	}
#endif
#if 1
	m_serverEvent = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, SERVER_EVENT_NAME);
	if (m_serverEvent == NULL)
	{
		std::cout << "open server event kernel object fail..." << GetLastError() << std::endl;
	}
	m_clientEvent = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, CLIENT_EVENT_NAME);
	if (m_clientEvent == NULL)
	{
		std::cout << "open client event kernel object fail..." << GetLastError() << std::endl;
	}
#endif
	return 0;
}

int MyCtrlClient::OpenMMap()
{
	// 打开共享内存
	m_MMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		MEM_MAP_NAME);
	if (NULL == m_MMap)
	{
		std::cout << "OpenFileMapping fail = " << GetLastError() << std::endl;
		ErrorProcess();
	}
	return 0;
}