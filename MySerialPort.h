#ifndef __MySerialPort_H__
#define __MySerialPort_H__

#include <windows.h>
#include <process.h>
#include <stdint.h>
#include <queue>
#include <string>
#include <sstream>
#include <devguid.h>
#include <SetupAPI.h>
#include <time.h>

#pragma comment(lib, "SetupAPI.lib")

// �洢�������ֺʹ��ں�
typedef struct _sComInfo_t
{
	std::string ComName;
	int comId;
	_sComInfo_t()
	{
		comId = -1;
	}
}sComInfo_t;

class MySerialPort
{
public:
	MySerialPort();
	~MySerialPort();
	bool OpenPort();
	bool OpenPort(int comNo);                            //�򿪴���
	bool ClosePort();                                    //�رմ���

	void SearchCom();                                    //�������ڲ������ڽṹ����
	int SearchComNo(std::string comName);                //����ָ�����ֵĴ��ڣ���û�ѵ��򷵻�0

	bool SendCmd(uint8_t *data_buf, int len);            //������
	UINT BytesToRead();                                  //�ж϶��˶��ٸ��ֽ�
	bool ReadChar(char &portData);                       //������

	bool IsOpen() { return port_ != INVALID_HANDLE_VALUE; }
	std::vector<sComInfo_t> cominfo_buf_;
private:
	int portNum_;
	HANDLE port_;
	CRITICAL_SECTION critical_section_;
};


#endif