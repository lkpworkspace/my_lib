#include "MyCtrlServer.h"
#if DEBUG_SERVICE
MyDelayTest g_delayTest("COM2");
#endif

MyCtrlServer::MyCtrlServer()
{
	m_hFileMapping = INVALID_HANDLE_VALUE;
	m_serverEvent = INVALID_HANDLE_VALUE;
	m_clientEvent = INVALID_HANDLE_VALUE;
	m_MMapPointer = nullptr;
	m_semphores.clear();
}

MyCtrlServer::~MyCtrlServer()
{
	ErrorProcess();
}

int MyCtrlServer::Go()
{
	// 创建C/S通信事件
	//m_serverEvent = CreateEvent(NULL, TRUE, FALSE, SERVER_EVENT_NAME);
	//m_clientEvent = CreateEvent(NULL, TRUE, FALSE, CLIENT_EVENT_NAME);
	SECURITY_DESCRIPTOR sd;
	if (0 == InitializeSecurityDescriptor(&sd,
		SECURITY_DESCRIPTOR_REVISION) ||
		0 == SetSecurityDescriptorDacl(&sd,
		TRUE,
		(PACL)0,
		FALSE))
	{
		/* Failed to create security descriptor. */
		StepVR_Log::GetInstance().AddLog("create sd fail");
	}
	else
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;

		//HANDLE sh = CreateSemaphore(&sa, 1, 1, "Global\\bitmap");
		m_serverEvent = CreateSemaphore(&sa, 0, 1, SERVER_EVENT_NAME);
		m_clientEvent = CreateSemaphore(&sa, 0, 1, CLIENT_EVENT_NAME);
		if (m_serverEvent == NULL || m_clientEvent == NULL)
		{
			StepVR_Log::GetInstance().AddLog("mmap open event fail");
#if DEBUG_SERVER
			std::cout << "open event fail : " << GetLastError() << std::endl;
#endif
		}
		else
		{
			StepVR_Log::GetInstance().AddLog("mmap open event success");
#if DEBUG_SERVER
			std::cout << "Open event success" << std::endl;
#endif
		}
	}
	//m_serverEvent = CreateSemaphore(NULL, 0, 1, SERVER_EVENT_NAME);
	//m_clientEvent = CreateSemaphore(NULL, 0, 1, CLIENT_EVENT_NAME);
	/*if (m_serverEvent == NULL || m_clientEvent == NULL)
	{
		StepVR_Log::GetInstance().AddLog("open event fail");
		std::cout << "open event fail : " << GetLastError() << std::endl;
	}
	else
	{
		std::cout << "Open event success" << std::endl;
	}*/

	// 创建共享内存
	CreateMMap();
	
	// 获得共享内存指针
	m_MMapPointer = GetMMAPPointer();
	// 启动接受客户端命令线程
#if DEBUG
	std::cout << "mmap server start" << std::endl;
#endif
	StepVR_Log::GetInstance().AddLog("waiting for client connect");
	this->Start();
	return 0;
}

int MyCtrlServer::CreateMMap()
{
#ifdef SERVICE
	// 创建安全描述符
	SECURITY_DESCRIPTOR sd;
	if (0 == InitializeSecurityDescriptor(&sd,
		SECURITY_DESCRIPTOR_REVISION) ||
		0 == SetSecurityDescriptorDacl(&sd,
		TRUE,
		(PACL)0,
		FALSE))
	{
		/* Failed to create security descriptor. */
		StepVR_Log::GetInstance().AddLog("sd fail");
	}
	else
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;

		m_hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE,
			&sa,
			PAGE_READWRITE,
			0,
			MMAP_SIZE,
			MEM_MAP_NAME);
	}
#else
	m_hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		MMAP_SIZE,
		MEM_MAP_NAME);
#endif
	// end
	if (NULL == m_hFileMapping)
	{
		StepVR_Log::GetInstance().AddLog("Create file mapping fail");
#if DEBUG_SERVER
		std::cout << "CreateFileMapping fail : " << GetLastError() << std::endl;
#endif
		return ErrorProcess();
	}
	else
	{
		StepVR_Log::GetInstance().AddLog("create file mapping success");
#if DEBUG_SERVER
		std::cout << "Create File Mapping success" << std::endl;
#endif
	}
	return 0;
}

