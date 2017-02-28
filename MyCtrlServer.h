#ifndef __MyCtrl_H__
#define __MyCtrl_H__
#include <iostream>
#include <vector>
#include <Windows.h> 
#include <string>
#include "MyThread.h"
#include "StepVR_Log.h"

// 编译服务版
#define SERVICE
// 调试选项
#define DEBUG_SERVICE 1
#define DEBUG_SERVER 0

#if DEBUG_SERVICE
#include "MyDelayTest.h"
extern MyDelayTest g_delayTest;
#endif
/*
	共享内存结构划分:
		第一块:(200Byte)
			服务端放命令的地方
		第二块:(200Byte)
			客户端放命令的地方
		第三块:
			存放解析后数据的地方
		第四块:
			存放原始数据的地方
		第五块:
			待定
*/
// 第一块大小
#define SECTION_ONE_SIZE   200
// 第二块大小
#define SECTION_TWO_SIZE   200
// 第三块大小
#define SECTION_THREE_SIZE
// 第四块大小
#define SECTION_FOUR_SIZE
// 事件所占用空间(字节数)
#define EVENT_SIZE        1
// 共享内存大小
#define MMAP_SIZE         (1024*1024)
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

// 客户端连接使用的信号量信息
typedef struct conn_info
{
	HANDLE semphore;
	std::wstring name;
}conn_info;

class MyCtrlServer : public MyThread
{
public:
	MyCtrlServer();
	~MyCtrlServer();

	// 重写基类方法
	void Run();

	int Go();                                 // 开始接受客户端命令
	int CreateMMap();                         // 创建共享内存
	void* GetMMAPPointer();                   // 获得共享内存的首地址
	int ErrorProcess();                       // 出错处理
	int GetEvent();                           // 获取事件类型

	void InsertData(float* data, int len)
	{
		this->mutex_.lock();

		std::vector<conn_info>::iterator begin = m_semphores.begin();
		std::vector<conn_info>::iterator end = m_semphores.end();
		uint8_t* MMap_pointer = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE + SECTION_TWO_SIZE);

	
		// 将数据拷贝到共享内存
		memcpy((void*)MMap_pointer,
			(void*)data,
			len*sizeof(float));
#if DEBUG_SERVICE
		// biu biu biu
		g_delayTest.Send();
#endif
		// END
#if DEBUG_SERVER
		// 测试读出数据
		printf("length = %d\n", len);
		for (int i = 0; i < 200; ++i)
		{
			printf("%f\t", *((float*)MMap_pointer + i));
		}
		printf("\n");
#endif
		// 添加信号量
		for (; begin != end; ++begin)
		{
			ReleaseSemaphore(begin->semphore, 1, NULL);
		}

		this->mutex_.unlock();
	}
	//////////////////////////////////////////// 事件处理函数
	int ProcessEvent1();                      // 处理客户端连接事件
private:
	conn_info AssignSemphore();               // 分配信号量
	std::wstring ToWstring(std::string str);  // 将窄字符转换成宽字符
private:
	HANDLE m_serverEvent;
	HANDLE m_clientEvent;
	HANDLE m_hFileMapping;                    // 共享内存句柄
	void* m_MMapPointer;                      // 共享内存指针
	std::vector<conn_info> m_semphores;       // 进程同步信号量名
};


#endif