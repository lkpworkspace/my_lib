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
	// �������������¼�
	BuildEvent1();
	if (!ReleaseSemaphore(m_serverEvent, 1, NULL))
		exit(-1);
	//SetEvent(m_serverEvent);
	// �ȴ���Ӧ
	WaitForSingleObject(m_clientEvent, INFINITE);
	// ��û�Ӧ
	ProcessEvent();

	// ��ʼ�߳̽�������
	this->Start();
	//ResetEvent(m_clientEvent);
	return 0;
}
////////////////////////////////////////////SendEvent
void MyCtrlClient::BuildEvent1()
{// �ͻ������ӷ���������
	uint8_t* temp = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE);
	temp[0] = 0x01;
}
////////////////////////////////////////////�¼�������
void MyCtrlClient::ProcessEvent()
{// Ŀǰֻ�����ӷ������¼�
	// TODO...
	int event_num = GetEvent();
#if DEBUG
	std::cout << "event num = " << event_num << std::endl;
#endif
	switch (event_num)
	{
	case 1:
		// ��ù����ڴ��ͬ���ź���������
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
	// ����ź�������
	int length = *((uint8_t*)m_MMapPointer + 1);
	uint8_t* buf = (uint8_t*)malloc(sizeof(wchar_t)*length + 1);
	memset(buf, 0, sizeof(wchar_t)*length + 1);
	memcpy(buf,
		((uint8_t*)m_MMapPointer) + 2,
		sizeof(WCHAR) * length + sizeof(WCHAR));
	// ���ź���
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
////////////////////////////////////////////��������
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
{// ��ȡ�������˴�ŵ��¼�����
	uint8_t event_num;
	uint8_t* temp = ((uint8_t*)m_MMapPointer);
	memcpy(&event_num, m_MMapPointer, sizeof(uint8_t));
	return event_num;
}

int MyCtrlClient::ConnServer()
{
	// �򿪷������¼��ں˶���
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
	// �򿪹����ڴ�
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