conn_info MyCtrlServer::AssignSemphore()
{
	conn_info temp;
	char suffix[20] = { 0 };

	_itoa(m_semphores.size(), suffix, 10);
	temp.name = SEMPHORE_NAME + ToWstring(suffix);
	// 设置安全描述符
	SECURITY_DESCRIPTOR sd;
	if (0 == InitializeSecurityDescriptor(&sd,
		SECURITY_DESCRIPTOR_REVISION) ||
		0 == SetSecurityDescriptorDacl(&sd,
		TRUE,
		(PACL)0,
		FALSE))
	{
		/* Failed to create security descriptor. */
		StepVR_Log::GetInstance().AddLog("sd fail");
	}
	else
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;

		temp.semphore = CreateSemaphore(&sa, 0, 1, temp.name.c_str());
	}
	// end
#if DEBUG_SERVER
	if (GetLastError() != 0)
		std::cout << "create client semphore error num = " << GetLastError() << std::endl;
#endif
	this->mutex_.lock();
	m_semphores.push_back(temp);
	this->mutex_.unlock();

	return temp;
}
//////////////////////////////////////////////////////////事件处理
int MyCtrlServer::ProcessEvent1()
{
	conn_info info;

	info = AssignSemphore();
	*((uint8_t*)m_MMapPointer) = 0x01;
	*((uint8_t*)m_MMapPointer + 1) = info.name.length();
	memcpy(((uint8_t*)m_MMapPointer) + 2,
		info.name.c_str(), 
		sizeof(WCHAR)*info.name.length());
#if DEBUG
	std::cout << "client connect info: " << std::endl;
	std::cout << "    length = " << info.name.length() << "   ";
	std::wcout << info.name << std::endl;
#endif
	// 触发客户端等待事件
	//SetEvent(m_clientEvent);
	ReleaseSemaphore(m_clientEvent, 1, NULL);
	return 0;
}
//////////////////////////////////////////////////////////事件发送

//////////////////////////////////////////////////////////方法重写
// 此线程处理事件消息
void MyCtrlServer::Run()
{
	WaitForSingleObject(m_serverEvent, INFINITE);
	StepVR_Log::GetInstance().AddLog("get client conn info");
	int event_num = GetEvent();
	switch (event_num)
	{
	case 1:
		ProcessEvent1();
		break;
	case 2:
		break;
	default:
		break;
	}

	//ResetEvent(m_serverEvent);
}

//////////////////////////////////////////////////////////辅助函数
int MyCtrlServer::GetEvent()
{
	uint8_t event_num = 0x00;
	memcpy(&event_num, ((uint8_t*)m_MMapPointer + SECTION_ONE_SIZE), sizeof(uint8_t));
	return event_num;
}

void* MyCtrlServer::GetMMAPPointer()
{
	void* temp = nullptr;
	temp = MapViewOfFile(m_hFileMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,      // memory start address 
		0);     // all memory space 
	if (NULL == temp)
	{
		StepVR_Log::GetInstance().AddLog("get mmap pointer fail");
#if DEBUG_SERVER
		std::cout << "MapViewOfFile : " << GetLastError() << std::endl;
#endif
		ErrorProcess();
	}
	else
	{
		StepVR_Log::GetInstance().AddLog("get mmap pointer success");
#if DEBUG_SERVER
		std::cout << "Get MMap pointer success" << std::endl;
#endif
	}
	return temp;
}

std::wstring MyCtrlServer::ToWstring(std::string str)
{
	DWORD num = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	WCHAR *wword;
	
	wword = (WCHAR*)malloc(num*sizeof(WCHAR));
	memset(wword, 0, num*sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wword, num);
	std::wstring temp(wword);
	delete wword;

	return temp;
}

int MyCtrlServer::ErrorProcess()
{
	std::vector<conn_info>::iterator begin = m_semphores.begin();
	std::vector<conn_info>::iterator end = m_semphores.end();

	if (NULL != m_hFileMapping)CloseHandle(m_hFileMapping);
	for (; begin != end; ++begin)
	{
		if (begin->semphore != NULL) CloseHandle(begin->semphore);
	}
	return -1;
}