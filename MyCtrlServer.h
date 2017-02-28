#ifndef __MyCtrl_H__
#define __MyCtrl_H__
#include <iostream>
#include <vector>
#include <Windows.h> 
#include <string>
#include "MyThread.h"
#include "StepVR_Log.h"

// ��������
#define SERVICE
// ����ѡ��
#define DEBUG_SERVICE 1
#define DEBUG_SERVER 0

#if DEBUG_SERVICE
#include "MyDelayTest.h"
extern MyDelayTest g_delayTest;
#endif
/*
	�����ڴ�ṹ����:
		��һ��:(200Byte)
			����˷�����ĵط�
		�ڶ���:(200Byte)
			�ͻ��˷�����ĵط�
		������:
			��Ž��������ݵĵط�
		���Ŀ�:
			���ԭʼ���ݵĵط�
		�����:
			����
*/
// ��һ���С
#define SECTION_ONE_SIZE   200
// �ڶ����С
#define SECTION_TWO_SIZE   200
// �������С
#define SECTION_THREE_SIZE
// ���Ŀ��С
#define SECTION_FOUR_SIZE
// �¼���ռ�ÿռ�(�ֽ���)
#define EVENT_SIZE        1
// �����ڴ��С
#define MMAP_SIZE         (1024*1024)
// �����ʹ�������¼����������
#define SERVER_EVENT_NAME L"Global\\GCWT_STEPVR_SERVER_EVENT"
// �ͻ���ʹ�������¼����������
#define CLIENT_EVENT_NAME L"Global\\GCWT_STEPVR_CLIENT_EVENT"
// �ź�������ǰ׺		
#define SEMPHORE_NAME     L"Global\\GCWT_STEPVR_SEMPHORE"
// �����ڴ�����	
#ifdef SERVICE
#define MEM_MAP_NAME      L"Global\\GCWT_STEPVR_MMAP"
#else
#define MEM_MAP_NAME      L"GCWT_STEPVR_MMAP"
#endif

// �ͻ�������ʹ�õ��ź�����Ϣ
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

	// ��д���෽��
	void Run();

	int Go();                                 // ��ʼ���ܿͻ�������
	int CreateMMap();                         // ���������ڴ�
	void* GetMMAPPointer();                   // ��ù����ڴ���׵�ַ
	int ErrorProcess();                       // ������
	int GetEvent();                           // ��ȡ�¼�����

	void InsertData(float* data, int len)
	{
		this->mutex_.lock();

		std::vector<conn_info>::iterator begin = m_semphores.begin();
		std::vector<conn_info>::iterator end = m_semphores.end();
		uint8_t* MMap_pointer = (((uint8_t*)m_MMapPointer) + SECTION_ONE_SIZE + SECTION_TWO_SIZE);

	
		// �����ݿ����������ڴ�
		memcpy((void*)MMap_pointer,
			(void*)data,
			len*sizeof(float));
#if DEBUG_SERVICE
		// biu biu biu
		g_delayTest.Send();
#endif
		// END
#if DEBUG_SERVER
		// ���Զ�������
		printf("length = %d\n", len);
		for (int i = 0; i < 200; ++i)
		{
			printf("%f\t", *((float*)MMap_pointer + i));
		}
		printf("\n");
#endif
		// ����ź���
		for (; begin != end; ++begin)
		{
			ReleaseSemaphore(begin->semphore, 1, NULL);
		}

		this->mutex_.unlock();
	}
	//////////////////////////////////////////// �¼�������
	int ProcessEvent1();                      // ����ͻ��������¼�
private:
	conn_info AssignSemphore();               // �����ź���
	std::wstring ToWstring(std::string str);  // ��խ�ַ�ת���ɿ��ַ�
private:
	HANDLE m_serverEvent;
	HANDLE m_clientEvent;
	HANDLE m_hFileMapping;                    // �����ڴ���
	void* m_MMapPointer;                      // �����ڴ�ָ��
	std::vector<conn_info> m_semphores;       // ����ͬ���ź�����
};


#endif